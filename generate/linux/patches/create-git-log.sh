#!/bin/sh

old_release=$1
new_release=$2

commits="`git rev-list --reverse $old_release..$new_release`"
commits_count="`git rev-list --reverse $old_release..$new_release | wc -l`"

digit=1
while [ $commits_count -gt 9 ] ; do
        commits_count=`expr $commits_count / 10`
        digit=`expr $digit + 1`
done

num=0

for commit in $commits ; do
        num=`expr $num + 1`

	#create git log similar to cvs log, so we can reuse code in make-patches.pl
        patchnum=`printf "%.${digit}d" $num`
	echo "---------------------"
	echo "PatchSet $patchnum"

	format="Date: %ad%nAuthor: %an%nBranch: HEAD%nTag: (none)%nLog:%n%s"

	body=`git show --pretty=format:"%b" $commit | grep "<unknown>"`
	if [ -z "$body" ] ; then
		format="$format%n%b"
	fi

	l=`git show --pretty=format:"${format}%n" $commit | grep -n "diff --git" | head -n 1 | awk -F: '{print $1}'`
	if [ ! -z "$l" ] ; then
		l=`expr $l - 1`
		git show --pretty=format:"${format}%n" $commit | head -n $l 
	fi
done
