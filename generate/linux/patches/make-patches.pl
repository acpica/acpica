#! /usr/bin/perl
#
# Make linux patches for ACPICA
#
# Usage:
#   edit $release to reflect desired tag (release) of ACPICA
#   run perl make-patches.pl
#   collect *.patch files
#
# Requires: cvs, cvsp
#
# Note: Must get the *previous* release of ACPICA to generate the patches
#
# These warnings are ok:
# can't open cvsps.cache for write: No such file or directory
#
use File::stat;

#
# Configuration
#
$release = "R03_20_07";

$patch_from = "Bob Moore <robert.moore\@intel.com>";
$patch_signoff = "Bob Moore <robert.moore\@intel.com>";
$linux_patch_dir = "patches.linux";
$cvs_patch_dir = "patches.cvs";
$cvsps_log = 'cvsps.log';
$mbox_name = "$linux_patch_dir/patches.mbox";

$linux_patch_count;
$patch_num;



#
# Main function
#
# 1) Get the latest version of the acpisrc utility and generate it
# 2) Checkout the specified tagged release of the ACPICA source
# 3) Create the CVS logfile and patches against the original ACPICA source
# 4) Create the Linux patches
#


# Generate the acpisrc utility

#system("echo [make-patches] Generate acpisrc utility from source");
#system("perl acpisrc.pl");


# Checkout the previous ACPICA release

system("echo [make-patches] Getting clean ACPICA release, version $release");
system("perl get-acpi.pl $release");


# Create CVS log

system("echo [make-patches] Creating the CVS log");
system("cd Acpi/source; cvsps -z 6 -u -r $release > ../../$cvsps_log");


# Create CVS patches

system("echo [make-patches] Creating the CVS patches");
system("mkdir -p $cvs_patch_dir");
system("cd Acpi/source; cvsps -z 6 -r $release -g -p ../../$cvs_patch_dir");


# Create "linuxized" reference ACPICA directory

system("echo [make-patches] Creating the Linuxized ACPICA source");
system("sh linuxize.sh");


# Create the linux patches, one per file

system("echo [make-patches] Creating the Linux patches");
system("rm -rf $linux_patch_dir");
system("mkdir -p $linux_patch_dir");
&make_patches;


# Create the mailbox format patch file (contains all linux patches)

system("echo [make-patches] Creating the mbox patch file");
&make_mbox;


#
# Walk the log created by cvsps, invoke callback for each entry
# Example log entry:
#
# ---------------------
# PatchSet 16465 
# Date: 2007/03/27 20:25:46
# Author: rmoore1
# Branch: HEAD
# Tag: (none) 
# Log:
# Changes for Cygwin compatibility.
# Allow generation of ACPICA apps on Cygwin.
# 
# Members: 
# 	include/platform/acenv.h:1.131->1.132 
# 	include/platform/aclinux.h:1.42->1.43 
# 	tools/acpisrc/acpisrc.h:1.41->1.42 
# 
sub walk_cvsps_log
{
    my $callback = @_[0];
    my $patch_name;
    my $date;
    my $tag;
    my $file_name;
    my $short_log;
    my $long_log;
    my $log_entry;
    my $short_idx;


    # open the CVS log file

    open(INFO, $cvsps_log) or die ("Cannot open $cvsps_log");

    # process each entry in the log file

    while($_ = <INFO>) {
        if (s/^PatchSet\s*(\d+)/\1/) {
            $patch_name = $1;
        }

        # extract the patchset checkin date
        
        if (s/^Date:\s*(.+)/\1/) {
            $date = $1;
        }

        # extract the CVS tag, "(none)" if none

        if (s/^Tag:\s*(.+)/\1/) {
            $tag = $1;
            chop $tag;

            # Construct the filename for the patch

            $file_name = "$linux_patch_dir/$patch_name";
            if ($tag !~ /\(none\)/) {
                $file_name .= "-".$tag;
            }
            $file_name .= ".patch";
        }

        # extract the CVS log message and make the linux patch

        if (/^Log:/) {
            $/ = "";
            $log_entry = <INFO>;
            $/ = "\n";

            $short_idx = index ($log_entry, ".");
            $short_log = substr ($log_entry, 0, $short_idx);
            $long_log = substr ($log_entry, $short_idx + 2, length($log_entry) - $short_idx -2);

            &$callback ($patch_name, $date, $file_name, $short_log, $long_log);
        }
    }
    close(INFO);
}


