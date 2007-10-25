# Microsoft Developer Studio Project File - Name="AcpiSubsystem64" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=AcpiSubsystem64 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AcpiSubsystem64.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AcpiSubsystem64.mak" CFG="AcpiSubsystem64 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AcpiSubsystem64 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AcpiSubsystem64 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Acpi Components/Subsystem", CQBAAAAA"
# PROP Scc_LocalPath "..\.."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug"
# PROP Intermediate_Dir "\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /MT /Za /W4 /Gm /GX /Zi /O1 /I "..\..\source\Include" /D "NDEBUG" /D "DRIVER" /D "_USE_INTEL_COMPILER" /D "ACPI_LIBRARY" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN64" /FR /FD /c
# SUBTRACT CPP /nologo /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /out:"bin\acpica64.lib" /machine:IA64
# SUBTRACT LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Checking existence of acpi/libraries directory
PreLink_Cmds=if NOT EXIST ..\..\libraries mkdir ..\..\libraries
PostBuild_Desc=Copy library to acpi/libraries
PostBuild_Cmds=copy bin\acpica64.lib ..\..\libraries\acpica64.lib	dir ..\..\libraries\acpica64.lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\Acpi\Generate\msvc\AcpiSubsystem64\Debug"
# PROP Intermediate_Dir "\Acpi\Generate\msvc\AcpiSubsystem64\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /MTd /Za /W4 /Gm /GX /Zi /Oa /Og /Os /Oy /I "..\..\source\Include" /D "ACPI_FULL_DEBUG" /D "_USE_INTEL_COMPILER" /D "ACPI_LIBRARY" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN64" /FR /FD /c
# SUBTRACT CPP /nologo
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /out:"bin\acpica_dbg64.lib" /machine:IA64
# SUBTRACT LIB32 /nologo
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Checking existence of acpi/libraries directory
PreLink_Cmds=if NOT EXIST ..\..\libraries mkdir ..\..\libraries
PostBuild_Desc=Copy library to acpi/libraries
PostBuild_Cmds=copy bin\acpica_dbg64.lib ..\..\libraries\acpica_dbg64.lib	dir ..\..\libraries\acpica_dbg64.lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "AcpiSubsystem64 - Win32 Release"
# Name "AcpiSubsystem64 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Utilities"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\source\components\utilities\utalloc.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utalloc.c
InputName=utalloc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utalloc.c
InputName=utalloc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utcache.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utcache.c
InputName=utcache

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utcache.c
InputName=utcache

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utclib.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utclib.c
InputName=utclib

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utclib.c
InputName=utclib

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utcopy.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utcopy.c
InputName=utcopy

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utcopy.c
InputName=utcopy

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utdebug.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utdebug.c
InputName=utdebug

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utdebug.c
InputName=utdebug

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utdelete.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utdelete.c
InputName=utdelete

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utdelete.c
InputName=utdelete

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\uteval.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\uteval.c
InputName=uteval

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\uteval.c
InputName=uteval

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utglobal.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utglobal.c
InputName=utglobal

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utglobal.c
InputName=utglobal

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utinit.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utinit.c
InputName=utinit

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utinit.c
InputName=utinit

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utmath.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utmath.c
InputName=utmath

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utmath.c
InputName=utmath

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utmisc.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utmisc.c
InputName=utmisc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utmisc.c
InputName=utmisc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utmutex.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utmutex.c
InputName=utmutex

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utmutex.c
InputName=utmutex

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utobject.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utobject.c
InputName=utobject

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utobject.c
InputName=utobject

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utresrc.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utresrc.c
InputName=utresrc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utresrc.c
InputName=utresrc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utstate.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utstate.c
InputName=utstate

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utstate.c
InputName=utstate

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utxface.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\utilities\utxface.c
InputName=utxface

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\utilities\utxface.c
InputName=utxface

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\source\components\events\evevent.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\events\evevent.c
InputName=evevent

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\events\evevent.c
InputName=evevent

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\EVENTS\evgpe.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\EVENTS\evgpe.c
InputName=evgpe

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\EVENTS\evgpe.c
InputName=evgpe

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\SOURCE\COMPONENTS\EVENTS\evgpeblk.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\SOURCE\COMPONENTS\EVENTS\evgpeblk.c
InputName=evgpeblk

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\SOURCE\COMPONENTS\EVENTS\evgpeblk.c
InputName=evgpeblk

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\events\evmisc.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\events\evmisc.c
InputName=evmisc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\events\evmisc.c
InputName=evmisc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\events\evregion.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\events\evregion.c
InputName=evregion

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\events\evregion.c
InputName=evregion

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\events\evrgnini.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\events\evrgnini.c
InputName=evrgnini

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\events\evrgnini.c
InputName=evrgnini

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\events\evsci.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\events\evsci.c
InputName=evsci

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\events\evsci.c
InputName=evsci

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\events\evxface.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\events\evxface.c
InputName=evxface

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\events\evxface.c
InputName=evxface

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\events\evxfevnt.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\events\evxfevnt.c
InputName=evxfevnt

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\events\evxfevnt.c
InputName=evxfevnt

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\events\evxfregn.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\events\evxfregn.c
InputName=evxfregn

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\events\evxfregn.c
InputName=evxfregn

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Hardware"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\source\components\hardware\hwacpi.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\hardware\hwacpi.c
InputName=hwacpi

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\hardware\hwacpi.c
InputName=hwacpi

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\hardware\hwgpe.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\hardware\hwgpe.c
InputName=hwgpe

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\hardware\hwgpe.c
InputName=hwgpe

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\hardware\hwregs.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\hardware\hwregs.c
InputName=hwregs

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\hardware\hwregs.c
InputName=hwregs

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\hardware\hwsleep.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\hardware\hwsleep.c
InputName=hwsleep

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\hardware\hwsleep.c
InputName=hwsleep

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\hardware\hwtimer.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\hardware\hwtimer.c
InputName=hwtimer

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\hardware\hwtimer.c
InputName=hwtimer

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Interpreter"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exconfig.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exconfig.c
InputName=exconfig

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exconfig.c
InputName=exconfig

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exconvrt.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exconvrt.c
InputName=exconvrt

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exconvrt.c
InputName=exconvrt

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\excreate.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\excreate.c
InputName=excreate

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\excreate.c
InputName=excreate

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exdump.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exdump.c
InputName=exdump

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exdump.c
InputName=exdump

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exfield.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exfield.c
InputName=exfield

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exfield.c
InputName=exfield

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exfldio.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exfldio.c
InputName=exfldio

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exfldio.c
InputName=exfldio

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exmisc.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exmisc.c
InputName=exmisc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exmisc.c
InputName=exmisc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exmutex.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exmutex.c
InputName=exmutex

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exmutex.c
InputName=exmutex

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exnames.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exnames.c
InputName=exnames

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exnames.c
InputName=exnames

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exoparg1.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exoparg1.c
InputName=exoparg1

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exoparg1.c
InputName=exoparg1

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exoparg2.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exoparg2.c
InputName=exoparg2

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exoparg2.c
InputName=exoparg2

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exoparg3.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exoparg3.c
InputName=exoparg3

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exoparg3.c
InputName=exoparg3

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exoparg6.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exoparg6.c
InputName=exoparg6

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exoparg6.c
InputName=exoparg6

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exprep.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exprep.c
InputName=exprep

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exprep.c
InputName=exprep

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exregion.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exregion.c
InputName=exregion

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exregion.c
InputName=exregion

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exresnte.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exresnte.c
InputName=exresnte

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exresnte.c
InputName=exresnte

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exresolv.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exresolv.c
InputName=exresolv

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exresolv.c
InputName=exresolv

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exresop.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exresop.c
InputName=exresop

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exresop.c
InputName=exresop

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exstore.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exstore.c
InputName=exstore

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exstore.c
InputName=exstore

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exstoren.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exstoren.c
InputName=exstoren

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exstoren.c
InputName=exstoren

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exstorob.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exstorob.c
InputName=exstorob

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exstorob.c
InputName=exstorob

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exsystem.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exsystem.c
InputName=exsystem

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exsystem.c
InputName=exsystem

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\executer\exutils.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\executer\exutils.c
InputName=exutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\executer\exutils.c
InputName=exutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Namespace"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\source\components\namespace\nsaccess.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nsaccess.c
InputName=nsaccess

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nsaccess.c
InputName=nsaccess

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\namespace\nsalloc.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nsalloc.c
InputName=nsalloc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nsalloc.c
InputName=nsalloc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\namespace\nsdump.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nsdump.c
InputName=nsdump

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nsdump.c
InputName=nsdump

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nsdumpdv.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\NAMESPACE\nsdumpdv.c
InputName=nsdumpdv

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\NAMESPACE\nsdumpdv.c
InputName=nsdumpdv

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\namespace\nseval.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nseval.c
InputName=nseval

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nseval.c
InputName=nseval

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\namespace\nsinit.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nsinit.c
InputName=nsinit

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nsinit.c
InputName=nsinit

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\namespace\nsload.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nsload.c
InputName=nsload

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nsload.c
InputName=nsload

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\namespace\nsnames.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nsnames.c
InputName=nsnames

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nsnames.c
InputName=nsnames

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\namespace\nsobject.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nsobject.c
InputName=nsobject

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nsobject.c
InputName=nsobject

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nsparse.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\NAMESPACE\nsparse.c
InputName=nsparse

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\NAMESPACE\nsparse.c
InputName=nsparse

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\namespace\nssearch.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nssearch.c
InputName=nssearch

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nssearch.c
InputName=nssearch

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\namespace\nsutils.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nsutils.c
InputName=nsutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nsutils.c
InputName=nsutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\namespace\nswalk.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nswalk.c
InputName=nswalk

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nswalk.c
InputName=nswalk

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nsxfeval.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\NAMESPACE\nsxfeval.c
InputName=nsxfeval

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\NAMESPACE\nsxfeval.c
InputName=nsxfeval

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\namespace\nsxfname.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nsxfname.c
InputName=nsxfname

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nsxfname.c
InputName=nsxfname

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\namespace\nsxfobj.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\namespace\nsxfobj.c
InputName=nsxfobj

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\namespace\nsxfobj.c
InputName=nsxfobj

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\source\components\resources\rsaddr.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\resources\rsaddr.c
InputName=rsaddr

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\resources\rsaddr.c
InputName=rsaddr

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\resources\rscalc.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\resources\rscalc.c
InputName=rscalc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\resources\rscalc.c
InputName=rscalc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\resources\rscreate.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\resources\rscreate.c
InputName=rscreate

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\resources\rscreate.c
InputName=rscreate

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\resources\rsdump.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\resources\rsdump.c
InputName=rsdump

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\resources\rsdump.c
InputName=rsdump

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\resources\rsinfo.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\resources\rsinfo.c
InputName=rsinfo

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\resources\rsinfo.c
InputName=rsinfo

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\resources\rsio.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\resources\rsio.c
InputName=rsio

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\resources\rsio.c
InputName=rsio

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\resources\rsirq.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\resources\rsirq.c
InputName=rsirq

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\resources\rsirq.c
InputName=rsirq

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\resources\rslist.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\resources\rslist.c
InputName=rslist

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\resources\rslist.c
InputName=rslist

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\resources\rsmemory.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\resources\rsmemory.c
InputName=rsmemory

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\resources\rsmemory.c
InputName=rsmemory

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\resources\rsmisc.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\resources\rsmisc.c
InputName=rsmisc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\resources\rsmisc.c
InputName=rsmisc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\resources\rsutils.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\resources\rsutils.c
InputName=rsutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\resources\rsutils.c
InputName=rsutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\resources\rsxface.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\resources\rsxface.c
InputName=rsxface

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\resources\rsxface.c
InputName=rsxface

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Tables"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\components\tables\tbfadt.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\tables\tbfadt.c
InputName=tbfadt

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\tables\tbfadt.c
InputName=tbfadt

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\tables\tbfind.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\tables\tbfind.c
InputName=tbfind

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\tables\tbfind.c
InputName=tbfind

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\tables\tbinstal.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\tables\tbinstal.c
InputName=tbinstal

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\tables\tbinstal.c
InputName=tbinstal

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\tables\tbutils.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\tables\tbutils.c
InputName=tbutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\tables\tbutils.c
InputName=tbutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\tables\tbxface.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\tables\tbxface.c
InputName=tbxface

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\tables\tbxface.c
InputName=tbxface

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\tables\tbxfroot.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\tables\tbxfroot.c
InputName=tbxfroot

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\tables\tbxfroot.c
InputName=tbxfroot

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Parser"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\source\components\interpreter\parser\psargs.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\parser\psargs.c
InputName=psargs

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\parser\psargs.c
InputName=psargs

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\parser\psloop.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\parser\psloop.c
InputName=psloop

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\parser\psloop.c
InputName=psloop

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\parser\psopcode.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\parser\psopcode.c
InputName=psopcode

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\parser\psopcode.c
InputName=psopcode

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\parser\psparse.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\parser\psparse.c
InputName=psparse

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\parser\psparse.c
InputName=psparse

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\parser\psscope.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\parser\psscope.c
InputName=psscope

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\parser\psscope.c
InputName=psscope

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\parser\pstree.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\parser\pstree.c
InputName=pstree

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\parser\pstree.c
InputName=pstree

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\parser\psutils.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\parser\psutils.c
InputName=psutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\parser\psutils.c
InputName=psutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\parser\pswalk.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\parser\pswalk.c
InputName=pswalk

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\parser\pswalk.c
InputName=pswalk

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\parser\psxface.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\parser\psxface.c
InputName=psxface

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\parser\psxface.c
InputName=psxface

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Dispatcher"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\components\interpreter\dispatcher\dsfield.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\dispatcher\dsfield.c
InputName=dsfield

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\dispatcher\dsfield.c
InputName=dsfield

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\DISPATCHER\dsinit.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\INTERPRETER\DISPATCHER\dsinit.c
InputName=dsinit

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\INTERPRETER\DISPATCHER\dsinit.c
InputName=dsinit

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\dispatcher\dsmethod.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\dispatcher\dsmethod.c
InputName=dsmethod

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\dispatcher\dsmethod.c
InputName=dsmethod

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\dispatcher\dsmthdat.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\dispatcher\dsmthdat.c
InputName=dsmthdat

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\dispatcher\dsmthdat.c
InputName=dsmthdat

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\dispatcher\dsobject.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\dispatcher\dsobject.c
InputName=dsobject

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\dispatcher\dsobject.c
InputName=dsobject

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\dispatcher\dsopcode.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\dispatcher\dsopcode.c
InputName=dsopcode

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\dispatcher\dsopcode.c
InputName=dsopcode

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\dispatcher\dsutils.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\dispatcher\dsutils.c
InputName=dsutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\dispatcher\dsutils.c
InputName=dsutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\dispatcher\dswexec.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\dispatcher\dswexec.c
InputName=dswexec

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\dispatcher\dswexec.c
InputName=dswexec

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\dispatcher\dswload.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\dispatcher\dswload.c
InputName=dswload

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\dispatcher\dswload.c
InputName=dswload

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\dispatcher\dswscope.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\dispatcher\dswscope.c
InputName=dswscope

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\dispatcher\dswscope.c
InputName=dswscope

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\dispatcher\dswstate.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\components\interpreter\dispatcher\dswstate.c
InputName=dswstate

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\components\interpreter\dispatcher\dswstate.c
InputName=dswstate

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Disassembler"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmbuffer.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\Disassembler\dmbuffer.c
InputName=dmbuffer

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\Disassembler\dmbuffer.c
InputName=dmbuffer

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmnames.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\Disassembler\dmnames.c
InputName=dmnames

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\Disassembler\dmnames.c
InputName=dmnames

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\SOURCE\COMPONENTS\disassembler\dmobject.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\SOURCE\COMPONENTS\disassembler\dmobject.c
InputName=dmobject

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\SOURCE\COMPONENTS\disassembler\dmobject.c
InputName=dmobject

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmopcode.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\Disassembler\dmopcode.c
InputName=dmopcode

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\Disassembler\dmopcode.c
InputName=dmopcode

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmresrc.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\Disassembler\dmresrc.c
InputName=dmresrc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\Disassembler\dmresrc.c
InputName=dmresrc

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmresrcl.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\Disassembler\dmresrcl.c
InputName=dmresrcl

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\Disassembler\dmresrcl.c
InputName=dmresrcl

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmresrcs.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\Disassembler\dmresrcs.c
InputName=dmresrcs

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\Disassembler\dmresrcs.c
InputName=dmresrcs

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmutils.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\Disassembler\dmutils.c
InputName=dmutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\Disassembler\dmutils.c
InputName=dmutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmwalk.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\Disassembler\dmwalk.c
InputName=dmwalk

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\Disassembler\dmwalk.c
InputName=dmwalk

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Debugger"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\COMPONENTS\DEBUGGER\dbcmds.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbcmds.c
InputName=dbcmds

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbcmds.c
InputName=dbcmds

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\DEBUGGER\dbdisply.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbdisply.c
InputName=dbdisply

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbdisply.c
InputName=dbdisply

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\DEBUGGER\dbexec.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbexec.c
InputName=dbexec

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbexec.c
InputName=dbexec

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\DEBUGGER\dbfileio.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbfileio.c
InputName=dbfileio

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbfileio.c
InputName=dbfileio

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\DEBUGGER\dbhistry.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbhistry.c
InputName=dbhistry

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbhistry.c
InputName=dbhistry

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\DEBUGGER\dbinput.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbinput.c
InputName=dbinput

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbinput.c
InputName=dbinput

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\DEBUGGER\dbstats.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbstats.c
InputName=dbstats

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbstats.c
InputName=dbstats

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\DEBUGGER\dbutils.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbutils.c
InputName=dbutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbutils.c
InputName=dbutils

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\DEBUGGER\dbxface.c

