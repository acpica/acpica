#
# get-acpi
#
# Checkout a version of ACPICA, including all source, headers, and
# makefiles. The parameter, if given, specifies the CVS tag to be checked out.
#
# requires CVS
#
# modify cvshome as necessary.
#

$cvshome = ":pserver:rmoore1\@cvs.sc.intel.com:/home/cmplr/cvs/acpica";
$cvsroot = "Acpi";

$version;
$version_name = "cvs-HEAD";


# Get optional parameter and use as the CVS tag

if ($ARGV[0])
{
    $version = "-r $ARGV[0]";
    $version_name = $ARGV[0];
}

# Checkout entire source and linux makefiles

system("echo Getting version $version_name of ACPICA");
system("rm -rf $cvsroot/source; cvs -z 6 -d $cvshome co $version $cvsroot/source");
system("rm -rf $cvsroot/source/tools/aapits");
system("rm -rf $cvsroot/generate/linux; cvs -z 6 -d $cvshome co $version $cvsroot/generate/linux");

