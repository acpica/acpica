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
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Subsystem - Win32 Release"
# Name "Subsystem - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\NameSpace\acpiinit.c
# End Source File
# Begin Source File

SOURCE=.\Device\dvlegacy.c
# End Source File
# Begin Source File

SOURCE=.\Device\dvregs.c
# End Source File
# Begin Source File

SOURCE=.\Device\dvsleep.c
# End Source File
# Begin Source File

SOURCE=.\Device\dvtimer.c
# End Source File
# Begin Source File

SOURCE=.\Event\evregs.c
# End Source File
# Begin Source File

SOURCE=.\Event\evsci.c
# End Source File
# Begin Source File

SOURCE=.\Execute\excommon.c
# End Source File
# Begin Source File

SOURCE=.\Execute\exmexist.c
# End Source File
# Begin Source File

SOURCE=.\Execute\exmpts.c
# End Source File
# Begin Source File

SOURCE=.\Execute\exmwak.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\iefield.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\ieopexec.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\ieprep.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\iesystem.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\iexecute.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\isatoms.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\iscode.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\isdebug.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\isdump.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\isexprs.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\isidata.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\isnames.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\isopcode.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\isrdata.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\isstack.c
# End Source File
# Begin Source File

SOURCE=.\Interpreter\isutils.c
# End Source File
# Begin Source File

SOURCE=.\NameSpace\nsaccess.c
# End Source File
# Begin Source File

SOURCE=.\NameSpace\nsapi.c
# End Source File
# Begin Source File

SOURCE=.\NameSpace\nsdump.c
# End Source File
# Begin Source File

SOURCE=.\NameSpace\nsfamily.c
# End Source File
# Begin Source File

SOURCE=.\NameSpace\nspriv.c
# End Source File
# Begin Source File

SOURCE=.\NameSpace\nsscope.c
# End Source File
# Begin Source File

SOURCE=.\NameSpace\nsstack.c
# End Source File
# Begin Source File

SOURCE=.\NameSpace\nstables.c
# End Source File
# Begin Source File

SOURCE=.\NameSpace\nsutils.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Include\acpi.h
# End Source File
# Begin Source File

SOURCE=.\Include\acpiasm.h
# End Source File
# Begin Source File

SOURCE=.\Include\acpiobj.h
# End Source File
# Begin Source File

SOURCE=.\Include\acpiosd.h
# End Source File
# Begin Source File

SOURCE=.\Include\acpisubsys.h
# End Source File
# Begin Source File

SOURCE=.\Include\acpitables.h
# End Source File
# Begin Source File

SOURCE=.\Include\amlcode.h
# End Source File
# Begin Source File

SOURCE=.\Include\config.h
# End Source File
# Begin Source File

SOURCE=.\Include\datatypes.h
# End Source File
# Begin Source File

SOURCE=.\Include\devices.h
# End Source File
# Begin Source File

SOURCE=.\Include\display.h
# End Source File
# Begin Source File

SOURCE=.\Include\enumerate.h
# End Source File
# Begin Source File

SOURCE=.\Include\events.h
# End Source File
# Begin Source File

SOURCE=.\Include\excep.h
# End Source File
# Begin Source File

SOURCE=.\Include\exmethod.h
# End Source File
# Begin Source File

SOURCE=.\Include\interpreter.h
# End Source File
# Begin Source File

SOURCE=.\Include\namespace.h
# End Source File
# Begin Source File

SOURCE=.\Include\output.h
# End Source File
# Begin Source File

SOURCE=.\Include\pnp.h
# End Source File
# End Group
# End Target
# End Project
