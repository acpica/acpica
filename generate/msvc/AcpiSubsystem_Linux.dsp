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
CPP=cl.exe
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
# ADD CPP /nologo /GB /Gr /MT /Za /W4 /GX /O2 /I "..\..\source_linux\Include" /D "ACPI_LIBRARY" /D "NDEBUG" /D "DRIVER" /D "_NDEBUG" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN32" /D "_WIN_VER" /D "ACPI_DEFINE_ALTERNATE_TYPES" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
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
# ADD CPP /nologo /GB /Gr /MTd /Za /W4 /Gm /GX /ZI /Od /I "..\..\source_linux\Include" /D "ACPI_LIBRARY" /D "ACPI_FULL_DEBUG" /D "_DEBUG" /D "_WINDOWS" /D PROCESSOR_ARCHITECTURE=x86 /D "WIN32" /D "_WIN_VER" /D "ACPI_DEFINE_ALTERNATE_TYPES" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"\Acpi\Generate\msvc\AcpiSubsystem_Linux\AcpiCa_Linux.lib"

!ENDIF 

# Begin Target

# Name "AcpiSubsystem_Linux - Win32 Release"
# Name "AcpiSubsystem_Linux - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Group "Utilities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utcache.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\utilities\utclib.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\utilities\utcopy.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\utilities\utdebug.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\utilities\utdelete.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\utilities\uteval.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\utilities\utglobal.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\utilities\utinit.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\utilities\utmath.c
# ADD CPP /Ze
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\utilities\utmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utmutex.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\utilities\utobject.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utresrc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\utilities\utstate.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\utilities\utxface.c
# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\EVENTS\evevent.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\EVENTS\evgpe.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\events\evgpeblk.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\EVENTS\evmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\EVENTS\evregion.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\EVENTS\evrgnini.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\EVENTS\evsci.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\EVENTS\evxface.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\EVENTS\evxfevnt.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\EVENTS\evxfregn.c
# End Source File
# End Group
# Begin Group "Hardware"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\HARDWARE\hwacpi.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\HARDWARE\hwgpe.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\HARDWARE\hwregs.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\HARDWARE\hwsleep.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\HARDWARE\hwtimer.c
# ADD CPP /Ze
# End Source File
# End Group
# Begin Group "Interpreter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exconfig.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exconvrt.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\excreate.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exdump.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exfield.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exfldio.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exmutex.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exnames.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exoparg1.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exoparg2.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exoparg3.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exoparg6.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exprep.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exregion.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exresnte.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exresolv.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exresop.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exstore.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exstoren.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exstorob.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exsystem.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\EXECUTER\exutils.c
# End Source File
# End Group
# Begin Group "Namespace"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsaccess.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsdump.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsdumpdv.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nseval.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsinit.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsload.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsnames.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsobject.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsparse.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nssearch.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nswalk.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsxfeval.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsxfname.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\NAMESPACE\nsxfobj.c
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\resources\rsaddr.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\resources\rscalc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\resources\rscreate.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\resources\rsdump.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\resources\rsinfo.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\resources\rsio.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\resources\rsirq.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\resources\rslist.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\resources\rsmemory.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\resources\rsmisc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\resources\rsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\resources\rsxface.c
# End Source File
# End Group
# Begin Group "Tables"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\tables\tbconvrt.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\tables\tbget.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\tables\tbgetall.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\tables\tbinstal.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\tables\tbrsdt.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\tables\tbutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\tables\tbxface.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\tables\tbxfroot.c
# End Source File
# End Group
# Begin Group "Parser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\PARSER\psargs.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\interpreter\parser\psloop.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\PARSER\psopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\PARSER\psparse.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\PARSER\psscope.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\PARSER\pstree.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\PARSER\psutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\PARSER\pswalk.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\PARSER\psxface.c
# End Source File
# End Group
# Begin Group "Dispatcher"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\DISPATCHER\dsfield.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\DISPATCHER\dsinit.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\DISPATCHER\dsmethod.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\DISPATCHER\dsmthdat.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\DISPATCHER\dsobject.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\DISPATCHER\dsopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\DISPATCHER\dsutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\DISPATCHER\dswexec.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\DISPATCHER\dswload.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\DISPATCHER\dswscope.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\INTERPRETER\DISPATCHER\dswstate.c
# End Source File
# End Group
# Begin Group "Disassembler"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\Disassembler\dmbuffer.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\Disassembler\dmnames.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\components\disassembler\dmobject.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\Disassembler\dmopcode.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\Disassembler\dmresrc.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\Disassembler\dmresrcl.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\Disassembler\dmresrcs.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\Disassembler\dmutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\Disassembler\dmwalk.c
# End Source File
# End Group
# Begin Group "Debugger"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\DEBUGGER\dbcmds.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\DEBUGGER\dbdisply.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\DEBUGGER\dbexec.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\DEBUGGER\dbfileio.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\DEBUGGER\dbhistry.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\DEBUGGER\dbinput.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\DEBUGGER\dbstats.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\DEBUGGER\dbutils.c
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\COMPONENTS\DEBUGGER\dbxface.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\source_linux\Include\acconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acdebug.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\INCLUDE\acdisasm.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acdispat.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\platform\acefi.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\platform\acenv.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acevents.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acexcep.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\platform\acfreebsd.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\platform\acgcc.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acglobal.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\achware.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acinterp.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\platform\aclinux.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\aclocal.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acmacros.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\platform\acmsvc.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acnamesp.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acobject.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acoutput.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acparser.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acpi.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acpiosxf.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acpixf.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acresrc.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\include\acstruct.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\actables.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\actbl.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\actbl1.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\actbl2.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\actypes.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\acutils.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\platform\acwin.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\Include\amlcode.h
# End Source File
# Begin Source File

SOURCE=..\..\source_linux\INCLUDE\amlresrc.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\source\include\acnames.h
# End Source File
# Begin Source File

SOURCE=..\..\source\include\acopcode.h
# End Source File
# End Target
# End Project
