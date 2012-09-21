/******************************************************************************
 *
 * Module Name: atosxfctrl - include for AcpiOs* interfaces control
 *
 *****************************************************************************/

#ifndef _ATOSXFCTRL
#define _ATOSXFCTRL

#include "acpi.h"
#include "accommon.h"

/*
 * AcpiOs* interfaces enumeration
 */
typedef enum
{
    AcpiOsTotalC,
    AcpiOsInitializeC,
    AcpiOsTerminateC,
    AcpiOsGetRootPointerC,
    AcpiOsPredefinedOverrideC,
    AcpiOsTableOverrideC,
    AcpiOsGetTimerC,
    AcpiOsReadableC,
    AcpiOsWritableC,
    AcpiOsRedirectOutputC,
    AcpiOsPrintfC,
    AcpiOsVprintfC,
    AcpiOsGetLineC,
    AcpiOsMapMemoryC,
    AcpiOsUnmapMemoryC,
    AcpiOsAllocateC,
    AcpiOsFreeC,
    AcpiOsCreateSemaphoreC,
    AcpiOsDeleteSemaphoreC,
    AcpiOsWaitSemaphoreC,
    AcpiOsSignalSemaphoreC,
    AcpiOsCreateLockC,
    AcpiOsDeleteLockC,
    AcpiOsAcquireLockC,
    AcpiOsReleaseLockC,
    AcpiOsInstallInterruptHandlerC,
    AcpiOsRemoveInterruptHandlerC,
    AcpiOsGetThreadIdC,
    AcpiOsExecuteC,
    AcpiOsStallC,
    AcpiOsSleepC,
    AcpiOsValidateInterfaceC,
    AcpiOsValidateAddressC,
    AcpiOsReadPciConfigurationC,
    AcpiOsWritePciConfigurationC,
    AcpiOsDerivePciIdC,
    AcpiOsReadPortC,
    AcpiOsWritePortC,
    AcpiOsReadMemoryC,
    AcpiOsWriteMemoryC,
    AcpiOsSignalC,
    AcpiOsAllC,
} ACPI_OSXF;

#define OSXF_NUM(inds)    (inds##C)

/*
 * Test action codes
 */
typedef enum
{
    AtActUndefined,
    AtActRet_NULL,
    AtActRet_OK,
    AtActRet_ERROR,
    AtActRet_NO_MEMORY,
    AtActAll,
} AT_ACT_CODE;

/*
 * Test action duration flags
 */
typedef enum
{
    AtActD_Permanent,
    AtActD_OneTime,
    AtActD_All,
} AT_ACTD_FLAG;

typedef struct acpi_os_ctrl_act
{
    UINT64                  CallsCount;
    AT_ACTD_FLAG            ActFlag;
    AT_ACT_CODE             ActCode;
    ACPI_OSXF               ActOsxf;
} ACPI_OSXF_CTRL_ACT;

typedef struct acpi_os_control
{
    UINT64                  CallsCount;
    UINT64                  SuccessCount;
    ACPI_OSXF_CTRL_ACT      CtrlAct;
} ACPI_OSXF_CONTROL;

struct acpi_os_emul_reg;

typedef struct acpi_os_emul_reg
{
    UINT32                  Type;
    ACPI_PHYSICAL_ADDRESS   Address;
    UINT32                  Value;
    UINT32                  Width;
    UINT32                  ReadCount;
    UINT32                  WriteCount;
    struct acpi_os_emul_reg *Next;
} ACPI_OSXF_EMUL_REG;

#define EMUL_REG_MODE          1
#define EMUL_STATUS_REG_MODE   1

/*
 * Emulated registers types
 */
#define EMUL_REG_SYS           0x01
#define EMUL_REG_IO            0x02

/*
 * Fixed ACPI h/w emulated registers numbers
 */
typedef enum
{
    AtPm1aStatus,
    AtPm1bStatus,
    AtPm1aEnable,
    AtPm1bEnable,
    AtPm1aControl,
    AtPm1bControl,
    AtPm2Control,
    AtPmTimer,
    AtSmiCmdBlock,
    AtFixeReg_All,
} AT_FIXED_REG_NUM;

#define MAX(a,b)             ((a) < (b))? (b) : (a)
#define MIN(a,b)             ((a) < (b))? (a) : (b)

/*
 * Check IF statistics conditions flags
 */
