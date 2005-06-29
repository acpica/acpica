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
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "ACPILIB_GEN" /D "DRIVER" /D PROCESSOR_ARCHITECTURE=x86 /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Release\acpilib.lib"

!ELSEIF  "$(CFG)" == "Subsystem - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_TRACE" /D "WIN32" /D "_WINDOWS" /D "ACPILIB_GEN" /D "DRIVER" /D PROCESSOR_ARCHITECTURE=x86 /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\acpilib.lib"

!ENDIF 

# Begin Target

# Name "Subsystem - Win32 Release"
# Name "Subsystem - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\acpiinit.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Device\dvlegacy.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Device\dvregs.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Device\dvsleep.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Device\dvtimer.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Event\evregs.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Event\evsci.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Execute\excommon.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Execute\exmexist.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Execute\exmpts.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Execute\exmwak.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iefield.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\ieopexec.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\ieprep.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iesystem.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iexecute.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isatoms.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iscode.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isdebug.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isdump.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isexprs.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isidata.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isnames.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isrdata.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isstack.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isutils.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nsaccess.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nsapi.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nsdump.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nsfamily.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nspriv.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nsscope.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nsstack.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nstables.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\NameSpace\nsutils.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpi.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\acpiasm.h
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

SOURCE=..\..\Subsystem\Include\amlcode.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\config.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\datatypes.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\devices.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\display.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\enumerate.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\events.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\excep.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\exmethod.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\interpreter.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\namespace.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\output.h
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Include\pnp.h
# End Source File
# End Group
# End Target
# End Project
