# Microsoft Developer Studio Project File - Name="AslCompiler64" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=AslCompiler64 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AslCompiler64.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AslCompiler64.mak" CFG="AslCompiler64 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AslCompiler64 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AslCompiler64 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Acpi/source/compiler", CRIAAAAA"
# PROP Scc_LocalPath "..\.."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AslCompiler64 - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\Acpi\generate\msvc\AslCompiler64\NoDebug"
# PROP Intermediate_Dir "\Acpi\generate\msvc\AslCompiler64\NoDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /Gr /Za /W3 /Gm /GX /Zi /O2 /I "$(OutDir)\..\\" /I "..\..\source\Include" /D "NDEBUG" /D "WIN64" /D "_WINDOWS" /D "_MBCS" /D "YY_NEVER_INTERACTIVE" /D "ACPI_ASL_COMPILER" /D "_IA64" /FR /FD /c
# SUBTRACT CPP /nologo /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:IX86 /machine:IA64
# ADD LINK32 ..\..\tools_3rd_party\BisonFlex\libflex.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /incremental:yes /machine:IX86 /out:"Release/iasl64.exe" /machine:IA64
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copy compiler to libraries directory
PostBuild_Cmds=copy Release\iasl64.exe ..\..\Libraries
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AslCompiler64 - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\Acpi\generate\msvc\AslCompiler64\Debug"
# PROP Intermediate_Dir "\Acpi\generate\msvc\AslCompiler64\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /Gr /Za /W4 /Gm /GX /Zi /Od /I "$(OutDir)" /I "$(OutDir)\..\\" /I "..\..\source\Include" /D "_DEBUG" /D "WIN64" /D "_WINDOWS" /D "_MBCS" /D "YY_NEVER_INTERACTIVE" /D "ACPI_ASL_COMPILER" /D "_IA64" /D "_M_IX86" /FR /FD /GZ /c
# SUBTRACT CPP /nologo /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept /machine:IA64
# ADD LINK32 ..\..\tools_3rd_party\BisonFlex\libflex.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /debug /machine:IX86 /out:"Debug/iasldebug64.exe" /pdbtype:sept /machine:IA64
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Copy compiler to libraries directory
PostBuild_Cmds=copy Debug\iasldebug64.exe ..\..\Libraries
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "AslCompiler64 - Win32 Release"
# Name "AslCompiler64 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Utilities"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\source\COMPONENTS\utilities\utalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utcache.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\utilities\utcopy.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\utilities\utdebug.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\utilities\utdelete.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\utilities\utglobal.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\utilities\utmath.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\utilities\utmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utmutex.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\utilities\utobject.c
# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utresrc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\components\utilities\utstate.c
# End Source File
# End Group
# Begin Group "Namespace"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nsaccess.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nsalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nsdump.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nsnames.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nsobject.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nsparse.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nssearch.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nswalk.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\NAMESPACE\nsxfobj.c
# End Source File
# End Group
# Begin Group "Compiler"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\compiler\aslanalyze.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslcodegen.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslcompile.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslerror.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslfiles.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslfold.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\asllength.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\asllisting.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslload.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\asllookup.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslmain.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslmap.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslopcodes.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\asloperands.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslopt.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslresource.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslrestype1.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslrestype2.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslstubs.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\asltransform.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\asltree.c
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslutils.c
# End Source File
# End Group
# Begin Group "Parser"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\PARSER\psargs.c
# End Source File
# Begin Source File

SOURCE=..\..\source\components\interpreter\parser\psloop.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\PARSER\psopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\PARSER\psparse.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\PARSER\psscope.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\PARSER\pstree.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\PARSER\psutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\PARSER\pswalk.c
# End Source File
# End Group
# Begin Group "Dispatcher"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\DISPATCHER\dsfield.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\DISPATCHER\dsobject.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\DISPATCHER\dsopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\DISPATCHER\dsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\DISPATCHER\dswexec.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\DISPATCHER\dswload.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\DISPATCHER\dswscope.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\DISPATCHER\dswstate.c
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\source\common\adisasm.c
# End Source File
# Begin Source File

SOURCE=..\..\source\common\dmrestag.c
# End Source File
# Begin Source File

SOURCE=..\..\source\common\dmtable.c
# End Source File
# Begin Source File

