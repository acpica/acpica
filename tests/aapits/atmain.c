/******************************************************************************
 *
 * Module Name: atmain - ACPICA API test suit launcher
 *
 *****************************************************************************/

#define AT_GLOBAL_DATA

#include "atcommon.h"
#include "atinit.h"
#include "atmemory.h"
#include "athardware.h"
#include "attable.h"
#include "atnamespace.h"
#include "atresource.h"
#include "atfixedevent.h"
#include "atgpe.h"
#include "athandlers.h"
#include "atosxfctrl.h"

#define _COMPONENT          ACPI_TOOLS
        ACPI_MODULE_NAME    ("atmain")


typedef struct at_test_case_descriptor
{
    AT_TEST                 **Tests;
    UINT32                  TestsNum;
    char                    *BaseName;
} AT_TEST_CASE_DESC;

AT_TEST                 *AtInitTests[AT_INIT_TEST_NUM] = {
    AtInitTest0000, AtInitTest0001, AtInitTest0002, AtInitTest0003,
    AtInitTest0004, AtInitTest0005, AtInitTest0006, AtInitTest0007,
    AtInitTest0008, AtInitTest0009, AtInitTest0010, AtInitTest0011,
    AtInitTest0012, AtInitTest0013, AtInitTest0014, AtInitTest0015,
    AtInitTest0016, AtInitTest0017, AtInitTest0018, AtInitTest0019,
    AtInitTest0020, AtInitTest0021, AtInitTest0022, AtInitTest0023,
    AtInitTest0024, AtInitTest0025, AtInitTest0026, AtInitTest0027,
    AtInitTest0028, AtInitTest0029, AtInitTest0030, AtInitTest0031,
    AtInitTest0032, AtInitTest0033, AtInitTest0034, AtInitTest0035,
    AtInitTest0036, AtInitTest0037, AtInitTest0038, AtInitTest0039,
    AtInitTest0040, AtInitTest0041, AtInitTest0042, AtInitTest0043,
    AtInitTest0044, AtInitTest0045, AtInitTest0046, AtInitTest0047,
    AtInitTest0048, AtInitTest0049, AtInitTest0050, AtInitTest0051,
    AtInitTest0052, AtInitTest0053, AtInitTest0054, AtInitTest0055,
    AtInitTest0056, AtInitTest0057, AtInitTest0058, AtInitTest0059,
    AtInitTest0060};

AT_TEST                 *AtMemoryTests[AT_MEMM_TEST_NUM] = {
    AtMemoryTest0000};

AT_TEST                 *AtHardwareTests[AT_HDWM_TEST_NUM] = {
    AtHardwTest0000, AtHardwTest0001, AtHardwTest0002, AtHardwTest0003,
    AtHardwTest0004, AtHardwTest0005, AtHardwTest0006, AtHardwTest0007,
    AtHardwTest0008, AtHardwTest0009, AtHardwTest0010, AtHardwTest0011,
    AtHardwTest0012, AtHardwTest0013, AtHardwTest0014, AtHardwTest0015,
    AtHardwTest0016, AtHardwTest0017, AtHardwTest0018, AtHardwTest0019,
    AtHardwTest0020, AtHardwTest0021, AtHardwTest0022, AtHardwTest0023,
    AtHardwTest0024, AtHardwTest0025, AtHardwTest0026, AtHardwTest0027,
    AtHardwTest0028, AtHardwTest0029, AtHardwTest0030, AtHardwTest0031,
    AtHardwTest0032, AtHardwTest0033, AtHardwTest0034, AtHardwTest0035,
    AtHardwTest0036, AtHardwTest0037, AtHardwTest0038, AtHardwTest0039,
    AtHardwTest0040, AtHardwTest0041};

AT_TEST                 *AtTableTests[AT_TBLM_TEST_NUM] = {
    AtTableTest0000, AtTableTest0001, AtTableTest0002, AtTableTest0003,
    AtTableTest0004, AtTableTest0005, AtTableTest0006, AtTableTest0007,
    AtTableTest0008, AtTableTest0009, AtTableTest0010, AtTableTest0011,
    AtTableTest0012, AtTableTest0013, AtTableTest0014, AtTableTest0015,
    AtTableTest0016, AtTableTest0017, AtTableTest0018, AtTableTest0019,
    AtTableTest0020, AtTableTest0021, AtTableTest0022, AtTableTest0023,
    AtTableTest0024, AtTableTest0025, AtTableTest0026, AtTableTest0027,
    AtTableTest0028, AtTableTest0029, AtTableTest0030, AtTableTest0031,
    AtTableTest0032, AtTableTest0033, AtTableTest0034, AtTableTest0035,
    AtTableTest0036, AtTableTest0037, AtTableTest0038, AtTableTest0039,
    AtTableTest0040, AtTableTest0041, AtTableTest0042, AtTableTest0043,
    AtTableTest0044, AtTableTest0045, AtTableTest0046, AtTableTest0047,
    AtTableTest0048, AtTableTest0049, AtTableTest0050, AtTableTest0051,
    AtTableTest0052, AtTableTest0053, AtTableTest0054, AtTableTest0055,
    AtTableTest0056, AtTableTest0057, AtTableTest0058, AtTableTest0059,
    AtTableTest0060, AtTableTest0061};

