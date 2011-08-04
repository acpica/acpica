#!/bin/sh
#
# Generate acpisrc utility
#

git_root=$1

mkdir -p bin
cp $git_root/generate/linux/Makefile.acpisrc $git_root/source/tools/acpisrc/Makefile
cp $git_root/source/os_specific/service_layers/osunixdir.c $git_root/source/tools/acpisrc
make -C $git_root/source/tools/acpisrc
cp $git_root/source/tools/acpisrc/acpisrc bin
