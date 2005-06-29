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
# PROP Output_Dir "\Acpi\Components\Generate\VC\AcpiSubsystem"
# PROP Intermediate_Dir "\Acpi\Components\Generate\VC\AcpiSubsystem"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Gz /MT /Za /W4 /GX /O2 /I "..\..\Subsystem\Include" /I "\98ddk\inc\win98" /D "NDEBUG" /D "ACPILIB_GEN" /D "DRIVER" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN32" /YX /FD /c
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
PostBuild_Desc=Copy library to acpi/components/libraries
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
# PROP Output_Dir "\Acpi\Components\Generate\VC\AcpiSubsystem"
# PROP Intermediate_Dir "\Acpi\Components\Generate\VC\AcpiSubsystem"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /MT /Za /W4 /GX /Z7 /Od /I "..\..\Subsystem\Include" /I "\98ddk\inc\win98" /D "ACPI_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN32" /FR /FD /c
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
PreLink_Desc=Checking existence of acpi/components/libraries directory
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
# Begin Group "Common"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmclib.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmcopy.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmdebug.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmdelete.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmeval.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmglobal.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cminit.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmobject.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmutils.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Common\cmxface.c
# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\subsystem\Events\evevent.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Events\evmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Events\evregion.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Events\evrgnini.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Events\evsci.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Events\evxface.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Events\evxfevnt.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Events\evxfregn.c
# End Source File
# End Group
# Begin Group "Hardware"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\subsystem\Hardware\hwacpi.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Hardware\hwcpu32.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Hardware\hwgpe.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Hardware\hwregs.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Hardware\hwxface.c
# End Source File
# End Group
# Begin Group "Interpreter"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amconfig.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amcreate.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amdump.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amdyadic.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amfield.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amfldio.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\ammisc.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\ammonad.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amnames.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amprep.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amregion.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amresnte.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amresolv.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amresop.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amstore.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amstoren.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amstorob.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amsystem.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amutils.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Interpreter\amxface.c
# End Source File
# End Group
# Begin Group "Namespace"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nsaccess.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nsalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nsdump.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nseval.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nsinit.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nsload.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nsnames.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nsobject.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nssearch.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nswalk.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nsxfname.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Namespace\nsxfobj.c
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\subsystem\Resources\rsaddr.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Resources\rscalc.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Resources\rscreate.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Resources\rsdump.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Resources\rsio.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Resources\rsirq.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Resources\rslist.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Resources\rsmemory.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Resources\rsmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Resources\rsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Resources\rsxface.c
# End Source File
# End Group
# Begin Group "Tables"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Subsystem\Tables\tbget.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Tables\tbinstal.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Tables\tbtable.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Tables\tbutils.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Tables\tbxface.c
# End Source File
# End Group
# Begin Group "Parser"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psargs.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psparse.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psscope.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\pstree.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psutils.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\pswalk.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Parser\psxface.c
# End Source File
# End Group
# Begin Group "Debugger"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Subsystem\Debugger\dbcmds.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Debugger\dbdisasm.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Debugger\dbdisply.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Debugger\dbexec.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Debugger\dbfileio.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Debugger\dbhistry.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Debugger\dbinput.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Debugger\dbstats.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Debugger\dbutils.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Debugger\dbxface.c
# End Source File
# End Group
# Begin Group "Dispatcher"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\subsystem\Dispatcher\dsfield.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Dispatcher\dsmethod.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Dispatcher\dsmthdat.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Dispatcher\dsobject.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Dispatcher\dsopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Dispatcher\dsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Dispatcher\dswexec.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Dispatcher\dswload.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Dispatcher\dswscope.c
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Dispatcher\dswstate.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\subsystem\Include\accommon.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acdebug.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acdispat.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acenv.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acevents.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acexcep.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acglobal.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\achware.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acinterp.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\aclocal.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acmacros.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acnamesp.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acobject.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acoutput.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acparser.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpi.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acpiosxf.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acpixf.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\acresrc.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\actables.h
# End Source File
# Begin Source File

SOURCE=..\..\subsystem\Include\actbl.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\actbl32.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\actbl64.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\actypes.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\amlcode.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AcpiSubsystem.plg
# End Source File
# End Target
# End Project
