/*
 * __________________________________________________________________________
 *
 *
 *           Copyright (C) Intel Corporation 1994-1996
 *
 * All rights reserved.  No part of this program or publication may be
 * reproduced, transmitted, transcribed, stored in a retrieval system, or
 * translated into any language or computer language, in any form or by any
 * means, electronic, mechanical, magnetic, optical, chemical, manual, or
 * otherwise, without the prior written permission of Intel Corporation.
 *__________________________________________________________________________
 *
 * FILENAME: datatypes.h
 *__________________________________________________________________________
 *
 *
 *__________________________________________________________________________
 */

#ifndef _DATATYPES_H
#define _DATATYPES_H


/* 
 * Data types - Fixed across all compilation models
 * 
 * BOOLEAN	    Logical Boolean. 1 byte value containing a 0 for FALSE or a 1 for TRUE.  Other values are undefined.
 * INT	        Signed value. (4 bytes on IA-32, 8 bytes on IA-64)
 * UINT	        Unsigned value. (4 bytes on IA-32, 8 bytes on IA-64)
 * INT8	        1 byte signed value
 * UINT8	    1 byte unsigned value
 * INT16	    2 byte signed value
 * UINT16	    2 byte unsigned value
 * INT32	    4 byte signed value
 * UINT32	    4 byte unsigned value
 * UINT64	    8 byte unsigned value.
 * UCHAR	    Character. 1 byte unsigned value. 
 * WCHAR	    Wide Character. 2 byte unsigned value. 
 * VOID	        Undeclared type
 */

/* 
 * Need a 32-bit vs. 64-bit section !!! 
 */

/*  IA-32 type definitions */

typedef unsigned char   BOOLEAN;
typedef int             INT;
typedef unsigned int    UINT;
typedef char            INT8;
typedef unsigned char   UINT8;
typedef short           INT16;
typedef unsigned short  UINT16;
typedef int             INT32;
typedef unsigned int    UINT32;
typedef unsigned char   UCHAR;

typedef unsigned char   UINT8_BIT;
typedef unsigned short  UINT16_BIT;
typedef unsigned long   UINT32_BIT;

#ifndef NOVOID
typedef void            VOID;
#endif

/* Not supported */

#define UINT64 
/*
 * This is needed somewhere!!!
 * #define WCHAR
 */


/* The 64-bit data type in IA-32 */

#ifndef  _QWORD_DEFINED
typedef struct
{
    UINT32 Low;
    UINT32 High;
}  QWORD;
#endif


/* Miscellaneous data manipulation macros */

#ifndef LOWORD
#define LOWORD(l)   ((UINT16)(UINT32)(l))
#endif

#ifndef HIWORD
#define HIWORD(l)   ((UINT16)((((UINT32)(l)) >> 16) & 0xFFFF))
#endif

#ifndef LOBYTE
#define LOBYTE(l)   ((UINT8)(UINT16)(l))
#endif

#ifndef HIBYTE
#define HIBYTE(l)   ((UINT8)((((UINT16)(l)) >> 8) & 0xFF))
#endif

#define BIT0(x) 	((((x) & 0x1) > 0) ? 1 : 0)
#define BIT1(x)    	((((x) & 0x2) > 0) ? 1 : 0)
#define BIT2(x)   	((((x) & 0x4) > 0) ? 1 : 0)
#define BIT3(x)   	((((x) & 0x8) > 0) ? 1 : 0)
#define BIT4(x)   	((((x) & 0x10) > 0) ? 1 : 0)
#define BIT5(x)    	((((x) & 0x20) > 0) ? 1 : 0)
#define BIT6(x)  	((((x) & 0x40) > 0) ? 1 : 0)
#define BIT7(x)    	((((x) & 0x80) > 0) ? 1 : 0)

#ifndef VERBOSE
#define VERBOSE 0xFF
#endif


#define LOW_BASE(w)     ((UINT16) ((w) & 0x0000FFFF))
#define MID_BASE(b)     ((UINT8)(((b) & 0x00FF0000) >> 16))
#define HI_BASE(b)      ((UINT8)(((b) & 0xFF000000) >> 24))
#define LOW_LIMIT(w)  	((UINT16) ((w) & 0x0000FFFF))
#define HI_LIMIT(b)     ((UINT8)(((b) & 0x00FF0000) >> 16))

#endif /* DATATYPES_H */