#define OSINIT_STAT             0x01
#define MALLOC_STAT             0x02
#define MMAP_STAT               0x04
#define SEMAPH_STAT             0x08
#define LOCK_STAT               0x10
#define TOTAL_STAT              0x20
#define FREE_STAT               0x40
#define SUCCESS_STAT            (OSINIT_STAT | MALLOC_STAT | MMAP_STAT|\
    SEMAPH_STAT | LOCK_STAT)
#define ALL_STAT                (SUCCESS_STAT | FREE_STAT)
#define SYS_STAT                (SUCCESS_STAT & ~MMAP_STAT)

extern const char               *OsxfNames[];

#define OSXF_NAME(ind)          OsxfNames[ind]

extern ACPI_OSXF_CONTROL        OsxfCtrl[];

extern UINT32                   OsInitialized;
extern UINT64                   TotalCallsCountMark;
extern UINT64                   FinalCallsCountMark;
extern ACPI_OSXF_CONTROL        Init_OsxfCtrl;


#define AT_CTRL_DECL1(inds) \
    ACPI_STATUS             Status; \
    ACPI_OSXF_CONTROL       *Ctrl = &OsxfCtrl[OSXF_NUM(inds)]

#define AT_CTRL_DECL2(inds) \
    if (!(++OsxfCtrl[AcpiOsTotalC].CallsCount)) \
    { \
        printf("%s error: too many Calls!\n", \
            OSXF_NAME(AcpiOsTotalC)); \
        exit(-1); \
    } \
    if (!(++Ctrl->CallsCount)) \
    { \
        printf("%s error: too many Calls!\n", \
            OSXF_NAME(OSXF_NUM(inds))); \
        exit(-1); \
    }

#define AT_CTRL_DECL3(inds) \
    ACPI_OSXF_CONTROL       *Ctrl = &OsxfCtrl[OSXF_NUM(inds)]

#define AT_CTRL_SUCCESS0(inds) \
    if (!(++Ctrl->SuccessCount)) \
    { \
        printf("%s error: too many Success Calls!\n", \
            OSXF_NAME(OSXF_NUM(inds))); \
        exit(-1); \
    }

#define AT_CTRL_SUCCESS(inds) \
    if (ACPI_SUCCESS(Status) && !(++Ctrl->SuccessCount)) \
    { \
        printf("%s error: too many Success Calls!\n", \
            OSXF_NAME(OSXF_NUM(inds))); \
        exit(-1); \
    }

#define AT_CTRL_DECL(inds) \
    AT_CTRL_DECL1(inds); \
    AT_CTRL_DECL2(inds);

#define AT_CTRL_DECL0(inds) \
    AT_CTRL_DECL3(inds); \
    AT_CTRL_DECL2(inds);

#define AT_ACT_EXIT(inds) \
    printf("Test error: for %s unknown test action %d," \
        " CallsCount %d\n", OSXF_NAME(OSXF_NUM(inds)), \
        Ctrl->CtrlAct.ActCode, (UINT32)Ctrl->CtrlAct.CallsCount); \
    exit(-1)

#define AT_CHCK_RET_STATUS(inds) \
        if (OsxfCtrlRetError(OSXF_NUM(inds))) \
        { \
            return (AE_ERROR); \
        }

#define AT_CHCK_RET_STATUS2(inds) \
    if (OsxfCtrl[AcpiOsTotalC].CtrlAct.CallsCount && \
        OsxfCtrl[AcpiOsTotalC].CallsCount >= \
        OsxfCtrl[AcpiOsTotalC].CtrlAct.CallsCount) \
    { \
        if (OsxfCtrl[AcpiOsTotalC].CtrlAct.ActCode == AtActRet_ERROR) \
        { \
            if (OsxfCtrl[AcpiOsTotalC].CtrlAct.ActFlag == AtActD_OneTime) { \
                OsxfCtrl[AcpiOsTotalC].CtrlAct.CallsCount = 0; \
            } \
            OsxfCtrl[AcpiOsTotalC].CtrlAct.ActOsxf = OSXF_NUM(inds); \
            return (AE_ERROR); \
        } \
        AT_ACT_EXIT(inds); \
    }

#define AT_CHCK_RET_ERROR(inds) \
    if (Ctrl->CtrlAct.CallsCount && \
        Ctrl->CallsCount >= Ctrl->CtrlAct.CallsCount) \
    { \
        if (Ctrl->CtrlAct.ActCode == AtActRet_ERROR) \
        { \
            if (Ctrl->CtrlAct.ActFlag == AtActD_OneTime) \
            { \
                Ctrl->CtrlAct.CallsCount = 0; \
            } \
            Ctrl->CtrlAct.ActOsxf = OSXF_NUM(inds); \
            return (AE_ERROR); \
        } \
        AT_ACT_EXIT(inds); \
    }

