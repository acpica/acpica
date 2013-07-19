#!/bin/sh
#
# Generate acpisrc utility
#

identify_bits()
{
	arch=`uname -m`
	no64=`echo ${arch%64}`

	if [ "x$arch" != "x$no64" ] ; then
		echo 64
	else
		echo 32
	fi
}

git_root=$1
bits=`identify_bits`

mkdir -p bin
make -C $git_root acpisrc

if [ ! -f $git_root/generate/unix/bin$bits/acpisrc ]; then
	bits=
fi

cp $git_root/generate/unix/bin$bits/acpisrc bin

