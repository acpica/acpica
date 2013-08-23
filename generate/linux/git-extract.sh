#!/bin/sh
#
# NAME:
#         git-extract.sh - extract linuxized sources/patches from the ACPICA
#                          git repository
#
# SYNOPSIS:
#         git-extract.sh [-c] [-f from] [-i index] [-r] [-s sign] <commit>
#
# DESCRIPTION:
#         Extract linuxized patches from the git repository.
#         Modes:
#         !-r mode (extracting patches mode):
#                  Extract the linuxized patch of the given commit from the
#                  ACPICA git repository.
#          -r mode (extracting sources mode):
#                  Extract the linuxized repository of the given commit from
#                  the ACPICA git repository.
#         Options:
#          -c       Force regeneration of acpisrc.
#          -f from  Specify name <email> for From field.
#          -i index Specify patch index.
#          -s sign  Specify name <email> for Signed-off-by field.
#	  NOTE: Be careful using this script on a repo in detached HEAD mode.
#

usage() {
	echo "Usage: `basename $0` [-c] [-f from] [-i index] [-r] [-s sign] <commit>"
	echo "Where:"
	echo "     -c: Force regeneration of acpisrc."
	echo "     -f: Specify name <email> for From field (default to author)."
	echo "     -i: Specify patch index (default to 0)."
	echo "     -r: Extract Linux repository of the commit."
	echo "         or"
	echo "         Extract Linux patch of the commit."
	echo "     -s: Specify name <email> for Signed-off-by field."
	echo " commit: GIT commit (default to HEAD)."
	exit 1
}

FROM_EMAIL="%aN <%aE>"
INDEX=0

while getopts "cf:i:rs:" opt
do
	case $opt in
	c) FORCE_ACPISRC=force;;
	r) EXTRACT_REPO=true;;
	s) SIGNED_OFF_BY=$OPTARG;;
	f) FROM_EMAIL=$OPTARG;;
	i) INDEX=$OPTARG;;
	?) echo "Invalid argument $opt"
	   usage;;
	esac
done
shift $(($OPTIND - 1))

version=`git log -1 -c $1 --format=%H | cut -c1-8`

SCRIPT=`(cd \`dirname $0\`; pwd)`
source $SCRIPT/libacpica.sh

GE_acpica_repo=$CURDIR/acpica-$version
GE_linux_repo=$CURDIR/linux-$version
GE_linux_before=$CURDIR/linux.before
GE_linux_after=$CURDIR/linux.after

linuxize()
{
	# Be careful with local variable namings
	repo_acpica=$1
	repo_linux=$2

	mkdir -p $repo_linux/source
	cp -rf $repo_acpica/source $repo_linux/

	echo "[git-extract.sh]  Converting format (hierarchy)..."
	linuxize_hierarchy_noref $repo_linux

	echo "[git-extract.sh]  Converting format (acpisrc)..."
	$ACPISRC -ldqy $repo_linux $repo_linux > /dev/null

	echo "[git-extract.sh]  Converting format (lindent)..."
	lindent $repo_linux
}

FORMAT="From %H Mon Sep 17 00:00:00 2001%nFrom: $FROM_EMAIL%nData: %aD%nSubject: [PATCH $INDEX] ACPICA: %s%n%n%b"

(
	echo "[git-extract.sh] Extracting GIT ($SRCDIR)..."
	# Cleanup
	rm -rf $GE_acpica_repo

	echo "[git-extract.sh] Creating ACPICA repository (acpica-$version)..."
	git clone $SRCDIR $GE_acpica_repo > /dev/null || exit 2
	(
		cd $GE_acpica_repo
		git reset $version --hard >/dev/null 2>&1
	)

	echo "[git-extract.sh] Generating tool (acpisrc)..."
	make_acpisrc $GE_acpica_repo $FORCE_ACPISRC > /dev/null

	if [ "x$EXTRACT_REPO" = "xtrue" ] ; then
		# Cleanup
		rm -rf $GE_linux_repo

		echo "[git-extract.sh] Creating Linux repository (linux-$version)..."
		linuxize $GE_acpica_repo $GE_linux_repo
	else
		GE_acpica_patch=$CURDIR/acpica-$version.patch
		GE_linux_patch=$CURDIR/linux-$version.patch

		# Cleanup
		rm -rf $GE_linux_after
		rm -rf $GE_linux_before
		rm -f $GE_linux_patch
		rm -f $GE_acpica_patch

		(
			echo "[git-extract.sh] Creating ACPICA patch (acpica-$version.patch)..."
			cd $GE_acpica_repo
			git format-patch -1 --stdout >> $GE_acpica_patch
		)

		echo "[git-extract.sh] Creating Linux repository ($version+)..."
		linuxize $GE_acpica_repo $GE_linux_after

		(
			echo "[git-extract.sh] Patching repository (acpica-$version)..."
			cd $GE_acpica_repo
			patch -R -p1 < $GE_acpica_patch > /dev/null
		)

		echo "[git-extract.sh] Creating Linux repository ($version-)..."
		linuxize $GE_acpica_repo $GE_linux_before

		(
			echo "[git-extract.sh] Creating Linux patch (linux-$version.patch)..."
			cd $CURDIR
			tmpfile=`tempfile`
			diff -Nurp linux.before linux.after >> $tmpfile

			if [ $? -ne 0 ]; then
				GIT_LOG_FORMAT=`echo $FORMAT`
				eval "git log -c $version -1 --format=\"$GIT_LOG_FORMAT\" > $GE_linux_patch"
				if [ "x$SIGNED_OFF_BY" != "x" ]; then
					echo "" >> $GE_linux_patch
					echo "Signed-off-by: $SIGNED_OFF_BY" >> $GE_linux_patch
				fi
				echo "---" >> $GE_linux_patch
				diffstat $tmpfile >> $GE_linux_patch
				echo >> $GE_linux_patch
				cat $tmpfile >> $GE_linux_patch
			else
				echo "Warning: Linux version is empty, skipping $version..."
			fi
			rm -f $tmpfile
		)

		# Cleanup temporary directories
		rm -rf $GE_linux_before
		rm -rf $GE_linux_after
		rm -rf $GE_acpica_repo
	fi
)