!IF  "$(CFG)" == "AcpiSubsystem64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\NoDebug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbxface.c
InputName=dbxface

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AcpiSubsystem64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
IntDir=\Acpi\Generate\msvc\AcpiSubsystem64\Debug
InputPath=..\..\source\COMPONENTS\DEBUGGER\dbxface.c
InputName=dbxface

"$(IntDir)/$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	icl /W4 /Qms0 /Zc:forScope /WL /D ACPI_DEBUG_OUTPUT /D ACPI_DISASSEMBLER /D IA64 /Qstd=c99 /Za /Ob1 /c /I..\..\source\include /D ACPI_MACHINE_WIDTH=64 /D ACPI_LIBRARY /D ACPI_DEBUGGER /nologo /Qtrapuv /RTCu /Wcheck /Wport $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\source\Include\acconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acdebug.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acdispat.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\platform\acefi.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\platform\acenv.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acevents.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acexcep.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\platform\acfreebsd.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\platform\acgcc.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acglobal.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\achware.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acinterp.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\platform\aclinux.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\aclocal.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acmacros.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\platform\acmsvc.h
# End Source File
# Begin Source File

SOURCE=..\..\source\include\acnames.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acnamesp.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acobject.h
# End Source File
# Begin Source File

SOURCE=..\..\source\include\acopcode.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acoutput.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acparser.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acpi.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acpiosxf.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acpixf.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acresrc.h
# End Source File
# Begin Source File

SOURCE=..\..\source\include\acstruct.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\actables.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\actbl.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\actbl1.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\actbl2.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\actypes.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\acutils.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\platform\acwin.h
# End Source File
# Begin Source File

SOURCE=..\..\source\Include\amlcode.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\AcpiSubsystem64.plg
# End Source File
# End Target
# End Project
