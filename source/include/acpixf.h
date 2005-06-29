/*__________________________________________________________________________
 |
 |
 |           Copyright (C) Intel Corporation 1994-1996
 |
 | All rights reserved.  No part of this program or publication may be
 | reproduced, transmitted, transcribed, stored in a retrieval system, or
 | translated into any language or computer language, in any form or by any
 | means, electronic, mechanical, magnetic, optical, chemical, manual, or
 | otherwise, without the prior written permission of Intel Corporation.
 |__________________________________________________________________________
 |
 | FILENAME: acpisubsys.h - external interfaces to the ACPI subsystem
 |__________________________________________________________________________
*/

#include <datatypes.h>
#include <acpiobj.h>

#define ACPI_MODE               1
#define LEGACY_MODE             2
#define DISABLE_KNOWN_EVENTS    8


INT32 
AcpiInit (
    char                *AcpiFile);

INT32
AcpiLoadNameSpace (
    INT32               DisplayAmlDuringLoad);

INT32
AcpiExecuteMethod (
    char                *MethodName, 
    OBJECT_DESCRIPTOR   **ReturnValue,
    OBJECT_DESCRIPTOR   **Params);

INT32
AcpiSetMode (
    INT32               Mode);

INT32
AcpiModeStatus (
    void);

INT32
AcpiModeCapabilities (
    void);

INT32
AcpiEnable (
    char                *TestName, 
    INT32               Flags);

INT32 
AcpiDisable (
    void);
