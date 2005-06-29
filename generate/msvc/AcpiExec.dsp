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
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AcpiExec - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W4 /GX /O2 /I "..\..\Subsystem\Include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "SYSTEM_CLIB_FUNCTIONS" /D "ACPI_DEBUG" /D "ACPI_APPLICATION" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "AcpiExec - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MT /W4 /Gm /GX /ZI /Od /I "..\..\Subsystem\Include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "SYSTEM_CLIB_FUNCTIONS" /D "ACPI_DEBUG" /D "ACPI_APPLICATION" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

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

SOURCE=..\..\Subsystem\Common\cmapi.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmcreate.c
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

SOURCE=..\..\Subsystem\Common\cmsize.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Common\cmstate.c
# End Source File
# End Group
# Begin Group "Interpreter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iapi.c
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

SOURCE=..\..\Subsystem\Interpreter\ievalue.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\iexecute.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isdebug.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isdump.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isnames.c
# End Source File
# Begin Source File

SOURCE=..\..\Subsystem\Interpreter\isutils.c
# End Source File
# End Group
# Begin Group "Methods"

# PROP Default_Filter ""
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

# PROP Default_Filter ""
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
# Begin Group "Parser"

# PROP Default_Filter ""
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
# Begin Group "Hardware"

# PROP Default_Filter ""
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
# Begin Group "Events"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Subsystem\Events\evapi.c
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

SOURCE=..\..\Subsystem\Events\evsci.c
# End Source File
# End Group
# Begin Group "AcpiExec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Tools\AcpiExec\aeexec.c
# End Source File
# Begin Source File

SOURCE=..\..\Tools\AcpiExec\aemain.c

!IF  "$(CFG)" == "AcpiExec - Win32 Release"

!ELSEIF  "$(CFG)" == "AcpiExec - Win32 Debug"

# ADD CPP /FR

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Tools\AcpiExec\aeosd.c

!IF  "$(CFG)" == "AcpiExec - Win32 Release"

!ELSEIF  "$(CFG)" == "AcpiExec - Win32 Debug"

# ADD CPP /FR

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Tools\AcpiExec\getopt.c

!IF  "$(CFG)" == "AcpiExec - Win32 Release"

!ELSEIF  "$(CFG)" == "AcpiExec - Win32 Debug"

# ADD CPP /FR

!ENDIF 

# End Source File
# End Group
# Begin Group "Debugger"

# PROP Default_Filter ".c"
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

SOURCE=..\..\Subsystem\Debugger\dbfileio.c
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
# Begin Group "Tables"

# PROP Default_Filter ".c"
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
