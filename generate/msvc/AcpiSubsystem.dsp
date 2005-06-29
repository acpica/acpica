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
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AcpiSubsystem - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "AcpiSubsystem"
# PROP Intermediate_Dir "AcpiSubsystem"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Gz /MT /W4 /GX /O2 /I "..\..\Subsystem\Include" /I "\98ddk\inc\win98" /D "NDEBUG" /D "ACPILIB_GEN" /D "DRIVER" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN32" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
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
# PROP Output_Dir "AcpiSubsystem"
# PROP Intermediate_Dir "AcpiSubsystem"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /MT /W4 /GX /Z7 /Od /I "..\..\Subsystem\Include" /I "\98ddk\inc\win98" /D "ACPI_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN32" /FR /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
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

SOURCE=..\..\Subsystem\Common\cmapi.c
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

SOURCE=..\..\Subsystem\Common\cmerror.c
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

SOURCE=..\..\Subsystem\Common\cmmutex.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmobject.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmrefcnt.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmsize.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmstate.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmutils.c
# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\Subsystem\Events\evapi.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Events\evapievt.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Events\evapirgn.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Events\evfixed.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Events\evglock.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Events\evgpe.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Events\evnotify.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Events\evregion.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Events\evrgnini.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Events\evsci.c
# End Source File
# End Group
# Begin Group "Hardware"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\Subsystem\Hardware\hw32Cx.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Hardware\hw32thrt.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Hardware\hwapi.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Hardware\hwgpe.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Hardware\hwmode.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Hardware\hwregs.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Hardware\hwtimer.c
# End Source File
# End Group
# Begin Group "Interpreter"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iapi.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\icopy.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\ieconfig.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iecreate.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iedyad.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iefield.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iefread.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iefwrite.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iemonad.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\ieopexec.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\ieprep.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\ieregion.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iesystem.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iresnte.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iresobj.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iresolve.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iresop.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isdump.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isnames.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\istore.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\istorent.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\istoreob.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isutils.c
# End Source File
# End Group
# Begin Group "Namespace"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nsaccess.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nsalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nsapinam.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nsapiobj.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nsdump.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nseval.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nsfamily.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nsload.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nsmodify.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nsnames.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nsobject.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nsscope.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nssearch.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nswalk.c
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsaddr16.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsaddr32.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsapi.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsby2lst.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rscalcb.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rscalcl.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rscrbyst.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rscrprt.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rscrresl.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsdepend.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsdma.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsdump.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rseirq.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsgetbss.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsio.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsirq.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rslst2by.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsmem24.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsmem32.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rstag.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Resources\rsvendor.c
# End Source File
# End Group
# Begin Group "Tables"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Subsystem\Tables\tbapi.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Tables\tbfac.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Tables\tbget.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Tables\tbgetall.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Tables\tbinstal.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Tables\tbremove.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Tables\tbrsd.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Tables\tbutils.c
# End Source File
# End Group
# Begin Group "Parser"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psapi.c
# End Source File
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
# End Group
# Begin Group "Debugger"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Subsystem\Debugger\dbapi.c
# End Source File
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
# End Group
# Begin Group "Dispatcher"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Subsystem\Dispatcher\dscontrl.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Dispatcher\dsfield.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Dispatcher\dsmethod.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Dispatcher\dsmthdat.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Dispatcher\dsobject.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Dispatcher\dsregion.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Dispatcher\dsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Dispatcher\dswexec.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Dispatcher\dswload1.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Dispatcher\dswload2.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Dispatcher\dswscope.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Dispatcher\dswstate.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\Subsystem\Include\acapi.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acenv.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acexcep.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acobject.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpi.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpiosd.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\actables.h
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
# Begin Source File

SOURCE=..\..\Subsystem\Include\common.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\config.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\debugger.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\dispatch.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\events.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\globals.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\hardware.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\internal.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\interp.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\macros.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\namesp.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\output.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\parser.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\pnp.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\resource.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\tables.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AcpiSubsystem.plg
# End Source File
# End Target
# End Project
