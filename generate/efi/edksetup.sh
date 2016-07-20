#!/bin/sh

EFIPROGS="acpidump"

EFIDIR=`(cd \`dirname $0\`; pwd)`
TOPDIR=`(cd ${EFIDIR}/../..; pwd)`

echo "Copying AcpiPkg package files..."
cp -f ${EFIDIR}/AcpiPkg.dec ${TOPDIR}/AcpiPkg.dec
cp -f ${EFIDIR}/AcpiPkg.dsc ${TOPDIR}/AcpiPkg.dsc
for p in ${EFIPROGS}; do
	echo "Copying $p build files..."
	cp -f ${EFIDIR}/$p/${p}.inf ${TOPDIR}/source/${p}.inf
done
