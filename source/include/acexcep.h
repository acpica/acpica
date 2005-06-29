/*
  __________________________________________________________________________
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
 | FILENAME: excep.h - local exception codes
 |__________________________________________________________________________
*/



#ifndef _EXCEP_H
#define _EXCEP_H


/* Error codes  */

#ifndef EXIT_SUCCESS                                  /* also defined in stdlib.h as 0 */
#define EXIT_SUCCESS        0
#endif

#ifndef E_OK
#define E_OK                0
#endif

#ifndef NO_ERROR
#define NO_ERROR            0
#endif

#ifndef E_ERROR
#define E_ERROR             1
#endif

#ifdef E_IRQ_ERROR
#undef E_IRQ_ERROR
#endif
#define E_IRQ_ERROR         -1 /* MUST be negative */

#ifndef E_FILE_NOT_EXIST
#define E_FILE_NOT_EXIST    1
#endif

#ifndef E_ARGUMENT
#define E_ARGUMENT          2
#endif

#ifndef E_MEMORY
#define E_MEMORY            3
#endif

/* returned from parse_command_line() */

#ifndef E_HELP_MESSAGE
#define E_HELP_MESSAGE      4
#endif

#ifndef E_NO_ACPI_TBLS
#define E_NO_ACPI_TBLS      5
#endif

/* returned from parse_command_line() */

#ifndef E_NON_STANDARD_ARGUMENT
#define E_NON_STANDARD_ARGUMENT 0xff
#endif




#endif
