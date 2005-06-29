# Microsoft Developer Studio Project File - Name="AslCompiler" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AslCompiler - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AslCompiler.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AslCompiler.mak" CFG="AslCompiler - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AslCompiler - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AslCompiler - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AslCompiler - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\Acpi\Components\Generate\VC\AslCompiler"
# PROP Intermediate_Dir "\Acpi\Components\Generate\VC\AslCompiler"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /W4 /GX /O2 /I "..\..\Subsystem\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "YY_NEVER_INTERACTIVE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 libflex.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /machine:I386 /out:"Release/iasl.exe"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copy compiler to libraries directory
PostBuild_Cmds=copy Release\iasl.exe ..\..\Libraries
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AslCompiler - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\Acpi\Components\Generate\VC\AslCompiler"
# PROP Intermediate_Dir "\Acpi\Components\Generate\VC\AslCompiler"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\Subsystem\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "YY_NEVER_INTERACTIVE" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libflex.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /machine:I386 /out:"Debug/iasl.exe" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copy compiler to libraries directory
PostBuild_Cmds=copy Debug\iasl.exe ..\..\Libraries
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "AslCompiler - Win32 Release"
# Name "AslCompiler - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\aslanalyze.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\aslcodegen.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\AslCompiler.l.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\AslCompiler.y.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\aslerror.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\asllength.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\aslmain.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\aslmap.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\aslopcodes.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\aslresource.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\asltree.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\aslutils.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\Common\getopt.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\AslCompiler.h
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\AslCompiler.y.h
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AslCompiler\aslresource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=../../Tools/AslCompiler/AslCompiler.l

!IF  "$(CFG)" == "AslCompiler - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Building Lexer
InputPath=../../Tools/AslCompiler/AslCompiler.l
InputName=AslCompiler

"$(InputName).l.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex.exe -PAslCompiler -i -t $(InputName).l > $(InputName).l.c

# End Custom Build

!ELSEIF  "$(CFG)" == "AslCompiler - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Building Lexer from $(InputPath)
InputPath=../../Tools/AslCompiler/AslCompiler.l

"$(InputPath).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	flex.exe -PAslCompiler -i -o$(InputPath).c $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=../../Tools/AslCompiler/AslCompiler.y

!IF  "$(CFG)" == "AslCompiler - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Building Parser
InputPath=../../Tools/AslCompiler/AslCompiler.y
InputName=AslCompiler

BuildCmds= \
	bison.exe -pAslCompiler -d -v -o$(InputName).c $(InputName)

"$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AslCompiler - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Building Parser from $(InputPath)
InputPath=../../Tools/AslCompiler/AslCompiler.y

BuildCmds= \
	bison.exe -pAslCompiler -t -d -v -o$(InputPath).c $(InputPath)

"$(InputPath).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputPath).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
