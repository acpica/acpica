# Microsoft Developer Studio Project File - Name="AcpiSubsystem" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=AcpiSubsystem - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AcpiSubsystem.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AcpiSubsystem.mak" CFG="AcpiSubsystem - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AcpiSubsystem - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AcpiSubsystem - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Acpi Components/Subsystem", CQBAAAAA"
# PROP Scc_LocalPath "..\.."
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "AcpiSubsystem - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\Acpi\Generate\msvc\AcpiSubsystem"
# PROP Intermediate_Dir "\Acpi\Generate\msvc\AcpiSubsystem"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Gz /MT /Za /W4 /GX /O1 /I "..\..\components\Include" /D "NDEBUG" /D "ACPILIB_GEN" /D "DRIVER" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN32" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"bin\acpica.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Checking existence of acpi/components/libraries directory
PreLink_Cmds=if NOT EXIST ..\..\libraries mkdir ..\..\libraries
PostBuild_Desc=Copy library to acpi/libraries
PostBuild_Cmds=copy bin\acpica.lib ..\..\libraries\acpica.lib	dir ..\..\libraries\acpica.lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AcpiSubsystem - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\Acpi\Generate\msvc\AcpiSubsystem"
# PROP Intermediate_Dir "\Acpi\Generate\msvc\AcpiSubsystem"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /MT /Za /W4 /GX /Z7 /Od /I "..\..\components\Include" /D "ACPI_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN32" /D "ENABLE_DEBUGGER" /FR /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"bin\acpica.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Checking existence of acpi/libraries directory
PreLink_Cmds=if NOT EXIST ..\..\libraries mkdir ..\..\libraries
PostBuild_Desc=Copy library to acpi/components/libraries
PostBuild_Cmds=copy bin\acpica.lib ..\..\libraries\acpica.lib	dir ..\..\libraries\acpica.lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "AcpiSubsystem - Win32 Release"
# Name "AcpiSubsystem - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Utilities"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\components\core\utils\cmalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\utils\cmclib.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\utils\cmcopy.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\utils\cmdebug.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\utils\cmdelete.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\utils\cmeval.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\utils\cmglobal.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\utils\cminit.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\utils\cmobject.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\utils\cmutils.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\utils\cmxface.c
# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\components\core\events\evevent.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\events\evmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\events\evregion.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\events\evrgnini.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\events\evsci.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\events\evxface.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\events\evxfevnt.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\events\evxfregn.c
# End Source File
# End Group
# Begin Group "Hardware"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\components\core\hardware\hwacpi.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\hardware\hwgpe.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\hardware\hwregs.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\hardware\hwsleep.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\hardware\hwtimer.c
# End Source File
# End Group
# Begin Group "Interpreter"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amconfig.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amconvrt.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amcreate.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amdump.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amdyadic.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amfield.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amfldio.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\ammisc.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\ammonad.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\ammutex.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amnames.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amprep.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amregion.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amresnte.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amresolv.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amresop.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amstore.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amstoren.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amstorob.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amsystem.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amutils.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\executer\amxface.c
# End Source File
# End Group
# Begin Group "Namespace"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\components\core\namespace\nsaccess.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\namespace\nsalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\namespace\nsdump.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\namespace\nseval.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\namespace\nsinit.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\namespace\nsload.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\namespace\nsnames.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\namespace\nsobject.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\namespace\nssearch.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\namespace\nsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\namespace\nswalk.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\namespace\nsxfname.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\namespace\nsxfobj.c
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\components\services\resource\rsaddr.c
# End Source File
# Begin Source File

SOURCE=..\..\components\services\resource\rscalc.c
# End Source File
# Begin Source File

SOURCE=..\..\components\services\resource\rscreate.c
# End Source File
# Begin Source File

SOURCE=..\..\components\services\resource\rsdump.c
# End Source File
# Begin Source File

SOURCE=..\..\components\services\resource\rsio.c
# End Source File
# Begin Source File

SOURCE=..\..\components\services\resource\rsirq.c
# End Source File
# Begin Source File

SOURCE=..\..\components\services\resource\rslist.c
# End Source File
# Begin Source File

SOURCE=..\..\components\services\resource\rsmemory.c
# End Source File
# Begin Source File

SOURCE=..\..\components\services\resource\rsmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\components\services\resource\rsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\components\services\resource\rsxface.c
# End Source File
# End Group
# Begin Group "Tables"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\components\core\tables\tbconvrt.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\tables\tbget.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\tables\tbinstal.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\tables\tbutils.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\tables\tbxface.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\tables\tbxfroot.c
# End Source File
# End Group
# Begin Group "Parser"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\components\interpreter\parser\psargs.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\parser\psopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\parser\psparse.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\parser\psscope.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\parser\pstree.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\parser\psutils.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\parser\pswalk.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\parser\psxface.c
# End Source File
# End Group
# Begin Group "Debugger"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\components\interpreter\debugger\dbcmds.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\debugger\dbdisasm.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\debugger\dbdisply.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\debugger\dbexec.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\debugger\dbfileio.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\debugger\dbhistry.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\debugger\dbinput.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\debugger\dbstats.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\debugger\dbutils.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\debugger\dbxface.c
# End Source File
# End Group
# Begin Group "Dispatcher"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\components\interpreter\dispatcher\dsfield.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\dispatcher\dsmethod.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\dispatcher\dsmthdat.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\dispatcher\dsobject.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\dispatcher\dsopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\dispatcher\dsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\dispatcher\dswexec.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\dispatcher\dswload.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\dispatcher\dswscope.c
# End Source File
# Begin Source File

SOURCE=..\..\components\interpreter\dispatcher\dswstate.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\components\Include\accommon.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acdebug.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acdispat.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\platform\acefi.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\platform\acenv.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acevents.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acexcep.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\platform\acfreebsd.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\platform\acgcc.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acglobal.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\achware.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acinterp.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\platform\aclinux.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\aclocal.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acmacros.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\platform\acmsvc.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acnamesp.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acobject.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acoutput.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acparser.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acpi.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acpiosxf.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acpixf.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\acresrc.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\actables.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\actbl.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\actbl1.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\actbl2.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\actbl71.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\actypes.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\platform\acwin.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Include\amlcode.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AcpiSubsystem.plg
# End Source File
# End Target
# End Project
