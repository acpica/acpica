/******************************************************************************
 *
 * Module Name: atfixedevents - ACPICA Fixed Event Management API tests
 *
 *****************************************************************************/

#include "atcommon.h"
#include "atfixedevent.h"
#include "atosxfctrl.h"

#define _COMPONENT          ACPI_TOOLS
        ACPI_MODULE_NAME    ("atfixedevent")

ACPI_STATUS
AtFixedEventsCommon(
    UINT32                  ApiCall,
    UINT32                  CheckAction,
    ACPI_STATUS             ExpectedStatus)
{
    ACPI_STATUS             Status;
    UINT32                  Event, Flags = 0;
    UINT32                  i;
    char                    *ApiCallName;
    ACPI_EVENT_STATUS       EventStatus, *EventStatusPointer = &EventStatus;

    Status = AtSubsystemInit(
        AAPITS_INI_DEF,
        AAPITS_EN_FLAGS, AAPITS_OI_FLAGS, NULL);
    if (ACPI_FAILURE(Status))
    {
        return (Status);
    }

    for (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++)
    {
        switch (i)
        {
        case 0:
            Event = ACPI_EVENT_PMTIMER;
            break;
        case 1:
            Event = ACPI_EVENT_GLOBAL;
            break;
        case 2:
            Event = ACPI_EVENT_POWER_BUTTON;
            break;
        case 3:
            Event = ACPI_EVENT_SLEEP_BUTTON;
            break;
        case 4:
            Event = ACPI_EVENT_RTC;
            break;
        default:
            TestErrors++;
            printf ("Test Error: the number of Fixed Events (%d) too big (should be 5)\n",
                ACPI_NUM_FIXED_EVENTS);
            return (AE_ERROR);
        }
        if (CheckAction == 1)
        {
            Event += ACPI_NUM_FIXED_EVENTS;
        }
        else if (CheckAction == 2)
        {
            EventStatusPointer = NULL;
        }

        switch (ApiCall)
        {
        case 0:
            ApiCallName = "AcpiEnableEvent";
            Status = AcpiEnableEvent(Event, Flags);
            break;
        case 1:
            ApiCallName = "AcpiDisableEvent";
            Status = AcpiDisableEvent(Event, Flags);
            break;
        case 2:
            ApiCallName = "AcpiClearEvent";
            Status = AcpiClearEvent(Event);
            break;
        case 3:
            ApiCallName = "AcpiGetEventStatus";
            Status = AcpiGetEventStatus(Event, EventStatusPointer);
            break;
        default:
            TestErrors++;
            printf ("Test Error: the ApiCall number (%d) should be in range 0-3\n",
                ApiCall);
            return (AE_ERROR);
        }

        if (Status != ExpectedStatus)
        {
            AapiErrors++;
            printf ("Api Error: %s(%d) returned %s, expected %s\n",
                ApiCallName, Event, AcpiFormatException(Status),
                AcpiFormatException(ExpectedStatus));
            if (Status != AE_OK)
            {
                return (Status);
            }
            else
            {
                return (AE_ERROR);
            }
        }
    }

    return (AtTerminateCtrlCheck(AE_OK, ALL_STAT));
}

/*
 * ASSERTION 0000:
 */
ACPI_STATUS
AtFixEvTest0000(void)
{
    return (AtFixedEventsCommon(0 /* Enable */, 0, AE_OK));
}

/*
 * ASSERTION 0001:
 */
ACPI_STATUS
AtFixEvTest0001(void)
{
    return (AtFixedEventsCommon(0 /* Enable */, 1, AE_BAD_PARAMETER));
}

/*
 * ASSERTION 0002:
 */
ACPI_STATUS
AtFixEvTest0002(void)
{
    return (AtFixedEventsCommon(1 /* Disable */, 0, AE_OK));
}

/*
 * ASSERTION 0003:
 */
