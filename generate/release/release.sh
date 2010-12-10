#******************************************************************************
#
# ACPICA release generation script for Cygwin/Windows execution
#
# front end for build.sh
#
#******************************************************************************

bash build.sh $1
#
# d2u:
#
# for i in `find . -type f`
# do
# echo $i
# tr -d '\r' < $i >$i.n
# mv -f $i.n $i
# done