SOURCE=..\..\source\common\dmtbdump.c
# End Source File
# Begin Source File

SOURCE=..\..\source\common\dmtbinfo.c
# End Source File
# Begin Source File

SOURCE=..\..\source\common\getopt.c
# End Source File
# Begin Source File

SOURCE=..\..\source\os_specific\service_layers\oswinxf.c
# End Source File
# End Group
# Begin Group "Intermediate"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AslCompiler\aslcompiler.l.c
# ADD CPP /I "..\..\source\compiler"
# End Source File
# Begin Source File

SOURCE=.\AslCompiler\aslcompiler.y.c
# ADD CPP /I "..\..\source\compiler"
# End Source File
# Begin Source File

SOURCE=.\AslCompiler\AslCompiler.y.h
# End Source File
# End Group
# Begin Group "Interpreter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exconvrt.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\excreate.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exdump.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exmutex.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exnames.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exoparg1.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exoparg2.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exoparg3.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exoparg6.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exprep.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exregion.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exresnte.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exresolv.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exresop.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exstore.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exstoren.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exstorob.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exsystem.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\INTERPRETER\EXECUTER\exutils.c
# End Source File
# End Group
# Begin Group "Disassembler"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\COMPONENTS\DEBUGGER\dbfileio.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmbuffer.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmnames.c
# End Source File
# Begin Source File

SOURCE=..\..\SOURCE\COMPONENTS\disassembler\dmobject.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmresrc.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmresrcl.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmresrcs.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\Disassembler\dmwalk.c
# End Source File
# End Group
# Begin Group "Tables"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source\components\tables\tbfadt.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\tables\tbinstal.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\tables\tbutils.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\source\include\acnames.h
# End Source File
# Begin Source File

SOURCE=..\..\source\include\acopcode.h
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\AslCompiler.h
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\aslglobal.h
# End Source File
# Begin Source File

SOURCE=..\..\source\compiler\asltypes.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=../../source/compiler/AslCompiler.l

!IF  "$(CFG)" == "AslCompiler64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Building Lexer from $(InputPath) to $(ProjDir)/AslCompiler64/$(InputName).l.c
ProjDir=.
InputPath=../../source/compiler/AslCompiler.l
InputName=AslCompiler

"$(ProjDir)/AslCompiler64/$(InputName).l.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\Tools_3rd_party\BisonFlex\flex.exe -PAslCompiler -i -s -CF -o$(ProjDir)/AslCompiler64/$(InputName).l.c $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "AslCompiler64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Building Lexer from $(InputPath) to $(ProjDir)/AslCompiler64/$(InputName).l.c
ProjDir=.
InputPath=../../source/compiler/AslCompiler.l
InputName=AslCompiler

"$(ProjDir)/AslCompiler64/$(InputName).l.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\Tools_3rd_party\BisonFlex\flex.exe -PAslCompiler -i -s -CF -o$(ProjDir)/AslCompiler64/$(InputName).l.c $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=../../source/compiler/AslCompiler.y

!IF  "$(CFG)" == "AslCompiler64 - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Building parser from $(InputPath) to $(ProjDir)/AslCompiler64/$(InputName).y.c
WkspDir=.
ProjDir=.
InputPath=../../source/compiler/AslCompiler.y
InputName=AslCompiler

BuildCmds= \
	$(WkspDir)\..\..\Tools_3rd_party\BisonFlex\bison_custom.exe -pAslCompiler -t -d -v -o$(ProjDir)/AslCompiler64/$(InputName).y.c $(InputPath)

"$(ProjDir)/AslCompiler64/$(InputName).y.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)/AslCompiler64/$(InputName).y.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "AslCompiler64 - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Building parser from $(InputPath) to $(ProjDir)/AslCompiler64/$(InputName).y.c
WkspDir=.
ProjDir=.
InputPath=../../source/compiler/AslCompiler.y
InputName=AslCompiler

BuildCmds= \
	$(WkspDir)\..\..\Tools_3rd_party\BisonFlex\bison_custom.exe -pAslCompiler -t -d -v -o$(ProjDir)/AslCompiler64/$(InputName).y.c $(InputPath)

"$(ProjDir)/AslCompiler64/$(InputName).y.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(ProjDir)/AslCompiler64/$(InputName).y.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