ACPI_STATUS
AtFixEvTest0003(void)
{
    return (AtFixedEventsCommon(1 /* Disable */, 1, AE_BAD_PARAMETER));
}

/*
 * ASSERTION 0004:
 */
ACPI_STATUS
AtFixEvTest0004(void)
{
    return (AtFixedEventsCommon(2 /* Clear */, 0, AE_OK));
}

/*
 * ASSERTION 0005:
 */
ACPI_STATUS
AtFixEvTest0005(void)
{
    return (AtFixedEventsCommon(2 /* Clear */, 1, AE_BAD_PARAMETER));
}

/*
 * ASSERTION 0006:
 */
ACPI_STATUS
AtFixEvTest0006(void)
{
    return (AtFixedEventsCommon(3 /* Status */, 0, AE_OK));
}

/*
 * ASSERTION 0007:
 */
ACPI_STATUS
AtFixEvTest0007(void)
{
    return (AtFixedEventsCommon(3 /* Status */, 1, AE_BAD_PARAMETER));
}

/*
 * ASSERTION 0008:
 */
ACPI_STATUS
AtFixEvTest0008(void)
{
    return (AtFixedEventsCommon(3 /* Status */, 2, AE_BAD_PARAMETER));
}

static UINT32           FixedEventHandlerCounter;
static UINT32           FixedEventHandlerContext[ACPI_NUM_FIXED_EVENTS];

UINT32
AtFixedEventHandler0 (
    void                    *Context)
{
    UINT32                  HandlerId = 0;

    printf ("AtFixedEventHandler%d: Context %p\n", HandlerId, Context);
    ++FixedEventHandlerCounter;

    if ((UINT32 *)Context - FixedEventHandlerContext > ACPI_NUM_FIXED_EVENTS) {
        AapiErrors++;
        printf ("AtFixedEventHandler: Context (0x%p) is out of"
            " FixedEventHandlerContext (0x%p: %d)\n",
            Context, FixedEventHandlerContext, ACPI_NUM_FIXED_EVENTS);
    }

    return (0);
}

UINT32
AtFixedEventHandler1 (
    void                    *Context)
{
    UINT32                  HandlerId = 1;

    printf ("AtFixedEventHandler%d: Context %p\n", HandlerId, Context);
    ++FixedEventHandlerCounter;

    if ((UINT32 *)Context - FixedEventHandlerContext > ACPI_NUM_FIXED_EVENTS) {
        AapiErrors++;
        printf ("AtFixedEventHandler: Context (0x%p) is out of"
            " FixedEventHandlerContext (0x%p: %d)\n",
            Context, FixedEventHandlerContext, ACPI_NUM_FIXED_EVENTS);
    }

    return (0);
}

UINT32
AtFixedEventHandler2 (
    void                    *Context)
{
    UINT32                  HandlerId = 2;

    printf ("AtFixedEventHandler%d: Context %p\n", HandlerId, Context);
    ++FixedEventHandlerCounter;

    if ((UINT32 *)Context - FixedEventHandlerContext > ACPI_NUM_FIXED_EVENTS) {
        AapiErrors++;
        printf ("AtFixedEventHandler: Context (0x%p) is out of"
            " FixedEventHandlerContext (0x%p: %d)\n",
            Context, FixedEventHandlerContext, ACPI_NUM_FIXED_EVENTS);
    }

    return (0);
}

static ACPI_EVENT_HANDLER   FixedEventHandlers[ACPI_NUM_FIXED_EVENTS] = {
    AtFixedEventHandler0, AtFixedEventHandler0,
    AtFixedEventHandler1, AtFixedEventHandler1,
    AtFixedEventHandler2};