AT_TEST                 *AtNSpaceTests[AT_NSPM_TEST_NUM] = {
    AtNSpaceTest0000, AtNSpaceTest0001, AtNSpaceTest0002, AtNSpaceTest0003,
    AtNSpaceTest0004, AtNSpaceTest0005, AtNSpaceTest0006, AtNSpaceTest0007,
    NULL,             NULL,             AtNSpaceTest0010, AtNSpaceTest0011,
    AtNSpaceTest0012, AtNSpaceTest0013, AtNSpaceTest0014, AtNSpaceTest0015,
    AtNSpaceTest0016, AtNSpaceTest0017, AtNSpaceTest0018, AtNSpaceTest0019,
    AtNSpaceTest0020, AtNSpaceTest0021, AtNSpaceTest0022, AtNSpaceTest0023,
    NULL,             AtNSpaceTest0025, AtNSpaceTest0026, AtNSpaceTest0027,
    NULL,             AtNSpaceTest0029, AtNSpaceTest0030, AtNSpaceTest0031,
    AtNSpaceTest0032, AtNSpaceTest0033, NULL,             AtNSpaceTest0035,
    AtNSpaceTest0036, AtNSpaceTest0037, NULL,             NULL,
    AtNSpaceTest0040, AtNSpaceTest0041, AtNSpaceTest0042, AtNSpaceTest0043,
    AtNSpaceTest0044, AtNSpaceTest0045, AtNSpaceTest0046, AtNSpaceTest0047,
    AtNSpaceTest0048, AtNSpaceTest0049, AtNSpaceTest0050, AtNSpaceTest0051,
    AtNSpaceTest0052, AtNSpaceTest0053, AtNSpaceTest0054, AtNSpaceTest0055,
    AtNSpaceTest0056, AtNSpaceTest0057, AtNSpaceTest0058, AtNSpaceTest0059,
    AtNSpaceTest0060, AtNSpaceTest0067, AtNSpaceTest0062, AtNSpaceTest0063,
    AtNSpaceTest0064, AtNSpaceTest0065, AtNSpaceTest0066, AtNSpaceTest0067,
    AtNSpaceTest0068, AtNSpaceTest0069, AtNSpaceTest0070, AtNSpaceTest0071,
    AtNSpaceTest0072, AtNSpaceTest0073, AtNSpaceTest0074, AtNSpaceTest0075,
    AtNSpaceTest0076, AtNSpaceTest0077, AtNSpaceTest0078, AtNSpaceTest0079,
    AtNSpaceTest0080, AtNSpaceTest0087, AtNSpaceTest0082, AtNSpaceTest0083,
    AtNSpaceTest0084, AtNSpaceTest0085, AtNSpaceTest0086, AtNSpaceTest0087,
    AtNSpaceTest0088, AtNSpaceTest0089, AtNSpaceTest0090, AtNSpaceTest0091,
    AtNSpaceTest0092, AtNSpaceTest0093, AtNSpaceTest0094, AtNSpaceTest0095,
    AtNSpaceTest0096, NULL,             AtNSpaceTest0098, AtNSpaceTest0099,
    AtNSpaceTest0100, AtNSpaceTest0107, NULL,             AtNSpaceTest0103,
    AtNSpaceTest0104, AtNSpaceTest0105, AtNSpaceTest0106, AtNSpaceTest0107,
    AtNSpaceTest0108, NULL,             AtNSpaceTest0110, AtNSpaceTest0111,
    AtNSpaceTest0112, AtNSpaceTest0113, AtNSpaceTest0114, AtNSpaceTest0115,
    AtNSpaceTest0116, AtNSpaceTest0117, AtNSpaceTest0118, AtNSpaceTest0119,
    AtNSpaceTest0120, AtNSpaceTest0121, AtNSpaceTest0122, AtNSpaceTest0123,
    AtNSpaceTest0124, AtNSpaceTest0125, AtNSpaceTest0126};

