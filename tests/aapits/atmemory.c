/******************************************************************************
 *
 * Module Name: atmemory - ACPICA Memory Management API tests
 *
 *****************************************************************************/

#include "atcommon.h"
#include "atmemory.h"
#include "atosxfctrl.h"

#define _COMPONENT          ACPI_TOOLS
        ACPI_MODULE_NAME    ("atmemory")

/*
 * ASSERTION 0000:
 */
ACPI_STATUS
AtMemoryTest0000(void)
{
    ACPI_STATUS             Status;

    Status = AtSubsystemInit(
        AAPITS_INI_DEF,
        AAPITS_EN_FLAGS, AAPITS_OI_FLAGS, NULL);
    if (ACPI_FAILURE(Status))
    {
        return (Status);
    }

    TestSkipped++;

    return (AtTerminateCtrlCheck(AE_OK, ALL_STAT));
}
