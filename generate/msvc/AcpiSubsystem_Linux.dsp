# Microsoft Developer Studio Project File - Name="AcpiSubsystem_Linux" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=AcpiSubsystem_Linux - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AcpiSubsystem_Linux.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AcpiSubsystem_Linux.mak" CFG="AcpiSubsystem_Linux - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AcpiSubsystem_Linux - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "AcpiSubsystem_Linux - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Acpi/generate/msvc", SVBAAAAA"
# PROP Scc_LocalPath "."
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "AcpiSubsystem_Linux - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\Acpi\Generate\msvc\AcpiSubsystem_Linux"
# PROP Intermediate_Dir "\Acpi\Generate\msvc\AcpiSubsystem_Linux"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Gz /Za /W4 /GX /O2 /I "..\..\source_linux\Include" /D "NDEBUG" /D "ACPILIB_GEN" /D "DRIVER" /D "_NDEBUG" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN32" /D "_WIN_VER" /D "DEFINE_ALTERNATE_TYPES" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"\Acpi\Generate\msvc\AcpiSubsystem_Linux\AcpiCa_Linux.lib"

!ELSEIF  "$(CFG)" == "AcpiSubsystem_Linux - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\Acpi\Generate\msvc\AcpiSubsystem_Linux"
# PROP Intermediate_Dir "\Acpi\Generate\msvc\AcpiSubsystem_Linux"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Gz /Za /W4 /Gm /GX /ZI /Od /I "..\..\source_linux\Include" /D "ACPI_DEBUG" /D "_DEBUG" /D "ENABLE_DEBUGGER" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN32" /D "_WIN_VER" /D "DEFINE_ALTERNATE_TYPES" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"\Acpi\Generate\msvc\AcpiSubsystem_Linux\AcpiCa_Linux.lib"

!ENDIF 

# Begin Target

# Name "AcpiSubsystem_Linux - Win32 Release"
# Name "AcpiSubsystem_Linux - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\debugger\dbcmds.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\debugger\dbdisasm.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\debugger\dbdisply.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\debugger\dbexec.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\debugger\dbfileio.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\debugger\dbhistry.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\debugger\dbinput.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\debugger\dbstats.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\debugger\dbutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\debugger\dbxface.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\dispatcher\dsfield.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\dispatcher\dsmethod.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\dispatcher\dsmthdat.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\dispatcher\dsobject.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\dispatcher\dsopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\dispatcher\dsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\dispatcher\dswexec.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\dispatcher\dswload.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\dispatcher\dswscope.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\dispatcher\dswstate.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\events\evevent.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\events\evmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\events\evregion.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\events\evrgnini.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\events\evsci.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\events\evxface.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\events\evxfevnt.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\events\evxfregn.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exconfig.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exconvrt.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\excreate.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exdump.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exfield.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exfldio.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exmutex.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exnames.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exoparg1.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exoparg2.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exoparg3.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exoparg6.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exprep.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exregion.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exresnte.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exresolv.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exresop.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exstore.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exstoren.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exstorob.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exsystem.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\executer\exutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\hardware\hwacpi.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\hardware\hwgpe.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\hardware\hwregs.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\hardware\hwsleep.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\hardware\hwtimer.c
# ADD CPP /Ze
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nsaccess.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nsalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nsdump.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nseval.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nsinit.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nsload.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nsnames.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nsobject.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nssearch.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nswalk.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nsxfname.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\namespace\nsxfobj.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\parser\psargs.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\parser\psfind.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\parser\psopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\parser\psparse.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\parser\psscope.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\parser\pstree.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\parser\psutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\parser\pswalk.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\parser\psxface.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\resources\rsaddr.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\resources\rscalc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\resources\rscreate.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\resources\rsdump.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\resources\rsio.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\resources\rsirq.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\resources\rslist.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\resources\rsmemory.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\resources\rsmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\resources\rsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\resources\rsxface.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\tables\tbconvrt.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\tables\tbget.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\tables\tbgetall.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\tables\tbinstal.c
# End Source File
# Begin Source File

SOURCE=..\..\source\COMPONENTS\tables\tbrsdt.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\tables\tbutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\tables\tbxface.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\tables\tbxfroot.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utclib.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utcopy.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utdebug.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utdelete.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\uteval.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utglobal.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utinit.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utmath.c
# ADD CPP /Ze
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utobject.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utxface.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\source_linux\include\acconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acdebug.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acdispat.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\platform\acefi.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\platform\acenv.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acevents.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acexcep.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\platform\acfreebsd.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\platform\acgcc.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acglobal.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\achware.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acinterp.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\platform\aclinux.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\aclocal.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acmacros.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\platform\acmsvc.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acnamesp.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acobject.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acoutput.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acparser.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acpi.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acpiosxf.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acpixf.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acresrc.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acstruct.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\actables.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\actbl.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\actbl1.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\actbl2.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\actypes.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acutils.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\platform\acwin.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\amlcode.h
# End Source File
# End Group
# End Target
# End Project
