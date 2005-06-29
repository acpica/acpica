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
# PROP Scc_ProjName ""$/Acpi Components/Generate/VC", SVBAAAAA"
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
# PROP Output_Dir "\Acpi\Components\Generate\VC\AcpiExec"
# PROP Intermediate_Dir "\Acpi\Components\Generate\VC\AcpiExec"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /Za /W4 /GX /O2 /I "..\..\Subsystem\Include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "ACPI_USE_SYSTEM_CLIBRARY" /D "ACPI_DEBUG" /D "ACPI_APPLICATION" /D "ENABLE_DEBUGGER" /YX /FD /c
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
# PROP Output_Dir "\Acpi\Components\Generate\VC\AcpiExec"
# PROP Intermediate_Dir "\Acpi\Components\Generate\VC\AcpiExec"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MT /Za /W4 /Gm /GX /ZI /Od /I "..\..\Subsystem\Include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "ACPI_USE_SYSTEM_CLIBRARY" /D "ACPI_DEBUG" /D "ACPI_APPLICATION" /D "ENABLE_DEBUGGER" /FR /YX /FD /GZ /c
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
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmalloc.c
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
# Begin Group "Interpreter"

# PROP Default_Filter ""
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

# PROP Default_Filter ""
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
# Begin Group "Parser"

# PROP Default_Filter ""
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
# Begin Group "Hardware"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\subsystem\Hardware\hwacpi.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Hardware\hwgpe.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Hardware\hwregs.c
# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter ""
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
# Begin Group "AcpiExec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Tools\AcpiExec\aeexec.c
# ADD CPP /Ze
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AcpiExec\aemain.c

!IF  "$(CFG)" == "AcpiExec - Win32 Release"

# ADD CPP /Ze

!ELSEIF  "$(CFG)" == "AcpiExec - Win32 Debug"

# ADD CPP /Ze /FR

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Tools\AcpiExec\aeosd.c

!IF  "$(CFG)" == "AcpiExec - Win32 Release"

# ADD CPP /Ze

!ELSEIF  "$(CFG)" == "AcpiExec - Win32 Debug"

# ADD CPP /Ze /FR

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Tools\Common\getopt.c
# ADD CPP /Ze
# End Source File
# End Group
# Begin Group "Debugger"

# PROP Default_Filter ".c"
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
# Begin Group "Tables"

# PROP Default_Filter ".c"
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
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\Tools\AcpiExec\aecommon.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