ACPI_STATUS
AtInstallFixedEventHandlerCommon(
    UINT32                  CheckAction,
    ACPI_STATUS             ExpectedStatus)
{
    ACPI_STATUS             Status;
    UINT32                  Event = ACPI_NUM_FIXED_EVENTS;
    ACPI_EVENT_HANDLER      EventHandler;
    ACPI_OSXF               OsxfNumAct;
    UINT32                  i;

    Status = AtSubsystemInit(
        AAPITS_INI_DEF & ~AAPITS_INSTALL_HS,
        AAPITS_EN_FLAGS | ACPI_NO_HANDLER_INIT, AAPITS_OI_FLAGS, NULL);
    if (ACPI_FAILURE(Status))
    {
        return (Status);
    }

    if (CheckAction == 4)
    {
        if (ExpectedStatus != AE_ALREADY_EXISTS)
        {
            TestErrors++;
            printf ("Test Error: ExpectedStatus %s != AE_ALREADY_EXISTS\n",
                AcpiFormatException(ExpectedStatus));
            return (AE_ERROR);
        }
        ExpectedStatus = AE_OK;
    }

    FixedEventHandlerCounter = 0;
    for (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++)
    {
        switch (i)
        {
        case 0:
            Event = ACPI_EVENT_PMTIMER;
            break;
        case 1:
            Event = ACPI_EVENT_GLOBAL;
            break;
        case 2:
            Event = ACPI_EVENT_POWER_BUTTON;
            break;
        case 3:
            Event = ACPI_EVENT_SLEEP_BUTTON;
            break;
        case 4:
            Event = ACPI_EVENT_RTC;
            break;
        default:
            TestErrors++;
            printf ("Test Error: the number of Fixed Events (%d) too big (should be 5)\n",
                ACPI_NUM_FIXED_EVENTS);
            return (AE_ERROR);
        }
        EventHandler = FixedEventHandlers[i];

        if (CheckAction == 1)
        {
            Event += ACPI_NUM_FIXED_EVENTS;
        }
        else if (CheckAction == 2)
        {
            EventHandler = NULL;
        }
        else if (CheckAction == 3)
        {
            /*
             * initiate the situation when fixed event
             * enable register can not be written
             */
            Status = OsxfCtrlSet(OSXF_NUM(AcpiOsWritePort), 1,
                AtActD_OneTime, AtActRet_ERROR);
            if (ACPI_FAILURE(Status))
            {
                TestErrors++;
                printf ("Test error: OsxfCtrlSet returned %s\n",
                    AcpiFormatException(Status));
                return (Status);
            }
        }

        FixedEventHandlerContext[i] = 0;

        Status = AcpiInstallFixedEventHandler(Event,
            EventHandler, &FixedEventHandlerContext[i]);

        if (CheckAction == 3 &&
            !(OsxfNumAct = OsxfCtrlGetActOsxf(OSXF_NUM(AcpiOsWritePort), 1)))
        {
            TestSkipped++;
            printf ("Test note: test action hasn't occur\n");
            return (AE_ERROR);
        }
        TestPass++;

        if (Status != ExpectedStatus)
        {
            AapiErrors++;
            printf ("Api Error: AcpiInstallFixedEventHandler(%d, 0x%p)"
                " returned %s, expected %s\n",
                Event, EventHandler, AcpiFormatException(Status),
                AcpiFormatException(ExpectedStatus));
            if (Status != AE_OK)
            {
                return (Status);
            }
            else
            {
                return (AE_ERROR);
            }
        }
    }

    if (CheckAction == 4)
    {
        for (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++)
        {
            switch (i)
            {
            case 0:
                Event = ACPI_EVENT_PMTIMER;
                break;
            case 1:
                Event = ACPI_EVENT_GLOBAL;
                break;
            case 2:
                Event = ACPI_EVENT_POWER_BUTTON;
                break;
            case 3:
                Event = ACPI_EVENT_SLEEP_BUTTON;
                break;
            case 4:
                Event = ACPI_EVENT_RTC;
                break;
            }
            EventHandler = FixedEventHandlers[(i + 1) % ACPI_NUM_FIXED_EVENTS];

            Status = AcpiInstallFixedEventHandler(Event,
                EventHandler, &FixedEventHandlerContext[i]);
            if (Status != AE_ALREADY_EXISTS)
            {
                AapiErrors++;
                printf ("Error: AcpiInstallFixedEventHandler(%d, 0x%p) returned %s,"
                    " expected %s\n",
                    Event, EventHandler, AcpiFormatException(Status),
                    AcpiFormatException(AE_ALREADY_EXISTS));
                return (AE_ERROR);
            }
        }
    }

    if (FixedEventHandlerCounter != 0)
    {
        AapiErrors++;
        printf ("Api Error: FixedEvent Handler invoked %d times\n",
            FixedEventHandlerCounter);
        return (AE_ERROR);
    }

    return (AtTerminateCtrlCheck(AE_OK, ALL_STAT));
}

