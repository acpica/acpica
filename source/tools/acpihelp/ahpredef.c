/******************************************************************************
 *
 * Module Name: ahpredef - Table of all known ACPI predefined names
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2011, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights.  You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code.  No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision.  In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change.  Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee.  Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution.  In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
 * Intel shall be used in advertising or otherwise to promote the sale, use or
 * other dealings in products derived from or relating to the Covered Code
 * without prior written authorization from Intel.
 *
 * 4. Disclaimer and Export Compliance
 *
 * 4.1. INTEL MAKES NO WARRANTY OF ANY KIND REGARDING ANY SOFTWARE PROVIDED
 * HERE.  ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT,  ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES.  INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS.  INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.  THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government.  In the
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/

#include "acpihelp.h"

/*
 * Predefined ACPI names, with short description and return value.
 * This table was extracted directly from the ACPI specification.
 */
const AH_PREDEFINED_NAME    AslPredefinedInfo[] =
{
    {"_ACx",    "Active Cooling", "Returns the active cooling policy threshold values"},
    {"_ADR",    "Address", "Returns the address of a device on its parent bus"},
    {"_ALC",    "Ambient Light Chromaticity", "Returns the ambient light color chromaticity"},
    {"_ALI",    "Ambient Light Illuminance", "Returns the ambient light brightness"},
    {"_ALN",    "Alignment", "Base alignment, Resource Descriptor field"},
    {"_ALP",    "Ambient Light Polling", "Returns the ambient light sensor polling frequency"},
    {"_ALR",    "Ambient Light Response", "Returns the ambient light brightness to display brightness mappings"},
    {"_ALT",    "Ambient Light Temperature", "Returns the ambient light color temperature"},
    {"_ALx",    "Active List", "Returns a list of active cooling device objects"},
    {"_ART",    "Active cooling Relationship Table", "Returns thermal relationship information between platform devices and fan devices"},
    {"_ASI",    "Address Space Id", "Resource Descriptor field"},
    {"_ASZ",    "Access Size", "Resource Descriptor field"},
    {"_ATT",    "Type-Specific Attribute", "Resource Descriptor field"},
    {"_BAS",    "Base Address", "Range base address, Resource Descriptor field"},
    {"_BBN",    "Bios Bus Number", "Returns the PCI bus number returned by the BIOS"},
    {"_BCL",    "Brightness Control Levels", "Returns a list of supported brightness control levels"},
    {"_BCM",    "Brightness Control Method", "Sets the brightness level of the display device"},
    {"_BCT",    "Battery Charge Time", "Returns time remaining to complete charging battery"},
    {"_BDN",    "Bios Dock Name", "Returns the Dock ID returned by the BIOS"},
    {"_BFS",    "Back From Sleep", "Inform AML of a wake event"},
    {"_BIF",    "Battery Information", "Returns a Control Method Battery information block"},
    {"_BIX",    "Battery Information Extended", "Returns a Control Method Battery extended information block"},
    {"_BLT",    "Battery Level Threshold", "Set battery level threshold preferences"},
    {"_BM_",    "Bus Master", "Resource Descriptor field"},
    {"_BMA",    "Battery Measurement Averaging Interval", "Sets battery measurement averaging interval"},
    {"_BMC",    "Battery Maintenance Control", "Sets battery maintenance and control features"},
    {"_BMD",    "Battery Maintenance Data", "Returns battery maintenance, control, and state data"},
    {"_BMS",    "Battery Measurement Sampling Time", "Sets the battery measurement sampling time"},
    {"_BQC",    "Brightness Query Current", "Returns the current display brightness level"},
    {"_BST",    "Battery Status", "Returns a Control Method Battery status block"},
    {"_BTM",    "Battery Time", "Returns the battery runtime"},
    {"_BTP",    "Battery Trip Point", "Sets a Control Method Battery trip point"},
    {"_CBA",    "Configuration Base Address", "Sets the CBA for a PCI Express host bridge"},
    {"_CDM",    "Clock Domain", "Returns a logical processor's clock domain identifier"},
    {"_CID",    "Compatible ID", "Returns a device's Plug and Play Compatible ID list"},
    {"_CRS",    "Current Resource Settings", "Returns the current resource settings for a device"},
    {"_CRT",    "Critical Temperature", "Returns the shutdown critical temperature"},
    {"_CSD",    "C State Dependencies", "Returns a list of C-state dependencies"},
    {"_CST",    "C States", "Returns a list of supported C-states"},
    {"_DCK",    "Dock", "Sets docking isolation. Presence indicates device is a docking station"},
    {"_DCS",    "Display Current Status", "Returns status of the display output device"},
    {"_DDC",    "Display Data Current", "Returns the EDID for the display output device"},
    {"_DDN",    "Dos Device Name", "Returns a device logical name"},
    {"_DEC",    "Decode", "Device decoding type, Resource Descriptor field"},
    {"_DGS",    "Display Graphics State", "Return the current state of the output device"},
    {"_DIS",    "Disable", "Disables a device"},
    {"_DMA",    "Direct Memory Access", "Returns a device's current resources for DMA transactions"},
    {"_DOD",    "Display Output Devices", "Enumerate all devices attached to the display adapter"},
    {"_DOS",    "Disable Output Switching", "Sets the display output switching mode"},
    {"_DSM",    "Device Specific Method", "Executes device-specific functions"},
    {"_DSS",    "Device Set State", "Sets the display device state"},
    {"_DSW",    "Device Sleep Wake", "Sets the sleep and wake transition states for a device"},
    {"_DTI",    "Device Temperature Indication", "Conveys native device temperature to the platform"},
    {"_Exx",    "Edge GPE", "Method executed as a result of a general-purpose event"},
    {"_EC_",    "Embedded Controller", "returns EC offset and query information"},
    {"_EDL",    "Eject Device List", "Returns a list of devices that are dependent on a device (docking)"},
    {"_EJD",    "Ejection Dependent Device", "Returns the name of dependent (parent) device (docking)"},
    {"_EJx",    "Eject", "Begin or cancel a device ejection request (docking)"},
    {"_FDE",    "Floppy Disk Enumerate", "Returns floppy disk configuration information"},
    {"_FDI",    "Floppy Drive Information", "Returns a floppy drive information block"},
    {"_FDM",    "Floppy Drive Mode", "Sets a floppy drive speed"},
    {"_FIF",    "Fan Information", "Returns fan device information"},
    {"_FIX",    "Fixed Register Resource Provider", "Returns a list of devices that implement FADT register blocks"},
    {"_FPS",    "Fan Performance States", "Returns a list of supported fan performance states"},
    {"_FSL",    "Fan Set Level", "Control method that sets the fan device's speed level (performance state)"},
    {"_FST",    "Fan Status", "Returns current status information for a fan device"},
    {"_GAI",    "Get Averaging Interval", "Returns the power meter averaging interval"},
    {"_GHL",    "Get Hardware Limit", "Returns the hardware limit enforced by the power meter"},
    {"_GL_",    "Global Lock", "OS-defined Global Lock mutex object"},
    {"_GLK",    "Global Lock", "Returns a device's Global Lock requirement for device access"},
    {"_GPD",    "Get Post Data", "Returns the value of the VGA device that will be posted at boot"},
    {"_GPE",    "General Purpose Events", "(1) predefined Scope (\\_GPE.)"},
    {"_GRA",    "Granularity", "Address space granularity, Resource Descriptor field"},
    {"_GSB",    "Global System Interrupt Base", "Returns the GSB for a I/O APIC device"},
    {"_GTF",    "Get Task File", "Returns a list of ATA commands to restore a drive to default state"},
    {"_GTM",    "Get Timing Mode", "Returns a list of IDE controller timing information"},
    {"_GTS",    "Going To Sleep", "Inform AML of pending sleep"},
    {"_HE_",    "High-Edge", "Interrupt triggering, Resource Descriptor field"},
    {"_HID",    "Hardware ID", "Returns a device's Plug and Play Hardware ID"},
    {"_HOT",    "Hot Temperature", "Returns the critical temperature for sleep (entry to S4)"},
    {"_HPP",    "Hot Plug Parameters", "Returns a list of hot-plug information for a PCI device"},
    {"_HPX",    "Hot Plug Parameter Extensions", "Returns a list of hot-plug information for a PCI device. Supersedes _HPP"},
    {"_IFT",    "IPMI Interface Type", "See the Intelligent Platform Management Interface Specification"},
    {"_INI",    "Initialize", "Performs device specific initialization"},
    {"_INT",    "Interrupts", "Interrupt mask bits, Resource Descriptor field"},
    {"_IRC",    "Inrush Current", "Presence indicates that a device has a significant inrush current draw"},
    {"_Lxx",    "Level GPE", "Control method executed as a result of a general-purpose event"},
    {"_LCK",    "Lock", "Locks or unlocks a device (docking)"},
    {"_LEN",    "Length", "Range length, Resource Descriptor field"},
    {"_LID",    "Lid", "Returns the open/closed status of the lid on a mobile system"},
    {"_LL_",    "Low Level", "Interrupt polarity, Resource Descriptor field"},
    {"_MAF",    "Maximum Address Fixed", "Resource Descriptor field"},
    {"_MAT",    "Multiple Apic Table Entry", "Returns a list of MADT APIC structure entries"},
    {"_MAX",    "Maximum Base Address", "Resource Descriptor field"},
    {"_MBM",    "Memory Bandwidth Monitoring Data", "Returns bandwidth monitoring data for a memory device"},
    {"_MEM",    "Memory Attributes", "Resource Descriptor field"},
    {"_MIF",    "Minimum Address Fixed", "Resource Descriptor field"},
    {"_MIN",    "Minimum Base Address", "Resource Descriptor field"},
    {"_MLS",    "Multiple Language String", "Returns a device description in multiple languages"},
    {"_MSG",    "Message", "Sets the system message waiting status indicator"},
    {"_MSM",    "Memory Set Monitoring", "Sets bandwidth monitoring parameters for a memory device"},
    {"_MTP",    "Memory Type", "Resource Descriptor field"},
    {"_NTT",    "Notification Temperature Threshold", "Returns a threshold for device temperature change that requires platform notification"},
    {"_OFF",    "Off", "Sets a power resource to the off state"},
    {"_ON_",    "On", "Sets a power resource to the on state"},
    {"_OS_",    "Operating System", "Returns a string that identifies the operating system"},
    {"_OSC",    "Operating System Capabilities", "Inform AML of host features and capabilities"},
    {"_OSI",    "Operating System Interfaces", "Returns supported interfaces, behaviors, and features"},
    {"_OST",    "Ospm Status Indication", "Inform AML of event processing status"},
    {"_PAI",    "Power Averaging Interval", "Sets the averaging interval for a power meter"},
    {"_PCL",    "Power Consumer List", "Returns a list of devices powered by a power source"},
    {"_PCT",    "Performance Control", "Returns processor performance control and status registers"},
    {"_PDC",    "Processor Driver Capabilities", "Inform AML of processor driver capabilities"},
    {"_PDL",    "P-state Depth Limit", "Returns the lowest available performance P-state"},
    {"_PIC",    "PIC", "Inform AML of the interrupt model in use"},
    {"_PIF",    "Power Source Information", "Returns a Power Source information block"},
    {"_PLD",    "Physical Device Location", "Returns a device's physical location information"},
    {"_PMC",    "Power Meter Capabilities", "Returns a list of Power Meter capabilities info"},
    {"_PMD",    "Power Metered Devices", "Returns a list of devices that are measured by the power meter device"},
    {"_PMM",    "Power Meter Measurement", "Returns the current value of the Power Meter"},
    {"_PPC",    "Performance Present Capabilites", "Returns a list of the performance states currently supported by the platform"},
    {"_PPE",    "Polling for Platform Error", "Returns the polling interval to retrieve Corrected Platform Error information"},
    {"_PR",     "Processor", "Predefined scope for processor objects"},
    {"_PR0",    "Power Resources for D0", "Returns a list of dependent power resources to enter state D0 (fully on)"},
    {"_PR1",    "Power Resources for D1", "Returns a list of dependent power resources to enter state D1"},
    {"_PR2",    "Power Resources for D2", "Returns a list of dependent power resources to enter state D2"},
    {"_PR3",    "Power Resources for D3hot", "Returns a list of dependent power resources to enter state D3hot"},
    {"_PRL",    "Power Source Redundancy List", "Returns a list of power source devices in the same redundancy grouping"},
    {"_PRS",    "Possible Resource Settings", "Returns a list of a device's possible resource settings"},
    {"_PRT",    "Pci Routing Table", "Returns a list of PCI interrupt mappings"},
    {"_PRW",    "Power Resources for Wake", "Returns a list of dependent power resources for waking"},
    {"_PS0",    "Power State 0", "Sets a device's power state to D0 (device fully on)"},
    {"_PS1",    "Power State 1", "Sets a device's power state to D1"},
    {"_PS2",    "Power State 2", "Sets a device's power state to D2"},
    {"_PS3",    "Power State 3", "Sets a device's power state to D3 (device off)"},
    {"_PSC",    "Power State Current", "Returns a device's current power state"},
    {"_PSD",    "Processor State Dependencies", "Returns processor P-State dependencies"},
    {"_PSL",    "Passive List", "Returns a list of passive cooling device objects"},
    {"_PSR",    "Power Source", "Returns the power source device currently in use"},
    {"_PSS",    "Performance Supported States", "Returns a list of supported processor performance states"},
    {"_PSV",    "Passive", "Returns the passive trip point temperature"},
    {"_PSW",    "Power State Wake", "Sets a device's wake function"},
    {"_PTC",    "Processor Throttling Control", "Returns throttling control and status registers"},
    {"_PTP",    "Power Trip Points", "Sets trip points for the Power Meter device"},
    {"_PTS",    "Prepare To Sleep", "Inform the platform of an impending sleep transition"},
    {"_PUR",    "Processor Utilization Request", "Returns the number of processors that the platform would like to idle"},
    {"_PXM",    "Proximity", "Returns a device's proximity domain identifier"},
    {"_Qxx",    "Query", "Embedded Controller query and SMBus Alarm control method"},
    {"_RBO",    "Register Bit Offset", "Resource Descriptor field"},
    {"_RBW",    "Register Bit Width", "Resource Descriptor field"},
    {"_REG",    "Region", "Inform AML code of an operation region availability change"},
    {"_REV",    "Revision", "Returns the revision of the ACPI specification that is implemented"},
    {"_RMV",    "Remove", "Returns a device's removal ability status (docking)"},
    {"_RNG",    "Range", "Memory range type, Resource Descriptor field"},
    {"_ROM",    "Read-Only Memory", "Returns a copy of the ROM data for a display device"},
    {"_RT_",    "Resource Type", "Resource Descriptor field"},
    {"_RTV",    "Relative Temperature Values", "Returns temperature value information"},
    {"_RW_",    "Read-Write Status", "Resource Descriptor field"},
    {"_S0_",    "S0 System State", "Returns values to enter the system into the S0 state"},
    {"_S1_",    "S1 System State", "Returns values to enter the system into the S1 state"},
    {"_S2_",    "S2 System State", "Returns values to enter the system into the S2 state"},
    {"_S3_",    "S3 System State", "Returns values to enter the system into the S3 state"},
    {"_S4_",    "S4 System State", "Returns values to enter the system into the S4 state"},
    {"_S5_",    "S5 System State", "Returns values to enter the system into the S5 state"},
    {"_S1D",    "S1 Device State", "Returns the highest D-state supported by a device when in the S1 state"},
    {"_S2D",    "S2 Device State", "Returns the highest D-state supported by a device when in the S2 state"},
    {"_S3D",    "S3 Device State", "Returns the highest D-state supported by a device when in the S3 state"},
    {"_S4D",    "S4 Device State", "Returns the highest D-state supported by a device when in the S4 state"},
    {"_S0W",    "S0 Device Wake State", "Returns the lowest D-state that the device can wake itself from S0"},
    {"_S1W",    "S1 Device Wake State", "Returns the lowest D-state for this device that can wake the system from S1"},
    {"_S2W",    "S2 Device Wake State", "Returns the lowest D-state for this device that can wake the system from S2"},
    {"_S3W",    "S3 Device Wake State", "Returns the lowest D-state for this device that can wake the system from S3"},
    {"_S4W",    "S4 Device Wake State", "Returns the lowest D-state for this device that can wake the system from S4"},
    {"_SB_",    "System Bus", "Scope for device and bus objects"},
    {"_SBS",    "Smart Battery Subsystem", "Returns the subsystem configuration"},
    {"_SCP",    "Set Cooling Policy", "Sets the cooling policy (active or passive)"},
    {"_SDD",    "Set Device Data", "Sets data for a SATA device"},
    {"_SEG",    "Segment", "Returns a device's PCI Segment Group number"},
    {"_SHL",    "Set Hardware Limit", "Sets the hardware limit enforced by the Power Meter"},
    {"_SHR",    "Sharable", "Interrupt share status, Resource Descriptor field"},
    {"_SI_",    "System Indicators", "Predefined scope"},
    {"_SIZ",    "Size", "DMA transfer size, Resource Descriptor field"},
    {"_SLI",    "System Locality Information", "Returns a list of NUMA system localities"},
    {"_SPD",    "Set Post Device", "Sets which video device will be posted at boot"},
    {"_SRS",    "Set Resource Settings", "Sets a device's resource allocation"},
    {"_SRV",    "IPMI Spec Revision", "See the Intelligent Platform Management Interface Specification"},
    {"_SST",    "System Status", "Sets the system status indicator"},
    {"_STA",    "Status", " (1) returns the current status of a device"},
    {"_STM",    "Set Timing Mode", "Sets an IDE controller transfer timings"},
    {"_STP",    "Set Expired Timer Wake Policy", "Sets expired timer policies of the wake alarm device"},
    {"_STR",    "String", "Returns a device's description string"},
    {"_STV",    "Set Timer Value", "Set timer values of the wake alarm device"},
    {"_SUN",    "Slot User Number", "Returns the slot unique ID number"},
    {"_SWS",    "System Wake Source", "Returns the source event that caused the system to wake"},
    {"_T_x",    "Temporary", "Reserved for use by ASL compilers"},
    {"_TC1",    "Thermal Constant 1", "Returns TC1 for the passive cooling formula"},
    {"_TC2",    "Thermal Constant 2", "Returns TC2 for the passive cooling formula"},
    {"_TDL",    "T-State Depth Limit", "Returns the _TSS entry number of the lowest power throttling state"},
    {"_TIP",    "Expired Timer Wake Policy", "Returns timer policies of the wake alarm device"},
    {"_TIV",    "Timer Values", "Returns remaining time of the wake alarm device"},
    {"_TMP",    "Temperature", "Returns a thermal zone's current temperature"},
    {"_TPC",    "Throttling Present Capabilities", "Returns the current number of supported throttling states"},
    {"_TPT",    "Trip Point Temperature", "Inform AML that a device's embedded temperature sensor has crossed a temperature trip point"},
    {"_TRA",    "Translation", "Address translation offset, Resource Descriptor field"},
    {"_TRS",    "Translation Sparse", "Sparse/dense flag, Resource Descriptor field"},
    {"_TRT",    "Thermal Relationship Table", "Returns thermal relationships between platform devices"},
    {"_TSD",    "Throttling State Dependencies", "Returns a list of T-state dependencies"},
    {"_TSF",    "Type-Specific Flags", "Resource Descriptor field"},
    {"_TSP",    "Thermal Sampling Period", "Returns the thermal sampling period for passive cooling"},
    {"_TSS",    "Throttling Supported States", "Returns supported throttling state information"},
    {"_TST",    "Temperature Sensor Threshold", "Returns the minimum separation for a device's temperature trip points"},
    {"_TTP",    "Translation Type", "Translation/static flag, Resource Descriptor field"},
    {"_TTS",    "Transition To State", "Inform AML of an S-state transition"},
    {"_TYP",    "Type", "DMA channel type (speed), Resource Descriptor field"},
    {"_TZ_",    "Thermal Zone", "Predefined scope: ACPI 1.0"},
    {"_TZD",    "Thermal Zone Devices", "Returns a list of device names associated with a Thermal Zone"},
    {"_TZM",    "Thermal Zone Member", "Returns a reference to the thermal zone of which a device is a member"},
    {"_TZP",    "Thermal Zone Polling", "Returns a Thermal zone's polling frequency"},
    {"_UID",    "Unique ID", "Return a device's unique persistent ID"},
    {"_UPC",    "USB Port Capabilities", "Returns a list of USB port capabilities"},
    {"_UPD",    "User Presence Detect", "Returns user detection information"},
    {"_UPP",    "User Presence Polling", "Returns the recommended user presence polling interval"},
    {"_VPO",    "Video Post Options", "Returns the implemented video post options"},
    {"_WAK",    "Wake", "Inform AML that the system has just awakened"},
    {"_Wxx",    "Wake Event", "Method executed as a result of a wake event"}
};
