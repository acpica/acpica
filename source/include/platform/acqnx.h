/******************************************************************************
 *
 * Name: acqnx.h - OS specific defines, etc.
 *
 *****************************************************************************/

#ifndef __ACQNX_H__
#define __ACQNX_H__

/* QNX uses GCC */

#include "acgcc.h"

#define ACPI_UINTPTR_T          uintptr_t
#define ACPI_USE_LOCAL_CACHE
#define ACPI_CAST_PTHREAD_T(x)  ((ACPI_THREAD_ID) ACPI_TO_INTEGER (x))

/* At present time (QNX 6.6) all supported architectures are 32 bits. */
#define ACPI_MACHINE_WIDTH      32

#define COMPILER_DEPENDENT_INT64  int64_t
#define COMPILER_DEPENDENT_UINT64 uint64_t

#include <ctype.h>
#include <stdint.h>
#include <sys/neutrino.h>

#define ACPI_USE_STANDARD_HEADERS

#define __cli() InterruptDisable();
#define __sti() InterruptEnable();
#define __cdecl

#define ACPI_USE_SYSTEM_CLIBRARY
#define ACPI_USE_NATIVE_DIVIDE

#endif /* __ACQNX_H__ */