/*
 * ASSERTION 0009:
 *
 */
ACPI_STATUS
AtFixEvTest0009(void)
{
    return (AtInstallFixedEventHandlerCommon(0, AE_OK));
}

/*
 * ASSERTION 0010:
 *
 */
ACPI_STATUS
AtFixEvTest0010(void)
{
    return (AtInstallFixedEventHandlerCommon(1, AE_BAD_PARAMETER));
}

/*
 * ASSERTION 0011:
 *
 */
ACPI_STATUS
AtFixEvTest0011(void)
{
    return (AtInstallFixedEventHandlerCommon(2, AE_BAD_PARAMETER));
}

/*
 * ASSERTION 0012:
 *
 */
ACPI_STATUS
AtFixEvTest0012(void)
{
    return (AtInstallFixedEventHandlerCommon(3, AE_ERROR));
}

/*
 * ASSERTION 0013:
 *
 */
ACPI_STATUS
AtFixEvTest0013(void)
{
    return (AtInstallFixedEventHandlerCommon(4, AE_ALREADY_EXISTS));
}

ACPI_STATUS
AtRemoveFixedEventHandlerCommon(
    UINT32                  CheckAction,
    ACPI_STATUS             ExpectedStatus)
{
    ACPI_STATUS             Status;
    UINT32                  Event = ACPI_NUM_FIXED_EVENTS;
    ACPI_EVENT_HANDLER      EventHandler;
    ACPI_OSXF               OsxfNumAct;
    UINT32                  i;

    Status = AtSubsystemInit(
        AAPITS_INI_DEF & ~AAPITS_INSTALL_HS,
        AAPITS_EN_FLAGS | ACPI_NO_HANDLER_INIT, AAPITS_OI_FLAGS, NULL);
    if (ACPI_FAILURE(Status))
    {
        return (Status);
    }

    FixedEventHandlerCounter = 0;
    for (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++)
    {
        if (CheckAction == 5)
        {
            continue;
        }
        switch (i)
        {
        case 0:
            Event = ACPI_EVENT_PMTIMER;
            break;
        case 1:
            Event = ACPI_EVENT_GLOBAL;
            break;
        case 2:
            Event = ACPI_EVENT_POWER_BUTTON;
            break;
        case 3:
            Event = ACPI_EVENT_SLEEP_BUTTON;
            break;
        case 4:
            Event = ACPI_EVENT_RTC;
            break;
        default:
            TestErrors++;
            printf ("Test Error: the number of Fixed Events (%d) too big (should be 5)\n",
                ACPI_NUM_FIXED_EVENTS);
            return (AE_ERROR);
        }
        EventHandler = FixedEventHandlers[i];

        FixedEventHandlerContext[i] = 0;

        Status = AcpiInstallFixedEventHandler(Event,
            EventHandler, &FixedEventHandlerContext[i]);
        if (ACPI_FAILURE(Status))
        {
            AapiErrors++;
            printf ("Api Error: AcpiInstallFixedEventHandler(%d) returned %s\n",
                Event, AcpiFormatException(Status));
            return (Status);
        }
    }

    for (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++)
    {
        switch (i)
        {
        case 0:
            Event = ACPI_EVENT_PMTIMER;
            break;
        case 1:
            Event = ACPI_EVENT_GLOBAL;
            break;
        case 2:
            Event = ACPI_EVENT_POWER_BUTTON;
            break;
        case 3:
            Event = ACPI_EVENT_SLEEP_BUTTON;
            break;
        case 4:
            Event = ACPI_EVENT_RTC;
            break;
        }
        EventHandler = FixedEventHandlers[i];

        if (CheckAction == 1)
        {
            Event += ACPI_NUM_FIXED_EVENTS;
        }
        else if (CheckAction == 2)
        {
            EventHandler = NULL;
        }
        else if (CheckAction == 3)
        {
            /*
             * initiate the situation when fixed event
             * enable register can not be written
             */
            Status = OsxfCtrlSet(OSXF_NUM(AcpiOsWritePort), 1,
                AtActD_OneTime, AtActRet_ERROR);
            if (ACPI_FAILURE(Status))
            {
                TestErrors++;
                printf ("Test error: OsxfCtrlSet returned %s\n",
                    AcpiFormatException(Status));
                return (Status);
            }
        }
        else if (CheckAction == 4)
        {
            EventHandler = FixedEventHandlers[(i + 2) % ACPI_NUM_FIXED_EVENTS];
        }

        Status = AcpiRemoveFixedEventHandler(Event, EventHandler);

        if (CheckAction == 3 &&
            !(OsxfNumAct = OsxfCtrlGetActOsxf(OSXF_NUM(AcpiOsWritePort), 1)))
        {
            TestSkipped++;
            printf ("Test note: test action hasn't occur\n");
            return (AE_ERROR);
        }
        TestPass++;

        if (Status != ExpectedStatus)
        {
            AapiErrors++;
            printf ("Api Error: AcpiRemoveFixedEventHandler(%d, 0x%p)"
                " returned %s, expected %s\n",
                Event, EventHandler, AcpiFormatException(Status),
                AcpiFormatException(ExpectedStatus));
            if (Status != AE_OK)
            {
                return (Status);
            }
            else
            {
                return (AE_ERROR);
            }
        }
    }

    if (FixedEventHandlerCounter != 0)
    {
        AapiErrors++;
        printf ("Api Error: FixedEvent Handler invoked %d times\n",
            FixedEventHandlerCounter);
        return (AE_ERROR);
    }

    return (AtTerminateCtrlCheck(AE_OK, ALL_STAT));
}

