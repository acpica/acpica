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

#ifdef FLAT_MODEL

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
 * Get rid of FLAT_MODEL !!!
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
typedef void            VOID;

/* Not supported */

#define UINT64 
#define WCHAR


    /* We want to obsolete these !!!!*/

    #define BYTE    	unsigned char
    #define WORD    	unsigned short
    #define DWORD   	unsigned long
    /* #define BOOLEAN 	unsigned char */
    #define BYTE_BIT   	BYTE
    #define NATIVE_WORD	WORD

/* We want to obsolete everything that is NOT flat model */

#else                                             	/* ! RMX   */
    #pragma pack(1)
    #include <graph.h>

    #define BYTE    	unsigned char
    #define WORD    	unsigned short
    #define DWORD   	unsigned long
    #define BOOLEAN 	unsigned char
    #define BYTE_BIT  	BYTE
    #define NATIVE_WORD WORD

    #ifdef BULIB_GEN
        #include "switch.h"
    #else
        #include <switch.h>
    #endif
#endif                                                /* ! RMX   */

#define WORD_BIT    unsigned

#ifndef  _QWORD_DEFINED
typedef struct
{
    DWORD Low;
    DWORD High;
}  QWORD;
#endif

#ifndef LOWORD
#define LOWORD(l)   ((WORD)(DWORD)(l))
#endif

#ifndef HIWORD
#define HIWORD(l)   ((WORD)((((DWORD)(l)) >> 16) & 0xFFFF))
#endif

#ifndef LOBYTE
#define LOBYTE(l)   ((BYTE)(WORD)(l))
#endif

#ifndef HIBYTE
#define HIBYTE(l)   ((BYTE)((((WORD)(l)) >> 8) & 0xFF))
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


#ifndef RMX
  #ifndef FLAT_MODEL
    #define selector                        __segment
  #else
    #define selector                        DWORD
    #define FAR
    extern selector sFlatSeg;
  #endif

  #ifndef GDT_SLOTS
    #define GDT_SLOTS 10
  #endif
#else       /* RMX */
  #define MAX_PRIORITY    (unsigned char) 0X37
  #define THIS_JOB     	NULLSEL
  #define s4GBSegName     (const char *) "4GB selector"
  #ifndef __BU_BASE_C__
    extern selector sF000;
    extern selector sFlatSeg;
    #define s4GBSeg sFlatSeg
  #endif
#endif  /* RMX */

#define LOW_BASE(w)     ((WORD) ((w) & 0x0000FFFF))
#define MID_BASE(b)     ((BYTE)(((b) & 0x00FF0000) >> 16))
#define HI_BASE(b)      ((BYTE)(((b) & 0xFF000000) >> 24))
#define LOW_LIMIT(w)  	((WORD) ((w) & 0x0000FFFF))
#define HI_LIMIT(b)     ((BYTE)(((b) & 0x00FF0000) >> 16))

#endif /* DATATYPES_H */