#!/bin/sh

old_release=$1
new_release=$2
git_patch_dir=$3

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
	
	#patch file name: 01.patch 02.patch ...
	filename=`printf "%.${digit}d" $num`	
	git show $commit > ${git_patch_dir}/${filename}.patch
done

