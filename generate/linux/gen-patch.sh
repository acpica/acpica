#!/bin/bash
#
# NAME:
#         gen-patch.sh - extract linuxized patches from the ACPICA git
#                        repository
#
# SYNOPSIS:
#         gen-patch.sh [-f from] [-i index] [-l link] [-m maintainer] <commit>
#
# DESCRIPTION:
#         Extract linuxized patches from the git repository.
#         Options:
#          -i index Specify patch index.
#          -l: Specify a URL prefix that can be used to link the commit.
#          -m: Specify maintainer name <email> for Signed-off-by field.
#

usage() {
	echo "Usage: `basename $0` [-f from] [-i index] [-l link] [-m maintainer] <commit>"
	echo "Where:"
	echo "     -i: Specify patch index (default to 0)."
	echo "     -l: Specify a URL prefix that can be used to link the commit."
	echo "     -m: Specify maintainer name <email> for Signed-off-by field."
	echo " commit: GIT commit (default to HEAD)."
	exit 1
}

COMMITTER="`git config user.name` <`git config user.email`>"
INDEX=0
LINK=https://github.com/acpica/acpica/commit/

while getopts "i:l:m:" opt
do
	case $opt in
	i) INDEX=$OPTARG;;
	l) LINK=$OPTARG;;
	m) MAINTAINER=$OPTARG;;
	?) echo "Invalid argument $opt"
	   usage;;
	esac
done
shift $(($OPTIND - 1))

after=`git log -1 -c $1 --format=%H | cut -c1-8`
before=`git log -1 -c $1^1 --format=%H | cut -c1-8`

SCRIPT=`(cd \`dirname $0\`; pwd)`
. $SCRIPT/libacpica.sh

GP_acpica_repo=$CURDIR/acpica.repo
GP_acpica_url=$LINK
GP_linux_before=$CURDIR/linux.before
GP_linux_after=$CURDIR/linux.after
GP_acpica_patch=$CURDIR/acpica-$after.patch
GP_linux_patch=$CURDIR/linux-$after.patch

echo "[gen-patch.sh] Extracting GIT ($SRCDIR)..."
# Cleanup
rm -rf $GP_linux_before
rm -rf $GP_linux_after
rm -rf $GP_acpica_repo
git clone $SRCDIR $GP_acpica_repo > /dev/null || exit 2

generate_refs()
{
	echo "Link: ${GP_acpica_url}$1"
}

generate_sobs()
{
	echo "Signed-off-by: $AUTHOR"
	if [ "x$MAINTAINER" != "x" ]; then
		echo "Signed-off-by: $MAINTAINER"
	fi
	echo "Signed-off-by: $COMMITTER"
}

echo "[gen-patch.sh] Creating ACPICA repository ($after)..."
(
	cd $GP_acpica_repo
	git reset $after --hard >/dev/null 2>&1
)

echo "[gen-patch.sh] Creating ACPICA patch (acpica-$after.patch)..."
(
	cd $GP_acpica_repo
	git format-patch -1 --stdout >> $GP_acpica_patch
)

echo "[gen-patch.sh] Creating Linux repository ($after)..."
(
	cd $GP_acpica_repo/generate/linux
	if [ ! -f ./gen-repo.sh ]; then
		cp $SRCDIR/generate/linux/gen-repo.sh ./
	fi
	./gen-repo.sh -c $after
)
mv -f $GP_acpica_repo/generate/linux/linux-$after $GP_linux_after

echo "[gen-patch.sh] Creating ACPICA repository ($before)..."
(
	cd $GP_acpica_repo
	git reset $before --hard >/dev/null 2>&1
)

echo "[gen-patch.sh] Creating Linux repository ($before)..."
(
	cd $GP_acpica_repo/generate/linux
	if [ ! -f ./gen-repo.sh ]; then
		cp $SRCDIR/generate/linux/gen-repo.sh ./
	fi
	./gen-repo.sh -c $before
)
mv -f $GP_acpica_repo/generate/linux/linux-$before $GP_linux_before

(
	echo "[gen-patch.sh] Creating Linux patch (linux-$after.patch)..."
	cd $CURDIR
	tmpdiff=`tempfile`
	tmpdesc=`tempfile`
	diff -Nurp linux.before linux.after >> $tmpdiff

	if [ $? -ne 0 ]; then
		AUTHOR_NAME=`git log -c $after -1 --format="%aN"`
		AUTHOR_EMAIL=`git log -c $after -1 --format="%aE"`
		if [ "x$AUTHOR_NAME" = "xRobert Moore" ]; then
			AUTHOR_NAME="Bob Moore"
		fi
		if [ "x$AUTHOR_EMAIL" = "xRobert.Moore@intel.com" ]; then
			AUTHOR_EMAIL="robert.moore@intel.com"
		fi
		AUTHOR="${AUTHOR_NAME} <${AUTHOR_EMAIL}>"
		FORMAT="From %H Mon Sep 17 00:00:00 2001%nFrom: $COMMITTER%nData: %aD%nFrom: $AUTHOR%nSubject: [PATCH $INDEX] ACPICA: %s%n%nACPICA commit %H%n%n%b"
		GIT_LOG_FORMAT=`echo $FORMAT`
		eval "git log -c $after -1 --format=\"$GIT_LOG_FORMAT\" | \
		tac | awk 'NF>0{x=1}x' | tac > $tmpdesc"
		cat $tmpdesc > $GP_linux_patch
		echo "" >> $GP_linux_patch
		generate_refs $after >> $GP_linux_patch
		generate_sobs | uniq >> $GP_linux_patch
		$ACPISRC -ldqy $GP_linux_patch $GP_linux_patch > /dev/null
		echo "---" >> $GP_linux_patch
		diffstat $tmpdiff >> $GP_linux_patch
		echo >> $GP_linux_patch
		cat $tmpdiff >> $GP_linux_patch
	else
		echo "Warning: Linux version is empty, skipping $after..."
	fi
	rm -f $tmpdiff
	rm -f $tmpdesc
)

# Cleanup temporary directories
rm -rf $GP_linux_before
rm -rf $GP_linux_after
rm -rf $GP_acpica_repo