#
# Create the mailbox format patchfile from the individual patches
#
sub make_mbox
{
    $linux_patch_count = 0;
    $patch_num = 0;
    system("rm -f $mbox_name");
    
    &walk_cvsps_log (count_patches);
    &walk_cvsps_log (make_mbox_entry);
}


#
# Count the individual patches
#
sub count_patches
{
    my $file_name = @_[2];

    open(PTCH, $file_name) or return;
    close(PTCH);

    $linux_patch_count++;
}


#
# Make one mailbox entry and append it to the mbox file
#
sub make_mbox_entry
{
    my $patch_name = @_[0];
    my $date = @_[1];
    my $file_name = @_[2];
    my $short_log = @_[3];
    my $long_log = @_[4];



    open(PTCH, $file_name) or return;
    close(PTCH);

    $patch_num++;

    # Emit common patch header for mbox

    open(MBOX, ">>$mbox_name") or die ("Cannot open $mbox_name for appending");
    print(MBOX "From nobody Wed Mar 21 16:27:33 2007\n");
    print(MBOX "Subject: [Patch $patch_num/$linux_patch_count] ACPICA: $short_log\n");
    print(MBOX "From: $patch_from\n");
    print(MBOX "Date: $date\n");
    print(MBOX "\n");
    close(MBOX);

    # Append the full patch to the mbox file

    system("cat $file_name >> $mbox_name");
    open(MBOX, ">>$mbox_name") or die ("Cannot open $mbox_name for appending");
    print(MBOX "\n");
    close(MBOX);
}


#
# This function creates the linux patches from the CVS log file.
# Requires the cvs log and the cvs patch set (both created by cvsps)
#
sub make_patches
{
    $linux_patch_count = 0;
    &walk_cvsps_log (make_patch);

    # cleanup

    system("rm -rf original.linux");
    system("rm -rf new.linux");
    system("echo [make-patches] Created $linux_patch_count Linux patches");
}



#
# This function creates a linux patch from the corresponding
# CVS patch against the original ACPICA source tree
#
sub make_patch
{
    my $patch_name = @_[0];
    my $date = @_[1];
    my $file_name = @_[2];
    my $short_log = @_[3];
    my $long_log = @_[4];


    system("echo [make-patches] Creating Linux patch named $patch_name");

    # Take a snapshot of current "new' linuxized tree: copy to "original.linux"

    system("rm -rf original.linux");
    system("mv new.linux/ original.linux");

    # Apply CVS patch to the non-linuxized ACPICA tree and linuxize the tree to "new.linux"

    system("patch -p0 < $cvs_patch_dir/$patch_name.patch");
    system("sh linuxize.sh");

    # diff the new and original linuxed trees

    system("diff -Nurp original.linux new.linux > diff.linux");

    #
    # The patch could be zero length if it patches a non-linux part of the ACPICA
    # tree. In this case, we just ignore the patch, don't create a linux patch
    #
    my $stats = stat ("diff.linux");
    if ($stats->size == 0) {
        print "[make-patches] Skipping patch named $patch_name, Linux version is empty\n";
        system("rm -f diff.linux");
        return;
    }

    $linux_patch_count++;

    # Format the log (eliminate long lines) and append it

    system("rm -f temp temp2");
    open(PTCH, ">temp") or die ("Cannot open temp for writing");
    print(PTCH $long_log);
    close(PTCH);

    system("fmt -w68 temp >temp2");
    system("cat temp2 >> $file_name");
    system("rm -f temp temp2");

    # Complete the header

    open(PTCH, ">>$file_name") or die ("Cannot open $file_name for appending");
    print(PTCH "Signed-off-by: $patch_signoff\n");
    print(PTCH "---\n\n");
    close(PTCH);

    # Append statistics

    system("diffstat diff.linux >> $file_name");
    open(PTCH, ">>$file_name") or die ("Cannot open $file_name for appending");
    print(PTCH "\n");
    close(PTCH);

    # Append the actual patch to the file

    system("cat diff.linux >> $file_name");
    system("rm -f diff.linux");
}