AT_TEST                 *AtResourceTests[AT_RSCM_TEST_NUM] = {
    AtRsrcTest0000, AtRsrcTest0001, AtRsrcTest0002, AtRsrcTest0003,
    AtRsrcTest0004, AtRsrcTest0005, AtRsrcTest0006, AtRsrcTest0007,
    AtRsrcTest0008, AtRsrcTest0009, AtRsrcTest0010, AtRsrcTest0011,
    AtRsrcTest0012, AtRsrcTest0013, AtRsrcTest0014, AtRsrcTest0015,
    AtRsrcTest0016, AtRsrcTest0017, AtRsrcTest0018, AtRsrcTest0019,
    AtRsrcTest0020, AtRsrcTest0021, AtRsrcTest0022, AtRsrcTest0023,
    AtRsrcTest0024, AtRsrcTest0025, AtRsrcTest0026, AtRsrcTest0027,
    AtRsrcTest0028, AtRsrcTest0029, AtRsrcTest0030, AtRsrcTest0031,
    AtRsrcTest0032, AtRsrcTest0033, AtRsrcTest0034, AtRsrcTest0035,
    AtRsrcTest0036, AtRsrcTest0037};

AT_TEST                 *AtFixedEvTests[AT_FEVM_TEST_NUM] = {
    AtFixEvTest0000, AtFixEvTest0001, AtFixEvTest0002, AtFixEvTest0003,
    AtFixEvTest0004, AtFixEvTest0005, AtFixEvTest0006, AtFixEvTest0007,
    AtFixEvTest0008, AtFixEvTest0009, AtFixEvTest0010, AtFixEvTest0011,
    AtFixEvTest0012, AtFixEvTest0013, AtFixEvTest0014, AtFixEvTest0015,
    AtFixEvTest0016, AtFixEvTest0017, AtFixEvTest0018, AtFixEvTest0019};

AT_TEST                 *AtGpeTests[AT_GPEM_TEST_NUM] = {
    AtGpeTest0000, AtGpeTest0001, AtGpeTest0002, AtGpeTest0003,
    AtGpeTest0004, AtGpeTest0005, AtGpeTest0006, AtGpeTest0007,
    AtGpeTest0008, AtGpeTest0009, AtGpeTest0010, AtGpeTest0011,
    AtGpeTest0012, AtGpeTest0013, AtGpeTest0014, AtGpeTest0015,
    AtGpeTest0016, AtGpeTest0017, AtGpeTest0018, AtGpeTest0019,
    AtGpeTest0020, AtGpeTest0021, AtGpeTest0022, AtGpeTest0023,
    AtGpeTest0024, AtGpeTest0025, AtGpeTest0026, AtGpeTest0027,
    AtGpeTest0028, AtGpeTest0029, AtGpeTest0030, AtGpeTest0031,
    AtGpeTest0032, AtGpeTest0033, AtGpeTest0034, AtGpeTest0035,
    AtGpeTest0036, AtGpeTest0037, AtGpeTest0038, AtGpeTest0039,
    AtGpeTest0040, AtGpeTest0041, AtGpeTest0042, AtGpeTest0043,
    AtGpeTest0044, AtGpeTest0045, AtGpeTest0046, AtGpeTest0047};

AT_TEST                 *AtHandlersTests[AT_HNDM_TEST_NUM] = {
    AtHndlrTest0000, AtHndlrTest0001, AtHndlrTest0002, AtHndlrTest0003,
    AtHndlrTest0004, AtHndlrTest0005, AtHndlrTest0006, AtHndlrTest0007,
    AtHndlrTest0008, AtHndlrTest0009, AtHndlrTest0010, AtHndlrTest0011,
    AtHndlrTest0012, AtHndlrTest0013, AtHndlrTest0014, AtHndlrTest0015,
    AtHndlrTest0016, AtHndlrTest0017, AtHndlrTest0018, AtHndlrTest0019,
    AtHndlrTest0020, AtHndlrTest0021, AtHndlrTest0022, AtHndlrTest0023,
    AtHndlrTest0024, AtHndlrTest0025, AtHndlrTest0026, AtHndlrTest0027,
    AtHndlrTest0028, AtHndlrTest0029, AtHndlrTest0030, AtHndlrTest0031,
    AtHndlrTest0032, AtHndlrTest0033, AtHndlrTest0034, AtHndlrTest0035,
    AtHndlrTest0036, AtHndlrTest0037, AtHndlrTest0038};

#define AT_TEST_CASE_NUM      9

AT_TEST_CASE_DESC       AtTestCase[AT_TEST_CASE_NUM + 1] = {
    {NULL},
    {AtInitTests,       AT_INIT_TEST_NUM, "Init"},
    {AtMemoryTests,     AT_MEMM_TEST_NUM, "Memory"},
    {AtHardwareTests,   AT_HDWM_TEST_NUM, "Hardw"},
    {AtTableTests,      AT_TBLM_TEST_NUM, "Table"},
    {AtNSpaceTests,     AT_NSPM_TEST_NUM, "NSpace"},
    {AtResourceTests,   AT_RSCM_TEST_NUM, "Rsrc"},
    {AtFixedEvTests,    AT_FEVM_TEST_NUM, "FixEv"},
    {AtGpeTests,        AT_GPEM_TEST_NUM, "Gpe"},
    {AtHandlersTests,   AT_HNDM_TEST_NUM, "Hndlr"},
};