/*
 * ASSERTION 0014:
 *
 */
ACPI_STATUS
AtFixEvTest0014(void)
{
    return (AtRemoveFixedEventHandlerCommon(0, AE_OK));
}

/*
 * ASSERTION 0015:
 *
 */
ACPI_STATUS
AtFixEvTest0015(void)
{
    return (AtRemoveFixedEventHandlerCommon(1, AE_BAD_PARAMETER));
}

/*
 * ASSERTION 0016:
 *
 */
ACPI_STATUS
AtFixEvTest0016(void)
{
    return (AtRemoveFixedEventHandlerCommon(2, AE_BAD_PARAMETER));
}

/*
 * ASSERTION 0017:
 *
 */
ACPI_STATUS
AtFixEvTest0017(void)
{
    return (AtRemoveFixedEventHandlerCommon(3, AE_ERROR));
}

/*
 * ASSERTION 0018:
 *
 */
ACPI_STATUS
AtFixEvTest0018(void)
{
    return (AtRemoveFixedEventHandlerCommon(4, AE_BAD_PARAMETER));
}

/*
 * ASSERTION 0019:
 *
 */
ACPI_STATUS
AtFixEvTest0019(void)
{
    return (AtRemoveFixedEventHandlerCommon(5, AE_NOT_EXIST));
}
