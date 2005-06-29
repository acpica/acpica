# Microsoft Developer Studio Project File - Name="AcpiExec" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=AcpiExec - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AcpiExec.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AcpiExec.mak" CFG="AcpiExec - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AcpiExec - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "AcpiExec - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Acpi/Generate/msvc", SVBAAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "AcpiExec - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\Acpi\Generate\msvc\AcpiExec"
# PROP Intermediate_Dir "\Acpi\Generate\msvc\AcpiExec"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "..\..\components\include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_ACPI_EXEC_APP" /D "_MULTI_THREADED" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"bin/AcpiExec.exe"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Checking existence of acpi/components/libraries directory
PreLink_Cmds=if NOT EXIST ..\..\libraries mkdir ..\..\libraries
PostBuild_Desc=Copy executable to acpi/components/libraries
PostBuild_Cmds=copy bin\acpiexec.exe ..\..\libraries\acpiexec.exe	dir ..\..\libraries\acpiexec.exe
# End Special Build Tool

!ELSEIF  "$(CFG)" == "AcpiExec - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\Acpi\generate\msvc\AcpiExec"
# PROP Intermediate_Dir "\Acpi\generate\msvc\AcpiExec"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MT /W4 /Gm /GX /ZI /Od /I "..\..\components\include" /D "_DEBUG" /D "WIN32" /D "WIN32_LEAN_AND_MEAN" /D "_CONSOLE" /D "_MBCS" /D "_ACPI_EXEC_APP" /D "_MULTI_THREADED" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"bin/AcpiExec.exe" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Checking existence of acpi/components/libraries directory
PreLink_Cmds=if NOT EXIST ..\..\libraries mkdir ..\..\libraries
PostBuild_Desc=Copy executable to acpi/components/libraries
PostBuild_Cmds=copy bin\acpiexec.exe ..\..\libraries\acpiexec.exe	dir ..\..\libraries\acpiexec.exe
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "AcpiExec - Win32 Release"
# Name "AcpiExec - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Utilities"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\components\core\utils\cmalloc.c
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
# Begin Group "Interpreter"

# PROP Default_Filter ""
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

# PROP Default_Filter ""
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
# Begin Group "Parser"

# PROP Default_Filter ""
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
# Begin Group "Hardware"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\components\core\hardware\hwacpi.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\hardware\hwgpe.c
# End Source File
# Begin Source File

SOURCE=..\..\components\core\hardware\hwregs.c
# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter ""
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
# Begin Group "AcpiExec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\components\Tools\AcpiExec\aeexec.c
# ADD CPP /Ze
# End Source File
# Begin Source File

SOURCE=..\..\components\Tools\AcpiExec\aemain.c

!IF  "$(CFG)" == "AcpiExec - Win32 Release"

# ADD CPP /Ze

!ELSEIF  "$(CFG)" == "AcpiExec - Win32 Debug"

# ADD CPP /Ze /FR

!ENDIF 

# End Source File
# End Group
# Begin Group "Debugger"

# PROP Default_Filter ".c"
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
# Begin Group "Tables"

# PROP Default_Filter ".c"
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
# End Group
# Begin Group "Common"

# PROP Default_Filter ".c"
# Begin Source File

SOURCE=..\..\components\common\getopt.c
# End Source File
# Begin Source File

SOURCE=..\..\components\os_interfaces\oswinxf.c
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ""
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
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\components\include\acstruct.h
# End Source File
# Begin Source File

SOURCE=..\..\components\Tools\AcpiExec\aecommon.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