#define AT_CHCK_RET_NULL(inds) \
    if (Ctrl->CtrlAct.CallsCount && \
        Ctrl->CallsCount >= Ctrl->CtrlAct.CallsCount) \
    { \
        if (Ctrl->CtrlAct.ActCode == AtActRet_NULL) \
        { \
            if (Ctrl->CtrlAct.ActFlag == AtActD_OneTime) \
            {\
                Ctrl->CtrlAct.CallsCount = 0; \
            } \
            Ctrl->CtrlAct.ActOsxf = OSXF_NUM(inds); \
            return (NULL); \
        } \
        AT_ACT_EXIT(inds); \
    }

#define AT_CHCK_RET_ZERO(inds) \
    if (Ctrl->CtrlAct.CallsCount && \
        Ctrl->CallsCount >= Ctrl->CtrlAct.CallsCount) \
    { \
        if (Ctrl->CtrlAct.ActCode == AtActRet_NULL) \
        { \
            if (Ctrl->CtrlAct.ActFlag == AtActD_OneTime) \
            {\
                Ctrl->CtrlAct.CallsCount = 0; \
            } \
            Ctrl->CtrlAct.ActOsxf = OSXF_NUM(inds); \
            return (0); \
        } \
        AT_ACT_EXIT(inds); \
    }

#define AT_CHCK_RET_NO_MEMORY(inds) \
    if (Ctrl->CtrlAct.CallsCount && \
        Ctrl->CallsCount >= Ctrl->CtrlAct.CallsCount) \
    { \
	    if (Ctrl->CtrlAct.ActCode == AtActRet_NO_MEMORY) \
        { \
            if (Ctrl->CtrlAct.ActFlag == AtActD_OneTime) \
            { \
                Ctrl->CtrlAct.CallsCount = 0; \
            } \
            Ctrl->CtrlAct.ActOsxf = OSXF_NUM(inds); \
            return (AE_NO_MEMORY); \
	    } \
        AT_ACT_EXIT(inds); \
    }

ACPI_STATUS
OsxfCtrlInit(
    void);

ACPI_STATUS
OsxfCtrlSet(
    ACPI_OSXF               OsxfNum,
    UINT64                  CallsCount,
    AT_ACTD_FLAG            ActFlag,
    AT_ACT_CODE             ActCode);

ACPI_OSXF
OsxfCtrlGetActOsxf(
    ACPI_OSXF               OsxfNum,
    UINT32                  Clean);

void
OsxfUpdateCallsMark(void);

UINT64
OsxfGetCallsDiff(void);

ACPI_STATUS
OsxfCtrlPrint(
    void);

ACPI_STATUS
OsxfCtrlCheck(
    UINT32                  CondFlags,
    UINT32                  FreeCond);

ACPI_STATUS
InitOsxfCtrlCheck(
    ACPI_STATUS             Check_Status);

UINT64
OsxfCtrlTotalCalls(
    UINT32                  SuccessCountFlag);

UINT64
OsxfCtrlGetCalls(
    ACPI_OSXF               OsxfNum,
    UINT32                  SuccessCountFlag);

INT64
OsxfCtrlGetDiff(
    UINT32                  OsxfFlags);

ACPI_STATUS
OsxfCtrlSetFixedReg(
    AT_FIXED_REG_NUM       RegNum,
    UINT32                 Value);

ACPI_STATUS
OsxfCtrlSetFixedRegOnes(
    AT_FIXED_REG_NUM       RegNum);

ACPI_STATUS
OsxfCtrlGetFixedReg(
    AT_FIXED_REG_NUM       RegNum,
    UINT32                 *Value);

ACPI_STATUS
OsxfCtrlClearFixedRegs(void);

ACPI_STATUS
OsxfCtrlWriteReg(
    UINT32                  Type,
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT32                  Value,
    UINT32                  Width);

ACPI_STATUS
OsxfCtrlReadReg(
    UINT32                  Type,
    ACPI_PHYSICAL_ADDRESS   Address,
    UINT32                  *Value,
    UINT32                  Width);

ACPI_STATUS
OsxfCtrlAcpiRegsInit(
    ACPI_TABLE_FADT         *FADT,
    ACPI_GENERIC_ADDRESS    XPm1aEnable,
    ACPI_GENERIC_ADDRESS    XPm1bEnable);

void
OsxfCtrlRegService(UINT32 ServiceFlag);

UINT32
OsxfCtrlRetError(
    ACPI_OSXF               OsxfNum);

#endif /* _ATOSXFCTRL */
