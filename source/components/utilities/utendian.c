/******************************************************************************
 *
 * Module Name: utendian -- byte swapping support for other-endianness
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * Copyright (c) 2020, Al Stone <ahs3@redhat.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification.
 * 2. Redistributions in binary form must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement for further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Alternatively, you may choose to be licensed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 *****************************************************************************/

#include "acpi.h"
#include "accommon.h"

#define _COMPONENT          ACPI_COMPILER
        ACPI_MODULE_NAME    ("utendian")

/*
 * Endianness support functions.
 *
 * Ultimately, everything in ACPI tables or AML must be in little-endian
 * format.  However, we sometimes find it necessary to run on a big-endian
 * machine and create or read those little-endian values.  This is a small
 * libary of functions to make that easier, and more visible.
 *
 */

/*******************************************************************************
 *
 * FUNCTION:    UtIsBigEndianMachine
 *
 * PARAMETERS:  None
 *
 * RETURN:      TRUE if machine is big endian
 *              FALSE if machine is little endian
 *
 * DESCRIPTION: Detect whether machine is little endian or big endian.
 *
 ******************************************************************************/

UINT8
UtIsBigEndianMachine (
    void)
{
    union {
        UINT32              Integer;
        UINT8               Bytes[4];
    } Overlay =                 {0xFF000000};


    return (Overlay.Bytes[0]); /* Returns 0xFF (TRUE) for big endian */
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiUtReadUint16
 *
 * PARAMETERS:  Src         - location containing the little-endian
 *                                    value
 *
 * RETURN:      UINT16 value in host-native form
 *
 * DESCRIPTION: Read a UINT16 little-endian value from a given location
 *              and return it in host-native form
 *
 ******************************************************************************/

UINT16
AcpiUtReadUint16 (
    void                    *SrcPtr)
{
    UINT16                  Result = 0;
    UINT8                   *Dst = (UINT8 *) &Result;
    UINT8                   *Src = (UINT8 *) SrcPtr;

    if (!UtIsBigEndianMachine())
    {
        return (*(UINT16 *) SrcPtr);
    }

    Dst[0] = Src[1];
    Dst[1] = Src[0];

    return (Result);
}

/*******************************************************************************
 *
 * FUNCTION:    AcpiUtReadUint32
 *
 * PARAMETERS:  Src         - location containing the little-endian
 *                                    value
 *
 * RETURN:      UINT32 value in host-native form
 *
 * DESCRIPTION: Read a UINT32 little-endian value from a given location
 *              and return it in host-native form
 *
 ******************************************************************************/

UINT32
AcpiUtReadUint32 (
    void                    *SrcPtr)
{
    UINT32                  Result = 0;
    UINT8                   *Dst = (UINT8 *) &Result;
    UINT8                   *Src = (UINT8 *) SrcPtr;

    if (!UtIsBigEndianMachine())
    {
        return (*(UINT32 *) SrcPtr);
    }

    Dst[0] = Src[3];
    Dst[1] = Src[2];
    Dst[2] = Src[1];
    Dst[3] = Src[0];

    return (Result);
}

/*******************************************************************************
 *
 * FUNCTION:    AcpiUtReadUint64
 *
 * PARAMETERS:  Src         - location containing the little-endian
 *                                    value
 *
 * RETURN:      UINT64 value in host-native form
 *
 * DESCRIPTION: Read a UINT64 little-endian value from a given location
 *              and return it in host-native form
 *
 ******************************************************************************/

UINT64
AcpiUtReadUint64 (
    void                    *SrcPtr)
{
    UINT64                  Result = 0;
    UINT8                   *Dst = (UINT8 *) &Result;
    UINT8                   *Src = (UINT8 *) SrcPtr;

    if (!UtIsBigEndianMachine())
    {
        return (*(UINT64 *) SrcPtr);
    }

    Dst[0] = Src[7];
    Dst[1] = Src[6];
    Dst[2] = Src[5];
    Dst[3] = Src[4];
    Dst[4] = Src[3];
    Dst[5] = Src[2];
    Dst[6] = Src[1];
    Dst[7] = Src[0];

    return (Result);
}

/*******************************************************************************
 *
 * FUNCTION:    AcpiUtWriteUint
 *
 * PARAMETERS:  DstPtr      - where to place the retrieved value
 *              DstLength   - space in bytes for this int type
 *              SrcPtr      - where the little-endian value lives
 *              SrcLength   - space in bytes for this int type
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Write a host-native integer value of the given size, and
 *              store it in the location specified in little-endian form.
 *              Given the amount of integer type casting done, this general
 *              version seems the most useful (vs 32->32, 32->16, 16->32,
 *              ad infinitum)
 *
 ******************************************************************************/

void
AcpiUtWriteUint (
    void                    *DstPtr,
    int                     DstLength,
    const void              *SrcPtr,
    const int               SrcLength)
{
    UINT8                   *Dst = (UINT8 *) DstPtr;
    UINT8                   *Src = (UINT8 *) SrcPtr;
    int                      Length;
    int                      ii;

    if (!UtIsBigEndianMachine())
    {
        Length = SrcLength > DstLength ? DstLength : SrcLength;
        memcpy (Dst, Src, Length);
	return;
    }

    Length = SrcLength >= DstLength ? DstLength : SrcLength;
    for (ii = 0; ii < Length; ii++)
        Dst[ii] = Src[SrcLength - ii - 1];

}