static char             TestName[33];

#define DBG_OS_CTRL_PRINT       1
#define DBG_OS_REG_EMUL_PRINT   1
#define DBG_OUTPUT_SET          0

extern FILE             *AcpiGbl_OutputFile;

int
ExecuteTest (
    UINT32                  test_case,
    UINT32                  test_num)
{
    int                     status;


    AapiTestMode = AT_EMULATION_MODE;
    AapiErrors = 0;
    TestErrors = 0;
    TestSkipped = 0;
    TestPass = 0;
    AtAMLcodeFileName = NULL;
    AtAMLcodeFileDir = NULL;
    NullBldTask = ZeroBldTask;

    OsxfCtrlInit();

    if (!AtTestCase[test_case].Tests[test_num])
    {
        printf ("ACPICA API TS err: test num %ld of test case %ld"
            " is not implemented\n",
            test_num, test_case);
        return (AtRetNotImpl);
    }

    if (DBG_OUTPUT_SET)
    {
        AcpiGbl_OutputFile = stdout;
    }

    sprintf(TestName, "At%sTest%.4d",
        AtTestCase[test_case].BaseName, (int)test_num);

    printf ("%s:\n", TestName);

    AcpiGbl_EnableInterpreterSlack = TRUE;
    printf ("AML Interpreter slack mode enabled\n");

    AtTestCase[test_case].Tests[test_num]();

    /* Print Statistics of OSL iterfaces calls */
    if (DBG_OS_CTRL_PRINT)
    {
        OsxfCtrlPrint();
    }

    /* Print Statistics of Registers Emulation */
    if (DBG_OS_REG_EMUL_PRINT)
    {
        OsxfCtrlRegService(1);
    }

    AtRegionCleanup();

    printf ("ACPICA API TS status of %s: ", TestName);
    if (TestErrors && AapiErrors)
    {
        printf ("both FAIL and TEST FAULT,"
            " %d API errors, %d TEST errors\n",
            AapiErrors, TestErrors);
        status = AtRetApiErr;
    }
    else if (AapiErrors)
    {
        printf ("FAIL, %d API errors\n", AapiErrors);
        status = AtRetApiErr;
    }
    else if (TestErrors)
    {
        printf ("TEST FAULT, %d TEST errors\n", TestErrors);
        status = AtRetTestErr;
    }
    else if (TestPass && TestSkipped)
    {
        printf ("PASS, Pass/Skip counters %d/%d\n",
            TestPass, TestSkipped);
        status = AtRetPass;
    }
    else if (TestSkipped)
    {
        printf ("SKIP, counter %d\n", TestSkipped);
        status = AtRetSkip;
    }
    else
    {
        printf ("PASS\n");
        status = AtRetPass;
    }

    return (status);
}


int ACPI_SYSTEM_XFACE
main(
    int                     argc,
    char                    **argv)
{
    UINT32                  test_case;
    UINT32                  test_num;
    UINT32                  i;
    UINT32                  j;


    signal (SIGINT, AtSigHandler);
    signal (SIGILL, AtSigHandler);
    signal (SIGFPE, AtSigHandler);
//    signal (SIGSEGV, AtSigHandler);
#ifdef Linux
    signal (SIGALRM, AtSigHandler);
    (void) alarm(AT_ALARM_PERIOD);
#endif

    if (argc < 3)
    {
/*
        printf ("ACPICA API TS: <test case: 1 - 9 > <test number>"
            " should be specified\n");
        return (AtRetBadParam);
*/
        for (i = 7; i < 8 /*AT_TEST_CASE_NUM */; i++)
        {
            for (j = 0; j < 3 /* AtTestCase[i].TestsNum */; j++)
            {
                ExecuteTest (7, 0);
            }
        }
        return (0);
    }

    test_case = strtoul (argv[1], NULL, 0);
    if (test_case < 1 || test_case > AT_TEST_CASE_NUM)
    {
        printf ("ACPICA API TS err: test case %ld is out of range 1 - %d\n",
            test_case, AT_TEST_CASE_NUM);
        return (AtRetBadParam);
    }

    test_num = strtoul (argv[2], NULL, 0);
    if (test_num < 0 || test_num > AtTestCase[test_case].TestsNum)
    {
        printf ("ACPICA API TS err: test num %ld is out of range 0 - %d\n",
            test_num, AtTestCase[test_case].TestsNum);
        return (AtRetBadParam);
    }

    if (argc > 3)
    {
        AtAMLcodeFileDir = argv[3];
    }

    ExecuteTest (test_case, test_num);
    return (0);

}
