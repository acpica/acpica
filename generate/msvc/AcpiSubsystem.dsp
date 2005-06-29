# Microsoft Developer Studio Project File - Name="Subsystem" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Subsystem - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Subsystem.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Subsystem.mak" CFG="Subsystem - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Subsystem - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Subsystem - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Acpi Components/Subsystem", CQBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Subsystem - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "bin"
# PROP Intermediate_Dir "bin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Gz /MT /W3 /GX /O2 /I "..\..\Subsystem\Include" /I "\98ddk\inc\win98" /D "NDEBUG" /D "ACPILIB_GEN" /D "DRIVER" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN32" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\acpilib.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copying built library [Release Version]
PostBuild_Cmds=copy release\acpilib.lib ..\..\libraries\acpilib.lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "bin"
# PROP Intermediate_Dir "bin"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /MT /W3 /GX /Z7 /Od /I "..\..\Subsystem\Include" /I "\98ddk\inc\win98" /D "ACPI_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN32" /FR /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"bin\acpilib.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=deleting old library
PreLink_Cmds=del ..\..\libraries\acpilib.lib
PostBuild_Desc=Copying built library [Debug Version]
PostBuild_Cmds=copy bin\acpilib.lib ..\..\libraries\acpilib.lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Subsystem - Win32 Release"
# Name "Subsystem - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Common"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmalloc.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmapi.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmclib.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmcreate.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmdebug.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmdelete.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmerror.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmglobal.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

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

SOURCE=..\..\Subsystem\Common\cmsize.c
# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\Subsystem\Events\evapi.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Events\evfixed.c
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

SOURCE=..\..\Subsystem\Events\evsci.c
# End Source File
# End Group
# Begin Group "Hardware"

# PROP Default_Filter ".c"
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

SOURCE=..\..\Subsystem\Interpreter\iedyad.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iefield.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

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

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\ieprep.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\ieregion.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iesystem.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\ievalue.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iexecute.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isdebug.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isdump.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isnames.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isutils.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# End Group
# Begin Group "Methods"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\Subsystem\Methods\mtadr.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Methods\mtexist.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Methods\mthid.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Methods\mtpts.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Methods\mtsta.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Methods\mtuid.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Methods\mtwak.c
# End Source File
# End Group
# Begin Group "Namespace"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nsaccess.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

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

SOURCE=..\..\Subsystem\NameSpace\nsdump.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nseval.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nsfamily.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

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

SOURCE=..\..\Subsystem\NameSpace\nsscope.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Namespace\nssearch.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nsstack.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nsutils.c

!IF  "$(CFG)" == "Subsystem - Win32 Release"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# ADD CPP /W3 /Z7

!ENDIF 

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
# Begin Source File

SOURCE=..\..\Subsystem\Parser\pswstate.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psxctrl.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psxexec.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psxfield.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psxload.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psxmargs.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psxmethd.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psxobj.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psxregn.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Parser\psxutils.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpi.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpiexcep.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpiobj.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpiosd.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpisubsys.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpitables.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpitbl32.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpitbl64.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpitypes.h
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

SOURCE=..\..\Subsystem\Include\enumerate.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\environment.h
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

SOURCE=..\..\Subsystem\Include\interpreter.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\macros.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\methods.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\namespace.h
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

SOURCE=.\Subsystem.plg
# End Source File
# End Target
# End Project
