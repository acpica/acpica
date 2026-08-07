/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20260408 (64-bit version)
 * Copyright (c) 2000 - 2026 Intel Corporation
 * 
 * Disassembling to non-symbolic legacy ASL operators
 *
 * Disassembly of extra_aslts-extInPlace.aml
 *
 * Original Table Header:
 *     Signature        "DSDT"
 *     Length           0x00029ADD (170717)
 *     Revision         0x02
 *     Checksum         0xA0
 *     OEM ID           "INTEL"
 *     OEM Table ID     "ABCDE"
 *     OEM Revision     0x00000001 (1)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20260408 (539362312)
 */
DefinitionBlock ("", "DSDT", 2, "INTEL", "ABCDE", 0x00000001)
{
    Name (Z062, 0x3E)
    Name (FF32, 0xFFFFFFFF)
    Name (FF64, Ones)
    Name (TRCF, 0x00)
    Name (TRCH, "ASLTS")
    Name (STST, "STST")
    Name (CTST, "CTST")
    Name (PR01, 0x01)
    Name (PR02, 0x01)
    Name (TMT0, 0x00)
    Name (MTHR, 0x00)
    Method (SET3, 1, NotSerialized)
    {
        Store (Arg0, MTHR) /* \MTHR */
    }

    Name (C000, 0x0A)
    Name (C001, 0x05)
    Name (C002, 0x0D)
    Name (C003, 0x0C)
    Name (C004, 0x06)
    Name (C005, 0x04)
    Name (C006, 0x1F)
    Name (C007, 0x33)
    Name (C008, 0x00)
    Name (C009, 0x01)
    Name (C00A, 0x02)
    Name (C00B, 0x03)
    Name (C00C, 0x04)
    Name (C00D, 0x05)
    Name (C00E, 0x06)
    Name (C00F, 0x07)
    Name (C010, 0x08)
    Name (C011, 0x09)
    Name (C012, 0x0A)
    Name (C013, 0x0B)
    Name (C014, 0x0C)
    Name (C015, 0x0D)
    Name (C016, 0x0E)
    Name (C017, 0x0F)
    Name (C018, 0x10)
    Name (C019, 0x11)
    Name (C01A, 0x12)
    Name (C01B, 0x13)
    Name (C01C, 0x14)
    Name (C01D, 0x15)
    Name (C01E, 0x16)
    Name (C01F, 0x17)
    Name (C020, 0x18)
    Name (C021, 0x19)
    Name (C022, 0x1A)
    Name (C023, 0x1B)
    Name (C024, 0x1C)
    Name (C025, 0x1D)
    Name (C027, 0x1E)
    Name (C028, 0x00)
    Name (NMTP, Package (0x20)
    {
        "Uninitialized", 
        "Integer", 
        "String", 
        "Buffer", 
        "Package", 
        "Field Unit", 
        "Device", 
        "Event", 
        "Method", 
        "Mutex", 
        "Operation Region", 
        "Power Resource", 
        "Processor", 
        "Thermal Zone", 
        "Buffer Field", 
        "DDB Handle", 
        "Debug Object", 
        "LOCAL_REGION_FIELD", 
        "LOCAL_BANK_FIELD", 
        "LOCAL_INDEX_FIELD", 
        "LOCAL_REFERENCE", 
        "LOCAL_ALIAS", 
        "LOCAL_METHOD_ALIAS", 
        "LOCAL_NOTIFY", 
        "LOCAL_ADDRESS_HANDLER", 
        "LOCAL_RESOURCE", 
        "LOCAL_RESOURCE_FIELD", 
        "LOCAL_SCOPE", 
        "LOCAL_EXTRA", 
        "LOCAL_DATA", 
        "--", 
        "--"
    })
    Name (C080, 0x00)
    Name (C081, 0x00)
    Name (C082, 0x00)
    Name (C083, 0x00)
    Name (C084, 0x00)
    Name (C085, 0x00)
    Name (C086, 0x00)
    Name (C087, 0x00)
    Name (C088, 0x00)
    Name (C089, 0x00)
    Name (C08A, 0x00)
    Name (C08B, 0x00)
    Name (C08C, 0x00788B60)
    Name (EXCV, 0x00)
    Name (ZFFF, 0x07FF)
    Name (F64, 0x00)
    Name (ISZ0, 0x00)
    Name (ISZC, 0x00)
    Name (ETR0, 0x04B0)
    Name (ETR1, 0x0190)
    Name (ERRP, Package (ETR0, ){})
    Name (RP0P, Package (ETR0, ){})
    Name (RMRC, 0x00)
    Name (ERRS, 0x00)
    Name (ERRB, 0x00)
    Name (ERR0, 0x00)
    Name (ERR1, 0x00)
    Name (ERR2, 0x00)
    Name (ERR3, 0x00)
    Name (ERR4, 0x00)
    Name (ERR5, 0x00)
    Name (ERR6, 0x00)
    Name (ERR7, 0x00)
    Name (FNAM, 0x00)
    Method (SET0, 3, NotSerialized)
    {
        If (ERR0)
        {
            ERR ("SET0", Z062, 0x010A, 0x00, 0x00, ERR0, 0x00)
        }
        Else
        {
            CopyObject (Arg0, ERR0) /* \ERR0 */
            CopyObject (Arg1, ERR1) /* \ERR1 */
            CopyObject (Arg2, ERR2) /* \ERR2 */
        }
    }

    Method (RST0, 0, NotSerialized)
    {
        CopyObject (0x00, ERR0) /* \ERR0 */
        CopyObject (0x00, ERR1) /* \ERR1 */
        CopyObject (0x00, ERR2) /* \ERR2 */
        CopyObject (0x00, FNAM) /* \FNAM */
    }

    Method (RST2, 0, NotSerialized)
    {
        Store (0x00, ERR3) /* \ERR3 */
    }

    Method (GET2, 0, NotSerialized)
    {
        Return (ERR3) /* \ERR3 */
    }

    Name (TCLA, 0x00)
    Name (TCLF, 0x01)
    Name (TCLC, 0x02)
    Name (TCLE, 0x03)
    Name (TCLD, 0x04)
    Name (TCLS, 0x05)
    Name (TCLM, 0x06)
    Name (TCLT, 0x07)
    Name (TCLI, 0x08)
    Name (MAXC, 0x08)
    Name (TCLL, 0x00)
    Name (TIND, 0x12345678)
    Name (TSNM, "NAME_OF_TEST")
    Name (NRMT, "")
    Name (FLG5, 0x00)
    Name (FLG6, 0x00)
    Name (ABUU, 0x00)
    Method (SETF, 1, NotSerialized)
    {
        CopyObject (Arg0, FNAM) /* \FNAM */
    }

    Method (THDR, 3, NotSerialized)
    {
        SETF (Arg2)
        Concatenate ("TEST: ", Arg0, Local1)
        Concatenate (Local1, ", ", Local2)
        Concatenate (Local2, Arg1, Local3)
        Concatenate (Local3, " (", Local4)
        Concatenate (Local4, Arg2, Local5)
        Concatenate (Local5, ")", Local6)
        Store (Local6, Debug)
    }

    Method (RPT0, 0, NotSerialized)
    {
        Name (B000, Buffer (0x04){})
        If (SizeOf (NRMT))
        {
            Concatenate (":", TCN0 (TCLL), Local1)
            Concatenate (Local1, ":", Local0)
            Concatenate (Local0, TNIC (TCLL, TIND), Local1)
            Concatenate (Local1, ":", Local0)
            Concatenate (Local0, NRMT, Local1)
            Concatenate (Local1, ":", Local0)
            Subtract (ERRS, ERR5, Local7)
            If (FLG5)
            {
                Concatenate (Local0, "SKIPPED:", Local1)
            }
            ElseIf (FLG6)
            {
                Concatenate (Local0, "BLOCKED:", Local1)
            }
            ElseIf (Local7)
            {
                Concatenate (Local0, "FAIL:Errors # ", Local2)
                Store (Local7, B000) /* \RPT0.B000 */
                Concatenate (Local2, B000, Local0)
                Concatenate (Local0, ":", Local1)
                Increment (ERR6)
            }
            Else
            {
                Concatenate (Local0, "PASS:", Local1)
            }

            Concatenate (":", CTST, Local0)
            Concatenate (Local0, Local1, Local2)
            Store (Local2, Debug)
            If (LLess (RMRC, ETR0))
            {
                Concatenate (":", STST, Local2)
                Concatenate (Local2, Local1, Local0)
                Store (Local0, Index (RP0P, RMRC))
            }

            Increment (RMRC)
        }

        Store (0x00, ERR5) /* \ERR5 */
        Store (0x00, FLG5) /* \FLG5 */
        Store (0x00, FLG6) /* \FLG6 */
    }

    Method (SRMT, 1, NotSerialized)
    {
        RPT0 ()
        Store (ERRS, ERR5) /* \ERR5 */
        If (0x01)
        {
            Concatenate (Arg0, " test started", Debug)
        }

        CopyObject (Arg0, NRMT) /* \NRMT */
    }

    Method (SKIP, 0, NotSerialized)
    {
        Store (0x01, FLG5) /* \FLG5 */
    }

    Method (BLCK, 0, NotSerialized)
    {
        Store (0x01, FLG6) /* \FLG6 */
    }

    Method (BEG0, 2, NotSerialized)
    {
        SET0 (Arg0, Arg1, 0x00)
    }

    Method (END0, 0, NotSerialized)
    {
        RST0 ()
    }

    Method (STTT, 4, NotSerialized)
    {
        Store (Arg0, TSNM) /* \TSNM */
        Store (Arg1, TCLL) /* \TCLL */
        Store (Arg2, TIND) /* \TIND */
        Store ("", NRMT) /* \NRMT */
        Store (0x00, FLG5) /* \FLG5 */
        Store (0x00, FLG6) /* \FLG6 */
        Store (0x00, ERR5) /* \ERR5 */
        Store (PK00 (Arg1, Arg2), ERRB) /* \ERRB */
        Concatenate ("TEST (", TCN0 (TCLL), Local1)
        Concatenate (Local1, "), ", Local0)
        Concatenate (Local0, TSNM, Local1)
        If (RTPT)
        {
            Store (0x00, Local7)
            If (LEqual (RUN0, 0x00))
            {
                Store (0x01, Local7)
            }
            ElseIf (LEqual (RUN0, 0x01))
            {
                If (Arg3)
                {
                    Store (0x01, Local7)
                }
            }
            ElseIf (LEqual (RUN0, 0x02))
            {
                If (LEqual (Arg3, 0x00))
                {
                    Store (0x01, Local7)
                }
            }
            ElseIf (LEqual (RUN0, 0x03))
            {
                If (LEqual (Arg3, RUN1))
                {
                    Store (0x01, Local7)
                }
            }
            ElseIf (LEqual (RUN0, 0x04))
            {
                If (LEqual (Arg1, RUN2))
                {
                    If (LEqual (Arg2, RUN3))
                    {
                        Store (0x01, Local7)
                    }
                }
            }
        }
        Else
        {
            Store (0x01, Local7)
        }

        If (LNot (Local7))
        {
            Concatenate (Local1, ", SKIPPED", Local0)
            Store (Local0, Local1)
        }

        Store (Local1, Debug)
        Return (Local7)
    }

    Method (FTTT, 0, NotSerialized)
    {
        CH03 ("FTTT", 0x00, 0x0249, 0x00, 0x00)
        RPT0 ()
        Store ("NAME_OF_TEST", TSNM) /* \TSNM */
        Store (0x00, TCLL) /* \TCLL */
        Store (0x12345678, TIND) /* \TIND */
        Store ("", NRMT) /* \NRMT */
        Store (0x00, FLG5) /* \FLG5 */
        Store (0x00, FLG6) /* \FLG6 */
        Store (0x00, ERR5) /* \ERR5 */
    }

    Method (PK00, 2, NotSerialized)
    {
        And (Arg0, 0x0F, Local0)
        And (Arg1, 0x1F, Local1)
        ShiftLeft (Local0, 0x05, Local2)
        Or (Local2, Local1, Local0)
        ShiftLeft (Local0, 0x17, Local7)
        Return (Local7)
    }

    Method (PK01, 2, NotSerialized)
    {
        And (Arg0, 0x07FF, Local0)
        And (Arg1, 0x0FFF, Local1)
        ShiftLeft (Local0, 0x0C, Local2)
        Or (Local2, Local1, Local7)
        Return (Local7)
    }

    Method (PK02, 1, NotSerialized)
    {
        And (Arg0, 0x01FF, Local0)
        ShiftLeft (Local0, 0x17, Local7)
        Return (Local7)
    }

    Method (PK03, 2, NotSerialized)
    {
        And (Arg0, 0x07FF, Local0)
        And (Arg1, 0x0FFF, Local1)
        ShiftLeft (Local0, 0x0C, Local2)
        Or (Local2, Local1, Local7)
        Return (Local7)
    }

    Method (ERR, 7, NotSerialized)
    {
        Store (0x00, Local3)
        Store (0x00, Local6)
        If (ERR0)
        {
            Store (ERR0, Local4)
            Store (ERR1, Local3)
            If (ERR2)
            {
                Store (ERR2, Local5)
            }
            Else
            {
                Store (Arg4, Local5)
            }
        }
        Else
        {
            Store (0x00, Local4)
            Store (Arg4, Local5)
            If (LEqual (TCLL, TCLD))
            {
                If (Local5)
                {
                    Store (ZFFF, Local4)
                }
            }
            Else
            {
                Store (Arg3, Local4)
            }

            If (LEqual (ObjectType (Arg0), C00A))
            {
                Store (Arg0, Local3)
            }
        }

        If (Local4)
        {
            Store (PK01 (Local4, Local5), Local6)
        }

        If (LEqual (TCLL, TCLD))
        {
            Store (PK02 (TIND), Local0)
            Or (Local6, Local0, Local6)
        }

        Store (PK03 (Arg1, Arg2), Local0)
        Or (ERRB, Local0, Local7)
        Store ("---------- ERROR    : ", Local1)
        Concatenate (Local1, Arg0, Local0)
        Store (Local0, Debug)
        ERP0 (Arg1, Arg2, Local4, Local3, Local5)
        If (LEqual (ObjectType (Arg5), 0x01))
        {
            ToHexString (Arg6, Local0)
            ToDecimalString (Arg6, Local1)
            Concatenate ("**** Expected Result: 0x", Local0, Local0)
            Concatenate (Local0, ", (", Local0)
            Concatenate (Local0, Local1, Local0)
            Concatenate (Local0, ")", Local0)
            Store (Local0, Debug)
            ToHexString (Arg5, Local0)
            ToDecimalString (Arg5, Local1)
            Concatenate ("**** Actual Result  : 0x", Local0, Local0)
            Concatenate (Local0, ", (", Local0)
            Concatenate (Local0, Local1, Local0)
            Concatenate (Local0, ")", Local0)
            Store (Local0, Debug)
        }
        Else
        {
            Store ("**** Actual Result:", Debug)
            Store (Arg5, Debug)
            Store ("**** Expected Result:", Debug)
            Store (Arg6, Debug)
        }

        Store ("---------- END\n", Debug)
        If (LLess (ERRS, ETR1))
        {
            Multiply (ERRS, 0x03, Local0)
            Store (Local7, Index (ERRP, Local0))
            Increment (Local0)
            Store (Local6, Index (ERRP, Local0))
            Increment (Local0)
            Store (Local3, Index (ERRP, Local0))
        }

        Increment (ERRS)
        Store (0x01, ERR3) /* \ERR3 */
    }

    Method (ERP0, 5, NotSerialized)
    {
        Concatenate ("TITLE               : ", TSNM, Local0)
        Store (Local0, Debug)
        Concatenate ("COLLECTION          : ", TCN0 (TCLL), Local0)
        Store (TNIC (TCLL, TIND), Local1)
        Store (Local0, Debug)
        Concatenate ("TEST CASE           : ", Local1, Local0)
        Store (Local0, Debug)
        Concatenate ("TEST                : ", NRMT, Local0)
        Store (Local0, Debug)
        If (LNotEqual (FNAM, 0x00))
        {
            Store (FNAM, Local1)
        }
        ElseIf (LEqual (Arg0, ZFFF))
        {
            Store (SB00 (TIND, 0x00), Local1)
        }
        Else
        {
            Store (DerefOf (Index (TFN0, Arg0)), Local1)
        }

        Concatenate ("ERROR,    File      : ", Local1, Local0)
        Store (Local0, Debug)
        Concatenate ("          Line      : ", ToDecimalString (Arg1), Local0)
        Store (Local0, Debug)
        If (Arg2)
        {
            If (LEqual (Arg2, ZFFF))
            {
                Store (SB00 (TIND, 0x00), Local1)
            }
            Else
            {
                Store (DerefOf (Index (TFN0, Arg2)), Local1)
            }

            Concatenate ("CHECKING, File      : ", Local1, Local0)
            Store (Local0, Debug)
            If (LEqual (ObjectType (Arg3), C00A))
            {
                Concatenate ("             Method : ", Arg3, Local0)
                Store (Local0, Debug)
            }

            Concatenate ("             Line   : ", ToDecimalString (Arg4), Local0)
            Store (Local0, Debug)
        }
    }

    Method (SB00, 2, NotSerialized)
    {
        Store ("?", Local7)
        If (LEqual (Arg1, 0x00))
        {
            ToDecimalString (Arg0, Local0)
            Concatenate ("*", Local0, Local1)
            Concatenate (Local1, ".asl", Local7)
        }
        ElseIf (LEqual (Arg1, 0x01))
        {
            ToDecimalString (Arg0, Local0)
            Concatenate ("Demo of bug ", Local0, Local7)
        }

        Return (Local7)
    }

    Method (PRN0, 1, Serialized)
    {
        Name (LPN0, 0x00)
        Name (LPC0, 0x00)
        Store (SizeOf (Arg0), LPN0) /* \PRN0.LPN0 */
        Store (0x00, LPC0) /* \PRN0.LPC0 */
        While (LPN0)
        {
            Store (DerefOf (Index (Arg0, LPC0)), Local0)
            Store (Local0, Debug)
            Decrement (LPN0)
            Increment (LPC0)
        }
    }

    Method (CH00, 4, NotSerialized)
    {
        If (LNotEqual (Arg3, Zero))
        {
            ERR (Arg0, Z062, 0x03AD, 0x00, 0x00, Arg1, Arg2)
        }
    }

    Method (CH01, 4, NotSerialized)
    {
        If (LNotEqual (Arg3, Ones))
        {
            ERR (Arg0, Z062, 0x03BC, 0x00, 0x00, Arg1, Arg2)
        }
    }

    Method (RNG0, 3, NotSerialized)
    {
        If (LGreater (Arg1, Arg2))
        {
            Store ("RNG0: RangeMin greater than RangeMax", Debug)
            Fatal (0x00, 0x00000000, 0x00)
        }

        If (LGreater (Arg1, Arg0))
        {
            Return (Zero)
        }
        ElseIf (LGreater (Arg0, Arg2))
        {
            Return (Zero)
        }

        Return (Ones)
    }

    Name (BIG0, "qwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdf")
    Name (ALL0, "`1234567890-=qwertyuiop[]\\asdfghjkl;\'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?")
    Method (CST0, 0, NotSerialized)
    {
        If (LNotEqual (C000, 0x0A))
        {
            ERR ("c000 corrupted", Z062, 0x03E7, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C001, 0x05))
        {
            ERR ("c001 corrupted", Z062, 0x03EC, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C002, 0x0D))
        {
            ERR ("c002 corrupted", Z062, 0x03F1, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C003, 0x0C))
        {
            ERR ("c003 corrupted", Z062, 0x03F6, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C004, 0x06))
        {
            ERR ("c004 corrupted", Z062, 0x03FB, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C005, 0x04))
        {
            ERR ("c005 corrupted", Z062, 0x0400, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C006, 0x1F))
        {
            ERR ("c006 corrupted", Z062, 0x0405, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C007, 0x33))
        {
            ERR ("c007 corrupted", Z062, 0x040A, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C008, 0x00))
        {
            ERR ("c008 corrupted", Z062, 0x040F, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C009, 0x01))
        {
            ERR ("c009 corrupted", Z062, 0x0414, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C00A, 0x02))
        {
            ERR ("c00a corrupted", Z062, 0x0419, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C00B, 0x03))
        {
            ERR ("c00b corrupted", Z062, 0x041E, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C00C, 0x04))
        {
            ERR ("c00c corrupted", Z062, 0x0423, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C00D, 0x05))
        {
            ERR ("c00d corrupted", Z062, 0x0428, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C00E, 0x06))
        {
            ERR ("c00e corrupted", Z062, 0x042D, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C00F, 0x07))
        {
            ERR ("c00f corrupted", Z062, 0x0432, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C010, 0x08))
        {
            ERR ("c010 corrupted", Z062, 0x0437, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C011, 0x09))
        {
            ERR ("c011 corrupted", Z062, 0x043C, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C012, 0x0A))
        {
            ERR ("c012 corrupted", Z062, 0x0441, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C013, 0x0B))
        {
            ERR ("c013 corrupted", Z062, 0x0446, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C014, 0x0C))
        {
            ERR ("c014 corrupted", Z062, 0x044B, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C015, 0x0D))
        {
            ERR ("c015 corrupted", Z062, 0x0450, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C016, 0x0E))
        {
            ERR ("c016 corrupted", Z062, 0x0455, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C017, 0x0F))
        {
            ERR ("c017 corrupted", Z062, 0x045A, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C018, 0x10))
        {
            ERR ("c018 corrupted", Z062, 0x045F, 0x00, 0x00, 0x00, 0x00)
        }

        If (LNotEqual (C019, 0x11))
        {
            ERR ("c019 corrupted", Z062, 0x0464, 0x00, 0x00, 0x00, 0x00)
        }
    }

    Method (SFT0, 4, Serialized)
    {
        Name (N000, 0x00)
        Name (NCUR, 0x00)
        Store (Arg1, N000) /* \SFT0.N000 */
        Store (0x00, NCUR) /* \SFT0.NCUR */
        Store (0x00, Local6)
        If (Arg2)
        {
            Store (Arg3, Local3)
            Subtract (0x08, Local3, Local5)
        }
        Else
        {
            Store (Arg3, Local5)
            Subtract (0x08, Local5, Local3)
        }

        Store (Arg1, Local0)
        Increment (Local0)
        Name (B000, Buffer (Local0){})
        While (N000)
        {
            Store (DerefOf (Index (Arg0, NCUR)), Local0)
            ShiftRight (Local0, Local3, Local1)
            And (Local1, 0xFF, Local2)
            Or (Local2, Local6, Local1)
            ShiftLeft (Local0, Local5, Local4)
            And (Local4, 0xFF, Local6)
            Store (Local1, Index (B000, NCUR))
            Decrement (N000)
            Increment (NCUR)
        }

        Store (Local6, Index (B000, NCUR))
        Return (B000) /* \SFT0.B000 */
    }

    Method (MBS0, 2, NotSerialized)
    {
        Add (Arg0, Arg1, Local0)
        Add (Local0, 0x07, Local1)
        Divide (Local1, 0x08, Local2, Local0)
        Return (Local0)
    }

    Method (SFT1, 5, Serialized)
    {
        Name (PREV, 0x00)
        Name (MS00, 0x00)
        Name (MS01, 0x00)
        Name (MS02, 0x00)
        Name (MS03, 0x00)
        Name (TAIL, 0x00)
        Name (LBT0, 0x00)
        Name (LPN0, 0x00)
        Name (LPC0, 0x00)
        Name (NB01, 0x00)
        Name (NREG, 0x00)
        Name (NB08, 0x00)
        Name (NB09, 0x00)
        Name (REST, 0x00)
        If (LLess (Arg2, 0x01))
        {
            ERR ("sft", Z062, 0x04CD, 0x00, 0x00, Arg2, 0x01)
            Return (Ones)
        }

        If (LGreater (Arg1, 0x07))
        {
            ERR ("sft", Z062, 0x04D3, 0x00, 0x00, Arg1, 0x07)
            Return (Ones)
        }

        Store (MBS0 (Arg1, Arg2), NB01) /* \SFT1.NB01 */
        Name (B000, Buffer (NB01){})
        Store (Arg1, NB08) /* \SFT1.NB08 */
        Subtract (0x08, NB08, NB09) /* \SFT1.NB09 */
        ShiftRight (0xFF, NB08, Local0)
        ShiftLeft (Local0, NB08, MS01) /* \SFT1.MS01 */
        Not (MS01, MS00) /* \SFT1.MS00 */
        Add (Arg1, Arg2, Local7)
        Mod (Local7, 0x08, REST) /* \SFT1.REST */
        If (LEqual (REST, 0x00))
        {
            Store (0x08, REST) /* \SFT1.REST */
        }

        And (Arg3, MS00, PREV) /* \SFT1.PREV */
        If (LGreaterEqual (Arg2, NB09))
        {
            Store (0x01, NREG) /* \SFT1.NREG */
            Subtract (Arg2, NB09, Local7)
            Divide (Local7, 0x08, Local1, Local0)
            Add (NREG, Local0, NREG) /* \SFT1.NREG */
        }

        Store (NREG, LPN0) /* \SFT1.LPN0 */
        Store (0x00, LPC0) /* \SFT1.LPC0 */
        While (LPN0)
        {
            Store (DerefOf (Index (Arg0, LPC0)), Local7)
            ShiftLeft (Local7, NB08, Local0)
            Or (Local0, PREV, Local1)
            Store (Local1, Index (B000, LPC0))
            ShiftRight (Local7, NB09, PREV) /* \SFT1.PREV */
            Decrement (LPN0)
            Increment (LPC0)
        }

        If (LEqual (REST, 0x08))
        {
            Store (0x00, TAIL) /* \SFT1.TAIL */
        }
        ElseIf (LLessEqual (REST, NB08))
        {
            Store (0x01, TAIL) /* \SFT1.TAIL */
        }
        Else
        {
            Store (0x02, TAIL) /* \SFT1.TAIL */
            Store (DerefOf (Index (Arg0, LPC0)), LBT0) /* \SFT1.LBT0 */
        }

        If (LEqual (TAIL, 0x01))
        {
            ShiftRight (0xFF, REST, Local0)
            ShiftLeft (Local0, REST, MS03) /* \SFT1.MS03 */
            Not (MS03, MS02) /* \SFT1.MS02 */
            And (PREV, MS02, Local0)
            And (Arg4, MS03, Local1)
            Or (Local0, Local1, Local2)
            Store (Local2, Index (B000, LPC0))
        }
        ElseIf (LEqual (TAIL, 0x02))
        {
            And (PREV, MS00, Local0)
            ShiftLeft (LBT0, NB08, Local1)
            Or (Local0, Local1, Local7)
            ShiftRight (0xFF, REST, Local2)
            ShiftLeft (Local2, REST, Local0)
            Not (Local0, Local1)
            And (Local7, Local1, Local2)
            And (Arg4, Local0, Local3)
            Or (Local2, Local3, Local0)
            Store (Local0, Index (B000, LPC0))
        }

        Return (B000) /* \SFT1.B000 */
    }

    Method (M4C0, 4, Serialized)
    {
        Name (TMP0, 0x00)
        Name (TMP1, 0x00)
        Store (0x00, Local7)
        Store (ObjectType (Arg1), TMP0) /* \M4C0.TMP0 */
        If (F64)
        {
            Store (ObjectType (Arg2), TMP1) /* \M4C0.TMP1 */
            If (LNotEqual (TMP0, TMP1))
            {
                ERR (Arg0, Z062, 0x055B, 0x00, 0x00, TMP0, TMP1)
                Store (0x01, Local7)
            }
            ElseIf (LNotEqual (Arg1, Arg2))
            {
                ERR (Arg0, Z062, 0x0560, 0x00, 0x00, Arg1, Arg2)
                Store (0x01, Local7)
            }
        }
        Else
        {
            Store (ObjectType (Arg3), TMP1) /* \M4C0.TMP1 */
            If (LNotEqual (TMP0, TMP1))
            {
                ERR (Arg0, Z062, 0x0569, 0x00, 0x00, TMP0, TMP1)
                Store (0x01, Local7)
            }
            ElseIf (LNotEqual (Arg1, Arg3))
            {
                ERR (Arg0, Z062, 0x056E, 0x00, 0x00, Arg1, Arg3)
                Store (0x01, Local7)
            }
        }

        Return (Local7)
    }

    Method (M4A1, 2, Serialized)
    {
        Name (S000, " ")
        Store (DerefOf (Index (Arg0, Arg1)), Local0)
        Store (Local0, Index (S000, 0x00))
        Return (S000) /* \M4A1.S000 */
    }

    Method (STRT, 1, Serialized)
    {
        Method (M555, 0, NotSerialized)
        {
        }

        DataTableRegion (HDR, "DSDT", "", "")
        Field (HDR, AnyAcc, NoLock, Preserve)
        {
            SIG,    32, 
            LENG,   32, 
            REV,    8, 
            SUM,    8, 
            OID,    48, 
            OTID,   64, 
            OREV,   32, 
            CID,    32, 
            CREV,   32
        }

        M555 ()
        Store (Timer, TMT0) /* \TMT0 */
        If (LLess (REV, 0x02))
        {
            Store (0x00, F64) /* \F64_ */
            Store (0x04, ISZ0) /* \ISZ0 */
            Store (0x08, ISZC) /* \ISZC */
            Store ("32-bit mode", Debug)
        }
        Else
        {
            Store (0x01, F64) /* \F64_ */
            Store (0x08, ISZ0) /* \ISZ0 */
            Store (0x10, ISZC) /* \ISZC */
            Store ("64-bit mode", Debug)
        }

        If (CH02 ())
        {
            Increment (ERR7)
            CH03 ("STRT", 0x00, 0x05BD, 0x00, 0x00)
            Store (0x00, EXC0) /* \EXC0 */
            Store (0x00, EXC1) /* \EXC1 */
        }

        SRTP (Arg0)
        RTPI ()
        RST0 ()
        RST2 ()
        SET2 (SETN)
    }

    Name (TCNP, Package (0x09)
    {
        "compilation", 
        "functional", 
        "complex", 
        "exceptions", 
        "bdemo", 
        "service", 
        "mt", 
        "Identity2MS", 
        "IMPL"
    })
    Method (TCN0, 1, NotSerialized)
    {
        Store ("?", Local7)
        If (LLessEqual (Arg0, MAXC))
        {
            Store (DerefOf (Index (TCNP, Arg0)), Local7)
        }

        Return (Local7)
    }

    Method (TNIC, 2, Serialized)
    {
        Store ("?", Local7)
        Switch (ToInteger (Arg0))
        {
            Case (0x01)
            {
                Store (DerefOf (Index (TNF0, Arg1)), Local7)
            }
            Case (0x02)
            {
                Store (DerefOf (Index (TNC0, Arg1)), Local7)
            }
            Case (0x03)
            {
                Store (DerefOf (Index (TNE0, Arg1)), Local7)
            }
            Case (0x04)
            {
                Store (SB00 (Arg1, 0x01), Local7)
            }
            Case (0x05)
            {
                Store (DerefOf (Index (TNS0, Arg1)), Local7)
            }
            Case (0x06)
            {
                Store (DerefOf (Index (TNM0, Arg1)), Local7)
            }
            Case (0x07)
            {
                Store (DerefOf (Index (TNT0, Arg1)), Local7)
            }
            Case (0x08)
            {
                Store (DerefOf (Index (TNI0, Arg1)), Local7)
            }

        }

        Return (Local7)
    }

    Name (TNF0, Package (0x0F)
    {
        "arithmetic", 
        "bfield", 
        "constant", 
        "control", 
        "descriptor", 
        "external", 
        "local", 
        "logic", 
        "manipulation", 
        "name", 
        "reference", 
        "region", 
        "synchronization", 
        "table", 
        "module"
    })
    Name (TNC0, Package (0x14)
    {
        "misc", 
        "provoke", 
        "oarg", 
        "oconst", 
        "olocal", 
        "oreturn", 
        "onamedloc", 
        "onamedglob", 
        "opackageel", 
        "oreftonamed", 
        "oconversion", 
        "oreftopackageel", 
        "rstore", 
        "roptional", 
        "rconversion", 
        "rcopyobject", 
        "rindecrement", 
        "rexplicitconv", 
        "badasl", 
        "namespace"
    })
    Name (TNE0, Package (0x07)
    {
        "exc", 
        "exc_operand1", 
        "exc_operand2", 
        "exc_result1", 
        "exc_result2", 
        "exc_ref", 
        "exc_tbl"
    })
    Name (TNS0, Package (0x01)
    {
        "condbranches"
    })
    Name (TNM0, Package (0x01)
    {
        "mt-mutex"
    })
    Name (TNT0, Package (0x01)
    {
        "abbu"
    })
    Name (TNI0, Package (0x01)
    {
        "dynobj"
    })
    Name (TFN0, Package (0xCD)
    {
        "UNDEF", 
        "crbuffield.asl", 
        "constants.asl", 
        "ctl0.asl", 
        "ctl1.asl", 
        "ctl2.asl", 
        "timing.asl", 
        "concatenaterestemplate.asl", 
        "dependentfn.asl", 
        "dma.asl", 
        "dwordio.asl", 
        "dwordmemory.asl", 
        "dwordspace.asl", 
        "extendedio.asl", 
        "extendedmemory.asl", 
        "extendedspace.asl", 
        "fixedio.asl", 
        "interrupt.asl", 
        "io.asl", 
        "irq.asl", 
        "irqnoflags.asl", 
        "memory24.asl", 
        "memory32.asl", 
        "memory32fixed.asl", 
        "qwordio.asl", 
        "qwordmemory.asl", 
        "qwordspace.asl", 
        "register.asl", 
        "resourcetemplate.asl", 
        "rtemplate.asl", 
        "vendorlong.asl", 
        "vendorshort.asl", 
        "wordbusnumber.asl", 
        "wordio.asl", 
        "wordspace.asl", 
        "logical.asl", 
        "concatenate.asl", 
        "eisaid.asl", 
        "match1.asl", 
        "mid.asl", 
        "objecttype.asl", 
        "sizeof.asl", 
        "store.asl", 
        "tobuffer.asl", 
        "todecimalstring.asl", 
        "tofrombcd.asl", 
        "tohexstring.asl", 
        "tointeger.asl", 
        "tostring.asl", 
        "touuid.asl", 
        "unicode.asl", 
        "package.asl", 
        "event.asl", 
        "mutex.asl", 
        "misc.asl", 
        "provoke.asl", 
        "oconversion.asl", 
        "rconversion.asl", 
        "exc.asl", 
        "exc_operand1.asl", 
        "exc_result.asl", 
        "XXXXXX.asl", 
        "common.asl", 
        "ehandle.asl", 
        "oproc.asl", 
        "otest.asl", 
        "rproc.asl", 
        "rtest.asl", 
        "switch1.asl", 
        "switch2.asl", 
        "switch3.asl", 
        "switch4.asl", 
        "switch5.asl", 
        "switch6.asl", 
        "while.asl", 
        "match2.asl", 
        "ref00.asl", 
        "ref01.asl", 
        "ref02.asl", 
        "ref03.asl", 
        "ref04.asl", 
        "ref70.asl", 
        "operations.asl", 
        "arithmetic.asl", 
        "ocommon.asl", 
        "oconst.asl", 
        "onamedglob1.asl", 
        "onamedglob2.asl", 
        "onamedloc1.asl", 
        "onamedloc2.asl", 
        "opackageel.asl", 
        "oreftonamed1.asl", 
        "exc_00_undef.asl", 
        "exc_01_int.asl", 
        "exc_02_str.asl", 
        "exc_03_buf.asl", 
        "exc_04_pckg.asl", 
        "exc_05_funit.asl", 
        "exc_06_dev.asl", 
        "exc_07_event.asl", 
        "exc_08_method.asl", 
        "exc_09_mux.asl", 
        "exc_10_oreg.asl", 
        "exc_11_pwr.asl", 
        "exc_12_proc.asl", 
        "exc_13_tzone.asl", 
        "exc_14_bfield.asl", 
        "exc_operand2.asl", 
        "ref05.asl", 
        "ref71.asl", 
        "ref06.asl", 
        "ref50.asl", 
        "name.asl", 
        "data.asl", 
        "dataproc.asl", 
        "datastproc.asl", 
        "ref07.asl", 
        "olocal.asl", 
        "oreturn.asl", 
        "oreftopackageel.asl", 
        "oreftonamed2.asl", 
        "oarg.asl", 
        "rcommon.asl", 
        "rstore.asl", 
        "rcopyobject.asl", 
        "rindecrement.asl", 
        "rexplicitconv.asl", 
        "roptional.asl", 
        "tcicmd.asl", 
        "dobexec.asl", 
        "dobdecl.asl", 
        "dobctl.asl", 
        "dobexceptions.asl", 
        "method.asl", 
        "function.asl", 
        "condbranches.asl", 
        "add.asl", 
        "standaloneRet.asl", 
        "store.asl", 
        "return.asl", 
        "dobmisc.asl", 
        "opregions.asl", 
        "dtregions.asl", 
        "regionfield.asl", 
        "indexfield.asl", 
        "bankfield.asl", 
        "badasl.asl", 
        "mt-common.asl", 
        "mt-mutex.asl", 
        "mt-mxs.asl", 
        "mutex2.asl", 
        "mutex_proc.asl", 
        "mt-tests.asl", 
        "mt-service.asl", 
        "ns0.asl", 
        "ns1.asl", 
        "ns2.asl", 
        "ns3.asl", 
        "ns4.asl", 
        "ns5.asl", 
        "ns6.asl", 
        "I2MS_msfail0.asl", 
        "I2MS_st0.asl", 
        "I2MS_ns_in00.asl", 
        "I2MS_ns_in10.asl", 
        "I2MS_ns_in20.asl", 
        "I2MS_ns_in30.asl", 
        "I2MS_ns_in40.asl", 
        "I2MS_ns_in50.asl", 
        "I2MS_mt0_abbu.asl", 
        "I2MS_mt0_aslts.asl", 
        "I2MS_recursion_abbu.asl", 
        "I2MS_recursion_aslts.asl", 
        "serialized.asl", 
        "load.asl", 
        "unload.asl", 
        "loadtable.asl", 
        "recursion.asl", 
        "ns-scope.asl", 
        "ns-fullpath.asl", 
        "scope.asl", 
        "object.asl", 
        "order.asl", 
        "I2MS_ns_dv00.asl", 
        "I2MS_ns_dv10.asl", 
        "I2MS_ns_dv20.asl", 
        "I2MS_ns_dv30.asl", 
        "I2MS_ns_device.asl", 
        "I2MS_ns_device_abbu.asl", 
        "I2MS_ns_device_aslts.asl", 
        "I2MS_ns4.asl", 
        "I2MS_ns5.asl", 
        "I2MS_ns6.asl", 
        "fixeddma.asl", 
        "gpioint.asl", 
        "gpioio.asl", 
        "i2cserialbus.asl", 
        "spiserialbus.asl", 
        "uartserialbus.asl", 
        "pinfunction.asl", 
        "pinconfig.asl", 
        "pingroup.asl", 
        "pingroupfunction.asl", 
        "pingroupconfig.asl", 
        "external.asl"
    })
    Method (UNP0, 3, Serialized)
    {
        ShiftRight (Arg0, 0x1C, Local7)
        And (Local7, 0x0F, Local0)
        ShiftRight (Arg0, 0x17, Local7)
        And (Local7, 0x1F, Local1)
        ShiftRight (Arg0, 0x0C, Local7)
        And (Local7, 0x07FF, Local2)
        And (Arg0, 0x0FFF, Local3)
        Store ("", Local6)
        Store ("", Local7)
        Switch (ToInteger (Local0))
        {
            Case (0x01)
            {
                Store (DerefOf (Index (TNF0, Local1)), Local6)
                If (ERR4)
                {
                    Store (", functional, ", Local7)
                }
            }
            Case (0x02)
            {
                Store (DerefOf (Index (TNC0, Local1)), Local6)
                If (ERR4)
                {
                    Store (", complex, ", Local7)
                }
            }
            Case (0x03)
            {
                Store (DerefOf (Index (TNE0, Local1)), Local6)
                If (ERR4)
                {
                    Store (", exceptions, ", Local7)
                }
            }
            Case (0x04)
            {
                ShiftRight (Arg1, 0x17, Local0)
                And (Local0, 0x01FF, Local1)
                Store (SB00 (Local1, 0x01), Local6)
                If (ERR4)
                {
                    Store (", bug-demo, ", Local7)
                }
            }
            Case (0x05)
            {
                Store (DerefOf (Index (TNS0, Local1)), Local6)
                If (ERR4)
                {
                    Store (", service, ", Local7)
                }
            }
            Case (0x06)
            {
                Store (DerefOf (Index (TNM0, Local1)), Local6)
                If (ERR4)
                {
                    Store (", mt, ", Local7)
                }
            }
            Case (0x07)
            {
                Store (DerefOf (Index (TNT0, Local1)), Local6)
                If (ERR4)
                {
                    Store (", Identity2MS, ", Local7)
                }
            }
            Case (0x08)
            {
                Store (DerefOf (Index (TNI0, Local1)), Local6)
                If (ERR4)
                {
                    Store (", IMPL, ", Local7)
                }
            }

        }

        Concatenate (Local7, Local6, Local5)
        Concatenate (Local5, ", ", Local1)
        If (LEqual (Local2, ZFFF))
        {
            ShiftRight (Arg1, 0x17, Local0)
            And (Local0, 0x01FF, Local2)
            Store (SB00 (Local2, 0x00), Local6)
        }
        Else
        {
            Store (DerefOf (Index (TFN0, Local2)), Local6)
        }

        Concatenate (Local1, Local6, Local7)
        Concatenate (Local7, ", ", Local1)
        Concatenate (Local1, Local3, Local7)
        And (Arg1, 0x007FFFFF, Local5)
        If (Local5)
        {
            ShiftRight (Arg1, 0x0C, Local5)
            And (Local5, 0x07FF, Local2)
            And (Arg1, 0x0FFF, Local3)
            If (LEqual (Local2, ZFFF))
            {
                ShiftRight (Arg1, 0x17, Local0)
                And (Local0, 0x01FF, Local2)
                Store (SB00 (Local2, 0x00), Local6)
            }
            Else
            {
                Store (DerefOf (Index (TFN0, Local2)), Local6)
            }

            Concatenate (Local7, ", ", Local1)
            Concatenate (Local1, Local6, Local5)
            Concatenate (Local5, ", ", Local1)
            Concatenate (Local1, Local3, Local7)
            If (LEqual (ObjectType (Arg2), C00A))
            {
                Concatenate (Local7, ", ", Local1)
                Concatenate (Local1, Arg2, Local7)
            }
        }

        Return (Local7)
    }

    Method (RERR, 0, Serialized)
    {
        Name (LPN0, 0x00)
        Name (LPC0, 0x00)
        Store (ETR1, LPN0) /* \RERR.LPN0 */
        If (LLess (ERRS, LPN0))
        {
            Store (ERRS, LPN0) /* \RERR.LPN0 */
        }

        Store (0x00, Local0)
        Store ("========= ERRORS SUMMARY (max 400):", Debug)
        While (LPN0)
        {
            Store (DerefOf (Index (ERRP, Local0)), Local7)
            Increment (Local0)
            Store (DerefOf (Index (ERRP, Local0)), Local6)
            Increment (Local0)
            Store (DerefOf (Index (ERRP, Local0)), Local4)
            Increment (Local0)
            Store (UNP0 (Local7, Local6, Local4), Local1)
            If (ERR4)
            {
                Concatenate ("", Local7, Local2)
                Concatenate (Local2, ", ", Local5)
                Concatenate (Local5, Local6, Local2)
                Concatenate (Local2, Local1, Local7)
            }
            Else
            {
                Concatenate ("", Local1, Local7)
            }

            Store (Local7, Debug)
            Decrement (LPN0)
            Increment (LPC0)
        }

        If (LGreater (ERRS, ETR1))
        {
            Store ("********* Not all errors were traced, maximum exceeded!", Debug)
        }

        Store ("========= END.", Debug)
    }

    Method (RRM0, 0, Serialized, 3)
    {
        Name (LPN0, 0x00)
        Name (LPC0, 0x00)
        Store (ETR0, LPN0) /* \RRM0.LPN0 */
        If (LLess (RMRC, LPN0))
        {
            Store (RMRC, LPN0) /* \RRM0.LPN0 */
        }

        Store ("========= ROOT METHODS SUMMARY (max 600):", Debug)
        While (LPN0)
        {
            Store (DerefOf (Index (RP0P, LPC0)), Local7)
            Store (Local7, Debug)
            Decrement (LPN0)
            Increment (LPC0)
        }

        If (LGreater (RMRC, ETR0))
        {
            Store ("********* Not all root Methods were traced, maximum exceeded!", Debug)
        }

        Store ("========= END.", Debug)
    }

    Method (FNSH, 0, NotSerialized)
    {
        CH03 ("FNSH", 0x00, 0x0834, 0x00, 0x00)
        CST0 ()
        Store (Timer, Local7)
        Subtract (Local7, TMT0, Local6)
        Divide (Local6, 0x0A, Local1, Local2)
        Divide (Local2, 0x000F4240, Local1, Local0)
        Store (Concatenate ("Run time (in seconds): 0x", Local0), Debug)
        Store (Concatenate ("The total number of exceptions handled: 0x", EXC1), Debug)
        If (ERRS)
        {
            RERR ()
        }

        RRM0 ()
        If (F64)
        {
            Concatenate ("TEST ACPICA: ", "64-bit :", Local0)
        }
        Else
        {
            Concatenate ("TEST ACPICA: ", "32-bit :", Local0)
        }

        If (ERR7)
        {
            Concatenate ("!!!! ERRORS were detected during the loading stage, # 0x", ERR7, Debug)
        }

        Store (0x00, EXC1) /* \EXC1 */
        If (LOr (ERRS, ERR7))
        {
            Concatenate (Local0, " FAIL : Errors # 0x", Local1)
            Concatenate (Local1, ERRS, Local2)
            Concatenate (Local2, ", Failed tests # 0x", Local1)
            Store (Concatenate (Local1, ERR6), Debug)
            Return (0x01)
        }

        Store (Concatenate (Local0, " PASS"), Debug)
        Return (0x00)
    }

    Method (TRC0, 3, NotSerialized)
    {
        If (TRCF)
        {
            Concatenate (TRCH, ", WRITE: where ", Local0)
            Concatenate (Local0, Arg1, Local1)
            Concatenate (Local1, ", ", Local0)
            Concatenate (Local0, Arg2, Local1)
            Store (Local1, Debug)
        }
    }

    Method (TRC1, 3, NotSerialized)
    {
        If (TRCF)
        {
            Concatenate (TRCH, ", READ: where ", Local0)
            Concatenate (Local0, Arg1, Local1)
            Concatenate (Local1, ", ", Local0)
            Concatenate (Local0, Arg2, Local1)
            Store (Local1, Debug)
        }
    }

    Method (TRC2, 1, NotSerialized)
    {
        If (TRCF)
        {
            Concatenate (TRCH, ", ", Local0)
            Concatenate (Local0, Arg0, Local1)
            Store (Local1, Debug)
        }
    }

    Method (TRC8, 0, NotSerialized)
    {
        Store (0x01, TRCF) /* \TRCF */
    }

    Method (TRC9, 0, NotSerialized)
    {
        Store (0x00, TRCF) /* \TRCF */
    }

    Method (TS00, 1, NotSerialized)
    {
        If (PR01)
        {
            Concatenate ("Test ", Arg0, Local0)
            Concatenate (Local0, " started", Local1)
            Store (Local1, Debug)
        }
    }

    Method (TMR0, 1, NotSerialized)
    {
        Divide (Arg0, 0x0A, Local0, Local1)
        Divide (Local1, 0x000F4240, Local0, Local2)
        Return (Local2)
    }

    Name (SLCK, 0x00)
    Name (MLVL, 0x00)
    Method (MN00, 0, NotSerialized)
    {
        Store (0x00, SLCK) /* \SLCK */
        Store (0x01, MLVL) /* \MLVL */
        Store (MAIN (), Local7)
        Return (Local7)
    }

    Method (MN01, 0, NotSerialized)
    {
        Store (0x01, SLCK) /* \SLCK */
        Store (0x01, MLVL) /* \MLVL */
        Store (MAIN (), Local7)
        Return (Local7)
    }

    Name (RUN0, 0x00)
    Name (RUN1, 0x00)
    Name (RUN2, 0x00)
    Name (RUN3, 0x00)
    Name (RTPT, 0x00)
    Name (W000, 0x00)
    Name (W001, 0x00)
    Name (W002, 0x00)
    Name (W003, 0x00)
    Name (W004, 0x00)
    Name (W005, 0x00)
    Name (W006, 0x00)
    Name (W007, 0x00)
    Name (W008, 0x00)
    Name (W009, 0x00)
    Name (W00A, 0x00)
    Name (W00B, 0x00)
    Name (W00C, 0x00)
    Name (W00D, 0x00)
    Name (W01A, 0x00)
    Name (W00E, 0x00)
    Name (W00F, 0x00)
    Name (W010, 0x00)
    Name (W011, 0x00)
    Name (W012, 0x00)
    Name (W022, 0x00)
    Name (W013, 0x00)
    Name (W014, 0x00)
    Name (W015, 0x00)
    Name (W016, 0x00)
    Name (W017, 0x00)
    Name (W021, 0x00)
    Name (W018, 0x00)
    Name (W019, 0x00)
    Name (W020, 0x00)
    Method (SRTP, 1, NotSerialized)
    {
        Store (Arg0, RTPT) /* \RTPT */
    }

    Method (RTPI, 0, NotSerialized)
    {
        Store (0x00, RUN0) /* \RUN0 */
        Store (0x00, RUN1) /* \RUN1 */
        Store (0x01, RUN2) /* \RUN2 */
        Store (0x03, RUN3) /* \RUN3 */
        Store (0x01, W000) /* \W000 */
        Store (0x01, W001) /* \W001 */
        Store (0x01, W002) /* \W002 */
        Store (0x01, W003) /* \W003 */
        Store (0x01, W004) /* \W004 */
        Store (0x01, W005) /* \W005 */
        Store (0x01, W006) /* \W006 */
        Store (0x01, W007) /* \W007 */
        Store (0x01, W008) /* \W008 */
        Store (0x01, W009) /* \W009 */
        Store (0x01, W00A) /* \W00A */
        Store (0x01, W00B) /* \W00B */
        Store (0x01, W00C) /* \W00C */
        Store (0x01, W00D) /* \W00D */
        Store (0x01, W00E) /* \W00E */
        Store (0x01, W00F) /* \W00F */
        Store (0x01, W010) /* \W010 */
        Store (0x01, W011) /* \W011 */
        Store (0x01, W021) /* \W021 */
        Store (0x01, W012) /* \W012 */
        Store (0x01, W013) /* \W013 */
        Store (0x01, W014) /* \W014 */
        Store (0x01, W015) /* \W015 */
        Store (0x01, W016) /* \W016 */
        Store (0x01, W019) /* \W019 */
        Store (0x01, W017) /* \W017 */
        Store (0x01, W018) /* \W018 */
    }

    Name (Y078, 0x00)
    Name (Y083, 0x00)
    Name (Y084, 0x01)
    Name (Y098, 0x01)
    Name (Y100, 0x00)
    Name (Y103, 0x01)
    Name (Y104, 0x01)
    Name (Y105, 0x01)
    Name (Y106, 0x00)
    Name (Y111, 0x01)
    Name (Y113, 0x00)
    Name (Y114, 0x00)
    Name (Y118, 0x00)
    Name (Y119, 0x00)
    Name (Y120, 0x00)
    Name (Y121, 0x00)
    Name (Y126, 0x00)
    Name (Y127, 0x00)
    Name (Y128, 0x01)
    Name (Y132, 0x00)
    Name (Y133, 0x00)
    Name (Y134, 0x00)
    Name (Y135, 0x00)
    Name (Y136, 0x01)
    Name (Y157, 0x01)
    Name (Y164, 0x01)
    Name (Y176, 0x00)
    Name (Y178, 0x01)
    Name (Y182, 0x01)
    Name (Y192, 0x01)
    Name (Y200, 0x00)
    Name (Y203, 0x00)
    Name (Y204, 0x00)
    Name (Y205, 0x00)
    Name (Y206, 0x00)
    Name (Y207, 0x00)
    Name (Y208, 0x00)
    Name (Y213, 0x00)
    Name (Y214, 0x00)
    Name (Y215, 0x00)
    Name (Y216, 0x00)
    Name (Y217, 0x00)
    Name (Y220, 0x00)
    Name (Y221, 0x01)
    Name (Y222, 0x00)
    Name (Y223, 0x01)
    Name (Y224, 0x00)
    Name (Y238, 0x00)
    Name (Y242, 0x00)
    Name (Y243, 0x00)
    Name (Y248, 0x00)
    Name (Y251, 0x00)
    Name (Y260, 0x00)
    Name (Y261, 0x00)
    Name (Y262, 0x00)
    Name (Y263, 0x00)
    Name (Y264, 0x00)
    Name (Y275, 0x00)
    Name (Y276, 0x00)
    Name (Y281, 0x00)
    Name (Y282, 0x00)
    Name (Y283, 0x01)
    Name (Y284, 0x01)
    Name (Y286, 0x01)
    Name (Y287, 0x00)
    Name (Y288, 0x00)
    Name (Y289, 0x00)
    Name (Y290, 0x00)
    Name (Y292, 0x00)
    Name (Y293, 0x00)
    Name (Y294, 0x00)
    Name (Y296, 0x00)
    Name (Y297, 0x00)
    Name (Y300, 0x00)
    Name (Y301, 0x00)
    Name (Y302, 0x00)
    Name (Y349, 0x00)
    Name (Y350, 0x00)
    Name (Y361, 0x00)
    Name (Y362, 0x00)
    Name (Y364, 0x00)
    Name (Y365, 0x00)
    Name (Y366, 0x00)
    Name (Y367, 0x00)
    Name (Y500, 0x00)
    Name (Y501, 0x00)
    Name (Y502, 0x00)
    Name (Y503, 0x00)
    Name (Y504, 0x00)
    Name (Y505, 0x00)
    Name (Y506, 0x00)
    Name (Y507, 0x00)
    Name (Y508, 0x00)
    Name (Y509, 0x00)
    Name (Y510, 0x00)
    Name (Y511, 0x00)
    Name (Y512, 0x00)
    Name (Y513, 0x00)
    Name (Y514, 0x00)
    Name (Y516, 0x00)
    Name (Y517, 0x00)
    Name (Y518, 0x00)
    Name (Y519, 0x00)
    Name (Y520, 0x00)
    Name (Y521, 0x00)
    Name (Y522, 0x01)
    Name (Y523, 0x00)
    Name (Y524, 0x00)
    Name (Y525, 0x00)
    Name (Y526, 0x00)
    Name (Y527, 0x00)
    Name (Y600, 0x00)
    Name (Y601, 0x00)
    Name (Y602, 0x01)
    Name (Y603, 0x00)
    Name (Y900, 0x00)
    Name (Y901, 0x01)
    Name (Y902, 0x01)
    Name (Q001, 0x01)
    Name (Q002, 0x00)
    Name (Q003, 0x00)
    Name (Q004, 0x00)
    Name (Q005, 0x00)
    Name (Q006, 0x00)
    Name (Q007, 0x00)
    Name (Q008, 0x00)
    Name (Q009, 0x00)
    Name (Q00A, 0x00)
    Name (Q00B, 0x00)
    Name (RN00, 0x01)
    Name (RN01, 0x00)
    Name (RN02, 0x00)
    Name (RN03, 0x00)
    Name (RN04, 0x00)
    Name (RN05, 0x00)
    Name (RN06, 0x00)
    Name (X104, 0x01)
    Name (X114, 0x01)
    Name (X127, 0x01)
    Name (X128, 0x01)
    Name (X131, 0x01)
    Name (X132, 0x01)
    Name (X133, 0x01)
    Name (X153, 0x01)
    Name (X170, 0x01)
    Name (X191, 0x01)
    Name (X192, 0x01)
    Name (X193, 0x01)
    Name (X194, 0x01)
    Name (X195, 0x00)
    Name (FLG9, 0x00)
    Name (RUN4, 0x00)
    Name (REL0, 0x16)
    Name (SETN, 0x05)
    Method (SET2, 1, Serialized)
    {
        Store (Arg0, Local0)
        Switch (ToInteger (Local0))
        {
            Case (0x00)
            {
                Store (0x00, Y135) /* \Y135 */
                Store (0x01, Y900) /* \Y900 */
                Store (0x00, Y901) /* \Y901 */
                Store (0x01, FLG9) /* \FLG9 */
                Store (0x00, Y263) /* \Y263 */
                Store (0x00, Y275) /* \Y275 */
                Store (0x00, Y276) /* \Y276 */
            }
            Case (0x01)
            {
                Store (0x01, Y135) /* \Y135 */
                Store (0x00, Y900) /* \Y900 */
                Store (0x00, Y901) /* \Y901 */
                Store (0x01, FLG9) /* \FLG9 */
                Store (0x00, Y263) /* \Y263 */
                Store (0x00, Y275) /* \Y275 */
                Store (0x00, Y276) /* \Y276 */
            }
            Case (0x02)
            {
                Store (0x00, Y135) /* \Y135 */
                Store (0x00, Y900) /* \Y900 */
                Store (0x01, Y901) /* \Y901 */
                Store (0x00, FLG9) /* \FLG9 */
                Store (0x00, Y263) /* \Y263 */
                Store (0x00, Y275) /* \Y275 */
                Store (0x00, Y276) /* \Y276 */
            }
            Case (0x03)
            {
                Store (0x00, Y135) /* \Y135 */
                Store (0x01, Y900) /* \Y900 */
                Store (0x00, Y901) /* \Y901 */
                Store (0x01, FLG9) /* \FLG9 */
                Store (0x01, Y263) /* \Y263 */
                Store (0x00, Y275) /* \Y275 */
                Store (0x00, Y276) /* \Y276 */
                Store (0x00, Y262) /* \Y262 */
            }
            Case (0x04)
            {
                Store (0x00, Y135) /* \Y135 */
                Store (0x01, Y900) /* \Y900 */
                Store (0x00, Y901) /* \Y901 */
                Store (0x01, FLG9) /* \FLG9 */
                Store (0x01, Y263) /* \Y263 */
                Store (0x01, Y275) /* \Y275 */
                Store (0x01, Y276) /* \Y276 */
                Store (0x00, Y262) /* \Y262 */
                Store (0x00, Y251) /* \Y251 */
                Store (0x00, Y300) /* \Y300 */
            }
            Case (0x05)
            {
                Store (0x00, Y135) /* \Y135 */
                Store (0x01, Y900) /* \Y900 */
                Store (0x01, Y901) /* \Y901 */
                Store (0x01, FLG9) /* \FLG9 */
                Store (0x01, Y263) /* \Y263 */
                Store (0x01, Y275) /* \Y275 */
                Store (0x01, Y276) /* \Y276 */
                Store (0x01, Y262) /* \Y262 */
                Store (0x00, Y251) /* \Y251 */
                Store (0x00, Y300) /* \Y300 */
            }
            Case (0x06)
            {
                Store (0x00, Y135) /* \Y135 */
                Store (0x01, Y900) /* \Y900 */
                Store (0x00, Y901) /* \Y901 */
                Store (0x01, FLG9) /* \FLG9 */
                Store (0x01, Y263) /* \Y263 */
                Store (0x01, Y275) /* \Y275 */
                Store (0x01, Y276) /* \Y276 */
                Store (0x01, Y262) /* \Y262 */
                Store (0x01, Y251) /* \Y251 */
                Store (0x01, Y300) /* \Y300 */
                Store (0x00, Y902) /* \Y902 */
            }

        }

        If (LNot (RUN4))
        {
            Concatenate ("Release of parent ACPICA code 0x", Revision, Debug)
            Concatenate ("Release of ASLTS test suite  0x", REL0, Debug)
            Concatenate ("Settings of ASLTS test suite 0x", Arg0, Debug)
        }
    }

    Name (Z063, 0x3F)
    Name (EXC0, 0x00)
    Name (EXC1, 0x00)
    Name (EX00, 0x00)
    Name (EX01, "")
    Name (EX04, 0x00)
    Name (EX05, "")
    Name (EX0D, 0xFD)
    Name (EX0E, 0xFE)
    Name (EX0F, 0xFF)
    Name (PF00, Package (0x57)
    {
        Package (0x03)
        {
            0x00, 
            0x00, 
            "AE_OK"
        }, 

        Package (0x03)
        {
            0x01, 
            0x01, 
            "AE_ERROR"
        }, 

        Package (0x03)
        {
            0x02, 
            0x02, 
            "AE_NO_ACPI_TABLES"
        }, 

        Package (0x03)
        {
            0x03, 
            0x03, 
            "AE_NO_NAMESPACE"
        }, 

        Package (0x03)
        {
            0x04, 
            0x04, 
            "AE_NO_MEMORY"
        }, 

        Package (0x03)
        {
            0x05, 
            0x05, 
            "AE_NOT_FOUND"
        }, 

        Package (0x03)
        {
            0x06, 
            0x06, 
            "AE_NOT_EXIST"
        }, 

        Package (0x03)
        {
            0x07, 
            0x07, 
            "AE_ALREADY_EXISTS"
        }, 

        Package (0x03)
        {
            0x08, 
            0x08, 
            "AE_TYPE"
        }, 

        Package (0x03)
        {
            0x09, 
            0x09, 
            "AE_NULL_OBJECT"
        }, 

        Package (0x03)
        {
            0x0A, 
            0x0A, 
            "AE_NULL_ENTRY"
        }, 

        Package (0x03)
        {
            0x0B, 
            0x0B, 
            "AE_BUFFER_OVERFLOW"
        }, 

        Package (0x03)
        {
            0x0C, 
            0x0C, 
            "AE_STACK_OVERFLOW"
        }, 

        Package (0x03)
        {
            0x0D, 
            0x0D, 
            "AE_STACK_UNDERFLOW"
        }, 

        Package (0x03)
        {
            0x0E, 
            0x0E, 
            "AE_NOT_IMPLEMENTED"
        }, 

        Package (0x03)
        {
            0x0F, 
            0x0F, 
            "AE_VERSION_MISMATCH"
        }, 

        Package (0x03)
        {
            0x10, 
            0x0F, 
            "AE_SUPPORT"
        }, 

        Package (0x03)
        {
            0x11, 
            0x11, 
            "AE_SHARE"
        }, 

        Package (0x03)
        {
            0x12, 
            0x10, 
            "AE_LIMIT"
        }, 

        Package (0x03)
        {
            0x13, 
            0x11, 
            "AE_TIME"
        }, 

        Package (0x03)
        {
            0x14, 
            0x14, 
            "AE_UNKNOWN_STATUS"
        }, 

        Package (0x03)
        {
            0x15, 
            0x12, 
            "AE_ACQUIRE_DEADLOCK"
        }, 

        Package (0x03)
        {
            0x16, 
            0x13, 
            "AE_RELEASE_DEADLOCK"
        }, 

        Package (0x03)
        {
            0x17, 
            0x14, 
            "AE_NOT_ACQUIRED"
        }, 

        Package (0x03)
        {
            0x18, 
            0x15, 
            "AE_ALREADY_ACQUIRED"
        }, 

        Package (0x03)
        {
            0x19, 
            0x16, 
            "AE_NO_HARDWARE_RESPONSE"
        }, 

        Package (0x03)
        {
            0x1A, 
            0x17, 
            "AE_NO_GLOBAL_LOCK"
        }, 

        Package (0x03)
        {
            0x1B, 
            0x18, 
            "AE_ABORT_METHOD"
        }, 

        Package (0x03)
        {
            0x1C, 
            0x1001, 
            "AE_BAD_PARAMETER"
        }, 

        Package (0x03)
        {
            0x1D, 
            0x1002, 
            "AE_BAD_CHARACTER"
        }, 

        Package (0x03)
        {
            0x1E, 
            0x1003, 
            "AE_BAD_PATHNAME"
        }, 

        Package (0x03)
        {
            0x1F, 
            0x1004, 
            "AE_BAD_DATA"
        }, 

        Package (0x03)
        {
            0x20, 
            0x1005, 
            "AE_BAD_ADDRESS"
        }, 

        Package (0x03)
        {
            0x21, 
            0x1006, 
            "AE_ALIGNMENT"
        }, 

        Package (0x03)
        {
            0x22, 
            0x1005, 
            "AE_BAD_HEX_CONSTANT"
        }, 

        Package (0x03)
        {
            0x23, 
            0x1006, 
            "AE_BAD_OCTAL_CONSTANT"
        }, 

        Package (0x03)
        {
            0x24, 
            0x1007, 
            "AE_BAD_DECIMAL_CONSTANT"
        }, 

        Package (0x03)
        {
            0x25, 
            0x2001, 
            "AE_BAD_SIGNATURE"
        }, 

        Package (0x03)
        {
            0x26, 
            0x2002, 
            "AE_BAD_HEADER"
        }, 

        Package (0x03)
        {
            0x27, 
            0x2003, 
            "AE_BAD_CHECKSUM"
        }, 

        Package (0x03)
        {
            0x28, 
            0x2004, 
            "AE_BAD_VALUE"
        }, 

        Package (0x03)
        {
            0x29, 
            0x2005, 
            "AE_TABLE_NOT_SUPPORTED"
        }, 

        Package (0x03)
        {
            0x2A, 
            0x2005, 
            "AE_INVALID_TABLE_LENGTH"
        }, 

        Package (0x03)
        {
            0x2B, 
            0x3001, 
            "AE_AML_ERROR"
        }, 

        Package (0x03)
        {
            0x2C, 
            0x3002, 
            "AE_AML_PARSE"
        }, 

        Package (0x03)
        {
            0x2D, 
            0x3001, 
            "AE_AML_BAD_OPCODE"
        }, 

        Package (0x03)
        {
            0x2E, 
            0x3002, 
            "AE_AML_NO_OPERAND"
        }, 

        Package (0x03)
        {
            0x2F, 
            0x3003, 
            "AE_AML_OPERAND_TYPE"
        }, 

        Package (0x03)
        {
            0x30, 
            0x3004, 
            "AE_AML_OPERAND_VALUE"
        }, 

        Package (0x03)
        {
            0x31, 
            0x3005, 
            "AE_AML_UNINITIALIZED_LOCAL"
        }, 

        Package (0x03)
        {
            0x32, 
            0x3006, 
            "AE_AML_UNINITIALIZED_ARG"
        }, 

        Package (0x03)
        {
            0x33, 
            0x3007, 
            "AE_AML_UNINITIALIZED_ELEMENT"
        }, 

        Package (0x03)
        {
            0x34, 
            0x3008, 
            "AE_AML_NUMERIC_OVERFLOW"
        }, 

        Package (0x03)
        {
            0x35, 
            0x3009, 
            "AE_AML_REGION_LIMIT"
        }, 

        Package (0x03)
        {
            0x36, 
            0x300A, 
            "AE_AML_BUFFER_LIMIT"
        }, 

        Package (0x03)
        {
            0x37, 
            0x300B, 
            "AE_AML_PACKAGE_LIMIT"
        }, 

        Package (0x03)
        {
            0x38, 
            0x300C, 
            "AE_AML_DIVIDE_BY_ZERO"
        }, 

        Package (0x03)
        {
            0x39, 
            0x300D, 
            "AE_AML_BAD_NAME"
        }, 

        Package (0x03)
        {
            0x3A, 
            0x300E, 
            "AE_AML_NAME_NOT_FOUND"
        }, 

        Package (0x03)
        {
            0x3B, 
            0x300F, 
            "AE_AML_INTERNAL"
        }, 

        Package (0x03)
        {
            0x3C, 
            0x3010, 
            "AE_AML_INVALID_SPACE_ID"
        }, 

        Package (0x03)
        {
            0x3D, 
            0x3011, 
            "AE_AML_STRING_LIMIT"
        }, 

        Package (0x03)
        {
            0x3E, 
            0x3012, 
            "AE_AML_NO_RETURN_VALUE"
        }, 

        Package (0x03)
        {
            0x3F, 
            0x3014, 
            "AE_AML_NOT_OWNER"
        }, 

        Package (0x03)
        {
            0x40, 
            0x3015, 
            "AE_AML_MUTEX_ORDER"
        }, 

        Package (0x03)
        {
            0x41, 
            0x3016, 
            "AE_AML_MUTEX_NOT_ACQUIRED"
        }, 

        Package (0x03)
        {
            0x42, 
            0x3017, 
            "AE_AML_INVALID_RESOURCE_TYPE"
        }, 

        Package (0x03)
        {
            0x43, 
            0x3018, 
            "AE_AML_INVALID_INDEX"
        }, 

        Package (0x03)
        {
            0x44, 
            0x3019, 
            "AE_AML_REGISTER_LIMIT"
        }, 

        Package (0x03)
        {
            0x45, 
            0x301A, 
            "AE_AML_NO_WHILE"
        }, 

        Package (0x03)
        {
            0x46, 
            0x301B, 
            "AE_AML_ALIGNMENT"
        }, 

        Package (0x03)
        {
            0x47, 
            0x301C, 
            "AE_AML_NO_RESOURCE_END_TAG"
        }, 

        Package (0x03)
        {
            0x48, 
            0x301D, 
            "AE_AML_BAD_RESOURCE_VALUE"
        }, 

        Package (0x03)
        {
            0x49, 
            0x301E, 
            "AE_AML_CIRCULAR_REFERENCE"
        }, 

        Package (0x03)
        {
            0x4A, 
            0x4001, 
            "AE_CTRL_RETURN_VALUE"
        }, 

        Package (0x03)
        {
            0x4B, 
            0x4002, 
            "AE_CTRL_PENDING"
        }, 

        Package (0x03)
        {
            0x4C, 
            0x4003, 
            "AE_CTRL_TERMINATE"
        }, 

        Package (0x03)
        {
            0x4D, 
            0x4004, 
            "AE_CTRL_TRUE"
        }, 

        Package (0x03)
        {
            0x4E, 
            0x4005, 
            "AE_CTRL_FALSE"
        }, 

        Package (0x03)
        {
            0x4F, 
            0x4006, 
            "AE_CTRL_DEPTH"
        }, 

        Package (0x03)
        {
            0x50, 
            0x4007, 
            "AE_CTRL_END"
        }, 

        Package (0x03)
        {
            0x51, 
            0x4008, 
            "AE_CTRL_TRANSFER"
        }, 

        Package (0x03)
        {
            0x52, 
            0x4009, 
            "AE_CTRL_BREAK"
        }, 

        Package (0x03)
        {
            0x53, 
            0x400A, 
            "AE_CTRL_CONTINUE"
        }, 

        Package (0x03)
        {
            0x54, 
            0x3013, 
            "AE_AML_METHOD_LIMIT"
        }, 

        Package (0x03)
        {
            0x55, 
            0x100B, 
            "AE_INDEX_TO_NOT_ATTACHED"
        }, 

        Package (0x03)
        {
            0x56, 
            0x1B, 
            "AE_OWNER_ID_LIMIT"
        }
    })
    Name (EXC2, 0xC8)
    Name (EX02, Package (EXC2, ){})
    Name (EX03, Package (EXC2, ){})
    Method (_ERR, 3, NotSerialized)
    {
        Store (Arg0, EX00) /* \EX00 */
        Store (Arg1, EX01) /* \EX01 */
        If (LEqual (EX04, 0x00))
        {
            Store (Arg0, EX04) /* \EX04 */
            Store (Arg1, EX05) /* \EX05 */
        }

        If (MTHR)
        {
            If (LLess (EXC0, EXC2))
            {
                Store (Arg2, Index (EX02, EXC0))
                Store (Arg0, Index (EX03, EXC0))
            }
            Else
            {
                Store ("Maximal number of exceptions exceeded", Debug)
                ERR ("_ERR", Z063, 0x02DF, 0x00, 0x00, EXC0, EXC2)
            }
        }

        Increment (EXC0)
        Increment (EXC1)
        Return (0x00)
    }

    Method (CH02, 0, NotSerialized)
    {
        If (EXC1)
        {
            Concatenate ("Some unexpected exceptions were handled, 0x", EXC1, Local0)
            ERR ("CH02", Z063, 0x02F3, 0x00, 0x00, Local0, 0x00)
        }

        Return (EXC1) /* \EXC1 */
    }

    Method (CH03, 5, NotSerialized)
    {
        Store (0x00, Local7)
        If (EXC0)
        {
            Concatenate ("Unexpected exceptions (count ", EXC0, Local0)
            Concatenate (Local0, "), the last is ", Local1)
            Concatenate (Local1, EX01, Local0)
            Concatenate (Local0, ", ", Local1)
            Concatenate (Local1, EX00, Debug)
            ERR (Arg0, Z063, 0x030B, Arg1, Arg2, Arg3, Arg4)
            Store (EXC0, Local7)
        }

        Store (0x00, EXC0) /* \EXC0 */
        Store (0x00, EX04) /* \EX04 */
        Return (Local7)
    }

    Method (ST16, 1, Serialized)
    {
        Name (EBUF, Buffer (ISZC){})
        Name (RBUF, Buffer (0x04){})
        Store (ToHexString (Arg0), EBUF) /* \ST16.EBUF */
        Mid (EBUF, Subtract (ISZC, 0x04), 0x04, RBUF) /* \ST16.RBUF */
        Return (Concatenate ("0x", ToString (RBUF, Ones)))
    }

    Method (CH04, 7, NotSerialized)
    {
        Store (0x00, Local5)
        If (LEqual (Arg2, 0xFF))
        {
            If (LEqual (EXC0, 0x00))
            {
                Store (0x01, Local5)
                Store ("ERROR: No ANY exception has arisen.", Debug)
            }
        }
        Else
        {
            Store (DerefOf (Index (PF00, Arg2)), Local2)
            Store (DerefOf (Index (Local2, 0x01)), Local3)
            Store (DerefOf (Index (Local2, 0x02)), Local4)
            If (LEqual (EXC0, 0x00))
            {
                Store (0x01, Local5)
                Concatenate ("No exception - expected: ", Local4, Local0)
                Concatenate (Local0, "-", Local0)
                Concatenate (Local0, ST16 (Local3), Local0)
                Store (Local0, Debug)
            }
            ElseIf (LAnd (LNot (Arg1), LGreater (EXC0, 0x01)))
            {
                Store (0x01, Local5)
                Concatenate ("More than one exception: 0x", EXC0, Local0)
                Store (Local0, Debug)
            }
            Else
            {
                If (LEqual (Arg1, 0x01))
                {
                    Store (EX04, Local6)
                    Store (EX05, Local7)
                }
                Else
                {
                    Store (EX00, Local6)
                    Store (EX01, Local7)
                }

                If (LNotEqual (Local3, Local6))
                {
                    Store (0x01, Local5)
                    Concatenate ("Exception: ", Local7, Local0)
                    Concatenate (Local0, "-", Local0)
                    Concatenate (Local0, ST16 (Local6), Local0)
                    Concatenate (" differs from expected: ", Local4, Local1)
                    Concatenate (Local0, Local1, Local0)
                    Concatenate (Local0, "-", Local0)
                    Concatenate (Local0, ST16 (Local3), Local0)
                    Store (Local0, Debug)
                }

                If (LNotEqual (Local4, Local7))
                {
                    Store (0x01, Local5)
                    Store ("Unexpected exception:", Debug)
                    Store (Concatenate ("Expected: ", Local4), Debug)
                    Store (Concatenate ("Received: ", Local7), Debug)
                }
            }
        }

        Store (0x00, EXC0) /* \EXC0 */
        Store (0x00, EX04) /* \EX04 */
        If (Local5)
        {
            ERR (Arg0, Z063, 0x038A, Arg3, Arg4, Arg5, Arg6)
        }

        Return (Local5)
    }

    Method (CH05, 0, NotSerialized)
    {
        Return (CH03 ("CH05", 0x00, 0x0392, 0x00, 0x00))
    }

    Method (CH06, 3, NotSerialized)
    {
        If (EXCV)
        {
            Return (CH04 (Arg0, 0x00, Arg2, 0x00, 0x0399, 0x00, 0x00))
        }
        Else
        {
            Return (CH04 (Arg0, 0x00, 0xFF, 0x00, 0x039F, 0x00, 0x00))
        }
    }

    Method (CH07, 7, NotSerialized)
    {
        If (SLCK)
        {
            CH03 (Arg0, Arg3, 0x03AA, 0x00, Arg6)
        }
        Else
        {
            CH04 (Arg0, Arg1, Arg2, Arg3, 0x03AE, Arg5, Arg6)
        }
    }

    Method (MSG0, 2, NotSerialized)
    {
        Concatenate ("THREAD ID ", Arg0, Local0)
        Concatenate (Local0, ": ", Local1)
        Concatenate (Local1, Arg1, Local0)
        Store (Local0, Debug)
    }

    Method (MTEX, 1, NotSerialized)
    {
        Store (Package (0x02)
            {
                0x00, 
                0x00
            }, Local2)
        Store (0x00, Local3)
        Store (EXC0, Local4)
        Store (0x00, Local5)
        While (Local4)
        {
            Store (DerefOf (Index (EX02, Local5)), Local0)
            If (LEqual (Local0, Arg0))
            {
                Store (DerefOf (Index (EX03, Local5)), Local1)
                If (LEqual (Local3, 0x00))
                {
                    Store (Local1, Index (Local2, 0x00))
                }

                Increment (Local3)
                Store (0x00, Index (EX02, Local5))
            }

            Decrement (Local4)
            Increment (Local5)
        }

        Store (Local3, Index (Local2, 0x01))
        Return (Local2)
    }

    Method (CH08, 6, NotSerialized)
    {
        Store (MTEX (Arg1), Local2)
        Store (DerefOf (Index (Local2, 0x00)), Local3)
        Store (DerefOf (Index (Local2, 0x01)), Local4)
        Store (0x00, Local7)
        If (Local4)
        {
            Concatenate ("Unexpected exception 0x", Local3, Local0)
            Concatenate (Local0, ", number of exceptions 0x", Local1)
            Concatenate (Local1, Local4, Local0)
            MSG0 (Arg1, Local0)
            ERR (Arg0, Z063, 0x040D, Arg2, Arg3, Arg4, Arg5)
            Store (0x01, Local7)
        }

        Return (Local4)
    }

    Method (CH09, 6, NotSerialized)
    {
        Store (MTEX (Arg1), Local7)
        Store (DerefOf (Index (Local7, 0x00)), Local6)
        Store (DerefOf (Index (Local7, 0x01)), Local7)
        Store (0x00, Local5)
        If (LEqual (Arg2, 0xFF))
        {
            If (LEqual (Local7, 0x00))
            {
                Store (0x01, Local5)
                MSG0 (Arg1, "ERROR: No ANY exception has arisen.")
            }
        }
        Else
        {
            Store (DerefOf (Index (PF00, Arg2)), Local2)
            Store (DerefOf (Index (Local2, 0x01)), Local3)
            Store (DerefOf (Index (Local2, 0x02)), Local4)
            If (LEqual (Local7, 0x00))
            {
                Store (0x01, Local5)
                Concatenate ("No exception has arisen, expected: ", Local4, Local0)
                Concatenate (", opcode 0x", Local3, Local1)
                Concatenate (Local0, Local1, Local0)
                MSG0 (Arg1, Local0)
            }
            ElseIf (LAnd (Arg0, LGreater (Local7, 0x01)))
            {
                Store (0x01, Local5)
                Concatenate ("More than one exception has arisen: 0x", Local7, Local0)
                MSG0 (Arg1, Local0)
            }
            ElseIf (LNotEqual (Local3, Local6))
            {
                Store (0x01, Local5)
                Concatenate ("The exception 0x", Local6, Local0)
                Concatenate (Local0, " differs from expected ", Local1)
                Concatenate (Local1, ST16 (Local3), Local0)
                MSG0 (Arg1, Local0)
            }
        }

        If (Local5)
        {
            ERR ("CH09", Z063, 0x045E, Arg3, Arg4, 0x00, 0x00)
        }

        Store (Local7, Arg5)
        Return (Local5)
    }

    Method (CH0A, 0, NotSerialized)
    {
        Store (0x00, EXC0) /* \EXC0 */
    }

    Name (Z173, 0xAD)
    Method (DVF2, 0, Serialized)
    {
        Name (TS, "dvf2")
        Device (D000)
        {
            Name (I000, 0x01)
        }

        Method (M001, 0, NotSerialized)
        {
            Method (M002, 0, NotSerialized)
            {
                Method (M003, 0, NotSerialized)
                {
                    Return (0xABCD0000)
                }

                Return (Add (\DVF2.D000.I000, M003 ()))
            }

            Return (Add (\DVF2.D000.I000, M002 ()))
        }

        Store (Add (\DVF2.D000.I000, M001 ()), Local0)
        If (LNotEqual (Local0, 0xABCD0003))
        {
            ERR (TS, Z173, 0x39, 0x00, 0x00, Local0, 0xABCD0003)
        }
    }

    Method (MF26, 0, Serialized)
    {
        Name (TS, "mf26")
        Name (I000, 0xABCD0000)
        Name (I001, 0xABCD0001)
        Name (I002, 0xABCD0002)
        Name (I003, 0xABCD0003)
        Name (II00, 0x11112222)
        Name (P000, Package (0x06)
        {
            I000, , 
            I001, , 
            I002, , 
            "i000", 
            \MF26.I003, , 
            0xABCD0004
        })
        Method (M001, 2, NotSerialized)
        {
            Store (DerefOf (Index (Arg0, 0x00)), Local0)
            If (LNotEqual (Local0, 0xABCD0000))
            {
                ERR (TS, Z164, 0x5A, 0x00, 0x00, Local0, 0xABCD0000)
            }

            Store (DerefOf (Index (Arg0, 0x01)), Local0)
            If (LNotEqual (Local0, 0xABCD0001))
            {
                ERR (TS, Z164, 0x5E, 0x00, 0x00, Local0, 0xABCD0001)
            }

            Store (DerefOf (Index (Arg0, 0x02)), Local0)
            If (LNotEqual (Local0, 0xABCD0002))
            {
                ERR (TS, Z164, 0x62, 0x00, 0x00, Local0, 0xABCD0002)
            }

            Store (DerefOf (Index (Arg0, 0x03)), Local0)
            If (LNotEqual (Local0, "i000"))
            {
                ERR (TS, Z164, 0x66, 0x00, 0x00, Local0, "i000")
            }

            Store (DerefOf (Index (Arg0, 0x04)), Local0)
            If (LNotEqual (Local0, 0xABCD0003))
            {
                ERR (TS, Z164, 0x6A, 0x00, 0x00, Local0, 0xABCD0003)
            }

            Store (DerefOf (Index (Arg0, 0x05)), Local0)
            If (LNotEqual (Local0, 0xABCD0004))
            {
                ERR (TS, Z164, 0x6E, 0x00, 0x00, Local0, 0xABCD0004)
            }

            Store (II00, Index (Arg0, 0x00))
            Store (DerefOf (Index (Arg0, 0x00)), Local0)
            If (LNotEqual (Local0, 0x11112222))
            {
                ERR (TS, Z164, 0x75, 0x00, 0x00, Local0, 0x11112222)
            }
        }

        M001 (P000, RefOf (P000))
        Store (DerefOf (Index (P000, 0x00)), Local0)
        If (LNotEqual (Local0, 0x11112222))
        {
            ERR (TS, Z164, 0x7D, 0x00, 0x00, Local0, 0x11112222)
        }

        Store (DerefOf (Index (P000, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z164, 0x82, 0x00, 0x00, Local0, 0xABCD0001)
        }

        Store (DerefOf (Index (P000, 0x02)), Local0)
        If (LNotEqual (Local0, 0xABCD0002))
        {
            ERR (TS, Z164, 0x87, 0x00, 0x00, Local0, 0xABCD0002)
        }

        Store (DerefOf (Index (P000, 0x03)), Local0)
        If (LNotEqual (Local0, "i000"))
        {
            ERR (TS, Z164, 0x8C, 0x00, 0x00, Local0, "i000")
        }

        Store (DerefOf (Index (P000, 0x04)), Local0)
        If (LNotEqual (Local0, 0xABCD0003))
        {
            ERR (TS, Z164, 0x91, 0x00, 0x00, Local0, 0xABCD0003)
        }

        Store (DerefOf (Index (P000, 0x05)), Local0)
        If (LNotEqual (Local0, 0xABCD0004))
        {
            ERR (TS, Z164, 0x96, 0x00, 0x00, Local0, 0xABCD0004)
        }
    }

    Name (Z170, 0xAA)
    Processor (PR7D, 0x00, 0x00000000, 0x08)
    {
        Name (IY07, 0xABCD0120)
    }

    Method (MT00, 0, Serialized)
    {
        Name (TS, "mt00")
        Name (I000, 0x00)
        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Method (MM08, 0, NotSerialized)
                                        {
                                            Method (MM09, 0, NotSerialized)
                                            {
                                                Method (MM0A, 0, NotSerialized)
                                                {
                                                    Method (MM0B, 0, NotSerialized)
                                                    {
                                                        OUTC ("Max")
                                                        Store (0xABCD0000, I000) /* \MT00.I000 */
                                                    }

                                                    MM0B ()
                                                }

                                                MM0A ()
                                            }

                                            MM09 ()
                                        }

                                        MM08 ()
                                    }

                                    MM07 ()
                                }

                                MM06 ()
                            }

                            MM05 ()
                        }

                        MM04 ()
                    }

                    MM03 ()
                }

                MM02 ()
            }

            MM01 ()
        }

        CH03 (TS, Z170, 0x0100, 0x65, 0x00)
        MM00 ()
        If (LNotEqual (I000, 0xABCD0000))
        {
            ERR (TS, Z170, 0x6A, 0x00, 0x00, I000, 0xABCD0000)
        }

        CH03 (TS, Z170, 0x0101, 0x6D, 0x00)
    }

    Method (MT01, 0, Serialized)
    {
        Name (TS, "mt01")
        Name (I000, 0x00)
        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Method (MM08, 0, NotSerialized)
                                        {
                                            Method (MM09, 0, NotSerialized)
                                            {
                                                Method (MM0A, 0, NotSerialized)
                                                {
                                                    Method (MM0B, 0, NotSerialized)
                                                    {
                                                        Method (MM0C, 0, NotSerialized)
                                                        {
                                                            Method (MM0D, 0, NotSerialized)
                                                            {
                                                                Method (MM0E, 0, NotSerialized)
                                                                {
                                                                    Method (MM0F, 0, NotSerialized)
                                                                    {
                                                                        Method (MM10, 0, NotSerialized)
                                                                        {
                                                                            Method (MM11, 0, NotSerialized)
                                                                            {
                                                                                Method (MM12, 0, NotSerialized)
                                                                                {
                                                                                    Method (MM13, 0, NotSerialized)
                                                                                    {
                                                                                        Method (MM14, 0, NotSerialized)
                                                                                        {
                                                                                            Method (MM15, 0, NotSerialized)
                                                                                            {
                                                                                                Method (MM16, 0, NotSerialized)
                                                                                                {
                                                                                                    Method (MM17, 0, NotSerialized)
                                                                                                    {
                                                                                                        Method (MM18, 0, NotSerialized)
                                                                                                        {
                                                                                                            Method (MM19, 0, NotSerialized)
                                                                                                            {
                                                                                                                Method (MM1A, 0, NotSerialized)
                                                                                                                {
                                                                                                                    Method (MM1B, 0, NotSerialized)
                                                                                                                    {
                                                                                                                        Method (MM1C, 0, NotSerialized)
                                                                                                                        {
                                                                                                                            Method (MM1D, 0, NotSerialized)
                                                                                                                            {
                                                                                                                                Method (MM1E, 0, NotSerialized)
                                                                                                                                {
                                                                                                                                    Method (MM1F, 0, NotSerialized)
                                                                                                                                    {
                                                                                                                                        OUTC ("Max")
                                                                                                                                        Store (0xABCD0000, I000) /* \MT01.I000 */
                                                                                                                                    }

                                                                                                                                    MM1F ()
                                                                                                                                }

                                                                                                                                MM1E ()
                                                                                                                            }

                                                                                                                            MM1D ()
                                                                                                                        }

                                                                                                                        MM1C ()
                                                                                                                    }

                                                                                                                    MM1B ()
                                                                                                                }

                                                                                                                MM1A ()
                                                                                                            }

                                                                                                            MM19 ()
                                                                                                        }

                                                                                                        MM18 ()
                                                                                                    }

                                                                                                    MM17 ()
                                                                                                }

                                                                                                MM16 ()
                                                                                            }

                                                                                            MM15 ()
                                                                                        }

                                                                                        MM14 ()
                                                                                    }

                                                                                    MM13 ()
                                                                                }

                                                                                MM12 ()
                                                                            }

                                                                            MM11 ()
                                                                        }

                                                                        MM10 ()
                                                                    }

                                                                    MM0F ()
                                                                }

                                                                MM0E ()
                                                            }

                                                            MM0D ()
                                                        }

                                                        MM0C ()
                                                    }

                                                    MM0B ()
                                                }

                                                MM0A ()
                                            }

                                            MM09 ()
                                        }

                                        MM08 ()
                                    }

                                    MM07 ()
                                }

                                MM06 ()
                            }

                            MM05 ()
                        }

                        MM04 ()
                    }

                    MM03 ()
                }

                MM02 ()
            }

            MM01 ()
        }

        CH03 (TS, Z170, 0x0102, 0xFC, 0x00)
        MM00 ()
        If (LNotEqual (I000, 0xABCD0000))
        {
            ERR (TS, Z170, 0x0101, 0x00, 0x00, I000, 0xABCD0000)
        }

        CH03 (TS, Z170, 0x0103, 0x0104, 0x00)
    }

    Method (MT02, 0, Serialized)
    {
        Name (TS, "mt02")
        Name (I000, 0x00)
        Method (MM00, 0, NotSerialized)
        {
            MM01 ()
        }

        Method (MM01, 0, NotSerialized)
        {
            MM02 ()
        }

        Method (MM02, 0, NotSerialized)
        {
            MM03 ()
        }

        Method (MM03, 0, NotSerialized)
        {
            MM04 ()
        }

        Method (MM04, 0, NotSerialized)
        {
            MM05 ()
        }

        Method (MM05, 0, NotSerialized)
        {
            MM06 ()
        }

        Method (MM06, 0, NotSerialized)
        {
            MM07 ()
        }

        Method (MM07, 0, NotSerialized)
        {
            MM08 ()
        }

        Method (MM08, 0, NotSerialized)
        {
            MM09 ()
        }

        Method (MM09, 0, NotSerialized)
        {
            MM0A ()
        }

        Method (MM0A, 0, NotSerialized)
        {
            MM0B ()
        }

        Method (MM0B, 0, NotSerialized)
        {
            MM0C ()
        }

        Method (MM0C, 0, NotSerialized)
        {
            MM0D ()
        }

        Method (MM0D, 0, NotSerialized)
        {
            MM0E ()
        }

        Method (MM0E, 0, NotSerialized)
        {
            MM0F ()
        }

        Method (MM0F, 0, NotSerialized)
        {
            OUTC ("Max")
            Store (0xABCD0000, I000) /* \MT02.I000 */
        }

        CH03 (TS, Z170, 0x0104, 0x0152, 0x00)
        MM00 ()
        If (LNotEqual (I000, 0xABCD0000))
        {
            ERR (TS, Z170, 0x0157, 0x00, 0x00, I000, 0xABCD0000)
        }

        CH03 (TS, Z170, 0x0105, 0x015A, 0x00)
    }

    Method (MT03, 0, Serialized)
    {
        Name (TS, "mt03")
        Name (I000, 0x00)
        Method (MM00, 0, NotSerialized)
        {
            MM01 ()
        }

        Method (MM01, 0, NotSerialized)
        {
            MM02 ()
        }

        Method (MM02, 0, NotSerialized)
        {
            MM03 ()
        }

        Method (MM03, 0, NotSerialized)
        {
            MM04 ()
        }

        Method (MM04, 0, NotSerialized)
        {
            MM05 ()
        }

        Method (MM05, 0, NotSerialized)
        {
            MM06 ()
        }

        Method (MM06, 0, NotSerialized)
        {
            MM07 ()
        }

        Method (MM07, 0, NotSerialized)
        {
            MM08 ()
        }

        Method (MM08, 0, NotSerialized)
        {
            MM09 ()
        }

        Method (MM09, 0, NotSerialized)
        {
            MM0A ()
        }

        Method (MM0A, 0, NotSerialized)
        {
            MM0B ()
        }

        Method (MM0B, 0, NotSerialized)
        {
            MM0C ()
        }

        Method (MM0C, 0, NotSerialized)
        {
            MM0D ()
        }

        Method (MM0D, 0, NotSerialized)
        {
            MM0E ()
        }

        Method (MM0E, 0, NotSerialized)
        {
            MM0F ()
        }

        Method (MM0F, 0, NotSerialized)
        {
            MM10 ()
        }

        Method (MM10, 0, NotSerialized)
        {
            MM11 ()
        }

        Method (MM11, 0, NotSerialized)
        {
            MM12 ()
        }

        Method (MM12, 0, NotSerialized)
        {
            MM13 ()
        }

        Method (MM13, 0, NotSerialized)
        {
            MM14 ()
        }

        Method (MM14, 0, NotSerialized)
        {
            MM15 ()
        }

        Method (MM15, 0, NotSerialized)
        {
            MM16 ()
        }

        Method (MM16, 0, NotSerialized)
        {
            MM17 ()
        }

        Method (MM17, 0, NotSerialized)
        {
            MM18 ()
        }

        Method (MM18, 0, NotSerialized)
        {
            MM19 ()
        }

        Method (MM19, 0, NotSerialized)
        {
            MM1A ()
        }

        Method (MM1A, 0, NotSerialized)
        {
            MM1B ()
        }

        Method (MM1B, 0, NotSerialized)
        {
            MM1C ()
        }

        Method (MM1C, 0, NotSerialized)
        {
            MM1D ()
        }

        Method (MM1D, 0, NotSerialized)
        {
            MM1E ()
        }

        Method (MM1E, 0, NotSerialized)
        {
            MM1F ()
        }

        Method (MM1F, 0, NotSerialized)
        {
            OUTC ("Max")
            Store (0xABCD0000, I000) /* \MT03.I000 */
        }

        CH03 (TS, Z170, 0x0106, 0x01E9, 0x00)
        MM00 ()
        If (LNotEqual (I000, 0xABCD0000))
        {
            ERR (TS, Z170, 0x01EE, 0x00, 0x00, I000, 0xABCD0000)
        }

        CH03 (TS, Z170, 0x0107, 0x01F1, 0x00)
    }

    Method (MT04, 0, Serialized)
    {
        Name (TS, "mt04")
        Device (DZ05)
        {
            Name (IY07, 0xABCD0100)
        }

        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Increment (\MT04.DZ05.IY07)
                                        Store (\MT04.DZ05.IY07, Local0)
                                        OUTC ("mt04,   \\mt04.dz05.iy07:")
                                        OUTC (Local0)
                                        If (LNotEqual (Local0, 0xABCD0109))
                                        {
                                            ERR (TS, Z170, 0x0215, 0x00, 0x00, Local0, 0xABCD0109)
                                        }

                                        If (LNotEqual (\MT04.DZ05.IY07, 0xABCD0109))
                                        {
                                            ERR (TS, Z170, 0x0218, 0x00, 0x00, \MT04.DZ05.IY07, 0xABCD0109)
                                        }
                                    }

                                    Increment (\MT04.DZ05.IY07)
                                    MM07 ()
                                }

                                Increment (\MT04.DZ05.IY07)
                                MM06 ()
                            }

                            Increment (\MT04.DZ05.IY07)
                            MM05 ()
                        }

                        Increment (\MT04.DZ05.IY07)
                        MM04 ()
                    }

                    Increment (\MT04.DZ05.IY07)
                    MM03 ()
                }

                Increment (\MT04.DZ05.IY07)
                MM02 ()
            }

            Increment (\MT04.DZ05.IY07)
            MM01 ()
        }

        CH03 (TS, Z170, 0x06, 0x0231, 0x00)
        Increment (\MT04.DZ05.IY07)
        MM00 ()
        If (LNotEqual (\MT04.DZ05.IY07, 0xABCD0109))
        {
            ERR (TS, Z170, 0x0238, 0x00, 0x00, \MT04.DZ05.IY07, 0xABCD0109)
        }

        CH03 (TS, Z170, 0x08, 0x023B, 0x00)
    }

    Method (MT05, 0, Serialized)
    {
        Name (TS, "mt05")
        Device (DZ05)
        {
            Name (IY07, 0xABCD0200)
        }

        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Method (MM08, 0, NotSerialized)
                                        {
                                            Method (MM09, 0, NotSerialized)
                                            {
                                                Method (MM0A, 0, NotSerialized)
                                                {
                                                    Method (MM0B, 0, NotSerialized)
                                                    {
                                                        Method (MM0C, 0, NotSerialized)
                                                        {
                                                            Method (MM0D, 0, NotSerialized)
                                                            {
                                                                Method (MM0E, 0, NotSerialized)
                                                                {
                                                                    Method (MM0F, 0, NotSerialized)
                                                                    {
                                                                        Increment (\MT05.DZ05.IY07)
                                                                        Store (\MT05.DZ05.IY07, Local0)
                                                                        OUTC ("mt05,   \\mt05.dz05.iy07:")
                                                                        OUTC (Local0)
                                                                        If (LNotEqual (Local0, 0xABCD0211))
                                                                        {
                                                                            ERR (TS, Z170, 0x026F, 0x00, 0x00, Local0, 0xABCD0211)
                                                                        }

                                                                        If (LNotEqual (\MT05.DZ05.IY07, 0xABCD0211))
                                                                        {
                                                                            ERR (TS, Z170, 0x0272, 0x00, 0x00, \MT05.DZ05.IY07, 0xABCD0211)
                                                                        }
                                                                    }

                                                                    Increment (\MT05.DZ05.IY07)
                                                                    MM0F ()
                                                                }

                                                                Increment (\MT05.DZ05.IY07)
                                                                MM0E ()
                                                            }

                                                            Increment (\MT05.DZ05.IY07)
                                                            MM0D ()
                                                        }

                                                        Increment (\MT05.DZ05.IY07)
                                                        MM0C ()
                                                    }

                                                    Increment (\MT05.DZ05.IY07)
                                                    MM0B ()
                                                }

                                                Increment (\MT05.DZ05.IY07)
                                                MM0A ()
                                            }

                                            Increment (\MT05.DZ05.IY07)
                                            MM09 ()
                                        }

                                        Increment (\MT05.DZ05.IY07)
                                        MM08 ()
                                    }

                                    Increment (\MT05.DZ05.IY07)
                                    MM07 ()
                                }

                                Increment (\MT05.DZ05.IY07)
                                MM06 ()
                            }

                            Increment (\MT05.DZ05.IY07)
                            MM05 ()
                        }

                        Increment (\MT05.DZ05.IY07)
                        MM04 ()
                    }

                    Increment (\MT05.DZ05.IY07)
                    MM03 ()
                }

                Increment (\MT05.DZ05.IY07)
                MM02 ()
            }

            Increment (\MT05.DZ05.IY07)
            MM01 ()
        }

        CH03 (TS, Z170, 0x0108, 0x02A3, 0x00)
        Increment (\MT05.DZ05.IY07)
        MM00 ()
        If (LNotEqual (\MT05.DZ05.IY07, 0xABCD0211))
        {
            ERR (TS, Z170, 0x02A9, 0x00, 0x00, \MT05.DZ05.IY07, 0xABCD0211)
        }

        CH03 (TS, Z170, 0x0109, 0x02AC, 0x00)
    }

    Method (MT06, 0, Serialized)
    {
        Name (TS, "mt06")
        Device (DZ05)
        {
            Name (IY07, 0xABCD0300)
        }

        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Method (MM08, 0, NotSerialized)
                                        {
                                            Method (MM09, 0, NotSerialized)
                                            {
                                                Method (MM0A, 0, NotSerialized)
                                                {
                                                    Store (0x11112222, \MT06.DZ05.IY07)
                                                }

                                                MM0A ()
                                            }

                                            MM09 ()
                                        }

                                        MM08 ()
                                    }

                                    MM07 ()
                                }

                                MM06 ()
                            }

                            MM05 ()
                            Store (\MT06.DZ05.IY07, Local0)
                            OUTC ("mt06,   \\mt06.dz05.iy07:")
                            OUTC (Local0)
                            If (LNotEqual (Local0, 0x11112222))
                            {
                                ERR (TS, Z170, 0x02E4, 0x00, 0x00, Local0, 0x11112222)
                            }

                            If (LNotEqual (\MT06.DZ05.IY07, 0x11112222))
                            {
                                ERR (TS, Z170, 0x02E7, 0x00, 0x00, \MT06.DZ05.IY07, 0x11112222)
                            }
                        }

                        MM04 ()
                    }

                    MM03 ()
                }

                MM02 ()
            }

            MM01 ()
        }

        CH03 (TS, Z170, 0x010A, 0x02F3, 0x00)
        MM00 ()
        MT07 ()
        If (LNotEqual (\MT06.DZ05.IY07, 0x11112222))
        {
            ERR (TS, Z170, 0x02FA, 0x00, 0x00, \MT06.DZ05.IY07, 0x11112222)
        }

        CH03 (TS, Z170, 0x010B, 0x02FD, 0x00)
    }

    Method (MT07, 0, Serialized)
    {
        Name (TS, "mt07")
        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Store (\MT06.DZ05.IY07, Local0)
                                        OUTC ("0 mt07,   \\mt06.dz05.iy07:")
                                        OUTC (Local0)
                                        If (LNotEqual (Local0, 0x11112222))
                                        {
                                            ERR (TS, Z170, 0x031F, 0x00, 0x00, Local0, 0x11112222)
                                        }

                                        If (LNotEqual (\MT06.DZ05.IY07, 0x11112222))
                                        {
                                            ERR (TS, Z170, 0x0322, 0x00, 0x00, \MT06.DZ05.IY07, 0x11112222)
                                        }
                                    }

                                    MM07 ()
                                }

                                MM06 ()
                            }

                            MM05 ()
                        }

                        MM04 ()
                    }

                    MM03 ()
                }

                MM02 ()
            }

            MM01 ()
        }

        CH03 (TS, Z170, 0x010C, 0x0334, 0x00)
        MM00 ()
        Store (\MT06.DZ05.IY07, Local0)
        OUTC ("1 mt07,   \\mt06.dz05.iy07:")
        OUTC (Local0)
        If (LNotEqual (Local0, 0x11112222))
        {
            ERR (TS, Z170, 0x033C, 0x00, 0x00, Local0, 0x11112222)
        }

        If (LNotEqual (\MT06.DZ05.IY07, 0x11112222))
        {
            ERR (TS, Z170, 0x033F, 0x00, 0x00, \MT06.DZ05.IY07, 0x11112222)
        }

        CH03 (TS, Z170, 0x010D, 0x0342, 0x00)
    }

    Method (MT08, 0, Serialized)
    {
        Name (TS, "mt08")
        Device (DZ05)
        {
            Name (IY07, 0xABCD0400)
        }

        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Method (MM08, 0, NotSerialized)
                                        {
                                            Method (MM09, 0, NotSerialized)
                                            {
                                                Method (MM0A, 0, NotSerialized)
                                                {
                                                    Method (MM0B, 0, NotSerialized)
                                                    {
                                                        Method (MM0C, 0, NotSerialized)
                                                        {
                                                            Method (MM0D, 0, NotSerialized)
                                                            {
                                                                Method (MM0E, 0, NotSerialized)
                                                                {
                                                                    Method (MM0F, 0, NotSerialized)
                                                                    {
                                                                        Store (0x22223333, \MT08.DZ05.IY07)
                                                                    }

                                                                    MM0F ()
                                                                }

                                                                MM0E ()
                                                            }

                                                            MM0D ()
                                                        }

                                                        MM0C ()
                                                    }

                                                    MM0B ()
                                                }

                                                MM0A ()
                                            }

                                            MM09 ()
                                        }

                                        MM08 ()
                                        Store (\MT08.DZ05.IY07, Local0)
                                        OUTC ("mt08,   \\mt08.dz05.iy07:")
                                        OUTC (Local0)
                                        If (LNotEqual (Local0, 0x22223333))
                                        {
                                            ERR (TS, Z170, 0x0387, 0x00, 0x00, Local0, 0x22223333)
                                        }

                                        If (LNotEqual (\MT08.DZ05.IY07, 0x22223333))
                                        {
                                            ERR (TS, Z170, 0x038A, 0x00, 0x00, \MT08.DZ05.IY07, 0x22223333)
                                        }
                                    }

                                    MM07 ()
                                }

                                MM06 ()
                            }

                            MM05 ()
                        }

                        MM04 ()
                    }

                    MM03 ()
                }

                MM02 ()
            }

            MM01 ()
        }

        CH03 (TS, Z170, 0x010E, 0x039C, 0x00)
        MM00 ()
        MT09 ()
        If (LNotEqual (\MT08.DZ05.IY07, 0x22223333))
        {
            ERR (TS, Z170, 0x03A3, 0x00, 0x00, \MT08.DZ05.IY07, 0x22223333)
        }

        CH03 (TS, Z170, 0x010F, 0x03A6, 0x00)
    }

    Method (MT09, 0, Serialized)
    {
        Name (TS, "mt09")
        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Method (MM08, 0, NotSerialized)
                                        {
                                            Method (MM09, 0, NotSerialized)
                                            {
                                                Method (MM0A, 0, NotSerialized)
                                                {
                                                    Method (MM0B, 0, NotSerialized)
                                                    {
                                                        Method (MM0C, 0, NotSerialized)
                                                        {
                                                            Method (MM0D, 0, NotSerialized)
                                                            {
                                                                Method (MM0E, 0, NotSerialized)
                                                                {
                                                                    Method (MM0F, 0, NotSerialized)
                                                                    {
                                                                        Store (\MT08.DZ05.IY07, Local0)
                                                                        OUTC ("0 mt09,   \\mt08.dz05.iy07:")
                                                                        OUTC (Local0)
                                                                        If (LNotEqual (Local0, 0x22223333))
                                                                        {
                                                                            ERR (TS, Z170, 0x03D6, 0x00, 0x00, Local0, 0x22223333)
                                                                        }

                                                                        If (LNotEqual (\MT08.DZ05.IY07, 0x22223333))
                                                                        {
                                                                            ERR (TS, Z170, 0x03D9, 0x00, 0x00, \MT08.DZ05.IY07, 0x22223333)
                                                                        }
                                                                    }

                                                                    MM0F ()
                                                                }

                                                                MM0E ()
                                                            }

                                                            MM0D ()
                                                        }

                                                        MM0C ()
                                                    }

                                                    MM0B ()
                                                }

                                                MM0A ()
                                            }

                                            MM09 ()
                                        }

                                        MM08 ()
                                    }

                                    MM07 ()
                                }

                                MM06 ()
                            }

                            MM05 ()
                        }

                        MM04 ()
                    }

                    MM03 ()
                }

                MM02 ()
            }

            MM01 ()
        }

        CH03 (TS, Z170, 0x0110, 0x03FB, 0x00)
        MM00 ()
        Store (\MT08.DZ05.IY07, Local0)
        OUTC ("1 mt09,   \\mt08.dz05.iy07:")
        OUTC (Local0)
        If (LNotEqual (Local0, 0x22223333))
        {
            ERR (TS, Z170, 0x0403, 0x00, 0x00, Local0, 0x22223333)
        }

        If (LNotEqual (\MT08.DZ05.IY07, 0x22223333))
        {
            ERR (TS, Z170, 0x0406, 0x00, 0x00, \MT08.DZ05.IY07, 0x22223333)
        }

        CH03 (TS, Z170, 0x0111, 0x0409, 0x00)
    }

    Method (MT0A, 0, Serialized)
    {
        Name (TS, "mt0a")
        CH03 (TS, Z170, 0x0112, 0x0414, 0x00)
        Store (\PR7D.IY07, Local0)
        OUTC ("mt0a,   \\pr7d.iy07:")
        OUTC (Local0)
        If (LNotEqual (\PR7D.IY07, 0xABCD0120))
        {
            ERR (TS, Z170, 0x041A, 0x00, 0x00, \PR7D.IY07, 0xABCD0120)
        }

        CH03 (TS, Z170, 0x0113, 0x041D, 0x00)
    }

    Method (MT0B, 0, Serialized)
    {
        Name (TS, "mt0b")
        CH03 (TS, Z170, 0x0114, 0x0427, 0x00)
        Increment (\PR7D.IY07)
        Store (\PR7D.IY07, Local0)
        OUTC ("mt0b,   \\pr7d.iy07:")
        OUTC (Local0)
        If (LNotEqual (\PR7D.IY07, 0xABCD0121))
        {
            ERR (TS, Z170, 0x042F, 0x00, 0x00, \PR7D.IY07, 0xABCD0121)
        }

        CH03 (TS, Z170, 0x0115, 0x0432, 0x00)
    }

    Method (MT0C, 0, Serialized)
    {
        Name (TS, "mt0c")
        Processor (PR7D, 0x00, 0x00000000, 0x08)
        {
            Name (IY07, 0xABCD0660)
        }

        CH03 (TS, Z170, 0x0116, 0x0442, 0x00)
        Increment (\MT0C.PR7D.IY07)
        Store (\MT0C.PR7D.IY07, Local0)
        OUTC ("mt0c,   \\mt0c.pr7d.iy07:")
        OUTC (Local0)
        If (LNotEqual (\MT0C.PR7D.IY07, 0xABCD0661))
        {
            ERR (TS, Z170, 0x044A, 0x00, 0x00, \MT0C.PR7D.IY07, 0xABCD0661)
        }

        CH03 (TS, Z170, 0x0117, 0x044D, 0x00)
    }

    Method (MT0D, 0, Serialized)
    {
        Name (TS, "mt0d")
        Name (I000, 0xABCD1234)
        CH03 (TS, Z170, 0x0118, 0x0459, 0x00)
        Store (0x00, Local0)
        While (0x01)
        {
            Increment (Local0)
            If (LEqual (Local0, 0x64))
            {
                OUTC ("mt0d,   Local0:")
                OUTC (Local0)
                MT0E ()
                CH03 (TS, Z170, 0x0119, 0x0466, 0x00)
                Return (Zero)
            }
        }

        CH03 (TS, Z170, 0x011A, 0x046C, 0x00)
    }

    Method (MT0E, 0, Serialized)
    {
        Name (TS, "mt0e")
        CH03 (TS, Z170, 0x011B, 0x0476, 0x00)
        Store (\MT0D.I000, Local0)
        OUTC ("mt0e,   \\mt0d.i000:")
        OUTC (Local0)
        If (LNotEqual (\MT0D.I000, 0xABCD1234))
        {
            ERR (TS, Z170, 0x047D, 0x00, 0x00, \MT0D.I000, 0xABCD1234)
        }

        CH03 (TS, Z170, 0x011C, 0x0480, 0x00)
    }

    Method (MT0F, 0, Serialized)
    {
        Name (TS, "mt0f")
        Device (DZ05)
        {
            Name (IY07, 0xABCD0500)
        }

        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Add (\MT0F.DZ05.IY07, 0x01, \MT0F.DZ05.IY07)
                                        Store (\MT0F.DZ05.IY07, Local0)
                                        OUTC ("mt0f,   \\mt0f.dz05.iy07:")
                                        OUTC (Local0)
                                        If (LNotEqual (Local0, 0xABCD0509))
                                        {
                                            ERR (TS, Z170, 0x04A5, 0x00, 0x00, Local0, 0xABCD0509)
                                        }

                                        If (LNotEqual (\MT0F.DZ05.IY07, 0xABCD0509))
                                        {
                                            ERR (TS, Z170, 0x04A8, 0x00, 0x00, \MT0F.DZ05.IY07, 0xABCD0509)
                                        }
                                    }

                                    Add (\MT0F.DZ05.IY07, 0x01, \MT0F.DZ05.IY07)
                                    MM07 ()
                                }

                                Add (\MT0F.DZ05.IY07, 0x01, \MT0F.DZ05.IY07)
                                MM06 ()
                            }

                            Add (\MT0F.DZ05.IY07, 0x01, \MT0F.DZ05.IY07)
                            MM05 ()
                        }

                        Add (\MT0F.DZ05.IY07, 0x01, \MT0F.DZ05.IY07)
                        MM04 ()
                    }

                    Add (\MT0F.DZ05.IY07, 0x01, \MT0F.DZ05.IY07)
                    MM03 ()
                }

                Add (\MT0F.DZ05.IY07, 0x01, \MT0F.DZ05.IY07)
                MM02 ()
            }

            Add (\MT0F.DZ05.IY07, 0x01, \MT0F.DZ05.IY07)
            MM01 ()
        }

        CH03 (TS, Z170, 0x22, 0x04C1, 0x00)
        Add (\MT0F.DZ05.IY07, 0x01, \MT0F.DZ05.IY07)
        MM00 ()
        If (LNotEqual (\MT0F.DZ05.IY07, 0xABCD0509))
        {
            ERR (TS, Z170, 0x04C7, 0x00, 0x00, \MT0F.DZ05.IY07, 0xABCD0509)
        }

        CH03 (TS, Z170, 0x24, 0x04CA, 0x00)
    }

    Method (MT10, 0, Serialized)
    {
        Name (TS, "mt10")
        Device (DZ05)
        {
            Name (IY07, 0xABCD0600)
        }

        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Method (MM08, 0, NotSerialized)
                                        {
                                            Method (MM09, 0, NotSerialized)
                                            {
                                                Method (MM0A, 0, NotSerialized)
                                                {
                                                    Method (MM0B, 0, NotSerialized)
                                                    {
                                                        Method (MM0C, 0, NotSerialized)
                                                        {
                                                            Method (MM0D, 0, NotSerialized)
                                                            {
                                                                Method (MM0E, 0, NotSerialized)
                                                                {
                                                                    Method (MM0F, 0, NotSerialized)
                                                                    {
                                                                        Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                                                                        Store (\MT10.DZ05.IY07, Local0)
                                                                        OUTC ("mt10,   \\mt10.dz05.iy07:")
                                                                        OUTC (Local0)
                                                                        If (LNotEqual (Local0, 0xABCD0611))
                                                                        {
                                                                            ERR (TS, Z170, 0x04FE, 0x00, 0x00, Local0, 0xABCD0611)
                                                                        }

                                                                        If (LNotEqual (\MT10.DZ05.IY07, 0xABCD0611))
                                                                        {
                                                                            ERR (TS, Z170, 0x0501, 0x00, 0x00, \MT10.DZ05.IY07, 0xABCD0611)
                                                                        }
                                                                    }

                                                                    Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                                                                    MM0F ()
                                                                }

                                                                Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                                                                MM0E ()
                                                            }

                                                            Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                                                            MM0D ()
                                                        }

                                                        Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                                                        MM0C ()
                                                    }

                                                    Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                                                    MM0B ()
                                                }

                                                Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                                                MM0A ()
                                            }

                                            Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                                            MM09 ()
                                        }

                                        Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                                        MM08 ()
                                    }

                                    Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                                    MM07 ()
                                }

                                Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                                MM06 ()
                            }

                            Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                            MM05 ()
                        }

                        Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                        MM04 ()
                    }

                    Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                    MM03 ()
                }

                Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
                MM02 ()
            }

            Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
            MM01 ()
        }

        CH03 (TS, Z170, 0x27, 0x0532, 0x00)
        Add (\MT10.DZ05.IY07, 0x01, \MT10.DZ05.IY07)
        MM00 ()
        If (LNotEqual (\MT10.DZ05.IY07, 0xABCD0611))
        {
            ERR (TS, Z170, 0x0538, 0x00, 0x00, \MT10.DZ05.IY07, 0xABCD0611)
        }

        CH03 (TS, Z170, 0x29, 0x053B, 0x00)
    }

    Method (MT11, 0, Serialized)
    {
        Name (TS, "mt11")
        Device (DZ05)
        {
            Name (IY07, 0xABCD0700)
        }

        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Increment (^^^^^^^^DZ05.IY07)
                                        Store (^^^^^^^^DZ05.IY07, Local0)
                                        OUTC ("mt11,   ^^^^^^^^dz05.iy07:")
                                        OUTC (Local0)
                                        If (LNotEqual (Local0, 0xABCD0709))
                                        {
                                            ERR (TS, Z170, 0x055F, 0x00, 0x00, Local0, 0xABCD0709)
                                        }

                                        If (LNotEqual (^^^^^^^^DZ05.IY07, 0xABCD0709))
                                        {
                                            ERR (TS, Z170, 0x0562, 0x00, 0x00, ^^^^^^^^DZ05.IY07, 0xABCD0709)
                                        }
                                    }

                                    Increment (^^^^^^^DZ05.IY07)
                                    MM07 ()
                                }

                                Increment (^^^^^^DZ05.IY07)
                                MM06 ()
                            }

                            Increment (^^^^^DZ05.IY07)
                            MM05 ()
                        }

                        Increment (^^^^DZ05.IY07)
                        MM04 ()
                    }

                    Increment (^^^DZ05.IY07)
                    MM03 ()
                }

                Increment (^^DZ05.IY07)
                MM02 ()
            }

            Increment (^DZ05.IY07)
            MM01 ()
        }

        CH03 (TS, Z170, 0x2C, 0x057B, 0x00)
        Increment (DZ05.IY07)
        MM00 ()
        If (LNotEqual (DZ05.IY07, 0xABCD0709))
        {
            ERR (TS, Z170, 0x0581, 0x00, 0x00, DZ05.IY07, 0xABCD0709)
        }

        CH03 (TS, Z170, 0x2E, 0x0584, 0x00)
    }

    Method (MT12, 0, Serialized)
    {
        Name (TS, "mt12")
        Device (DZ05)
        {
            Name (IY07, 0xABCD0800)
        }

        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Method (MM08, 0, NotSerialized)
                                        {
                                            Method (MM09, 0, NotSerialized)
                                            {
                                                Method (MM0A, 0, NotSerialized)
                                                {
                                                    Method (MM0B, 0, NotSerialized)
                                                    {
                                                        Method (MM0C, 0, NotSerialized)
                                                        {
                                                            Method (MM0D, 0, NotSerialized)
                                                            {
                                                                Method (MM0E, 0, NotSerialized)
                                                                {
                                                                    Method (MM0F, 0, NotSerialized)
                                                                    {
                                                                        Method (MM10, 0, NotSerialized)
                                                                        {
                                                                            Method (MM11, 0, NotSerialized)
                                                                            {
                                                                                Method (MM12, 0, NotSerialized)
                                                                                {
                                                                                    Method (MM13, 0, NotSerialized)
                                                                                    {
                                                                                        Method (MM14, 0, NotSerialized)
                                                                                        {
                                                                                            Method (MM15, 0, NotSerialized)
                                                                                            {
                                                                                                Method (MM16, 0, NotSerialized)
                                                                                                {
                                                                                                    Method (MM17, 0, NotSerialized)
                                                                                                    {
                                                                                                        Method (MM18, 0, NotSerialized)
                                                                                                        {
                                                                                                            Method (MM19, 0, NotSerialized)
                                                                                                            {
                                                                                                                Method (MM1A, 0, NotSerialized)
                                                                                                                {
                                                                                                                    Method (MM1B, 0, NotSerialized)
                                                                                                                    {
                                                                                                                        Method (MM1C, 0, NotSerialized)
                                                                                                                        {
                                                                                                                            Method (MM1D, 0, NotSerialized)
                                                                                                                            {
                                                                                                                                Method (MM1E, 0, NotSerialized)
                                                                                                                                {
                                                                                                                                    Method (MM1F, 0, NotSerialized)
                                                                                                                                    {
                                                                                                                                        Increment (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                                                                        Store (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                                                                        OUTC ("mt12,   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^dz05.iy07:")
                                                                                                                                        OUTC (Local0)
                                                                                                                                        If (LNotEqual (Local0, 0xABCD0821))
                                                                                                                                        {
                                                                                                                                            ERR (TS, Z170, 0x05D8, 0x00, 0x00, Local0, 0xABCD0821)
                                                                                                                                        }

                                                                                                                                        If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD0821))
                                                                                                                                        {
                                                                                                                                            ERR (TS, Z170, 0x05DB, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD0821)
                                                                                                                                        }
                                                                                                                                    }

                                                                                                                                    Increment (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                                                                    MM1F ()
                                                                                                                                }

                                                                                                                                Increment (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                                                                MM1E ()
                                                                                                                            }

                                                                                                                            Increment (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                                                            MM1D ()
                                                                                                                        }

                                                                                                                        Increment (^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                                                        MM1C ()
                                                                                                                    }

                                                                                                                    Increment (^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                                                    MM1B ()
                                                                                                                }

                                                                                                                Increment (^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                                                MM1A ()
                                                                                                            }

                                                                                                            Increment (^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                                            MM19 ()
                                                                                                        }

                                                                                                        Increment (^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                                        MM18 ()
                                                                                                    }

                                                                                                    Increment (^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                                    MM17 ()
                                                                                                }

                                                                                                Increment (^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                                MM16 ()
                                                                                            }

                                                                                            Increment (^^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                            MM15 ()
                                                                                        }

                                                                                        Increment (^^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                        MM14 ()
                                                                                    }

                                                                                    Increment (^^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                    MM13 ()
                                                                                }

                                                                                Increment (^^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                                MM12 ()
                                                                            }

                                                                            Increment (^^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                            MM11 ()
                                                                        }

                                                                        Increment (^^^^^^^^^^^^^^^^DZ05.IY07)
                                                                        MM10 ()
                                                                    }

                                                                    Increment (^^^^^^^^^^^^^^^DZ05.IY07)
                                                                    MM0F ()
                                                                }

                                                                Increment (^^^^^^^^^^^^^^DZ05.IY07)
                                                                MM0E ()
                                                            }

                                                            Increment (^^^^^^^^^^^^^DZ05.IY07)
                                                            MM0D ()
                                                        }

                                                        Increment (^^^^^^^^^^^^DZ05.IY07)
                                                        MM0C ()
                                                    }

                                                    Increment (^^^^^^^^^^^DZ05.IY07)
                                                    MM0B ()
                                                }

                                                Increment (^^^^^^^^^^DZ05.IY07)
                                                MM0A ()
                                            }

                                            Increment (^^^^^^^^^DZ05.IY07)
                                            MM09 ()
                                        }

                                        Increment (^^^^^^^^DZ05.IY07)
                                        MM08 ()
                                    }

                                    Increment (^^^^^^^DZ05.IY07)
                                    MM07 ()
                                }

                                Increment (^^^^^^DZ05.IY07)
                                MM06 ()
                            }

                            Increment (^^^^^DZ05.IY07)
                            MM05 ()
                        }

                        Increment (^^^^DZ05.IY07)
                        MM04 ()
                    }

                    Increment (^^^DZ05.IY07)
                    MM03 ()
                }

                Increment (^^DZ05.IY07)
                MM02 ()
            }

            Increment (^DZ05.IY07)
            MM01 ()
        }

        CH03 (TS, Z170, 0x011D, 0x063C, 0x00)
        Increment (DZ05.IY07)
        MM00 ()
        If (LNotEqual (DZ05.IY07, 0xABCD0821))
        {
            ERR (TS, Z170, 0x0642, 0x00, 0x00, DZ05.IY07, 0xABCD0821)
        }

        CH03 (TS, Z170, 0x011E, 0x0645, 0x00)
    }

    Method (MT13, 0, Serialized)
    {
        Name (TS, "mt13")
        Device (DZ05)
        {
            Name (IY07, 0xABCD0500)
        }

        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Store (\MT13.DZ05.IY07, Local0)
                                    OUTC ("mt13,   \\mt13.dz05.iy07:")
                                    OUTC (Local0)
                                    If (LNotEqual (Local0, 0xABCD0500))
                                    {
                                        ERR (TS, Z170, 0x0666, 0x00, 0x00, Local0, 0xABCD0500)
                                    }

                                    If (LNotEqual (\MT13.DZ05.IY07, 0xABCD0500))
                                    {
                                        ERR (TS, Z170, 0x0669, 0x00, 0x00, \MT13.DZ05.IY07, 0xABCD0500)
                                    }
                                }

                                Store (\MT13.DZ05.IY07, Local0)
                                MM06 ()
                                If (LNotEqual (\MT13.DZ05.IY07, 0xABCD0500))
                                {
                                    ERR (TS, Z170, 0x066F, 0x00, 0x00, \MT13.DZ05.IY07, 0xABCD0500)
                                }
                            }

                            Store (\MT13.DZ05.IY07, Local0)
                            MM05 ()
                            If (LNotEqual (\MT13.DZ05.IY07, 0xABCD0500))
                            {
                                ERR (TS, Z170, 0x0675, 0x00, 0x00, \MT13.DZ05.IY07, 0xABCD0500)
                            }
                        }

                        Store (\MT13.DZ05.IY07, Local0)
                        MM04 ()
                        If (LNotEqual (\MT13.DZ05.IY07, 0xABCD0500))
                        {
                            ERR (TS, Z170, 0x067B, 0x00, 0x00, \MT13.DZ05.IY07, 0xABCD0500)
                        }
                    }

                    Store (\MT13.DZ05.IY07, Local0)
                    MM03 ()
                    If (LNotEqual (\MT13.DZ05.IY07, 0xABCD0500))
                    {
                        ERR (TS, Z170, 0x0681, 0x00, 0x00, \MT13.DZ05.IY07, 0xABCD0500)
                    }
                }

                Store (\MT13.DZ05.IY07, Local0)
                MM02 ()
                If (LNotEqual (\MT13.DZ05.IY07, 0xABCD0500))
                {
                    ERR (TS, Z170, 0x0687, 0x00, 0x00, \MT13.DZ05.IY07, 0xABCD0500)
                }
            }

            Store (\MT13.DZ05.IY07, Local0)
            MM01 ()
            If (LNotEqual (\MT13.DZ05.IY07, 0xABCD0500))
            {
                ERR (TS, Z170, 0x068D, 0x00, 0x00, \MT13.DZ05.IY07, 0xABCD0500)
            }
        }

        CH03 (TS, Z170, 0x3A, 0x0691, 0x00)
        Store (\MT13.DZ05.IY07, Local0)
        MM00 ()
        If (LNotEqual (\MT13.DZ05.IY07, 0xABCD0500))
        {
            ERR (TS, Z170, 0x0697, 0x00, 0x00, \MT13.DZ05.IY07, 0xABCD0500)
        }

        CH03 (TS, Z170, 0x3C, 0x069A, 0x00)
    }

    Method (MT14, 0, Serialized)
    {
        Name (TS, "mt14")
        Device (DZ05)
        {
            Name (IY07, 0xABCD2900)
        }

        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Method (MM08, 0, NotSerialized)
                                        {
                                            Method (MM09, 0, NotSerialized)
                                            {
                                                Method (MM0A, 0, NotSerialized)
                                                {
                                                    Method (MM0B, 0, NotSerialized)
                                                    {
                                                        Method (MM0C, 0, NotSerialized)
                                                        {
                                                            Method (MM0D, 0, NotSerialized)
                                                            {
                                                                Method (MM0E, 0, NotSerialized)
                                                                {
                                                                    Method (MM0F, 0, NotSerialized)
                                                                    {
                                                                        Method (MM10, 0, NotSerialized)
                                                                        {
                                                                            Method (MM11, 0, NotSerialized)
                                                                            {
                                                                                Method (MM12, 0, NotSerialized)
                                                                                {
                                                                                    Method (MM13, 0, NotSerialized)
                                                                                    {
                                                                                        Method (MM14, 0, NotSerialized)
                                                                                        {
                                                                                            Method (MM15, 0, NotSerialized)
                                                                                            {
                                                                                                Method (MM16, 0, NotSerialized)
                                                                                                {
                                                                                                    Method (MM17, 0, NotSerialized)
                                                                                                    {
                                                                                                        Method (MM18, 0, NotSerialized)
                                                                                                        {
                                                                                                            Method (MM19, 0, NotSerialized)
                                                                                                            {
                                                                                                                Method (MM1A, 0, NotSerialized)
                                                                                                                {
                                                                                                                    Method (MM1B, 0, NotSerialized)
                                                                                                                    {
                                                                                                                        Method (MM1C, 0, NotSerialized)
                                                                                                                        {
                                                                                                                            Method (MM1D, 0, NotSerialized)
                                                                                                                            {
                                                                                                                                Method (MM1E, 0, NotSerialized)
                                                                                                                                {
                                                                                                                                    Method (MM1F, 0, NotSerialized)
                                                                                                                                    {
                                                                                                                                        Store (\MT14.DZ05.IY07, Local0)
                                                                                                                                        OUTC ("mt14,   \\mt14.dz05.iy07:")
                                                                                                                                        OUTC (Local0)
                                                                                                                                        If (LNotEqual (Local0, 0xABCD2900))
                                                                                                                                        {
                                                                                                                                            ERR (TS, Z170, 0x06ED, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                                                                        }

                                                                                                                                        If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                                                                        {
                                                                                                                                            ERR (TS, Z170, 0x06F0, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                                                                        }
                                                                                                                                    }

                                                                                                                                    Store (\MT14.DZ05.IY07, Local0)
                                                                                                                                    MM1F ()
                                                                                                                                    If (LNotEqual (Local0, 0xABCD2900))
                                                                                                                                    {
                                                                                                                                        ERR (TS, Z170, 0x06F6, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                                                                    }

                                                                                                                                    If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                                                                    {
                                                                                                                                        ERR (TS, Z170, 0x06F9, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                                                                    }
                                                                                                                                }

                                                                                                                                Store (\MT14.DZ05.IY07, Local0)
                                                                                                                                MM1E ()
                                                                                                                                If (LNotEqual (Local0, 0xABCD2900))
                                                                                                                                {
                                                                                                                                    ERR (TS, Z170, 0x06FF, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                                                                }

                                                                                                                                If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                                                                {
                                                                                                                                    ERR (TS, Z170, 0x0702, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                                                                }
                                                                                                                            }

                                                                                                                            Store (\MT14.DZ05.IY07, Local0)
                                                                                                                            MM1D ()
                                                                                                                            If (LNotEqual (Local0, 0xABCD2900))
                                                                                                                            {
                                                                                                                                ERR (TS, Z170, 0x0708, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                                                            }

                                                                                                                            If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                                                            {
                                                                                                                                ERR (TS, Z170, 0x070B, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                                                            }
                                                                                                                        }

                                                                                                                        Store (\MT14.DZ05.IY07, Local0)
                                                                                                                        MM1C ()
                                                                                                                        If (LNotEqual (Local0, 0xABCD2900))
                                                                                                                        {
                                                                                                                            ERR (TS, Z170, 0x0711, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                                                        }

                                                                                                                        If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                                                        {
                                                                                                                            ERR (TS, Z170, 0x0714, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                                                        }
                                                                                                                    }

                                                                                                                    Store (\MT14.DZ05.IY07, Local0)
                                                                                                                    MM1B ()
                                                                                                                    If (LNotEqual (Local0, 0xABCD2900))
                                                                                                                    {
                                                                                                                        ERR (TS, Z170, 0x071A, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                                                    }

                                                                                                                    If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                                                    {
                                                                                                                        ERR (TS, Z170, 0x071D, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                                                    }
                                                                                                                }

                                                                                                                Store (\MT14.DZ05.IY07, Local0)
                                                                                                                MM1A ()
                                                                                                                If (LNotEqual (Local0, 0xABCD2900))
                                                                                                                {
                                                                                                                    ERR (TS, Z170, 0x0723, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                                                }

                                                                                                                If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                                                {
                                                                                                                    ERR (TS, Z170, 0x0726, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                                                }
                                                                                                            }

                                                                                                            Store (\MT14.DZ05.IY07, Local0)
                                                                                                            MM19 ()
                                                                                                            If (LNotEqual (Local0, 0xABCD2900))
                                                                                                            {
                                                                                                                ERR (TS, Z170, 0x072C, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                                            }

                                                                                                            If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                                            {
                                                                                                                ERR (TS, Z170, 0x072F, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                                            }
                                                                                                        }

                                                                                                        Store (\MT14.DZ05.IY07, Local0)
                                                                                                        MM18 ()
                                                                                                        If (LNotEqual (Local0, 0xABCD2900))
                                                                                                        {
                                                                                                            ERR (TS, Z170, 0x0735, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                                        }

                                                                                                        If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                                        {
                                                                                                            ERR (TS, Z170, 0x0738, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                                        }
                                                                                                    }

                                                                                                    Store (\MT14.DZ05.IY07, Local0)
                                                                                                    MM17 ()
                                                                                                    If (LNotEqual (Local0, 0xABCD2900))
                                                                                                    {
                                                                                                        ERR (TS, Z170, 0x073E, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                                    }

                                                                                                    If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                                    {
                                                                                                        ERR (TS, Z170, 0x0741, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                                    }
                                                                                                }

                                                                                                Store (\MT14.DZ05.IY07, Local0)
                                                                                                MM16 ()
                                                                                                If (LNotEqual (Local0, 0xABCD2900))
                                                                                                {
                                                                                                    ERR (TS, Z170, 0x0747, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                                }

                                                                                                If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                                {
                                                                                                    ERR (TS, Z170, 0x074A, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                                }
                                                                                            }

                                                                                            Store (\MT14.DZ05.IY07, Local0)
                                                                                            MM15 ()
                                                                                            If (LNotEqual (Local0, 0xABCD2900))
                                                                                            {
                                                                                                ERR (TS, Z170, 0x0750, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                            }

                                                                                            If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                            {
                                                                                                ERR (TS, Z170, 0x0753, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                            }
                                                                                        }

                                                                                        Store (\MT14.DZ05.IY07, Local0)
                                                                                        MM14 ()
                                                                                        If (LNotEqual (Local0, 0xABCD2900))
                                                                                        {
                                                                                            ERR (TS, Z170, 0x0759, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                        }

                                                                                        If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                        {
                                                                                            ERR (TS, Z170, 0x075C, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                        }
                                                                                    }

                                                                                    Store (\MT14.DZ05.IY07, Local0)
                                                                                    MM13 ()
                                                                                    If (LNotEqual (Local0, 0xABCD2900))
                                                                                    {
                                                                                        ERR (TS, Z170, 0x0762, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                    }

                                                                                    If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                    {
                                                                                        ERR (TS, Z170, 0x0765, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                    }
                                                                                }

                                                                                Store (\MT14.DZ05.IY07, Local0)
                                                                                MM12 ()
                                                                                If (LNotEqual (Local0, 0xABCD2900))
                                                                                {
                                                                                    ERR (TS, Z170, 0x076B, 0x00, 0x00, Local0, 0xABCD2900)
                                                                                }

                                                                                If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                                {
                                                                                    ERR (TS, Z170, 0x076E, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                                }
                                                                            }

                                                                            Store (\MT14.DZ05.IY07, Local0)
                                                                            MM11 ()
                                                                            If (LNotEqual (Local0, 0xABCD2900))
                                                                            {
                                                                                ERR (TS, Z170, 0x0774, 0x00, 0x00, Local0, 0xABCD2900)
                                                                            }

                                                                            If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                            {
                                                                                ERR (TS, Z170, 0x0777, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                            }
                                                                        }

                                                                        Store (\MT14.DZ05.IY07, Local0)
                                                                        MM10 ()
                                                                        If (LNotEqual (Local0, 0xABCD2900))
                                                                        {
                                                                            ERR (TS, Z170, 0x077D, 0x00, 0x00, Local0, 0xABCD2900)
                                                                        }

                                                                        If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                        {
                                                                            ERR (TS, Z170, 0x0780, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                        }
                                                                    }

                                                                    Store (\MT14.DZ05.IY07, Local0)
                                                                    MM0F ()
                                                                    If (LNotEqual (Local0, 0xABCD2900))
                                                                    {
                                                                        ERR (TS, Z170, 0x0786, 0x00, 0x00, Local0, 0xABCD2900)
                                                                    }

                                                                    If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                    {
                                                                        ERR (TS, Z170, 0x0789, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                    }
                                                                }

                                                                Store (\MT14.DZ05.IY07, Local0)
                                                                MM0E ()
                                                                If (LNotEqual (Local0, 0xABCD2900))
                                                                {
                                                                    ERR (TS, Z170, 0x078F, 0x00, 0x00, Local0, 0xABCD2900)
                                                                }

                                                                If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                                {
                                                                    ERR (TS, Z170, 0x0792, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                                }
                                                            }

                                                            Store (\MT14.DZ05.IY07, Local0)
                                                            MM0D ()
                                                            If (LNotEqual (Local0, 0xABCD2900))
                                                            {
                                                                ERR (TS, Z170, 0x0798, 0x00, 0x00, Local0, 0xABCD2900)
                                                            }

                                                            If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                            {
                                                                ERR (TS, Z170, 0x079B, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                            }
                                                        }

                                                        Store (\MT14.DZ05.IY07, Local0)
                                                        MM0C ()
                                                        If (LNotEqual (Local0, 0xABCD2900))
                                                        {
                                                            ERR (TS, Z170, 0x07A1, 0x00, 0x00, Local0, 0xABCD2900)
                                                        }

                                                        If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                        {
                                                            ERR (TS, Z170, 0x07A4, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                        }
                                                    }

                                                    Store (\MT14.DZ05.IY07, Local0)
                                                    MM0B ()
                                                    If (LNotEqual (Local0, 0xABCD2900))
                                                    {
                                                        ERR (TS, Z170, 0x07AA, 0x00, 0x00, Local0, 0xABCD2900)
                                                    }

                                                    If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                    {
                                                        ERR (TS, Z170, 0x07AD, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                    }
                                                }

                                                Store (\MT14.DZ05.IY07, Local0)
                                                MM0A ()
                                                If (LNotEqual (Local0, 0xABCD2900))
                                                {
                                                    ERR (TS, Z170, 0x07B3, 0x00, 0x00, Local0, 0xABCD2900)
                                                }

                                                If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                                {
                                                    ERR (TS, Z170, 0x07B6, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                                }
                                            }

                                            Store (\MT14.DZ05.IY07, Local0)
                                            MM09 ()
                                            If (LNotEqual (Local0, 0xABCD2900))
                                            {
                                                ERR (TS, Z170, 0x07BC, 0x00, 0x00, Local0, 0xABCD2900)
                                            }

                                            If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                            {
                                                ERR (TS, Z170, 0x07BF, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                            }
                                        }

                                        Store (\MT14.DZ05.IY07, Local0)
                                        MM08 ()
                                        If (LNotEqual (Local0, 0xABCD2900))
                                        {
                                            ERR (TS, Z170, 0x07C5, 0x00, 0x00, Local0, 0xABCD2900)
                                        }

                                        If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                        {
                                            ERR (TS, Z170, 0x07C8, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                        }
                                    }

                                    Store (\MT14.DZ05.IY07, Local0)
                                    MM07 ()
                                    If (LNotEqual (Local0, 0xABCD2900))
                                    {
                                        ERR (TS, Z170, 0x07CE, 0x00, 0x00, Local0, 0xABCD2900)
                                    }

                                    If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                    {
                                        ERR (TS, Z170, 0x07D1, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                    }
                                }

                                Store (\MT14.DZ05.IY07, Local0)
                                MM06 ()
                                If (LNotEqual (Local0, 0xABCD2900))
                                {
                                    ERR (TS, Z170, 0x07D7, 0x00, 0x00, Local0, 0xABCD2900)
                                }

                                If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                                {
                                    ERR (TS, Z170, 0x07DA, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                                }
                            }

                            Store (\MT14.DZ05.IY07, Local0)
                            MM05 ()
                            If (LNotEqual (Local0, 0xABCD2900))
                            {
                                ERR (TS, Z170, 0x07E0, 0x00, 0x00, Local0, 0xABCD2900)
                            }

                            If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                            {
                                ERR (TS, Z170, 0x07E3, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                            }
                        }

                        Store (\MT14.DZ05.IY07, Local0)
                        MM04 ()
                        If (LNotEqual (Local0, 0xABCD2900))
                        {
                            ERR (TS, Z170, 0x07E9, 0x00, 0x00, Local0, 0xABCD2900)
                        }

                        If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                        {
                            ERR (TS, Z170, 0x07EC, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                        }
                    }

                    Store (\MT14.DZ05.IY07, Local0)
                    MM03 ()
                    If (LNotEqual (Local0, 0xABCD2900))
                    {
                        ERR (TS, Z170, 0x07F2, 0x00, 0x00, Local0, 0xABCD2900)
                    }

                    If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                    {
                        ERR (TS, Z170, 0x07F5, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                    }
                }

                Store (\MT14.DZ05.IY07, Local0)
                MM02 ()
                If (LNotEqual (Local0, 0xABCD2900))
                {
                    ERR (TS, Z170, 0x07FB, 0x00, 0x00, Local0, 0xABCD2900)
                }

                If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
                {
                    ERR (TS, Z170, 0x07FE, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
                }
            }

            Store (\MT14.DZ05.IY07, Local0)
            MM01 ()
            If (LNotEqual (Local0, 0xABCD2900))
            {
                ERR (TS, Z170, 0x0804, 0x00, 0x00, Local0, 0xABCD2900)
            }

            If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
            {
                ERR (TS, Z170, 0x0807, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
            }
        }

        CH03 (TS, Z170, 0x011F, 0x080B, 0x00)
        Store (\MT14.DZ05.IY07, Local0)
        MM00 ()
        If (LNotEqual (Local0, 0xABCD2900))
        {
            ERR (TS, Z170, 0x0810, 0x00, 0x00, Local0, 0xABCD2900)
        }

        If (LNotEqual (\MT14.DZ05.IY07, 0xABCD2900))
        {
            ERR (TS, Z170, 0x0813, 0x00, 0x00, \MT14.DZ05.IY07, 0xABCD2900)
        }

        CH03 (TS, Z170, 0x0120, 0x0816, 0x00)
    }

    Method (MT15, 0, Serialized)
    {
        Name (TS, "mt15")
        Device (DZ05)
        {
            Name (IY07, 0xABCD3900)
        }

        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Method (MM08, 0, NotSerialized)
                                        {
                                            Method (MM09, 0, NotSerialized)
                                            {
                                                Method (MM0A, 0, NotSerialized)
                                                {
                                                    Method (MM0B, 0, NotSerialized)
                                                    {
                                                        Method (MM0C, 0, NotSerialized)
                                                        {
                                                            Method (MM0D, 0, NotSerialized)
                                                            {
                                                                Method (MM0E, 0, NotSerialized)
                                                                {
                                                                    Method (MM0F, 0, NotSerialized)
                                                                    {
                                                                        Method (MM10, 0, NotSerialized)
                                                                        {
                                                                            Method (MM11, 0, NotSerialized)
                                                                            {
                                                                                Method (MM12, 0, NotSerialized)
                                                                                {
                                                                                    Method (MM13, 0, NotSerialized)
                                                                                    {
                                                                                        Method (MM14, 0, NotSerialized)
                                                                                        {
                                                                                            Method (MM15, 0, NotSerialized)
                                                                                            {
                                                                                                Method (MM16, 0, NotSerialized)
                                                                                                {
                                                                                                    Method (MM17, 0, NotSerialized)
                                                                                                    {
                                                                                                        Method (MM18, 0, NotSerialized)
                                                                                                        {
                                                                                                            Method (MM19, 0, NotSerialized)
                                                                                                            {
                                                                                                                Method (MM1A, 0, NotSerialized)
                                                                                                                {
                                                                                                                    Method (MM1B, 0, NotSerialized)
                                                                                                                    {
                                                                                                                        Method (MM1C, 0, NotSerialized)
                                                                                                                        {
                                                                                                                            Method (MM1D, 0, NotSerialized)
                                                                                                                            {
                                                                                                                                Method (MM1E, 0, NotSerialized)
                                                                                                                                {
                                                                                                                                    Method (MM1F, 0, NotSerialized)
                                                                                                                                    {
                                                                                                                                        Store (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                                                                        OUTC ("mt15,   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^dz05.iy07:")
                                                                                                                                        OUTC (Local0)
                                                                                                                                        If (LNotEqual (Local0, 0xABCD3900))
                                                                                                                                        {
                                                                                                                                            ERR (TS, Z170, 0x0869, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                                                                        }

                                                                                                                                        If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                                                                        {
                                                                                                                                            ERR (TS, Z170, 0x086C, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                                                                        }
                                                                                                                                    }

                                                                                                                                    Store (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                                                                    MM1F ()
                                                                                                                                    If (LNotEqual (Local0, 0xABCD3900))
                                                                                                                                    {
                                                                                                                                        ERR (TS, Z170, 0x0872, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                                                                    }

                                                                                                                                    If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                                                                    {
                                                                                                                                        ERR (TS, Z170, 0x0875, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                                                                    }
                                                                                                                                }

                                                                                                                                Store (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                                                                MM1E ()
                                                                                                                                If (LNotEqual (Local0, 0xABCD3900))
                                                                                                                                {
                                                                                                                                    ERR (TS, Z170, 0x087B, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                                                                }

                                                                                                                                If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                                                                {
                                                                                                                                    ERR (TS, Z170, 0x087E, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                                                                }
                                                                                                                            }

                                                                                                                            Store (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                                                            MM1D ()
                                                                                                                            If (LNotEqual (Local0, 0xABCD3900))
                                                                                                                            {
                                                                                                                                ERR (TS, Z170, 0x0884, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                                                            }

                                                                                                                            If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                                                            {
                                                                                                                                ERR (TS, Z170, 0x0887, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                                                            }
                                                                                                                        }

                                                                                                                        Store (^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                                                        MM1C ()
                                                                                                                        If (LNotEqual (Local0, 0xABCD3900))
                                                                                                                        {
                                                                                                                            ERR (TS, Z170, 0x088D, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                                                        }

                                                                                                                        If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                                                        {
                                                                                                                            ERR (TS, Z170, 0x0890, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                                                        }
                                                                                                                    }

                                                                                                                    Store (^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                                                    MM1B ()
                                                                                                                    If (LNotEqual (Local0, 0xABCD3900))
                                                                                                                    {
                                                                                                                        ERR (TS, Z170, 0x0896, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                                                    }

                                                                                                                    If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                                                    {
                                                                                                                        ERR (TS, Z170, 0x0899, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                                                    }
                                                                                                                }

                                                                                                                Store (^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                                                MM1A ()
                                                                                                                If (LNotEqual (Local0, 0xABCD3900))
                                                                                                                {
                                                                                                                    ERR (TS, Z170, 0x089F, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                                                }

                                                                                                                If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                                                {
                                                                                                                    ERR (TS, Z170, 0x08A2, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                                                }
                                                                                                            }

                                                                                                            Store (^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                                            MM19 ()
                                                                                                            If (LNotEqual (Local0, 0xABCD3900))
                                                                                                            {
                                                                                                                ERR (TS, Z170, 0x08A8, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                                            }

                                                                                                            If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                                            {
                                                                                                                ERR (TS, Z170, 0x08AB, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                                            }
                                                                                                        }

                                                                                                        Store (^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                                        MM18 ()
                                                                                                        If (LNotEqual (Local0, 0xABCD3900))
                                                                                                        {
                                                                                                            ERR (TS, Z170, 0x08B1, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                                        }

                                                                                                        If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                                        {
                                                                                                            ERR (TS, Z170, 0x08B4, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                                        }
                                                                                                    }

                                                                                                    Store (^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                                    MM17 ()
                                                                                                    If (LNotEqual (Local0, 0xABCD3900))
                                                                                                    {
                                                                                                        ERR (TS, Z170, 0x08BA, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                                    }

                                                                                                    If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                                    {
                                                                                                        ERR (TS, Z170, 0x08BD, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                                    }
                                                                                                }

                                                                                                Store (^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                                MM16 ()
                                                                                                If (LNotEqual (Local0, 0xABCD3900))
                                                                                                {
                                                                                                    ERR (TS, Z170, 0x08C3, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                                }

                                                                                                If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                                {
                                                                                                    ERR (TS, Z170, 0x08C6, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                                }
                                                                                            }

                                                                                            Store (^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                            MM15 ()
                                                                                            If (LNotEqual (Local0, 0xABCD3900))
                                                                                            {
                                                                                                ERR (TS, Z170, 0x08CC, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                            }

                                                                                            If (LNotEqual (^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                            {
                                                                                                ERR (TS, Z170, 0x08CF, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                            }
                                                                                        }

                                                                                        Store (^^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                        MM14 ()
                                                                                        If (LNotEqual (Local0, 0xABCD3900))
                                                                                        {
                                                                                            ERR (TS, Z170, 0x08D5, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                        }

                                                                                        If (LNotEqual (^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                        {
                                                                                            ERR (TS, Z170, 0x08D8, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                        }
                                                                                    }

                                                                                    Store (^^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                    MM13 ()
                                                                                    If (LNotEqual (Local0, 0xABCD3900))
                                                                                    {
                                                                                        ERR (TS, Z170, 0x08DE, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                    }

                                                                                    If (LNotEqual (^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                    {
                                                                                        ERR (TS, Z170, 0x08E1, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                    }
                                                                                }

                                                                                Store (^^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                                MM12 ()
                                                                                If (LNotEqual (Local0, 0xABCD3900))
                                                                                {
                                                                                    ERR (TS, Z170, 0x08E7, 0x00, 0x00, Local0, 0xABCD3900)
                                                                                }

                                                                                If (LNotEqual (^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                                {
                                                                                    ERR (TS, Z170, 0x08EA, 0x00, 0x00, ^^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                                }
                                                                            }

                                                                            Store (^^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                            MM11 ()
                                                                            If (LNotEqual (Local0, 0xABCD3900))
                                                                            {
                                                                                ERR (TS, Z170, 0x08F0, 0x00, 0x00, Local0, 0xABCD3900)
                                                                            }

                                                                            If (LNotEqual (^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                            {
                                                                                ERR (TS, Z170, 0x08F3, 0x00, 0x00, ^^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                            }
                                                                        }

                                                                        Store (^^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                        MM10 ()
                                                                        If (LNotEqual (Local0, 0xABCD3900))
                                                                        {
                                                                            ERR (TS, Z170, 0x08F9, 0x00, 0x00, Local0, 0xABCD3900)
                                                                        }

                                                                        If (LNotEqual (^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                        {
                                                                            ERR (TS, Z170, 0x08FC, 0x00, 0x00, ^^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                        }
                                                                    }

                                                                    Store (^^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                    MM0F ()
                                                                    If (LNotEqual (Local0, 0xABCD3900))
                                                                    {
                                                                        ERR (TS, Z170, 0x0902, 0x00, 0x00, Local0, 0xABCD3900)
                                                                    }

                                                                    If (LNotEqual (^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                    {
                                                                        ERR (TS, Z170, 0x0905, 0x00, 0x00, ^^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                    }
                                                                }

                                                                Store (^^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                                MM0E ()
                                                                If (LNotEqual (Local0, 0xABCD3900))
                                                                {
                                                                    ERR (TS, Z170, 0x090B, 0x00, 0x00, Local0, 0xABCD3900)
                                                                }

                                                                If (LNotEqual (^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                                {
                                                                    ERR (TS, Z170, 0x090E, 0x00, 0x00, ^^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                                }
                                                            }

                                                            Store (^^^^^^^^^^^^^DZ05.IY07, Local0)
                                                            MM0D ()
                                                            If (LNotEqual (Local0, 0xABCD3900))
                                                            {
                                                                ERR (TS, Z170, 0x0914, 0x00, 0x00, Local0, 0xABCD3900)
                                                            }

                                                            If (LNotEqual (^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                            {
                                                                ERR (TS, Z170, 0x0917, 0x00, 0x00, ^^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                            }
                                                        }

                                                        Store (^^^^^^^^^^^^DZ05.IY07, Local0)
                                                        MM0C ()
                                                        If (LNotEqual (Local0, 0xABCD3900))
                                                        {
                                                            ERR (TS, Z170, 0x091D, 0x00, 0x00, Local0, 0xABCD3900)
                                                        }

                                                        If (LNotEqual (^^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                        {
                                                            ERR (TS, Z170, 0x0920, 0x00, 0x00, ^^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                        }
                                                    }

                                                    Store (^^^^^^^^^^^DZ05.IY07, Local0)
                                                    MM0B ()
                                                    If (LNotEqual (Local0, 0xABCD3900))
                                                    {
                                                        ERR (TS, Z170, 0x0926, 0x00, 0x00, Local0, 0xABCD3900)
                                                    }

                                                    If (LNotEqual (^^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                    {
                                                        ERR (TS, Z170, 0x0929, 0x00, 0x00, ^^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                    }
                                                }

                                                Store (^^^^^^^^^^DZ05.IY07, Local0)
                                                MM0A ()
                                                If (LNotEqual (Local0, 0xABCD3900))
                                                {
                                                    ERR (TS, Z170, 0x092F, 0x00, 0x00, Local0, 0xABCD3900)
                                                }

                                                If (LNotEqual (^^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                                {
                                                    ERR (TS, Z170, 0x0932, 0x00, 0x00, ^^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                                }
                                            }

                                            Store (^^^^^^^^^DZ05.IY07, Local0)
                                            MM09 ()
                                            If (LNotEqual (Local0, 0xABCD3900))
                                            {
                                                ERR (TS, Z170, 0x0938, 0x00, 0x00, Local0, 0xABCD3900)
                                            }

                                            If (LNotEqual (^^^^^^^^^DZ05.IY07, 0xABCD3900))
                                            {
                                                ERR (TS, Z170, 0x093B, 0x00, 0x00, ^^^^^^^^^DZ05.IY07, 0xABCD3900)
                                            }
                                        }

                                        Store (^^^^^^^^DZ05.IY07, Local0)
                                        MM08 ()
                                        If (LNotEqual (Local0, 0xABCD3900))
                                        {
                                            ERR (TS, Z170, 0x0941, 0x00, 0x00, Local0, 0xABCD3900)
                                        }

                                        If (LNotEqual (^^^^^^^^DZ05.IY07, 0xABCD3900))
                                        {
                                            ERR (TS, Z170, 0x0944, 0x00, 0x00, ^^^^^^^^DZ05.IY07, 0xABCD3900)
                                        }
                                    }

                                    Store (^^^^^^^DZ05.IY07, Local0)
                                    MM07 ()
                                    If (LNotEqual (Local0, 0xABCD3900))
                                    {
                                        ERR (TS, Z170, 0x094A, 0x00, 0x00, Local0, 0xABCD3900)
                                    }

                                    If (LNotEqual (^^^^^^^DZ05.IY07, 0xABCD3900))
                                    {
                                        ERR (TS, Z170, 0x094D, 0x00, 0x00, ^^^^^^^DZ05.IY07, 0xABCD3900)
                                    }
                                }

                                Store (^^^^^^DZ05.IY07, Local0)
                                MM06 ()
                                If (LNotEqual (Local0, 0xABCD3900))
                                {
                                    ERR (TS, Z170, 0x0953, 0x00, 0x00, Local0, 0xABCD3900)
                                }

                                If (LNotEqual (^^^^^^DZ05.IY07, 0xABCD3900))
                                {
                                    ERR (TS, Z170, 0x0956, 0x00, 0x00, ^^^^^^DZ05.IY07, 0xABCD3900)
                                }
                            }

                            Store (^^^^^DZ05.IY07, Local0)
                            MM05 ()
                            If (LNotEqual (Local0, 0xABCD3900))
                            {
                                ERR (TS, Z170, 0x095C, 0x00, 0x00, Local0, 0xABCD3900)
                            }

                            If (LNotEqual (^^^^^DZ05.IY07, 0xABCD3900))
                            {
                                ERR (TS, Z170, 0x095F, 0x00, 0x00, ^^^^^DZ05.IY07, 0xABCD3900)
                            }
                        }

                        Store (^^^^DZ05.IY07, Local0)
                        MM04 ()
                        If (LNotEqual (Local0, 0xABCD3900))
                        {
                            ERR (TS, Z170, 0x0965, 0x00, 0x00, Local0, 0xABCD3900)
                        }

                        If (LNotEqual (^^^^DZ05.IY07, 0xABCD3900))
                        {
                            ERR (TS, Z170, 0x0968, 0x00, 0x00, ^^^^DZ05.IY07, 0xABCD3900)
                        }
                    }

                    Store (^^^DZ05.IY07, Local0)
                    MM03 ()
                    If (LNotEqual (Local0, 0xABCD3900))
                    {
                        ERR (TS, Z170, 0x096E, 0x00, 0x00, Local0, 0xABCD3900)
                    }

                    If (LNotEqual (^^^DZ05.IY07, 0xABCD3900))
                    {
                        ERR (TS, Z170, 0x0971, 0x00, 0x00, ^^^DZ05.IY07, 0xABCD3900)
                    }
                }

                Store (^^DZ05.IY07, Local0)
                MM02 ()
                If (LNotEqual (Local0, 0xABCD3900))
                {
                    ERR (TS, Z170, 0x0977, 0x00, 0x00, Local0, 0xABCD3900)
                }

                If (LNotEqual (^^DZ05.IY07, 0xABCD3900))
                {
                    ERR (TS, Z170, 0x097A, 0x00, 0x00, ^^DZ05.IY07, 0xABCD3900)
                }
            }

            Store (^DZ05.IY07, Local0)
            MM01 ()
            If (LNotEqual (Local0, 0xABCD3900))
            {
                ERR (TS, Z170, 0x0980, 0x00, 0x00, Local0, 0xABCD3900)
            }

            If (LNotEqual (^DZ05.IY07, 0xABCD3900))
            {
                ERR (TS, Z170, 0x0983, 0x00, 0x00, ^DZ05.IY07, 0xABCD3900)
            }
        }

        CH03 (TS, Z170, 0x0121, 0x0987, 0x00)
        Store (DZ05.IY07, Local0)
        MM00 ()
        If (LNotEqual (Local0, 0xABCD3900))
        {
            ERR (TS, Z170, 0x098C, 0x00, 0x00, Local0, 0xABCD3900)
        }

        If (LNotEqual (DZ05.IY07, 0xABCD3900))
        {
            ERR (TS, Z170, 0x098F, 0x00, 0x00, DZ05.IY07, 0xABCD3900)
        }

        CH03 (TS, Z170, 0x0122, 0x0992, 0x00)
    }

    Method (MT16, 1, Serialized)
    {
        Name (TS, "mt16")
        Name (I000, 0x00)
        Name (I001, 0x00)
        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, Serialized)
                        {
                            Device (DZ05)
                            {
                                Name (IY07, 0xABCD4900)
                            }

                            If (LEqual (I001, 0x01))
                            {
                                Store (0xABCD4904, DZ05.IY07) /* \MT16.MM00.MM01.MM02.MM03.MM04.DZ05.IY07 */
                                M001 (0x01)
                            }
                            ElseIf (LEqual (I001, 0x02))
                            {
                                Store (0xABCD4905, DZ05.IY07) /* \MT16.MM00.MM01.MM02.MM03.MM04.DZ05.IY07 */
                                M001 (0x02)
                            }
                            ElseIf (LEqual (I001, 0x03))
                            {
                                M001 (0x03)
                            }
                        }

                        MM04 ()
                    }

                    MM03 ()
                }

                MM02 ()
            }

            MM01 ()
        }

        Method (M000, 0, NotSerialized)
        {
            Store (^MM00.MM01.MM02.MM03.MM04.DZ05.IY07, I000) /* \MT16.I000 */
        }

        Method (M001, 1, NotSerialized)
        {
            Method (MMF1, 1, NotSerialized)
            {
                Method (MMF2, 1, Serialized)
                {
                    Device (DZ05)
                    {
                        Name (IY07, 0xABCD6900)
                    }

                    If (LEqual (Arg0, 0x01))
                    {
                        Store (\MT16.MM00.MM01.MM02.MM03.MM04.DZ05.IY07, I000) /* \MT16.I000 */
                    }
                    ElseIf (LEqual (Arg0, 0x02))
                    {
                        Store (^^^MM00.MM01.MM02.MM03.MM04.DZ05.IY07, I000) /* \MT16.I000 */
                    }
                    ElseIf (LEqual (Arg0, 0x03))
                    {
                        Store (^^MMF1.MMF2.DZ05.IY07, I000) /* \MT16.I000 */
                    }
                }

                MMF2 (Arg0)
            }

            MMF1 (Arg0)
        }

        CH03 (TS, Z170, 0xC1, 0x09DC, 0x00)
        If (LEqual (Arg0, 0x00))
        {
            M000 ()
            CH04 (TS, 0x01, 0x05, Z170, 0x09E1, 0x00, 0x00)
        }
        ElseIf (LEqual (Arg0, 0x01))
        {
            Store (0x00, I000) /* \MT16.I000 */
            Store (0x01, I001) /* \MT16.I001 */
            MM00 ()
            If (LNotEqual (I000, 0xABCD4904))
            {
                ERR (TS, Z170, 0x09EB, 0x00, 0x00, I000, 0xABCD4904)
            }
        }
        ElseIf (LEqual (Arg0, 0x02))
        {
            Store (0x02, I001) /* \MT16.I001 */
            MM00 ()
            If (LNotEqual (I000, 0xABCD4905))
            {
                ERR (TS, Z170, 0x09F5, 0x00, 0x00, I000, 0xABCD4905)
            }
        }
        ElseIf (LEqual (Arg0, 0x03))
        {
            Store (0x03, I001) /* \MT16.I001 */
            MM00 ()
            If (LNotEqual (I000, 0xABCD6900))
            {
                ERR (TS, Z170, 0x0A00, 0x00, 0x00, I000, 0xABCD6900)
            }
        }

        CH03 (TS, Z170, 0xC5, 0x0A04, 0x00)
    }

    Method (MT17, 1, Serialized)
    {
        Name (TS, "mt17")
        Name (I000, 0x00)
        Name (I001, 0x00)
        Method (MM00, 0, NotSerialized)
        {
            Method (MM01, 0, NotSerialized)
            {
                Method (MM02, 0, NotSerialized)
                {
                    Method (MM03, 0, NotSerialized)
                    {
                        Method (MM04, 0, NotSerialized)
                        {
                            Method (MM05, 0, NotSerialized)
                            {
                                Method (MM06, 0, NotSerialized)
                                {
                                    Method (MM07, 0, NotSerialized)
                                    {
                                        Method (MM08, 0, NotSerialized)
                                        {
                                            Method (MM09, 0, NotSerialized)
                                            {
                                                Method (MM0A, 0, NotSerialized)
                                                {
                                                    Method (MM0B, 0, NotSerialized)
                                                    {
                                                        Method (MM0C, 0, NotSerialized)
                                                        {
                                                            Method (MM0D, 0, NotSerialized)
                                                            {
                                                                Method (MM0E, 0, NotSerialized)
                                                                {
                                                                    Method (MM0F, 0, NotSerialized)
                                                                    {
                                                                        Method (MM10, 0, NotSerialized)
                                                                        {
                                                                            Method (MM11, 0, NotSerialized)
                                                                            {
                                                                                Method (MM12, 0, NotSerialized)
                                                                                {
                                                                                    Method (MM13, 0, NotSerialized)
                                                                                    {
                                                                                        Method (MM14, 0, NotSerialized)
                                                                                        {
                                                                                            Method (MM15, 0, NotSerialized)
                                                                                            {
                                                                                                Method (MM16, 0, NotSerialized)
                                                                                                {
                                                                                                    Method (MM17, 0, NotSerialized)
                                                                                                    {
                                                                                                        Method (MM18, 0, NotSerialized)
                                                                                                        {
                                                                                                            Method (MM19, 0, NotSerialized)
                                                                                                            {
                                                                                                                Method (MM1A, 0, NotSerialized)
                                                                                                                {
                                                                                                                    Method (MM1B, 0, NotSerialized)
                                                                                                                    {
                                                                                                                        Method (MM1C, 0, NotSerialized)
                                                                                                                        {
                                                                                                                            Method (MM1D, 0, NotSerialized)
                                                                                                                            {
                                                                                                                                Method (MM1E, 0, NotSerialized)
                                                                                                                                {
                                                                                                                                    Method (MM1F, 0, NotSerialized)
                                                                                                                                    {
                                                                                                                                        Method (MM20, 0, NotSerialized)
                                                                                                                                        {
                                                                                                                                            Method (MM21, 0, Serialized)
                                                                                                                                            {
                                                                                                                                                Device (DZ05)
                                                                                                                                                {
                                                                                                                                                    Name (IY07, 0xABCD5900)
                                                                                                                                                }

                                                                                                                                                Method (MM22, 0, NotSerialized)
                                                                                                                                                {
                                                                                                                                                    Method (MM23, 0, NotSerialized)
                                                                                                                                                    {
                                                                                                                                                        Method (MM24, 0, NotSerialized)
                                                                                                                                                        {
                                                                                                                                                            Method (MM25, 0, NotSerialized)
                                                                                                                                                            {
                                                                                                                                                                If (LEqual (I001, 0x01))
                                                                                                                                                                {
                                                                                                                                                                    Store (0xABCD4906, ^^^^DZ05.IY07) /* \MT17.MM00.MM01.MM02.MM03.MM04.MM05.MM06.MM07.MM08.MM09.MM0A.MM0B.MM0C.MM0D.MM0E.MM0F.MM10.MM11.MM12.MM13.MM14.MM15.MM16.MM17.MM18.MM19.MM1A.MM1B.MM1C.MM1D.MM1E.MM1F.MM20.MM21.DZ05.IY07 */
                                                                                                                                                                    M001 (0x01)
                                                                                                                                                                }
                                                                                                                                                                ElseIf (LEqual (I001, 0x02))
                                                                                                                                                                {
                                                                                                                                                                    Store (0xABCD4907, ^^^^DZ05.IY07) /* \MT17.MM00.MM01.MM02.MM03.MM04.MM05.MM06.MM07.MM08.MM09.MM0A.MM0B.MM0C.MM0D.MM0E.MM0F.MM10.MM11.MM12.MM13.MM14.MM15.MM16.MM17.MM18.MM19.MM1A.MM1B.MM1C.MM1D.MM1E.MM1F.MM20.MM21.DZ05.IY07 */
                                                                                                                                                                    M001 (0x02)
                                                                                                                                                                }
                                                                                                                                                                ElseIf (LEqual (I001, 0x03))
                                                                                                                                                                {
                                                                                                                                                                    M001 (0x03)
                                                                                                                                                                }
                                                                                                                                                            }

                                                                                                                                                            MM25 ()
                                                                                                                                                        }

                                                                                                                                                        MM24 ()
                                                                                                                                                    }

                                                                                                                                                    MM23 ()
                                                                                                                                                }

                                                                                                                                                MM22 ()
                                                                                                                                            }

                                                                                                                                            MM21 ()
                                                                                                                                        }

                                                                                                                                        MM20 ()
                                                                                                                                    }

                                                                                                                                    MM1F ()
                                                                                                                                }

                                                                                                                                MM1E ()
                                                                                                                            }

                                                                                                                            MM1D ()
                                                                                                                        }

                                                                                                                        MM1C ()
                                                                                                                    }

                                                                                                                    MM1B ()
                                                                                                                }

                                                                                                                MM1A ()
                                                                                                            }

                                                                                                            MM19 ()
                                                                                                        }

                                                                                                        MM18 ()
                                                                                                    }

                                                                                                    MM17 ()
                                                                                                }

                                                                                                MM16 ()
                                                                                            }

                                                                                            MM15 ()
                                                                                        }

                                                                                        MM14 ()
                                                                                    }

                                                                                    MM13 ()
                                                                                }

                                                                                MM12 ()
                                                                            }

                                                                            MM11 ()
                                                                        }

                                                                        MM10 ()
                                                                    }

                                                                    MM0F ()
                                                                }

                                                                MM0E ()
                                                            }

                                                            MM0D ()
                                                        }

                                                        MM0C ()
                                                    }

                                                    MM0B ()
                                                }

                                                MM0A ()
                                            }

                                            MM09 ()
                                        }

                                        MM08 ()
                                    }

                                    MM07 ()
                                }

                                MM06 ()
                            }

                            MM05 ()
                        }

                        MM04 ()
                    }

                    MM03 ()
                }

                MM02 ()
            }

            MM01 ()
        }

        Method (M000, 0, NotSerialized)
        {
            Store (^MM00.MM01.MM02.MM03.MM04.MM05.MM06.MM07.MM08.MM09.MM0A.MM0B.MM0C.MM0D.MM0E.MM0F.MM10.MM11.MM12.MM13.MM14.MM15.MM16.MM17.MM18.MM19.MM1A.MM1B.MM1C.MM1D.MM1E.MM1F.MM20.MM21.DZ05.IY07, I000) /* \MT17.I000 */
        }

        Method (M001, 1, NotSerialized)
        {
            Method (MMF1, 1, NotSerialized)
            {
                Method (MMF2, 1, NotSerialized)
                {
                    Method (MMF3, 1, NotSerialized)
                    {
                        Method (MMF4, 1, NotSerialized)
                        {
                            Method (MMF5, 1, NotSerialized)
                            {
                                Method (MMF6, 1, NotSerialized)
                                {
                                    Method (MMF7, 1, NotSerialized)
                                    {
                                        Method (MMF8, 1, NotSerialized)
                                        {
                                            Method (MMF9, 1, NotSerialized)
                                            {
                                                Method (MMFA, 1, NotSerialized)
                                                {
                                                    Method (MMFB, 1, NotSerialized)
                                                    {
                                                        Method (MMFC, 1, NotSerialized)
                                                        {
                                                            Method (MMFD, 1, NotSerialized)
                                                            {
                                                                Method (MMFE, 1, NotSerialized)
                                                                {
                                                                    Method (MMFF, 1, NotSerialized)
                                                                    {
                                                                        Method (MM10, 1, NotSerialized)
                                                                        {
                                                                            Method (MM11, 1, Serialized)
                                                                            {
                                                                                Device (DZ05)
                                                                                {
                                                                                    Name (IY07, 0xABCD4908)
                                                                                }

                                                                                Method (MM12, 1, NotSerialized)
                                                                                {
                                                                                    Method (MM13, 1, NotSerialized)
                                                                                    {
                                                                                        Method (MM14, 1, NotSerialized)
                                                                                        {
                                                                                            Method (MM15, 1, NotSerialized)
                                                                                            {
                                                                                                Method (MM16, 1, NotSerialized)
                                                                                                {
                                                                                                    Method (MM17, 1, NotSerialized)
                                                                                                    {
                                                                                                        Method (MM18, 1, NotSerialized)
                                                                                                        {
                                                                                                            Method (MM19, 1, NotSerialized)
                                                                                                            {
                                                                                                                Method (MM1A, 1, NotSerialized)
                                                                                                                {
                                                                                                                    Method (MM1B, 1, NotSerialized)
                                                                                                                    {
                                                                                                                        Method (MM1C, 1, NotSerialized)
                                                                                                                        {
                                                                                                                            Method (MM1D, 1, NotSerialized)
                                                                                                                            {
                                                                                                                                Method (MM1E, 1, NotSerialized)
                                                                                                                                {
                                                                                                                                    Method (MM1F, 1, NotSerialized)
                                                                                                                                    {
                                                                                                                                        If (LEqual (Arg0, 0x01))
                                                                                                                                        {
                                                                                                                                            Store (\MT17.MM00.MM01.MM02.MM03.MM04.MM05.MM06.MM07.MM08.MM09.MM0A.MM0B.MM0C.MM0D.MM0E.MM0F.MM10.MM11.MM12.MM13.MM14.MM15.MM16.MM17.MM18.MM19.MM1A.MM1B.MM1C.MM1D.MM1E.MM1F.MM20.MM21.DZ05.IY07, I000) /* \MT17.I000 */
                                                                                                                                        }
                                                                                                                                        ElseIf (LEqual (Arg0, 0x02))
                                                                                                                                        {
                                                                                                                                            Store (^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^MM00.MM01.MM02.MM03.MM04.MM05.MM06.MM07.MM08.MM09.MM0A.MM0B.MM0C.MM0D.MM0E.MM0F.MM10.MM11.MM12.MM13.MM14.MM15.MM16.MM17.MM18.MM19.MM1A.MM1B.MM1C.MM1D.MM1E.MM1F.MM20.MM21.DZ05.IY07, I000) /* \MT17.I000 */
                                                                                                                                        }
                                                                                                                                        ElseIf (LEqual (Arg0, 0x03))
                                                                                                                                        {
                                                                                                                                            Store (^^^^^^^^^^^^^^^^^^^^^^^^^^MMF6.MMF7.MMF8.MMF9.MMFA.MMFB.MMFC.MMFD.MMFE.MMFF.MM10.MM11.DZ05.IY07, I000) /* \MT17.I000 */
                                                                                                                                        }
                                                                                                                                    }

                                                                                                                                    MM1F (Arg0)
                                                                                                                                }

                                                                                                                                MM1E (Arg0)
                                                                                                                            }

                                                                                                                            MM1D (Arg0)
                                                                                                                        }

                                                                                                                        MM1C (Arg0)
                                                                                                                    }

                                                                                                                    MM1B (Arg0)
                                                                                                                }

                                                                                                                MM1A (Arg0)
                                                                                                            }

                                                                                                            MM19 (Arg0)
                                                                                                        }

                                                                                                        MM18 (Arg0)
                                                                                                    }

                                                                                                    MM17 (Arg0)
                                                                                                }

                                                                                                MM16 (Arg0)
                                                                                            }

                                                                                            MM15 (Arg0)
                                                                                        }

                                                                                        MM14 (Arg0)
                                                                                    }

                                                                                    MM13 (Arg0)
                                                                                }

                                                                                MM12 (Arg0)
                                                                            }

                                                                            MM11 (Arg0)
                                                                        }

                                                                        MM10 (Arg0)
                                                                    }

                                                                    MMFF (Arg0)
                                                                }

                                                                MMFE (Arg0)
                                                            }

                                                            MMFD (Arg0)
                                                        }

                                                        MMFC (Arg0)
                                                    }

                                                    MMFB (Arg0)
                                                }

                                                MMFA (Arg0)
                                            }

                                            MMF9 (Arg0)
                                        }

                                        MMF8 (Arg0)
                                    }

                                    MMF7 (Arg0)
                                }

                                MMF6 (Arg0)
                            }

                            MMF5 (Arg0)
                        }

                        MMF4 (Arg0)
                    }

                    MMF3 (Arg0)
                }

                MMF2 (Arg0)
            }

            MMF1 (Arg0)
        }

        CH03 (TS, Z170, 0xC6, 0x0B47, 0x00)
        If (LEqual (Arg0, 0x00))
        {
            M000 ()
            CH04 (TS, 0x01, 0x05, Z170, 0x0B4C, 0x00, 0x00)
        }
        ElseIf (LEqual (Arg0, 0x01))
        {
            Store (0x01, I001) /* \MT17.I001 */
            MM00 ()
            If (LNotEqual (I000, 0xABCD4906))
            {
                ERR (TS, Z170, 0x0B55, 0x00, 0x00, I000, 0xABCD4906)
            }
        }
        ElseIf (LEqual (Arg0, 0x02))
        {
            Store (0x02, I001) /* \MT17.I001 */
            MM00 ()
            If (LNotEqual (I000, 0xABCD4907))
            {
                ERR (TS, Z170, 0x0B5F, 0x00, 0x00, I000, 0xABCD4907)
            }
        }
        ElseIf (LEqual (Arg0, 0x03))
        {
            Store (0x03, I001) /* \MT17.I001 */
            MM00 ()
            If (LNotEqual (I000, 0xABCD4908))
            {
                ERR (TS, Z170, 0x0B6A, 0x00, 0x00, I000, 0xABCD4908)
            }
        }

        CH03 (TS, Z170, 0xCB, 0x0B6E, 0x00)
    }

    Method (MT18, 1, Serialized)
    {
        Name (TS, "mt18")
        Device (DZ05)
        {
            Name (IY07, 0xABCD4900)
        }

        CH03 (TS, Z170, 0xCC, 0x0B7A, 0x00)
        If (Arg0)
        {
            Store (0xABCD9000, \MT18.DZ05.IY07)
            If (LNotEqual (\MT18.DZ05.IY07, 0xABCD9000))
            {
                ERR (TS, Z170, 0x0B7F, 0x00, 0x00, \MT18.DZ05.IY07, 0xABCD9000)
            }
        }
        Else
        {
            Store (0xABCD9001, DZ05.IY07) /* \MT18.DZ05.IY07 */
            If (LNotEqual (DZ05.IY07, 0xABCD9001))
            {
                ERR (TS, Z170, 0x0B84, 0x00, 0x00, DZ05.IY07, 0xABCD9001)
            }
        }

        CH03 (TS, Z170, 0xCD, 0x0B88, 0x00)
    }

    Method (MT19, 1, Serialized)
    {
        Name (TS, "mt19")
        Processor (PR7D, 0x00, 0x00000000, 0x08)
        {
            Name (IY07, 0xABCD0660)
        }

        CH03 (TS, Z170, 0xCE, 0x0B94, 0x00)
        If (Arg0)
        {
            Store (0xABCD9002, \MT19.PR7D.IY07)
            If (LNotEqual (\MT19.PR7D.IY07, 0xABCD9002))
            {
                ERR (TS, Z170, 0x0B99, 0x00, 0x00, \MT19.PR7D.IY07, 0xABCD9002)
            }
        }
        Else
        {
            Store (0xABCD9003, PR7D.IY07) /* \MT19.PR7D.IY07 */
            If (LNotEqual (PR7D.IY07, 0xABCD9003))
            {
                ERR (TS, Z170, 0x0B9E, 0x00, 0x00, PR7D.IY07, 0xABCD9003)
            }
        }

        CH03 (TS, Z170, 0xCF, 0x0BA2, 0x00)
    }

    Method (MT1A, 1, Serialized)
    {
        Name (TS, "mt1a")
        CH03 (TS, Z170, 0xD0, 0x0BA9, 0x00)
        If (Arg0)
        {
            Store (0xABCD9004, \PR7D.IY07)
            If (LNotEqual (\PR7D.IY07, 0xABCD9004))
            {
                ERR (TS, Z170, 0x0BAD, 0x00, 0x00, \PR7D.IY07, 0xABCD9004)
            }
        }
        Else
        {
            Store (0xABCD9005, ^PR7D.IY07) /* \PR7D.IY07 */
            If (LNotEqual (^PR7D.IY07, 0xABCD9005))
            {
                ERR (TS, Z170, 0x0BB2, 0x00, 0x00, ^PR7D.IY07, 0xABCD9005)
            }
        }

        CH03 (TS, Z170, 0xD1, 0x0BB5, 0x00)
    }

    Method (MTFF, 0, Serialized)
    {
        Name (RUN0, 0x01)
        SRMT ("mt00")
        MT00 ()
        If (CHK0)
        {
            SRMT ("mt01")
            MT01 ()
        }

        SRMT ("mt02")
        MT02 ()
        If (CHK0)
        {
            SRMT ("mt03")
            MT03 ()
        }

        If (RUN0)
        {
            SRMT ("mt04")
            MT04 ()
        }

        If (LAnd (CHK0, RUN0))
        {
            SRMT ("mt05")
            MT05 ()
        }

        If (RUN0)
        {
            SRMT ("mt06")
            MT06 ()
        }

        If (0x00)
        {
            SRMT ("mt07")
            MT07 ()
        }

        If (CHK0)
        {
            SRMT ("mt08")
            MT08 ()
        }

        SRMT ("mt0a")
        MT0A ()
        SRMT ("mt0b")
        MT0B ()
        If (RUN0)
        {
            SRMT ("mt0c")
            MT0C ()
        }

        SRMT ("mt0d")
        MT0D ()
        If (0x00)
        {
            SRMT ("mt0e")
            MT0E ()
        }

        If (RUN0)
        {
            SRMT ("mt0f")
            MT0F ()
        }

        If (LAnd (CHK0, RUN0))
        {
            SRMT ("mt10")
            MT10 ()
        }

        If (RUN0)
        {
            SRMT ("mt11")
            MT11 ()
        }

        If (LAnd (CHK0, RUN0))
        {
            SRMT ("mt12")
            MT12 ()
        }

        SRMT ("mt13")
        MT13 ()
        If (CHK0)
        {
            SRMT ("mt14")
            MT14 ()
            SRMT ("mt15")
            MT15 ()
        }

        If (CHK0)
        {
            SRMT ("mt16-0")
            MT16 (0x00)
        }

        If (RUN0)
        {
            SRMT ("mt16-1")
            MT16 (0x01)
            SRMT ("mt16-2")
            MT16 (0x02)
            SRMT ("mt16-3")
            MT16 (0x03)
        }

        If (CHK0)
        {
            SRMT ("mt17-0")
            MT17 (0x00)
        }

        If (LAnd (CHK0, RUN0))
        {
            SRMT ("mt17-1")
            MT17 (0x01)
            SRMT ("mt17-2")
            MT17 (0x02)
        }

        SRMT ("mt18-0")
        MT18 (0x00)
        SRMT ("mt18-1")
        MT18 (0x01)
        SRMT ("mt19-0")
        MT19 (0x00)
        SRMT ("mt19-1")
        MT19 (0x01)
        SRMT ("mt1a-0")
        MT1A (0x00)
        SRMT ("mt1a-1")
        MT1A (0x01)
    }

    Name (Z172, 0xAC)
    Name (IG00, 0x00)
    Name (IG01, 0x00)
    Name (IG02, 0x00)
    Name (IG03, 0x00)
    Name (RC00, 0x05)
    Name (RCFF, 0x01)
    Name (TS, "mr00")
    Processor (PR00, 0x00, 0x00000000, 0x08)
    {
        Name (I000, 0xABCD0000)
    }

    Method (MRFD, 0, NotSerialized)
    {
        Store (0x00, IG00) /* \IG00 */
        Store (0x00, IG01) /* \IG01 */
        Store (0x00, IG02) /* \IG02 */
        Store (0x00, IG03) /* \IG03 */
    }

    Method (MRFE, 1, NotSerialized)
    {
        If (RCFF)
        {
            Store (Arg0, Debug)
        }
    }

    Method (MR00, 0, NotSerialized)
    {
        Store ("mr00", TS) /* \TS__ */
        MRFE (TS)
        Store (IG00, Local0)
        Increment (IG00)
        Increment (IG02)
        If (LLess (IG00, RC00))
        {
            MR00 ()
        }

        Decrement (IG00)
        If (LNotEqual (Local0, IG00))
        {
            ERR (TS, Z172, 0x58, 0x00, 0x00, Local0, IG00)
        }

        If (LNotEqual (IG02, RC00))
        {
            If (LNot (IG03))
            {
                Store (0x01, IG03) /* \IG03 */
                ERR (TS, Z172, 0x5E, 0x00, 0x00, IG02, RC00)
            }
        }
    }

    Method (MR01, 1, NotSerialized)
    {
        Store ("mr01", TS) /* \TS__ */
        MRFE (TS)
        Store (IG00, Local1)
        Store (Arg0, Local2)
        Increment (IG00)
        Increment (IG02)
        If (LLess (IG00, RC00))
        {
            MR02 (IG00)
        }

        Decrement (IG00)
        If (LNotEqual (Local1, IG00))
        {
            ERR (TS, Z172, 0x78, 0x00, 0x00, Local1, IG00)
        }

        If (LNotEqual (Local2, Arg0))
        {
            ERR (TS, Z172, 0x7B, 0x00, 0x00, Local2, Arg0)
        }

        Multiply (RC00, 0x02, Local0)
        Decrement (Local0)
        If (LNotEqual (IG02, Local0))
        {
            If (LNot (IG03))
            {
                Store (0x01, IG03) /* \IG03 */
                ERR (TS, Z172, 0x83, 0x00, 0x00, IG02, Local0)
            }
        }
    }

    Method (MR02, 1, NotSerialized)
    {
        Store ("mr02", TS) /* \TS__ */
        MRFE (TS)
        Store (IG01, Local1)
        Store (Arg0, Local2)
        Increment (IG01)
        Increment (IG02)
        If (LLess (IG01, RC00))
        {
            MR01 (IG01)
        }

        Decrement (IG01)
        If (LNotEqual (Local1, IG01))
        {
            ERR (TS, Z172, 0x98, 0x00, 0x00, Local1, IG01)
        }

        If (LNotEqual (Local2, Arg0))
        {
            ERR (TS, Z172, 0x9B, 0x00, 0x00, Local2, Arg0)
        }

        Multiply (RC00, 0x02, Local0)
        Decrement (Local0)
        If (LNotEqual (IG02, Local0))
        {
            If (LNot (IG03))
            {
                Store (0x01, IG03) /* \IG03 */
                ERR (TS, Z172, 0xA3, 0x00, 0x00, IG02, Local0)
            }
        }
    }

    Method (MR03, 0, Serialized)
    {
        Store ("mr03", TS) /* \TS__ */
        Device (D100)
        {
            Name (I200, 0xABCD0200)
            Name (I201, 0xABCD0201)
        }

        Device (D101)
        {
            Name (I202, 0xABCD0202)
            Method (M203, 0, NotSerialized)
            {
                MRFE ("m203")
                Store (IG00, Local0)
                Increment (IG00)
                Increment (IG02)
                If (LLess (IG00, RC00))
                {
                    M203 ()
                }

                Decrement (IG00)
                If (LNotEqual (Local0, IG00))
                {
                    ERR (TS, Z172, 0xC6, 0x00, 0x00, Local0, IG00)
                }
            }

            Name (I204, 0xABCD0204)
        }

        Device (D102)
        {
            Name (I205, 0xABCD0205)
            Name (I206, 0xABCD0206)
        }

        D101.M203 ()
        If (LNotEqual (IG02, RC00))
        {
            If (LNot (IG03))
            {
                Store (0x01, IG03) /* \IG03 */
                ERR (TS, Z172, 0xD7, 0x00, 0x00, IG02, RC00)
            }
        }
    }

    Method (MR04, 0, Serialized)
    {
        Store ("mr04", TS) /* \TS__ */
        Device (D100)
        {
            Name (I200, 0xABCD0200)
            Name (I201, 0xABCD0201)
        }

        Device (D101)
        {
            Name (I202, 0xABCD0202)
            Method (M203, 1, NotSerialized)
            {
                MRFE ("m203")
                Store (IG00, Local0)
                Increment (IG00)
                Increment (IG02)
                If (LLess (IG00, RC00))
                {
                    MR05 (IG00)
                }

                Decrement (IG00)
                If (LNotEqual (Local0, IG00))
                {
                    ERR (TS, Z172, 0xFF, 0x00, 0x00, Local0, IG00)
                }
            }

            Name (I204, 0xABCD0204)
        }

        Device (D102)
        {
            Name (I205, 0xABCD0205)
            Name (I206, 0xABCD0206)
        }

        D101.M203 (0x00)
        Multiply (RC00, 0x02, Local0)
        Decrement (Local0)
        If (LNotEqual (IG02, Local0))
        {
            If (LNot (IG03))
            {
                Store (0x01, IG03) /* \IG03 */
                ERR (TS, Z172, 0x0112, 0x00, 0x00, IG02, Local0)
            }
        }
    }

    Method (MR05, 1, NotSerialized)
    {
        Store ("mr05", TS) /* \TS__ */
        MRFE (TS)
        Store (IG01, Local1)
        Store (Arg0, Local2)
        Increment (IG01)
        Increment (IG02)
        If (LLess (IG01, RC00))
        {
            ^MR04.D101.M203 (IG01)
        }

        Decrement (IG01)
        If (LNotEqual (Local1, IG01))
        {
            ERR (TS, Z172, 0x0127, 0x00, 0x00, Local1, IG01)
        }

        If (LNotEqual (Local2, Arg0))
        {
            ERR (TS, Z172, 0x012A, 0x00, 0x00, Local2, Arg0)
        }

        Multiply (RC00, 0x02, Local0)
        Decrement (Local0)
        If (LNotEqual (IG02, Local0))
        {
            If (LNot (IG03))
            {
                Store (0x01, IG03) /* \IG03 */
                ERR (TS, Z172, 0x0132, 0x00, 0x00, IG02, Local0)
            }
        }
    }

    Method (MRFF, 0, Serialized)
    {
        Name (TS, "mrff")
        Name (RUN0, 0x01)
        CH03 (TS, Z172, 0x00, 0x013D, 0x00)
        SRMT ("mr00")
        MRFD ()
        MR00 ()
        SRMT ("mr01")
        MRFD ()
        MR01 (0x00)
        SRMT ("mr02")
        MRFD ()
        MR02 (0x00)
        SRMT ("mr03")
        MRFD ()
        MR03 ()
        SRMT ("mr04")
        MRFD ()
        MR04 ()
        CH03 (TS, Z172, 0x00, 0x0158, 0x00)
    }

    Name (FIX0, 0x01)
    Name (FIX1, 0x01)
    Name (CHK0, 0x00)
    Name (CHK1, 0x01)
    Name (CHK2, 0x00)
    Name (PRT0, 0x00)
    Name (SLC0, 0x00)
    Method (IIN1, 0, NotSerialized)
    {
        If (RUN4)
        {
            Store (0x01, Y262) /* \Y262 */
            Store (0x01, Y275) /* \Y275 */
            Store (0x01, SLC0) /* \SLC0 */
            Store (0x00, SLCK) /* \SLCK */
        }
        Else
        {
            OUTP ("WARNING: don\'t forget to check run4 !!!!!!!!!!")
            Store (0x00, SLC0) /* \SLC0 */
            If (SLCK)
            {
                Store (0x01, SLC0) /* \SLC0 */
            }
        }

        If (ABUU)
        {
            Store (0x00, CHK0) /* \CHK0 */
            Store (0x01, CHK1) /* \CHK1 */
            Store (0x00, CHK2) /* \CHK2 */
            Store (0x00, FIX0) /* \FIX0 */
            Store (0x00, FIX1) /* \FIX1 */
        }
        Else
        {
            Store (0x01, CHK0) /* \CHK0 */
            Store (0x01, CHK1) /* \CHK1 */
            Store (0x01, CHK2) /* \CHK2 */
            Store (0x01, FIX0) /* \FIX0 */
            Store (0x00, FIX1) /* \FIX1 */
        }
    }

    Method (LF00, 0, NotSerialized)
    {
        IIN0 ()
        MF00 ()
        Return (POUT) /* \POUT */
    }

    Method (LF01, 0, NotSerialized)
    {
        IIN0 ()
        MF01 ()
        Return (POUT) /* \POUT */
    }

    Method (LF02, 0, NotSerialized)
    {
        IIN0 ()
        MF02 ()
        Return (POUT) /* \POUT */
    }

    Method (LF03, 0, NotSerialized)
    {
        IIN0 ()
        MF03 ()
        Return (POUT) /* \POUT */
    }

    Method (LF04, 0, NotSerialized)
    {
        IIN0 ()
        MF04 ()
        Return (POUT) /* \POUT */
    }

    Method (LF05, 0, NotSerialized)
    {
        IIN0 ()
        MF05 ()
        Return (POUT) /* \POUT */
    }

    Method (LF06, 0, NotSerialized)
    {
        IIN0 ()
        MF06 ()
        Return (POUT) /* \POUT */
    }

    Method (LF07, 0, NotSerialized)
    {
        IIN0 ()
        MF07 ()
        Return (POUT) /* \POUT */
    }

    Method (LF08, 0, NotSerialized)
    {
        IIN0 ()
        MF08 ()
        Return (POUT) /* \POUT */
    }

    Method (LF09, 0, NotSerialized)
    {
        IIN0 ()
        MF09 ()
        Return (POUT) /* \POUT */
    }

    Method (LF0A, 0, NotSerialized)
    {
        IIN0 ()
        MF0A ()
        Return (POUT) /* \POUT */
    }

    Method (LF0B, 0, NotSerialized)
    {
        IIN0 ()
        MF0B ()
        Return (POUT) /* \POUT */
    }

    Method (LF0C, 0, NotSerialized)
    {
        IIN0 ()
        MF0C ()
        Return (POUT) /* \POUT */
    }

    Method (LF0D, 0, NotSerialized)
    {
        IIN0 ()
        MF0D ()
        Return (POUT) /* \POUT */
    }

    Method (LF0E, 0, NotSerialized)
    {
        IIN0 ()
        MF0E ()
        Return (POUT) /* \POUT */
    }

    Method (LF0F, 0, NotSerialized)
    {
        IIN0 ()
        MF0F ()
        Return (POUT) /* \POUT */
    }

    Method (LF10, 0, NotSerialized)
    {
        IIN0 ()
        MF10 ()
        Return (POUT) /* \POUT */
    }

    Method (LF11, 0, NotSerialized)
    {
        IIN0 ()
        MF11 ()
        Return (POUT) /* \POUT */
    }

    Method (LF12, 0, NotSerialized)
    {
        IIN0 ()
        MF12 ()
        Return (POUT) /* \POUT */
    }

    Method (LF13, 0, NotSerialized)
    {
        IIN0 ()
        MF13 ()
        Return (POUT) /* \POUT */
    }

    Method (LF14, 0, NotSerialized)
    {
        IIN0 ()
        MF14 ()
        Return (POUT) /* \POUT */
    }

    Method (LF15, 0, NotSerialized)
    {
        IIN0 ()
        MF15 ()
        Return (POUT) /* \POUT */
    }

    Method (LF16, 0, NotSerialized)
    {
        IIN0 ()
        MF16 ()
        Return (POUT) /* \POUT */
    }

    Method (LF17, 0, NotSerialized)
    {
        IIN0 ()
        MF17 ()
        Return (POUT) /* \POUT */
    }

    Method (LF18, 0, NotSerialized)
    {
        IIN0 ()
        MF18 ()
        Return (POUT) /* \POUT */
    }

    Method (LF19, 0, NotSerialized)
    {
        IIN0 ()
        MF19 ()
        Return (POUT) /* \POUT */
    }

    Method (LF1A, 0, NotSerialized)
    {
        IIN0 ()
        MF1A ()
        Return (POUT) /* \POUT */
    }

    Method (LF1B, 0, NotSerialized)
    {
        IIN0 ()
        MF1B ()
        Return (POUT) /* \POUT */
    }

    Method (LF1C, 0, NotSerialized)
    {
        IIN0 ()
        MF1C ()
        Return (POUT) /* \POUT */
    }

    Method (LF1D, 0, NotSerialized)
    {
        IIN0 ()
        MF1D ()
        Return (POUT) /* \POUT */
    }

    Method (LF1E, 0, NotSerialized)
    {
        IIN0 ()
        MF1E ()
        Return (POUT) /* \POUT */
    }

    Method (LF1F, 0, NotSerialized)
    {
        IIN0 ()
        MF1F ()
        Return (POUT) /* \POUT */
    }

    Method (LF20, 0, NotSerialized)
    {
        IIN0 ()
        MF20 ()
        Return (POUT) /* \POUT */
    }

    Method (LF21, 0, NotSerialized)
    {
        IIN0 ()
        MF21 ()
        Return (POUT) /* \POUT */
    }

    Method (LF22, 0, NotSerialized)
    {
        IIN0 ()
        MF22 ()
        Return (POUT) /* \POUT */
    }

    Method (LF23, 0, NotSerialized)
    {
        IIN0 ()
        MF23 ()
        Return (POUT) /* \POUT */
    }

    Method (LF24, 0, NotSerialized)
    {
        IIN0 ()
        MF24 ()
        Return (POUT) /* \POUT */
    }

    Method (LF25, 0, NotSerialized)
    {
        IIN0 ()
        MF25 ()
        Return (POUT) /* \POUT */
    }

    Method (LF26, 0, NotSerialized)
    {
        IIN0 ()
        MF26 ()
        Return (POUT) /* \POUT */
    }

    Method (LF27, 0, NotSerialized)
    {
        IIN0 ()
        MF27 ()
        Return (POUT) /* \POUT */
    }

    Method (LF28, 0, NotSerialized)
    {
        IIN0 ()
        MF28 ()
        Return (POUT) /* \POUT */
    }

    Method (LF29, 0, NotSerialized)
    {
        IIN0 ()
        MF29 (0x00)
        Return (POUT) /* \POUT */
    }

    Method (LF2A, 0, NotSerialized)
    {
        IIN0 ()
        MF2A (0x00)
        Return (POUT) /* \POUT */
    }

    Method (LF2B, 0, NotSerialized)
    {
        IIN0 ()
        MF2B ()
        Return (POUT) /* \POUT */
    }

    Method (LF2C, 0, NotSerialized)
    {
        IIN0 ()
        MF2C (0x00)
        Return (POUT) /* \POUT */
    }

    Method (LF2D, 0, NotSerialized)
    {
        IIN0 ()
        MT0E ()
        Return (POUT) /* \POUT */
    }

    Name (Z163, 0xA3)
    Method (IN00, 1, Serialized)
    {
        Name (TS, "in00")
        Name (I000, 0x01)
        Name (P000, Package (0x04)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04
        })
        Name (I001, 0x00)
        Store (Arg0, I001) /* \IN00.I001 */
        Method (M001, 0, NotSerialized)
        {
            Method (M002, 0, NotSerialized)
            {
                Method (M003, 0, NotSerialized)
                {
                    If (I001)
                    {
                        CopyObject (P000, I000) /* \IN00.I000 */
                    }

                    Return (0xABCD0000)
                }

                Return (Add (I000, M003 ()))
            }

            Return (Add (I000, M002 ()))
        }

        Store (Add (I000, M001 ()), Local0)
        If (LNotEqual (Local0, 0xABCD0003))
        {
            ERR (TS, Z163, 0x55, 0x00, 0x00, Local0, 0xABCD0003)
        }
    }

    Method (IN01, 1, Serialized)
    {
        Name (TS, "in01")
        Name (I000, 0x01)
        Name (I001, 0x00)
        Name (P000, Package (0x04)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04
        })
        Store (Arg0, I001) /* \IN01.I001 */
        Method (M001, 0, NotSerialized)
        {
            Method (M002, 0, NotSerialized)
            {
                Method (M003, 0, NotSerialized)
                {
                    Method (M004, 0, NotSerialized)
                    {
                        Method (M005, 0, NotSerialized)
                        {
                            Method (M006, 0, NotSerialized)
                            {
                                Method (M007, 0, NotSerialized)
                                {
                                    Method (M008, 0, NotSerialized)
                                    {
                                        If (I001)
                                        {
                                            CopyObject (P000, I000) /* \IN01.I000 */
                                        }

                                        Return (0x00)
                                    }

                                    Store (0x80000000, I000) /* \IN01.I000 */
                                    Return (Add (I000, M008 ()))
                                }

                                Store (0x07000000, I000) /* \IN01.I000 */
                                Return (Add (I000, M007 ()))
                            }

                            Store (0x00600000, I000) /* \IN01.I000 */
                            Return (Add (I000, M006 ()))
                        }

                        Store (0x00050000, I000) /* \IN01.I000 */
                        Return (Add (I000, M005 ()))
                    }

                    Store (0x4000, I000) /* \IN01.I000 */
                    Return (Add (I000, M004 ()))
                }

                Store (0x0300, I000) /* \IN01.I000 */
                Return (Add (I000, M003 ()))
            }

            Store (0x20, I000) /* \IN01.I000 */
            Return (Add (I000, M002 ()))
        }

        Store (Add (I000, M001 ()), Local0)
        If (LNotEqual (Local0, 0x87654321))
        {
            ERR (TS, Z163, 0x95, 0x00, 0x00, Local0, 0x87654321)
        }

        If (LNotEqual (I000, 0x80000000))
        {
            ERR (TS, Z163, 0x99, 0x00, 0x00, I000, 0x80000000)
        }
    }

    Method (IN02, 0, Serialized)
    {
        Name (TS, "in02")
        Name (I000, 0x00100000)
        Name (I001, 0x00)
        Method (M001, 0, NotSerialized)
        {
            If (LLess (I001, 0x0B))
            {
                Increment (I000)
                Increment (I001)
                Add (I000, M001 (), Local0)
                Return (Local0)
            }

            Return (0x00)
        }

        Store (Add (I000, M001 ()), Local0)
        If (LNotEqual (Local0, 0x00C00042))
        {
            ERR (TS, Z163, 0xB8, 0x00, 0x00, Local0, 0x00C00042)
        }

        If (LNotEqual (I000, 0x0010000B))
        {
            ERR (TS, Z163, 0xBC, 0x00, 0x00, I000, 0x0010000B)
        }
    }

    Method (IN03, 1, Serialized)
    {
        Name (TS, "in03")
        Name (I001, 0x00)
        Name (P000, Package (0x04)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04
        })
        Store (Arg0, I001) /* \IN03.I001 */
        Store (0x01, Local7)
        Method (M001, 0, NotSerialized)
        {
            Method (M002, 0, NotSerialized)
            {
                Method (M003, 0, NotSerialized)
                {
                    Method (M004, 0, NotSerialized)
                    {
                        Method (M005, 0, NotSerialized)
                        {
                            Method (M006, 0, NotSerialized)
                            {
                                Method (M007, 0, NotSerialized)
                                {
                                    Method (M008, 0, NotSerialized)
                                    {
                                        If (I001)
                                        {
                                            CopyObject (P000, Local7)
                                        }

                                        Return (0x00)
                                    }

                                    Store (0x80000000, Local7)
                                    Return (Add (Local7, M008 ()))
                                }

                                Store (0x07000000, Local7)
                                Return (Add (Local7, M007 ()))
                            }

                            Store (0x00600000, Local7)
                            Return (Add (Local7, M006 ()))
                        }

                        Store (0x00050000, Local7)
                        Return (Add (Local7, M005 ()))
                    }

                    Store (0x4000, Local7)
                    Return (Add (Local7, M004 ()))
                }

                Store (0x0300, Local7)
                Return (Add (Local7, M003 ()))
            }

            Store (0x20, Local7)
            Return (Add (Local7, M002 ()))
        }

        Store (Add (Local7, M001 ()), Local0)
        If (LNotEqual (Local0, 0x87654321))
        {
            ERR (TS, Z163, 0xFB, 0x00, 0x00, Local0, 0x87654321)
        }

        If (LNotEqual (Local7, 0x01))
        {
            ERR (TS, Z163, 0xFF, 0x00, 0x00, Local7, 0x01)
        }
    }

    Method (IN04, 0, Serialized)
    {
        Name (TS, "in04")
        Name (I000, 0x01)
        Name (I001, 0x00)
        Name (P000, Package (0x04)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04
        })
        Method (M001, 2, NotSerialized)
        {
            Method (M002, 2, NotSerialized)
            {
                Method (M003, 2, NotSerialized)
                {
                    Method (M004, 2, NotSerialized)
                    {
                        Method (M005, 2, NotSerialized)
                        {
                            Method (M006, 2, NotSerialized)
                            {
                                Method (M007, 2, NotSerialized)
                                {
                                    Store (0x80000000, I000) /* \IN04.I000 */
                                    Store (0x10000007, Arg0)
                                    Add (I000, 0x00, Local0)
                                    Return (Local0)
                                }

                                Store (0x07000000, I000) /* \IN04.I000 */
                                Store (0x10000006, Arg0)
                                Return (Add (I000, M007 (I000, Arg0)))
                            }

                            Store (0x00600000, I000) /* \IN04.I000 */
                            Store (0x10000005, Arg0)
                            Return (Add (I000, M006 (I000, Arg0)))
                        }

                        Store (0x00050000, I000) /* \IN04.I000 */
                        Store (0x10000004, Arg0)
                        Return (Add (I000, M005 (I000, Arg0)))
                    }

                    If (LNotEqual (Arg0, 0x0300))
                    {
                        ERR (TS, Z163, 0x0158, 0x00, 0x00, Arg0, 0x0300)
                    }

                    If (LNotEqual (Arg1, 0x10000001))
                    {
                        ERR (TS, Z163, 0x015B, 0x00, 0x00, Arg1, 0x10000001)
                    }

                    Store (0x4000, I000) /* \IN04.I000 */
                    Store (0x10000003, Arg0)
                    Return (Add (I000, M004 (I000, Arg0)))
                }

                If (LNotEqual (Arg0, 0x20))
                {
                    ERR (TS, Z163, 0x0162, 0x00, 0x00, Arg0, 0x20)
                }

                If (LNotEqual (I000, 0x20))
                {
                    ERR (TS, Z163, 0x0165, 0x00, 0x00, I000, 0x20)
                }

                Store (0x10000002, Arg0)
                If (LNotEqual (I000, 0x20))
                {
                    ERR (TS, Z163, 0x0169, 0x00, 0x00, I000, 0x20)
                }

                If (LNotEqual (Arg0, 0x10000002))
                {
                    ERR (TS, Z163, 0x016C, 0x00, 0x00, Arg0, 0x10000002)
                }

                Store (0x0300, I000) /* \IN04.I000 */
                If (LNotEqual (I000, 0x0300))
                {
                    ERR (TS, Z163, 0x0170, 0x00, 0x00, I000, 0x0300)
                }

                If (LNotEqual (Arg0, 0x10000002))
                {
                    ERR (TS, Z163, 0x0173, 0x00, 0x00, Arg0, 0x10000002)
                }

                If (LNotEqual (Arg1, 0x10000001))
                {
                    ERR (TS, Z163, 0x0176, 0x00, 0x00, Arg1, 0x10000001)
                }

                Store (0x10000002, Arg0)
                Store (0x0300, I000) /* \IN04.I000 */
                Return (Add (I000, M003 (I000, Arg1)))
            }

            If (LNotEqual (Arg0, 0x01))
            {
                ERR (TS, Z163, 0x017D, 0x00, 0x00, Arg0, 0x01)
            }

            If (LNotEqual (I000, 0x01))
            {
                ERR (TS, Z163, 0x0180, 0x00, 0x00, I000, 0x01)
            }

            Store (0x10000001, Arg0)
            If (LNotEqual (I000, 0x01))
            {
                ERR (TS, Z163, 0x0184, 0x00, 0x00, I000, 0x01)
            }

            If (LNotEqual (Arg0, 0x10000001))
            {
                ERR (TS, Z163, 0x0187, 0x00, 0x00, Arg0, 0x10000001)
            }

            Store (0x20, I000) /* \IN04.I000 */
            If (LNotEqual (I000, 0x20))
            {
                ERR (TS, Z163, 0x018B, 0x00, 0x00, I000, 0x20)
            }

            If (LNotEqual (Arg0, 0x10000001))
            {
                ERR (TS, Z163, 0x018E, 0x00, 0x00, Arg0, 0x10000001)
            }

            If (LNotEqual (Arg1, 0x10000000))
            {
                ERR (TS, Z163, 0x0191, 0x00, 0x00, Arg1, 0x10000000)
            }

            Store (0x10000001, Arg0)
            Store (0x20, I000) /* \IN04.I000 */
            Return (Add (I000, M002 (I000, Arg0)))
        }

        Store (Add (I000, M001 (I000, 0x10000000)), Local0)
        If (LNotEqual (Local0, 0x87654321))
        {
            ERR (TS, Z163, 0x019A, 0x00, 0x00, Local0, 0x87654321)
        }

        If (LNotEqual (I000, 0x80000000))
        {
            ERR (TS, Z163, 0x019E, 0x00, 0x00, I000, 0x80000000)
        }
    }

    Method (IN05, 0, Serialized)
    {
        Name (TS, "in05")
        Name (I000, 0xABCD0000)
        Name (S000, "qwrtyu0003")
        Name (B000, Buffer (0x05)
        {
             0xB0, 0xB1, 0xB2, 0xB3, 0xB4                     // .....
        })
        Name (P000, Package (0x03)
        {
            0xABCD0001, 
            0xABCD0002, 
            0xABCD0003
        })
        Event (E000)
        Mutex (MX00, 0x00)
        Method (MMM0, 0, Serialized)
        {
            Name (IM00, 0xABCD0004)
            Name (SM00, "qwertyui")
        }

        Method (MMM1, 0, Serialized)
        {
            Name (IM00, 0xABCD0004)
            Name (SM00, "qwertyui")
            Return ("qwertyui")
        }

        Device (D000)
        {
            Name (ID00, 0xABCD0005)
        }

        ThermalZone (TZ00)
        {
            Name (ITZ0, 0xABCD0006)
        }

        Processor (PR00, 0x00, 0xFFFFFFFF, 0x00)
        {
            Name (IPR0, 0xABCD0007)
        }

        PowerResource (PW00, 0x01, 0x0000)
        {
            Name (IPW0, 0xABCD0008)
        }

        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Name (B001, Buffer (0x05)
        {
             0xA0, 0xA1, 0xA2, 0xA3, 0xA4                     // .....
        })
        CreateField (B001, 0x00, 0x08, BF00)
        OperationRegion (R001, SystemMemory, 0x0100, 0x0100)
        Field (R001, ByteAcc, NoLock, Preserve)
        {
            F000,   32, 
            F001,   32, 
            F002,   32, 
            F003,   32
        }

        BankField (R001, F001, 0x00
, ByteAcc, NoLock, Preserve)
        {
            BNK0,   32
        }

        IndexField (F002, F003, ByteAcc, NoLock, Preserve)
        {
            IF00,   32, 
            IF01,   32
        }

        Method (M001, 2, NotSerialized)
        {
            Store (ObjectType (Arg0), Local0)
            If (LNotEqual (Local0, Arg1))
            {
                ERR (TS, Z163, 0x01CC, 0x00, 0x00, Local0, Arg1)
            }

            Return (0x05)
        }

        CH03 (TS, Z163, 0x00, 0x01D1, 0x00)
        Store (Add (DerefOf (Index (P000, 0x00)), M001 (I000, C009)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x01D5, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (S000, C00A)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x01D9, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (B000, C00B)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x01DD, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (P000, C00C)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x01E1, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (E000, C00F)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x01E5, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (MX00, C011)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x01E9, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (MMM0 (), C008)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x01ED, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (MMM1 (), C00A)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x01F1, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (D000, C00E)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x01F5, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (TZ00, C015)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x01F9, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (PR00, C014)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x01FD, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (PW00, C013)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x0201, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (R000, C012)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x0205, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (BF00, C00B)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x0209, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (F000, C009)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x020D, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (BNK0, C009)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x0211, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (Add (DerefOf (Index (P000, 0x00)), M001 (IF00, C009)), Local0)
        If (LNotEqual (Local0, 0xABCD0006))
        {
            ERR (TS, Z163, 0x0215, 0x00, 0x00, Local0, 0xABCD0006)
        }

        Store (ObjectType (F000), Local0)
        If (LNotEqual (Local0, C00D))
        {
            ERR (TS, Z163, 0x021B, 0x00, 0x00, Local0, C00D)
        }

        Store (ObjectType (IF00), Local0)
        If (LNotEqual (Local0, C00D))
        {
            ERR (TS, Z163, 0x021F, 0x00, 0x00, Local0, C00D)
        }

        Store (ObjectType (BNK0), Local0)
        If (LNotEqual (Local0, C00D))
        {
            ERR (TS, Z163, 0x0223, 0x00, 0x00, Local0, C00D)
        }

        Store (ObjectType (BF00), Local0)
        If (LNotEqual (Local0, C016))
        {
            ERR (TS, Z163, 0x0227, 0x00, 0x00, Local0, C016)
        }

        CH03 (TS, Z163, 0x00, 0x022A, 0x00)
    }

    Method (IN06, 0, Serialized)
    {
        Name (TS, "in06")
        Name (I000, 0xABCD0000)
        Store (ObjectType (I000), Local0)
        If (LNotEqual (Local0, C009))
        {
            ERR (TS, Z163, 0x0234, 0x00, 0x00, Local0, C009)
        }
    }

    Method (INI0, 0, NotSerialized)
    {
        SRMT ("in00-0")
        IN00 (0x00)
        SRMT ("in01-0")
        IN01 (0x00)
        SRMT ("in02")
        IN02 ()
        SRMT ("in03-0")
        IN03 (0x00)
        SRMT ("in04")
        IN04 ()
        SRMT ("in05")
        If (LAnd (FIX1, CHK2))
        {
            IN05 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("in06")
        IN06 ()
        CH03 ("ini0", Z163, 0x00, 0x0252, 0x00)
    }

    Name (Z164, 0xA4)
    Method (IN10, 0, Serialized)
    {
        Name (TS, "in10")
        Name (P000, Package (0x03)
        {
            0xABCD0000, 
            0xABCD0001, 
            0xABCD0002
        })
        Method (M001, 2, NotSerialized)
        {
            Store (DerefOf (Index (Arg0, 0x00)), Local0)
            If (LNotEqual (Local0, 0xABCD0000))
            {
                ERR (TS, Z164, 0x44, 0x00, 0x00, Local0, 0xABCD0000)
            }

            Store (0x11112222, Index (Arg0, 0x00))
            Store (DerefOf (Index (Arg0, 0x00)), Local0)
            If (LNotEqual (Local0, 0x11112222))
            {
                ERR (TS, Z164, 0x4B, 0x00, 0x00, Local0, 0x11112222)
            }
        }

        M001 (P000, RefOf (P000))
        Store (DerefOf (Index (P000, 0x00)), Local0)
        If (LNotEqual (Local0, 0x11112222))
        {
            ERR (TS, Z164, 0x53, 0x00, 0x00, Local0, 0x11112222)
        }

        Store (DerefOf (Index (P000, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z164, 0x58, 0x00, 0x00, Local0, 0xABCD0001)
        }
    }

    Method (IN11, 0, Serialized)
    {
        Name (TS, "in11")
        Name (P000, Package (0x03)
        {
            0xABCD0000, 
            0xABCD0001, 
            0xABCD0002
        })
        Method (M001, 2, NotSerialized)
        {
            Store (DerefOf (Arg1), Local7)
            Store (DerefOf (Index (Local7, 0x01)), Local0)
            If (LNotEqual (Local0, 0xABCD0001))
            {
                ERR (TS, Z164, 0x6A, 0x00, 0x00, Local0, 0xABCD0001)
            }

            Store (0x33334444, Index (Local7, 0x01))
            Store (DerefOf (Index (Local7, 0x01)), Local0)
            If (LNotEqual (Local0, 0x33334444))
            {
                ERR (TS, Z164, 0x71, 0x00, 0x00, Local0, 0x33334444)
            }
        }

        M001 (P000, RefOf (P000))
        Store (DerefOf (Index (P000, 0x00)), Local0)
        If (LNotEqual (Local0, 0xABCD0000))
        {
            ERR (TS, Z164, 0x79, 0x00, 0x00, Local0, 0xABCD0000)
        }

        Store (DerefOf (Index (P000, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z164, 0x7E, 0x00, 0x00, Local0, 0xABCD0001)
        }
    }

    Method (IN12, 0, Serialized)
    {
        Name (TS, "in12")
        Name (P000, Package (0x03)
        {
            0xABCD0000, 
            0xABCD0001, 
            0xABCD0002
        })
        Method (M001, 2, NotSerialized)
        {
            Store (0x11112222, Index (Arg0, 0x00))
            Store (DerefOf (Index (Arg0, 0x00)), Local0)
            If (LNotEqual (Local0, 0x11112222))
            {
                ERR (TS, Z164, 0x91, 0x00, 0x00, Local0, 0x11112222)
            }

            Store (DerefOf (Arg1), Local7)
            Store (0x33334444, Index (Local7, 0x01))
            Store (DerefOf (Index (Local7, 0x01)), Local0)
            If (LNotEqual (Local0, 0x33334444))
            {
                ERR (TS, Z164, 0x99, 0x00, 0x00, Local0, 0x33334444)
            }
        }

        M001 (P000, RefOf (P000))
        Store (DerefOf (Index (P000, 0x00)), Local0)
        If (LNotEqual (Local0, 0x11112222))
        {
            ERR (TS, Z164, 0xA1, 0x00, 0x00, Local0, 0x11112222)
        }

        Store (DerefOf (Index (P000, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z164, 0xA6, 0x00, 0x00, Local0, 0xABCD0001)
        }
    }

    Method (IN13, 0, Serialized)
    {
        Name (TS, "in13")
        Name (P000, Package (0x03)
        {
            0xABCD0000, 
            0xABCD0001, 
            0xABCD0002
        })
        Method (M001, 2, NotSerialized)
        {
            Store (RefOf (P000), Local6)
            Store (DerefOf (Local6), Local7)
            Store (DerefOf (Index (Local7, 0x01)), Local0)
            If (LNotEqual (Local0, 0xABCD0001))
            {
                ERR (TS, Z164, 0xBA, 0x00, 0x00, Local0, 0xABCD0001)
            }

            Store (0x33334444, Index (Local7, 0x01))
            Store (DerefOf (Index (Local7, 0x01)), Local0)
            If (LNotEqual (Local0, 0x33334444))
            {
                ERR (TS, Z164, 0xC1, 0x00, 0x00, Local0, 0x33334444)
            }
        }

        M001 (P000, RefOf (P000))
        Store (DerefOf (Index (P000, 0x00)), Local0)
        If (LNotEqual (Local0, 0xABCD0000))
        {
            ERR (TS, Z164, 0xC9, 0x00, 0x00, Local0, 0xABCD0000)
        }

        Store (DerefOf (Index (P000, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z164, 0xCD, 0x00, 0x00, Local0, 0xABCD0001)
        }

        Store (DerefOf (Index (P000, 0x02)), Local0)
        If (LNotEqual (Local0, 0xABCD0002))
        {
            ERR (TS, Z164, 0xD1, 0x00, 0x00, Local0, 0xABCD0002)
        }
    }

    Method (IN14, 0, Serialized)
    {
        Name (TS, "in14")
        Name (I000, 0xABCD0000)
        Name (I001, 0xABCD0001)
        Name (I002, 0xABCD0002)
        Name (II00, 0x11112222)
        Name (P000, Package (0x04)
        {
            I000, , 
            I001, , 
            I002, , 
            "i000"
        })
        Method (M001, 2, NotSerialized)
        {
            Store (DerefOf (Index (Arg0, 0x00)), Local0)
            If (LNotEqual (Local0, 0xABCD0000))
            {
                ERR (TS, Z164, 0xF2, 0x00, 0x00, Local0, 0xABCD0000)
            }

            Store (DerefOf (Index (Arg0, 0x01)), Local0)
            If (LNotEqual (Local0, 0xABCD0001))
            {
                ERR (TS, Z164, 0xF6, 0x00, 0x00, Local0, 0xABCD0001)
            }

            Store (DerefOf (Index (Arg0, 0x02)), Local0)
            If (LNotEqual (Local0, 0xABCD0002))
            {
                ERR (TS, Z164, 0xFA, 0x00, 0x00, Local0, 0xABCD0002)
            }

            Store (DerefOf (Index (Arg0, 0x03)), Local0)
            If (LNotEqual (Local0, "i000"))
            {
                ERR (TS, Z164, 0xFE, 0x00, 0x00, Local0, "i000")
            }

            Store (II00, Index (Arg0, 0x00))
            Store (DerefOf (Index (Arg0, 0x00)), Local0)
            If (LNotEqual (Local0, 0x11112222))
            {
                ERR (TS, Z164, 0x0105, 0x00, 0x00, Local0, 0x11112222)
            }
        }

        M001 (P000, RefOf (P000))
        Store (DerefOf (Index (P000, 0x00)), Local0)
        If (LNotEqual (Local0, 0x11112222))
        {
            ERR (TS, Z164, 0x010D, 0x00, 0x00, Local0, 0x11112222)
        }

        Store (DerefOf (Index (P000, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z164, 0x0112, 0x00, 0x00, Local0, 0xABCD0001)
        }

        Store (DerefOf (Index (P000, 0x02)), Local0)
        If (LNotEqual (Local0, 0xABCD0002))
        {
            ERR (TS, Z164, 0x0117, 0x00, 0x00, Local0, 0xABCD0002)
        }

        Store (DerefOf (Index (P000, 0x03)), Local0)
        If (LNotEqual (Local0, "i000"))
        {
            ERR (TS, Z164, 0x011C, 0x00, 0x00, Local0, "i000")
        }
    }

    Method (IN15, 0, Serialized)
    {
        Name (TS, "in15")
        Name (I000, 0xABCD0000)
        Name (I001, 0xABCD0001)
        Name (I002, 0xABCD0002)
        Name (II00, 0x11112222)
        Name (P000, Package (0x04)
        {
            I000, , 
            I001, , 
            I002, , 
            "i000"
        })
        Store (DerefOf (Index (P000, 0x00)), Local0)
        OUTP (Local0)
        Store (DerefOf (Index (P000, 0x01)), Local0)
        OUTP (Local0)
        Store (DerefOf (Index (P000, 0x02)), Local0)
        OUTP (Local0)
        Store (DerefOf (Index (P000, 0x03)), Local0)
        OUTP (Local0)
        Store (II00, Index (P000, 0x01))
        OUTP ("After re-write 1-th element:")
        Store (DerefOf (Index (P000, 0x00)), Local0)
        OUTP (Local0)
        Store (DerefOf (Index (P000, 0x01)), Local0)
        OUTP (Local0)
        Store (DerefOf (Index (P000, 0x02)), Local0)
        OUTP (Local0)
        Store (DerefOf (Index (P000, 0x03)), Local0)
        OUTP (Local0)
    }

    Method (IN16, 0, Serialized)
    {
        Name (TS, "in16")
        Name (B000, Buffer (0x03)
        {
             0x10, 0x11, 0x12                                 // ...
        })
        Method (M001, 2, NotSerialized)
        {
            Store (DerefOf (Index (Arg0, 0x00)), Local0)
            If (LNotEqual (Local0, 0x10))
            {
                ERR (TS, Z164, 0x0158, 0x00, 0x00, Local0, 0x10)
            }

            Store (0x67, Index (Arg0, 0x00))
            Store (DerefOf (Index (Arg0, 0x00)), Local0)
            If (LNotEqual (Local0, 0x67))
            {
                ERR (TS, Z164, 0x015F, 0x00, 0x00, Local0, 0x67)
            }

            Store (DerefOf (Arg1), Local7)
            Store (0x55, Index (Local7, 0x01))
            Store (DerefOf (Index (Local7, 0x01)), Local0)
            If (LNotEqual (Local0, 0x55))
            {
                ERR (TS, Z164, 0x0169, 0x00, 0x00, Local0, 0x55)
            }
        }

        M001 (B000, RefOf (B000))
        Store (DerefOf (Index (B000, 0x00)), Local0)
        If (LNotEqual (Local0, 0x67))
        {
            ERR (TS, Z164, 0x0171, 0x00, 0x00, Local0, 0x67)
        }

        Store (DerefOf (Index (B000, 0x01)), Local0)
        If (LNotEqual (Local0, 0x11))
        {
            ERR (TS, Z164, 0x0176, 0x00, 0x00, Local0, 0x11)
        }

        Store (DerefOf (Index (B000, 0x02)), Local0)
        If (LNotEqual (Local0, 0x12))
        {
            ERR (TS, Z164, 0x017B, 0x00, 0x00, Local0, 0x12)
        }
    }

    Method (IN17, 0, Serialized)
    {
        Name (TS, "in17")
        Name (I001, 0x00)
        Name (PP00, Package (0x03)
        {
            0x11111111, 
            0x00100000, 
            0x22223333
        })
        Method (M001, 0, NotSerialized)
        {
            If (LLess (I001, 0x0B))
            {
                Store (DerefOf (Index (PP00, 0x01)), Local0)
                Increment (Local0)
                Store (Local0, Index (PP00, 0x01))
                Increment (I001)
                Add (DerefOf (Index (PP00, 0x01)), M001 (), Local0)
                Return (Local0)
            }

            Return (0x00)
        }

        Store (Add (DerefOf (Index (PP00, 0x01)), M001 ()), Local0)
        If (LNotEqual (Local0, 0x00C00042))
        {
            ERR (TS, Z164, 0x019E, 0x00, 0x00, Local0, 0x00C00042)
        }

        Store (DerefOf (Index (PP00, 0x01)), Local0)
        If (LNotEqual (Local0, 0x0010000B))
        {
            ERR (TS, Z164, 0x01A4, 0x00, 0x00, Local0, 0x0010000B)
        }

        CH03 (TS, Z164, 0x0C, 0x01A7, 0x00)
    }

    Method (IN18, 1, Serialized)
    {
        Name (TS, "in18")
        Name (I001, 0x00)
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32, 
            F001,   32
        }

        CH03 (TS, Z164, 0x11, 0x01BD, 0x00)
        Store (Arg0, I001) /* \IN18.I001 */
        Method (M001, 0, NotSerialized)
        {
            Method (M002, 0, NotSerialized)
            {
                Method (M003, 0, NotSerialized)
                {
                    Method (M004, 0, NotSerialized)
                    {
                        Method (M005, 0, NotSerialized)
                        {
                            Method (M006, 0, NotSerialized)
                            {
                                Method (M007, 0, NotSerialized)
                                {
                                    Method (M008, 0, NotSerialized)
                                    {
                                        If (I001)
                                        {
                                            Store (0x11223344, F001) /* \IN18.F001 */
                                        }

                                        Return (0x00)
                                    }

                                    Store (0x80000000, F001) /* \IN18.F001 */
                                    Return (Add (F001, M008 ()))
                                }

                                Store (0x07000000, F001) /* \IN18.F001 */
                                Return (Add (F001, M007 ()))
                            }

                            Store (0x00600000, F001) /* \IN18.F001 */
                            Return (Add (F001, M006 ()))
                        }

                        Store (0x00050000, F001) /* \IN18.F001 */
                        Return (Add (F001, M005 ()))
                    }

                    Store (0x4000, F001) /* \IN18.F001 */
                    Return (Add (F001, M004 ()))
                }

                Store (0x0300, F001) /* \IN18.F001 */
                Return (Add (F001, M003 ()))
            }

            Store (0x20, F001) /* \IN18.F001 */
            Return (Add (F001, M002 ()))
        }

        Store (0x01, F001) /* \IN18.F001 */
        Store (Add (F001, M001 ()), Local0)
        If (LNotEqual (Local0, 0x87654321))
        {
            ERR (TS, Z164, 0x01F2, 0x00, 0x00, Local0, 0x87654321)
        }

        If (Arg0)
        {
            Store (0x11223344, Local1)
        }
        Else
        {
            Store (0x80000000, Local1)
        }

        If (LNotEqual (F001, Local1))
        {
            ERR (TS, Z164, 0x01FC, 0x00, 0x00, F001, Local1)
        }

        CH03 (TS, Z164, 0x14, 0x01FF, 0x00)
    }

    Method (IN19, 1, Serialized)
    {
        Name (TS, "in19")
        Name (I001, 0x00)
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32, 
            F001,   32
        }

        BankField (R000, F001, 0x00
, ByteAcc, NoLock, Preserve)
        {
            BNK0,   32
        }

        CH03 (TS, Z164, 0x15, 0x020F, 0x00)
        Store (Arg0, I001) /* \IN19.I001 */
        Method (M001, 0, NotSerialized)
        {
            Method (M002, 0, NotSerialized)
            {
                Method (M003, 0, NotSerialized)
                {
                    Method (M004, 0, NotSerialized)
                    {
                        Method (M005, 0, NotSerialized)
                        {
                            Method (M006, 0, NotSerialized)
                            {
                                Method (M007, 0, NotSerialized)
                                {
                                    Method (M008, 0, NotSerialized)
                                    {
                                        If (I001)
                                        {
                                            Store (0x11223344, BNK0) /* \IN19.BNK0 */
                                        }

                                        Return (0x00)
                                    }

                                    Store (0x80000000, BNK0) /* \IN19.BNK0 */
                                    Return (Add (BNK0, M008 ()))
                                }

                                Store (0x07000000, BNK0) /* \IN19.BNK0 */
                                Return (Add (BNK0, M007 ()))
                            }

                            Store (0x00600000, BNK0) /* \IN19.BNK0 */
                            Return (Add (BNK0, M006 ()))
                        }

                        Store (0x00050000, BNK0) /* \IN19.BNK0 */
                        Return (Add (BNK0, M005 ()))
                    }

                    Store (0x4000, BNK0) /* \IN19.BNK0 */
                    Return (Add (BNK0, M004 ()))
                }

                Store (0x0300, BNK0) /* \IN19.BNK0 */
                Return (Add (BNK0, M003 ()))
            }

            Store (0x20, BNK0) /* \IN19.BNK0 */
            Return (Add (BNK0, M002 ()))
        }

        Store (0x01, BNK0) /* \IN19.BNK0 */
        Store (Add (BNK0, M001 ()), Local0)
        If (LNotEqual (Local0, 0x87654321))
        {
            ERR (TS, Z164, 0x0244, 0x00, 0x00, Local0, 0x87654321)
        }

        If (Arg0)
        {
            Store (0x11223344, Local1)
        }
        Else
        {
            Store (0x80000000, Local1)
        }

        If (LNotEqual (BNK0, Local1))
        {
            ERR (TS, Z164, 0x024E, 0x00, 0x00, BNK0, Local1)
        }

        CH03 (TS, Z164, 0x18, 0x0251, 0x00)
    }

    Method (IN1A, 1, Serialized)
    {
        Name (TS, "in1a")
        Name (I001, 0x00)
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32, 
            F001,   32
        }

        IndexField (F000, F001, ByteAcc, NoLock, Preserve)
        {
            IF00,   32
        }

        CH03 (TS, Z164, 0x19, 0x0261, 0x00)
        Store (Arg0, I001) /* \IN1A.I001 */
        Method (M001, 0, NotSerialized)
        {
            Method (M002, 0, NotSerialized)
            {
                Method (M003, 0, NotSerialized)
                {
                    Method (M004, 0, NotSerialized)
                    {
                        Method (M005, 0, NotSerialized)
                        {
                            Method (M006, 0, NotSerialized)
                            {
                                Method (M007, 0, NotSerialized)
                                {
                                    Method (M008, 0, NotSerialized)
                                    {
                                        If (I001)
                                        {
                                            Store (0x11223344, IF00) /* \IN1A.IF00 */
                                        }

                                        Return (0x00)
                                    }

                                    Store (0x80000000, IF00) /* \IN1A.IF00 */
                                    Return (Add (IF00, M008 ()))
                                }

                                Store (0x07000000, IF00) /* \IN1A.IF00 */
                                Return (Add (IF00, M007 ()))
                            }

                            Store (0x00600000, IF00) /* \IN1A.IF00 */
                            Return (Add (IF00, M006 ()))
                        }

                        Store (0x00050000, IF00) /* \IN1A.IF00 */
                        Return (Add (IF00, M005 ()))
                    }

                    Store (0x4000, IF00) /* \IN1A.IF00 */
                    Return (Add (IF00, M004 ()))
                }

                Store (0x0300, IF00) /* \IN1A.IF00 */
                Return (Add (IF00, M003 ()))
            }

            Store (0x20, IF00) /* \IN1A.IF00 */
            Return (Add (IF00, M002 ()))
        }

        Store (0x01, IF00) /* \IN1A.IF00 */
        Store (Add (IF00, M001 ()), Local0)
        If (LNotEqual (Local0, 0x87878787))
        {
            ERR (TS, Z164, 0x029B, 0x00, 0x00, Local0, 0x87878787)
        }

        If (Arg0)
        {
            Store (0x11223344, Local1)
        }
        Else
        {
            Store (0x80808080, Local1)
        }

        If (LNotEqual (IF00, Local1))
        {
            ERR (TS, Z164, 0x02A5, 0x00, 0x00, IF00, Local1)
        }

        CH03 (TS, Z164, 0x1C, 0x02A8, 0x00)
    }

    Method (IN1B, 1, Serialized)
    {
        Name (TS, "in1b")
        Name (I001, 0x00)
        Name (B000, Buffer (0x03)
        {
             0x11, 0x01, 0x22                                 // .."
        })
        CH03 (TS, Z164, 0x1D, 0x02B4, 0x00)
        Store (Arg0, I001) /* \IN1B.I001 */
        Method (M001, 0, NotSerialized)
        {
            Method (M002, 0, NotSerialized)
            {
                Method (M003, 0, NotSerialized)
                {
                    Method (M004, 0, NotSerialized)
                    {
                        Method (M005, 0, NotSerialized)
                        {
                            Method (M006, 0, NotSerialized)
                            {
                                Method (M007, 0, NotSerialized)
                                {
                                    Return (0x00)
                                }

                                Store (0x07, Index (B000, 0x01))
                                Return (Add (DerefOf (Index (B000, 0x01)), M007 ()))
                            }

                            Store (0x06, Index (B000, 0x01))
                            Return (Add (DerefOf (Index (B000, 0x01)), M006 ()))
                        }

                        Store (0x05, Index (B000, 0x01))
                        Return (Add (DerefOf (Index (B000, 0x01)), M005 ()))
                    }

                    Store (0x04, Index (B000, 0x01))
                    Return (Add (DerefOf (Index (B000, 0x01)), M004 ()))
                }

                Store (0x03, Index (B000, 0x01))
                Return (Add (DerefOf (Index (B000, 0x01)), M003 ()))
            }

            Store (0x02, Index (B000, 0x01))
            Return (Add (DerefOf (Index (B000, 0x01)), M002 ()))
        }

        Store (Add (DerefOf (Index (B000, 0x01)), M001 ()), Local0)
        If (LNotEqual (Local0, 0x1C))
        {
            ERR (TS, Z164, 0x02DD, 0x00, 0x00, Local0, 0x1C)
        }

        Store (DerefOf (Index (B000, 0x01)), Local0)
        If (Arg0)
        {
            Store (0xFF, Local1)
        }
        Else
        {
            Store (0x07, Local1)
        }

        If (LNotEqual (Local0, Local1))
        {
            ERR (TS, Z164, 0x02E9, 0x00, 0x00, Local0, Local1)
        }

        CH03 (TS, Z164, 0x20, 0x02EC, 0x00)
    }

    Method (IN1C, 1, Serialized)
    {
        Name (TS, "in1c")
        Name (I001, 0x00)
        Name (B000, Buffer (0x03)
        {
             0x11, 0x01, 0x22                                 // .."
        })
        CH03 (TS, Z164, 0x1D, 0x02FC, 0x00)
        Store (Arg0, I001) /* \IN1C.I001 */
        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Method (M002, 1, NotSerialized)
                {
                    Method (M003, 1, NotSerialized)
                    {
                        Method (M004, 1, NotSerialized)
                        {
                            Method (M005, 1, NotSerialized)
                            {
                                Method (M006, 1, NotSerialized)
                                {
                                    Method (M007, 1, NotSerialized)
                                    {
                                        Return (0x00)
                                    }

                                    Store (0x07, Index (B000, 0x01))
                                    Return (Add (DerefOf (Index (B000, 0x01)), M007 (B000)))
                                }

                                Store (0x06, Index (B000, 0x01))
                                Return (Add (DerefOf (Index (B000, 0x01)), M006 (B000)))
                            }

                            Store (0x05, Index (B000, 0x01))
                            Return (Add (DerefOf (Index (B000, 0x01)), M005 (B000)))
                        }

                        Store (0x04, Index (B000, 0x01))
                        Return (Add (DerefOf (Index (B000, 0x01)), M004 (B000)))
                    }

                    Store (0x03, Index (B000, 0x01))
                    Return (Add (DerefOf (Index (B000, 0x01)), M003 (B000)))
                }

                Store (0x02, Index (B000, 0x01))
                Return (Add (DerefOf (Index (B000, 0x01)), M002 (B000)))
            }

            Store (Add (DerefOf (Index (B000, 0x01)), M001 (B000)), Local0)
            Return (Local0)
        }

        CH03 (TS, Z164, 0x00, 0x0329, 0x00)
        Store (M000 (B000), Local0)
        If (LNotEqual (Local0, 0x1C))
        {
            ERR (TS, Z164, 0x032E, 0x00, 0x00, Local0, 0x1C)
        }

        Store (DerefOf (Index (B000, 0x01)), Local0)
        If (Arg0)
        {
            Store (0xFF, Local1)
        }
        Else
        {
            Store (0x07, Local1)
        }

        If (LNotEqual (Local0, Local1))
        {
            ERR (TS, Z164, 0x033A, 0x00, 0x00, Local0, Local1)
        }

        CH03 (TS, Z164, 0x20, 0x033D, 0x00)
    }

    Method (IN1D, 0, Serialized)
    {
        Name (TS, "in1d")
        Name (I001, 0x00)
        Name (P000, Package (0x04)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04
        })
        Name (PP00, Package (0x03)
        {
            0x11111111, 
            0x01, 
            0x22223333
        })
        CH03 (TS, Z164, 0x06, 0x034B, 0x00)
        Method (M001, 0, NotSerialized)
        {
            Method (M002, 0, NotSerialized)
            {
                Method (M003, 0, NotSerialized)
                {
                    Method (M004, 0, NotSerialized)
                    {
                        Method (M005, 0, NotSerialized)
                        {
                            Method (M006, 0, NotSerialized)
                            {
                                Method (M007, 0, NotSerialized)
                                {
                                    Return (0x00)
                                }

                                Store (0x07000000, Index (PP00, 0x01))
                                Return (Add (DerefOf (Index (PP00, 0x01)), M007 ()))
                            }

                            Store (0x00600000, Index (PP00, 0x01))
                            Return (Add (DerefOf (Index (PP00, 0x01)), M006 ()))
                        }

                        Store (0x00050000, Index (PP00, 0x01))
                        Return (Add (DerefOf (Index (PP00, 0x01)), M005 ()))
                    }

                    Store (0x4000, Index (PP00, 0x01))
                    Return (Add (DerefOf (Index (PP00, 0x01)), M004 ()))
                }

                Store (0x0300, Index (PP00, 0x01))
                Return (Add (DerefOf (Index (PP00, 0x01)), M003 ()))
            }

            Store (0x20, Index (PP00, 0x01))
            Return (Add (DerefOf (Index (PP00, 0x01)), M002 ()))
        }

        Store (Add (DerefOf (Index (PP00, 0x01)), M001 ()), Local0)
        If (LNotEqual (Local0, 0x07654321))
        {
            ERR (TS, Z164, 0x0372, 0x00, 0x00, Local0, 0x07654321)
        }

        Store (DerefOf (Index (PP00, 0x01)), Local0)
        If (LNotEqual (Local0, 0x07000000))
        {
            ERR (TS, Z164, 0x0378, 0x00, 0x00, Local0, 0x07000000)
        }

        CH03 (TS, Z164, 0x09, 0x037B, 0x00)
    }

    Method (IN1E, 0, Serialized)
    {
        Name (TS, "in1e")
        Name (I001, 0x00)
        Name (P000, Package (0x04)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04
        })
        Name (PP00, Package (0x03)
        {
            0x11111111, 
            0x01, 
            0x22223333
        })
        CH03 (TS, Z164, 0x06, 0x038C, 0x00)
        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Method (M002, 1, NotSerialized)
                {
                    Method (M003, 1, NotSerialized)
                    {
                        Method (M004, 1, NotSerialized)
                        {
                            Method (M005, 1, NotSerialized)
                            {
                                Method (M006, 1, NotSerialized)
                                {
                                    Method (M007, 1, NotSerialized)
                                    {
                                        Return (0x00)
                                    }

                                    Store (0x07000000, Index (PP00, 0x01))
                                    Return (Add (DerefOf (Index (PP00, 0x01)), M007 (PP00)))
                                }

                                Store (0x00600000, Index (PP00, 0x01))
                                Return (Add (DerefOf (Index (PP00, 0x01)), M006 (PP00)))
                            }

                            Store (0x00050000, Index (PP00, 0x01))
                            Return (Add (DerefOf (Index (PP00, 0x01)), M005 (PP00)))
                        }

                        Store (0x4000, Index (PP00, 0x01))
                        Return (Add (DerefOf (Index (PP00, 0x01)), M004 (PP00)))
                    }

                    Store (0x0300, Index (PP00, 0x01))
                    Return (Add (DerefOf (Index (PP00, 0x01)), M003 (PP00)))
                }

                Store (0x20, Index (PP00, 0x01))
                Return (Add (DerefOf (Index (PP00, 0x01)), M002 (PP00)))
            }

            Store (Add (DerefOf (Index (PP00, 0x01)), M001 (PP00)), Local0)
            Return (Local0)
        }

        CH03 (TS, Z164, 0x00, 0x03B7, 0x00)
        Store (M000 (PP00), Local0)
        If (LNotEqual (Local0, 0x07654321))
        {
            ERR (TS, Z164, 0x03BC, 0x00, 0x00, Local0, 0x07654321)
        }

        Store (DerefOf (Index (PP00, 0x01)), Local0)
        If (LNotEqual (Local0, 0x07000000))
        {
            ERR (TS, Z164, 0x03C2, 0x00, 0x00, Local0, 0x07000000)
        }

        CH03 (TS, Z164, 0x09, 0x03C5, 0x00)
    }

    Method (INI1, 0, NotSerialized)
    {
        SRMT ("in10")
        IN10 ()
        SRMT ("in11")
        IN11 ()
        SRMT ("in12")
        IN12 ()
        SRMT ("in13")
        IN13 ()
        SRMT ("in14")
        If (CHK0)
        {
            IN14 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("in15")
        If (CHK0)
        {
            IN15 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("in16")
        IN16 ()
        SRMT ("in17")
        IN17 ()
        SRMT ("in18-0")
        IN18 (0x00)
        SRMT ("in19-0")
        IN19 (0x00)
        SRMT ("in1a-0")
        IN1A (0x00)
        SRMT ("in1b-0")
        IN1B (0x00)
        SRMT ("in1c-0")
        If (Y275)
        {
            IN1C (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("in1d")
        IN1D ()
        SRMT ("in1e")
        If (LAnd (FIX0, Y275))
        {
            IN1E ()
        }
        Else
        {
            BLCK ()
        }

        CH03 ("ini1", Z164, 0x00, 0x03F9, 0x00)
    }

    Name (Z165, 0xA5)
    Method (IN20, 1, Serialized)
    {
        Name (TS, "in20")
        Name (I000, 0x01)
        Name (P000, Package (0x04)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04
        })
        Name (I001, 0x00)
        CH03 (TS, Z165, 0x00, 0x35, 0x00)
        Store (Arg0, I001) /* \IN20.I001 */
        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Method (M002, 1, NotSerialized)
                {
                    Method (M003, 1, NotSerialized)
                    {
                        If (I001)
                        {
                            CopyObject (P000, Arg0)
                        }

                        Return (0xABCD0000)
                    }

                    Return (Add (Arg0, M003 (Arg0)))
                }

                Return (Add (Arg0, M002 (Arg0)))
            }

            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (M000 (I000), Local0)
        If (LNotEqual (Local0, 0xABCD0003))
        {
            ERR (TS, Z165, 0x52, 0x00, 0x00, Local0, 0xABCD0003)
        }
    }

    Method (IN21, 1, Serialized)
    {
        Name (TS, "in21")
        Name (I000, 0x01)
        Name (I001, 0x00)
        Name (P000, Package (0x04)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04
        })
        Store (Arg0, I001) /* \IN21.I001 */
        Method (M001, 1, NotSerialized)
        {
            Method (M002, 1, NotSerialized)
            {
                Method (M003, 1, NotSerialized)
                {
                    Method (M004, 1, NotSerialized)
                    {
                        Method (M005, 1, NotSerialized)
                        {
                            Method (M006, 1, NotSerialized)
                            {
                                Method (M007, 1, NotSerialized)
                                {
                                    Method (M008, 1, NotSerialized)
                                    {
                                        If (I001)
                                        {
                                            CopyObject (P000, Arg0)
                                        }

                                        Return (0x00)
                                    }

                                    Store (0x80000000, Arg0)
                                    Return (Add (Arg0, M008 (Arg0)))
                                }

                                Store (0x07000000, Arg0)
                                Return (Add (Arg0, M007 (Arg0)))
                            }

                            Store (0x00600000, Arg0)
                            Return (Add (Arg0, M006 (Arg0)))
                        }

                        Store (0x00050000, Arg0)
                        Return (Add (Arg0, M005 (Arg0)))
                    }

                    Store (0x4000, Arg0)
                    Return (Add (Arg0, M004 (Arg0)))
                }

                Store (0x0300, Arg0)
                Return (Add (Arg0, M003 (Arg0)))
            }

            Store (0x20, Arg0)
            Return (Add (Arg0, M002 (Arg0)))
        }

        Store (Add (I000, M001 (I000)), Local0)
        If (LNotEqual (Local0, 0x87654321))
        {
            ERR (TS, Z165, 0x93, 0x00, 0x00, Local0, 0x87654321)
        }

        If (LNotEqual (I000, 0x01))
        {
            ERR (TS, Z165, 0x97, 0x00, 0x00, I000, 0x01)
        }
    }

    Method (IN22, 0, Serialized)
    {
        Name (TS, "in22")
        Name (I000, 0x00100000)
        Name (I001, 0x00)
        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                If (LLess (I001, 0x09))
                {
                    Increment (Arg0)
                    Increment (I001)
                    Add (Arg0, M001 (Arg0), Local0)
                    Return (Local0)
                }

                Return (0x00)
            }

            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (Add (I000, M000 (I000)), Local0)
        If (LNotEqual (Local0, 0x00B0002D))
        {
            ERR (TS, Z165, 0xBC, 0x00, 0x00, Local0, 0x00B0002D)
        }

        If (LNotEqual (I000, 0x00100000))
        {
            ERR (TS, Z165, 0xC0, 0x00, 0x00, I000, 0x00100000)
        }
    }

    Method (IN23, 2, Serialized)
    {
        Name (TS, "in23")
        Name (I001, 0x00)
        Name (P000, Package (0x04)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04
        })
        Store (Arg0, I001) /* \IN23.I001 */
        Store (0x01, Arg1)
        Method (M001, 1, NotSerialized)
        {
            Method (M002, 1, NotSerialized)
            {
                Method (M003, 1, NotSerialized)
                {
                    Method (M004, 1, NotSerialized)
                    {
                        Method (M005, 1, NotSerialized)
                        {
                            Method (M006, 1, NotSerialized)
                            {
                                Method (M007, 1, NotSerialized)
                                {
                                    Method (M008, 1, NotSerialized)
                                    {
                                        If (I001)
                                        {
                                            CopyObject (P000, Arg0)
                                        }

                                        Return (0x00)
                                    }

                                    Store (0x80000000, Arg0)
                                    Return (Add (Arg0, M008 (0x08)))
                                }

                                Store (0x07000000, Arg0)
                                Return (Add (Arg0, M007 (0x07)))
                            }

                            Store (0x00600000, Arg0)
                            Return (Add (Arg0, M006 (0x06)))
                        }

                        Store (0x00050000, Arg0)
                        Return (Add (Arg0, M005 (0x05)))
                    }

                    Store (0x4000, Arg0)
                    Return (Add (Arg0, M004 (0x04)))
                }

                Store (0x0300, Arg0)
                Return (Add (Arg0, M003 (0x03)))
            }

            Store (0x20, Arg0)
            Return (Add (Arg0, M002 (0x02)))
        }

        Store (Add (Arg1, M001 (0x01)), Local0)
        If (LNotEqual (Local0, 0x87654321))
        {
            ERR (TS, Z165, 0xFF, 0x00, 0x00, Local0, 0x87654321)
        }

        If (LNotEqual (Arg1, 0x01))
        {
            ERR (TS, Z165, 0x0103, 0x00, 0x00, Arg1, 0x01)
        }

        CH03 (TS, Z165, 0x11, 0x0106, 0x00)
    }

    Method (INI2, 0, NotSerialized)
    {
        SRMT ("in20-0")
        IN20 (0x00)
        SRMT ("in21-0")
        IN21 (0x00)
        SRMT ("in22")
        IN22 ()
        SRMT ("in23-0")
        IN23 (0x00, 0x00)
        CH03 ("ini2", Z165, 0x00, 0x0114, 0x00)
    }

    Name (Z166, 0xA6)
    Method (IN30, 0, Serialized)
    {
        Name (TS, "in30")
        Name (P000, Package (0x03)
        {
            0xABCD0000, 
            0xABCD0001, 
            0xABCD0002
        })
        Method (M000, 2, NotSerialized)
        {
            Method (M001, 2, NotSerialized)
            {
                Store (DerefOf (Index (Arg0, 0x00)), Local0)
                If (LNotEqual (Local0, 0xABCD0000))
                {
                    ERR (TS, Z166, 0x41, 0x00, 0x00, Local0, 0xABCD0000)
                }

                Store (0x11112222, Index (Arg0, 0x00))
                Store (DerefOf (Index (Arg0, 0x00)), Local0)
                If (LNotEqual (Local0, 0x11112222))
                {
                    ERR (TS, Z166, 0x48, 0x00, 0x00, Local0, 0x11112222)
                }
            }

            M001 (Arg0, Arg1)
        }

        M000 (P000, RefOf (P000))
        Store (DerefOf (Index (P000, 0x00)), Local0)
        If (LNotEqual (Local0, 0x11112222))
        {
            ERR (TS, Z166, 0x52, 0x00, 0x00, Local0, 0x11112222)
        }

        Store (DerefOf (Index (P000, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z166, 0x57, 0x00, 0x00, Local0, 0xABCD0001)
        }
    }

    Method (IN31, 0, Serialized)
    {
        Name (TS, "in31")
        Name (P000, Package (0x03)
        {
            0xABCD0000, 
            0xABCD0001, 
            0xABCD0002
        })
        Method (M000, 2, NotSerialized)
        {
            Method (M001, 2, NotSerialized)
            {
                Store (DerefOf (Arg1), Local7)
                Store (DerefOf (Index (Local7, 0x01)), Local0)
                If (LNotEqual (Local0, 0xABCD0001))
                {
                    ERR (TS, Z166, 0x6C, 0x00, 0x00, Local0, 0xABCD0001)
                }

                Store (0x33334444, Index (Local7, 0x01))
                Store (DerefOf (Index (Local7, 0x01)), Local0)
                If (LNotEqual (Local0, 0x33334444))
                {
                    ERR (TS, Z166, 0x73, 0x00, 0x00, Local0, 0x33334444)
                }
            }

            M001 (Arg0, Arg1)
        }

        M000 (P000, RefOf (P000))
        Store (DerefOf (Index (P000, 0x00)), Local0)
        If (LNotEqual (Local0, 0xABCD0000))
        {
            ERR (TS, Z166, 0x7D, 0x00, 0x00, Local0, 0xABCD0000)
        }

        Store (DerefOf (Index (P000, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z166, 0x82, 0x00, 0x00, Local0, 0xABCD0001)
        }
    }

    Method (IN32, 0, Serialized)
    {
        Name (TS, "in32")
        Name (P000, Package (0x03)
        {
            0xABCD0000, 
            0xABCD0001, 
            0xABCD0002
        })
        Method (M000, 2, NotSerialized)
        {
            Method (M001, 2, NotSerialized)
            {
                Store (0x11112222, Index (Arg0, 0x00))
                Store (DerefOf (Index (Arg0, 0x00)), Local0)
                If (LNotEqual (Local0, 0x11112222))
                {
                    ERR (TS, Z166, 0x98, 0x00, 0x00, Local0, 0x11112222)
                }

                Store (DerefOf (Arg1), Local7)
                Store (0x33334444, Index (Local7, 0x01))
                Store (DerefOf (Index (Local7, 0x01)), Local0)
                If (LNotEqual (Local0, 0x33334444))
                {
                    ERR (TS, Z166, 0xA0, 0x00, 0x00, Local0, 0x33334444)
                }
            }

            M001 (Arg0, Arg1)
        }

        M000 (P000, RefOf (P000))
        Store (DerefOf (Index (P000, 0x00)), Local0)
        If (LNotEqual (Local0, 0x11112222))
        {
            ERR (TS, Z166, 0xAA, 0x00, 0x00, Local0, 0x11112222)
        }

        Store (DerefOf (Index (P000, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z166, 0xAF, 0x00, 0x00, Local0, 0xABCD0001)
        }
    }

    Method (IN33, 0, Serialized)
    {
        Name (TS, "in33")
        Name (P000, Package (0x03)
        {
            0xABCD0000, 
            0xABCD0001, 
            0xABCD0002
        })
        Method (M000, 2, NotSerialized)
        {
            Method (M001, 2, NotSerialized)
            {
                Store (RefOf (Arg0), Local6)
                Store (DerefOf (Local6), Local7)
                Store (DerefOf (Index (Local7, 0x01)), Local0)
                If (LNotEqual (Local0, 0xABCD0001))
                {
                    ERR (TS, Z166, 0xC6, 0x00, 0x00, Local0, 0xABCD0001)
                }

                Store (0x33334444, Index (Local7, 0x01))
                Store (DerefOf (Index (Local7, 0x01)), Local0)
                If (LNotEqual (Local0, 0x33334444))
                {
                    ERR (TS, Z166, 0xCD, 0x00, 0x00, Local0, 0x33334444)
                }
            }

            M001 (Arg0, Arg1)
        }

        M000 (P000, RefOf (P000))
        Store (DerefOf (Index (P000, 0x00)), Local0)
        If (LNotEqual (Local0, 0xABCD0000))
        {
            ERR (TS, Z166, 0xD7, 0x00, 0x00, Local0, 0xABCD0000)
        }

        Store (DerefOf (Index (P000, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z166, 0xDB, 0x00, 0x00, Local0, 0xABCD0001)
        }

        Store (DerefOf (Index (P000, 0x02)), Local0)
        If (LNotEqual (Local0, 0xABCD0002))
        {
            ERR (TS, Z166, 0xDF, 0x00, 0x00, Local0, 0xABCD0002)
        }
    }

    Method (IN34, 0, Serialized)
    {
        Name (TS, "in34")
        Name (I000, 0xABCD0000)
        Name (I001, 0xABCD0001)
        Name (I002, 0xABCD0002)
        Name (II00, 0x11112222)
        Name (P000, Package (0x04)
        {
            I000, , 
            I001, , 
            I002, , 
            "i000"
        })
        Method (M000, 2, NotSerialized)
        {
            Method (M001, 2, NotSerialized)
            {
                Store (DerefOf (Index (Arg0, 0x00)), Local0)
                If (LNotEqual (Local0, 0xABCD0000))
                {
                    ERR (TS, Z166, 0x0101, 0x00, 0x00, Local0, 0xABCD0000)
                }

                Store (DerefOf (Index (Arg0, 0x01)), Local0)
                If (LNotEqual (Local0, 0xABCD0001))
                {
                    ERR (TS, Z166, 0x0105, 0x00, 0x00, Local0, 0xABCD0001)
                }

                Store (DerefOf (Index (Arg0, 0x02)), Local0)
                If (LNotEqual (Local0, 0xABCD0002))
                {
                    ERR (TS, Z166, 0x0109, 0x00, 0x00, Local0, 0xABCD0002)
                }

                Store (DerefOf (Index (Arg0, 0x03)), Local0)
                If (LNotEqual (Local0, "i000"))
                {
                    ERR (TS, Z166, 0x010D, 0x00, 0x00, Local0, "i000")
                }

                Store (II00, Index (Arg0, 0x00))
                Store (DerefOf (Index (Arg0, 0x00)), Local0)
                If (LNotEqual (Local0, 0x11112222))
                {
                    ERR (TS, Z166, 0x0114, 0x00, 0x00, Local0, 0x11112222)
                }
            }

            M001 (Arg0, Arg1)
        }

        M000 (P000, RefOf (P000))
        Store (DerefOf (Index (P000, 0x00)), Local0)
        If (LNotEqual (Local0, 0x11112222))
        {
            ERR (TS, Z166, 0x011E, 0x00, 0x00, Local0, 0x11112222)
        }

        Store (DerefOf (Index (P000, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z166, 0x0123, 0x00, 0x00, Local0, 0xABCD0001)
        }

        Store (DerefOf (Index (P000, 0x02)), Local0)
        If (LNotEqual (Local0, 0xABCD0002))
        {
            ERR (TS, Z166, 0x0128, 0x00, 0x00, Local0, 0xABCD0002)
        }

        Store (DerefOf (Index (P000, 0x03)), Local0)
        If (LNotEqual (Local0, "i000"))
        {
            ERR (TS, Z166, 0x012D, 0x00, 0x00, Local0, "i000")
        }
    }

    Method (IN36, 0, Serialized)
    {
        Name (TS, "in36")
        Name (B000, Buffer (0x03)
        {
             0x10, 0x11, 0x12                                 // ...
        })
        Method (M000, 2, NotSerialized)
        {
            Method (M001, 2, NotSerialized)
            {
                Store (DerefOf (Index (Arg0, 0x00)), Local0)
                If (LNotEqual (Local0, 0x10))
                {
                    ERR (TS, Z166, 0x0141, 0x00, 0x00, Local0, 0x10)
                }

                Store (0x67, Index (Arg0, 0x00))
                Store (DerefOf (Index (Arg0, 0x00)), Local0)
                If (LNotEqual (Local0, 0x67))
                {
                    ERR (TS, Z166, 0x0148, 0x00, 0x00, Local0, 0x67)
                }

                Store (DerefOf (Arg1), Local7)
                Store (0x55, Index (Local7, 0x01))
                Store (DerefOf (Index (Local7, 0x01)), Local0)
                If (LNotEqual (Local0, 0x55))
                {
                    ERR (TS, Z166, 0x0152, 0x00, 0x00, Local0, 0x55)
                }
            }

            M001 (Arg0, Arg1)
        }

        M000 (B000, RefOf (B000))
        Store (DerefOf (Index (B000, 0x00)), Local0)
        If (LNotEqual (Local0, 0x67))
        {
            ERR (TS, Z166, 0x015C, 0x00, 0x00, Local0, 0x67)
        }

        Store (DerefOf (Index (B000, 0x01)), Local0)
        If (LNotEqual (Local0, 0x11))
        {
            ERR (TS, Z166, 0x0161, 0x00, 0x00, Local0, 0x11)
        }

        Store (DerefOf (Index (B000, 0x02)), Local0)
        If (LNotEqual (Local0, 0x12))
        {
            ERR (TS, Z166, 0x0166, 0x00, 0x00, Local0, 0x12)
        }
    }

    Method (IN37, 0, Serialized)
    {
        Name (TS, "in37")
        Name (I001, 0x00)
        Name (PP00, Package (0x03)
        {
            0x11111111, 
            0x00100000, 
            0x22223333
        })
        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                If (LLess (I001, 0x09))
                {
                    Store (DerefOf (Index (Arg0, 0x01)), Local0)
                    Increment (Local0)
                    Store (Local0, Index (Arg0, 0x01))
                    Increment (I001)
                    Add (DerefOf (Index (Arg0, 0x01)), M001 (Arg0), Local0)
                    Return (Local0)
                }

                Return (0x00)
            }

            Store (Add (DerefOf (Index (Arg0, 0x01)), M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (M000 (PP00), Local0)
        If (LNotEqual (Local0, 0x00A0002D))
        {
            ERR (TS, Z166, 0x018F, 0x00, 0x00, Local0, 0x00A0002D)
        }

        Store (DerefOf (Index (PP00, 0x01)), Local0)
        If (LNotEqual (Local0, 0x00100009))
        {
            ERR (TS, Z166, 0x0195, 0x00, 0x00, Local0, 0x00100009)
        }

        CH03 (TS, Z166, 0x0C, 0x0198, 0x00)
    }

    Method (IN38, 1, Serialized)
    {
        Name (TS, "in38")
        Name (I001, 0x00)
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32, 
            F001,   32
        }

        CH03 (TS, Z166, 0x11, 0x01AE, 0x00)
        Store (Arg0, I001) /* \IN38.I001 */
        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Method (M002, 1, NotSerialized)
                {
                    Method (M003, 1, NotSerialized)
                    {
                        Method (M004, 1, NotSerialized)
                        {
                            Method (M005, 1, NotSerialized)
                            {
                                Method (M006, 1, NotSerialized)
                                {
                                    Method (M007, 1, NotSerialized)
                                    {
                                        Return (0x00)
                                    }

                                    Store (0x07000000, Arg0)
                                    Return (Add (Arg0, M007 (Arg0)))
                                }

                                Store (0x00600000, Arg0)
                                Return (Add (Arg0, M006 (Arg0)))
                            }

                            Store (0x00050000, Arg0)
                            Return (Add (Arg0, M005 (Arg0)))
                        }

                        Store (0x4000, Arg0)
                        Return (Add (Arg0, M004 (Arg0)))
                    }

                    Store (0x0300, Arg0)
                    Return (Add (Arg0, M003 (Arg0)))
                }

                Store (0x20, Arg0)
                Return (Add (Arg0, M002 (Arg0)))
            }

            Store (0x01, Arg0)
            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (0xABCD9876, F001) /* \IN38.F001 */
        Store (M000 (F001), Local0)
        If (LNotEqual (Local0, 0x07654321))
        {
            ERR (TS, Z166, 0x01F1, 0x00, 0x00, Local0, 0x07654321)
        }

        If (Arg0)
        {
            Store (0x11223344, Local1)
        }
        Else
        {
            Store (0xABCD9876, Local1)
        }

        If (LNotEqual (F001, Local1))
        {
            ERR (TS, Z166, 0x01FB, 0x00, 0x00, F001, Local1)
        }

        CH03 (TS, Z166, 0x14, 0x01FE, 0x00)
    }

    Method (IN39, 1, Serialized)
    {
        Name (TS, "in39")
        Name (I001, 0x00)
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32, 
            F001,   32
        }

        BankField (R000, F001, 0x00
, ByteAcc, NoLock, Preserve)
        {
            BNK0,   32
        }

        CH03 (TS, Z166, 0x15, 0x020E, 0x00)
        Store (Arg0, I001) /* \IN39.I001 */
        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Method (M002, 1, NotSerialized)
                {
                    Method (M003, 1, NotSerialized)
                    {
                        Method (M004, 1, NotSerialized)
                        {
                            Method (M005, 1, NotSerialized)
                            {
                                Method (M006, 1, NotSerialized)
                                {
                                    Method (M007, 1, NotSerialized)
                                    {
                                        Return (0x00)
                                    }

                                    Store (0x07000000, Arg0)
                                    Return (Add (Arg0, M007 (Arg0)))
                                }

                                Store (0x00600000, Arg0)
                                Return (Add (Arg0, M006 (Arg0)))
                            }

                            Store (0x00050000, Arg0)
                            Return (Add (Arg0, M005 (Arg0)))
                        }

                        Store (0x4000, Arg0)
                        Return (Add (Arg0, M004 (Arg0)))
                    }

                    Store (0x0300, Arg0)
                    Return (Add (Arg0, M003 (Arg0)))
                }

                Store (0x20, Arg0)
                Return (Add (Arg0, M002 (Arg0)))
            }

            Store (0x01, Arg0)
            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (0xAABBCCDD, BNK0) /* \IN39.BNK0 */
        Store (M000 (BNK0), Local0)
        If (LNotEqual (Local0, 0x07654321))
        {
            ERR (TS, Z166, 0x0250, 0x00, 0x00, Local0, 0x07654321)
        }

        If (Arg0)
        {
            Store (0x11223344, Local1)
        }
        Else
        {
            Store (0xAABBCCDD, Local1)
        }

        If (LNotEqual (BNK0, Local1))
        {
            ERR (TS, Z166, 0x025A, 0x00, 0x00, BNK0, Local1)
        }

        CH03 (TS, Z166, 0x18, 0x025D, 0x00)
    }

    Method (IN3A, 1, Serialized)
    {
        Name (TS, "in3a")
        Name (I001, 0x00)
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32, 
            F001,   32
        }

        IndexField (F000, F001, ByteAcc, NoLock, Preserve)
        {
            IF00,   32
        }

        CH03 (TS, Z166, 0x19, 0x026D, 0x00)
        Store (Arg0, I001) /* \IN3A.I001 */
        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Method (M002, 1, NotSerialized)
                {
                    Method (M003, 1, NotSerialized)
                    {
                        Method (M004, 1, NotSerialized)
                        {
                            Method (M005, 1, NotSerialized)
                            {
                                Method (M006, 1, NotSerialized)
                                {
                                    Method (M007, 1, NotSerialized)
                                    {
                                        Return (0x00)
                                    }

                                    Store (0x07000000, IF00) /* \IN3A.IF00 */
                                    Return (Add (IF00, M007 (IF00)))
                                }

                                Store (0x00600000, IF00) /* \IN3A.IF00 */
                                Return (Add (IF00, M006 (IF00)))
                            }

                            Store (0x00050000, IF00) /* \IN3A.IF00 */
                            Return (Add (IF00, M005 (IF00)))
                        }

                        Store (0x4000, IF00) /* \IN3A.IF00 */
                        Return (Add (IF00, M004 (IF00)))
                    }

                    Store (0x0300, IF00) /* \IN3A.IF00 */
                    Return (Add (IF00, M003 (IF00)))
                }

                Store (0x20, IF00) /* \IN3A.IF00 */
                Return (Add (IF00, M002 (IF00)))
            }

            Store (0x01, IF00) /* \IN3A.IF00 */
            Store (Add (IF00, M001 (IF00)), Local0)
            Return (Local0)
        }

        Store (0xABABABAB, IF00) /* \IN3A.IF00 */
        Store (M000 (IF00), Local0)
        If (LNotEqual (Local0, 0x07070707))
        {
            ERR (TS, Z166, 0x02B4, 0x00, 0x00, Local0, 0x07070707)
        }

        If (Arg0)
        {
            Store (0x11223344, Local1)
        }
        Else
        {
            Store (0x07070707, Local1)
        }

        If (LNotEqual (IF00, Local1))
        {
            ERR (TS, Z166, 0x02BE, 0x00, 0x00, IF00, Local1)
        }

        CH03 (TS, Z166, 0x1C, 0x02C1, 0x00)
    }

    Method (IN3C, 1, Serialized)
    {
        Name (TS, "in3c")
        Name (I001, 0x00)
        Name (B000, Buffer (0x03)
        {
             0x11, 0x01, 0x22                                 // .."
        })
        CH03 (TS, Z166, 0x1D, 0x02DB, 0x00)
        Store (Arg0, I001) /* \IN3C.I001 */
        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Method (M002, 1, NotSerialized)
                {
                    Method (M003, 1, NotSerialized)
                    {
                        Method (M004, 1, NotSerialized)
                        {
                            Method (M005, 1, NotSerialized)
                            {
                                Method (M006, 1, NotSerialized)
                                {
                                    Method (M007, 1, NotSerialized)
                                    {
                                        Return (0x00)
                                    }

                                    Store (0x07, Index (Arg0, 0x01))
                                    Return (Add (DerefOf (Index (Arg0, 0x01)), M007 (Arg0)))
                                }

                                Store (0x06, Index (Arg0, 0x01))
                                Return (Add (DerefOf (Index (Arg0, 0x01)), M006 (Arg0)))
                            }

                            Store (0x05, Index (Arg0, 0x01))
                            Return (Add (DerefOf (Index (Arg0, 0x01)), M005 (Arg0)))
                        }

                        Store (0x04, Index (Arg0, 0x01))
                        Return (Add (DerefOf (Index (Arg0, 0x01)), M004 (Arg0)))
                    }

                    Store (0x03, Index (Arg0, 0x01))
                    Return (Add (DerefOf (Index (Arg0, 0x01)), M003 (Arg0)))
                }

                Store (0x02, Index (Arg0, 0x01))
                Return (Add (DerefOf (Index (Arg0, 0x01)), M002 (Arg0)))
            }

            Store (Add (DerefOf (Index (Arg0, 0x01)), M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (M000 (B000), Local0)
        If (LNotEqual (Local0, 0x1C))
        {
            ERR (TS, Z166, 0x030B, 0x00, 0x00, Local0, 0x1C)
        }

        Store (DerefOf (Index (B000, 0x01)), Local0)
        If (Arg0)
        {
            Store (0xFF, Local1)
        }
        Else
        {
            Store (0x07, Local1)
        }

        If (LNotEqual (Local0, Local1))
        {
            ERR (TS, Z166, 0x0317, 0x00, 0x00, Local0, Local1)
        }

        CH03 (TS, Z166, 0x20, 0x031A, 0x00)
    }

    Method (IN3E, 0, Serialized)
    {
        Name (TS, "in3e")
        Name (I001, 0x00)
        Name (P000, Package (0x04)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04
        })
        Name (PP00, Package (0x03)
        {
            0x11111111, 
            0x01, 
            0x22223333
        })
        CH03 (TS, Z166, 0x06, 0x0335, 0x00)
        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Method (M002, 1, NotSerialized)
                {
                    Method (M003, 1, NotSerialized)
                    {
                        Method (M004, 1, NotSerialized)
                        {
                            Method (M005, 1, NotSerialized)
                            {
                                Method (M006, 1, NotSerialized)
                                {
                                    Method (M007, 1, NotSerialized)
                                    {
                                        Return (0x00)
                                    }

                                    Store (0x07000000, Index (Arg0, 0x01))
                                    Return (Add (DerefOf (Index (Arg0, 0x01)), M007 (Arg0)))
                                }

                                Store (0x00600000, Index (Arg0, 0x01))
                                Return (Add (DerefOf (Index (Arg0, 0x01)), M006 (Arg0)))
                            }

                            Store (0x00050000, Index (Arg0, 0x01))
                            Return (Add (DerefOf (Index (Arg0, 0x01)), M005 (Arg0)))
                        }

                        Store (0x4000, Index (Arg0, 0x01))
                        Return (Add (DerefOf (Index (Arg0, 0x01)), M004 (Arg0)))
                    }

                    Store (0x0300, Index (Arg0, 0x01))
                    Return (Add (DerefOf (Index (Arg0, 0x01)), M003 (Arg0)))
                }

                Store (0x20, Index (Arg0, 0x01))
                Return (Add (DerefOf (Index (Arg0, 0x01)), M002 (Arg0)))
            }

            Store (Add (DerefOf (Index (Arg0, 0x01)), M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (M000 (PP00), Local0)
        If (LNotEqual (Local0, 0x07654321))
        {
            ERR (TS, Z166, 0x0363, 0x00, 0x00, Local0, 0x07654321)
        }

        Store (DerefOf (Index (PP00, 0x01)), Local0)
        If (LNotEqual (Local0, 0x07000000))
        {
            ERR (TS, Z166, 0x0369, 0x00, 0x00, Local0, 0x07000000)
        }

        CH03 (TS, Z166, 0x09, 0x036C, 0x00)
    }

    Method (INI3, 0, NotSerialized)
    {
        SRMT ("in30")
        IN30 ()
        SRMT ("in31")
        IN31 ()
        SRMT ("in32")
        IN32 ()
        SRMT ("in33")
        IN33 ()
        SRMT ("in34")
        If (CHK0)
        {
            IN34 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("in36")
        IN36 ()
        SRMT ("in37")
        IN37 ()
        SRMT ("in38-0")
        IN38 (0x00)
        SRMT ("in39-0")
        IN39 (0x00)
        SRMT ("in3a-0")
        IN3A (0x00)
        SRMT ("in3c-0")
        IN3C (0x00)
        SRMT ("in3e")
        IN3E ()
        CH03 ("ini3", Z166, 0x00, 0x038E, 0x00)
    }

    Name (Z167, 0xA7)
    Name (CMD0, 0x00)
    Name (STP0, 0x00)
    Name (OT00, 0x00)
    Name (AD00, 0x01)
    Name (LN00, 0x02)
    Name (LN01, 0x03)
    Name (LN02, 0x04)
    Name (LN03, 0x05)
    Name (LN04, 0x06)
    Name (LN05, 0x07)
    Name (LN06, 0x08)
    Name (LN07, 0x09)
    Name (LN08, 0x0A)
    Method (OBT0, 2, NotSerialized)
    {
        Store (ObjectType (Arg0), Local0)
        If (LNotEqual (Local0, Arg1))
        {
            ERR ("obt0", Z167, 0x44, 0x00, 0x00, Local0, Arg1)
        }

        Return (0x05)
    }

    Method (ACT0, 4, Serialized)
    {
        Name (TS, "act0")
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                Store (ObjectType (Arg1), Local0)
                If (LNotEqual (Local0, Arg2))
                {
                    ERR (TS, Z167, 0x58, 0x00, 0x00, Local0, Arg2)
                }
            }
            Case (0x01)
            {
                Add (Arg1, Arg2, Local0)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z167, 0x5E, 0x00, 0x00, Local0, Arg3)
                }
            }
            Case (0x02)
            {
                If (LNotEqual (Arg1, 0xABCD0000))
                {
                    ERR (TS, Z167, 0x63, 0x00, 0x00, Arg1, 0xABCD0000)
                }
            }
            Case (0x03)
            {
                If (LNotEqual (Arg1, "qwrtyu0003"))
                {
                    ERR (TS, Z167, 0x69, 0x00, 0x00, Arg1, "qwrtyu0003")
                }
            }
            Case (0x04)
            {
                If (LNotEqual (Arg1, "abcd0800"))
                {
                    ERR (TS, Z167, 0x70, 0x00, 0x00, Arg1, "abcd0800")
                }
            }
            Case (0x05)
            {
                If (LNotEqual (Arg1, Buffer (0x05)
                            {
                                 0xB0, 0xB1, 0xB2, 0xB3, 0xB4                     // .....
                            }))
                {
                    ERR (TS, Z167, 0x77, 0x00, 0x00, Arg1, Buffer (0x05)
                        {
                             0xB0, 0xB1, 0xB2, 0xB3, 0xB4                     // .....
                        })
                }
            }
            Case (0x06)
            {
                Store (DerefOf (Index (Arg1, 0x01)), Local0)
                If (LNotEqual (Local0, 0xABCD0902))
                {
                    ERR (TS, Z167, 0x7E, 0x00, 0x00, Local0, 0xABCD0902)
                }
            }
            Case (0x07)
            {
                If (LNotEqual (Arg1, 0xABCD0A00))
                {
                    ERR (TS, Z167, 0x83, 0x00, 0x00, Arg1, 0xABCD0A00)
                }
            }
            Case (0x08)
            {
                If (LNotEqual (Arg1, 0xABABABAB))
                {
                    ERR (TS, Z167, 0x88, 0x00, 0x00, Arg1, 0xABABABAB)
                }
            }
            Case (0x09)
            {
                If (LNotEqual (Arg1, 0x00))
                {
                    ERR (TS, Z167, 0x8D, 0x00, 0x00, Arg1, 0x00)
                }
            }
            Case (0x0A)
            {
                If (LNotEqual (Arg1, Buffer (0x04)
                            {
                                 0x08, 0x0D, 0xCD, 0xAB                           // ....
                            }))
                {
                    ERR (TS, Z167, 0x92, 0x00, 0x00, Arg1, Buffer (0x04)
                        {
                             0x08, 0x0D, 0xCD, 0xAB                           // ....
                        })
                }
            }

        }
    }

    Method (MI01, 1, Serialized)
    {
        If (LNot (CHK0))
        {
            If (LEqual (CMD0, 0x01))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C009))
                {
                    ERR ("mI01", Z167, 0xAD, 0x00, 0x00, Local0, C009)
                }

                Add (Arg0, 0x01, Local0)
                If (LNotEqual (Local0, 0xABCD0001))
                {
                    ERR ("mI01", Z167, 0xB1, 0x00, 0x00, Local0, 0xABCD0001)
                }

                If (LNotEqual (Arg0, 0xABCD0000))
                {
                    ERR ("mI01", Z167, 0xB4, 0x00, 0x00, Arg0, 0xABCD0000)
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x02))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C00A))
                {
                    ERR ("mI01", Z167, 0xBD, 0x00, 0x00, Local0, C00A)
                }

                If (LNot (RUN4))
                {
                    If (LNotEqual (Arg0, "qwrtyu0003"))
                    {
                        ERR ("mI01", Z167, 0xC2, 0x00, 0x00, Arg0, "qwrtyu0003")
                    }
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x03))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C00A))
                {
                    ERR ("mI01", Z167, 0xCB, 0x00, 0x00, Local0, C00A)
                }

                If (LNot (RUN4))
                {
                    Add (Arg0, 0x05, Local0)
                    If (LNotEqual (Local0, 0xABCD0805))
                    {
                        ERR ("mI01", Z167, 0xD1, 0x00, 0x00, Local0, 0xABCD0805)
                    }

                    If (LNotEqual (Arg0, "abcd0800"))
                    {
                        ERR ("mI01", Z167, 0xD4, 0x00, 0x00, Arg0, "abcd0800")
                    }
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x04))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C00B))
                {
                    ERR ("mI01", Z167, 0xDE, 0x00, 0x00, Local0, C00B)
                }

                If (LNot (RUN4))
                {
                    Add (Arg0, 0x07, Local0)
                    If (LNotEqual (Local0, 0x000000B4B3B2B1B7))
                    {
                        ERR ("mI01", Z167, 0xE4, 0x00, 0x00, Local0, 0x000000B4B3B2B1B7)
                    }

                    If (LNotEqual (Arg0, Buffer (0x05)
                                {
                                     0xB0, 0xB1, 0xB2, 0xB3, 0xB4                     // .....
                                }))
                    {
                        ERR ("mI01", Z167, 0xE7, 0x00, 0x00, Arg0, Buffer (0x05)
                            {
                                 0xB0, 0xB1, 0xB2, 0xB3, 0xB4                     // .....
                            })
                    }
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x05))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C00C))
                {
                    ERR ("mI01", Z167, 0xF1, 0x00, 0x00, Local0, C00C)
                }

                Store (DerefOf (Index (Arg0, 0x01)), Local0)
                If (LNotEqual (Local0, 0xABCD0902))
                {
                    ERR ("mI01", Z167, 0xF5, 0x00, 0x00, Local0, 0xABCD0902)
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x06))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C009))
                {
                    ERR ("mI01", Z167, 0xFD, 0x00, 0x00, Local0, C009)
                }

                Add (Arg0, 0x09, Local0)
                If (LNotEqual (Local0, 0xABCD0A09))
                {
                    ERR ("mI01", Z167, 0x0101, 0x00, 0x00, Local0, 0xABCD0A09)
                }

                If (LNotEqual (Arg0, 0xABCD0A00))
                {
                    ERR ("mI01", Z167, 0x0104, 0x00, 0x00, Arg0, 0xABCD0A00)
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x07))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C00E))
                {
                    ERR ("mI01", Z167, 0x010D, 0x00, 0x00, Local0, C00E)
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x08))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C00F))
                {
                    ERR ("mI01", Z167, 0x0115, 0x00, 0x00, Local0, C00F)
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x09))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C011))
                {
                    ERR ("mI01", Z167, 0x011D, 0x00, 0x00, Local0, C011)
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x0A))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C012))
                {
                    ERR ("mI01", Z167, 0x0125, 0x00, 0x00, Local0, C012)
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x0B))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C013))
                {
                    ERR ("mI01", Z167, 0x012D, 0x00, 0x00, Local0, C013)
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x0C))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C014))
                {
                    ERR ("mI01", Z167, 0x0135, 0x00, 0x00, Local0, C014)
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x0D))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C015))
                {
                    ERR ("mI01", Z167, 0x013D, 0x00, 0x00, Local0, C015)
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x0E))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C009))
                {
                    ERR ("mI01", Z167, 0x0145, 0x00, 0x00, Local0, C009)
                }

                Add (Arg0, 0x09, Local0)
                If (LNotEqual (Local0, 0xABABABB4))
                {
                    ERR ("mI01", Z167, 0x0149, 0x00, 0x00, Local0, 0xABABABB4)
                }

                If (LNotEqual (Arg0, 0xABABABAB))
                {
                    ERR ("mI01", Z167, 0x014C, 0x00, 0x00, Arg0, 0xABABABAB)
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x0F))
            {
                Store (ObjectType (Arg0), Local0)
                If (LNotEqual (Local0, C009))
                {
                    ERR ("mI01", Z167, 0x0154, 0x00, 0x00, Local0, C009)
                }

                Add (Arg0, 0x09, Local0)
                If (LNotEqual (Local0, 0x09))
                {
                    ERR ("mI01", Z167, 0x0158, 0x00, 0x00, Local0, 0x09)
                }

                If (LNotEqual (Arg0, 0x00))
                {
                    ERR ("mI01", Z167, 0x015B, 0x00, 0x00, Arg0, 0x00)
                }

                Return (Arg0)
            }

            If (LEqual (CMD0, 0x10))
            {
                Store (ObjectType (Arg0), Local0)
                If (LAnd (LNotEqual (Local0, C009), LNotEqual (Local0, C00B)))
                {
                    ERR ("mI01", Z167, 0x0167, 0x00, 0x00, Local0, C00B)
                }

                If (CHK0)
                {
                    Add (Arg0, 0x02, Local0)
                    If (LNotEqual (Local0, 0xABCD0D0A))
                    {
                        ERR ("mI01", Z167, 0x016D, 0x00, 0x00, Local0, 0xABCD0D0A)
                    }

                    If (LNotEqual (Arg0, 0xABCD0D08))
                    {
                        ERR ("mI01", Z167, 0x0170, 0x00, 0x00, Arg0, 0xABCD0D08)
                    }
                }

                Return (Arg0)
            }
        }

        Switch (ToInteger (CMD0))
        {
            Case (0x01)
            {
                ACT0 (OT00, Arg0, C009, 0x00)
                ACT0 (LN00, Arg0, 0x00, 0x00)
                ACT0 (AD00, Arg0, 0x01, 0xABCD0001)
            }
            Case (0x02)
            {
                ACT0 (OT00, Arg0, C00A, 0x00)
                ACT0 (LN01, Arg0, 0x00, 0x00)
            }
            Case (0x03)
            {
                ACT0 (OT00, Arg0, C00A, 0x00)
                ACT0 (LN02, Arg0, 0x00, 0x00)
                ACT0 (AD00, Arg0, 0x05, 0xABCD0805)
            }
            Case (0x04)
            {
                ACT0 (OT00, Arg0, C00B, 0x00)
                ACT0 (LN03, Arg0, 0x00, 0x00)
                ACT0 (AD00, Arg0, 0x07, 0x000000B4B3B2B1B7)
            }
            Case (0x05)
            {
                ACT0 (OT00, Arg0, C00C, 0x00)
                ACT0 (LN04, Arg0, 0x00, 0x00)
            }
            Case (0x06)
            {
                ACT0 (OT00, Arg0, C009, 0x00)
                ACT0 (LN05, Arg0, 0x00, 0x00)
                ACT0 (AD00, Arg0, 0x09, 0xABCD0A09)
            }
            Case (0x07)
            {
                ACT0 (OT00, Arg0, C00E, 0x00)
            }
            Case (0x08)
            {
                ACT0 (OT00, Arg0, C00F, 0x00)
            }
            Case (0x09)
            {
                ACT0 (OT00, Arg0, C011, 0x00)
            }
            Case (0x0A)
            {
                ACT0 (OT00, Arg0, C012, 0x00)
            }
            Case (0x0B)
            {
                ACT0 (OT00, Arg0, C013, 0x00)
            }
            Case (0x0C)
            {
                ACT0 (OT00, Arg0, C014, 0x00)
            }
            Case (0x0D)
            {
                ACT0 (OT00, Arg0, C015, 0x00)
            }
            Case (0x0E)
            {
                ACT0 (OT00, Arg0, C009, 0x00)
                ACT0 (LN06, Arg0, 0x00, 0x00)
                ACT0 (AD00, Arg0, 0x09, 0xABABABB4)
            }
            Case (0x0F)
            {
                ACT0 (OT00, Arg0, C009, 0x00)
                ACT0 (LN07, Arg0, 0x00, 0x00)
                ACT0 (AD00, Arg0, 0x09, 0x09)
            }
            Case (0x10)
            {
                ACT0 (OT00, Arg0, C00B, 0x00)
                ACT0 (LN08, Arg0, 0x00, 0x00)
                ACT0 (AD00, Arg0, 0x02, Buffer (0x04)
                    {
                         0x0A, 0x0D, 0xCD, 0xAB                           // ....
                    })
            }
            Default
            {
                ACT0 (OT00, Arg0, C008, 0x00)
            }

        }

        Return (Arg0)
    }

    Method (MI02, 2, NotSerialized)
    {
        MI01 (Arg0)
        MI01 (Arg1)
        Return (Arg0)
    }

    Method (MI03, 3, NotSerialized)
    {
        MI01 (Arg0)
        MI01 (Arg1)
        MI01 (Arg2)
        Return (Arg0)
    }

    Method (MI04, 4, NotSerialized)
    {
        MI01 (Arg0)
        MI01 (Arg1)
        MI01 (Arg2)
        MI01 (Arg3)
        Return (Arg0)
    }

    Method (MI05, 5, NotSerialized)
    {
        MI01 (Arg0)
        MI01 (Arg1)
        MI01 (Arg2)
        MI01 (Arg3)
        MI01 (Arg4)
        Return (Arg0)
    }

    Method (MI06, 6, NotSerialized)
    {
        MI01 (Arg0)
        MI01 (Arg1)
        MI01 (Arg2)
        MI01 (Arg3)
        MI01 (Arg4)
        MI01 (Arg5)
        Return (Arg0)
    }

    Method (MI07, 7, NotSerialized)
    {
        MI01 (Arg0)
        MI01 (Arg1)
        MI01 (Arg2)
        MI01 (Arg3)
        MI01 (Arg4)
        MI01 (Arg5)
        MI01 (Arg6)
        Return (Arg0)
    }

    Method (IN40, 7, Serialized)
    {
        Name (TS, "in40")
        Name (I000, 0xABCD0000)
        Name (S000, "qwrtyu0003")
        Name (S001, "abcd0800")
        Name (B000, Buffer (0x05)
        {
             0xB0, 0xB1, 0xB2, 0xB3, 0xB4                     // .....
        })
        Name (P000, Package (0x03)
        {
            0xABCD0901, 
            0xABCD0902, 
            0xABCD0903
        })
        Method (MMM0, 0, Serialized)
        {
            Name (IM00, 0xABCD0004)
            Name (SM00, "qwertyui")
        }

        Method (MMM1, 0, Serialized)
        {
            Name (IM00, 0xABCD0004)
            Name (SM00, "qwertyui")
            Return ("qwertyui")
        }

        Name (II00, 0x00)
        Name (II01, 0x00)
        Name (II03, 0x00)
        Name (II05, 0x00)
        Store (0x01, CMD0) /* \CMD0 */
        Store (I000, II00) /* \IN40.II00 */
        MI01 (II00)
        MI02 (II00, II00)
        MI03 (II00, II00, II00)
        MI04 (II00, II00, II00, II00)
        MI05 (II00, II00, II00, II00, II00)
        MI06 (II00, II00, II00, II00, II00, II00)
        MI07 (II00, II00, II00, II00, II00, II00, II00)
        MI01 (MI01 (II00))
        MI02 (MI01 (II00), MI02 (II00, II00))
        MI03 (MI01 (II00), MI02 (II00, II00), MI03 (II00, II00, II00))
        MI04 (MI01 (II00), MI02 (II00, II00), MI03 (II00, II00, II00), MI04 (II00, 
            II00, II00, II00))
        If (Y262)
        {
            MI05 (MI01 (II00), MI02 (II00, II00), MI03 (II00, II00, II00), MI04 (II00, 
                II00, II00, II00), MI05 (II00, II00, II00, II00, II00))
            MI06 (MI01 (II00), MI02 (II00, II00), MI03 (II00, II00, II00), MI04 (II00, 
                II00, II00, II00), MI05 (II00, II00, II00, II00, II00), MI06 (II00, II00, II00, 
                II00, II00, II00))
            MI07 (MI01 (II00), MI02 (II00, II00), MI03 (II00, II00, II00), MI04 (II00, 
                II00, II00, II00), MI05 (II00, II00, II00, II00, II00), MI06 (II00, II00, II00, 
                II00, II00, II00), MI07 (II00, II00, II00, II00, II00, II00, II00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (II00, Local1)
        Store (II00, Local3)
        Store (II00, Local5)
        MI01 (II00)
        MI02 (II00, Local1)
        MI03 (II00, Local1, II00)
        MI04 (II00, Local1, II00, Local3)
        MI05 (II00, Local1, II00, Local3, II00)
        MI06 (II00, Local1, II00, Local3, II00, Local5)
        MI07 (II00, Local1, II00, Local3, II00, Local5, II00)
        MI01 (MI01 (II00))
        MI02 (MI01 (II00), MI02 (II00, Local1))
        MI03 (MI01 (II00), MI02 (II00, Local1), MI03 (II00, Local1, II00))
        MI04 (MI01 (II00), MI02 (II00, Local1), MI03 (II00, Local1, II00), MI04 (II00, 
            Local1, II00, Local3))
        If (Y262)
        {
            MI05 (MI01 (II00), MI02 (II00, Local1), MI03 (II00, Local1, II00), MI04 (II00, 
                Local1, II00, Local3), MI05 (II00, Local1, II00, Local3, II00))
            MI06 (MI01 (II00), MI02 (II00, Local1), MI03 (II00, Local1, II00), MI04 (II00, 
                Local1, II00, Local3), MI05 (II00, Local1, II00, Local3, II00), MI06 (II00, Local1, II00, 
                Local3, II00, Local5))
            MI07 (MI01 (II00), MI02 (II00, Local1), MI03 (II00, Local1, II00), MI04 (II00, 
                Local1, II00, Local3), MI05 (II00, Local1, II00, Local3, II00), MI06 (II00, Local1, II00, 
                Local3, II00, Local5), MI07 (II00, Local1, II00, Local3, II00, Local5, II00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (II00, Arg1)
        Store (II00, Arg3)
        Store (II00, Arg5)
        MI01 (II00)
        MI02 (II00, Arg1)
        MI03 (II00, Arg1, II00)
        MI04 (II00, Arg1, II00, Arg3)
        MI05 (II00, Arg1, II00, Arg3, II00)
        MI06 (II00, Arg1, II00, Arg3, II00, Arg5)
        MI07 (II00, Arg1, II00, Arg3, II00, Arg5, II00)
        MI01 (MI01 (II00))
        MI02 (MI01 (II00), MI02 (II00, Arg1))
        MI03 (MI01 (II00), MI02 (II00, Arg1), MI03 (II00, Arg1, II00))
        MI04 (MI01 (II00), MI02 (II00, Arg1), MI03 (II00, Arg1, II00), MI04 (II00, 
            Arg1, II00, Arg3))
        If (Y262)
        {
            MI05 (MI01 (II00), MI02 (II00, Arg1), MI03 (II00, Arg1, II00), MI04 (II00, 
                Arg1, II00, Arg3), MI05 (II00, Arg1, II00, Arg3, II00))
            MI06 (MI01 (II00), MI02 (II00, Arg1), MI03 (II00, Arg1, II00), MI04 (II00, 
                Arg1, II00, Arg3), MI05 (II00, Arg1, II00, Arg3, II00), MI06 (II00, Arg1, II00, 
                Arg3, II00, Arg5))
            MI07 (MI01 (II00), MI02 (II00, Arg1), MI03 (II00, Arg1, II00), MI04 (II00, 
                Arg1, II00, Arg3), MI05 (II00, Arg1, II00, Arg3, II00), MI06 (II00, Arg1, II00, 
                Arg3, II00, Arg5), MI07 (II00, Arg1, II00, Arg3, II00, Arg5, II00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (II00, II01) /* \IN40.II01 */
        Store (II00, II03) /* \IN40.II03 */
        Store (II00, II05) /* \IN40.II05 */
        MI01 (II00)
        MI02 (II00, II01)
        MI03 (II00, II01, II00)
        MI04 (II00, II01, II00, II03)
        MI05 (II00, II01, II00, II03, II00)
        MI06 (II00, II01, II00, II03, II00, II05)
        MI07 (II00, II01, II00, II03, II00, II05, II00)
        MI01 (MI01 (II00))
        MI02 (MI01 (II00), MI02 (II00, II01))
        MI03 (MI01 (II00), MI02 (II00, II01), MI03 (II00, II01, II00))
        MI04 (MI01 (II00), MI02 (II00, II01), MI03 (II00, II01, II00), MI04 (II00, 
            II01, II00, II03))
        If (Y262)
        {
            MI05 (MI01 (II00), MI02 (II00, II01), MI03 (II00, II01, II00), MI04 (II00, 
                II01, II00, II03), MI05 (II00, II01, II00, II03, II00))
            MI06 (MI01 (II00), MI02 (II00, II01), MI03 (II00, II01, II00), MI04 (II00, 
                II01, II00, II03), MI05 (II00, II01, II00, II03, II00), MI06 (II00, II01, II00, 
                II03, II00, II05))
            MI07 (MI01 (II00), MI02 (II00, II01), MI03 (II00, II01, II00), MI04 (II00, 
                II01, II00, II03), MI05 (II00, II01, II00, II03, II00), MI06 (II00, II01, II00, 
                II03, II00, II05), MI07 (II00, II01, II00, II03, II00, II05, II00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Name (SS00, "v")
        Name (SS01, "v")
        Name (SS03, "v")
        Name (SS05, "v")
        Store (0x02, CMD0) /* \CMD0 */
        Store (S000, SS00) /* \IN40.SS00 */
        MI01 (SS00)
        MI02 (SS00, SS00)
        MI03 (SS00, SS00, SS00)
        MI04 (SS00, SS00, SS00, SS00)
        MI05 (SS00, SS00, SS00, SS00, SS00)
        MI06 (SS00, SS00, SS00, SS00, SS00, SS00)
        MI07 (SS00, SS00, SS00, SS00, SS00, SS00, SS00)
        MI01 (MI01 (SS00))
        MI02 (MI01 (SS00), MI02 (SS00, SS00))
        MI03 (MI01 (SS00), MI02 (SS00, SS00), MI03 (SS00, SS00, SS00))
        MI04 (MI01 (SS00), MI02 (SS00, SS00), MI03 (SS00, SS00, SS00), MI04 (SS00, 
            SS00, SS00, SS00))
        If (Y262)
        {
            MI05 (MI01 (SS00), MI02 (SS00, SS00), MI03 (SS00, SS00, SS00), MI04 (SS00, 
                SS00, SS00, SS00), MI05 (SS00, SS00, SS00, SS00, SS00))
            MI06 (MI01 (SS00), MI02 (SS00, SS00), MI03 (SS00, SS00, SS00), MI04 (SS00, 
                SS00, SS00, SS00), MI05 (SS00, SS00, SS00, SS00, SS00), MI06 (SS00, SS00, SS00, 
                SS00, SS00, SS00))
            MI07 (MI01 (SS00), MI02 (SS00, SS00), MI03 (SS00, SS00, SS00), MI04 (SS00, 
                SS00, SS00, SS00), MI05 (SS00, SS00, SS00, SS00, SS00), MI06 (SS00, SS00, SS00, 
                SS00, SS00, SS00), MI07 (SS00, SS00, SS00, SS00, SS00, SS00, SS00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (SS00, Local1)
        Store (SS00, Local3)
        Store (SS00, Local5)
        MI01 (SS00)
        MI02 (SS00, Local1)
        MI03 (SS00, Local1, SS00)
        MI04 (SS00, Local1, SS00, Local3)
        MI05 (SS00, Local1, SS00, Local3, SS00)
        MI06 (SS00, Local1, SS00, Local3, SS00, Local5)
        MI07 (SS00, Local1, SS00, Local3, SS00, Local5, SS00)
        MI01 (MI01 (SS00))
        MI02 (MI01 (SS00), MI02 (SS00, Local1))
        MI03 (MI01 (SS00), MI02 (SS00, Local1), MI03 (SS00, Local1, SS00))
        MI04 (MI01 (SS00), MI02 (SS00, Local1), MI03 (SS00, Local1, SS00), MI04 (SS00, 
            Local1, SS00, Local3))
        If (Y262)
        {
            MI05 (MI01 (SS00), MI02 (SS00, Local1), MI03 (SS00, Local1, SS00), MI04 (SS00, 
                Local1, SS00, Local3), MI05 (SS00, Local1, SS00, Local3, SS00))
            MI06 (MI01 (SS00), MI02 (SS00, Local1), MI03 (SS00, Local1, SS00), MI04 (SS00, 
                Local1, SS00, Local3), MI05 (SS00, Local1, SS00, Local3, SS00), MI06 (SS00, Local1, SS00, 
                Local3, SS00, Local5))
            MI07 (MI01 (SS00), MI02 (SS00, Local1), MI03 (SS00, Local1, SS00), MI04 (SS00, 
                Local1, SS00, Local3), MI05 (SS00, Local1, SS00, Local3, SS00), MI06 (SS00, Local1, SS00, 
                Local3, SS00, Local5), MI07 (SS00, Local1, SS00, Local3, SS00, Local5, SS00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (SS00, Arg1)
        Store (SS00, Arg3)
        Store (SS00, Arg5)
        MI01 (SS00)
        MI02 (SS00, Arg1)
        MI03 (SS00, Arg1, SS00)
        MI04 (SS00, Arg1, SS00, Arg3)
        MI05 (SS00, Arg1, SS00, Arg3, SS00)
        MI06 (SS00, Arg1, SS00, Arg3, SS00, Arg5)
        MI07 (SS00, Arg1, SS00, Arg3, SS00, Arg5, SS00)
        MI01 (MI01 (SS00))
        MI02 (MI01 (SS00), MI02 (SS00, Arg1))
        MI03 (MI01 (SS00), MI02 (SS00, Arg1), MI03 (SS00, Arg1, SS00))
        MI04 (MI01 (SS00), MI02 (SS00, Arg1), MI03 (SS00, Arg1, SS00), MI04 (SS00, 
            Arg1, SS00, Arg3))
        If (Y262)
        {
            MI05 (MI01 (SS00), MI02 (SS00, Arg1), MI03 (SS00, Arg1, SS00), MI04 (SS00, 
                Arg1, SS00, Arg3), MI05 (SS00, Arg1, SS00, Arg3, SS00))
            MI06 (MI01 (SS00), MI02 (SS00, Arg1), MI03 (SS00, Arg1, SS00), MI04 (SS00, 
                Arg1, SS00, Arg3), MI05 (SS00, Arg1, SS00, Arg3, SS00), MI06 (SS00, Arg1, SS00, 
                Arg3, SS00, Arg5))
            MI07 (MI01 (SS00), MI02 (SS00, Arg1), MI03 (SS00, Arg1, SS00), MI04 (SS00, 
                Arg1, SS00, Arg3), MI05 (SS00, Arg1, SS00, Arg3, SS00), MI06 (SS00, Arg1, SS00, 
                Arg3, SS00, Arg5), MI07 (SS00, Arg1, SS00, Arg3, SS00, Arg5, SS00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (SS00, SS01) /* \IN40.SS01 */
        Store (SS00, SS03) /* \IN40.SS03 */
        Store (SS00, SS05) /* \IN40.SS05 */
        MI01 (SS00)
        MI02 (SS00, SS01)
        MI03 (SS00, SS01, SS00)
        MI04 (SS00, SS01, SS00, SS03)
        MI05 (SS00, SS01, SS00, SS03, SS00)
        MI06 (SS00, SS01, SS00, SS03, SS00, SS05)
        MI07 (SS00, SS01, SS00, SS03, SS00, SS05, SS00)
        MI01 (MI01 (SS00))
        MI02 (MI01 (SS00), MI02 (SS00, SS01))
        MI03 (MI01 (SS00), MI02 (SS00, SS01), MI03 (SS00, SS01, SS00))
        MI04 (MI01 (SS00), MI02 (SS00, SS01), MI03 (SS00, SS01, SS00), MI04 (SS00, 
            SS01, SS00, SS03))
        If (Y262)
        {
            MI05 (MI01 (SS00), MI02 (SS00, SS01), MI03 (SS00, SS01, SS00), MI04 (SS00, 
                SS01, SS00, SS03), MI05 (SS00, SS01, SS00, SS03, SS00))
            MI06 (MI01 (SS00), MI02 (SS00, SS01), MI03 (SS00, SS01, SS00), MI04 (SS00, 
                SS01, SS00, SS03), MI05 (SS00, SS01, SS00, SS03, SS00), MI06 (SS00, SS01, SS00, 
                SS03, SS00, SS05))
            MI07 (MI01 (SS00), MI02 (SS00, SS01), MI03 (SS00, SS01, SS00), MI04 (SS00, 
                SS01, SS00, SS03), MI05 (SS00, SS01, SS00, SS03, SS00), MI06 (SS00, SS01, SS00, 
                SS03, SS00, SS05), MI07 (SS00, SS01, SS00, SS03, SS00, SS05, SS00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (0x03, CMD0) /* \CMD0 */
        Store (S001, SS00) /* \IN40.SS00 */
        MI01 (SS00)
        MI02 (SS00, SS00)
        MI03 (SS00, SS00, SS00)
        MI04 (SS00, SS00, SS00, SS00)
        MI05 (SS00, SS00, SS00, SS00, SS00)
        MI06 (SS00, SS00, SS00, SS00, SS00, SS00)
        MI07 (SS00, SS00, SS00, SS00, SS00, SS00, SS00)
        MI01 (MI01 (SS00))
        MI02 (MI01 (SS00), MI02 (SS00, SS00))
        MI03 (MI01 (SS00), MI02 (SS00, SS00), MI03 (SS00, SS00, SS00))
        MI04 (MI01 (SS00), MI02 (SS00, SS00), MI03 (SS00, SS00, SS00), MI04 (SS00, 
            SS00, SS00, SS00))
        If (Y262)
        {
            MI05 (MI01 (SS00), MI02 (SS00, SS00), MI03 (SS00, SS00, SS00), MI04 (SS00, 
                SS00, SS00, SS00), MI05 (SS00, SS00, SS00, SS00, SS00))
            MI06 (MI01 (SS00), MI02 (SS00, SS00), MI03 (SS00, SS00, SS00), MI04 (SS00, 
                SS00, SS00, SS00), MI05 (SS00, SS00, SS00, SS00, SS00), MI06 (SS00, SS00, SS00, 
                SS00, SS00, SS00))
            MI07 (MI01 (SS00), MI02 (SS00, SS00), MI03 (SS00, SS00, SS00), MI04 (SS00, 
                SS00, SS00, SS00), MI05 (SS00, SS00, SS00, SS00, SS00), MI06 (SS00, SS00, SS00, 
                SS00, SS00, SS00), MI07 (SS00, SS00, SS00, SS00, SS00, SS00, SS00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (SS00, Local1)
        Store (SS00, Local3)
        Store (SS00, Local5)
        MI01 (SS00)
        MI02 (SS00, Local1)
        MI03 (SS00, Local1, SS00)
        MI04 (SS00, Local1, SS00, Local3)
        MI05 (SS00, Local1, SS00, Local3, SS00)
        MI06 (SS00, Local1, SS00, Local3, SS00, Local5)
        MI07 (SS00, Local1, SS00, Local3, SS00, Local5, SS00)
        MI01 (MI01 (SS00))
        MI02 (MI01 (SS00), MI02 (SS00, Local1))
        MI03 (MI01 (SS00), MI02 (SS00, Local1), MI03 (SS00, Local1, SS00))
        MI04 (MI01 (SS00), MI02 (SS00, Local1), MI03 (SS00, Local1, SS00), MI04 (SS00, 
            Local1, SS00, Local3))
        If (Y262)
        {
            MI05 (MI01 (SS00), MI02 (SS00, Local1), MI03 (SS00, Local1, SS00), MI04 (SS00, 
                Local1, SS00, Local3), MI05 (SS00, Local1, SS00, Local3, SS00))
            MI06 (MI01 (SS00), MI02 (SS00, Local1), MI03 (SS00, Local1, SS00), MI04 (SS00, 
                Local1, SS00, Local3), MI05 (SS00, Local1, SS00, Local3, SS00), MI06 (SS00, Local1, SS00, 
                Local3, SS00, Local5))
            MI07 (MI01 (SS00), MI02 (SS00, Local1), MI03 (SS00, Local1, SS00), MI04 (SS00, 
                Local1, SS00, Local3), MI05 (SS00, Local1, SS00, Local3, SS00), MI06 (SS00, Local1, SS00, 
                Local3, SS00, Local5), MI07 (SS00, Local1, SS00, Local3, SS00, Local5, SS00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (SS00, Arg1)
        Store (SS00, Arg3)
        Store (SS00, Arg5)
        MI01 (SS00)
        MI02 (SS00, Arg1)
        MI03 (SS00, Arg1, SS00)
        MI04 (SS00, Arg1, SS00, Arg3)
        MI05 (SS00, Arg1, SS00, Arg3, SS00)
        MI06 (SS00, Arg1, SS00, Arg3, SS00, Arg5)
        MI07 (SS00, Arg1, SS00, Arg3, SS00, Arg5, SS00)
        MI01 (MI01 (SS00))
        MI02 (MI01 (SS00), MI02 (SS00, Arg1))
        MI03 (MI01 (SS00), MI02 (SS00, Arg1), MI03 (SS00, Arg1, SS00))
        MI04 (MI01 (SS00), MI02 (SS00, Arg1), MI03 (SS00, Arg1, SS00), MI04 (SS00, 
            Arg1, SS00, Arg3))
        If (Y262)
        {
            MI05 (MI01 (SS00), MI02 (SS00, Arg1), MI03 (SS00, Arg1, SS00), MI04 (SS00, 
                Arg1, SS00, Arg3), MI05 (SS00, Arg1, SS00, Arg3, SS00))
            MI06 (MI01 (SS00), MI02 (SS00, Arg1), MI03 (SS00, Arg1, SS00), MI04 (SS00, 
                Arg1, SS00, Arg3), MI05 (SS00, Arg1, SS00, Arg3, SS00), MI06 (SS00, Arg1, SS00, 
                Arg3, SS00, Arg5))
            MI07 (MI01 (SS00), MI02 (SS00, Arg1), MI03 (SS00, Arg1, SS00), MI04 (SS00, 
                Arg1, SS00, Arg3), MI05 (SS00, Arg1, SS00, Arg3, SS00), MI06 (SS00, Arg1, SS00, 
                Arg3, SS00, Arg5), MI07 (SS00, Arg1, SS00, Arg3, SS00, Arg5, SS00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (SS00, SS01) /* \IN40.SS01 */
        Store (SS00, SS03) /* \IN40.SS03 */
        Store (SS00, SS05) /* \IN40.SS05 */
        MI01 (SS00)
        MI02 (SS00, SS01)
        MI03 (SS00, SS01, SS00)
        MI04 (SS00, SS01, SS00, SS03)
        MI05 (SS00, SS01, SS00, SS03, SS00)
        MI06 (SS00, SS01, SS00, SS03, SS00, SS05)
        MI07 (SS00, SS01, SS00, SS03, SS00, SS05, SS00)
        MI01 (MI01 (SS00))
        MI02 (MI01 (SS00), MI02 (SS00, SS01))
        MI03 (MI01 (SS00), MI02 (SS00, SS01), MI03 (SS00, SS01, SS00))
        MI04 (MI01 (SS00), MI02 (SS00, SS01), MI03 (SS00, SS01, SS00), MI04 (SS00, 
            SS01, SS00, SS03))
        If (Y262)
        {
            MI05 (MI01 (SS00), MI02 (SS00, SS01), MI03 (SS00, SS01, SS00), MI04 (SS00, 
                SS01, SS00, SS03), MI05 (SS00, SS01, SS00, SS03, SS00))
            MI06 (MI01 (SS00), MI02 (SS00, SS01), MI03 (SS00, SS01, SS00), MI04 (SS00, 
                SS01, SS00, SS03), MI05 (SS00, SS01, SS00, SS03, SS00), MI06 (SS00, SS01, SS00, 
                SS03, SS00, SS05))
            MI07 (MI01 (SS00), MI02 (SS00, SS01), MI03 (SS00, SS01, SS00), MI04 (SS00, 
                SS01, SS00, SS03), MI05 (SS00, SS01, SS00, SS03, SS00), MI06 (SS00, SS01, SS00, 
                SS03, SS00, SS05), MI07 (SS00, SS01, SS00, SS03, SS00, SS05, SS00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Name (BB00, Buffer (0x05){})
        Name (BB01, Buffer (0x05){})
        Name (BB03, Buffer (0x05){})
        Name (BB05, Buffer (0x05){})
        Store (0x04, CMD0) /* \CMD0 */
        Store (B000, BB00) /* \IN40.BB00 */
        MI01 (BB00)
        MI02 (BB00, BB00)
        MI03 (BB00, BB00, BB00)
        MI04 (BB00, BB00, BB00, BB00)
        MI05 (BB00, BB00, BB00, BB00, BB00)
        MI06 (BB00, BB00, BB00, BB00, BB00, BB00)
        MI07 (BB00, BB00, BB00, BB00, BB00, BB00, BB00)
        MI01 (MI01 (BB00))
        MI02 (MI01 (BB00), MI02 (BB00, BB00))
        MI03 (MI01 (BB00), MI02 (BB00, BB00), MI03 (BB00, BB00, BB00))
        MI04 (MI01 (BB00), MI02 (BB00, BB00), MI03 (BB00, BB00, BB00), MI04 (BB00, 
            BB00, BB00, BB00))
        If (Y262)
        {
            MI05 (MI01 (BB00), MI02 (BB00, BB00), MI03 (BB00, BB00, BB00), MI04 (BB00, 
                BB00, BB00, BB00), MI05 (BB00, BB00, BB00, BB00, BB00))
            MI06 (MI01 (BB00), MI02 (BB00, BB00), MI03 (BB00, BB00, BB00), MI04 (BB00, 
                BB00, BB00, BB00), MI05 (BB00, BB00, BB00, BB00, BB00), MI06 (BB00, BB00, BB00, 
                BB00, BB00, BB00))
            MI07 (MI01 (BB00), MI02 (BB00, BB00), MI03 (BB00, BB00, BB00), MI04 (BB00, 
                BB00, BB00, BB00), MI05 (BB00, BB00, BB00, BB00, BB00), MI06 (BB00, BB00, BB00, 
                BB00, BB00, BB00), MI07 (BB00, BB00, BB00, BB00, BB00, BB00, BB00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (BB00, Local1)
        Store (BB00, Local3)
        Store (BB00, Local5)
        MI01 (BB00)
        MI02 (BB00, Local1)
        MI03 (BB00, Local1, BB00)
        MI04 (BB00, Local1, BB00, Local3)
        MI05 (BB00, Local1, BB00, Local3, BB00)
        MI06 (BB00, Local1, BB00, Local3, BB00, Local5)
        MI07 (BB00, Local1, BB00, Local3, BB00, Local5, BB00)
        MI01 (MI01 (BB00))
        MI02 (MI01 (BB00), MI02 (BB00, Local1))
        MI03 (MI01 (BB00), MI02 (BB00, Local1), MI03 (BB00, Local1, BB00))
        MI04 (MI01 (BB00), MI02 (BB00, Local1), MI03 (BB00, Local1, BB00), MI04 (BB00, 
            Local1, BB00, Local3))
        If (Y262)
        {
            MI05 (MI01 (BB00), MI02 (BB00, Local1), MI03 (BB00, Local1, BB00), MI04 (BB00, 
                Local1, BB00, Local3), MI05 (BB00, Local1, BB00, Local3, BB00))
            MI06 (MI01 (BB00), MI02 (BB00, Local1), MI03 (BB00, Local1, BB00), MI04 (BB00, 
                Local1, BB00, Local3), MI05 (BB00, Local1, BB00, Local3, BB00), MI06 (BB00, Local1, BB00, 
                Local3, BB00, Local5))
            MI07 (MI01 (BB00), MI02 (BB00, Local1), MI03 (BB00, Local1, BB00), MI04 (BB00, 
                Local1, BB00, Local3), MI05 (BB00, Local1, BB00, Local3, BB00), MI06 (BB00, Local1, BB00, 
                Local3, BB00, Local5), MI07 (BB00, Local1, BB00, Local3, BB00, Local5, BB00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (BB00, Arg1)
        Store (BB00, Arg3)
        Store (BB00, Arg5)
        MI01 (BB00)
        MI02 (BB00, Arg1)
        MI03 (BB00, Arg1, BB00)
        MI04 (BB00, Arg1, BB00, Arg3)
        MI05 (BB00, Arg1, BB00, Arg3, BB00)
        MI06 (BB00, Arg1, BB00, Arg3, BB00, Arg5)
        MI07 (BB00, Arg1, BB00, Arg3, BB00, Arg5, BB00)
        MI01 (MI01 (BB00))
        MI02 (MI01 (BB00), MI02 (BB00, Arg1))
        MI03 (MI01 (BB00), MI02 (BB00, Arg1), MI03 (BB00, Arg1, BB00))
        MI04 (MI01 (BB00), MI02 (BB00, Arg1), MI03 (BB00, Arg1, BB00), MI04 (BB00, 
            Arg1, BB00, Arg3))
        If (Y262)
        {
            MI05 (MI01 (BB00), MI02 (BB00, Arg1), MI03 (BB00, Arg1, BB00), MI04 (BB00, 
                Arg1, BB00, Arg3), MI05 (BB00, Arg1, BB00, Arg3, BB00))
            MI06 (MI01 (BB00), MI02 (BB00, Arg1), MI03 (BB00, Arg1, BB00), MI04 (BB00, 
                Arg1, BB00, Arg3), MI05 (BB00, Arg1, BB00, Arg3, BB00), MI06 (BB00, Arg1, BB00, 
                Arg3, BB00, Arg5))
            MI07 (MI01 (BB00), MI02 (BB00, Arg1), MI03 (BB00, Arg1, BB00), MI04 (BB00, 
                Arg1, BB00, Arg3), MI05 (BB00, Arg1, BB00, Arg3, BB00), MI06 (BB00, Arg1, BB00, 
                Arg3, BB00, Arg5), MI07 (BB00, Arg1, BB00, Arg3, BB00, Arg5, BB00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (BB00, BB01) /* \IN40.BB01 */
        Store (BB00, BB03) /* \IN40.BB03 */
        Store (BB00, BB05) /* \IN40.BB05 */
        MI01 (BB00)
        MI02 (BB00, BB01)
        MI03 (BB00, BB01, BB00)
        MI04 (BB00, BB01, BB00, BB03)
        MI05 (BB00, BB01, BB00, BB03, BB00)
        MI06 (BB00, BB01, BB00, BB03, BB00, BB05)
        MI07 (BB00, BB01, BB00, BB03, BB00, BB05, BB00)
        MI01 (MI01 (BB00))
        MI02 (MI01 (BB00), MI02 (BB00, BB01))
        MI03 (MI01 (BB00), MI02 (BB00, BB01), MI03 (BB00, BB01, BB00))
        MI04 (MI01 (BB00), MI02 (BB00, BB01), MI03 (BB00, BB01, BB00), MI04 (BB00, 
            BB01, BB00, BB03))
        If (Y262)
        {
            MI05 (MI01 (BB00), MI02 (BB00, BB01), MI03 (BB00, BB01, BB00), MI04 (BB00, 
                BB01, BB00, BB03), MI05 (BB00, BB01, BB00, BB03, BB00))
            MI06 (MI01 (BB00), MI02 (BB00, BB01), MI03 (BB00, BB01, BB00), MI04 (BB00, 
                BB01, BB00, BB03), MI05 (BB00, BB01, BB00, BB03, BB00), MI06 (BB00, BB01, BB00, 
                BB03, BB00, BB05))
            MI07 (MI01 (BB00), MI02 (BB00, BB01), MI03 (BB00, BB01, BB00), MI04 (BB00, 
                BB01, BB00, BB03), MI05 (BB00, BB01, BB00, BB03, BB00), MI06 (BB00, BB01, BB00, 
                BB03, BB00, BB05), MI07 (BB00, BB01, BB00, BB03, BB00, BB05, BB00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Name (PP00, Package (0x03)
        {
            0xABCD0901, 
            0xABCD0902, 
            0xABCD0903
        })
        Name (PP01, Package (0x03){})
        Name (PP03, Package (0x03){})
        Name (PP05, Package (0x03){})
        Store (0x05, CMD0) /* \CMD0 */
        If (CHK0)
        {
            Store (P000, PP00) /* \IN40.PP00 */
        }

        MI01 (PP00)
        MI02 (PP00, PP00)
        MI03 (PP00, PP00, PP00)
        MI04 (PP00, PP00, PP00, PP00)
        MI05 (PP00, PP00, PP00, PP00, PP00)
        MI06 (PP00, PP00, PP00, PP00, PP00, PP00)
        MI07 (PP00, PP00, PP00, PP00, PP00, PP00, PP00)
        MI01 (MI01 (PP00))
        MI02 (MI01 (PP00), MI02 (PP00, PP00))
        MI03 (MI01 (PP00), MI02 (PP00, PP00), MI03 (PP00, PP00, PP00))
        MI04 (MI01 (PP00), MI02 (PP00, PP00), MI03 (PP00, PP00, PP00), MI04 (PP00, 
            PP00, PP00, PP00))
        If (Y262)
        {
            MI05 (MI01 (PP00), MI02 (PP00, PP00), MI03 (PP00, PP00, PP00), MI04 (PP00, 
                PP00, PP00, PP00), MI05 (PP00, PP00, PP00, PP00, PP00))
            MI06 (MI01 (PP00), MI02 (PP00, PP00), MI03 (PP00, PP00, PP00), MI04 (PP00, 
                PP00, PP00, PP00), MI05 (PP00, PP00, PP00, PP00, PP00), MI06 (PP00, PP00, PP00, 
                PP00, PP00, PP00))
            MI07 (MI01 (PP00), MI02 (PP00, PP00), MI03 (PP00, PP00, PP00), MI04 (PP00, 
                PP00, PP00, PP00), MI05 (PP00, PP00, PP00, PP00, PP00), MI06 (PP00, PP00, PP00, 
                PP00, PP00, PP00), MI07 (PP00, PP00, PP00, PP00, PP00, PP00, PP00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (PP00, Local1)
        Store (PP00, Local3)
        Store (PP00, Local5)
        MI01 (PP00)
        MI02 (PP00, Local1)
        MI03 (PP00, Local1, PP00)
        MI04 (PP00, Local1, PP00, Local3)
        MI05 (PP00, Local1, PP00, Local3, PP00)
        MI06 (PP00, Local1, PP00, Local3, PP00, Local5)
        MI07 (PP00, Local1, PP00, Local3, PP00, Local5, PP00)
        MI01 (MI01 (PP00))
        MI02 (MI01 (PP00), MI02 (PP00, Local1))
        MI03 (MI01 (PP00), MI02 (PP00, Local1), MI03 (PP00, Local1, PP00))
        MI04 (MI01 (PP00), MI02 (PP00, Local1), MI03 (PP00, Local1, PP00), MI04 (PP00, 
            Local1, PP00, Local3))
        If (Y262)
        {
            MI05 (MI01 (PP00), MI02 (PP00, Local1), MI03 (PP00, Local1, PP00), MI04 (PP00, 
                Local1, PP00, Local3), MI05 (PP00, Local1, PP00, Local3, PP00))
            MI06 (MI01 (PP00), MI02 (PP00, Local1), MI03 (PP00, Local1, PP00), MI04 (PP00, 
                Local1, PP00, Local3), MI05 (PP00, Local1, PP00, Local3, PP00), MI06 (PP00, Local1, PP00, 
                Local3, PP00, Local5))
            MI07 (MI01 (PP00), MI02 (PP00, Local1), MI03 (PP00, Local1, PP00), MI04 (PP00, 
                Local1, PP00, Local3), MI05 (PP00, Local1, PP00, Local3, PP00), MI06 (PP00, Local1, PP00, 
                Local3, PP00, Local5), MI07 (PP00, Local1, PP00, Local3, PP00, Local5, PP00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (PP00, Arg1)
        Store (PP00, Arg3)
        Store (PP00, Arg5)
        MI01 (PP00)
        MI02 (PP00, Arg1)
        MI03 (PP00, Arg1, PP00)
        MI04 (PP00, Arg1, PP00, Arg3)
        MI05 (PP00, Arg1, PP00, Arg3, PP00)
        MI06 (PP00, Arg1, PP00, Arg3, PP00, Arg5)
        MI07 (PP00, Arg1, PP00, Arg3, PP00, Arg5, PP00)
        MI01 (MI01 (PP00))
        MI02 (MI01 (PP00), MI02 (PP00, Arg1))
        MI03 (MI01 (PP00), MI02 (PP00, Arg1), MI03 (PP00, Arg1, PP00))
        MI04 (MI01 (PP00), MI02 (PP00, Arg1), MI03 (PP00, Arg1, PP00), MI04 (PP00, 
            Arg1, PP00, Arg3))
        If (Y262)
        {
            MI05 (MI01 (PP00), MI02 (PP00, Arg1), MI03 (PP00, Arg1, PP00), MI04 (PP00, 
                Arg1, PP00, Arg3), MI05 (PP00, Arg1, PP00, Arg3, PP00))
            MI06 (MI01 (PP00), MI02 (PP00, Arg1), MI03 (PP00, Arg1, PP00), MI04 (PP00, 
                Arg1, PP00, Arg3), MI05 (PP00, Arg1, PP00, Arg3, PP00), MI06 (PP00, Arg1, PP00, 
                Arg3, PP00, Arg5))
            MI07 (MI01 (PP00), MI02 (PP00, Arg1), MI03 (PP00, Arg1, PP00), MI04 (PP00, 
                Arg1, PP00, Arg3), MI05 (PP00, Arg1, PP00, Arg3, PP00), MI06 (PP00, Arg1, PP00, 
                Arg3, PP00, Arg5), MI07 (PP00, Arg1, PP00, Arg3, PP00, Arg5, PP00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        If (CHK0)
        {
            Store (PP00, PP01) /* \IN40.PP01 */
            Store (PP00, PP03) /* \IN40.PP03 */
            Store (PP00, PP05) /* \IN40.PP05 */
            MI01 (PP00)
            MI02 (PP00, PP01)
            MI03 (PP00, PP01, PP00)
            MI04 (PP00, PP01, PP00, PP03)
            MI05 (PP00, PP01, PP00, PP03, PP00)
            MI06 (PP00, PP01, PP00, PP03, PP00, PP05)
            MI07 (PP00, PP01, PP00, PP03, PP00, PP05, PP00)
            MI01 (MI01 (PP00))
            MI02 (MI01 (PP00), MI02 (PP00, PP01))
            MI03 (MI01 (PP00), MI02 (PP00, PP01), MI03 (PP00, PP01, PP00))
            MI04 (MI01 (PP00), MI02 (PP00, PP01), MI03 (PP00, PP01, PP00), MI04 (PP00, 
                PP01, PP00, PP03))
            If (Y262)
            {
                MI05 (MI01 (PP00), MI02 (PP00, PP01), MI03 (PP00, PP01, PP00), MI04 (PP00, 
                    PP01, PP00, PP03), MI05 (PP00, PP01, PP00, PP03, PP00))
                MI06 (MI01 (PP00), MI02 (PP00, PP01), MI03 (PP00, PP01, PP00), MI04 (PP00, 
                    PP01, PP00, PP03), MI05 (PP00, PP01, PP00, PP03, PP00), MI06 (PP00, PP01, PP00, 
                    PP03, PP00, PP05))
                MI07 (MI01 (PP00), MI02 (PP00, PP01), MI03 (PP00, PP01, PP00), MI04 (PP00, 
                    PP01, PP00, PP03), MI05 (PP00, PP01, PP00, PP03, PP00), MI06 (PP00, PP01, PP00, 
                    PP03, PP00, PP05), MI07 (PP00, PP01, PP00, PP03, PP00, PP05, PP00))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }
        }
    }

    Method (IN41, 7, Serialized)
    {
        Name (TS, "in41")
        Event (E000)
        Mutex (MX00, 0x00)
        Method (MMM0, 0, Serialized)
        {
            Name (IM00, 0xABCD0004)
            Name (SM00, "qwertyui")
        }

        Method (MMM1, 0, Serialized)
        {
            Name (IM00, 0xABCD0004)
            Name (SM00, "qwertyui")
            Return ("qwertyui")
        }

        Device (D000)
        {
            Name (ID00, 0xABCD0005)
        }

        ThermalZone (TZ00)
        {
            Name (ITZ0, 0xABCD0006)
        }

        Processor (PR00, 0x00, 0xFFFFFFFF, 0x00)
        {
            Name (IPR0, 0xABCD0007)
        }

        PowerResource (PW00, 0x01, 0x0000)
        {
            Name (IPW0, 0xABCD0008)
        }

        OperationRegion (R000, SystemMemory, 0x00, 0x80)
        Name (B001, Buffer (0x05)
        {
             0xA0, 0xA1, 0xA2, 0xA3, 0xA4                     // .....
        })
        CreateField (B001, 0x00, 0x20, BF00)
        OperationRegion (R001, SystemMemory, 0x80, 0x80)
        Field (R001, ByteAcc, NoLock, Preserve)
        {
            F000,   32, 
            F001,   32, 
            F002,   32, 
            F003,   32
        }

        BankField (R001, F001, 0x00
, ByteAcc, NoLock, Preserve)
        {
            BNK0,   32
        }

        IndexField (F002, F003, ByteAcc, NoLock, Preserve)
        {
            IF00,   32, 
            IF01,   32
        }

        OperationRegion (R002, SystemMemory, 0x0100, 0x80)
        Field (R002, ByteAcc, NoLock, Preserve)
        {
            FF00,   32, 
            FF01,   32, 
            FF03,   32, 
            FF05,   32
        }

        Store (0x06, CMD0) /* \CMD0 */
        Store (0xABCD0A00, F000) /* \IN41.F000 */
        Store (F000, FF00) /* \IN41.FF00 */
        MI01 (FF00)
        MI02 (FF00, FF00)
        MI03 (FF00, FF00, FF00)
        MI04 (FF00, FF00, FF00, FF00)
        MI05 (FF00, FF00, FF00, FF00, FF00)
        MI06 (FF00, FF00, FF00, FF00, FF00, FF00)
        MI07 (FF00, FF00, FF00, FF00, FF00, FF00, FF00)
        MI01 (MI01 (FF00))
        MI02 (MI01 (FF00), MI02 (FF00, FF00))
        MI03 (MI01 (FF00), MI02 (FF00, FF00), MI03 (FF00, FF00, FF00))
        MI04 (MI01 (FF00), MI02 (FF00, FF00), MI03 (FF00, FF00, FF00), MI04 (FF00, 
            FF00, FF00, FF00))
        If (Y262)
        {
            MI05 (MI01 (FF00), MI02 (FF00, FF00), MI03 (FF00, FF00, FF00), MI04 (FF00, 
                FF00, FF00, FF00), MI05 (FF00, FF00, FF00, FF00, FF00))
            MI06 (MI01 (FF00), MI02 (FF00, FF00), MI03 (FF00, FF00, FF00), MI04 (FF00, 
                FF00, FF00, FF00), MI05 (FF00, FF00, FF00, FF00, FF00), MI06 (FF00, FF00, FF00, 
                FF00, FF00, FF00))
            MI07 (MI01 (FF00), MI02 (FF00, FF00), MI03 (FF00, FF00, FF00), MI04 (FF00, 
                FF00, FF00, FF00), MI05 (FF00, FF00, FF00, FF00, FF00), MI06 (FF00, FF00, FF00, 
                FF00, FF00, FF00), MI07 (FF00, FF00, FF00, FF00, FF00, FF00, FF00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (FF00, Local1)
        Store (FF00, Local3)
        Store (FF00, Local5)
        MI01 (FF00)
        MI02 (FF00, Local1)
        MI03 (FF00, Local1, FF00)
        MI04 (FF00, Local1, FF00, Local3)
        MI05 (FF00, Local1, FF00, Local3, FF00)
        MI06 (FF00, Local1, FF00, Local3, FF00, Local5)
        MI07 (FF00, Local1, FF00, Local3, FF00, Local5, FF00)
        MI01 (MI01 (FF00))
        MI02 (MI01 (FF00), MI02 (FF00, Local1))
        MI03 (MI01 (FF00), MI02 (FF00, Local1), MI03 (FF00, Local1, FF00))
        MI04 (MI01 (FF00), MI02 (FF00, Local1), MI03 (FF00, Local1, FF00), MI04 (FF00, 
            Local1, FF00, Local3))
        If (Y262)
        {
            MI05 (MI01 (FF00), MI02 (FF00, Local1), MI03 (FF00, Local1, FF00), MI04 (FF00, 
                Local1, FF00, Local3), MI05 (FF00, Local1, FF00, Local3, FF00))
            MI06 (MI01 (FF00), MI02 (FF00, Local1), MI03 (FF00, Local1, FF00), MI04 (FF00, 
                Local1, FF00, Local3), MI05 (FF00, Local1, FF00, Local3, FF00), MI06 (FF00, Local1, FF00, 
                Local3, FF00, Local5))
            MI07 (MI01 (FF00), MI02 (FF00, Local1), MI03 (FF00, Local1, FF00), MI04 (FF00, 
                Local1, FF00, Local3), MI05 (FF00, Local1, FF00, Local3, FF00), MI06 (FF00, Local1, FF00, 
                Local3, FF00, Local5), MI07 (FF00, Local1, FF00, Local3, FF00, Local5, FF00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (FF00, Arg1)
        Store (FF00, Arg3)
        Store (FF00, Arg5)
        MI01 (FF00)
        MI02 (FF00, Arg1)
        MI03 (FF00, Arg1, FF00)
        MI04 (FF00, Arg1, FF00, Arg3)
        MI05 (FF00, Arg1, FF00, Arg3, FF00)
        MI06 (FF00, Arg1, FF00, Arg3, FF00, Arg5)
        MI07 (FF00, Arg1, FF00, Arg3, FF00, Arg5, FF00)
        MI01 (MI01 (FF00))
        MI02 (MI01 (FF00), MI02 (FF00, Arg1))
        MI03 (MI01 (FF00), MI02 (FF00, Arg1), MI03 (FF00, Arg1, FF00))
        MI04 (MI01 (FF00), MI02 (FF00, Arg1), MI03 (FF00, Arg1, FF00), MI04 (FF00, 
            Arg1, FF00, Arg3))
        If (Y262)
        {
            MI05 (MI01 (FF00), MI02 (FF00, Arg1), MI03 (FF00, Arg1, FF00), MI04 (FF00, 
                Arg1, FF00, Arg3), MI05 (FF00, Arg1, FF00, Arg3, FF00))
            MI06 (MI01 (FF00), MI02 (FF00, Arg1), MI03 (FF00, Arg1, FF00), MI04 (FF00, 
                Arg1, FF00, Arg3), MI05 (FF00, Arg1, FF00, Arg3, FF00), MI06 (FF00, Arg1, FF00, 
                Arg3, FF00, Arg5))
            MI07 (MI01 (FF00), MI02 (FF00, Arg1), MI03 (FF00, Arg1, FF00), MI04 (FF00, 
                Arg1, FF00, Arg3), MI05 (FF00, Arg1, FF00, Arg3, FF00), MI06 (FF00, Arg1, FF00, 
                Arg3, FF00, Arg5), MI07 (FF00, Arg1, FF00, Arg3, FF00, Arg5, FF00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (FF00, FF01) /* \IN41.FF01 */
        Store (FF00, FF03) /* \IN41.FF03 */
        Store (FF00, FF05) /* \IN41.FF05 */
        MI01 (FF00)
        MI02 (FF00, FF01)
        MI03 (FF00, FF01, FF00)
        MI04 (FF00, FF01, FF00, FF03)
        MI05 (FF00, FF01, FF00, FF03, FF00)
        MI06 (FF00, FF01, FF00, FF03, FF00, FF05)
        MI07 (FF00, FF01, FF00, FF03, FF00, FF05, FF00)
        MI01 (MI01 (FF00))
        MI02 (MI01 (FF00), MI02 (FF00, FF01))
        MI03 (MI01 (FF00), MI02 (FF00, FF01), MI03 (FF00, FF01, FF00))
        MI04 (MI01 (FF00), MI02 (FF00, FF01), MI03 (FF00, FF01, FF00), MI04 (FF00, 
            FF01, FF00, FF03))
        If (Y262)
        {
            MI05 (MI01 (FF00), MI02 (FF00, FF01), MI03 (FF00, FF01, FF00), MI04 (FF00, 
                FF01, FF00, FF03), MI05 (FF00, FF01, FF00, FF03, FF00))
            MI06 (MI01 (FF00), MI02 (FF00, FF01), MI03 (FF00, FF01, FF00), MI04 (FF00, 
                FF01, FF00, FF03), MI05 (FF00, FF01, FF00, FF03, FF00), MI06 (FF00, FF01, FF00, 
                FF03, FF00, FF05))
            MI07 (MI01 (FF00), MI02 (FF00, FF01), MI03 (FF00, FF01, FF00), MI04 (FF00, 
                FF01, FF00, FF03), MI05 (FF00, FF01, FF00, FF03, FF00), MI06 (FF00, FF01, FF00, 
                FF03, FF00, FF05), MI07 (FF00, FF01, FF00, FF03, FF00, FF05, FF00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        OperationRegion (R003, SystemMemory, 0x0180, 0x80)
        Field (R003, ByteAcc, NoLock, Preserve)
        {
            F004,   32, 
            F005,   32
        }

        IndexField (F004, F005, ByteAcc, NoLock, Preserve)
        {
            IF02,   32
        }

        Store (0x0E, CMD0) /* \CMD0 */
        Store (0xABCD0B04, IF00) /* \IN41.IF00 */
        Store (IF00, IF02) /* \IN41.IF02 */
        MI01 (IF02)
        MI02 (IF02, IF02)
        MI03 (IF02, IF02, IF02)
        MI04 (IF02, IF02, IF02, IF02)
        MI05 (IF02, IF02, IF02, IF02, IF02)
        MI06 (IF02, IF02, IF02, IF02, IF02, IF02)
        MI07 (IF02, IF02, IF02, IF02, IF02, IF02, IF02)
        MI01 (MI01 (IF02))
        MI02 (MI01 (IF02), MI02 (IF02, IF02))
        MI03 (MI01 (IF02), MI02 (IF02, IF02), MI03 (IF02, IF02, IF02))
        MI04 (MI01 (IF02), MI02 (IF02, IF02), MI03 (IF02, IF02, IF02), MI04 (IF02, 
            IF02, IF02, IF02))
        If (Y262)
        {
            MI05 (MI01 (IF02), MI02 (IF02, IF02), MI03 (IF02, IF02, IF02), MI04 (IF02, 
                IF02, IF02, IF02), MI05 (IF02, IF02, IF02, IF02, IF02))
            MI06 (MI01 (IF02), MI02 (IF02, IF02), MI03 (IF02, IF02, IF02), MI04 (IF02, 
                IF02, IF02, IF02), MI05 (IF02, IF02, IF02, IF02, IF02), MI06 (IF02, IF02, IF02, 
                IF02, IF02, IF02))
            MI07 (MI01 (IF02), MI02 (IF02, IF02), MI03 (IF02, IF02, IF02), MI04 (IF02, 
                IF02, IF02, IF02), MI05 (IF02, IF02, IF02, IF02, IF02), MI06 (IF02, IF02, IF02, 
                IF02, IF02, IF02), MI07 (IF02, IF02, IF02, IF02, IF02, IF02, IF02))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (IF02, Local1)
        Store (IF02, Local3)
        Store (IF02, Local5)
        MI01 (IF02)
        MI02 (IF02, Local1)
        MI03 (IF02, Local1, IF02)
        MI04 (IF02, Local1, IF02, Local3)
        MI05 (IF02, Local1, IF02, Local3, IF02)
        MI06 (IF02, Local1, IF02, Local3, IF02, Local5)
        MI07 (IF02, Local1, IF02, Local3, IF02, Local5, IF02)
        MI01 (MI01 (IF02))
        MI02 (MI01 (IF02), MI02 (IF02, Local1))
        MI03 (MI01 (IF02), MI02 (IF02, Local1), MI03 (IF02, Local1, IF02))
        MI04 (MI01 (IF02), MI02 (IF02, Local1), MI03 (IF02, Local1, IF02), MI04 (IF02, 
            Local1, IF02, Local3))
        If (Y262)
        {
            MI05 (MI01 (IF02), MI02 (IF02, Local1), MI03 (IF02, Local1, IF02), MI04 (IF02, 
                Local1, IF02, Local3), MI05 (IF02, Local1, IF02, Local3, IF02))
            MI06 (MI01 (IF02), MI02 (IF02, Local1), MI03 (IF02, Local1, IF02), MI04 (IF02, 
                Local1, IF02, Local3), MI05 (IF02, Local1, IF02, Local3, IF02), MI06 (IF02, Local1, IF02, 
                Local3, IF02, Local5))
            MI07 (MI01 (IF02), MI02 (IF02, Local1), MI03 (IF02, Local1, IF02), MI04 (IF02, 
                Local1, IF02, Local3), MI05 (IF02, Local1, IF02, Local3, IF02), MI06 (IF02, Local1, IF02, 
                Local3, IF02, Local5), MI07 (IF02, Local1, IF02, Local3, IF02, Local5, IF02))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (IF02, Arg1)
        Store (IF02, Arg3)
        Store (IF02, Arg5)
        MI01 (IF02)
        MI02 (IF02, Arg1)
        MI03 (IF02, Arg1, IF02)
        MI04 (IF02, Arg1, IF02, Arg3)
        MI05 (IF02, Arg1, IF02, Arg3, IF02)
        MI06 (IF02, Arg1, IF02, Arg3, IF02, Arg5)
        MI07 (IF02, Arg1, IF02, Arg3, IF02, Arg5, IF02)
        MI01 (MI01 (IF02))
        MI02 (MI01 (IF02), MI02 (IF02, Arg1))
        MI03 (MI01 (IF02), MI02 (IF02, Arg1), MI03 (IF02, Arg1, IF02))
        MI04 (MI01 (IF02), MI02 (IF02, Arg1), MI03 (IF02, Arg1, IF02), MI04 (IF02, 
            Arg1, IF02, Arg3))
        If (Y262)
        {
            MI05 (MI01 (IF02), MI02 (IF02, Arg1), MI03 (IF02, Arg1, IF02), MI04 (IF02, 
                Arg1, IF02, Arg3), MI05 (IF02, Arg1, IF02, Arg3, IF02))
            MI06 (MI01 (IF02), MI02 (IF02, Arg1), MI03 (IF02, Arg1, IF02), MI04 (IF02, 
                Arg1, IF02, Arg3), MI05 (IF02, Arg1, IF02, Arg3, IF02), MI06 (IF02, Arg1, IF02, 
                Arg3, IF02, Arg5))
            MI07 (MI01 (IF02), MI02 (IF02, Arg1), MI03 (IF02, Arg1, IF02), MI04 (IF02, 
                Arg1, IF02, Arg3), MI05 (IF02, Arg1, IF02, Arg3, IF02), MI06 (IF02, Arg1, IF02, 
                Arg3, IF02, Arg5), MI07 (IF02, Arg1, IF02, Arg3, IF02, Arg5, IF02))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (IF02, FF01) /* \IN41.FF01 */
        Store (IF02, FF03) /* \IN41.FF03 */
        Store (IF02, FF05) /* \IN41.FF05 */
        MI01 (IF02)
        MI02 (IF02, FF01)
        MI03 (IF02, FF01, IF02)
        MI04 (IF02, FF01, IF02, FF03)
        MI05 (IF02, FF01, IF02, FF03, IF02)
        MI06 (IF02, FF01, IF02, FF03, IF02, FF05)
        MI07 (IF02, FF01, IF02, FF03, IF02, FF05, IF02)
        MI01 (MI01 (IF02))
        MI02 (MI01 (IF02), MI02 (IF02, FF01))
        MI03 (MI01 (IF02), MI02 (IF02, FF01), MI03 (IF02, FF01, IF02))
        MI04 (MI01 (IF02), MI02 (IF02, FF01), MI03 (IF02, FF01, IF02), MI04 (IF02, 
            FF01, IF02, FF03))
        If (Y262)
        {
            MI05 (MI01 (IF02), MI02 (IF02, FF01), MI03 (IF02, FF01, IF02), MI04 (IF02, 
                FF01, IF02, FF03), MI05 (IF02, FF01, IF02, FF03, IF02))
            MI06 (MI01 (IF02), MI02 (IF02, FF01), MI03 (IF02, FF01, IF02), MI04 (IF02, 
                FF01, IF02, FF03), MI05 (IF02, FF01, IF02, FF03, IF02), MI06 (IF02, FF01, IF02, 
                FF03, IF02, FF05))
            MI07 (MI01 (IF02), MI02 (IF02, FF01), MI03 (IF02, FF01, IF02), MI04 (IF02, 
                FF01, IF02, FF03), MI05 (IF02, FF01, IF02, FF03, IF02), MI06 (IF02, FF01, IF02, 
                FF03, IF02, FF05), MI07 (IF02, FF01, IF02, FF03, IF02, FF05, IF02))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        OperationRegion (R004, SystemMemory, 0x0200, 0x80)
        Field (R004, ByteAcc, NoLock, Preserve)
        {
            F006,   32
        }

        BankField (R004, F006, 0x00
, ByteAcc, NoLock, Preserve)
        {
            BNK1,   32
        }

        Store (0x0F, CMD0) /* \CMD0 */
        Store (0xABCD0C07, BNK0) /* \IN41.BNK0 */
        Store (BNK0, BNK1) /* \IN41.BNK1 */
        MI01 (BNK1)
        MI02 (BNK1, BNK1)
        MI03 (BNK1, BNK1, BNK1)
        MI04 (BNK1, BNK1, BNK1, BNK1)
        MI05 (BNK1, BNK1, BNK1, BNK1, BNK1)
        MI06 (BNK1, BNK1, BNK1, BNK1, BNK1, BNK1)
        MI07 (BNK1, BNK1, BNK1, BNK1, BNK1, BNK1, BNK1)
        MI01 (MI01 (BNK1))
        MI02 (MI01 (BNK1), MI02 (BNK1, BNK1))
        MI03 (MI01 (BNK1), MI02 (BNK1, BNK1), MI03 (BNK1, BNK1, BNK1))
        MI04 (MI01 (BNK1), MI02 (BNK1, BNK1), MI03 (BNK1, BNK1, BNK1), MI04 (BNK1, 
            BNK1, BNK1, BNK1))
        If (Y262)
        {
            MI05 (MI01 (BNK1), MI02 (BNK1, BNK1), MI03 (BNK1, BNK1, BNK1), MI04 (BNK1, 
                BNK1, BNK1, BNK1), MI05 (BNK1, BNK1, BNK1, BNK1, BNK1))
            MI06 (MI01 (BNK1), MI02 (BNK1, BNK1), MI03 (BNK1, BNK1, BNK1), MI04 (BNK1, 
                BNK1, BNK1, BNK1), MI05 (BNK1, BNK1, BNK1, BNK1, BNK1), MI06 (BNK1, BNK1, BNK1, 
                BNK1, BNK1, BNK1))
            MI07 (MI01 (BNK1), MI02 (BNK1, BNK1), MI03 (BNK1, BNK1, BNK1), MI04 (BNK1, 
                BNK1, BNK1, BNK1), MI05 (BNK1, BNK1, BNK1, BNK1, BNK1), MI06 (BNK1, BNK1, BNK1, 
                BNK1, BNK1, BNK1), MI07 (BNK1, BNK1, BNK1, BNK1, BNK1, BNK1, BNK1))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (BNK1, Local1)
        Store (BNK1, Local3)
        Store (BNK1, Local5)
        MI01 (BNK1)
        MI02 (BNK1, Local1)
        MI03 (BNK1, Local1, BNK1)
        MI04 (BNK1, Local1, BNK1, Local3)
        MI05 (BNK1, Local1, BNK1, Local3, BNK1)
        MI06 (BNK1, Local1, BNK1, Local3, BNK1, Local5)
        MI07 (BNK1, Local1, BNK1, Local3, BNK1, Local5, BNK1)
        MI01 (MI01 (BNK1))
        MI02 (MI01 (BNK1), MI02 (BNK1, Local1))
        MI03 (MI01 (BNK1), MI02 (BNK1, Local1), MI03 (BNK1, Local1, BNK1))
        MI04 (MI01 (BNK1), MI02 (BNK1, Local1), MI03 (BNK1, Local1, BNK1), MI04 (BNK1, 
            Local1, BNK1, Local3))
        If (Y262)
        {
            MI05 (MI01 (BNK1), MI02 (BNK1, Local1), MI03 (BNK1, Local1, BNK1), MI04 (BNK1, 
                Local1, BNK1, Local3), MI05 (BNK1, Local1, BNK1, Local3, BNK1))
            MI06 (MI01 (BNK1), MI02 (BNK1, Local1), MI03 (BNK1, Local1, BNK1), MI04 (BNK1, 
                Local1, BNK1, Local3), MI05 (BNK1, Local1, BNK1, Local3, BNK1), MI06 (BNK1, Local1, BNK1, 
                Local3, BNK1, Local5))
            MI07 (MI01 (BNK1), MI02 (BNK1, Local1), MI03 (BNK1, Local1, BNK1), MI04 (BNK1, 
                Local1, BNK1, Local3), MI05 (BNK1, Local1, BNK1, Local3, BNK1), MI06 (BNK1, Local1, BNK1, 
                Local3, BNK1, Local5), MI07 (BNK1, Local1, BNK1, Local3, BNK1, Local5, BNK1))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (BNK1, Arg1)
        Store (BNK1, Arg3)
        Store (BNK1, Arg5)
        MI01 (BNK1)
        MI02 (BNK1, Arg1)
        MI03 (BNK1, Arg1, BNK1)
        MI04 (BNK1, Arg1, BNK1, Arg3)
        MI05 (BNK1, Arg1, BNK1, Arg3, BNK1)
        MI06 (BNK1, Arg1, BNK1, Arg3, BNK1, Arg5)
        MI07 (BNK1, Arg1, BNK1, Arg3, BNK1, Arg5, BNK1)
        MI01 (MI01 (BNK1))
        MI02 (MI01 (BNK1), MI02 (BNK1, Arg1))
        MI03 (MI01 (BNK1), MI02 (BNK1, Arg1), MI03 (BNK1, Arg1, BNK1))
        MI04 (MI01 (BNK1), MI02 (BNK1, Arg1), MI03 (BNK1, Arg1, BNK1), MI04 (BNK1, 
            Arg1, BNK1, Arg3))
        If (Y262)
        {
            MI05 (MI01 (BNK1), MI02 (BNK1, Arg1), MI03 (BNK1, Arg1, BNK1), MI04 (BNK1, 
                Arg1, BNK1, Arg3), MI05 (BNK1, Arg1, BNK1, Arg3, BNK1))
            MI06 (MI01 (BNK1), MI02 (BNK1, Arg1), MI03 (BNK1, Arg1, BNK1), MI04 (BNK1, 
                Arg1, BNK1, Arg3), MI05 (BNK1, Arg1, BNK1, Arg3, BNK1), MI06 (BNK1, Arg1, BNK1, 
                Arg3, BNK1, Arg5))
            MI07 (MI01 (BNK1), MI02 (BNK1, Arg1), MI03 (BNK1, Arg1, BNK1), MI04 (BNK1, 
                Arg1, BNK1, Arg3), MI05 (BNK1, Arg1, BNK1, Arg3, BNK1), MI06 (BNK1, Arg1, BNK1, 
                Arg3, BNK1, Arg5), MI07 (BNK1, Arg1, BNK1, Arg3, BNK1, Arg5, BNK1))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (BNK1, FF01) /* \IN41.FF01 */
        Store (BNK1, FF03) /* \IN41.FF03 */
        Store (BNK1, FF05) /* \IN41.FF05 */
        MI01 (BNK1)
        MI02 (BNK1, FF01)
        MI03 (BNK1, FF01, BNK1)
        MI04 (BNK1, FF01, BNK1, FF03)
        MI05 (BNK1, FF01, BNK1, FF03, BNK1)
        MI06 (BNK1, FF01, BNK1, FF03, BNK1, FF05)
        MI07 (BNK1, FF01, BNK1, FF03, BNK1, FF05, BNK1)
        MI01 (MI01 (BNK1))
        MI02 (MI01 (BNK1), MI02 (BNK1, FF01))
        MI03 (MI01 (BNK1), MI02 (BNK1, FF01), MI03 (BNK1, FF01, BNK1))
        MI04 (MI01 (BNK1), MI02 (BNK1, FF01), MI03 (BNK1, FF01, BNK1), MI04 (BNK1, 
            FF01, BNK1, FF03))
        If (Y262)
        {
            MI05 (MI01 (BNK1), MI02 (BNK1, FF01), MI03 (BNK1, FF01, BNK1), MI04 (BNK1, 
                FF01, BNK1, FF03), MI05 (BNK1, FF01, BNK1, FF03, BNK1))
            MI06 (MI01 (BNK1), MI02 (BNK1, FF01), MI03 (BNK1, FF01, BNK1), MI04 (BNK1, 
                FF01, BNK1, FF03), MI05 (BNK1, FF01, BNK1, FF03, BNK1), MI06 (BNK1, FF01, BNK1, 
                FF03, BNK1, FF05))
            MI07 (MI01 (BNK1), MI02 (BNK1, FF01), MI03 (BNK1, FF01, BNK1), MI04 (BNK1, 
                FF01, BNK1, FF03), MI05 (BNK1, FF01, BNK1, FF03, BNK1), MI06 (BNK1, FF01, BNK1, 
                FF03, BNK1, FF05), MI07 (BNK1, FF01, BNK1, FF03, BNK1, FF05, BNK1))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Name (B002, Buffer (0x05)
        {
             0xA0, 0xA1, 0xA2, 0xA3, 0xA4                     // .....
        })
        CreateField (B002, 0x00, 0x20, BF01)
        Store (0x10, CMD0) /* \CMD0 */
        Store (0xABCD0D08, BF00) /* \IN41.BF00 */
        Store (BF00, BF01) /* \IN41.BF01 */
        MI01 (BF01)
        MI02 (BF01, BF01)
        MI03 (BF01, BF01, BF01)
        MI04 (BF01, BF01, BF01, BF01)
        MI05 (BF01, BF01, BF01, BF01, BF01)
        MI06 (BF01, BF01, BF01, BF01, BF01, BF01)
        MI07 (BF01, BF01, BF01, BF01, BF01, BF01, BF01)
        MI01 (MI01 (BF01))
        MI02 (MI01 (BF01), MI02 (BF01, BF01))
        MI03 (MI01 (BF01), MI02 (BF01, BF01), MI03 (BF01, BF01, BF01))
        MI04 (MI01 (BF01), MI02 (BF01, BF01), MI03 (BF01, BF01, BF01), MI04 (BF01, 
            BF01, BF01, BF01))
        If (Y262)
        {
            MI05 (MI01 (BF01), MI02 (BF01, BF01), MI03 (BF01, BF01, BF01), MI04 (BF01, 
                BF01, BF01, BF01), MI05 (BF01, BF01, BF01, BF01, BF01))
            MI06 (MI01 (BF01), MI02 (BF01, BF01), MI03 (BF01, BF01, BF01), MI04 (BF01, 
                BF01, BF01, BF01), MI05 (BF01, BF01, BF01, BF01, BF01), MI06 (BF01, BF01, BF01, 
                BF01, BF01, BF01))
            MI07 (MI01 (BF01), MI02 (BF01, BF01), MI03 (BF01, BF01, BF01), MI04 (BF01, 
                BF01, BF01, BF01), MI05 (BF01, BF01, BF01, BF01, BF01), MI06 (BF01, BF01, BF01, 
                BF01, BF01, BF01), MI07 (BF01, BF01, BF01, BF01, BF01, BF01, BF01))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (BF01, Local1)
        Store (BF01, Local3)
        Store (BF01, Local5)
        MI01 (BF01)
        MI02 (BF01, Local1)
        MI03 (BF01, Local1, BF01)
        MI04 (BF01, Local1, BF01, Local3)
        MI05 (BF01, Local1, BF01, Local3, BF01)
        MI06 (BF01, Local1, BF01, Local3, BF01, Local5)
        MI07 (BF01, Local1, BF01, Local3, BF01, Local5, BF01)
        MI01 (MI01 (BF01))
        MI02 (MI01 (BF01), MI02 (BF01, Local1))
        MI03 (MI01 (BF01), MI02 (BF01, Local1), MI03 (BF01, Local1, BF01))
        MI04 (MI01 (BF01), MI02 (BF01, Local1), MI03 (BF01, Local1, BF01), MI04 (BF01, 
            Local1, BF01, Local3))
        If (Y262)
        {
            MI05 (MI01 (BF01), MI02 (BF01, Local1), MI03 (BF01, Local1, BF01), MI04 (BF01, 
                Local1, BF01, Local3), MI05 (BF01, Local1, BF01, Local3, BF01))
            MI06 (MI01 (BF01), MI02 (BF01, Local1), MI03 (BF01, Local1, BF01), MI04 (BF01, 
                Local1, BF01, Local3), MI05 (BF01, Local1, BF01, Local3, BF01), MI06 (BF01, Local1, BF01, 
                Local3, BF01, Local5))
            MI07 (MI01 (BF01), MI02 (BF01, Local1), MI03 (BF01, Local1, BF01), MI04 (BF01, 
                Local1, BF01, Local3), MI05 (BF01, Local1, BF01, Local3, BF01), MI06 (BF01, Local1, BF01, 
                Local3, BF01, Local5), MI07 (BF01, Local1, BF01, Local3, BF01, Local5, BF01))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (BF01, Arg1)
        Store (BF01, Arg3)
        Store (BF01, Arg5)
        MI01 (BF01)
        MI02 (BF01, Arg1)
        MI03 (BF01, Arg1, BF01)
        MI04 (BF01, Arg1, BF01, Arg3)
        MI05 (BF01, Arg1, BF01, Arg3, BF01)
        MI06 (BF01, Arg1, BF01, Arg3, BF01, Arg5)
        MI07 (BF01, Arg1, BF01, Arg3, BF01, Arg5, BF01)
        MI01 (MI01 (BF01))
        MI02 (MI01 (BF01), MI02 (BF01, Arg1))
        MI03 (MI01 (BF01), MI02 (BF01, Arg1), MI03 (BF01, Arg1, BF01))
        MI04 (MI01 (BF01), MI02 (BF01, Arg1), MI03 (BF01, Arg1, BF01), MI04 (BF01, 
            Arg1, BF01, Arg3))
        If (Y262)
        {
            MI05 (MI01 (BF01), MI02 (BF01, Arg1), MI03 (BF01, Arg1, BF01), MI04 (BF01, 
                Arg1, BF01, Arg3), MI05 (BF01, Arg1, BF01, Arg3, BF01))
            MI06 (MI01 (BF01), MI02 (BF01, Arg1), MI03 (BF01, Arg1, BF01), MI04 (BF01, 
                Arg1, BF01, Arg3), MI05 (BF01, Arg1, BF01, Arg3, BF01), MI06 (BF01, Arg1, BF01, 
                Arg3, BF01, Arg5))
            MI07 (MI01 (BF01), MI02 (BF01, Arg1), MI03 (BF01, Arg1, BF01), MI04 (BF01, 
                Arg1, BF01, Arg3), MI05 (BF01, Arg1, BF01, Arg3, BF01), MI06 (BF01, Arg1, BF01, 
                Arg3, BF01, Arg5), MI07 (BF01, Arg1, BF01, Arg3, BF01, Arg5, BF01))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        Store (0x07, CMD0) /* \CMD0 */
        MI01 (D000)
        MI02 (D000, D000)
        MI03 (D000, D000, D000)
        MI04 (D000, D000, D000, D000)
        MI05 (D000, D000, D000, D000, D000)
        MI06 (D000, D000, D000, D000, D000, D000)
        MI07 (D000, D000, D000, D000, D000, D000, D000)
        MI01 (MI01 (D000))
        MI02 (MI01 (D000), MI02 (D000, D000))
        MI03 (MI01 (D000), MI02 (D000, D000), MI03 (D000, D000, D000))
        MI04 (MI01 (D000), MI02 (D000, D000), MI03 (D000, D000, D000), MI04 (D000, 
            D000, D000, D000))
        If (Y262)
        {
            MI05 (MI01 (D000), MI02 (D000, D000), MI03 (D000, D000, D000), MI04 (D000, 
                D000, D000, D000), MI05 (D000, D000, D000, D000, D000))
            MI06 (MI01 (D000), MI02 (D000, D000), MI03 (D000, D000, D000), MI04 (D000, 
                D000, D000, D000), MI05 (D000, D000, D000, D000, D000), MI06 (D000, D000, D000, 
                D000, D000, D000))
            MI07 (MI01 (D000), MI02 (D000, D000), MI03 (D000, D000, D000), MI04 (D000, 
                D000, D000, D000), MI05 (D000, D000, D000, D000, D000), MI06 (D000, D000, D000, 
                D000, D000, D000), MI07 (D000, D000, D000, D000, D000, D000, D000))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        If (SLC0)
        {
            MI01 (D000)
            MI02 (D000, Local1)
            MI03 (D000, Local1, D000)
            MI04 (D000, Local1, D000, Local3)
            MI05 (D000, Local1, D000, Local3, D000)
            MI06 (D000, Local1, D000, Local3, D000, Local5)
            MI07 (D000, Local1, D000, Local3, D000, Local5, D000)
            MI01 (MI01 (D000))
            MI02 (MI01 (D000), MI02 (D000, Local1))
            MI03 (MI01 (D000), MI02 (D000, Local1), MI03 (D000, Local1, D000))
            MI04 (MI01 (D000), MI02 (D000, Local1), MI03 (D000, Local1, D000), MI04 (D000, 
                Local1, D000, Local3))
            If (Y262)
            {
                MI05 (MI01 (D000), MI02 (D000, Local1), MI03 (D000, Local1, D000), MI04 (D000, 
                    Local1, D000, Local3), MI05 (D000, Local1, D000, Local3, D000))
                MI06 (MI01 (D000), MI02 (D000, Local1), MI03 (D000, Local1, D000), MI04 (D000, 
                    Local1, D000, Local3), MI05 (D000, Local1, D000, Local3, D000), MI06 (D000, Local1, D000, 
                    Local3, D000, Local5))
                MI07 (MI01 (D000), MI02 (D000, Local1), MI03 (D000, Local1, D000), MI04 (D000, 
                    Local1, D000, Local3), MI05 (D000, Local1, D000, Local3, D000), MI06 (D000, Local1, D000, 
                    Local3, D000, Local5), MI07 (D000, Local1, D000, Local3, D000, Local5, D000))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }

            MI01 (D000)
            MI02 (D000, Arg1)
            MI03 (D000, Arg1, D000)
            MI04 (D000, Arg1, D000, Arg3)
            MI05 (D000, Arg1, D000, Arg3, D000)
            MI06 (D000, Arg1, D000, Arg3, D000, Arg5)
            MI07 (D000, Arg1, D000, Arg3, D000, Arg5, D000)
            MI01 (MI01 (D000))
            MI02 (MI01 (D000), MI02 (D000, Arg1))
            MI03 (MI01 (D000), MI02 (D000, Arg1), MI03 (D000, Arg1, D000))
            MI04 (MI01 (D000), MI02 (D000, Arg1), MI03 (D000, Arg1, D000), MI04 (D000, 
                Arg1, D000, Arg3))
            If (Y262)
            {
                MI05 (MI01 (D000), MI02 (D000, Arg1), MI03 (D000, Arg1, D000), MI04 (D000, 
                    Arg1, D000, Arg3), MI05 (D000, Arg1, D000, Arg3, D000))
                MI06 (MI01 (D000), MI02 (D000, Arg1), MI03 (D000, Arg1, D000), MI04 (D000, 
                    Arg1, D000, Arg3), MI05 (D000, Arg1, D000, Arg3, D000), MI06 (D000, Arg1, D000, 
                    Arg3, D000, Arg5))
                MI07 (MI01 (D000), MI02 (D000, Arg1), MI03 (D000, Arg1, D000), MI04 (D000, 
                    Arg1, D000, Arg3), MI05 (D000, Arg1, D000, Arg3, D000), MI06 (D000, Arg1, D000, 
                    Arg3, D000, Arg5), MI07 (D000, Arg1, D000, Arg3, D000, Arg5, D000))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }
        }

        Store (0x08, CMD0) /* \CMD0 */
        MI01 (E000)
        MI02 (E000, E000)
        MI03 (E000, E000, E000)
        MI04 (E000, E000, E000, E000)
        MI05 (E000, E000, E000, E000, E000)
        MI06 (E000, E000, E000, E000, E000, E000)
        MI07 (E000, E000, E000, E000, E000, E000, E000)
        MI01 (MI01 (E000))
        MI02 (MI01 (E000), MI02 (E000, E000))
        MI03 (MI01 (E000), MI02 (E000, E000), MI03 (E000, E000, E000))
        MI04 (MI01 (E000), MI02 (E000, E000), MI03 (E000, E000, E000), MI04 (E000, 
            E000, E000, E000))
        If (Y262)
        {
            MI05 (MI01 (E000), MI02 (E000, E000), MI03 (E000, E000, E000), MI04 (E000, 
                E000, E000, E000), MI05 (E000, E000, E000, E000, E000))
            MI06 (MI01 (E000), MI02 (E000, E000), MI03 (E000, E000, E000), MI04 (E000, 
                E000, E000, E000), MI05 (E000, E000, E000, E000, E000), MI06 (E000, E000, E000, 
                E000, E000, E000))
            MI07 (MI01 (E000), MI02 (E000, E000), MI03 (E000, E000, E000), MI04 (E000, 
                E000, E000, E000), MI05 (E000, E000, E000, E000, E000), MI06 (E000, E000, E000, 
                E000, E000, E000), MI07 (E000, E000, E000, E000, E000, E000, E000))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        If (SLC0)
        {
            Store (0x00, Local0)
            Store (0x02, Local2)
            Store (0x04, Local4)
            MI01 (E000)
            MI02 (E000, Local0)
            MI03 (E000, Local0, E000)
            MI04 (E000, Local0, E000, Local2)
            MI05 (E000, Local0, E000, Local2, E000)
            MI06 (E000, Local0, E000, Local2, E000, Local4)
            MI07 (E000, Local0, E000, Local2, E000, Local4, E000)
            MI01 (MI01 (E000))
            MI02 (MI01 (E000), MI02 (E000, Local0))
            MI03 (MI01 (E000), MI02 (E000, Local0), MI03 (E000, Local0, E000))
            MI04 (MI01 (E000), MI02 (E000, Local0), MI03 (E000, Local0, E000), MI04 (E000, 
                Local0, E000, Local2))
            If (Y262)
            {
                MI05 (MI01 (E000), MI02 (E000, Local0), MI03 (E000, Local0, E000), MI04 (E000, 
                    Local0, E000, Local2), MI05 (E000, Local0, E000, Local2, E000))
                MI06 (MI01 (E000), MI02 (E000, Local0), MI03 (E000, Local0, E000), MI04 (E000, 
                    Local0, E000, Local2), MI05 (E000, Local0, E000, Local2, E000), MI06 (E000, Local0, E000, 
                    Local2, E000, Local4))
                MI07 (MI01 (E000), MI02 (E000, Local0), MI03 (E000, Local0, E000), MI04 (E000, 
                    Local0, E000, Local2), MI05 (E000, Local0, E000, Local2, E000), MI06 (E000, Local0, E000, 
                    Local2, E000, Local4), MI07 (E000, Local0, E000, Local2, E000, Local4, E000))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }

            MI01 (E000)
            MI02 (E000, Arg0)
            MI03 (E000, Arg0, E000)
            MI04 (E000, Arg0, E000, Arg2)
            MI05 (E000, Arg0, E000, Arg2, E000)
            MI06 (E000, Arg0, E000, Arg2, E000, Arg4)
            MI07 (E000, Arg0, E000, Arg2, E000, Arg4, E000)
            MI01 (MI01 (E000))
            MI02 (MI01 (E000), MI02 (E000, Arg0))
            MI03 (MI01 (E000), MI02 (E000, Arg0), MI03 (E000, Arg0, E000))
            MI04 (MI01 (E000), MI02 (E000, Arg0), MI03 (E000, Arg0, E000), MI04 (E000, 
                Arg0, E000, Arg2))
            If (Y262)
            {
                MI05 (MI01 (E000), MI02 (E000, Arg0), MI03 (E000, Arg0, E000), MI04 (E000, 
                    Arg0, E000, Arg2), MI05 (E000, Arg0, E000, Arg2, E000))
                MI06 (MI01 (E000), MI02 (E000, Arg0), MI03 (E000, Arg0, E000), MI04 (E000, 
                    Arg0, E000, Arg2), MI05 (E000, Arg0, E000, Arg2, E000), MI06 (E000, Arg0, E000, 
                    Arg2, E000, Arg4))
                MI07 (MI01 (E000), MI02 (E000, Arg0), MI03 (E000, Arg0, E000), MI04 (E000, 
                    Arg0, E000, Arg2), MI05 (E000, Arg0, E000, Arg2, E000), MI06 (E000, Arg0, E000, 
                    Arg2, E000, Arg4), MI07 (E000, Arg0, E000, Arg2, E000, Arg4, E000))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }
        }

        Store (0x09, CMD0) /* \CMD0 */
        MI01 (MX00)
        MI02 (MX00, MX00)
        MI03 (MX00, MX00, MX00)
        MI04 (MX00, MX00, MX00, MX00)
        MI05 (MX00, MX00, MX00, MX00, MX00)
        MI06 (MX00, MX00, MX00, MX00, MX00, MX00)
        MI07 (MX00, MX00, MX00, MX00, MX00, MX00, MX00)
        MI01 (MI01 (MX00))
        MI02 (MI01 (MX00), MI02 (MX00, MX00))
        MI03 (MI01 (MX00), MI02 (MX00, MX00), MI03 (MX00, MX00, MX00))
        MI04 (MI01 (MX00), MI02 (MX00, MX00), MI03 (MX00, MX00, MX00), MI04 (MX00, 
            MX00, MX00, MX00))
        If (Y262)
        {
            MI05 (MI01 (MX00), MI02 (MX00, MX00), MI03 (MX00, MX00, MX00), MI04 (MX00, 
                MX00, MX00, MX00), MI05 (MX00, MX00, MX00, MX00, MX00))
            MI06 (MI01 (MX00), MI02 (MX00, MX00), MI03 (MX00, MX00, MX00), MI04 (MX00, 
                MX00, MX00, MX00), MI05 (MX00, MX00, MX00, MX00, MX00), MI06 (MX00, MX00, MX00, 
                MX00, MX00, MX00))
            MI07 (MI01 (MX00), MI02 (MX00, MX00), MI03 (MX00, MX00, MX00), MI04 (MX00, 
                MX00, MX00, MX00), MI05 (MX00, MX00, MX00, MX00, MX00), MI06 (MX00, MX00, MX00, 
                MX00, MX00, MX00), MI07 (MX00, MX00, MX00, MX00, MX00, MX00, MX00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        If (SLCK)
        {
            MI01 (MX00)
            MI02 (MX00, Local1)
            MI03 (MX00, Local1, MX00)
            MI04 (MX00, Local1, MX00, Local3)
            MI05 (MX00, Local1, MX00, Local3, MX00)
            MI06 (MX00, Local1, MX00, Local3, MX00, Local5)
            MI07 (MX00, Local1, MX00, Local3, MX00, Local5, MX00)
            MI01 (MI01 (MX00))
            MI02 (MI01 (MX00), MI02 (MX00, Local1))
            MI03 (MI01 (MX00), MI02 (MX00, Local1), MI03 (MX00, Local1, MX00))
            MI04 (MI01 (MX00), MI02 (MX00, Local1), MI03 (MX00, Local1, MX00), MI04 (MX00, 
                Local1, MX00, Local3))
            If (Y262)
            {
                MI05 (MI01 (MX00), MI02 (MX00, Local1), MI03 (MX00, Local1, MX00), MI04 (MX00, 
                    Local1, MX00, Local3), MI05 (MX00, Local1, MX00, Local3, MX00))
                MI06 (MI01 (MX00), MI02 (MX00, Local1), MI03 (MX00, Local1, MX00), MI04 (MX00, 
                    Local1, MX00, Local3), MI05 (MX00, Local1, MX00, Local3, MX00), MI06 (MX00, Local1, MX00, 
                    Local3, MX00, Local5))
                MI07 (MI01 (MX00), MI02 (MX00, Local1), MI03 (MX00, Local1, MX00), MI04 (MX00, 
                    Local1, MX00, Local3), MI05 (MX00, Local1, MX00, Local3, MX00), MI06 (MX00, Local1, MX00, 
                    Local3, MX00, Local5), MI07 (MX00, Local1, MX00, Local3, MX00, Local5, MX00))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }

            MI01 (MX00)
            MI02 (MX00, Arg1)
            MI03 (MX00, Arg1, MX00)
            MI04 (MX00, Arg1, MX00, Arg3)
            MI05 (MX00, Arg1, MX00, Arg3, MX00)
            MI06 (MX00, Arg1, MX00, Arg3, MX00, Arg5)
            MI07 (MX00, Arg1, MX00, Arg3, MX00, Arg5, MX00)
            MI01 (MI01 (MX00))
            MI02 (MI01 (MX00), MI02 (MX00, Arg1))
            MI03 (MI01 (MX00), MI02 (MX00, Arg1), MI03 (MX00, Arg1, MX00))
            MI04 (MI01 (MX00), MI02 (MX00, Arg1), MI03 (MX00, Arg1, MX00), MI04 (MX00, 
                Arg1, MX00, Arg3))
            If (Y262)
            {
                MI05 (MI01 (MX00), MI02 (MX00, Arg1), MI03 (MX00, Arg1, MX00), MI04 (MX00, 
                    Arg1, MX00, Arg3), MI05 (MX00, Arg1, MX00, Arg3, MX00))
                MI06 (MI01 (MX00), MI02 (MX00, Arg1), MI03 (MX00, Arg1, MX00), MI04 (MX00, 
                    Arg1, MX00, Arg3), MI05 (MX00, Arg1, MX00, Arg3, MX00), MI06 (MX00, Arg1, MX00, 
                    Arg3, MX00, Arg5))
                MI07 (MI01 (MX00), MI02 (MX00, Arg1), MI03 (MX00, Arg1, MX00), MI04 (MX00, 
                    Arg1, MX00, Arg3), MI05 (MX00, Arg1, MX00, Arg3, MX00), MI06 (MX00, Arg1, MX00, 
                    Arg3, MX00, Arg5), MI07 (MX00, Arg1, MX00, Arg3, MX00, Arg5, MX00))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }
        }

        Store (0x0A, CMD0) /* \CMD0 */
        MI01 (R000)
        MI02 (R000, R000)
        MI03 (R000, R000, R000)
        MI04 (R000, R000, R000, R000)
        MI05 (R000, R000, R000, R000, R000)
        MI06 (R000, R000, R000, R000, R000, R000)
        MI07 (R000, R000, R000, R000, R000, R000, R000)
        MI01 (MI01 (R000))
        MI02 (MI01 (R000), MI02 (R000, R000))
        MI03 (MI01 (R000), MI02 (R000, R000), MI03 (R000, R000, R000))
        MI04 (MI01 (R000), MI02 (R000, R000), MI03 (R000, R000, R000), MI04 (R000, 
            R000, R000, R000))
        If (Y262)
        {
            MI05 (MI01 (R000), MI02 (R000, R000), MI03 (R000, R000, R000), MI04 (R000, 
                R000, R000, R000), MI05 (R000, R000, R000, R000, R000))
            MI06 (MI01 (R000), MI02 (R000, R000), MI03 (R000, R000, R000), MI04 (R000, 
                R000, R000, R000), MI05 (R000, R000, R000, R000, R000), MI06 (R000, R000, R000, 
                R000, R000, R000))
            MI07 (MI01 (R000), MI02 (R000, R000), MI03 (R000, R000, R000), MI04 (R000, 
                R000, R000, R000), MI05 (R000, R000, R000, R000, R000), MI06 (R000, R000, R000, 
                R000, R000, R000), MI07 (R000, R000, R000, R000, R000, R000, R000))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        If (SLCK)
        {
            MI01 (R000)
            MI02 (R000, Local1)
            MI03 (R000, Local1, R000)
            MI04 (R000, Local1, R000, Local3)
            MI05 (R000, Local1, R000, Local3, R000)
            MI06 (R000, Local1, R000, Local3, R000, Local5)
            MI07 (R000, Local1, R000, Local3, R000, Local5, R000)
            MI01 (MI01 (R000))
            MI02 (MI01 (R000), MI02 (R000, Local1))
            MI03 (MI01 (R000), MI02 (R000, Local1), MI03 (R000, Local1, R000))
            MI04 (MI01 (R000), MI02 (R000, Local1), MI03 (R000, Local1, R000), MI04 (R000, 
                Local1, R000, Local3))
            If (Y262)
            {
                MI05 (MI01 (R000), MI02 (R000, Local1), MI03 (R000, Local1, R000), MI04 (R000, 
                    Local1, R000, Local3), MI05 (R000, Local1, R000, Local3, R000))
                MI06 (MI01 (R000), MI02 (R000, Local1), MI03 (R000, Local1, R000), MI04 (R000, 
                    Local1, R000, Local3), MI05 (R000, Local1, R000, Local3, R000), MI06 (R000, Local1, R000, 
                    Local3, R000, Local5))
                MI07 (MI01 (R000), MI02 (R000, Local1), MI03 (R000, Local1, R000), MI04 (R000, 
                    Local1, R000, Local3), MI05 (R000, Local1, R000, Local3, R000), MI06 (R000, Local1, R000, 
                    Local3, R000, Local5), MI07 (R000, Local1, R000, Local3, R000, Local5, R000))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }

            MI01 (R000)
            MI02 (R000, Arg1)
            MI03 (R000, Arg1, R000)
            MI04 (R000, Arg1, R000, Arg3)
            MI05 (R000, Arg1, R000, Arg3, R000)
            MI06 (R000, Arg1, R000, Arg3, R000, Arg5)
            MI07 (R000, Arg1, R000, Arg3, R000, Arg5, R000)
            MI01 (MI01 (R000))
            MI02 (MI01 (R000), MI02 (R000, Arg1))
            MI03 (MI01 (R000), MI02 (R000, Arg1), MI03 (R000, Arg1, R000))
            MI04 (MI01 (R000), MI02 (R000, Arg1), MI03 (R000, Arg1, R000), MI04 (R000, 
                Arg1, R000, Arg3))
            If (Y262)
            {
                MI05 (MI01 (R000), MI02 (R000, Arg1), MI03 (R000, Arg1, R000), MI04 (R000, 
                    Arg1, R000, Arg3), MI05 (R000, Arg1, R000, Arg3, R000))
                MI06 (MI01 (R000), MI02 (R000, Arg1), MI03 (R000, Arg1, R000), MI04 (R000, 
                    Arg1, R000, Arg3), MI05 (R000, Arg1, R000, Arg3, R000), MI06 (R000, Arg1, R000, 
                    Arg3, R000, Arg5))
                MI07 (MI01 (R000), MI02 (R000, Arg1), MI03 (R000, Arg1, R000), MI04 (R000, 
                    Arg1, R000, Arg3), MI05 (R000, Arg1, R000, Arg3, R000), MI06 (R000, Arg1, R000, 
                    Arg3, R000, Arg5), MI07 (R000, Arg1, R000, Arg3, R000, Arg5, R000))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }
        }

        Store (0x0B, CMD0) /* \CMD0 */
        MI01 (PW00)
        MI02 (PW00, PW00)
        MI03 (PW00, PW00, PW00)
        MI04 (PW00, PW00, PW00, PW00)
        MI05 (PW00, PW00, PW00, PW00, PW00)
        MI06 (PW00, PW00, PW00, PW00, PW00, PW00)
        MI07 (PW00, PW00, PW00, PW00, PW00, PW00, PW00)
        MI01 (MI01 (PW00))
        MI02 (MI01 (PW00), MI02 (PW00, PW00))
        MI03 (MI01 (PW00), MI02 (PW00, PW00), MI03 (PW00, PW00, PW00))
        MI04 (MI01 (PW00), MI02 (PW00, PW00), MI03 (PW00, PW00, PW00), MI04 (PW00, 
            PW00, PW00, PW00))
        If (Y262)
        {
            MI05 (MI01 (PW00), MI02 (PW00, PW00), MI03 (PW00, PW00, PW00), MI04 (PW00, 
                PW00, PW00, PW00), MI05 (PW00, PW00, PW00, PW00, PW00))
            MI06 (MI01 (PW00), MI02 (PW00, PW00), MI03 (PW00, PW00, PW00), MI04 (PW00, 
                PW00, PW00, PW00), MI05 (PW00, PW00, PW00, PW00, PW00), MI06 (PW00, PW00, PW00, 
                PW00, PW00, PW00))
            MI07 (MI01 (PW00), MI02 (PW00, PW00), MI03 (PW00, PW00, PW00), MI04 (PW00, 
                PW00, PW00, PW00), MI05 (PW00, PW00, PW00, PW00, PW00), MI06 (PW00, PW00, PW00, 
                PW00, PW00, PW00), MI07 (PW00, PW00, PW00, PW00, PW00, PW00, PW00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        If (SLCK)
        {
            MI01 (PW00)
            MI02 (PW00, Local1)
            MI03 (PW00, Local1, PW00)
            MI04 (PW00, Local1, PW00, Local3)
            MI05 (PW00, Local1, PW00, Local3, PW00)
            MI06 (PW00, Local1, PW00, Local3, PW00, Local5)
            MI07 (PW00, Local1, PW00, Local3, PW00, Local5, PW00)
            MI01 (MI01 (PW00))
            MI02 (MI01 (PW00), MI02 (PW00, Local1))
            MI03 (MI01 (PW00), MI02 (PW00, Local1), MI03 (PW00, Local1, PW00))
            MI04 (MI01 (PW00), MI02 (PW00, Local1), MI03 (PW00, Local1, PW00), MI04 (PW00, 
                Local1, PW00, Local3))
            If (Y262)
            {
                MI05 (MI01 (PW00), MI02 (PW00, Local1), MI03 (PW00, Local1, PW00), MI04 (PW00, 
                    Local1, PW00, Local3), MI05 (PW00, Local1, PW00, Local3, PW00))
                MI06 (MI01 (PW00), MI02 (PW00, Local1), MI03 (PW00, Local1, PW00), MI04 (PW00, 
                    Local1, PW00, Local3), MI05 (PW00, Local1, PW00, Local3, PW00), MI06 (PW00, Local1, PW00, 
                    Local3, PW00, Local5))
                MI07 (MI01 (PW00), MI02 (PW00, Local1), MI03 (PW00, Local1, PW00), MI04 (PW00, 
                    Local1, PW00, Local3), MI05 (PW00, Local1, PW00, Local3, PW00), MI06 (PW00, Local1, PW00, 
                    Local3, PW00, Local5), MI07 (PW00, Local1, PW00, Local3, PW00, Local5, PW00))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }

            MI01 (PW00)
            MI02 (PW00, Arg1)
            MI03 (PW00, Arg1, PW00)
            MI04 (PW00, Arg1, PW00, Arg3)
            MI05 (PW00, Arg1, PW00, Arg3, PW00)
            MI06 (PW00, Arg1, PW00, Arg3, PW00, Arg5)
            MI07 (PW00, Arg1, PW00, Arg3, PW00, Arg5, PW00)
            MI01 (MI01 (PW00))
            MI02 (MI01 (PW00), MI02 (PW00, Arg1))
            MI03 (MI01 (PW00), MI02 (PW00, Arg1), MI03 (PW00, Arg1, PW00))
            MI04 (MI01 (PW00), MI02 (PW00, Arg1), MI03 (PW00, Arg1, PW00), MI04 (PW00, 
                Arg1, PW00, Arg3))
            If (Y262)
            {
                MI05 (MI01 (PW00), MI02 (PW00, Arg1), MI03 (PW00, Arg1, PW00), MI04 (PW00, 
                    Arg1, PW00, Arg3), MI05 (PW00, Arg1, PW00, Arg3, PW00))
                MI06 (MI01 (PW00), MI02 (PW00, Arg1), MI03 (PW00, Arg1, PW00), MI04 (PW00, 
                    Arg1, PW00, Arg3), MI05 (PW00, Arg1, PW00, Arg3, PW00), MI06 (PW00, Arg1, PW00, 
                    Arg3, PW00, Arg5))
                MI07 (MI01 (PW00), MI02 (PW00, Arg1), MI03 (PW00, Arg1, PW00), MI04 (PW00, 
                    Arg1, PW00, Arg3), MI05 (PW00, Arg1, PW00, Arg3, PW00), MI06 (PW00, Arg1, PW00, 
                    Arg3, PW00, Arg5), MI07 (PW00, Arg1, PW00, Arg3, PW00, Arg5, PW00))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }
        }

        Store (0x0C, CMD0) /* \CMD0 */
        MI01 (PR00)
        MI02 (PR00, PR00)
        MI03 (PR00, PR00, PR00)
        MI04 (PR00, PR00, PR00, PR00)
        MI05 (PR00, PR00, PR00, PR00, PR00)
        MI06 (PR00, PR00, PR00, PR00, PR00, PR00)
        MI07 (PR00, PR00, PR00, PR00, PR00, PR00, PR00)
        MI01 (MI01 (PR00))
        MI02 (MI01 (PR00), MI02 (PR00, PR00))
        MI03 (MI01 (PR00), MI02 (PR00, PR00), MI03 (PR00, PR00, PR00))
        MI04 (MI01 (PR00), MI02 (PR00, PR00), MI03 (PR00, PR00, PR00), MI04 (PR00, 
            PR00, PR00, PR00))
        If (Y262)
        {
            MI05 (MI01 (PR00), MI02 (PR00, PR00), MI03 (PR00, PR00, PR00), MI04 (PR00, 
                PR00, PR00, PR00), MI05 (PR00, PR00, PR00, PR00, PR00))
            MI06 (MI01 (PR00), MI02 (PR00, PR00), MI03 (PR00, PR00, PR00), MI04 (PR00, 
                PR00, PR00, PR00), MI05 (PR00, PR00, PR00, PR00, PR00), MI06 (PR00, PR00, PR00, 
                PR00, PR00, PR00))
            MI07 (MI01 (PR00), MI02 (PR00, PR00), MI03 (PR00, PR00, PR00), MI04 (PR00, 
                PR00, PR00, PR00), MI05 (PR00, PR00, PR00, PR00, PR00), MI06 (PR00, PR00, PR00, 
                PR00, PR00, PR00), MI07 (PR00, PR00, PR00, PR00, PR00, PR00, PR00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        If (SLCK)
        {
            MI01 (PR00)
            MI02 (PR00, Local1)
            MI03 (PR00, Local1, PR00)
            MI04 (PR00, Local1, PR00, Local3)
            MI05 (PR00, Local1, PR00, Local3, PR00)
            MI06 (PR00, Local1, PR00, Local3, PR00, Local5)
            MI07 (PR00, Local1, PR00, Local3, PR00, Local5, PR00)
            MI01 (MI01 (PR00))
            MI02 (MI01 (PR00), MI02 (PR00, Local1))
            MI03 (MI01 (PR00), MI02 (PR00, Local1), MI03 (PR00, Local1, PR00))
            MI04 (MI01 (PR00), MI02 (PR00, Local1), MI03 (PR00, Local1, PR00), MI04 (PR00, 
                Local1, PR00, Local3))
            If (Y262)
            {
                MI05 (MI01 (PR00), MI02 (PR00, Local1), MI03 (PR00, Local1, PR00), MI04 (PR00, 
                    Local1, PR00, Local3), MI05 (PR00, Local1, PR00, Local3, PR00))
                MI06 (MI01 (PR00), MI02 (PR00, Local1), MI03 (PR00, Local1, PR00), MI04 (PR00, 
                    Local1, PR00, Local3), MI05 (PR00, Local1, PR00, Local3, PR00), MI06 (PR00, Local1, PR00, 
                    Local3, PR00, Local5))
                MI07 (MI01 (PR00), MI02 (PR00, Local1), MI03 (PR00, Local1, PR00), MI04 (PR00, 
                    Local1, PR00, Local3), MI05 (PR00, Local1, PR00, Local3, PR00), MI06 (PR00, Local1, PR00, 
                    Local3, PR00, Local5), MI07 (PR00, Local1, PR00, Local3, PR00, Local5, PR00))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }

            MI01 (PR00)
            MI02 (PR00, Arg1)
            MI03 (PR00, Arg1, PR00)
            MI04 (PR00, Arg1, PR00, Arg3)
            MI05 (PR00, Arg1, PR00, Arg3, PR00)
            MI06 (PR00, Arg1, PR00, Arg3, PR00, Arg5)
            MI07 (PR00, Arg1, PR00, Arg3, PR00, Arg5, PR00)
            MI01 (MI01 (PR00))
            MI02 (MI01 (PR00), MI02 (PR00, Arg1))
            MI03 (MI01 (PR00), MI02 (PR00, Arg1), MI03 (PR00, Arg1, PR00))
            MI04 (MI01 (PR00), MI02 (PR00, Arg1), MI03 (PR00, Arg1, PR00), MI04 (PR00, 
                Arg1, PR00, Arg3))
            If (Y262)
            {
                MI05 (MI01 (PR00), MI02 (PR00, Arg1), MI03 (PR00, Arg1, PR00), MI04 (PR00, 
                    Arg1, PR00, Arg3), MI05 (PR00, Arg1, PR00, Arg3, PR00))
                MI06 (MI01 (PR00), MI02 (PR00, Arg1), MI03 (PR00, Arg1, PR00), MI04 (PR00, 
                    Arg1, PR00, Arg3), MI05 (PR00, Arg1, PR00, Arg3, PR00), MI06 (PR00, Arg1, PR00, 
                    Arg3, PR00, Arg5))
                MI07 (MI01 (PR00), MI02 (PR00, Arg1), MI03 (PR00, Arg1, PR00), MI04 (PR00, 
                    Arg1, PR00, Arg3), MI05 (PR00, Arg1, PR00, Arg3, PR00), MI06 (PR00, Arg1, PR00, 
                    Arg3, PR00, Arg5), MI07 (PR00, Arg1, PR00, Arg3, PR00, Arg5, PR00))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }
        }

        Store (0x0D, CMD0) /* \CMD0 */
        MI01 (TZ00)
        MI02 (TZ00, TZ00)
        MI03 (TZ00, TZ00, TZ00)
        MI04 (TZ00, TZ00, TZ00, TZ00)
        MI05 (TZ00, TZ00, TZ00, TZ00, TZ00)
        MI06 (TZ00, TZ00, TZ00, TZ00, TZ00, TZ00)
        MI07 (TZ00, TZ00, TZ00, TZ00, TZ00, TZ00, TZ00)
        MI01 (MI01 (TZ00))
        MI02 (MI01 (TZ00), MI02 (TZ00, TZ00))
        MI03 (MI01 (TZ00), MI02 (TZ00, TZ00), MI03 (TZ00, TZ00, TZ00))
        MI04 (MI01 (TZ00), MI02 (TZ00, TZ00), MI03 (TZ00, TZ00, TZ00), MI04 (TZ00, 
            TZ00, TZ00, TZ00))
        If (Y262)
        {
            MI05 (MI01 (TZ00), MI02 (TZ00, TZ00), MI03 (TZ00, TZ00, TZ00), MI04 (TZ00, 
                TZ00, TZ00, TZ00), MI05 (TZ00, TZ00, TZ00, TZ00, TZ00))
            MI06 (MI01 (TZ00), MI02 (TZ00, TZ00), MI03 (TZ00, TZ00, TZ00), MI04 (TZ00, 
                TZ00, TZ00, TZ00), MI05 (TZ00, TZ00, TZ00, TZ00, TZ00), MI06 (TZ00, TZ00, TZ00, 
                TZ00, TZ00, TZ00))
            MI07 (MI01 (TZ00), MI02 (TZ00, TZ00), MI03 (TZ00, TZ00, TZ00), MI04 (TZ00, 
                TZ00, TZ00, TZ00), MI05 (TZ00, TZ00, TZ00, TZ00, TZ00), MI06 (TZ00, TZ00, TZ00, 
                TZ00, TZ00, TZ00), MI07 (TZ00, TZ00, TZ00, TZ00, TZ00, TZ00, TZ00))
        }
        Else
        {
            OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
        }

        If (SLCK)
        {
            MI01 (TZ00)
            MI02 (TZ00, Local1)
            MI03 (TZ00, Local1, TZ00)
            MI04 (TZ00, Local1, TZ00, Local3)
            MI05 (TZ00, Local1, TZ00, Local3, TZ00)
            MI06 (TZ00, Local1, TZ00, Local3, TZ00, Local5)
            MI07 (TZ00, Local1, TZ00, Local3, TZ00, Local5, TZ00)
            MI01 (MI01 (TZ00))
            MI02 (MI01 (TZ00), MI02 (TZ00, Local1))
            MI03 (MI01 (TZ00), MI02 (TZ00, Local1), MI03 (TZ00, Local1, TZ00))
            MI04 (MI01 (TZ00), MI02 (TZ00, Local1), MI03 (TZ00, Local1, TZ00), MI04 (TZ00, 
                Local1, TZ00, Local3))
            If (Y262)
            {
                MI05 (MI01 (TZ00), MI02 (TZ00, Local1), MI03 (TZ00, Local1, TZ00), MI04 (TZ00, 
                    Local1, TZ00, Local3), MI05 (TZ00, Local1, TZ00, Local3, TZ00))
                MI06 (MI01 (TZ00), MI02 (TZ00, Local1), MI03 (TZ00, Local1, TZ00), MI04 (TZ00, 
                    Local1, TZ00, Local3), MI05 (TZ00, Local1, TZ00, Local3, TZ00), MI06 (TZ00, Local1, TZ00, 
                    Local3, TZ00, Local5))
                MI07 (MI01 (TZ00), MI02 (TZ00, Local1), MI03 (TZ00, Local1, TZ00), MI04 (TZ00, 
                    Local1, TZ00, Local3), MI05 (TZ00, Local1, TZ00, Local3, TZ00), MI06 (TZ00, Local1, TZ00, 
                    Local3, TZ00, Local5), MI07 (TZ00, Local1, TZ00, Local3, TZ00, Local5, TZ00))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }

            MI01 (TZ00)
            MI02 (TZ00, Arg1)
            MI03 (TZ00, Arg1, TZ00)
            MI04 (TZ00, Arg1, TZ00, Arg3)
            MI05 (TZ00, Arg1, TZ00, Arg3, TZ00)
            MI06 (TZ00, Arg1, TZ00, Arg3, TZ00, Arg5)
            MI07 (TZ00, Arg1, TZ00, Arg3, TZ00, Arg5, TZ00)
            MI01 (MI01 (TZ00))
            MI02 (MI01 (TZ00), MI02 (TZ00, Arg1))
            MI03 (MI01 (TZ00), MI02 (TZ00, Arg1), MI03 (TZ00, Arg1, TZ00))
            MI04 (MI01 (TZ00), MI02 (TZ00, Arg1), MI03 (TZ00, Arg1, TZ00), MI04 (TZ00, 
                Arg1, TZ00, Arg3))
            If (Y262)
            {
                MI05 (MI01 (TZ00), MI02 (TZ00, Arg1), MI03 (TZ00, Arg1, TZ00), MI04 (TZ00, 
                    Arg1, TZ00, Arg3), MI05 (TZ00, Arg1, TZ00, Arg3, TZ00))
                MI06 (MI01 (TZ00), MI02 (TZ00, Arg1), MI03 (TZ00, Arg1, TZ00), MI04 (TZ00, 
                    Arg1, TZ00, Arg3), MI05 (TZ00, Arg1, TZ00, Arg3, TZ00), MI06 (TZ00, Arg1, TZ00, 
                    Arg3, TZ00, Arg5))
                MI07 (MI01 (TZ00), MI02 (TZ00, Arg1), MI03 (TZ00, Arg1, TZ00), MI04 (TZ00, 
                    Arg1, TZ00, Arg3), MI05 (TZ00, Arg1, TZ00, Arg3, TZ00), MI06 (TZ00, Arg1, TZ00, 
                    Arg3, TZ00, Arg5), MI07 (TZ00, Arg1, TZ00, Arg3, TZ00, Arg5, TZ00))
            }
            Else
            {
                OUTP ("WARNING: some tests of ns_in40.asl are blocked!")
            }
        }
    }

    Method (INI4, 0, NotSerialized)
    {
        SRMT ("in40")
        IN40 (0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        SRMT ("in41")
        IN41 (0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        CH03 ("ini4", Z167, 0x00, 0x11D9, 0x00)
    }

    Name (Z168, 0xA8)
    Method (IN50, 0, Serialized)
    {
        Name (TS, "in50")
        Store (0xABCD0000, Local0)
        Store (0x02, Local1)
        Add (Local0, Local1, Local2)
        Decrement (Local0)
        Increment (Local0)
        Divide (Local0, Local1, Local2, Local3)
        ShiftLeft (Local0, Local1, Local2)
        Multiply (Local0, Local1, Local2)
        Store (Local0, Local2)
        Or (Local0, Local1, Local2)
        ShiftRight (Local0, Local1, Local2)
        Subtract (Local0, Local1, Local2)
        And (Local0, Local1, Local2)
        If (CHK0)
        {
            Mod (Local0, Local1, Local2)
        }

        FindSetLeftBit (Local0, Local2)
        FindSetRightBit (Local0, Local2)
        XOr (Local0, Local1, Local2)
        NAnd (Local0, Local1, Local2)
        NOr (Local0, Local1, Local2)
        Not (Local0, Local2)
        Store (LNot (Local0), Local4)
        Store (LOr (Local0, Local1), Local4)
        Store (LAnd (Local0, Local1), Local4)
        Store (LEqual (Local0, Local1), Local4)
        Store (LGreater (Local0, Local1), Local4)
        Store (LGreaterEqual (Local0, Local1), Local4)
        Store (LLess (Local0, Local1), Local4)
        Store (LLessEqual (Local0, Local1), Local4)
        Store (LNotEqual (Local0, Local1), Local4)
    }

    Name (II31, 0xABCD0031)
    Name (II32, 0xABCD0032)
    Name (II33, 0xABCD0033)
    Name (II34, 0xABCD0034)
    Name (II35, 0xABCD0035)
    Name (II36, 0xABCD0036)
    Name (II37, 0xABCD0037)
    Name (II38, 0xABCD0038)
    Name (II39, 0xABCD0039)
    Name (II3A, 0xABCD003A)
    Name (II3B, 0xABCD003B)
    Name (II3C, 0xABCD003C)
    Name (II3D, 0xABCD003D)
    Name (II3E, 0xABCD003E)
    Name (II3F, 0xABCD003F)
    Name (II40, 0xABCD0040)
    Name (II41, 0xABCD0041)
    Name (II42, 0xABCD0042)
    Name (II43, 0xABCD0043)
    Name (II44, 0xABCD0044)
    Name (II45, 0xABCD0045)
    Name (II46, 0xABCD0046)
    Name (II47, 0xABCD0047)
    Method (IN51, 7, Serialized)
    {
        Name (TS, "in51")
        Name (I000, 0x00010000)
        Name (I001, 0x0A510010)
        Name (I002, 0x15210800)
        Name (I003, 0xFEABC8D9)
        Name (I004, 0x1234BCDE)
        Name (I005, 0xFE04BCDE)
        Name (I006, 0x12345678)
        Name (I007, 0x01000000)
        Name (I008, 0x60F5C7A2)
        Name (II00, 0xABCD0000)
        Name (II01, 0xABCD0001)
        Name (II02, 0xABCD0002)
        Name (II03, 0xABCD0003)
        Name (II04, 0xABCD0004)
        Name (II05, 0xABCD0005)
        Name (II06, 0xABCD0006)
        Name (II07, 0xABCD0007)
        Name (II08, 0xABCD0008)
        Name (II09, 0xABCD0009)
        Name (II0A, 0xABCD000A)
        Name (II0B, 0xABCD000B)
        Name (II0C, 0xABCD000C)
        Name (II0D, 0xABCD000D)
        Name (II0E, 0xABCD000E)
        Name (II0F, 0xABCD000F)
        Name (II10, 0xABCD0010)
        Name (II11, 0xABCD0011)
        Name (II12, 0xABCD0012)
        Name (II13, 0xABCD0013)
        Name (II14, 0xABCD0014)
        Name (II15, 0xABCD0015)
        Name (II16, 0xABCD0016)
        Name (II17, 0xABCD0017)
        Name (II18, 0xABCD0018)
        Name (II19, 0xABCD0019)
        Name (II1A, 0xABCD001A)
        Name (II1B, 0xABCD001B)
        Name (II1C, 0xABCD001C)
        Name (II1D, 0xABCD001D)
        Name (II1E, 0xABCD001E)
        Name (II1F, 0xABCD001F)
        Name (II20, 0xABCD0020)
        Name (II21, 0xABCD0021)
        Name (II22, 0xABCD0022)
        Name (II23, 0xABCD0023)
        Name (II24, 0xABCD0024)
        Name (II25, 0xABCD0025)
        Name (II26, 0xABCD0026)
        Name (II27, 0xABCD0027)
        Name (II28, 0xABCD0028)
        Name (II29, 0xABCD0029)
        Name (II2A, 0xABCD002A)
        Name (II2B, 0xABCD002B)
        Name (II2C, 0xABCD002C)
        Name (II2D, 0xABCD002D)
        Name (II2E, 0xABCD002E)
        Name (II2F, 0xABCD002F)
        Name (II30, 0xABCD0030)
        Add (Add (Add (Add (Add (Add (Add (Add (Add (Subtract (Or (And (
            Multiply (ShiftLeft (Divide (Add (Add (Add (Add (Increment (I000), Increment (I000), I000) /* \IN51.I000 */, Add (
            Increment (I000), Increment (I000), I000) /* \IN51.I000 */, Local0), Add (Add (Decrement (I000), Decrement (I000), I000) /* \IN51.I000 */, 
            Add (Decrement (I000), Decrement (I000), I000) /* \IN51.I000 */, Local1), Arg0), Add (Add (Increment (I000), Decrement (
            I000), I000) /* \IN51.I000 */, Add (Increment (I000), Decrement (I000), I000) /* \IN51.I000 */, Local2), Arg1), 0x11, II00, Local3), 
            0x03, II01) /* \IN51.II01 */, 0x02, I000) /* \IN51.I000 */, 0xFFFFFFFF, II0C) /* \IN51.II0C */, 0x20000000, II0D) /* \IN51.II0D */, Multiply (And (Add (Add (Add (
            XOr (Add (Add (Add (And (ShiftRight (Or (I001, 0x15210800, Local5), 0x03, II02) /* \IN51.II02 */, 0x035E2102, 
            Local6), Add (II0D, 0x07, II03) /* \IN51.II03 */, II04) /* \IN51.II04 */, FindSetLeftBit (0x7BCD0000, II05) /* \IN51.II05 */, Arg3), FindSetRightBit (0x7BCD0000, II06) /* \IN51.II06 */, 
            Arg4), 0x11B4937F, Arg5), NAnd (I003, 0xFFFFFFFF, II07) /* \IN51.II07 */, Arg6), NOr (I004, 0xF8F0F0F0, II08) /* \IN51.II08 */, Local7), 
            Not (I005, II09) /* \IN51.II09 */, II0A) /* \IN51.II0A */, 0xFFFFFFFF, II0B) /* \IN51.II0B */, And (Store (LNot (Store (LNot (II0B), II0E) /* \IN51.II0E */), 
            II0F) /* \IN51.II0F */, 0x01)), Local4), Store (LNot (Store (LNot (I006), II11) /* \IN51.II11 */), II12) /* \IN51.II12 */, II10) /* \IN51.II10 */, 
            Store (LOr (LNot (And (Store (LOr (I007, 0x00), II14) /* \IN51.II14 */, 0x01)), 0x00), II15) /* \IN51.II15 */, 
            II13) /* \IN51.II13 */, Store (LAnd (LNot (And (Store (LAnd (I007, 0x01), II16) /* \IN51.II16 */, 0x01)), 0x00), 
            II17) /* \IN51.II17 */, II18) /* \IN51.II18 */, Add (Store (LEqual (I008, 0x60F5C7A2), II19) /* \IN51.II19 */, Store (LEqual (I008, 0x60F5C7A0), II1A) /* \IN51.II1A */, 
            II1B) /* \IN51.II1B */, II1C) /* \IN51.II1C */, Add (Add (Store (LGreater (I008, 0x60F5C7A2), II1D) /* \IN51.II1D */, Store (LGreater (I008, 0x60F5C7A3), 
            II1E) /* \IN51.II1E */, II1F) /* \IN51.II1F */, Add (Store (LGreater (I008, 0x60F5C7A1), II20) /* \IN51.II20 */, Store (LGreater (I008, 0x60F5C7A0), II21) /* \IN51.II21 */, 
            II22) /* \IN51.II22 */, II23) /* \IN51.II23 */, II24) /* \IN51.II24 */, Add (Add (Store (LGreaterEqual (I008, 0x60F5C7A2), II25) /* \IN51.II25 */, Store (
            LGreaterEqual (I008, 0x60F5C7A3), II26) /* \IN51.II26 */, II27) /* \IN51.II27 */, Add (Store (LGreaterEqual (I008, 0x60F5C7A1), II28) /* \IN51.II28 */, Store (
            LGreaterEqual (I008, 0x60F5C7A0), II29) /* \IN51.II29 */, II2A) /* \IN51.II2A */, II2B) /* \IN51.II2B */, II2C) /* \IN51.II2C */, Add (Add (Store (LLess (I008, 
            0x60F5C7A2), II2D) /* \IN51.II2D */, Store (LLess (I008, 0x60F5C7A3), II2E) /* \IN51.II2E */, II2F) /* \IN51.II2F */, Add (Store (LLess (I008, 0x60F5C7A1), 
            II30) /* \IN51.II30 */, Store (LLess (I008, 0x60F5C7A0), II31) /* \II31 */, II32) /* \II32 */, II33) /* \II33 */, II34) /* \II34 */, Add (Add (Store (
            LLessEqual (I008, 0x60F5C7A2), II35) /* \II35 */, Store (LLessEqual (I008, 0x60F5C7A3), II36) /* \II36 */, II37) /* \II37 */, Add (Store (
            LLessEqual (I008, 0x60F5C7A1), II38) /* \II38 */, Store (LLessEqual (I008, 0x60F5C7A0), II39) /* \II39 */, II3A) /* \II3A */, II3B) /* \II3B */, 
            II3C) /* \II3C */, Add (Add (Store (LNotEqual (I008, 0x60F5C7A2), II3D) /* \II3D */, Store (LNotEqual (I008, 
            0x60F5C7A3), II3E) /* \II3E */, II3F) /* \II3F */, Add (Store (LNotEqual (I008, 0x60F5C7A1), II40) /* \II40 */, Store (LNotEqual (
            I008, 0x60F5C7A0), II41) /* \II41 */, II42) /* \II42 */, II43) /* \II43 */, II44) /* \II44 */
        If (LNotEqual (Local0, 0x0006000C))
        {
            ERR (TS, Z168, 0x0191, 0x00, 0x00, Local0, 0x0006000C)
        }

        If (LNotEqual (Local1, 0x0018002A))
        {
            ERR (TS, Z168, 0x0194, 0x00, 0x00, Local1, 0x0018002A)
        }

        If (LNotEqual (Local2, 0x006000A6))
        {
            ERR (TS, Z168, 0x0197, 0x00, 0x00, Local2, 0x006000A6)
        }

        If (LNotEqual (Arg0, 0x001E0036))
        {
            ERR (TS, Z168, 0x019A, 0x00, 0x00, Arg0, 0x001E0036)
        }

        If (LNotEqual (Arg1, 0x007E00DC))
        {
            ERR (TS, Z168, 0x019D, 0x00, 0x00, Arg1, 0x007E00DC)
        }

        If (LNotEqual (II00, 0x06))
        {
            ERR (TS, Z168, 0x01A0, 0x00, 0x00, II00, 0x06)
        }

        If (LNotEqual (Local3, 0x00076976))
        {
            ERR (TS, Z168, 0x01A3, 0x00, 0x00, Local3, 0x00076976)
        }

        If (LNotEqual (II01, 0x003B4BB0))
        {
            ERR (TS, Z168, 0x01A6, 0x00, 0x00, II01, 0x003B4BB0)
        }

        If (LNotEqual (Arg2, 0x00769760))
        {
            ERR (TS, Z168, 0x01A9, 0x00, 0x00, Arg2, 0x00769760)
        }

        If (LNotEqual (Local5, 0x1F710810))
        {
            ERR (TS, Z168, 0x01AC, 0x00, 0x00, Local5, 0x1F710810)
        }

        If (LNotEqual (II02, 0x03EE2102))
        {
            ERR (TS, Z168, 0x01AF, 0x00, 0x00, II02, 0x03EE2102)
        }

        If (LNotEqual (Local6, 0x034E2102))
        {
            ERR (TS, Z168, 0x01B2, 0x00, 0x00, Local6, 0x034E2102)
        }

        If (LNotEqual (II03, 0x07))
        {
            ERR (TS, Z168, 0x01B5, 0x00, 0x00, II03, 0x07)
        }

        If (LNotEqual (II04, 0x034E2109))
        {
            ERR (TS, Z168, 0x01B8, 0x00, 0x00, II04, 0x034E2109)
        }

        If (LNotEqual (II05, 0x1F))
        {
            ERR (TS, Z168, 0x01BB, 0x00, 0x00, II05, 0x1F)
        }

        If (LNotEqual (Arg3, 0x034E2128))
        {
            ERR (TS, Z168, 0x01BE, 0x00, 0x00, Arg3, 0x034E2128)
        }

        If (LNotEqual (II06, 0x11))
        {
            ERR (TS, Z168, 0x01C1, 0x00, 0x00, II06, 0x11)
        }

        If (LNotEqual (Arg4, 0x034E2139))
        {
            ERR (TS, Z168, 0x01C4, 0x00, 0x00, Arg4, 0x034E2139)
        }

        If (LNotEqual (Arg5, 0x12FAB246))
        {
            ERR (TS, Z168, 0x01C7, 0x00, 0x00, Arg5, 0x12FAB246)
        }

        If (LNotEqual (II07, 0xFFFFFFFF01543726))
        {
            ERR (TS, Z168, 0x01CA, 0x00, 0x00, II07, 0xFFFFFFFF01543726)
        }

        If (LNotEqual (Arg6, 0xFFFFFFFF144EE96C))
        {
            ERR (TS, Z168, 0x01CD, 0x00, 0x00, Arg6, 0xFFFFFFFF144EE96C)
        }

        If (LNotEqual (II08, 0xFFFFFFFF050B0301))
        {
            ERR (TS, Z168, 0x01D0, 0x00, 0x00, II08, 0xFFFFFFFF050B0301)
        }

        If (LNotEqual (Local7, 0xFFFFFFFE1959EC6D))
        {
            ERR (TS, Z168, 0x01D3, 0x00, 0x00, Local7, 0xFFFFFFFE1959EC6D)
        }

        If (LNotEqual (II09, 0xFFFFFFFF01FB4321))
        {
            ERR (TS, Z168, 0x01D6, 0x00, 0x00, II09, 0xFFFFFFFF01FB4321)
        }

        If (LNotEqual (II0A, 0xFFFFFFFD1B552F8E))
        {
            ERR (TS, Z168, 0x01D9, 0x00, 0x00, II0A, 0xFFFFFFFD1B552F8E)
        }

        If (LNotEqual (II0B, 0x1B552F8E))
        {
            ERR (TS, Z168, 0x01DC, 0x00, 0x00, II0B, 0x1B552F8E)
        }

        If (LNotEqual (II0C, 0x00769760))
        {
            ERR (TS, Z168, 0x01DF, 0x00, 0x00, II0C, 0x00769760)
        }

        If (LNotEqual (II0D, 0x20769760))
        {
            ERR (TS, Z168, 0x01E2, 0x00, 0x00, II0D, 0x20769760)
        }

        If (LNotEqual (II0E, 0x00))
        {
            ERR (TS, Z168, 0x01E5, 0x00, 0x00, II0E, 0x00)
        }

        If (LNotEqual (II0F, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x01E8, 0x00, 0x00, II0F, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (Local4, 0x052167D2))
        {
            ERR (TS, Z168, 0x01EB, 0x00, 0x00, Local4, 0x052167D2)
        }

        If (LNotEqual (II10, 0x052167D1))
        {
            ERR (TS, Z168, 0x01EE, 0x00, 0x00, II10, 0x052167D1)
        }

        If (LNotEqual (II11, 0x00))
        {
            ERR (TS, Z168, 0x01F1, 0x00, 0x00, II11, 0x00)
        }

        If (LNotEqual (II12, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x01F4, 0x00, 0x00, II12, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II13, 0x052167D1))
        {
            ERR (TS, Z168, 0x01F7, 0x00, 0x00, II13, 0x052167D1)
        }

        If (LNotEqual (II14, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x01FA, 0x00, 0x00, II14, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II15, 0x00))
        {
            ERR (TS, Z168, 0x01FD, 0x00, 0x00, II15, 0x00)
        }

        If (LNotEqual (II16, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x0200, 0x00, 0x00, II16, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II17, 0x00))
        {
            ERR (TS, Z168, 0x0203, 0x00, 0x00, II17, 0x00)
        }

        If (LNotEqual (II18, 0x052167D1))
        {
            ERR (TS, Z168, 0x0206, 0x00, 0x00, II18, 0x052167D1)
        }

        If (LNotEqual (II19, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x0209, 0x00, 0x00, II19, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II1A, 0x00))
        {
            ERR (TS, Z168, 0x020C, 0x00, 0x00, II1A, 0x00)
        }

        If (LNotEqual (II1B, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x020F, 0x00, 0x00, II1C, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II1C, 0x052167D0))
        {
            ERR (TS, Z168, 0x0212, 0x00, 0x00, II1D, 0x052167D0)
        }

        If (LNotEqual (II1D, 0x00))
        {
            ERR (TS, Z168, 0x0215, 0x00, 0x00, II1D, 0x00)
        }

        If (LNotEqual (II1E, 0x00))
        {
            ERR (TS, Z168, 0x0218, 0x00, 0x00, II1E, 0x00)
        }

        If (LNotEqual (II1F, 0x00))
        {
            ERR (TS, Z168, 0x021B, 0x00, 0x00, II1F, 0x00)
        }

        If (LNotEqual (II20, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x021E, 0x00, 0x00, II20, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II21, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x0221, 0x00, 0x00, II21, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II22, 0xFFFFFFFFFFFFFFFE))
        {
            ERR (TS, Z168, 0x0224, 0x00, 0x00, II22, 0xFFFFFFFFFFFFFFFE)
        }

        If (LNotEqual (II23, 0xFFFFFFFFFFFFFFFE))
        {
            ERR (TS, Z168, 0x0227, 0x00, 0x00, II23, 0xFFFFFFFFFFFFFFFE)
        }

        If (LNotEqual (II24, 0x052167CE))
        {
            ERR (TS, Z168, 0x022A, 0x00, 0x00, II24, 0x052167CE)
        }

        If (LNotEqual (II25, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x022D, 0x00, 0x00, II25, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II26, 0x00))
        {
            ERR (TS, Z168, 0x0230, 0x00, 0x00, II26, 0x00)
        }

        If (LNotEqual (II27, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x0233, 0x00, 0x00, II27, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II28, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x0236, 0x00, 0x00, II28, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II29, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x0239, 0x00, 0x00, II29, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II2A, 0xFFFFFFFFFFFFFFFE))
        {
            ERR (TS, Z168, 0x023C, 0x00, 0x00, II2A, 0xFFFFFFFFFFFFFFFE)
        }

        If (LNotEqual (II2B, 0xFFFFFFFFFFFFFFFD))
        {
            ERR (TS, Z168, 0x023F, 0x00, 0x00, II2B, 0xFFFFFFFFFFFFFFFD)
        }

        If (LNotEqual (II2C, 0x052167CB))
        {
            ERR (TS, Z168, 0x0242, 0x00, 0x00, II2C, 0x052167CB)
        }

        If (LNotEqual (II2D, 0x00))
        {
            ERR (TS, Z168, 0x0245, 0x00, 0x00, II2D, 0x00)
        }

        If (LNotEqual (II2E, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x0248, 0x00, 0x00, II2E, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II2F, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x024B, 0x00, 0x00, II2F, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II30, 0x00))
        {
            ERR (TS, Z168, 0x024E, 0x00, 0x00, II30, 0x00)
        }

        If (LNotEqual (II31, 0x00))
        {
            ERR (TS, Z168, 0x0251, 0x00, 0x00, II31, 0x00)
        }

        If (LNotEqual (II32, 0x00))
        {
            ERR (TS, Z168, 0x0254, 0x00, 0x00, II32, 0x00)
        }

        If (LNotEqual (II33, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x0257, 0x00, 0x00, II33, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II34, 0x052167CA))
        {
            ERR (TS, Z168, 0x025A, 0x00, 0x00, II34, 0x052167CA)
        }

        If (LNotEqual (II35, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x025D, 0x00, 0x00, II35, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II36, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x0260, 0x00, 0x00, II36, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II37, 0xFFFFFFFFFFFFFFFE))
        {
            ERR (TS, Z168, 0x0263, 0x00, 0x00, II37, 0xFFFFFFFFFFFFFFFE)
        }

        If (LNotEqual (II38, 0x00))
        {
            ERR (TS, Z168, 0x0266, 0x00, 0x00, II38, 0x00)
        }

        If (LNotEqual (II39, 0x00))
        {
            ERR (TS, Z168, 0x0269, 0x00, 0x00, II39, 0x00)
        }

        If (LNotEqual (II3A, 0x00))
        {
            ERR (TS, Z168, 0x026C, 0x00, 0x00, II3A, 0x00)
        }

        If (LNotEqual (II3B, 0xFFFFFFFFFFFFFFFE))
        {
            ERR (TS, Z168, 0x026F, 0x00, 0x00, II3B, 0xFFFFFFFFFFFFFFFE)
        }

        If (LNotEqual (II3C, 0x052167C8))
        {
            ERR (TS, Z168, 0x0272, 0x00, 0x00, II3C, 0x052167C8)
        }

        If (LNotEqual (II3D, 0x00))
        {
            ERR (TS, Z168, 0x0275, 0x00, 0x00, II3D, 0x00)
        }

        If (LNotEqual (II3E, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x0278, 0x00, 0x00, II3E, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II3F, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x027B, 0x00, 0x00, II3F, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II40, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x027E, 0x00, 0x00, II40, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II41, 0xFFFFFFFFFFFFFFFF))
        {
            ERR (TS, Z168, 0x0281, 0x00, 0x00, II41, 0xFFFFFFFFFFFFFFFF)
        }

        If (LNotEqual (II42, 0xFFFFFFFFFFFFFFFE))
        {
            ERR (TS, Z168, 0x0284, 0x00, 0x00, II42, 0xFFFFFFFFFFFFFFFE)
        }

        If (LNotEqual (II43, 0xFFFFFFFFFFFFFFFD))
        {
            ERR (TS, Z168, 0x0287, 0x00, 0x00, II43, 0xFFFFFFFFFFFFFFFD)
        }

        If (LNotEqual (II44, 0x052167C5))
        {
            ERR (TS, Z168, 0x028A, 0x00, 0x00, II44, 0x052167C5)
        }
    }

    Method (INI5, 0, NotSerialized)
    {
        SRMT ("in50")
        IN50 ()
        SRMT ("in51")
        IN51 (0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        CH03 ("ini5", Z168, 0x00, 0x0296, 0x00)
    }

    Name (Z174, 0xAE)
    Method (MD00, 0, Serialized)
    {
        Name (TS, "md00")
        Device (D000)
        {
            Name (I000, 0xABCD0000)
            Name (I001, 0x11111111)
        }

        Device (D001)
        {
            Name (I000, 0xABCD0001)
        }

        ThermalZone (TZ00)
        {
            Name (I000, 0xABCD0002)
            Name (I002, 0x22222222)
        }

        If (LNotEqual (D000.I000, 0xABCD0000))
        {
            ERR (TS, Z174, 0x32, 0x00, 0x00, D000.I000, 0xABCD0000)
        }

        CopyObject (D001, D000) /* \MD00.D000 */
        If (LNotEqual (D000.I000, 0xABCD0001))
        {
            ERR (TS, Z174, 0x37, 0x00, 0x00, D000.I000, 0xABCD0001)
        }

        CopyObject (TZ00, D000) /* \MD00.D000 */
        If (LNotEqual (D000.I000, 0xABCD0002))
        {
            ERR (TS, Z174, 0x3C, 0x00, 0x00, D000.I000, 0xABCD0002)
        }

        CH03 (TS, Z174, 0x03, 0x3F, 0x00)
        Store (D000.I001, Local0)
        CH04 (TS, 0x00, 0xFF, Z174, 0x41, 0x00, 0x00)
    }

    Method (MDFF, 0, NotSerialized)
    {
        SRMT ("md00")
        If (CHK0)
        {
            MD00 ()
        }
        Else
        {
            BLCK ()
        }
    }

    Method (MDFE, 0, NotSerialized)
    {
        SRMT ("dvf2")
        DVF2 ()
    }

    Name (Z100, 0x64)
    Method (M401, 1, Serialized)
    {
        Name (TS, "m401")
        Name (I000, 0x01)
        Name (I001, 0x00)
        Name (P000, Package (0x04)
        {
            0x01, 
            0x02, 
            0x03, 
            0x04
        })
        CH03 (TS, Z100, 0x00, 0x17, 0x00)
        Store (Arg0, I001) /* \M401.I001 */
        Method (MADD, 2, NotSerialized)
        {
            Add (Arg0, Arg1, Local0)
            Return (Local0)
        }

        Method (M001, 0, NotSerialized)
        {
            Method (M002, 0, NotSerialized)
            {
                Method (M003, 0, NotSerialized)
                {
                    Method (M004, 0, NotSerialized)
                    {
                        Method (M005, 0, NotSerialized)
                        {
                            Method (M006, 0, NotSerialized)
                            {
                                Method (M007, 0, NotSerialized)
                                {
                                    Return (0x00)
                                }

                                Store (0x07000000, I000) /* \M401.I000 */
                                Return (MADD (I000, M007 ()))
                            }

                            Store (0x00600000, I000) /* \M401.I000 */
                            Return (MADD (I000, M006 ()))
                        }

                        Store (0x00050000, I000) /* \M401.I000 */
                        Return (MADD (I000, M005 ()))
                    }

                    Store (0x4000, I000) /* \M401.I000 */
                    Return (MADD (I000, M004 ()))
                }

                Store (0x0300, I000) /* \M401.I000 */
                Return (MADD (I000, M003 ()))
            }

            Store (0x20, I000) /* \M401.I000 */
            Return (MADD (I000, M002 ()))
        }

        Store (MADD (I000, M001 ()), Local0)
        If (LNotEqual (Local0, 0x07654321))
        {
            ERR (TS, Z100, 0x4A, 0x00, 0x00, Local0, 0x07654321)
        }

        If (LNotEqual (I000, 0x07000000))
        {
            ERR (TS, Z100, 0x4E, 0x00, 0x00, I000, 0x07000000)
        }

        CH03 (TS, Z100, 0x03, 0x51, 0x00)
    }

    Method (N004, 0, NotSerialized)
    {
        SRMT ("m401-0")
        M401 (0x00)
    }

    Name (Z101, 0x65)
    Method (M600, 0, Serialized)
    {
        Name (TS, "m600")
        Name (I000, 0xABCD0000)
        Method (M000, 1, NotSerialized)
        {
            Store (0x11223344, I000) /* \M600.I000 */
            If (LNotEqual (Arg0, 0xABCD0000))
            {
                ERR (TS, Z101, 0x1D, 0x00, 0x00, Arg0, 0xABCD0000)
            }
        }

        M000 (I000)
        If (LNotEqual (I000, 0x11223344))
        {
            ERR (TS, Z101, 0x24, 0x00, 0x00, I000, 0x11223344)
        }
    }

    Method (N006, 0, NotSerialized)
    {
        SRMT ("m600")
        M600 ()
    }

    Name (Z162, 0xA2)
    Method (MS00, 0, Serialized)
    {
        Name (TS, "ms00")
        Name (IAD1, 0x01)
        Name (IAD2, 0x10)
        Name (IAD3, 0x0100)
        Name (IAD4, 0x1000)
        Name (IAD5, 0x00010000)
        Name (IAD6, 0x00100000)
        Name (IAD7, 0x01000000)
        Method (MAD1, 1, NotSerialized)
        {
            Return (Arg0)
        }

        Method (MAD7, 7, NotSerialized)
        {
            Return (Add (Add (Add (Add (Add (Add (Arg0, Arg1), Arg2), 
                Arg3), Arg4), Arg5), Arg6))
        }

        Method (M000, 0, NotSerialized)
        {
            Store (MAD7 (MAD1 (IAD1), MAD1 (IAD2), MAD1 (IAD3), MAD1 (IAD4), MAD1 (IAD5), 
                MAD1 (IAD6), MAD7 (MAD1 (IAD1), MAD1 (IAD2), MAD1 (IAD3), MAD1 (IAD4), MAD1 (IAD5), 
                MAD1 (IAD6), MAD7 (MAD1 (IAD1), MAD1 (IAD2), MAD1 (IAD3), MAD1 (IAD4), MAD1 (IAD5), 
                MAD1 (IAD6), MAD7 (MAD1 (IAD1), MAD1 (IAD2), MAD1 (IAD3), MAD1 (IAD4), MAD1 (IAD5), 
                MAD1 (IAD6), MAD7 (MAD1 (IAD1), MAD1 (IAD2), MAD1 (IAD3), MAD1 (IAD4), MAD1 (IAD5), 
                MAD1 (IAD6), MAD7 (MAD1 (IAD1), MAD1 (IAD2), MAD1 (IAD3), MAD1 (IAD4), MAD1 (IAD5), 
                MAD1 (IAD6), MAD7 (MAD1 (IAD1), MAD1 (IAD2), MAD1 (IAD3), MAD1 (IAD4), MAD1 (IAD5), 
                MAD1 (IAD6), MAD1 (IAD7)))))))), Local0)
            Store (Local0, Debug)
            If (LNotEqual (Local0, 0x01777777))
            {
                ERR (TS, Z162, 0x45, 0x00, 0x00, Local0, 0x01777777)
            }
        }

        CH03 (TS, Z162, 0x01, 0x49, 0x00)
        M000 ()
        CH03 (TS, Z162, 0x02, 0x4B, 0x00)
    }

    Method (MS01, 1, Serialized)
    {
        Name (TS, "ms01")
        Name (I000, 0x00)
        Name (B000, Buffer (0x09)
        {
            /* 0000 */  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,  // ........
            /* 0008 */  0x18                                             // .
        })
        CreateField (B000, 0x00, 0x08, BF00)
        Name (TP00, 0x00)
        Method (M000, 1, NotSerialized)
        {
            Store (ObjectType (Arg0), Local0)
            If (LNotEqual (Local0, TP00))
            {
                ERR (TS, Z162, 0x5E, 0x00, 0x00, Local0, TP00)
            }
        }

        Store (C009, TP00) /* \MS01.TP00 */
        Store (C00B, TP00) /* \MS01.TP00 */
        Store (ObjectType (BF00), Local0)
        If (LNotEqual (Local0, C016))
        {
            ERR (TS, Z162, 0x6B, 0x00, 0x00, Local0, C016)
        }

        M000 (BF00)
        Store (BF00, I000) /* \MS01.I000 */
        Store (ObjectType (I000), Local0)
        If (LNotEqual (Local0, C009))
        {
            ERR (TS, Z162, 0x73, 0x00, 0x00, Local0, C009)
        }

        Store (BF00, Local1)
        Store (ObjectType (Local1), Local0)
        If (LNotEqual (Local0, TP00))
        {
            ERR (TS, Z162, 0x79, 0x00, 0x00, Local0, TP00)
        }

        Store (BF00, Arg0)
        Store (ObjectType (Arg0), Local0)
        If (LNotEqual (Local0, TP00))
        {
            ERR (TS, Z162, 0x7F, 0x00, 0x00, Local0, TP00)
        }
    }

    Method (MS02, 1, Serialized)
    {
        Name (TS, "ms02")
        Name (I000, 0x00)
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   8
        }

        Name (TP00, 0x00)
        Method (M000, 1, NotSerialized)
        {
            Store (ObjectType (Arg0), Local0)
            If (LNotEqual (Local0, TP00))
            {
                ERR (TS, Z162, 0x93, 0x00, 0x00, Local0, TP00)
            }
        }

        Store (C009, TP00) /* \MS02.TP00 */
        Store (ObjectType (F000), Local0)
        If (LNotEqual (Local0, C00D))
        {
            ERR (TS, Z162, 0x9B, 0x00, 0x00, Local0, C00D)
        }

        M000 (F000)
        Store (F000, I000) /* \MS02.I000 */
        Store (ObjectType (I000), Local0)
        If (LNotEqual (Local0, C009))
        {
            ERR (TS, Z162, 0xA3, 0x00, 0x00, Local0, C009)
        }

        Store (F000, Local1)
        Store (ObjectType (Local1), Local0)
        If (LNotEqual (Local0, TP00))
        {
            ERR (TS, Z162, 0xA9, 0x00, 0x00, Local0, TP00)
        }

        Store (F000, Arg0)
        Store (ObjectType (Arg0), Local0)
        If (LNotEqual (Local0, TP00))
        {
            ERR (TS, Z162, 0xAF, 0x00, 0x00, Local0, TP00)
        }
    }

    Method (MS03, 0, Serialized)
    {
        Name (I000, 0x11000000)
        Name (I001, 0x00220000)
        Name (P000, Package (0x03)
        {
            0xABCD0000, 
            0xABCD0001, 
            0xABCD0002
        })
        Method (M000, 0, NotSerialized)
        {
            Return (P000) /* \MS03.P000 */
        }

        Method (M001, 1, NotSerialized)
        {
            Return (0xABCD0003)
        }

        Method (M002, 2, NotSerialized)
        {
            Index (Arg0, 0x01, Local0)
            Store (DerefOf (Local0), Local1)
            If (LNotEqual (Local1, 0xABCD0001))
            {
                ERR ("ms03", Z162, 0xCE, 0x00, 0x00, Local0, C00D)
            }
        }

        M002 (P000, 0xABCD0004)
        M002 (M000 (), 0xABCD0004)
        M002 (P000, M001 (Add (I000, I001)))
        M002 (M000 (), M001 (Add (I000, I001)))
    }

    Method (MSFF, 0, NotSerialized)
    {
        SRMT ("ms00")
        If (Y262)
        {
            MS00 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("ms01")
        MS01 (0x00)
        SRMT ("ms02")
        MS02 (0x00)
        SRMT ("ms03")
        If (Y275)
        {
            MS03 ()
        }
        Else
        {
            BLCK ()
        }
    }

    Name (Z179, 0xB3)
    Method (RSTO, 2, NotSerialized)
    {
        Store (Arg0, Arg1)
    }

    Method (DSTO, 2, NotSerialized)
    {
        Store (DerefOf (Arg0), Arg1)
    }

    Method (MS10, 1, Serialized)
    {
        Name (TS, "ms10")
        Method (M063, 2, NotSerialized)
        {
            OUTP ("Bug 63: Add(\"0x1111\", 0, Local0) should return 0?")
            OUTP ("Addend1:")
            OUTP (Arg0)
            Add (Arg0, 0x00, Local0)
            OUTP ("Result (Local0):")
            OUTP (Local0)
            If (LNotEqual (Arg1, Local0))
            {
                ERR (TS, Z179, 0x6F, 0x00, 0x00, Local0, Arg1)
            }
        }

        Method (N063, 3, Serialized)
        {
            Name (INT0, 0xFFFF)
            OUTP ("Bug 63upd: Implicit conversion \"0x1111\" to Integer should return 0?")
            OUTP ("String:")
            OUTP (Arg0)
            Store (Arg0, INT0) /* \MS10.N063.INT0 */
            OUTP ("Result (INT0):")
            OUTP (INT0)
            If (LAnd (ABUU, LNot (Q004)))
            {
                If (LNotEqual (Arg2, INT0))
                {
                    ERR (TS, Z179, 0x84, 0x00, 0x00, INT0, Arg2)
                }
            }
            ElseIf (LNotEqual (Arg1, INT0))
            {
                ERR (TS, Z179, 0x88, 0x00, 0x00, INT0, Arg1)
            }
        }

        Method (M000, 0, NotSerialized)
        {
            If (ABUU){}
            Else
            {
                M063 ("0", 0x00)
                M063 ("0x", 0x00)
                M063 ("0x1111", 0x00)
            }

            M063 (0x01, 0x01)
            N063 ("0", 0x00, 0x30)
            N063 ("0x", 0x00, 0x7830)
            N063 ("0x1111", 0x00, 0x31317830)
            N063 ("0x111111111", 0x00, 0x31317830)
        }

        CH03 (TS, Z179, 0x02, 0x9D, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                M063 ("0", 0x00)
            }
            Case (0x02)
            {
                M063 ("0x", 0x00)
            }
            Case (0x03)
            {
                M063 ("0x1111", 0x00)
            }
            Case (0x04)
            {
                M063 (0x01, 0x01)
            }
            Case (0x05)
            {
                N063 ("0", 0x00, 0x30)
            }
            Case (0x06)
            {
                N063 ("0x", 0x00, 0x7830)
            }
            Case (0x07)
            {
                N063 ("0x1111", 0x00, 0x31317830)
            }
            Case (0x08)
            {
                N063 ("0x111111111", 0x00, 0x31317830)
            }

        }

        CH03 (TS, Z179, 0x03, 0xAC, 0x00)
    }

    Method (A063, 0, NotSerialized)
    {
        IIN0 ()
        MS10 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B063, 0, NotSerialized)
    {
        IIN0 ()
        MS10 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (C063, 0, NotSerialized)
    {
        IIN0 ()
        MS10 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (D063, 0, NotSerialized)
    {
        IIN0 ()
        MS10 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (E063, 0, NotSerialized)
    {
        IIN0 ()
        MS10 (0x05)
        Return (POUT) /* \POUT */
    }

    Method (F063, 0, NotSerialized)
    {
        IIN0 ()
        MS10 (0x06)
        Return (POUT) /* \POUT */
    }

    Method (G063, 0, NotSerialized)
    {
        IIN0 ()
        MS10 (0x07)
        Return (POUT) /* \POUT */
    }

    Method (H063, 0, NotSerialized)
    {
        IIN0 ()
        MS10 (0x08)
        Return (POUT) /* \POUT */
    }

    Method (MS11, 1, Serialized)
    {
        Name (TS, "ms11")
        Method (M083, 1, Serialized)
        {
            Name (I000, 0x89ABCDEF)
            OUTP ("Bug 83: Derefof of non-Ref. (f.e. Integer) should produce exception")
            OUTP ("Name(i000, 0x89abcdef)")
            If (Arg0)
            {
                Store (DerefOf (I000), Local0)
                CH04 (TS, 0x00, 0xFF, Z179, 0xCC, 0x00, 0x00)
            }
            Else
            {
                Store (DerefOf (RefOf (I000)), Local0)
                CH03 (TS, Z179, 0x05, 0xCF, 0x00)
            }
        }

        Method (N083, 1, Serialized)
        {
            Name (I000, 0x89ABCDEF)
            OUTP ("Bug 83upd: Derefof of non-Ref. (f.e. Integer) should produce exception")
            If (Arg0)
            {
                Store (0x89ABCDEF, Local0)
                OUTP ("Store(0x89abcdef, Local0)")
            }
            Else
            {
                Store (RefOf (I000), Local0)
                OUTP ("Store(Refof(i000), Local0)")
            }

            Store (DerefOf (Local0), Local1)
            If (Arg0)
            {
                CH04 (TS, 0x00, 0xFF, Z179, 0xE2, 0x00, 0x00)
            }
            Else
            {
                CH03 (TS, Z179, 0x07, 0xE4, 0x00)
            }
        }

        Method (M000, 0, NotSerialized)
        {
            M083 (0x00)
            If (ABUU){}
            Else
            {
                M083 (0x01)
            }

            N083 (0x00)
            If (ABUU){}
            Else
            {
                N083 (0x01)
            }
        }

        CH03 (TS, Z179, 0x08, 0xF6, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                M083 (0x00)
            }
            Case (0x02)
            {
                M083 (0x01)
            }
            Case (0x03)
            {
                N083 (0x00)
            }
            Case (0x04)
            {
                N083 (0x01)
            }

        }

        CH03 (TS, Z179, 0x09, 0x0100, 0x00)
    }

    Method (A083, 0, NotSerialized)
    {
        IIN0 ()
        MS11 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B083, 0, NotSerialized)
    {
        IIN0 ()
        MS11 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (X083, 0, NotSerialized)
    {
        IIN0 ()
        MS11 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (D083, 0, NotSerialized)
    {
        IIN0 ()
        MS11 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (MS12, 0, Serialized)
    {
        Name (TS, "ms12")
        Method (M100, 0, NotSerialized)
        {
            Method (M000, 0, NotSerialized)
            {
                Return (0x00)
            }

            Method (M001, 0, Serialized)
            {
                M000 ()
                Device (D000)
                {
                }

                Name (I000, 0x00ABCDEF)
                OUTP ("Finish of test")
            }

            OUTP ("Bug 100 (fixed for 20050526): some combination of operators aborts execution")
            M001 ()
        }

        CH03 (TS, Z179, 0x0A, 0x0128, 0x00)
        M100 ()
        CH03 (TS, Z179, 0x0B, 0x012A, 0x00)
    }

    Method (A100, 0, NotSerialized)
    {
        IIN0 ()
        MS12 ()
        Return (POUT) /* \POUT */
    }

    Method (MS13, 1, Serialized)
    {
        Name (TS, "ms13")
        Name (P001, Package (0x05)
        {
            0x10, 
            0x11, 
            0x12, 
            0x13, 
            0x14
        })
        Name (P002, Package (0x05)
        {
            0x20, 
            0x21, 
            0x22, 
            0x23, 
            0x24
        })
        Name (P003, Package (0x05)
        {
            0x30, 
            0x31, 
            0x32, 
            0x33, 
            0x34
        })
        Name (P004, Package (0x05)
        {
            0x40, 
            0x41, 
            0x42, 
            0x43, 
            0x44
        })
        Name (P005, Package (0x05)
        {
            0x50, 
            0x51, 
            0x52, 
            0x53, 
            0x54
        })
        Method (A113, 0, NotSerialized)
        {
            Method (M000, 2, NotSerialized)
            {
                Store (DerefOf (Arg0), Local0)
                If (CH03 (TS, Z179, 0x0C, 0x0145, 0x00)){}
                ElseIf (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0147, 0x00, 0x00, Local0, Arg1)
                }
            }

            OUTP ("Bug 113: immediate Indexed Ref. as parameters of Methods are unexpectedly dereferenced 1")
            M000 (Index (P001, 0x00), 0x10)
        }

        Method (B113, 0, NotSerialized)
        {
            Method (M000, 2, NotSerialized)
            {
                Store (DerefOf (Arg0), Local0)
                If (CH03 (TS, Z179, 0x0E, 0x0155, 0x00)){}
                ElseIf (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0157, 0x00, 0x00, Local0, Arg1)
                }
            }

            OUTP ("Bug 113: immediate Indexed Ref. as parameters of Methods are unexpectedly dereferenced 2")
            Store (Index (P001, 0x00), Local0)
            M000 (Local0, 0x10)
        }

        Method (S113, 0, NotSerialized)
        {
            Method (M000, 6, NotSerialized)
            {
                OUTP (DerefOf (Arg0))
                CH03 (TS, Z179, 0x12, 0x0167, 0x00)
                OUTP (DerefOf (Arg1))
                CH03 (TS, Z179, 0x13, 0x0169, 0x00)
                OUTP (DerefOf (Arg2))
                CH03 (TS, Z179, 0x14, 0x016B, 0x00)
                OUTP (DerefOf (Arg3))
                CH03 (TS, Z179, 0x15, 0x016D, 0x00)
                OUTP (DerefOf (Arg4))
                CH03 (TS, Z179, 0x16, 0x016F, 0x00)
                OUTP (DerefOf (Arg5))
                CH03 (TS, Z179, 0x17, 0x0171, 0x00)
            }

            OUTP ("Bug 113 MS: immediate Indexed Ref. as parameters of Methods can be dereferenced 3")
            Store (Index (P002, 0x01), Local0)
            Index (P004, 0x03, Local1)
            Store (Index (P005, 0x04, Local2), Local3)
            M000 (Index (P001, 0x00), Local0, Index (P003, 0x02, Local4), Local1, Local2, 
                Local3)
            OUTP (DerefOf (Local4))
        }

        CH03 (TS, Z179, 0x18, 0x0181, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                A113 ()
                B113 ()
                S113 ()
            }
            Case (0x01)
            {
                A113 ()
            }
            Case (0x02)
            {
                B113 ()
            }
            Case (0x03)
            {
                S113 ()
            }

        }

        CH03 (TS, Z179, 0x19, 0x0188, 0x00)
    }

    Method (A113, 0, NotSerialized)
    {
        IIN0 ()
        MS13 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B113, 0, NotSerialized)
    {
        IIN0 ()
        MS13 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (C113, 0, NotSerialized)
    {
        IIN0 ()
        MS13 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (MS14, 1, Serialized)
    {
        Name (TS, "ms14")
        Method (M114, 1, NotSerialized)
        {
            Method (M000, 1, Serialized)
            {
                Name (I001, 0x00)
                Name (B001, Buffer (0x05)
                {
                     0x0A, 0x02, 0x03, 0x04, 0x05                     // .....
                })
                Method (M001, 0, NotSerialized)
                {
                    Increment (I001)
                    Return (Buffer (0x05)
                    {
                         0x0A, 0x02, 0x03, 0x04, 0x05                     // .....
                    })
                }

                Method (M002, 0, NotSerialized)
                {
                    Increment (I001)
                    Return (Package (0x05)
                    {
                        0x0A, 
                        0x02, 
                        0x03, 
                        0x04, 
                        0x05
                    })
                }

                If (LEqual (Arg0, 0x00))
                {
                    OUTP ("Start of test: Method returns (Buffer(){10,2,3,4,5})")
                    OUTP ("Index(m001, 0, Local0)")
                    Index (M001 (), 0x00, Local0)
                    If (LAnd (ABUU, LNot (Q005))){}
                    ElseIf (LNot (I001))
                    {
                        ERR (TS, Z179, 0x01B3, 0x00, 0x00, I001, 0x00)
                    }
                }
                ElseIf (LEqual (Arg0, 0x01))
                {
                    OUTP ("Start of test: Method returns (Package(){10,2,3,4,5})")
                    OUTP ("Index(m001, 0, Local0)")
                    Index (M001 (), 0x00, Local0)
                    If (LAnd (ABUU, LNot (Q005))){}
                    ElseIf (LNot (I001))
                    {
                        ERR (TS, Z179, 0x01BB, 0x00, 0x00, I001, 0x00)
                    }
                }
                ElseIf (LEqual (Arg0, 0x02))
                {
                    OUTP ("Start of test: Name(b001, Buffer(){10,2,3,4,5})")
                    OUTP ("Index(b001, 0, Local0)")
                    Index (B001, 0x00, Local0)
                    OUTP (I001)
                    Store (DerefOf (Local0), Local1)
                    OUTP (Local1)
                }

                OUTP ("Finish of test")
            }

            OUTP ("Bug 114: Method object as a Source of Index operation")
            M000 (Arg0)
        }

        Method (M000, 0, NotSerialized)
        {
            M114 (0x00)
            M114 (0x01)
            M114 (0x02)
        }

        CH03 (TS, Z179, 0x1E, 0x01D4, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                M114 (0x00)
            }
            Case (0x02)
            {
                M114 (0x01)
            }
            Case (0x03)
            {
                M114 (0x02)
            }

        }

        CH03 (TS, Z179, 0x1F, 0x01DB, 0x00)
    }

    Method (A114, 0, NotSerialized)
    {
        IIN0 ()
        MS14 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B114, 0, NotSerialized)
    {
        IIN0 ()
        MS14 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (C114, 0, NotSerialized)
    {
        IIN0 ()
        MS14 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (MS15, 1, Serialized)
    {
        Name (TS, "ms15")
        Name (P001, Package (0x01)
        {
            0x10
        })
        Name (P002, Package (0x01)
        {
            0x20
        })
        Name (P003, Package (0x01)
        {
            0x30
        })
        Name (P004, Package (0x01)
        {
            0x40
        })
        Name (P005, Package (0x01)
        {
            0x50
        })
        Name (P006, Package (0x01)
        {
            0x60
        })
        Method (M001, 0, NotSerialized)
        {
            Return (Index (P001, 0x00))
        }

        Method (M002, 0, NotSerialized)
        {
            Store (Index (P002, 0x00), Local0)
            Return (Local0)
        }

        Method (M003, 0, NotSerialized)
        {
            Return (Index (P003, 0x00, Local0))
        }

        Method (M004, 0, NotSerialized)
        {
            Index (P004, 0x00, Local0)
            Return (Local0)
        }

        Method (M005, 0, NotSerialized)
        {
            Store (Index (P005, 0x00, Local0), Local1)
            Return (Local1)
        }

        Method (M006, 0, NotSerialized)
        {
            Store (Index (P006, 0x00, Local0), Local1)
            Return (Local0)
        }

        Method (A115, 0, NotSerialized)
        {
            Method (M000, 2, NotSerialized)
            {
                Store (DerefOf (Arg0), Local0)
                If (CH03 (TS, Z179, 0x20, 0x0205, 0x00)){}
                ElseIf (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0207, 0x00, 0x00, Local0, Arg1)
                }
            }

            OUTP ("Bug 115: immediately returned Indexed Ref. as parameters of Methods are unexpectedly dereferenced 1")
            M000 (M001 (), 0x10)
        }

        Method (B115, 0, NotSerialized)
        {
            Method (M000, 2, NotSerialized)
            {
                Store (DerefOf (Arg0), Local0)
                If (CH03 (TS, Z179, 0x22, 0x0216, 0x00)){}
                ElseIf (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0218, 0x00, 0x00, Local0, Arg1)
                }
            }

            OUTP ("Bug 115: immediately returned Indexed Ref. as parameters of Methods are unexpectedly dereferenced 2")
            M000 (M002 (), 0x20)
        }

        Method (C115, 0, NotSerialized)
        {
            Method (M000, 2, NotSerialized)
            {
                Store (DerefOf (Arg0), Local0)
                If (CH03 (TS, Z179, 0x24, 0x0227, 0x00)){}
                ElseIf (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0229, 0x00, 0x00, Local0, Arg1)
                }
            }

            OUTP ("Bug 115: immediately returned Indexed Ref. as parameters of Methods are unexpectedly dereferenced 3")
            M000 (M003 (), 0x30)
        }

        Method (D115, 0, NotSerialized)
        {
            Method (M000, 2, NotSerialized)
            {
                Store (DerefOf (Arg0), Local0)
                If (CH03 (TS, Z179, 0x26, 0x0238, 0x00)){}
                ElseIf (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x023A, 0x00, 0x00, Local0, Arg1)
                }
            }

            OUTP ("Bug 115: immediately returned Indexed Ref. as parameters of Methods are unexpectedly dereferenced 4")
            M000 (M004 (), 0x40)
        }

        Method (E115, 0, NotSerialized)
        {
            Method (M000, 2, NotSerialized)
            {
                Store (DerefOf (Arg0), Local0)
                If (CH03 (TS, Z179, 0x28, 0x0249, 0x00)){}
                ElseIf (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x024B, 0x00, 0x00, Local0, Arg1)
                }
            }

            OUTP ("Bug 115: immediately returned Indexed Ref. as parameters of Methods are unexpectedly dereferenced 5")
            M000 (M005 (), 0x50)
        }

        Method (F115, 0, NotSerialized)
        {
            Method (M000, 2, NotSerialized)
            {
                Store (DerefOf (Arg0), Local0)
                If (CH03 (TS, Z179, 0x2A, 0x025A, 0x00)){}
                ElseIf (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x025C, 0x00, 0x00, Local0, Arg1)
                }
            }

            OUTP ("Bug 115: immediately returned Indexed Ref. as parameters of Methods are unexpectedly dereferenced 6")
            M000 (M006 (), 0x60)
        }

        CH03 (TS, Z179, 0x2C, 0x0265, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                A115 ()
                B115 ()
                C115 ()
                D115 ()
                E115 ()
                F115 ()
            }
            Case (0x01)
            {
                A115 ()
            }
            Case (0x02)
            {
                B115 ()
            }
            Case (0x03)
            {
                C115 ()
            }
            Case (0x04)
            {
                D115 ()
            }
            Case (0x05)
            {
                E115 ()
            }
            Case (0x06)
            {
                F115 ()
            }

        }

        CH03 (TS, Z179, 0x2D, 0x026F, 0x00)
    }

    Method (A115, 0, NotSerialized)
    {
        IIN0 ()
        MS15 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B115, 0, NotSerialized)
    {
        IIN0 ()
        MS15 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (C115, 0, NotSerialized)
    {
        IIN0 ()
        MS15 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (D115, 0, NotSerialized)
    {
        IIN0 ()
        MS15 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (E115, 0, NotSerialized)
    {
        IIN0 ()
        MS15 (0x05)
        Return (POUT) /* \POUT */
    }

    Method (F115, 0, NotSerialized)
    {
        IIN0 ()
        MS15 (0x06)
        Return (POUT) /* \POUT */
    }

    Method (MS16, 1, Serialized)
    {
        Name (TS, "ms16")
        Method (A118, 0, Serialized)
        {
            Name (P90D, Package (0x01)
            {
                0xD650A284
            })
            Method (M000, 0, NotSerialized)
            {
                OUTP ("Test m000 started")
                Store (Index (P90D, 0x00), Local0)
                Store (DerefOf (Local0), Local1)
                Store (ObjectType (Local1), Local2)
                If (LNotEqual (Local2, 0x01))
                {
                    ERR (TS, Z179, 0x0291, 0x00, 0x00, Local2, 0x01)
                    If (LEqual (Local2, 0x02))
                    {
                        OUTP (Local1)
                    }
                    Else
                    {
                        OUTP (Local2)
                    }
                }
                Else
                {
                    OUTP (Local1)
                    If (LNotEqual (Local1, 0xD650A284))
                    {
                        ERR (TS, Z179, 0x029A, 0x00, 0x00, Local1, 0xD650A284)
                    }
                    Else
                    {
                        OUTP ("Ok")
                    }
                }

                OUTP ("Test m000 finished")
            }

            OUTP ("Bug 118: Integer data as an element of Package")
            M000 ()
        }

        Method (B118, 0, Serialized)
        {
            Name (I900, 0xD650A284)
            Name (P90D, Package (0x01)
            {
                I900, 
            })
            Method (M000, 0, NotSerialized)
            {
                OUTP ("Test m000 started")
                Store (Index (P90D, 0x00), Local0)
                Store (DerefOf (Local0), Local1)
                Store (ObjectType (Local1), Local2)
                If (LAnd (ABUU, LNot (Q006)))
                {
                    If (LNotEqual (Local2, 0x02))
                    {
                        ERR (TS, Z179, 0x02B9, 0x00, 0x00, Local2, 0x02)
                    }
                }
                ElseIf (LNotEqual (Local2, 0x01))
                {
                    ERR (TS, Z179, 0x02BC, 0x00, 0x00, Local2, 0x01)
                }
                Else
                {
                    OUTP (Local1)
                    If (LNotEqual (Local1, 0xD650A284))
                    {
                        ERR (TS, Z179, 0x02C0, 0x00, 0x00, Local1, 0xD650A284)
                    }
                    Else
                    {
                        OUTP ("Ok")
                    }
                }

                OUTP ("Test m000 finished")
            }

            OUTP ("Bug 118: Named Integer Object reference in Package")
            M000 ()
        }

        Method (C118, 0, Serialized)
        {
            Name (B900, Buffer (0x09)
            {
                /* 0000 */  0x0A, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,  // ........
                /* 0008 */  0x09                                             // .
            })
            CreateField (B900, 0x00, 0x08, BF90)
            Name (P915, Package (0x01)
            {
                BF90, 
            })
            Method (M001, 0, NotSerialized)
            {
                OUTP ("Test m001 started")
                Store (Index (P915, 0x00), Local0)
                Store (DerefOf (Local0), Local1)
                Store (ObjectType (Local1), Local2)
                If (LAnd (ABUU, LNot (Q006)))
                {
                    If (LNotEqual (Local2, 0x02))
                    {
                        ERR (TS, Z179, 0x02E1, 0x00, 0x00, Local2, 0x02)
                    }
                }
                ElseIf (LNotEqual (Local2, 0x03))
                {
                    ERR (TS, Z179, 0x02E4, 0x00, 0x00, Local2, 0x03)
                }
                ElseIf (Y118)
                {
                    OUTP (Local1)
                    If (LNotEqual (Local1, 0x0A))
                    {
                        ERR (TS, Z179, 0x02E8, 0x00, 0x00, Local1, 0x0A)
                    }
                    Else
                    {
                        OUTP ("Ok")
                    }
                }

                OUTP ("Test m001 finished")
            }

            OUTP ("Bug 118: Named Buffer Field Object reference in Package")
            M001 ()
        }

        Method (D118, 0, Serialized)
        {
            Name (B900, Buffer (0x09)
            {
                /* 0000 */  0x0A, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,  // ........
                /* 0008 */  0x09                                             // .
            })
            CreateField (B900, 0x00, 0x08, BF90)
            Method (M001, 0, NotSerialized)
            {
                OUTP ("Test m001 started: Store bf90 to Local1")
                Store (BF90, Local1)
                Store (ObjectType (Local1), Local2)
                If (LAnd (ABUU, LNot (Q007)))
                {
                    If (LNotEqual (Local2, 0x03))
                    {
                        ERR (TS, Z179, 0x0306, 0x00, 0x00, Local2, 0x03)
                    }
                }
                ElseIf (LNotEqual (Local2, 0x03))
                {
                    ERR (TS, Z179, 0x0309, 0x00, 0x00, Local2, 0x03)
                }
                Else
                {
                    OUTP (Local1)
                    If (LNotEqual (Local1, Buffer (0x01)
                                {
                                     0x0A                                             // .
                                }))
                    {
                        ERR (TS, Z179, 0x030D, 0x00, 0x00, Local1, Buffer (0x01)
                            {
                                 0x0A                                             // .
                            })
                    }
                    Else
                    {
                        OUTP ("Ok")
                    }
                }

                OUTP ("Test m001 finished")
            }

            OUTP ("Bug 118 issue: Fields are immediately resolved to integers/buffers.")
            M001 ()
        }

        Method (E118, 0, Serialized)
        {
            Name (B900, Buffer (0x09)
            {
                /* 0000 */  0x0A, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,  // ........
                /* 0008 */  0x09                                             // .
            })
            CreateField (B900, 0x00, 0x08, BF90)
            Method (M001, 0, NotSerialized)
            {
                OUTP ("Test m001 started: Store DerefOf(Refof(bf90)) to Local1")
                Store (RefOf (BF90), Local0)
                Store (DerefOf (Local0), Local1)
                Store (ObjectType (Local1), Local2)
                If (LAnd (ABUU, LNot (Q007)))
                {
                    If (LNotEqual (Local2, 0x03))
                    {
                        ERR (TS, Z179, 0x032C, 0x00, 0x00, Local2, 0x03)
                    }
                }
                ElseIf (LNotEqual (Local2, 0x03))
                {
                    ERR (TS, Z179, 0x032F, 0x00, 0x00, Local2, 0x03)
                }
                Else
                {
                    OUTP (Local1)
                    If (LNotEqual (Local1, Buffer (0x01)
                                {
                                     0x0A                                             // .
                                }))
                    {
                        ERR (TS, Z179, 0x0333, 0x00, 0x00, Local1, Buffer (0x01)
                            {
                                 0x0A                                             // .
                            })
                    }
                    Else
                    {
                        OUTP ("Ok")
                    }
                }

                OUTP ("Test m001 finished")
            }

            OUTP ("Bug 118 issue: Fields are immediately resolved to integers/buffers.")
            M001 ()
        }

        Method (F118, 0, Serialized)
        {
            Name (B900, Buffer (0x09)
            {
                /* 0000 */  0x0A, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,  // ........
                /* 0008 */  0x09                                             // .
            })
            CreateField (B900, 0x00, 0x08, BF90)
            Name (P915, Package (0x01){})
            Method (M001, 0, NotSerialized)
            {
                Method (M000, 1, NotSerialized)
                {
                    Return (Arg0)
                }

                OUTP ("Test m001 started: Store DerefOf(Refof(bf90)) to Named Package")
                Store (RefOf (BF90), Local0)
                Store (DerefOf (Local0), P915) /* \MS16.F118.P915 */
                Store (ObjectType (P915), Local2)
                If (LNotEqual (Local2, 0x01))
                {
                    ERR (TS, Z179, 0x0355, 0x00, 0x00, Local2, 0x01)
                }
                Else
                {
                    OUTP (P915)
                    If (LNotEqual (M000 (P915), 0x0A))
                    {
                        ERR (TS, Z179, 0x0359, 0x00, 0x00, P915, 0x0A)
                    }
                    Else
                    {
                        OUTP ("Ok")
                    }
                }

                OUTP ("Test m001 finished")
            }

            OUTP ("Bug 118 issue: Fields are immediately resolved to integers/buffers.")
            M001 ()
        }

        Method (G118, 0, Serialized)
        {
            Name (I900, 0xD650A284)
            Name (P90D, Package (0x01)
            {
                I900, 
            })
            Method (M000, 0, NotSerialized)
            {
                OUTP ("Test m000 started")
                Store (Index (P90D, 0x00), Local0)
                Store (DerefOf (Local0), Local1)
                Store (ObjectType (Local1), Local2)
                If (LAnd (ABUU, LNot (Q006)))
                {
                    If (LNotEqual (Local2, 0x02))
                    {
                        ERR (TS, Z179, 0x0378, 0x00, 0x00, Local2, 0x02)
                    }
                }
                ElseIf (LNotEqual (Local2, 0x01))
                {
                    ERR (TS, Z179, 0x037B, 0x00, 0x00, Local2, 0x01)
                }
                Else
                {
                    OUTP (Local1)
                    If (LNotEqual (Local1, 0xD650A284))
                    {
                        ERR (TS, Z179, 0x037F, 0x00, 0x00, Local1, 0xD650A284)
                    }
                    Else
                    {
                        OUTP ("Ok")
                    }
                }

                OUTP ("Test m000 finished")
            }

            OUTP ("Bug 118: DerefOf Named Integer Object reference in Package")
            M000 ()
        }

        Method (M000, 0, NotSerialized)
        {
            A118 ()
            B118 ()
            C118 ()
            D118 ()
            E118 ()
            If (ABUU){}
            Else
            {
                F118 ()
            }

            G118 ()
        }

        CH03 (TS, Z179, 0x3C, 0x039B, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                A118 ()
            }
            Case (0x02)
            {
                B118 ()
            }
            Case (0x03)
            {
                C118 ()
            }
            Case (0x04)
            {
                D118 ()
            }
            Case (0x05)
            {
                E118 ()
            }
            Case (0x06)
            {
                F118 ()
            }
            Case (0x07)
            {
                G118 ()
            }

        }

        CH03 (TS, Z179, 0x3D, 0x03A6, 0x00)
    }

    Method (A118, 0, NotSerialized)
    {
        IIN0 ()
        MS16 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B118, 0, NotSerialized)
    {
        IIN0 ()
        MS16 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (C118, 0, NotSerialized)
    {
        IIN0 ()
        MS16 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (D118, 0, NotSerialized)
    {
        IIN0 ()
        MS16 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (E118, 0, NotSerialized)
    {
        IIN0 ()
        MS16 (0x05)
        Return (POUT) /* \POUT */
    }

    Method (F118, 0, NotSerialized)
    {
        IIN0 ()
        MS16 (0x06)
        Return (POUT) /* \POUT */
    }

    Method (G118, 0, NotSerialized)
    {
        IIN0 ()
        MS16 (0x07)
        Return (POUT) /* \POUT */
    }

    Method (MS17, 1, Serialized)
    {
        Name (TS, "ms17")
        Method (M126, 1, Serialized)
        {
            Method (M000, 1, Serialized)
            {
                Name (I001, 0x00)
                OUTP ("m000 started, apply DerefOf()")
                Store (DerefOf (Arg0), Local0)
                Add (Local0, 0x01, Local6)
                CH03 (TS, Z179, 0x3E, 0x03C5, 0x00)
                OUTP (Local6)
                Store (DerefOf (Arg0), I001) /* \MS17.M126.M000.I001 */
                OUTP (I001)
                Add (I001, 0x01, Local7)
                CH03 (TS, Z179, 0x3F, 0x03CB, 0x00)
                OUTP (Local7)
                If (LNotEqual (Local6, Local7))
                {
                    ERR (TS, Z179, 0x03CF, 0x00, 0x00, Local6, Local7)
                }

                OUTP ("m000 finished")
            }

            Method (M001, 1, Serialized)
            {
                Name (I001, 0x00)
                OUTP ("m001 started, DON\'T apply DerefOf()")
                Store (Arg0, Local0)
                OUTP ("Before Add")
                Add (Local0, 0x01, Local6)
                CH03 (TS, Z179, 0x41, 0x03DF, 0x00)
                OUTP ("After Add")
                OUTP (Local6)
                OUTP ("sit 1")
                Store (Arg0, I001) /* \MS17.M126.M001.I001 */
                CH03 (TS, Z179, 0x42, 0x03E6, 0x00)
                OUTP (I001)
                Add (I001, 0x01, Local7)
                CH03 (TS, Z179, 0x43, 0x03E9, 0x00)
                If (LNotEqual (Local6, Local7))
                {
                    ERR (TS, Z179, 0x03EB, 0x00, 0x00, Local6, Local7)
                }

                OUTP ("m001 finished")
            }

            Method (M002, 1, NotSerialized)
            {
                OUTP ("m002 started, immediate Arg")
                OUTP ("Before Add")
                Add (Arg0, 0x01, Local7)
                CH03 (TS, Z179, 0x45, 0x03F7, 0x00)
                OUTP ("After Add")
                If (LNotEqual (0x08, Local7))
                {
                    ERR (TS, Z179, 0x03FA, 0x00, 0x00, Local7, 0x08)
                }

                OUTP ("m002 finished")
            }

            Method (M003, 1, NotSerialized)
            {
                OUTP ("m003 started, apply DerefOf(Arg)")
                OUTP ("Before Add")
                Add (DerefOf (Arg0), 0x01, Local7)
                CH03 (TS, Z179, 0x47, 0x0406, 0x00)
                OUTP ("After Add")
                If (LNotEqual (0x08, Local7))
                {
                    ERR (TS, Z179, 0x0409, 0x00, 0x00, Local7, 0x08)
                }

                OUTP ("m003 finished")
            }

            Name (I000, 0x07)
            Name (I001, 0x07)
            Name (I002, 0x07)
            Name (I003, 0x07)
            OUTP ("Bug 126: automatic dereference on reading issue")
            If (LEqual (Arg0, 0x00))
            {
                M000 (RefOf (I000))
            }
            ElseIf (LEqual (Arg0, 0x01))
            {
                M001 (RefOf (I001))
            }
            ElseIf (LEqual (Arg0, 0x02))
            {
                M002 (RefOf (I002))
            }
            ElseIf (LEqual (Arg0, 0x03))
            {
                M003 (RefOf (I003))
            }
        }

        Method (M000, 0, NotSerialized)
        {
            M126 (0x00)
            If (ABUU){}
            Else
            {
                M126 (0x01)
                M126 (0x02)
            }

            M126 (0x03)
        }

        CH03 (TS, Z179, 0x49, 0x042C, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                M126 (0x00)
            }
            Case (0x02)
            {
                M126 (0x01)
            }
            Case (0x03)
            {
                M126 (0x02)
            }
            Case (0x04)
            {
                M126 (0x03)
            }

        }

        CH03 (TS, Z179, 0x4A, 0x0434, 0x00)
    }

    Method (A126, 0, NotSerialized)
    {
        IIN0 ()
        MS17 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B126, 0, NotSerialized)
    {
        IIN0 ()
        MS17 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (C126, 0, NotSerialized)
    {
        IIN0 ()
        MS17 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (D126, 0, NotSerialized)
    {
        IIN0 ()
        MS17 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (MS18, 0, Serialized)
    {
        Name (TS, "ms18")
        Method (M127, 0, Serialized)
        {
            Name (P000, Package (0x02)
            {
                0x01, 
                0x02
            })
            OUTP ("Bug 127: CopyObject unexpectedly performs dereference")
            OUTP ("Store(Index(p000, 0, Local0), Local1):")
            Store (Index (P000, 0x00, Local0), Local1)
            Store (DerefOf (Local0), Local4)
            CH03 (TS, Z179, 0x4B, 0x0452, 0x00)
            Store (DerefOf (Local1), Local4)
            CH03 (TS, Z179, 0x4C, 0x0455, 0x00)
            OUTP ("CopyObject(Index(p000, 0, Local2), Local3):")
            CopyObject (Index (P000, 0x00, Local2), Local3)
            Store (DerefOf (Local2), Local4)
            CH03 (TS, Z179, 0x4D, 0x045C, 0x00)
            Store (DerefOf (Local3), Local4)
            CH03 (TS, Z179, 0x4E, 0x045F, 0x00)
        }

        CH03 (TS, Z179, 0x4F, 0x0462, 0x00)
        M127 ()
        CH03 (TS, Z179, 0x50, 0x0464, 0x00)
    }

    Method (A127, 0, NotSerialized)
    {
        IIN0 ()
        MS18 ()
        Return (POUT) /* \POUT */
    }

    Method (MS19, 1, Serialized)
    {
        Name (TS, "ms19")
        Method (A128, 0, Serialized)
        {
            Name (I000, 0x1234)
            OUTP ("Bug 128:")
            OUTP ("a128 started: Store Object_Reference to LocalX (No exception, Ok)")
            Store (RefOf (I000), Local0)
            Store (DerefOf (Local0), Local1)
            If (LNotEqual (Local1, 0x1234))
            {
                ERR (TS, Z179, 0x0481, 0x00, 0x00, Local1, 0x1234)
            }

            OUTP ("a128 finished")
        }

        Method (B128, 0, Serialized)
        {
            Name (I000, 0x1234)
            Name (REF0, 0x00)
            OUTP ("Bug 128:")
            OUTP ("b128 started: Store Object_Reference to NamedX (Exception, Ok)")
            Store (RefOf (I000), REF0) /* \MS19.B128.REF0 */
            CH04 (TS, 0x00, 0xFF, Z179, 0x0492, 0x00, 0x00)
            OUTP ("b128 finished")
        }

        Method (C128, 0, Serialized)
        {
            Name (I000, 0x1234)
            Name (REF0, 0x00)
            OUTP ("Bug 128:")
            OUTP ("c128 started: CopyObject Object_Reference to NamedX (Exception, Bug)")
            CopyObject (RefOf (I000), REF0) /* \MS19.C128.REF0 */
            If (CH04 (TS, 0x00, 0xFF, Z179, 0x04A2, 0x00, 0x00))
            {
                Return (Zero)
            }

            Store (DerefOf (REF0), Local1)
            If (LNotEqual (Local1, 0x1234))
            {
                ERR (TS, Z179, 0x04AD, 0x00, 0x00, Local1, 0x1234)
            }

            OUTP ("c128 finished")
        }

        Method (D128, 0, Serialized)
        {
            Name (I000, 0x1234)
            Name (P000, Package (0x01){})
            OUTP ("Bug 128:")
            OUTP ("d128 started: Store Object_Reference to uninit Package element (No exception, Ok)")
            Store (RefOf (I000), Index (P000, 0x00))
            Store (DerefOf (DerefOf (Index (P000, 0x00))), Local1)
            If (LNotEqual (Local1, 0x1234))
            {
                ERR (TS, Z179, 0x04C2, 0x00, 0x00, Local1, 0x1234)
            }

            OUTP ("d128 finished")
        }

        Method (E128, 0, Serialized)
        {
            Name (I000, 0x1234)
            Name (P000, Package (0x01)
            {
                0x5678
            })
            OUTP ("Bug 128:")
            OUTP ("d128 started: Store Object_Reference to init Package element (No exception, Ok)")
            Store (RefOf (I000), Index (P000, 0x00))
            Store (DerefOf (DerefOf (Index (P000, 0x00))), Local1)
            If (LNotEqual (Local1, 0x1234))
            {
                ERR (TS, Z179, 0x04D7, 0x00, 0x00, Local1, 0x1234)
            }

            OUTP ("d128 finished")
        }

        Method (M000, 0, NotSerialized)
        {
            A128 ()
            If (ABUU){}
            Else
            {
                B128 ()
            }

            If (ABUU){}
            Else
            {
                C128 ()
            }

            If (ABUU){}
            Else
            {
                D128 ()
            }

            If (ABUU){}
            Else
            {
                E128 ()
            }
        }

        CH03 (TS, Z179, 0x57, 0x04F8, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                A128 ()
            }
            Case (0x02)
            {
                B128 ()
            }
            Case (0x03)
            {
                C128 ()
            }
            Case (0x04)
            {
                D128 ()
            }
            Case (0x05)
            {
                E128 ()
            }

        }

        CH03 (TS, Z179, 0x58, 0x0501, 0x00)
    }

    Method (A128, 0, NotSerialized)
    {
        IIN0 ()
        MS19 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B128, 0, NotSerialized)
    {
        IIN0 ()
        MS19 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (C128, 0, NotSerialized)
    {
        IIN0 ()
        MS19 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (D128, 0, NotSerialized)
    {
        IIN0 ()
        MS19 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (E128, 0, NotSerialized)
    {
        IIN0 ()
        MS19 (0x05)
        Return (POUT) /* \POUT */
    }

    Method (MS1A, 1, Serialized)
    {
        Name (TS, "ms1a")
        Method (A131, 0, Serialized)
        {
            Name (I000, 0x77)
            Name (I001, 0x00)
            Method (M000, 0, NotSerialized)
            {
                Increment (I001)
                Return (RefOf (I000))
            }

            Method (M001, 0, NotSerialized)
            {
                Increment (I001)
                Store (RefOf (I000), Local0)
                Return (Local0)
            }

            OUTP ("Case return (RefOf(i000))")
            If (LEqual (I001, 0x00))
            {
                ERR (TS, Z179, 0x052E, 0x00, 0x00, I001, 0x00)
            }
            ElseIf (LNotEqual (I000, 0x05))
            {
                ERR (TS, Z179, 0x0530, 0x00, 0x00, I000, 0x05)
            }
            Else
            {
                OUTP ("Ok a131")
            }
        }

        Method (B131, 0, Serialized)
        {
            Name (I000, 0x77)
            Name (I001, 0x00)
            Method (M000, 0, NotSerialized)
            {
                Increment (I001)
                Return (RefOf (I000))
            }

            Method (M001, 0, NotSerialized)
            {
                Increment (I001)
                Store (RefOf (I000), Local0)
                Return (Local0)
            }

            OUTP ("Case return (Local0) (= RefOf(i000))")
            If (LEqual (I001, 0x00))
            {
                ERR (TS, Z179, 0x0551, 0x00, 0x00, I001, 0x00)
            }
            ElseIf (LNotEqual (I000, 0x15))
            {
                ERR (TS, Z179, 0x0553, 0x00, 0x00, I000, 0x15)
            }
            Else
            {
                OUTP ("Ok b131")
            }
        }

        Method (C131, 0, Serialized)
        {
            Name (I000, 0x77)
            Name (I001, 0x00)
            Method (M000, 0, NotSerialized)
            {
                Increment (I001)
                Return (RefOf (I000))
            }

            Method (M001, 0, NotSerialized)
            {
                Increment (I001)
                Store (RefOf (I000), Local0)
                Return (Local0)
            }

            Store (RefOf (Local0), Local1)
            OUTP ("Case Store(return (RefOf(i000)), Local0)")
            Store (M000 (), Local0)
            Store (0x25, DerefOf (Local1))
            If (LEqual (I001, 0x00))
            {
                ERR (TS, Z179, 0x0574, 0x00, 0x00, I001, 0x00)
            }
            ElseIf (LNotEqual (I000, 0x25))
            {
                ERR (TS, Z179, 0x0576, 0x00, 0x00, I000, 0x25)
            }
            Else
            {
                OUTP ("Ok c131")
            }
        }

        Method (D131, 0, Serialized)
        {
            Name (I000, 0x77)
            Name (I001, 0x00)
            Method (M000, 0, NotSerialized)
            {
                Increment (I001)
                Return (RefOf (I000))
            }

            Method (M001, 0, NotSerialized)
            {
                Increment (I001)
                Store (RefOf (I000), Local0)
                Return (Local0)
            }

            OUTP ("Case - test tools proper work indication")
            RSTO (0x35, M000 ())
            If (LEqual (I001, 0x00))
            {
                ERR (TS, Z179, 0x0593, 0x00, 0x00, I001, 0x00)
            }
            ElseIf (LNotEqual (I000, 0x35))
            {
                ERR (TS, Z179, 0x0595, 0x00, 0x00, I000, 0x35)
            }
            Else
            {
                OUTP ("Ok d131")
            }
        }

        Method (E131, 0, Serialized)
        {
            Name (I000, 0x77)
            Name (I001, 0x00)
            Method (M000, 0, NotSerialized)
            {
                Increment (I001)
                Return (RefOf (I000))
            }

            OUTP ("Case Store(return (RefOf(i000)), Local0), step 1")
            Store (M000 (), Local0)
            If (LEqual (I001, 0x00))
            {
                ERR (TS, Z179, 0x05AB, 0x00, 0x00, I001, 0x00)
            }
            Else
            {
                OUTP ("Ok e131")
            }
        }

        Method (M000, 0, NotSerialized)
        {
            If (ABUU){}
            Else
            {
                A131 ()
            }

            If (ABUU){}
            Else
            {
                B131 ()
            }

            If (ABUU){}
            Else
            {
                C131 ()
            }

            D131 ()
            E131 ()
        }

        OUTP ("Bug 131: Writing to the reference immediately returned by Method")
        CH03 (TS, Z179, 0x62, 0x05C8, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                A131 ()
            }
            Case (0x02)
            {
                B131 ()
            }
            Case (0x03)
            {
                C131 ()
            }
            Case (0x04)
            {
                D131 ()
            }
            Case (0x05)
            {
                E131 ()
            }

        }

        CH03 (TS, Z179, 0x63, 0x05D1, 0x00)
    }

    Method (A131, 0, NotSerialized)
    {
        IIN0 ()
        MS1A (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B131, 0, NotSerialized)
    {
        IIN0 ()
        MS1A (0x02)
        Return (POUT) /* \POUT */
    }

    Method (C131, 0, NotSerialized)
    {
        IIN0 ()
        MS1A (0x03)
        Return (POUT) /* \POUT */
    }

    Method (D131, 0, NotSerialized)
    {
        IIN0 ()
        MS1A (0x04)
        Return (POUT) /* \POUT */
    }

    Method (E131, 0, NotSerialized)
    {
        IIN0 ()
        MS1A (0x04)
        Return (POUT) /* \POUT */
    }

    Method (MS1B, 1, Serialized)
    {
        Name (TS, "ms1b")
        Method (M132, 2, Serialized)
        {
            Name (P000, Package (0x01)
            {
                0x77
            })
            Method (M000, 2, NotSerialized)
            {
                OUTP ("m000 started")
                If (Arg1)
                {
                    Add (DerefOf (Arg0), 0x01, Local7)
                }
                Else
                {
                    Add (Arg0, 0x01, Local7)
                }

                CH03 (TS, Z179, 0x64, 0x05F2, 0x00)
                OUTP ("After Add")
                If (LNotEqual (Local7, 0x78))
                {
                    ERR (TS, Z179, 0x05F7, 0x00, 0x00, Local7, 0x78)
                }
                Else
                {
                    OUTP ("Ok 0")
                }

                OUTP (Local7)
                If (Arg1)
                {
                    OUTP ("Accessed with DerefOf properly!")
                }
                Else
                {
                    OUTP ("Accessed without DerefOf properly!")
                }
            }

            OUTP ("Bug 132: read access \"Automatic dereference\" for Index Reference")
            If (Arg0)
            {
                OUTP ("Transfer Index reference by LocalX:")
                Index (P000, 0x00, Local0)
                M000 (Local0, Arg1)
            }
            Else
            {
                OUTP ("Specify Index reference immediately:")
                M000 (Index (P000, 0x00), Arg1)
            }
        }

        Method (M000, 0, NotSerialized)
        {
            If (ABUU){}
            Else
            {
                M132 (0x00, 0x00)
            }

            If (ABUU){}
            Else
            {
                M132 (0x01, 0x00)
            }

            M132 (0x00, 0x01)
            M132 (0x01, 0x01)
        }

        CH03 (TS, Z179, 0x66, 0x0620, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                M132 (0x00, 0x00)
            }
            Case (0x02)
            {
                M132 (0x01, 0x00)
            }
            Case (0x03)
            {
                M132 (0x00, 0x01)
            }
            Case (0x04)
            {
                M132 (0x01, 0x01)
            }

        }

        CH03 (TS, Z179, 0x67, 0x0628, 0x00)
    }

    Method (A132, 0, NotSerialized)
    {
        IIN0 ()
        MS1B (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B132, 0, NotSerialized)
    {
        IIN0 ()
        MS1B (0x02)
        Return (POUT) /* \POUT */
    }

    Method (C132, 0, NotSerialized)
    {
        IIN0 ()
        MS1B (0x03)
        Return (POUT) /* \POUT */
    }

    Method (D132, 0, NotSerialized)
    {
        IIN0 ()
        MS1B (0x04)
        Return (POUT) /* \POUT */
    }

    Method (MS1C, 1, Serialized)
    {
        Name (TS, "ms1c")
        Method (M133, 1, Serialized)
        {
            Name (I000, 0x00)
            Name (S000, "q_er0000")
            Name (B000, Buffer (0x04)
            {
                 0x01, 0x00, 0x03, 0x04                           // ....
            })
            Name (P000, Package (0x03)
            {
                0x05, 
                0x00, 
                0x07
            })
            Method (M000, 1, NotSerialized)
            {
                Store (0x77, Arg0)
            }

            OUTP ("Bug 133: WRITE access to the initial object by reference in ArgX")
            If (LEqual (Arg0, 0x00))
            {
                OUTP ("Writing by RefOf reference to Integer")
                Store (RefOf (I000), Local0)
                M000 (Local0)
                If (LNotEqual (I000, 0x77))
                {
                    ERR (TS, Z179, 0x064E, 0x00, 0x00, I000, 0x77)
                }
                Else
                {
                    OUTP ("Ok 0")
                }

                OUTP (I000)
            }
            ElseIf (LEqual (Arg0, 0x01))
            {
                OUTP ("Writing by Index to String")
                Index (S000, 0x01, Local0)
                M000 (Local0)
                Store (DerefOf (Local0), Local1)
                If (LNotEqual (Local1, 0x77))
                {
                    ERR (TS, Z179, 0x065B, 0x00, 0x00, Local1, 0x77)
                }
                Else
                {
                    OUTP ("Ok 1")
                }

                OUTP (S000)
            }
            ElseIf (LEqual (Arg0, 0x02))
            {
                OUTP ("Writing by Index to Buffer")
                Index (B000, 0x01, Local0)
                M000 (Local0)
                Store (DerefOf (Local0), Local1)
                If (LNotEqual (Local1, 0x77))
                {
                    ERR (TS, Z179, 0x0669, 0x00, 0x00, Local1, 0x77)
                }
                Else
                {
                    OUTP ("Ok 2")
                }

                OUTP (B000)
            }
            ElseIf (LEqual (Arg0, 0x03))
            {
                OUTP ("Check Index of Package")
                Index (P000, 0x01, Local0)
                Store (DerefOf (Local0), Local1)
                If (LNotEqual (Local1, 0x00))
                {
                    ERR (TS, Z179, 0x0676, 0x00, 0x00, Local1, 0x00)
                }
                Else
                {
                    OUTP ("Ok 3")
                }

                OUTP (Local1)
            }
            ElseIf (LEqual (Arg0, 0x04))
            {
                OUTP ("Writing by Index to Package")
                Index (P000, 0x01, Local0)
                M000 (Local0)
                Store (DerefOf (Local0), Local1)
                If (LNotEqual (Local1, 0x77))
                {
                    ERR (TS, Z179, 0x0685, 0x00, 0x00, Local1, 0x77)
                }
                Else
                {
                    OUTP ("Ok 4")
                }

                OUTP (Local1)
            }
        }

        Method (M000, 0, NotSerialized)
        {
            M133 (0x00)
            If (ABUU){}
            Else
            {
                M133 (0x01)
            }

            M133 (0x02)
            M133 (0x03)
            M133 (0x04)
        }

        CH03 (TS, Z179, 0x6D, 0x069B, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                M133 (0x00)
            }
            Case (0x02)
            {
                M133 (0x01)
            }
            Case (0x03)
            {
                M133 (0x02)
            }
            Case (0x04)
            {
                M133 (0x03)
            }
            Case (0x05)
            {
                M133 (0x04)
            }

        }

        CH03 (TS, Z179, 0x6E, 0x06A4, 0x00)
    }

    Method (A133, 0, NotSerialized)
    {
        IIN0 ()
        MS1C (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B133, 0, NotSerialized)
    {
        IIN0 ()
        MS1C (0x02)
        Return (POUT) /* \POUT */
    }

    Method (C133, 0, NotSerialized)
    {
        IIN0 ()
        MS1C (0x03)
        Return (POUT) /* \POUT */
    }

    Method (D133, 0, NotSerialized)
    {
        IIN0 ()
        MS1C (0x04)
        Return (POUT) /* \POUT */
    }

    Method (E133, 0, NotSerialized)
    {
        IIN0 ()
        MS1C (0x05)
        Return (POUT) /* \POUT */
    }

    Method (MS1D, 1, Serialized)
    {
        Name (TS, "ms1d")
        Method (M134, 1, Serialized)
        {
            Name (I000, 0x11)
            Name (I001, 0x22)
            Name (I002, 0x33)
            Name (I003, 0x44)
            Name (I004, 0x55)
            Name (I005, 0x66)
            Name (I006, 0x77)
            Method (M000, 7, NotSerialized)
            {
                OUTP ("LocalX case of Method started:")
                Store (RefOf (I000), Local0)
                Store (Local0, Local1)
                Store (Local1, Local2)
                Store (Local2, Local3)
                Store (Local3, Local4)
                Store (Local4, Local5)
                Store (Local5, Local6)
                Store (0x88, Local6)
                If (LAnd (ABUU, LNot (Q008)))
                {
                    If (LNotEqual (I000, 0x88))
                    {
                        ERR (TS, Z179, 0x06D1, 0x00, 0x00, I000, 0x88)
                    }
                }
                ElseIf (LNotEqual (I000, 0x11))
                {
                    ERR (TS, Z179, 0x06D4, 0x00, 0x00, I000, 0x11)
                }
                Else
                {
                    If (LNotEqual (Local6, 0x88))
                    {
                        ERR (TS, Z179, 0x06D7, 0x00, 0x00, Local6, 0x88)
                    }
                    Else
                    {
                        OUTP ("Ok 0:")
                    }

                    OUTP (Local6)
                }

                OUTP ("LocalX case of Method finished")
            }

            Method (M001, 7, NotSerialized)
            {
                OUTP ("ArgX case of Method started:")
                Store (RefOf (I000), Arg0)
                Store (Arg0, Arg1)
                Store (Arg1, Arg2)
                Store (Arg2, Arg3)
                Store (Arg3, Arg4)
                Store (Arg4, Arg5)
                Store (Arg5, Arg6)
                Store (0x88, Arg6)
                If (LAnd (ABUU, LNot (Q008)))
                {
                    If (LNotEqual (I000, 0x88))
                    {
                        ERR (TS, Z179, 0x06F1, 0x00, 0x00, I000, 0x88)
                    }
                }
                ElseIf (LNotEqual (I000, 0x11))
                {
                    ERR (TS, Z179, 0x06F4, 0x00, 0x00, I000, 0x11)
                }
                Else
                {
                    If (LNotEqual (Arg6, 0x88))
                    {
                        ERR (TS, Z179, 0x06F7, 0x00, 0x00, Arg6, 0x88)
                    }
                    Else
                    {
                        OUTP ("Ok 1:")
                    }

                    OUTP (Arg6)
                }

                OUTP ("ArgX case of Method finished")
            }

            Method (M002, 7, NotSerialized)
            {
                OUTP ("references in ArgX case of Method started:")
                Store (RefOf (I000), Arg0)
                Store (Arg0, Arg1)
                Store (Arg1, Arg2)
                Store (Arg2, Arg3)
                Store (Arg3, Arg4)
                Store (Arg4, Arg5)
                Store (Arg5, Arg6)
                Store (0x88, Arg6)
                If (LAnd (ABUU, LNot (Q008)))
                {
                    If (LNotEqual (I000, 0x88))
                    {
                        ERR (TS, Z179, 0x0711, 0x00, 0x00, I000, 0x88)
                    }
                }
                ElseIf (LNotEqual (I000, 0x11))
                {
                    ERR (TS, Z179, 0x0714, 0x00, 0x00, I000, 0x11)
                    OUTP (I000)
                }
                Else
                {
                    Store (DerefOf (Arg6), Local1)
                    If (LNotEqual (Local1, 0x88))
                    {
                        ERR (TS, Z179, 0x0719, 0x00, 0x00, Local1, 0x88)
                    }
                    Else
                    {
                        OUTP ("Ok 1:")
                    }

                    OUTP (Arg6)
                }

                OUTP ("ArgX case of Method finished")
            }

            OUTP ("Bug 134: ArgX term effectively becomes a LocalX term")
            If (LEqual (Arg0, 0x00))
            {
                M000 (I000, I001, I002, I003, I004, I005, I006)
            }
            ElseIf (LEqual (Arg0, 0x01))
            {
                M001 (I000, I001, I002, I003, I004, I005, I006)
            }
            ElseIf (LEqual (Arg0, 0x02))
            {
                M002 (RefOf (Local0), RefOf (Local1), RefOf (Local2), RefOf (Local3), RefOf (Local4), RefOf (
                    Local5), RefOf (Local6))
            }
        }

        Method (M000, 0, NotSerialized)
        {
            M134 (0x00)
            M134 (0x01)
            M134 (0x02)
        }

        CH03 (TS, Z179, 0x75, 0x0736, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                M134 (0x00)
            }
            Case (0x02)
            {
                M134 (0x01)
            }
            Case (0x03)
            {
                M134 (0x02)
            }

        }

        CH03 (TS, Z179, 0x76, 0x073D, 0x00)
    }

    Method (A134, 0, NotSerialized)
    {
        IIN0 ()
        MS1D (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B134, 0, NotSerialized)
    {
        IIN0 ()
        MS1D (0x02)
        Return (POUT) /* \POUT */
    }

    Method (C134, 0, NotSerialized)
    {
        IIN0 ()
        MS1D (0x03)
        Return (POUT) /* \POUT */
    }

    Method (MS1E, 0, Serialized)
    {
        Name (TS, "ms1e")
        Method (M136, 0, Serialized)
        {
            Name (B000, Buffer (0x01)
            {
                 0x3C                                             // <
            })
            Name (B001, Buffer (0x03)
            {
                 0x01, 0x02, 0x03                                 // ...
            })
            OUTP ("Bug 136: CopyObject does not perform an implicit store")
            CopyObject (B000, B001) /* \MS1E.M136.B001 */
            If (LEqual (B000, B001))
            {
                OUTP ("Ok")
            }
            Else
            {
                ERR (TS, Z179, 0x075A, 0x00, 0x00, B000, B001)
            }

            OUTP (B000)
            OUTP (B001)
        }

        CH03 (TS, Z179, 0x78, 0x0760, 0x00)
        M136 ()
        CH03 (TS, Z179, 0x79, 0x0762, 0x00)
    }

    Method (A136, 0, NotSerialized)
    {
        IIN0 ()
        MS1E ()
        Return (POUT) /* \POUT */
    }

    Method (MS1F, 1, Serialized)
    {
        Name (TS, "ms1f")
        Name (I999, 0x00)
        Name (PREF, Package (0x04)
        {
            0xA5A5A5A5, 
            I999, , 
            I999, 
        })
        Method (MLRP, 2, NotSerialized)
        {
            Store (ObjectType (Arg0), Local0)
            Store (Arg0, Index (PREF, Arg1))
            CH03 (TS, Z179, 0x7A, 0x0778, 0x00)
            Store (ObjectType (Index (PREF, Arg1)), Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x077B, 0x00, 0x00, Local1, Local0)
            }
        }

        Method (MLR0, 0, NotSerialized)
        {
            OUTP ("Store a Local Reference to Uninit Package element")
            Store ("Local0", Local0)
            MLRP (RefOf (Local0), 0x03)
        }

        Method (MLR1, 0, NotSerialized)
        {
            OUTP ("Store a Local Reference to Integer Package element")
            Store ("Local0", Local0)
            MLRP (RefOf (Local0), 0x00)
        }

        Method (MLR2, 0, NotSerialized)
        {
            OUTP ("Store a Local Reference to Reference Package element")
            Store ("Local0", Local0)
            MLRP (RefOf (Local0), 0x01)
        }

        Method (MLR3, 0, NotSerialized)
        {
            OUTP ("Store a Integer to Reference Package element")
            Store ("Local0", Local0)
            MLRP (0x03, 0x02)
        }

        Method (M000, 0, NotSerialized)
        {
            MLR0 ()
            MLR1 ()
            MLR2 ()
            MLR3 ()
        }

        CH03 (TS, Z179, 0x7C, 0x07AB, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                MLR0 ()
            }
            Case (0x02)
            {
                MLR1 ()
            }
            Case (0x03)
            {
                MLR2 ()
            }
            Case (0x04)
            {
                MLR3 ()
            }

        }

        CH03 (TS, Z179, 0x7D, 0x07B3, 0x00)
    }

    Method (ALRP, 0, NotSerialized)
    {
        IIN0 ()
        MS1F (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BLRP, 0, NotSerialized)
    {
        IIN0 ()
        MS1F (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CLRP, 0, NotSerialized)
    {
        IIN0 ()
        MS1F (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DLRP, 0, NotSerialized)
    {
        IIN0 ()
        MS1F (0x04)
        Return (POUT) /* \POUT */
    }

    Method (ELRP, 0, NotSerialized)
    {
        IIN0 ()
        MS1F (0x00)
        Return (POUT) /* \POUT */
    }

    Method (MS20, 1, Serialized)
    {
        Name (TS, "ms20")
        Name (Y, 0x02)
        Method (MFR0, 0, Serialized)
        {
            OUTP ("Forward reference within a control method 0")
            Store (Y, Local0)
            If (LNotEqual (Local0, 0x02))
            {
                ERR (TS, Z179, 0x07CE, 0x00, 0x00, Local0, 0x02)
            }

            Name (Y, 0x01)
            Store (Y, Local0)
            If (LNotEqual (Local0, 0x01))
            {
                ERR (TS, Z179, 0x07D5, 0x00, 0x00, Local0, 0x01)
            }
        }

        Method (MFR1, 0, Serialized)
        {
            OUTP ("Natural reference within a control method")
            Name (Y, 0x01)
            Store (^Y, Local0)
            If (LNotEqual (Local0, 0x02))
            {
                ERR (TS, Z179, 0x07E1, 0x00, 0x00, Local0, 0x02)
            }

            Store (Y, Local0)
            If (LNotEqual (Local0, 0x01))
            {
                ERR (TS, Z179, 0x07E6, 0x00, 0x00, Local0, 0x01)
            }
        }

        Method (MFR2, 0, Serialized)
        {
            OUTP ("Forward reference within a control method 2")
            Store (^MFR2.Y, Local0)
            CH04 (TS, 0x00, 0xFF, Z179, 0x07EF, "^mfr2.Y", Local0)
            Name (Y, 0x01)
            Store (^MFR2.Y, Local0)
            If (LNotEqual (Local0, 0x01))
            {
                ERR (TS, Z179, 0x07F5, 0x00, 0x00, Local0, 0x01)
            }
        }

        Method (MFR3, 0, Serialized)
        {
            OUTP ("Forward reference within a control method 3")
            Name (Y, 0x01)
            Store (^MFR3.Y, Local0)
            If (LNotEqual (Local0, 0x01))
            {
                ERR (TS, Z179, 0x0801, 0x00, 0x00, Local0, 0x01)
            }
        }

        Method (M000, 0, NotSerialized)
        {
            MFR0 ()
            MFR1 ()
            If (ABUU){}
            Else
            {
                MFR2 ()
            }

            MFR3 ()
        }

        CH03 (TS, Z179, 0x85, 0x0812, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                MFR0 ()
            }
            Case (0x02)
            {
                MFR1 ()
            }
            Case (0x03)
            {
                MFR2 ()
            }
            Case (0x04)
            {
                MFR3 ()
            }

        }

        CH03 (TS, Z179, 0x86, 0x081A, 0x00)
    }

    Method (AMFR, 0, NotSerialized)
    {
        IIN0 ()
        MS20 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BMFR, 0, NotSerialized)
    {
        IIN0 ()
        MS20 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CMFR, 0, NotSerialized)
    {
        IIN0 ()
        MS20 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DMFR, 0, NotSerialized)
    {
        IIN0 ()
        MS20 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (MS21, 1, Serialized)
    {
        Name (TS, "ms21")
        Method (AACT, 1, Serialized)
        {
            If (Arg0)
            {
                Return (Add (Arg0, AACT (Subtract (Arg0, 0x01))))
            }
            Else
            {
                Return (0x00)
            }
        }

        Method (MAC0, 0, NotSerialized)
        {
            OUTP ("Recursive method execution aact(0)")
            OUTP (AACT (0x00))
        }

        Method (MAC1, 0, NotSerialized)
        {
            OUTP ("Recursive method execution aact(1)")
            OUTP (AACT (0x01))
        }

        Method (MAC2, 0, NotSerialized)
        {
            OUTP ("Recursive method execution aact(2)")
            OUTP (AACT (0x02))
        }

        Method (MAC3, 0, NotSerialized)
        {
            OUTP ("Recursive method execution aact(6)")
            OUTP (AACT (0x06))
        }

        Method (MAC4, 0, NotSerialized)
        {
            OUTP ("Recursive method execution aact(513)")
            OUTP (AACT (0x0201))
            CH04 (TS, 0x00, 0xFF, Z179, 0x0851, "recursion", 0x0201)
        }

        Method (M000, 0, NotSerialized)
        {
            MAC0 ()
            MAC1 ()
            MAC2 ()
            MAC3 ()
            If (ABUU){}
            Else
            {
                MAC4 ()
            }
        }

        CH03 (TS, Z179, 0x88, 0x0861, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                MAC0 ()
            }
            Case (0x02)
            {
                MAC1 ()
            }
            Case (0x03)
            {
                MAC2 ()
            }
            Case (0x04)
            {
                MAC3 ()
            }
            Case (0x05)
            {
                MAC4 ()
            }

        }

        CH03 (TS, Z179, 0x89, 0x086A, 0x00)
    }

    Method (AREC, 0, NotSerialized)
    {
        IIN0 ()
        MS21 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BREC, 0, NotSerialized)
    {
        IIN0 ()
        MS21 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CREC, 0, NotSerialized)
    {
        IIN0 ()
        MS21 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DREC, 0, NotSerialized)
    {
        IIN0 ()
        MS21 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (EREC, 0, NotSerialized)
    {
        IIN0 ()
        MS21 (0x05)
        Return (POUT) /* \POUT */
    }

    Method (MS22, 1, Serialized)
    {
        Name (TS, "ms22")
        Name (IACT, 0x00)
        Method (CACT, 1, Serialized)
        {
            If (Arg0)
            {
                Name (IACT, 0xFFFFFFFF)
            }

            Return (IACT) /* \MS22.CACT.IACT */
        }

        Method (M000, 0, NotSerialized)
        {
            OUTP ("Conditional reference within a control method 0")
            OUTP ("expected iact 0:")
            Store (CACT (0x00), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x088F, 0x00, 0x00, Local0, 0x00)
            }
        }

        Method (M001, 0, NotSerialized)
        {
            OUTP ("Conditional reference within a control method 1")
            OUTP ("expected iact 0xffffffff:")
            Store (CACT (0x01), Local0)
            If (LNotEqual (Local0, 0xFFFFFFFF))
            {
                ERR (TS, Z179, 0x089B, 0x00, 0x00, Local0, 0xFFFFFFFF)
            }
        }

        CH03 (TS, Z179, 0x8C, 0x089F, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
                M001 ()
            }
            Case (0x01)
            {
                M000 ()
            }
            Case (0x02)
            {
                M001 ()
            }

        }

        CH03 (TS, Z179, 0x8D, 0x08A5, 0x00)
    }

    Method (AMCR, 0, NotSerialized)
    {
        IIN0 ()
        MS22 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BMCR, 0, NotSerialized)
    {
        IIN0 ()
        MS22 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (MS23, 1, Serialized)
    {
        Name (TS, "ms23")
        Method (MIR0, 0, Serialized)
        {
            Name (FL00, 0x00)
            Method (M001, 0, NotSerialized)
            {
                If (FL00)
                {
                    Store (Add (0xABCD, 0x00), Local1)
                }
                ElseIf (0x00)
                {
                    Return (0x01)
                }
            }

            OUTP ("Implicit return no operator")
            OUTP ("An exception is expected: ...")
            Store (M001 (), Local0)
            CH04 (TS, 0x00, 0xFF, Z179, 0x08C7, 0x00, 0x00)
        }

        Method (MIR1, 0, Serialized)
        {
            Name (FL00, 0x01)
            Method (M001, 0, NotSerialized)
            {
                If (FL00)
                {
                    Store (Add (0xABCD, 0x00), Local1)
                }
                Else
                {
                    Return (0x01)
                }
            }

            OUTP ("Implicit return after Add")
            OUTP ("0xabcd expected: ...")
            Store (M001 (), Local0)
            If (SLCK)
            {
                If (CH03 (TS, Z179, 0x8F, 0x08DD, 0x00))
                {
                    Return (Zero)
                }

                If (LNotEqual (Local0, 0xABCD))
                {
                    ERR (TS, Z179, 0x08DF, 0x00, 0x00, Local0, 0xABCD)
                }
            }
            Else
            {
                CH04 (TS, 0x00, 0xFF, Z179, 0x08E2, 0x00, 0x00)
            }
        }

        Method (MIR2, 0, Serialized)
        {
            Name (FL00, 0x00)
            Method (M001, 0, NotSerialized)
            {
                If (FL00)
                {
                    Return (0xABCE)
                }
                ElseIf (0x00)
                {
                    Return (0x01)
                }
            }

            OUTP ("Implicit return no operator 2")
            OUTP ("An exception is expected: ...")
            Store (M001 (), Local0)
            CH04 (TS, 0x00, 0xFF, Z179, 0x08F7, 0x00, 0x00)
        }

        Method (MIR3, 0, Serialized)
        {
            Name (FL00, 0x01)
            Method (M001, 0, NotSerialized)
            {
                If (FL00)
                {
                    Return (0xABCE)
                }
                Else
                {
                    Return (0x01)
                }
            }

            OUTP ("Explicit return conditionally")
            OUTP ("0xabce expected: ...")
            Store (M001 (), Local0)
            If (SLCK)
            {
                If (CH03 (TS, Z179, 0x93, 0x090D, 0x00))
                {
                    Return (Zero)
                }

                If (LNotEqual (Local0, 0xABCE))
                {
                    ERR (TS, Z179, 0x090F, 0x00, 0x00, Local0, 0xABCE)
                }
            }
            Else
            {
                CH04 (TS, 0x00, 0xFF, Z179, 0x0912, 0x00, 0x00)
            }
        }

        Method (MIR4, 0, Serialized)
        {
            Name (FL00, 0x00)
            Name (I000, 0xABCD0000)
            Name (I001, 0xABCD0001)
            Method (M000, 0, Serialized)
            {
                Switch (ToInteger (Store (0xABCD000F, I001) /* \MS23.MIR4.I001 */))
                {
                    Case (0x00)
                    {
                        If (FL00)
                        {
                            Return (0x00)
                        }
                    }

                }
            }

            OUTP ("Implicit return on Switch")
            Store (0xDDDD9000, I000) /* \MS23.MIR4.I000 */
            Store (M000 (), I000) /* \MS23.MIR4.I000 */
            If (SLCK)
            {
                If (CH03 (TS, Z179, 0x96, 0x092E, 0x00))
                {
                    Return (Zero)
                }

                If (Y901)
                {
                    Store (0x00, Local0)
                }
                Else
                {
                    Store (0xABCD000F, Local0)
                }

                If (LNotEqual (I000, Local0))
                {
                    ERR (TS, Z179, 0x0937, 0x00, 0x00, I000, Local0)
                }
            }
            Else
            {
                CH04 (TS, 0x00, 0xFF, Z179, 0x093A, 0x00, 0x00)
            }
        }

        Method (MIR5, 0, Serialized)
        {
            Name (FL00, 0x00)
            Name (I000, 0xABCD0000)
            Name (I001, 0xABCD0001)
            Method (M000, 0, NotSerialized)
            {
                If (Store (0xABCD000D, I001) /* \MS23.MIR5.I001 */)
                {
                    If (FL00)
                    {
                        Return (0x00)
                    }
                }
            }

            OUTP ("Implicit return on If")
            Store (0xDDDD9000, I000) /* \MS23.MIR5.I000 */
            Store (M000 (), I000) /* \MS23.MIR5.I000 */
            If (SLCK)
            {
                If (CH03 (TS, Z179, 0x99, 0x0954, 0x00))
                {
                    Return (Zero)
                }

                If (Y901)
                {
                    Store (0x00, Local0)
                }
                Else
                {
                    Store (0xABCD000D, Local0)
                }

                If (LNotEqual (I000, Local0))
                {
                    ERR (TS, Z179, 0x095D, 0x00, 0x00, I000, Local0)
                }
            }
            Else
            {
                CH04 (TS, 0x00, 0xFF, Z179, 0x0960, 0x00, 0x00)
            }
        }

        Method (MIR6, 0, Serialized)
        {
            Name (FL00, 0x00)
            Name (I000, 0xABCD0000)
            Name (I001, 0xABCD0001)
            Method (M000, 0, NotSerialized)
            {
                While (Store (0xABCD000E, I001) /* \MS23.MIR6.I001 */)
                {
                    If (FL00)
                    {
                        Return (0x00)
                    }

                    Break
                }
            }

            OUTP ("Implicit return on While")
            Store (0xDDDD9000, I000) /* \MS23.MIR6.I000 */
            Store (M000 (), I000) /* \MS23.MIR6.I000 */
            If (SLCK)
            {
                If (CH03 (TS, Z179, 0x9C, 0x097B, 0x00))
                {
                    Return (Zero)
                }

                If (Y901)
                {
                    Store (0x00, Local0)
                }
                Else
                {
                    Store (0xABCD000E, Local0)
                }

                If (LNotEqual (I000, Local0))
                {
                    ERR (TS, Z179, 0x0984, 0x00, 0x00, I000, Local0)
                }
            }
            Else
            {
                CH04 (TS, 0x00, 0xFF, Z179, 0x0987, 0x00, 0x00)
            }
        }

        Method (M000, 0, NotSerialized)
        {
            MIR0 ()
            MIR1 ()
            MIR2 ()
            MIR3 ()
            If (ABUU){}
            Else
            {
                MIR4 ()
            }

            If (ABUU){}
            Else
            {
                MIR5 ()
            }

            If (ABUU){}
            Else
            {
                MIR6 ()
            }
        }

        CH03 (TS, Z179, 0x9F, 0x09A2, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                MIR0 ()
            }
            Case (0x02)
            {
                MIR1 ()
            }
            Case (0x03)
            {
                MIR2 ()
            }
            Case (0x04)
            {
                MIR3 ()
            }
            Case (0x05)
            {
                MIR4 ()
            }
            Case (0x06)
            {
                MIR5 ()
            }
            Case (0x07)
            {
                MIR6 ()
            }

        }

        CH03 (TS, Z179, 0xA0, 0x09AD, 0x00)
    }

    Method (AMIR, 0, NotSerialized)
    {
        IIN0 ()
        MS23 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BMIR, 0, NotSerialized)
    {
        IIN0 ()
        MS23 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CMIR, 0, NotSerialized)
    {
        IIN0 ()
        MS23 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DMIR, 0, NotSerialized)
    {
        IIN0 ()
        MS23 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (EMIR, 0, NotSerialized)
    {
        IIN0 ()
        MS23 (0x05)
        Return (POUT) /* \POUT */
    }

    Method (FMIR, 0, NotSerialized)
    {
        IIN0 ()
        MS23 (0x06)
        Return (POUT) /* \POUT */
    }

    Method (GMIR, 0, NotSerialized)
    {
        IIN0 ()
        MS23 (0x07)
        Return (POUT) /* \POUT */
    }

    Method (MS24, 0, Serialized)
    {
        Name (TS, "ms24")
        Method (MMID, 0, Serialized)
        {
            Name (S000, "0321")
            Name (S001, "0321")
            Name (B000, Buffer (0x03)
            {
                 0x21, 0x03, 0x00                                 // !..
            })
            Name (B001, Buffer (0x03)
            {
                 0x21, 0x03, 0x00                                 // !..
            })
            OUTP ("Increment/Decrement with String/Buffer")
            OUTP (S000)
            OUTP (S001)
            Subtract (S000, 0x01, S000) /* \MS24.MMID.S000 */
            Decrement (S001)
            Store (ObjectType (S000), Local0)
            Store (ObjectType (S001), Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x09D4, 0x00, 0x00, Local0, Local1)
            }
            ElseIf (LNotEqual (S000, S001))
            {
                ERR (TS, Z179, 0x09D6, 0x00, 0x00, S000, S001)
            }
            Else
            {
                OUTP ("Ok Subtract/Decrement for String")
            }

            OUTP ("======")
            OUTP (B000)
            OUTP (B001)
            Add (B000, 0x01, B000) /* \MS24.MMID.B000 */
            Increment (B001)
            Store (ObjectType (B000), Local0)
            Store (ObjectType (B001), Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x09E6, 0x00, 0x00, Local0, Local1)
            }
            ElseIf (LNotEqual (B000, B001))
            {
                ERR (TS, Z179, 0x09E8, 0x00, 0x00, Local0, Local1)
            }
            Else
            {
                OUTP ("Ok Add/Increment for Buffer")
            }
        }

        CH03 (TS, Z179, 0xA5, 0x09EE, 0x00)
        MMID ()
        CH03 (TS, Z179, 0xA6, 0x09F0, 0x00)
    }

    Method (AMID, 0, NotSerialized)
    {
        IIN0 ()
        MS24 ()
        Return (POUT) /* \POUT */
    }

    Method (MS25, 1, Serialized)
    {
        Name (TS, "ms25")
        Method (MSD0, 0, Serialized)
        {
            Name (I000, 0xFFFFFFFF)
            Name (I001, 0x12345678)
            OUTP ("Check Store(..., DeRefof(...)) behavior: none DeRefof")
            Store (I001, RefOf (I000))
            CH03 (TS, Z179, 0xA7, 0x0A08, 0x00)
            If (LNotEqual (I000, 0x12345678))
            {
                ERR (TS, Z179, 0x0A0A, 0x00, 0x00, I000, 0x12345678)
            }
        }

        Method (MSD1, 0, Serialized)
        {
            Name (I000, 0xFFFFFFFF)
            Name (I001, 0x12345678)
            OUTP ("Check Store(..., DeRefof(...)) behavior: Refof(Named)")
            Store (I001, DerefOf (RefOf (I000)))
            CH03 (TS, Z179, 0xA9, 0x0A16, 0x00)
            If (LNotEqual (I000, 0x12345678))
            {
                ERR (TS, Z179, 0x0A18, 0x00, 0x00, I000, 0x12345678)
            }
        }

        Method (MSD2, 0, Serialized)
        {
            Name (I000, 0xFFFFFFFF)
            Name (I001, 0x12345678)
            OUTP ("Check Store(..., DeRefof(...)) behavior: Refof in LocalX")
            Store (RefOf (I000), Local2)
            Store (I001, DerefOf (Local2))
            CH03 (TS, Z179, 0xAB, 0x0A26, 0x00)
            If (LNotEqual (I000, 0x12345678))
            {
                ERR (TS, Z179, 0x0A28, 0x00, 0x00, I000, 0x12345678)
            }
        }

        Method (MSD3, 0, Serialized)
        {
            Name (I000, 0xFFFFFFFF)
            Name (I001, 0x12345678)
            OUTP ("Check Store(..., DeRefof(...)) behavior: DeRefof(2xRefof)")
            Store (RefOf (I000), Local1)
            Store (RefOf (Local1), Local2)
            Store (I001, DerefOf (Local2))
            CH03 (TS, Z179, 0xAD, 0x0A37, 0x00)
            If (LNotEqual (I000, 0xFFFFFFFF))
            {
                ERR (TS, Z179, 0x0A3A, 0x00, 0x00, I000, 0xFFFFFFFF)
            }

            Store (DerefOf (Local1), Local4)
            If (CH04 (TS, 0x00, 0xFF, Z179, 0x0A3E, 0x00, 0x00)){}
            ElseIf (LNotEqual (Local1, 0x12345678))
            {
                ERR (TS, Z179, 0x0A40, 0x00, 0x00, Local1, 0x12345678)
            }
        }

        CH03 (TS, Z179, 0xB1, 0x0A44, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                MSD0 ()
                MSD1 ()
                MSD2 ()
                MSD3 ()
            }
            Case (0x01)
            {
                MSD0 ()
            }
            Case (0x02)
            {
                MSD1 ()
            }
            Case (0x03)
            {
                MSD2 ()
            }
            Case (0x04)
            {
                MSD3 ()
            }

        }

        CH03 (TS, Z179, 0xB2, 0x0A4C, 0x00)
    }

    Method (AMSD, 0, NotSerialized)
    {
        IIN0 ()
        MS25 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BMSD, 0, NotSerialized)
    {
        IIN0 ()
        MS25 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CMSD, 0, NotSerialized)
    {
        IIN0 ()
        MS25 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DMSD, 0, NotSerialized)
    {
        IIN0 ()
        MS25 (0x04)
        Return (POUT) /* \POUT */
    }

    Name (VMEM, 0x000A0000)
    Name (SMBA, 0x01)
    Method (MS26, 1, Serialized)
    {
        Name (TS, "ms26")
        OperationRegion (OPR0, SystemMemory, VMEM, 0x0100)
        Method (RFU0, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                G001,   128
            }

            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                Offset (0x08), 
                FU01,   8
            }

            OUTP ("Store Integer exceeding Field Unit")
            Store (0x00, G001) /* \MS26.RFU0.G001 */
            Store (FU01, Local0)
            Store (0x00, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0A7A, 0x00, 0x00, Local0, Local1)
            }

            Store (0x5A, FU01) /* \MS26.RFU0.FU01 */
            Store (FU01, Local0)
            Store (0x5A, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0A81, 0x00, 0x00, Local0, Local1)
            }

            Store (0x3C69, FU01) /* \MS26.RFU0.FU01 */
            Store (FU01, Local0)
            Store (0x69, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0A88, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (RFU1, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                G001,   128
            }

            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                Offset (0x08), 
                FU01,   8
            }

            OUTP ("Store Buffer exceeding Field Unit")
            Store (0x00, G001) /* \MS26.RFU1.G001 */
            Store (FU01, Local0)
            Store (0x00, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0A9D, 0x00, 0x00, Local0, Local1)
            }

            Store (0x5A, FU01) /* \MS26.RFU1.FU01 */
            Store (FU01, Local0)
            Store (0x5A, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0AA4, 0x00, 0x00, Local0, Local1)
            }

            Store (Buffer (0x02)
                {
                     0x3C, 0x69                                       // <i
                }, FU01) /* \MS26.RFU1.FU01 */
            Store (FU01, Local0)
            Store (0x3C, Local1)
            If (LAnd (ABUU, LNot (Q009)))
            {
                Store (0x69, Local1)
                If (LNotEqual (Local0, Local1))
                {
                    ERR (TS, Z179, 0x0AAD, 0x00, 0x00, Local0, Local1)
                }
            }
            ElseIf (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0AB0, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (RFU2, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                G001,   128
            }

            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                Offset (0x08), 
                FU01,   8
            }

            OUTP ("Store String exceeding Field Unit")
            Store (0x00, G001) /* \MS26.RFU2.G001 */
            Store (FU01, Local0)
            Store (0x00, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0AC5, 0x00, 0x00, Local0, Local1)
            }

            Store (0x5A, FU01) /* \MS26.RFU2.FU01 */
            Store (FU01, Local0)
            Store (0x5A, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0ACC, 0x00, 0x00, Local0, Local1)
            }

            Store ("79", FU01) /* \MS26.RFU2.FU01 */
            Store (FU01, Local0)
            Store (0x37, Local1)
            If (LAnd (ABUU, LNot (Q009)))
            {
                Store (0x39, Local1)
                If (LNotEqual (Local0, Local1))
                {
                    ERR (TS, Z179, 0x0AD5, 0x00, 0x00, Local0, Local1)
                }
            }
            ElseIf (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0AD8, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (RFU3, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                G001,   128
            }

            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                Offset (0x08), 
                FU01,   6, 
                FU02,   2
            }

            OUTP ("Store Buffer exceeding 6-bit Field Unit")
            Store (0x00, G001) /* \MS26.RFU3.G001 */
            Store (FU01, Local0)
            Store (0x00, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0AED, 0x00, 0x00, Local0, Local1)
            }

            Store (0x5A, FU01) /* \MS26.RFU3.FU01 */
            Store (FU01, Local0)
            Store (0x1A, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0AF4, 0x00, 0x00, Local0, Local1)
            }

            Store (Buffer (0x02)
                {
                     0x7C, 0x69                                       // |i
                }, FU01) /* \MS26.RFU3.FU01 */
            Store (FU01, Local0)
            Store (0x3C, Local1)
            If (LAnd (ABUU, LNot (Q009)))
            {
                Store (0x29, Local1)
                If (LNotEqual (Local0, Local1))
                {
                    ERR (TS, Z179, 0x0AFD, 0x00, 0x00, Local0, Local1)
                }
            }
            ElseIf (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B00, 0x00, 0x00, Local0, Local1)
            }

            Store (FU02, Local0)
            Store (0x00, Local1)
            If (LAnd (ABUU, LNot (Q009)))
            {
                Store (0x01, Local1)
                If (LNotEqual (Local0, Local1))
                {
                    ERR (TS, Z179, 0x0B08, 0x00, 0x00, Local0, Local1)
                }
            }
            ElseIf (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B0B, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (RFU4, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                G001,   128
            }

            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                Offset (0x08), 
                FU01,   6, 
                FU02,   2
            }

            OUTP ("Store String exceeding 6-bit Field Unit")
            Store (0x00, G001) /* \MS26.RFU4.G001 */
            Store (FU01, Local0)
            Store (0x00, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B20, 0x00, 0x00, Local0, Local1)
            }

            Store (0x5A, FU01) /* \MS26.RFU4.FU01 */
            Store (FU01, Local0)
            Store (0x1A, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B27, 0x00, 0x00, Local0, Local1)
            }

            Store ("79", FU01) /* \MS26.RFU4.FU01 */
            Store (FU01, Local0)
            Store (0x37, Local1)
            If (LAnd (ABUU, LNot (Q009)))
            {
                Store (0x39, Local1)
                If (LNotEqual (Local0, Local1))
                {
                    ERR (TS, Z179, 0x0B30, 0x00, 0x00, Local0, Local1)
                }
            }
            ElseIf (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B33, 0x00, 0x00, Local0, Local1)
            }

            Store (FU02, Local0)
            Store (0x00, Local1)
            If (LAnd (ABUU, LNot (Q009)))
            {
                Store (0x01, Local1)
                If (LNotEqual (Local0, Local1))
                {
                    ERR (TS, Z179, 0x0B3B, 0x00, 0x00, Local0, Local1)
                }
            }
            ElseIf (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B3E, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (RFU5, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                G001,   128
            }

            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                Offset (0x08), 
                FU01,   10, 
                FU02,   6
            }

            OUTP ("Store Buffer exceeding 10-bit Field Unit")
            Store (0x00, G001) /* \MS26.RFU5.G001 */
            Store (FU01, Local0)
            Store (0x00, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B53, 0x00, 0x00, Local0, Local1)
            }

            Store (0x5A, FU01) /* \MS26.RFU5.FU01 */
            Store (FU01, Local0)
            Store (0x5A, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B5A, 0x00, 0x00, Local0, Local1)
            }

            Store (Buffer (0x02)
                {
                     0x3C, 0x69                                       // <i
                }, FU01) /* \MS26.RFU5.FU01 */
            Store (FU01, Local0)
            Store (0x013C, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B61, 0x00, 0x00, Local0, Local1)
            }

            Store (FU02, Local0)
            Store (0x00, Local1)
            If (LAnd (ABUU, LNot (Q009)))
            {
                Store (0x1A, Local1)
                If (LNotEqual (Local0, Local1))
                {
                    ERR (TS, Z179, 0x0B69, 0x00, 0x00, Local0, Local1)
                }
            }
            ElseIf (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B6C, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (RFU6, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                G001,   128
            }

            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                Offset (0x08), 
                FU01,   10, 
                FU02,   6
            }

            OUTP ("Store String exceeding 10-bit Field Unit")
            Store (0x00, G001) /* \MS26.RFU6.G001 */
            Store (FU01, Local0)
            Store (0x00, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B81, 0x00, 0x00, Local0, Local1)
            }

            Store (0x5A, FU01) /* \MS26.RFU6.FU01 */
            Store (FU01, Local0)
            Store (0x5A, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B88, 0x00, 0x00, Local0, Local1)
            }

            Store ("79", FU01) /* \MS26.RFU6.FU01 */
            Store (FU01, Local0)
            Store (0x0137, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B8F, 0x00, 0x00, Local0, Local1)
            }

            Store (FU02, Local0)
            Store (0x00, Local1)
            If (LAnd (ABUU, LNot (Q009)))
            {
                Store (0x0E, Local1)
                If (LNotEqual (Local0, Local1))
                {
                    ERR (TS, Z179, 0x0B97, 0x00, 0x00, Local0, Local1)
                }
            }
            ElseIf (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0B9A, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (RFU7, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                G001,   128
            }

            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                Offset (0x08), 
                FU01,   10, 
                FU02,   6
            }

            OUTP ("Store 3-byte Buffer exceeding 10-bit Field Unit")
            Store (0x00, G001) /* \MS26.RFU7.G001 */
            Store (FU01, Local0)
            Store (0x00, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0BAF, 0x00, 0x00, Local0, Local1)
            }

            Store (0x5A, FU01) /* \MS26.RFU7.FU01 */
            Store (FU01, Local0)
            Store (0x5A, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0BB6, 0x00, 0x00, Local0, Local1)
            }

            Store (Buffer (0x03)
                {
                     0x3C, 0x69, 0xA5                                 // <i.
                }, FU01) /* \MS26.RFU7.FU01 */
            Store (FU01, Local0)
            Store (0x013C, Local1)
            If (LAnd (ABUU, LNot (Q009)))
            {
                Store (0xA5, Local1)
                If (LNotEqual (Local0, Local1))
                {
                    ERR (TS, Z179, 0x0BBF, 0x00, 0x00, Local0, Local1)
                }
            }
            ElseIf (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0BC2, 0x00, 0x00, Local0, Local1)
            }

            Store (FU02, Local0)
            Store (0x00, Local1)
            If (LAnd (ABUU, LNot (Q009)))
            {
                Store (0x1A, Local1)
                If (LNotEqual (Local0, Local1))
                {
                    ERR (TS, Z179, 0x0BCA, 0x00, 0x00, Local0, Local1)
                }
            }
            ElseIf (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0BCD, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (RFU8, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                G001,   128
            }

            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                Offset (0x08), 
                FU01,   10, 
                FU02,   6
            }

            OUTP ("Store 3-char String exceeding 10-bit Field Unit")
            Store (0x00, G001) /* \MS26.RFU8.G001 */
            Store (FU01, Local0)
            Store (0x00, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0BE2, 0x00, 0x00, Local0, Local1)
            }

            Store (0x5A, FU01) /* \MS26.RFU8.FU01 */
            Store (FU01, Local0)
            Store (0x5A, Local1)
            If (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0BE9, 0x00, 0x00, Local0, Local1)
            }

            Store ("795", FU01) /* \MS26.RFU8.FU01 */
            Store (FU01, Local0)
            Store (0x0137, Local1)
            If (LAnd (ABUU, LNot (Q009)))
            {
                Store (0x35, Local1)
                If (LNotEqual (Local0, Local1))
                {
                    ERR (TS, Z179, 0x0BF2, 0x00, 0x00, Local0, Local1)
                }
            }
            ElseIf (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0BF5, 0x00, 0x00, Local0, Local1)
            }

            Store (FU02, Local0)
            Store (0x00, Local1)
            If (LAnd (ABUU, LNot (Q009)))
            {
                Store (0x0E, Local1)
                If (LNotEqual (Local0, Local1))
                {
                    ERR (TS, Z179, 0x0BFD, 0x00, 0x00, Local0, Local1)
                }
            }
            ElseIf (LNotEqual (Local0, Local1))
            {
                ERR (TS, Z179, 0x0C00, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (M000, 0, NotSerialized)
        {
            RFU0 ()
            RFU1 ()
            RFU2 ()
            RFU3 ()
            RFU4 ()
            RFU5 ()
            RFU6 ()
            RFU7 ()
            RFU8 ()
        }

        CH03 (TS, Z179, 0xD4, 0x0C11, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                RFU0 ()
            }
            Case (0x02)
            {
                RFU1 ()
            }
            Case (0x03)
            {
                RFU2 ()
            }
            Case (0x04)
            {
                RFU3 ()
            }
            Case (0x05)
            {
                RFU4 ()
            }
            Case (0x06)
            {
                RFU5 ()
            }
            Case (0x07)
            {
                RFU6 ()
            }
            Case (0x08)
            {
                RFU7 ()
            }
            Case (0x09)
            {
                RFU8 ()
            }

        }

        CH03 (TS, Z179, 0xD5, 0x0C1E, 0x00)
    }

    Method (ARFU, 0, NotSerialized)
    {
        IIN0 ()
        MS26 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BRFU, 0, NotSerialized)
    {
        IIN0 ()
        MS26 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CRFU, 0, NotSerialized)
    {
        IIN0 ()
        MS26 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DRFU, 0, NotSerialized)
    {
        IIN0 ()
        MS26 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (ERFU, 0, NotSerialized)
    {
        IIN0 ()
        MS26 (0x05)
        Return (POUT) /* \POUT */
    }

    Method (FRFU, 0, NotSerialized)
    {
        IIN0 ()
        MS26 (0x06)
        Return (POUT) /* \POUT */
    }

    Method (GRFU, 0, NotSerialized)
    {
        IIN0 ()
        MS26 (0x07)
        Return (POUT) /* \POUT */
    }

    Method (HRFU, 0, NotSerialized)
    {
        IIN0 ()
        MS26 (0x08)
        Return (POUT) /* \POUT */
    }

    Method (IRFU, 0, NotSerialized)
    {
        IIN0 ()
        MS26 (0x09)
        Return (POUT) /* \POUT */
    }

    Method (MS27, 1, Serialized)
    {
        Name (TS, "ms27")
        OperationRegion (OPR0, SystemMemory, VMEM, 0x0100)
        Field (OPR0, ByteAcc, NoLock, Preserve)
        {
            TOT0,   32, 
            TOT1,   32
        }

        Method (IFD0, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX1,   4, 
                DTA1,   3
            }

            IndexField (IDX1, DTA1, ByteAcc, NoLock, WriteAsZeros)
            {
                RE10,   3, 
                RE11,   3, 
                RE12,   3, 
                RE13,   3
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MS27.TOT0 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (Ones, ^RE10) /* \MS27.IFD0.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (Ones, ^RE11) /* \MS27.IFD0.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (Ones, ^RE12) /* \MS27.IFD0.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (Ones, ^RE13) /* \MS27.IFD0.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0C5A, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0C5D, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField ByteAcc 4-3 Ones write 3-3-3-3")
            TRY0 (0x00, 0x00, 0x07)
            TRY0 (0x01, 0x00, 0x00)
            Store (0x01, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x07, Local0)
            }

            TRY0 (0x02, 0x00, Local0)
            TRY0 (0x03, 0x00, 0x06)
        }

        Method (IFD1, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX1,   8, 
                DTA1,   8
            }

            IndexField (IDX1, DTA1, ByteAcc, NoLock, WriteAsZeros)
            {
                RE10,   8, 
                RE11,   8, 
                RE12,   8, 
                RE13,   8
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MS27.TOT0 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (0x12345678, ^RE10) /* \MS27.IFD1.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (0x12345678, ^RE11) /* \MS27.IFD1.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (0x12345678, ^RE12) /* \MS27.IFD1.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (0x12345678, ^RE13) /* \MS27.IFD1.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0C8C, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0C8F, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField ByteAcc 0x12345678 write 8-8-8-8")
            TRY0 (0x00, 0x00, 0x78)
            TRY0 (0x01, 0x01, 0x78)
            TRY0 (0x02, 0x02, 0x78)
            TRY0 (0x03, 0x03, 0x78)
        }

        Method (IFD2, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX1,   8, 
                DTA1,   8
            }

            IndexField (IDX1, DTA1, ByteAcc, NoLock, WriteAsZeros)
            {
                    ,   7, 
                RE10,   1, 
                RE11,   1, 
                Offset (0x02), 
                RE12,   4, 
                RE13,   4
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MS27.TOT0 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (Ones, ^RE10) /* \MS27.IFD2.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (Ones, ^RE11) /* \MS27.IFD2.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (Ones, ^RE12) /* \MS27.IFD2.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (Ones, ^RE13) /* \MS27.IFD2.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0CBA, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0CBD, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField ByteAcc Ones write Offset (0:7)1-(1:0)1-(2:0)4-4")
            TRY0 (0x00, 0x00, 0x80)
            Store (0x01, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0xFF, Local0)
            }

            TRY0 (0x01, 0x01, Local0)
            Store (0x0F, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0xFF, Local0)
            }

            TRY0 (0x02, 0x02, Local0)
            TRY0 (0x03, 0x02, 0xF0)
        }

        Method (IFD3, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX1,   8, 
                DTA1,   8
            }

            IndexField (IDX1, DTA1, ByteAcc, NoLock, WriteAsZeros)
            {
                Offset (0x01), 
                RE10,   8, 
                Offset (0x02), 
                RE11,   8, 
                Offset (0x07), 
                RE12,   8, 
                Offset (0x10), 
                RE13,   8
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MS27.TOT0 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (0x12345678, ^RE10) /* \MS27.IFD3.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (0x12345678, ^RE11) /* \MS27.IFD3.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (0x12345678, ^RE12) /* \MS27.IFD3.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (0x12345678, ^RE13) /* \MS27.IFD3.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0CF5, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0CF8, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField ByteAcc 0x12345678 write Offset (1:0)8-(2:0)8-(7:0)8-(16:0)8")
            TRY0 (0x00, 0x01, 0x78)
            TRY0 (0x01, 0x02, 0x78)
            TRY0 (0x02, 0x07, 0x78)
            TRY0 (0x03, 0x10, 0x78)
        }

        CH03 (TS, Z179, 0xE6, 0x0D04, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                IFD0 ()
                IFD1 ()
                IFD2 ()
                IFD3 ()
            }
            Case (0x01)
            {
                IFD0 ()
            }
            Case (0x02)
            {
                IFD1 ()
            }
            Case (0x03)
            {
                IFD2 ()
            }
            Case (0x04)
            {
                IFD3 ()
            }

        }

        CH03 (TS, Z179, 0xE7, 0x0D11, 0x00)
    }

    Method (MT27, 1, Serialized)
    {
        Name (TS, "mt27")
        OperationRegion (OPR0, SystemMemory, VMEM, 0x0100)
        Field (OPR0, ByteAcc, NoLock, Preserve)
        {
            TOT0,   32, 
            TOT1,   32
        }

        Method (IFD4, 0, Serialized)
        {
            Field (OPR0, WordAcc, NoLock, WriteAsZeros)
            {
                IDX1,   16, 
                DTA1,   16
            }

            IndexField (IDX1, DTA1, WordAcc, NoLock, WriteAsZeros)
            {
                RE10,   8, 
                RE11,   8, 
                RE12,   8, 
                RE13,   8
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MT27.TOT0 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (0x12345678, ^RE10) /* \MT27.IFD4.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (0x12345678, ^RE11) /* \MT27.IFD4.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (0x12345678, ^RE12) /* \MT27.IFD4.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (0x12345678, ^RE13) /* \MT27.IFD4.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0D3C, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0D3F, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField WordAcc Ones write 8-8-8-8")
            Store (0x78, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x5678, Local0)
            }

            TRY0 (0x00, 0x00, Local0)
            TRY0 (0x01, 0x00, 0x7800)
            Store (0x78, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x5678, Local0)
            }

            TRY0 (0x02, 0x02, Local0)
            TRY0 (0x03, 0x02, 0x7800)
        }

        Method (IFD5, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX1,   8, 
                DTA1,   8
            }

            IndexField (IDX1, DTA1, ByteAcc, NoLock, WriteAsZeros)
            {
                    ,   1, 
                RE10,   8, 
                    ,   1, 
                RE11,   8, 
                    ,   1, 
                RE12,   8, 
                    ,   1, 
                RE13,   8
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MT27.TOT0 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (Ones, ^RE10) /* \MT27.IFD5.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (Ones, ^RE11) /* \MT27.IFD5.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (Ones, ^RE12) /* \MT27.IFD5.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (Ones, ^RE13) /* \MT27.IFD5.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0D77, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0D7A, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField ByteAcc Ones write (:1)8-(:1)8-(:1)8-(:1)8")
            TRY0 (0x00, 0x01, 0x01)
            TRY0 (0x01, 0x02, 0x03)
            TRY0 (0x02, 0x03, 0x07)
            TRY0 (0x03, 0x04, 0x0F)
        }

        Method (IFD6, 0, Serialized)
        {
            Field (OPR0, DWordAcc, NoLock, WriteAsZeros)
            {
                IDX1,   32, 
                DTA1,   32
            }

            IndexField (IDX1, DTA1, DWordAcc, NoLock, WriteAsZeros)
            {
                RE10,   8, 
                RE11,   8, 
                RE12,   8, 
                RE13,   8
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MT27.TOT0 */
                Store (Zero, TOT1) /* \MT27.TOT1 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (Ones, ^RE10) /* \MT27.IFD6.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (Ones, ^RE11) /* \MT27.IFD6.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (Ones, ^RE12) /* \MT27.IFD6.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (Ones, ^RE13) /* \MT27.IFD6.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0DA4, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0DA7, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField DWordAcc Ones write 8-8-8-8")
            Store (0xFF, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0xFFFFFFFF, Local0)
            }

            TRY0 (0x00, 0x00, Local0)
            Store (0xFF00, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0xFFFFFF00, Local0)
            }

            TRY0 (0x01, 0x00, Local0)
            Store (0x00FF0000, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0xFFFF0000, Local0)
            }

            TRY0 (0x02, 0x00, Local0)
            TRY0 (0x03, 0x00, 0xFF000000)
        }

        Method (IFD7, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX1,   8, 
                DTA1,   8
            }

            IndexField (IDX1, DTA1, ByteAcc, NoLock, WriteAsZeros)
            {
                    ,   2, 
                RE10,   7, 
                    ,   2, 
                RE11,   7, 
                    ,   2, 
                RE12,   7, 
                    ,   2, 
                RE13,   7
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MT27.TOT0 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (Ones, ^RE10) /* \MT27.IFD7.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (Ones, ^RE11) /* \MT27.IFD7.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (Ones, ^RE12) /* \MT27.IFD7.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (Ones, ^RE13) /* \MT27.IFD7.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0DE3, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0DE6, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField ByteAcc Ones write (:2)7-(:2)7-(:2)7-(:2)7")
            Store (0x01, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x03, Local0)
            }

            TRY0 (0x00, 0x01, Local0)
            Store (0x03, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x07, Local0)
            }

            TRY0 (0x01, 0x02, Local0)
            Store (0x07, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x0F, Local0)
            }

            TRY0 (0x02, 0x03, Local0)
            Store (0x0F, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x1F, Local0)
            }

            TRY0 (0x03, 0x04, Local0)
        }

        CH03 (TS, Z179, 0xE8, 0x0E05, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                IFD4 ()
                IFD5 ()
                IFD6 ()
                IFD7 ()
            }
            Case (0x05)
            {
                IFD4 ()
            }
            Case (0x06)
            {
                IFD5 ()
            }
            Case (0x07)
            {
                IFD6 ()
            }
            Case (0x08)
            {
                IFD7 ()
            }

        }

        CH03 (TS, Z179, 0xE9, 0x0E12, 0x00)
    }

    Method (MU27, 1, Serialized)
    {
        Name (TS, "mu27")
        OperationRegion (OPR0, SystemMemory, VMEM, 0x0100)
        Field (OPR0, ByteAcc, NoLock, Preserve)
        {
            TOT0,   32, 
            TOT1,   32
        }

        Method (IFD8, 0, Serialized)
        {
            Field (OPR0, DWordAcc, NoLock, WriteAsZeros)
            {
                IDX1,   32, 
                DTA1,   32
            }

            IndexField (IDX1, DTA1, DWordAcc, NoLock, WriteAsZeros)
            {
                Offset (0x01), 
                RE10,   8, 
                Offset (0x04), 
                RE11,   8, 
                Offset (0x09), 
                RE12,   8, 
                Offset (0x0C), 
                RE13,   8
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MU27.TOT0 */
                Store (Zero, TOT1) /* \MU27.TOT1 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (0x12345678, ^RE10) /* \MU27.IFD8.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (0x12345678, ^RE11) /* \MU27.IFD8.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (0x12345678, ^RE12) /* \MU27.IFD8.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (0x12345678, ^RE13) /* \MU27.IFD8.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0E42, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0E45, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField DWordAcc 0x12345678 write Offset (1)8-(4)8-(9)8-(12)8")
            Store (0x7800, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x34567800, Local0)
            }

            TRY0 (0x00, 0x00, Local0)
            Store (0x78, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x12345678, Local0)
            }

            TRY0 (0x01, 0x04, Local0)
            Store (0x7800, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x34567800, Local0)
            }

            TRY0 (0x02, 0x08, Local0)
            Store (0x78, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x12345678, Local0)
            }

            TRY0 (0x03, 0x0C, Local0)
        }

        Method (IFD9, 0, Serialized)
        {
            Field (OPR0, WordAcc, NoLock, WriteAsZeros)
            {
                IDX1,   16, 
                DTA1,   16
            }

            IndexField (IDX1, DTA1, WordAcc, NoLock, WriteAsZeros)
            {
                Offset (0x01), 
                RE10,   8, 
                Offset (0x04), 
                RE11,   8, 
                Offset (0x09), 
                RE12,   8, 
                Offset (0x0C), 
                RE13,   8
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MU27.TOT0 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (0x12345678, ^RE10) /* \MU27.IFD9.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (0x12345678, ^RE11) /* \MU27.IFD9.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (0x12345678, ^RE12) /* \MU27.IFD9.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (0x12345678, ^RE13) /* \MU27.IFD9.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0E85, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0E88, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField WordAcc 0x12345678 write Offset (1)8-(4)8-(9)8-(12)8")
            TRY0 (0x00, 0x00, 0x7800)
            Store (0x78, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x5678, Local0)
            }

            TRY0 (0x01, 0x04, Local0)
            TRY0 (0x02, 0x08, 0x7800)
            Store (0x78, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x5678, Local0)
            }

            TRY0 (0x03, 0x0C, Local0)
        }

        Method (IFDA, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX1,   16, 
                DTA1,   16
            }

            IndexField (IDX1, DTA1, ByteAcc, NoLock, WriteAsZeros)
            {
                Offset (0x01), 
                RE10,   8, 
                Offset (0x04), 
                RE11,   8, 
                Offset (0x09), 
                RE12,   8, 
                Offset (0x0C), 
                RE13,   8
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MU27.TOT0 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (0x12345678, ^RE10) /* \MU27.IFDA.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (0x12345678, ^RE11) /* \MU27.IFDA.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (0x12345678, ^RE12) /* \MU27.IFDA.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (0x12345678, ^RE13) /* \MU27.IFDA.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0EC0, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0EC3, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField ByteAcc 0x12345678 write Offset (1)8-(4)8-(9)8-(12)8")
            TRY0 (0x00, 0x01, 0x78)
            TRY0 (0x01, 0x04, 0x78)
            TRY0 (0x02, 0x09, 0x78)
            TRY0 (0x03, 0x0C, 0x78)
        }

        Method (IFDB, 0, Serialized)
        {
            Field (OPR0, AnyAcc, NoLock, WriteAsZeros)
            {
                IDX1,   16, 
                DTA1,   16
            }

            IndexField (IDX1, DTA1, AnyAcc, NoLock, WriteAsZeros)
            {
                Offset (0x01), 
                RE10,   8, 
                Offset (0x04), 
                RE11,   8, 
                Offset (0x09), 
                RE12,   8, 
                Offset (0x0C), 
                RE13,   8
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MU27.TOT0 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (0x12345678, ^RE10) /* \MU27.IFDB.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (0x12345678, ^RE11) /* \MU27.IFDB.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (0x12345678, ^RE12) /* \MU27.IFDB.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (0x12345678, ^RE13) /* \MU27.IFDB.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0EF0, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0EF3, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField AnyAcc 0x12345678 write Offset (1)8-(4)8-(9)8-(12)8")
            TRY0 (0x00, 0x01, 0x78)
            TRY0 (0x01, 0x04, 0x78)
            TRY0 (0x02, 0x09, 0x78)
            TRY0 (0x03, 0x0C, 0x78)
        }

        CH03 (TS, Z179, 0xEA, 0x0EFF, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                IFD8 ()
                IFD9 ()
                IFDA ()
                IFDB ()
            }
            Case (0x09)
            {
                IFD8 ()
            }
            Case (0x0A)
            {
                IFD9 ()
            }
            Case (0x0B)
            {
                IFDA ()
            }
            Case (0x0C)
            {
                IFDB ()
            }

        }

        CH03 (TS, Z179, 0xEB, 0x0F0C, 0x00)
    }

    Method (MV27, 1, Serialized)
    {
        Name (TS, "mv27")
        OperationRegion (OPR0, SystemMemory, VMEM, 0x0100)
        Field (OPR0, ByteAcc, NoLock, Preserve)
        {
            TOT0,   32, 
            TOT1,   32
        }

        Method (IFDC, 0, Serialized)
        {
            Field (OPR0, WordAcc, NoLock, WriteAsZeros)
            {
                IDX0,   16, 
                DTA0,   16
            }

            IndexField (IDX0, DTA0, WordAcc, NoLock, WriteAsZeros)
            {
                IDF0,   8, 
                Offset (0x03), 
                IDF1,   8, 
                Offset (0x06), 
                IDF2,   8, 
                Offset (0x0B), 
                IDF3,   8
            }

            Method (TRY0, 4, NotSerialized)
            {
                Store (IDX0, Local0)
                Store (DTA0, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x0F31, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x0F34, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField WordAcc read")
            Store (0x1234FFFF, TOT0) /* \MV27.TOT0 */
            TRY0 (0x00, 0x00, 0x1234, IDF0)
            Store (0x5678FFFF, TOT0) /* \MV27.TOT0 */
            TRY0 (0x02, 0x02, 0x5678, IDF1)
            Store (0x9ABCFFFF, TOT0) /* \MV27.TOT0 */
            TRY0 (0x03, 0x06, 0x9ABC, IDF2)
            Store (0xDE01FFFF, TOT0) /* \MV27.TOT0 */
            TRY0 (0x04, 0x0A, 0xDE01, IDF3)
        }

        Method (TRY4, 5, NotSerialized)
        {
            Method (TRY0, 3, NotSerialized)
            {
                Store (Arg0, TOT0) /* \MV27.TOT0 */
                Store (DerefOf (Arg1), Local0)
                Store (TOT0, Local1)
                Store (DerefOf (Index (Arg2, 0x00)), Local2)
                Store (DerefOf (Index (Arg2, 0x01)), Local3)
                Store (DerefOf (Index (Arg2, 0x02)), Local4)
                Add (0x0140, Multiply (Local2, 0x02), Local2)
                If (LNotEqual (Local0, Local3))
                {
                    ERR (TS, Z179, 0x0F54, 0x00, 0x00, Local0, Local3)
                }

                If (LNotEqual (Local1, Local4))
                {
                    ERR (TS, Z179, 0x0F57, 0x00, 0x00, Local1, Local4)
                }
            }

            Store (DerefOf (Index (Arg0, 0x00)), Local0)
            TRY0 (Local0, Arg1, DerefOf (Index (Arg0, 0x01)))
            TRY0 (Local0, Arg2, DerefOf (Index (Arg0, 0x02)))
            TRY0 (Local0, Arg3, DerefOf (Index (Arg0, 0x03)))
            TRY0 (Local0, Arg4, DerefOf (Index (Arg0, 0x04)))
        }

        Method (IFDD, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                IDX1,   8, 
                DTA1,   8
            }

            IndexField (IDX1, DTA1, ByteAcc, NoLock, Preserve)
            {
                    ,   4, 
                RE10,   1, 
                RE11,   1, 
                RE12,   3, 
                RE13,   3
            }

            OUTP ("Check IndexField implementation ByteAcc 4,1-1-3-3")
            Store (Package (0x05)
                {
                    0xA5A5A5A5, 
                    Package (0x03)
                    {
                        0x00, 
                        0x00, 
                        0xA5A5A500
                    }, 

                    Package (0x03)
                    {
                        0x01, 
                        0x01, 
                        0xA5A5A500
                    }, 

                    Package (0x03)
                    {
                        0x02, 
                        0x06, 
                        0xA5A5A501
                    }, 

                    Package (0x03)
                    {
                        0x03, 
                        0x02, 
                        0xA5A5A501
                    }
                }, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x96, Index (DerefOf (Index (Local0, 0x03)), 0x01))
            }

            TRY4 (Local0, RefOf (RE10), RefOf (RE11), RefOf (RE12), RefOf (RE13))
            Store (Package (0x05)
                {
                    0x5A5A5A5A, 
                    Package (0x03)
                    {
                        0x04, 
                        0x01, 
                        0x5A5A5A00
                    }, 

                    Package (0x03)
                    {
                        0x05, 
                        0x00, 
                        0x5A5A5A00
                    }, 

                    Package (0x03)
                    {
                        0x06, 
                        0x01, 
                        0x5A5A5A01
                    }, 

                    Package (0x03)
                    {
                        0x07, 
                        0x05, 
                        0x5A5A5A01
                    }
                }, Local0)
            If (LAnd (ABUU, LNot (Q00A)))
            {
                Store (0x0169, Index (DerefOf (Index (Local0, 0x03)), 0x01))
            }

            TRY4 (Local0, RefOf (RE10), RefOf (RE11), RefOf (RE12), RefOf (RE13))
        }

        Method (IFDE, 0, Serialized)
        {
            Field (OPR0, WordAcc, NoLock, Preserve)
            {
                IDX1,   16, 
                DTA1,   16
            }

            IndexField (IDX1, DTA1, WordAcc, NoLock, Preserve)
            {
                    ,   4, 
                RE10,   1, 
                RE11,   1, 
                RE12,   3, 
                RE13,   3
            }

            OUTP ("Check IndexField implementation WordAcc 4,1-1-3-3")
            Store (Package (0x05)
                {
                    0xA5A5A5A5, 
                    Package (0x03)
                    {
                        0x08, 
                        0x00, 
                        0xA5A50000
                    }, 

                    Package (0x03)
                    {
                        0x09, 
                        0x01, 
                        0xA5A50000
                    }, 

                    Package (0x03)
                    {
                        0x0A, 
                        0x06, 
                        0xA5A50000
                    }, 

                    Package (0x03)
                    {
                        0x0B, 
                        0x02, 
                        0xA5A50000
                    }
                }, Local0)
            TRY4 (Local0, RefOf (RE10), RefOf (RE11), RefOf (RE12), RefOf (RE13))
            Store (Package (0x05)
                {
                    0x5A5A5A5A, 
                    Package (0x03)
                    {
                        0x0C, 
                        0x01, 
                        0x5A5A0000
                    }, 

                    Package (0x03)
                    {
                        0x0D, 
                        0x00, 
                        0x5A5A0000
                    }, 

                    Package (0x03)
                    {
                        0x0E, 
                        0x01, 
                        0x5A5A0000
                    }, 

                    Package (0x03)
                    {
                        0x0F, 
                        0x05, 
                        0x5A5A0000
                    }
                }, Local0)
            TRY4 (Local0, RefOf (RE10), RefOf (RE11), RefOf (RE12), RefOf (RE13))
        }

        Method (IFDF, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                IDX1,   8, 
                DTA1,   8
            }

            IndexField (IDX1, DTA1, ByteAcc, NoLock, Preserve)
            {
                    ,   7, 
                RE10,   1, 
                RE11,   1, 
                Offset (0x02), 
                RE12,   4, 
                RE13,   4
            }

            OUTP ("Check IndexField implementation ByteAcc 7,1-1,O2,4-4")
            Store (Package (0x05)
                {
                    0xA5A5A5A5, 
                    Package (0x03)
                    {
                        0x10, 
                        0x01, 
                        0xA5A5A500
                    }, 

                    Package (0x03)
                    {
                        0x11, 
                        0x01, 
                        0xA5A5A501
                    }, 

                    Package (0x03)
                    {
                        0x12, 
                        0x05, 
                        0xA5A5A502
                    }, 

                    Package (0x03)
                    {
                        0x13, 
                        0x0A, 
                        0xA5A5A502
                    }
                }, Local0)
            TRY4 (Local0, RefOf (RE10), RefOf (RE11), RefOf (RE12), RefOf (RE13))
            Store (Package (0x05)
                {
                    0x5A5A5A5A, 
                    Package (0x03)
                    {
                        0x14, 
                        0x00, 
                        0x5A5A5A00
                    }, 

                    Package (0x03)
                    {
                        0x15, 
                        0x00, 
                        0x5A5A5A01
                    }, 

                    Package (0x03)
                    {
                        0x16, 
                        0x0A, 
                        0x5A5A5A02
                    }, 

                    Package (0x03)
                    {
                        0x17, 
                        0x05, 
                        0x5A5A5A02
                    }
                }, Local0)
            TRY4 (Local0, RefOf (RE10), RefOf (RE11), RefOf (RE12), RefOf (RE13))
        }

        CH03 (TS, Z179, 0xEC, 0x0FD6, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                IFDC ()
                IFDD ()
                IFDE ()
                IFDF ()
            }
            Case (0x0D)
            {
                IFDC ()
            }
            Case (0x0E)
            {
                IFDD ()
            }
            Case (0x0F)
            {
                IFDE ()
            }
            Case (0x10)
            {
                IFDF ()
            }

        }

        CH03 (TS, Z179, 0xED, 0x0FE3, 0x00)
    }

    Method (MW27, 1, Serialized)
    {
        Name (TS, "mw27")
        OperationRegion (OPR0, SystemMemory, VMEM, 0x0100)
        Field (OPR0, ByteAcc, NoLock, Preserve)
        {
            TOT0,   32, 
            TOT1,   32
        }

        Method (IFE0, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX0,   16, 
                DTA0,   16
            }

            IndexField (IDX0, DTA0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   6, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   6, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   6, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   6, 
                IDF7,   1
            }

            Method (M000, 5, NotSerialized)
            {
                Store (Arg0, TOT0) /* \MW27.TOT0 */
                Store (DerefOf (Arg1), Local0)
                Store (TOT0, Local1)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x1004, 0x00, 0x00, Local0, Arg3)
                }

                If (LNotEqual (Local1, Arg4))
                {
                    ERR (TS, Z179, 0x1007, 0x00, 0x00, Local1, Arg4)
                }
            }

            OUTP ("Check IndexField implementation: ByteAcc2")
            M000 (0x0001FFFF, RefOf (IDF0), 0x0150, 0x01, 0x00010000)
            M000 (0x0080FFFF, RefOf (IDF1), 0x0152, 0x01, 0x00800000)
            M000 (0x0001FFFF, RefOf (IDF2), 0x0154, 0x01, 0x00010001)
            M000 (0x0080FFFF, RefOf (IDF3), 0x0156, 0x01, 0x00800001)
            M000 (0x0001FFFF, RefOf (IDF4), 0x0158, 0x01, 0x00010002)
            M000 (0x0080FFFF, RefOf (IDF5), 0x015A, 0x01, 0x00800002)
            M000 (0x0001FFFF, RefOf (IDF6), 0x015C, 0x01, 0x00010003)
            M000 (0x0080FFFF, RefOf (IDF7), 0x015E, 0x01, 0x00800003)
        }

        Method (IFE1, 0, Serialized)
        {
            Field (OPR0, WordAcc, NoLock, WriteAsZeros)
            {
                IDX0,   16, 
                DTA0,   16
            }

            IndexField (IDX0, DTA0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   6, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   6, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   6, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   6, 
                IDF7,   1
            }

            Method (M000, 5, NotSerialized)
            {
                Store (Arg0, TOT0) /* \MW27.TOT0 */
                Store (DerefOf (Arg1), Local0)
                Store (TOT0, Local1)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x102A, 0x00, 0x00, Local0, Arg3)
                }

                If (LNotEqual (Local1, Arg4))
                {
                    ERR (TS, Z179, 0x102D, 0x00, 0x00, Local1, Arg4)
                }
            }

            OUTP ("Check IndexField implementation: WordAccByteAcc")
            M000 (0x0001FFFF, RefOf (IDF0), 0x0160, 0x01, 0x00010000)
            M000 (0x0080FFFF, RefOf (IDF1), 0x0162, 0x01, 0x00800000)
            M000 (0x0001FFFF, RefOf (IDF2), 0x0164, 0x01, 0x00010001)
            M000 (0x0080FFFF, RefOf (IDF3), 0x0166, 0x01, 0x00800001)
            M000 (0x0001FFFF, RefOf (IDF4), 0x0168, 0x01, 0x00010002)
            M000 (0x0080FFFF, RefOf (IDF5), 0x016A, 0x01, 0x00800002)
            M000 (0x0001FFFF, RefOf (IDF6), 0x016C, 0x01, 0x00010003)
            M000 (0x0080FFFF, RefOf (IDF7), 0x016E, 0x01, 0x00800003)
        }

        Method (IFE2, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX0,   16, 
                DTA0,   16
            }

            IndexField (IDX0, DTA0, WordAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   6, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   6, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   6, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   6, 
                IDF7,   1
            }

            Method (M000, 5, NotSerialized)
            {
                Store (Arg0, TOT0) /* \MW27.TOT0 */
                Store (DerefOf (Arg1), Local0)
                Store (TOT0, Local1)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x1050, 0x00, 0x00, Local0, Arg3)
                }

                If (LNotEqual (Local1, Arg4))
                {
                    ERR (TS, Z179, 0x1053, 0x00, 0x00, Local1, Arg4)
                }
            }

            OUTP ("Check IndexField implementation: ByteAccWordAcc")
            M000 (0x0001FFFF, RefOf (IDF0), 0x0170, 0x01, 0x00010000)
            M000 (0x0080FFFF, RefOf (IDF1), 0x0172, 0x01, 0x00800000)
            M000 (0x0001FFFF, RefOf (IDF2), 0x0174, 0x00, 0x00010000)
            M000 (0x0080FFFF, RefOf (IDF3), 0x0176, 0x00, 0x00800000)
            M000 (0x0001FFFF, RefOf (IDF4), 0x0178, 0x01, 0x00010002)
            M000 (0x0080FFFF, RefOf (IDF5), 0x017A, 0x01, 0x00800002)
            M000 (0x0001FFFF, RefOf (IDF6), 0x017C, 0x00, 0x00010002)
            M000 (0x0080FFFF, RefOf (IDF7), 0x017E, 0x00, 0x00800002)
        }

        Method (IFE3, 0, Serialized)
        {
            Field (OPR0, WordAcc, NoLock, WriteAsZeros)
            {
                IDX0,   16, 
                DTA0,   16
            }

            IndexField (IDX0, DTA0, WordAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   6, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   6, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   6, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   6, 
                IDF7,   1
            }

            Method (M000, 5, NotSerialized)
            {
                Store (Arg0, TOT0) /* \MW27.TOT0 */
                Store (DerefOf (Arg1), Local0)
                Store (TOT0, Local1)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x1076, 0x00, 0x00, Local0, Arg3)
                }

                If (LNotEqual (Local1, Arg4))
                {
                    ERR (TS, Z179, 0x1079, 0x00, 0x00, Local1, Arg4)
                }
            }

            OUTP ("Check IndexField implementation: WordAcc2")
            M000 (0x0001FFFF, RefOf (IDF0), 0x0180, 0x01, 0x00010000)
            M000 (0x0080FFFF, RefOf (IDF1), 0x0182, 0x01, 0x00800000)
            M000 (0x0001FFFF, RefOf (IDF2), 0x0184, 0x00, 0x00010000)
            M000 (0x0080FFFF, RefOf (IDF3), 0x0186, 0x00, 0x00800000)
            M000 (0x0001FFFF, RefOf (IDF4), 0x0188, 0x01, 0x00010002)
            M000 (0x0080FFFF, RefOf (IDF5), 0x018A, 0x01, 0x00800002)
            M000 (0x0001FFFF, RefOf (IDF6), 0x018C, 0x00, 0x00010002)
            M000 (0x0080FFFF, RefOf (IDF7), 0x018E, 0x00, 0x00800002)
        }

        CH03 (TS, Z179, 0xEE, 0x108A, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                IFE0 ()
                IFE1 ()
                IFE2 ()
                IFE3 ()
            }
            Case (0x11)
            {
                IFE0 ()
            }
            Case (0x12)
            {
                IFE1 ()
            }
            Case (0x13)
            {
                IFE2 ()
            }
            Case (0x14)
            {
                IFE3 ()
            }

        }

        CH03 (TS, Z179, 0xEF, 0x1097, 0x00)
    }

    Method (MX27, 1, Serialized)
    {
        Name (TS, "mx27")
        OperationRegion (OPR0, SystemMemory, VMEM, 0x0100)
        Field (OPR0, ByteAcc, NoLock, Preserve)
        {
            TOT0,   32, 
            TOT1,   32
        }

        Method (IFE4, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX0,   16, 
                DTA0,   4
            }

            IndexField (IDX0, DTA0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   6, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   6, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   6, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   6, 
                IDF7,   1
            }

            Method (M000, 5, NotSerialized)
            {
                Store (Arg0, TOT0) /* \MX27.TOT0 */
                Store (DerefOf (Arg1), Local0)
                Store (TOT0, Local1)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x10B8, 0x00, 0x00, Local0, Arg3)
                }

                If (LNotEqual (Local1, Arg4))
                {
                    ERR (TS, Z179, 0x10BB, 0x00, 0x00, Local1, Arg4)
                }
            }

            OUTP ("Check IndexField implementation: ByteAcc2, dta0:4")
            M000 (0x0001FFFF, RefOf (IDF0), 0x0190, 0x01, 0x00010000)
            M000 (0xFFFFFFFF, RefOf (IDF1), 0x0192, 0x00, 0xFFFF0000)
            M000 (0x0001FFFF, RefOf (IDF2), 0x0194, 0x01, 0x00010001)
            M000 (0xFFFFFFFF, RefOf (IDF3), 0x0196, 0x00, 0xFFFF0001)
            M000 (0x0001FFFF, RefOf (IDF4), 0x0198, 0x01, 0x00010002)
            M000 (0xFFFFFFFF, RefOf (IDF5), 0x019A, 0x00, 0xFFFF0002)
            M000 (0x0001FFFF, RefOf (IDF6), 0x019C, 0x01, 0x00010003)
            M000 (0xFFFFFFFF, RefOf (IDF7), 0x019E, 0x00, 0xFFFF0003)
        }

        Method (IFE5, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX0,   8, 
                DTA0,   8
            }

            IndexField (IDX0, DTA0, WordAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   6, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   6, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   6, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   6, 
                IDF7,   1
            }

            Method (M000, 5, NotSerialized)
            {
                Store (Arg0, TOT0) /* \MX27.TOT0 */
                Store (DerefOf (Arg1), Local0)
                Store (TOT0, Local1)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x10DE, 0x00, 0x00, Local0, Arg3)
                }

                If (LNotEqual (Local1, Arg4))
                {
                    ERR (TS, Z179, 0x10E1, 0x00, 0x00, Local1, Arg4)
                }
            }

            OUTP ("Check IndexField implementation: ByteAccWordAcc, idx0, 8, dta0, 8")
            M000 (0x01FF, RefOf (IDF0), 0x01A0, 0x01, 0x0100)
            M000 (0x80FF, RefOf (IDF1), 0x01A2, 0x01, 0x8000)
            M000 (0xFFFFFFFF, RefOf (IDF2), 0x01A4, 0x00, 0xFFFFFF00)
            M000 (0xFFFFFFFF, RefOf (IDF3), 0x01A6, 0x00, 0xFFFFFF00)
            M000 (0x01FF, RefOf (IDF4), 0x01A8, 0x01, 0x0102)
            M000 (0x80FF, RefOf (IDF5), 0x01AA, 0x01, 0x8002)
            M000 (0xFFFFFFFF, RefOf (IDF6), 0x01AC, 0x00, 0xFFFFFF02)
            M000 (0xFFFFFFFF, RefOf (IDF7), 0x01AE, 0x00, 0xFFFFFF02)
        }

        Method (IFE6, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX0,   32, 
                DTA0,   32
            }

            IndexField (IDX0, DTA0, WordAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   6, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   6, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   6, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   6, 
                IDF7,   1
            }

            Method (M000, 6, NotSerialized)
            {
                Store (0xFFFFFFFF, TOT0) /* \MX27.TOT0 */
                Store (Arg0, TOT1) /* \MX27.TOT1 */
                Store (DerefOf (Arg1), Local0)
                Store (TOT1, Local1)
                Store (TOT0, Local2)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x1106, 0x00, 0x00, Local0, Arg3)
                }

                If (LNotEqual (Local1, Arg4))
                {
                    ERR (TS, Z179, 0x1109, 0x00, 0x00, Local1, Arg4)
                }

                If (LNotEqual (Local2, Arg5))
                {
                    ERR (TS, Z179, 0x110C, 0x00, 0x00, Local2, Arg5)
                }
            }

            OUTP ("Check IndexField implementation: ByteAccWordAcc, idx0, 32, dta0, 32")
            M000 (0x01, RefOf (IDF0), 0x01B0, 0x01, 0x01, 0x00)
            M000 (0x80, RefOf (IDF1), 0x01B3, 0x01, 0x80, 0x00)
            M000 (0x0100, RefOf (IDF2), 0x01B6, 0x01, 0x0100, 0x00)
            M000 (0x8000, RefOf (IDF3), 0x01B9, 0x01, 0x8000, 0x00)
            M000 (0x01, RefOf (IDF4), 0x01BC, 0x01, 0x01, 0x02)
            M000 (0x80, RefOf (IDF5), 0x01BF, 0x01, 0x80, 0x02)
            M000 (0x0100, RefOf (IDF6), 0x01C2, 0x01, 0x0100, 0x02)
            M000 (0x8000, RefOf (IDF7), 0x01C5, 0x01, 0x8000, 0x02)
        }

        Method (IFE7, 0, Serialized)
        {
            Field (OPR0, DWordAcc, NoLock, WriteAsZeros)
            {
                IDX0,   32, 
                DTA0,   32
            }

            IndexField (IDX0, DTA0, WordAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   6, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   6, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   6, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   6, 
                IDF7,   1
            }

            Method (M000, 6, NotSerialized)
            {
                Store (0xFFFFFFFF, TOT0) /* \MX27.TOT0 */
                Store (Arg0, TOT1) /* \MX27.TOT1 */
                Store (DerefOf (Arg1), Local0)
                Store (TOT1, Local1)
                Store (TOT0, Local2)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x1131, 0x00, 0x00, Local0, Arg3)
                }

                If (LNotEqual (Local1, Arg4))
                {
                    ERR (TS, Z179, 0x1134, 0x00, 0x00, Local1, Arg4)
                }

                If (LNotEqual (Local2, Arg5))
                {
                    ERR (TS, Z179, 0x1137, 0x00, 0x00, Local2, Arg5)
                }
            }

            OUTP ("Check IndexField implementation: DWordAccWordAcc, idx0, 32, dta0, 32")
            M000 (0x01, RefOf (IDF0), 0x01F0, 0x01, 0x01, 0x00)
            M000 (0x80, RefOf (IDF1), 0x01F3, 0x01, 0x80, 0x00)
            M000 (0x0100, RefOf (IDF2), 0x01F6, 0x01, 0x0100, 0x00)
            M000 (0x8000, RefOf (IDF3), 0x01F9, 0x01, 0x8000, 0x00)
            M000 (0x01, RefOf (IDF4), 0x01FC, 0x01, 0x01, 0x02)
            M000 (0x80, RefOf (IDF5), 0x01FF, 0x01, 0x80, 0x02)
            M000 (0x0100, RefOf (IDF6), 0x0202, 0x01, 0x0100, 0x02)
            M000 (0x8000, RefOf (IDF7), 0x0215, 0x01, 0x8000, 0x02)
        }

        CH03 (TS, Z179, 0x01C8, 0x1147, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                IFE4 ()
                IFE5 ()
                IFE6 ()
                IFE7 ()
            }
            Case (0x15)
            {
                IFE4 ()
            }
            Case (0x16)
            {
                IFE5 ()
            }
            Case (0x17)
            {
                IFE6 ()
            }
            Case (0x18)
            {
                IFE7 ()
            }

        }

        CH03 (TS, Z179, 0x01C9, 0x1154, 0x00)
    }

    Method (MY27, 1, Serialized)
    {
        Name (TS, "my27")
        OperationRegion (OPR0, SystemMemory, VMEM, 0x0100)
        Field (OPR0, ByteAcc, NoLock, Preserve)
        {
            TOT0,   32, 
            TOT1,   32
        }

        Method (IFE8, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX0,   32, 
                DTA0,   32
            }

            IndexField (IDX0, DTA0, DWordAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   14, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   14, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   14, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   14, 
                IDF7,   1
            }

            Method (M000, 6, NotSerialized)
            {
                Store (0xFFFFFFFF, TOT0) /* \MY27.TOT0 */
                Store (Arg0, TOT1) /* \MY27.TOT1 */
                Store (DerefOf (Arg1), Local0)
                Store (TOT1, Local1)
                Store (TOT0, Local2)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x1177, 0x00, 0x00, Local0, Arg3)
                }

                If (LNotEqual (Local1, Arg4))
                {
                    ERR (TS, Z179, 0x117A, 0x00, 0x00, Local1, Arg4)
                }

                If (LNotEqual (Local2, Arg5))
                {
                    ERR (TS, Z179, 0x117D, 0x00, 0x00, Local2, Arg5)
                }
            }

            OUTP ("Check IndexField implementation: ByteAccDWordAcc, idx0, 32, dta0, 32")
            M000 (0x01, RefOf (IDF0), 0x0200, 0x01, 0x01, 0x00)
            M000 (0x8000, RefOf (IDF1), 0x0203, 0x01, 0x8000, 0x00)
            M000 (0x00010000, RefOf (IDF2), 0x0206, 0x01, 0x00010000, 0x00)
            M000 (0x80000000, RefOf (IDF3), 0x0209, 0x01, 0x80000000, 0x00)
            M000 (0x01, RefOf (IDF4), 0x020C, 0x01, 0x01, 0x04)
            M000 (0x8000, RefOf (IDF5), 0x020F, 0x01, 0x8000, 0x04)
            M000 (0x00010000, RefOf (IDF6), 0x0212, 0x01, 0x00010000, 0x04)
            M000 (0x80000000, RefOf (IDF7), 0x0215, 0x01, 0x80000000, 0x04)
        }

        Method (IFE9, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX0,   32, 
                DTA0,   32
            }

            IndexField (IDX0, DTA0, QWordAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   14, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   14, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   14, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   14, 
                IDF7,   1
            }

            Method (M000, 6, NotSerialized)
            {
                Store (0xFFFFFFFF, TOT0) /* \MY27.TOT0 */
                Store (Arg0, TOT1) /* \MY27.TOT1 */
                Store (DerefOf (Arg1), Local0)
                Store (TOT1, Local1)
                Store (TOT0, Local2)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x11A2, 0x00, 0x00, Local0, Arg3)
                }

                If (LNotEqual (Local1, Arg4))
                {
                    ERR (TS, Z179, 0x11A5, 0x00, 0x00, Local1, Arg4)
                }

                If (LNotEqual (Local2, Arg5))
                {
                    ERR (TS, Z179, 0x11A8, 0x00, 0x00, Local2, Arg5)
                }
            }

            OUTP ("Check IndexField implementation: ByteAccQWordAcc, idx0, 32, dta0, 32")
            M000 (0x01, RefOf (IDF0), 0x0220, 0x01, 0x01, 0x00)
            M000 (0x8000, RefOf (IDF1), 0x0223, 0x01, 0x8000, 0x00)
            M000 (0x00010000, RefOf (IDF2), 0x0226, 0x01, 0x00010000, 0x00)
            M000 (0x80000000, RefOf (IDF3), 0x0229, 0x01, 0x80000000, 0x00)
            M000 (0xFFFFFFFF, RefOf (IDF4), 0x022C, 0x00, 0xFFFFFFFF, 0x00)
            M000 (0xFFFFFFFF, RefOf (IDF5), 0x022F, 0x00, 0xFFFFFFFF, 0x00)
            M000 (0xFFFFFFFF, RefOf (IDF6), 0x0232, 0x00, 0xFFFFFFFF, 0x00)
            M000 (0xFFFFFFFF, RefOf (IDF7), 0x0235, 0x00, 0xFFFFFFFF, 0x00)
        }

        Method (IFEA, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX0,   16, 
                DTA0,   16
            }

            IndexField (IDX0, DTA0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   6, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   6, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   6, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   6, 
                IDF7,   1
            }

            Method (M000, 4, Serialized)
            {
                Store (Arg0, TOT0) /* \MY27.TOT0 */
                Switch (ToInteger (Arg1))
                {
                    Case (0x00)
                    {
                        Store (0x01, IDF0) /* \MY27.IFEA.IDF0 */
                    }
                    Case (0x01)
                    {
                        Store (0x01, IDF1) /* \MY27.IFEA.IDF1 */
                    }
                    Case (0x02)
                    {
                        Store (0x01, IDF2) /* \MY27.IFEA.IDF2 */
                    }
                    Case (0x03)
                    {
                        Store (0x01, IDF3) /* \MY27.IFEA.IDF3 */
                    }
                    Case (0x04)
                    {
                        Store (0x01, IDF4) /* \MY27.IFEA.IDF4 */
                    }
                    Case (0x05)
                    {
                        Store (0x01, IDF5) /* \MY27.IFEA.IDF5 */
                    }
                    Case (0x06)
                    {
                        Store (0x01, IDF6) /* \MY27.IFEA.IDF6 */
                    }
                    Case (0x07)
                    {
                        Store (0x01, IDF7) /* \MY27.IFEA.IDF7 */
                    }

                }

                Store (TOT0, Local0)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x11D4, 0x00, 0x00, Local0, Arg3)
                }
            }

            OUTP ("Check IndexField implementation: ByteAcc2, Store")
            M000 (0xFFFFFFFF, 0x00, 0x0240, 0x00010000)
            M000 (0xFFFFFFFF, 0x01, 0x0241, 0x00800000)
            M000 (0xFFFFFFFF, 0x02, 0x0242, 0x00010001)
            M000 (0xFFFFFFFF, 0x03, 0x0243, 0x00800001)
            M000 (0xFFFFFFFF, 0x04, 0x0244, 0x00010002)
            M000 (0xFFFFFFFF, 0x05, 0x0245, 0x00800002)
            M000 (0xFFFFFFFF, 0x06, 0x0246, 0x00010003)
            M000 (0xFFFFFFFF, 0x07, 0x0247, 0x00800003)
        }

        Method (IFEB, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX0,   16, 
                DTA0,   16
            }

            IndexField (IDX0, DTA0, WordAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   6, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   6, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   6, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   6, 
                IDF7,   1
            }

            Method (M000, 4, Serialized)
            {
                Store (Arg0, TOT0) /* \MY27.TOT0 */
                Switch (ToInteger (Arg1))
                {
                    Case (0x00)
                    {
                        Store (0x01, IDF0) /* \MY27.IFEB.IDF0 */
                    }
                    Case (0x01)
                    {
                        Store (0x01, IDF1) /* \MY27.IFEB.IDF1 */
                    }
                    Case (0x02)
                    {
                        Store (0x01, IDF2) /* \MY27.IFEB.IDF2 */
                    }
                    Case (0x03)
                    {
                        Store (0x01, IDF3) /* \MY27.IFEB.IDF3 */
                    }
                    Case (0x04)
                    {
                        Store (0x01, IDF4) /* \MY27.IFEB.IDF4 */
                    }
                    Case (0x05)
                    {
                        Store (0x01, IDF5) /* \MY27.IFEB.IDF5 */
                    }
                    Case (0x06)
                    {
                        Store (0x01, IDF6) /* \MY27.IFEB.IDF6 */
                    }
                    Case (0x07)
                    {
                        Store (0x01, IDF7) /* \MY27.IFEB.IDF7 */
                    }

                }

                Store (TOT0, Local0)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x1200, 0x00, 0x00, Local0, Arg3)
                }
            }

            OUTP ("Check IndexField implementation: ByteAccWordAcc, Store")
            M000 (0xFFFFFFFF, 0x00, 0x0248, 0x00010000)
            M000 (0xFFFFFFFF, 0x01, 0x0249, 0x00800000)
            M000 (0xFFFFFFFF, 0x02, 0x024A, 0x01000000)
            M000 (0xFFFFFFFF, 0x03, 0x024B, 0x80000000)
            M000 (0xFFFFFFFF, 0x04, 0x024C, 0x00010002)
            M000 (0xFFFFFFFF, 0x05, 0x024D, 0x00800002)
            M000 (0xFFFFFFFF, 0x06, 0x024E, 0x01000002)
            M000 (0xFFFFFFFF, 0x07, 0x024F, 0x80000002)
        }

        CH03 (TS, Z179, 0x01CA, 0x1210, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                IFE8 ()
                If (ABUU){}
                Else
                {
                    IFE9 ()
                }

                If (ABUU){}
                Else
                {
                    IFEA ()
                }

                If (ABUU){}
                Else
                {
                    IFEB ()
                }
            }
            Case (0x19)
            {
                IFE8 ()
            }
            Case (0x1A)
            {
                IFE9 ()
            }
            Case (0x1B)
            {
                IFEA ()
            }
            Case (0x1C)
            {
                IFEB ()
            }

        }

        CH03 (TS, Z179, 0x01CB, 0x1229, 0x00)
    }

    Method (MZ27, 1, Serialized)
    {
        Name (TS, "mz27")
        OperationRegion (OPR0, SystemMemory, VMEM, 0x0100)
        Field (OPR0, ByteAcc, NoLock, Preserve)
        {
            TOT0,   32, 
            TOT1,   32
        }

        Method (IFEC, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX0,   32, 
                DTA0,   32
            }

            IndexField (IDX0, DTA0, DWordAcc, NoLock, WriteAsZeros)
            {
                IDF0,   1, 
                    ,   14, 
                IDF1,   1, 
                IDF2,   1, 
                    ,   14, 
                IDF3,   1, 
                IDF4,   1, 
                    ,   14, 
                IDF5,   1, 
                IDF6,   1, 
                    ,   14, 
                IDF7,   1
            }

            Method (M000, 5, Serialized)
            {
                Store (0xFFFFFFFF, TOT0) /* \MZ27.TOT0 */
                Store (Arg0, TOT1) /* \MZ27.TOT1 */
                Switch (ToInteger (Arg1))
                {
                    Case (0x00)
                    {
                        Store (0x01, IDF0) /* \MZ27.IFEC.IDF0 */
                    }
                    Case (0x01)
                    {
                        Store (0x01, IDF1) /* \MZ27.IFEC.IDF1 */
                    }
                    Case (0x02)
                    {
                        Store (0x01, IDF2) /* \MZ27.IFEC.IDF2 */
                    }
                    Case (0x03)
                    {
                        Store (0x01, IDF3) /* \MZ27.IFEC.IDF3 */
                    }
                    Case (0x04)
                    {
                        Store (0x01, IDF4) /* \MZ27.IFEC.IDF4 */
                    }
                    Case (0x05)
                    {
                        Store (0x01, IDF5) /* \MZ27.IFEC.IDF5 */
                    }
                    Case (0x06)
                    {
                        Store (0x01, IDF6) /* \MZ27.IFEC.IDF6 */
                    }
                    Case (0x07)
                    {
                        Store (0x01, IDF7) /* \MZ27.IFEC.IDF7 */
                    }

                }

                Store (TOT1, Local0)
                Store (TOT0, Local1)
                If (LNotEqual (Local0, Arg3))
                {
                    ERR (TS, Z179, 0x1255, 0x00, 0x00, Local0, Arg3)
                }

                If (LNotEqual (Local1, Arg4))
                {
                    ERR (TS, Z179, 0x1258, 0x00, 0x00, Local1, Arg4)
                }
            }

            OUTP ("Check IndexField implementation: ByteAccDWordAcc, Store")
            M000 (0xFFFFFFFF, 0x00, 0x0250, 0x01, 0x00)
            M000 (0xFFFFFFFF, 0x01, 0x0252, 0x8000, 0x00)
            M000 (0xFFFFFFFF, 0x02, 0x0254, 0x00010000, 0x00)
            M000 (0xFFFFFFFF, 0x03, 0x0256, 0x80000000, 0x00)
            M000 (0xFFFFFFFF, 0x04, 0x0258, 0x01, 0x04)
            M000 (0xFFFFFFFF, 0x05, 0x025A, 0x8000, 0x04)
            M000 (0xFFFFFFFF, 0x06, 0x025C, 0x00010000, 0x04)
            M000 (0xFFFFFFFF, 0x07, 0x025E, 0x80000000, 0x04)
        }

        Method (IFED, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX0,   8, 
                DTA0,   24
            }

            IndexField (IDX0, DTA0, ByteAcc, NoLock, WriteAsZeros)
            {
                    ,   15, 
                IDF0,   1
            }

            OUTP ("Check IndexField implementation: dta wider than idf Access width")
            Store (0x03FF, IDF0) /* \MZ27.IFED.IDF0 */
            Store (TOT0, Local0)
            If (LNotEqual (Local0, 0x8001))
            {
                ERR (TS, Z179, 0x1279, 0x00, 0x00, Local0, 0x8001)
            }
        }

        Method (IFEE, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX0,   8, 
                DTA0,   24
            }

            IndexField (IDX0, DTA0, ByteAcc, NoLock, WriteAsZeros)
            {
                    ,   7, 
                IDF0,   1
            }

            OUTP ("Check IndexField implementation: dta wider than idf Access width 2")
            Store (0xFF, IDF0) /* \MZ27.IFEE.IDF0 */
            Store (TOT0, Local0)
            If (LNotEqual (Local0, 0x8000))
            {
                ERR (TS, Z179, 0x128E, 0x00, 0x00, Local0, 0x8000)
            }
        }

        Method (IFEF, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, WriteAsZeros)
            {
                IDX1,   8, 
                DTA1,   8
            }

            IndexField (IDX1, DTA1, ByteAcc, NoLock, WriteAsZeros)
            {
                    ,   2, 
                RE10,   6, 
                    ,   3, 
                RE11,   5, 
                    ,   4, 
                RE12,   4, 
                    ,   5, 
                RE13,   3
            }

            Method (TRY0, 3, Serialized)
            {
                Store (Zero, TOT0) /* \MZ27.TOT0 */
                Switch (ToInteger (Arg0))
                {
                    Case (0x00)
                    {
                        Store (Ones, ^RE10) /* \MZ27.IFEF.RE10 */
                    }
                    Case (0x01)
                    {
                        Store (Ones, ^RE11) /* \MZ27.IFEF.RE11 */
                    }
                    Case (0x02)
                    {
                        Store (Ones, ^RE12) /* \MZ27.IFEF.RE12 */
                    }
                    Case (0x03)
                    {
                        Store (Ones, ^RE13) /* \MZ27.IFEF.RE13 */
                    }

                }

                Store (IDX1, Local0)
                Store (DTA1, Local1)
                Multiply (Arg0, 0x02, Local2)
                If (LNotEqual (Local0, Arg1))
                {
                    ERR (TS, Z179, 0x12B3, 0x00, 0x00, Local0, Arg1)
                }

                If (LNotEqual (Local1, Arg2))
                {
                    ERR (TS, Z179, 0x12B6, 0x00, 0x00, Local1, Arg2)
                }
            }

            OUTP ("Check IndexField ByteAcc Ones write (:2)6-(:3)5-(:4)4-(:5)3")
            TRY0 (0x00, 0x00, 0xFC)
            TRY0 (0x01, 0x01, 0xF8)
            TRY0 (0x02, 0x02, 0xF0)
            TRY0 (0x03, 0x03, 0xE0)
        }

        CH03 (TS, Z179, 0x01CC, 0x12C2, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                IFEC ()
                IFED ()
                IFEE ()
                IFEF ()
            }
            Case (0x1D)
            {
                IFEC ()
            }
            Case (0x1E)
            {
                IFED ()
            }
            Case (0x1F)
            {
                IFEE ()
            }
            Case (0x20)
            {
                IFEF ()
            }

        }

        CH03 (TS, Z179, 0x01CD, 0x12CF, 0x00)
    }

    Method (AIFD, 0, NotSerialized)
    {
        IIN0 ()
        MS27 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BIFD, 0, NotSerialized)
    {
        IIN0 ()
        MS27 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CIFD, 0, NotSerialized)
    {
        IIN0 ()
        MS27 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DIFD, 0, NotSerialized)
    {
        IIN0 ()
        MS27 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (SIFD, 0, NotSerialized)
    {
        IIN0 ()
        MS27 (0x00)
        Return (POUT) /* \POUT */
    }

    Method (EIFD, 0, NotSerialized)
    {
        IIN0 ()
        MT27 (0x05)
        Return (POUT) /* \POUT */
    }

    Method (FIFD, 0, NotSerialized)
    {
        IIN0 ()
        MT27 (0x06)
        Return (POUT) /* \POUT */
    }

    Method (GIFD, 0, NotSerialized)
    {
        IIN0 ()
        MT27 (0x07)
        Return (POUT) /* \POUT */
    }

    Method (HIFD, 0, NotSerialized)
    {
        IIN0 ()
        MT27 (0x08)
        Return (POUT) /* \POUT */
    }

    Method (TIFD, 0, NotSerialized)
    {
        IIN0 ()
        MT27 (0x00)
        Return (POUT) /* \POUT */
    }

    Method (IIFD, 0, NotSerialized)
    {
        IIN0 ()
        MU27 (0x09)
        Return (POUT) /* \POUT */
    }

    Method (JIFD, 0, NotSerialized)
    {
        IIN0 ()
        MU27 (0x0A)
        Return (POUT) /* \POUT */
    }

    Method (KIFD, 0, NotSerialized)
    {
        IIN0 ()
        MU27 (0x0B)
        Return (POUT) /* \POUT */
    }

    Method (LIFD, 0, NotSerialized)
    {
        IIN0 ()
        MU27 (0x0C)
        Return (POUT) /* \POUT */
    }

    Method (UIFD, 0, NotSerialized)
    {
        IIN0 ()
        MU27 (0x00)
        Return (POUT) /* \POUT */
    }

    Method (MIFD, 0, NotSerialized)
    {
        IIN0 ()
        MV27 (0x0D)
        Return (POUT) /* \POUT */
    }

    Method (NIFD, 0, NotSerialized)
    {
        IIN0 ()
        MV27 (0x0E)
        Return (POUT) /* \POUT */
    }

    Method (OIFD, 0, NotSerialized)
    {
        IIN0 ()
        MV27 (0x0F)
        Return (POUT) /* \POUT */
    }

    Method (PIFD, 0, NotSerialized)
    {
        IIN0 ()
        MV27 (0x10)
        Return (POUT) /* \POUT */
    }

    Method (VIFD, 0, NotSerialized)
    {
        IIN0 ()
        MV27 (0x00)
        Return (POUT) /* \POUT */
    }

    Method (AIFE, 0, NotSerialized)
    {
        IIN0 ()
        MW27 (0x11)
        Return (POUT) /* \POUT */
    }

    Method (BIFE, 0, NotSerialized)
    {
        IIN0 ()
        MW27 (0x12)
        Return (POUT) /* \POUT */
    }

    Method (CIFE, 0, NotSerialized)
    {
        IIN0 ()
        MW27 (0x13)
        Return (POUT) /* \POUT */
    }

    Method (DIFE, 0, NotSerialized)
    {
        IIN0 ()
        MW27 (0x14)
        Return (POUT) /* \POUT */
    }

    Method (WIFE, 0, NotSerialized)
    {
        IIN0 ()
        MW27 (0x00)
        Return (POUT) /* \POUT */
    }

    Method (EIFE, 0, NotSerialized)
    {
        IIN0 ()
        MX27 (0x15)
        Return (POUT) /* \POUT */
    }

    Method (FIFE, 0, NotSerialized)
    {
        IIN0 ()
        MX27 (0x16)
        Return (POUT) /* \POUT */
    }

    Method (GIFE, 0, NotSerialized)
    {
        IIN0 ()
        MX27 (0x17)
        Return (POUT) /* \POUT */
    }

    Method (HIFE, 0, NotSerialized)
    {
        IIN0 ()
        MX27 (0x18)
        Return (POUT) /* \POUT */
    }

    Method (XIFE, 0, NotSerialized)
    {
        IIN0 ()
        MX27 (0x00)
        Return (POUT) /* \POUT */
    }

    Method (IIFE, 0, NotSerialized)
    {
        IIN0 ()
        MY27 (0x19)
        Return (POUT) /* \POUT */
    }

    Method (JIFE, 0, NotSerialized)
    {
        IIN0 ()
        MY27 (0x1A)
        Return (POUT) /* \POUT */
    }

    Method (KIFE, 0, NotSerialized)
    {
        IIN0 ()
        MY27 (0x1B)
        Return (POUT) /* \POUT */
    }

    Method (LIFE, 0, NotSerialized)
    {
        IIN0 ()
        MY27 (0x1C)
        Return (POUT) /* \POUT */
    }

    Method (YIFE, 0, NotSerialized)
    {
        IIN0 ()
        MY27 (0x00)
        Return (POUT) /* \POUT */
    }

    Method (MIFE, 0, NotSerialized)
    {
        IIN0 ()
        MZ27 (0x1D)
        Return (POUT) /* \POUT */
    }

    Method (NIFE, 0, NotSerialized)
    {
        IIN0 ()
        MZ27 (0x1E)
        Return (POUT) /* \POUT */
    }

    Method (OIFE, 0, NotSerialized)
    {
        IIN0 ()
        MZ27 (0x1F)
        Return (POUT) /* \POUT */
    }

    Method (PIFE, 0, NotSerialized)
    {
        IIN0 ()
        MZ27 (0x20)
        Return (POUT) /* \POUT */
    }

    Method (ZIFE, 0, NotSerialized)
    {
        IIN0 ()
        MZ27 (0x00)
        Return (POUT) /* \POUT */
    }

    Method (MS28, 0, Serialized)
    {
        Name (TS, "ms28")
        OperationRegion (OPR0, SystemMemory, 0x00, 0x0100)
        Field (OPR0, ByteAcc, NoLock, Preserve)
        {
            TOT0,   32, 
            TOT1,   32
        }

        Method (BFD0, 0, Serialized)
        {
            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                BNK0,   8
            }

            Field (OPR0, ByteAcc, NoLock, Preserve)
            {
                TOT0,   80
            }

            BankField (OPR0, BNK0, 0x00
, ByteAcc, NoLock, Preserve)
            {
                Offset (0x08), 
                BF00,   8
            }

            BankField (OPR0, BNK0, 0x01
, ByteAcc, NoLock, Preserve)
            {
                Offset (0x09), 
                BF01,   8
            }

            OUTP ("Check BankField implementation")
            Store (0x00, BNK0) /* \MS28.BFD0.BNK0 */
            If (LNotEqual (BNK0, 0x00))
            {
                ERR (TS, Z179, 0x1325, 0x00, 0x00, BNK0, 0x00)
            }

            Store (0x87, BF00) /* \MS28.BFD0.BF00 */
            If (LNotEqual (BNK0, 0x00))
            {
                ERR (TS, Z179, 0x132A, 0x00, 0x00, BNK0, 0x00)
            }

            If (LNotEqual (BF00, 0x87))
            {
                ERR (TS, Z179, 0x132E, 0x00, 0x00, BF00, 0x87)
            }

            Store (0x01, BNK0) /* \MS28.BFD0.BNK0 */
            If (LNotEqual (BNK0, 0x01))
            {
                ERR (TS, Z179, 0x1335, 0x00, 0x00, BNK0, 0x01)
            }

            Store (0x96, BF01) /* \MS28.BFD0.BF01 */
            If (LNotEqual (BNK0, 0x01))
            {
                ERR (TS, Z179, 0x133B, 0x00, 0x00, BNK0, 0x01)
            }

            If (LNotEqual (BF01, 0x96))
            {
                ERR (TS, Z179, 0x133F, 0x00, 0x00, BF01, 0x96)
            }
        }

        CH03 (TS, Z179, 0x0276, 0x1343, 0x00)
        BFD0 ()
        CH03 (TS, Z179, 0x0277, 0x1345, 0x00)
    }

    Method (ABFD, 0, NotSerialized)
    {
        IIN0 ()
        MS28 ()
        Return (POUT) /* \POUT */
    }

    Mutex (C152, 0x00)
    Mutex (C153, 0x00)
    Mutex (C154, 0x00)
    Mutex (C155, 0x00)
    Mutex (C156, 0x00)
    Mutex (C159, 0x00)
    Method (MS29, 1, Serialized)
    {
        Name (TS, "ms29")
        Method (C157, 1, NotSerialized)
        {
            If (Arg0)
            {
                Store (Acquire (C154, 0xFFFF), Local0)
            }
            Else
            {
                Store (Acquire (C154, 0x0000), Local0)
            }

            Return (Local0)
        }

        Method (C158, 0, NotSerialized)
        {
            Release (C154)
        }

        Method (C160, 0, NotSerialized)
        {
            Release (C152)
        }

        Method (MUT0, 0, NotSerialized)
        {
            OUTP ("Check Release by different ASL Methods")
            C160 ()
            CH04 (TS, 0x00, 0xFF, Z179, 0x1373, 0x00, 0x00)
        }

        Method (MUT1, 0, NotSerialized)
        {
            OUTP ("Check Acquire/Release by different ASL Methods")
            OUTP ("Acquire")
            Store (C157 (0x01), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x137E, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Release")
            C158 ()
        }

        Method (MUT2, 0, NotSerialized)
        {
            OUTP ("Check Acquire/Acquire by the different Method\'s calls")
            OUTP ("Acquire 1")
            Store (C157 (0x01), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x138D, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Acquire 2")
            Store (C157 (0x01), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x1394, 0x00, 0x00, Local0, 0x00)
            }
        }

        Method (MUT3, 0, NotSerialized)
        {
            OUTP ("Check Acquire/Acquire in one Method")
            OUTP ("Acquire 1")
            Store (Acquire (C155, 0xFFFF), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x13A0, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Acquire 2")
            Store (Acquire (C155, 0xFFFF), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x13A8, 0x00, 0x00, Local0, 0x00)
            }
        }

        Method (MUT4, 0, NotSerialized)
        {
            OUTP ("Check Acquire/Release/Release by different ASL Methods")
            OUTP ("Acquire")
            Store (C157 (0x01), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x13B4, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Release 1")
            C158 ()
            OUTP ("Release 2")
            C158 ()
            CH04 (TS, 0x00, 0xFF, Z179, 0x13BD, 0x00, 0x00)
        }

        Method (MUT5, 0, NotSerialized)
        {
            OUTP ("Check Acquire(,0xFFFF)/Acquire(,0) in one Method")
            OUTP ("Acquire( , 0xFFFF) 1")
            Store (Acquire (C156, 0xFFFF), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x13C8, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Acquire( , 0) 2")
            Store (Acquire (C156, 0x0000), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x13CF, 0x00, 0x00, Local0, 0x00)
            }
        }

        Method (MUT6, 0, NotSerialized)
        {
            OUTP ("Check Acquire2/Release2 in one Method")
            OUTP ("Acquire 1")
            Store (Acquire (C153, 0xFFFF), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x13DB, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Acquire 2")
            Store (Acquire (C153, 0xFFFF), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x13E3, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Release 1")
            Release (C153)
            OUTP ("Release 2")
            Release (C153)
        }

        Method (MUT7, 0, NotSerialized)
        {
            OUTP ("Check Acquire2/Release3 in one Method")
            OUTP ("Acquire 1")
            Store (Acquire (C159, 0xFFFF), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x13F5, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Acquire 2")
            Store (Acquire (C159, 0xFFFF), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x13FD, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Release 1")
            Release (C159)
            OUTP ("Release 2")
            Release (C159)
            OUTP ("Release 3")
            Release (C159)
            CH04 (TS, 0x00, 0xFF, Z179, 0x1408, 0x00, 0x00)
        }

        Method (MUT8, 0, NotSerialized)
        {
            OUTP ("Check Acquire2/Release2 in one Method")
            OUTP ("Acquire 1")
            Store (Acquire (C153, 0xFFFF), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x1413, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Acquire 2")
            Store (Acquire (C153, 0xFFFF), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x141B, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Release 1")
            Release (C153)
            OUTP ("Release 2")
            Release (C153)
        }

        Method (MUT9, 0, Serialized)
        {
            Mutex (C159, 0x00)
            OUTP ("Check Acquire2/Release2 in one Method for dynamic Mutex")
            OUTP ("Acquire 1")
            Store (Acquire (C159, 0xFFFF), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x142F, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Acquire 2")
            Store (Acquire (C159, 0xFFFF), Local0)
            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x1437, 0x00, 0x00, Local0, 0x00)
            }

            OUTP ("Release 1")
            Release (C159)
            OUTP ("Release 2")
            Release (C159)
            OUTP ("Release 3")
            Release (C159)
            CH04 (TS, 0x00, 0xFF, Z179, 0x1442, 0x00, 0x00)
        }

        Method (M000, 0, NotSerialized)
        {
            If (ABUU){}
            Else
            {
                MUT0 ()
            }

            MUT1 ()
            If (ABUU){}
            Else
            {
                MUT3 ()
            }

            If (ABUU){}
            Else
            {
                MUT4 ()
            }

            MUT5 ()
            MUT6 ()
            If (ABUU){}
            Else
            {
                MUT7 ()
            }

            MUT8 ()
            If (ABUU){}
            Else
            {
                MUT9 ()
            }
        }

        CH03 (TS, Z179, 0x0292, 0x1468, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                MUT0 ()
            }
            Case (0x02)
            {
                MUT1 ()
            }
            Case (0x03)
            {
                MUT2 ()
            }
            Case (0x04)
            {
                MUT3 ()
            }
            Case (0x05)
            {
                MUT4 ()
            }
            Case (0x06)
            {
                MUT5 ()
            }
            Case (0x07)
            {
                MUT6 ()
            }
            Case (0x08)
            {
                MUT7 ()
            }
            Case (0x09)
            {
                MUT8 ()
            }
            Case (0x0A)
            {
                MUT9 ()
            }

        }

        CH03 (TS, Z179, 0x0293, 0x1476, 0x00)
    }

    Method (AMUT, 0, NotSerialized)
    {
        IIN0 ()
        MS29 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BMUT, 0, NotSerialized)
    {
        IIN0 ()
        MS29 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CMUT, 0, NotSerialized)
    {
        IIN0 ()
        MS29 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DMUT, 0, NotSerialized)
    {
        IIN0 ()
        MS29 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (EMUT, 0, NotSerialized)
    {
        IIN0 ()
        MS29 (0x05)
        Return (POUT) /* \POUT */
    }

    Method (FMUT, 0, NotSerialized)
    {
        IIN0 ()
        MS29 (0x06)
        Return (POUT) /* \POUT */
    }

    Method (GMUT, 0, NotSerialized)
    {
        IIN0 ()
        MS29 (0x07)
        Return (POUT) /* \POUT */
    }

    Method (HMUT, 0, NotSerialized)
    {
        IIN0 ()
        MS29 (0x08)
        Return (POUT) /* \POUT */
    }

    Method (IMUT, 0, NotSerialized)
    {
        IIN0 ()
        MS29 (0x09)
        Return (POUT) /* \POUT */
    }

    Method (JMUT, 0, NotSerialized)
    {
        IIN0 ()
        MS29 (0x0A)
        Return (POUT) /* \POUT */
    }

    Method (KMUT, 0, NotSerialized)
    {
        IIN0 ()
        MS29 (0x00)
        Return (POUT) /* \POUT */
    }

    Method (BCMP, 2, NotSerialized)
    {
        If (ABUU)
        {
            Store (SizeOf (Arg0), Local0)
            If (LNotEqual (Local0, SizeOf (Arg1)))
            {
                Return (0x00)
            }

            Store (SizeOf (Arg0), Local0)
            While (Local0)
            {
                Decrement (Local0)
                Store (DerefOf (Index (Arg0, Local0)), Local1)
                Store (DerefOf (Index (Arg1, Local0)), Local2)
                If (LNotEqual (Local1, Local2))
                {
                    Return (0x00)
                }
            }

            Return (0x01)
        }
        Else
        {
            Return (LEqual (Arg0, Arg1))
        }
    }

    Method (MS2A, 1, Serialized)
    {
        Name (TS, "ms2a")
        Name (F64, 0x00)
        Method (TOB0, 0, NotSerialized)
        {
            Method (M000, 1, Serialized)
            {
                Name (B000, Buffer (0x01)
                {
                     0x3C                                             // <
                })
                Name (B001, Buffer (0x03)
                {
                     0x01, 0x02, 0x03                                 // ...
                })
                If (Arg0)
                {
                    OUTP ("ToBuffer(b001, b000)")
                    ToBuffer (B001, B000) /* \MS2A.TOB0.M000.B000 */
                }
                Else
                {
                    OUTP ("ToBuffer(b000, b001)")
                    ToBuffer (B000, B001) /* \MS2A.TOB0.M000.B001 */
                }

                If (LNot (BCMP (B000, B001)))
                {
                    ERR (TS, Z179, 0x14BB, 0x00, 0x00, B000, B001)
                }
            }

            OUTP ("Check ToBuffer optional store behaves like CopyObject")
            M000 (0x00)
            M000 (0x01)
        }

        Method (TOB1, 0, NotSerialized)
        {
            OUTP ("Check ToBuffer(0x456789ab)")
            Store (ToBuffer (0x456789AB), Local0)
            If (F64)
            {
                Store (Buffer (0x08)
                    {
                         0xAB, 0x89, 0x67, 0x45                           // ..gE
                    }, Local1)
            }
            Else
            {
                Store (Buffer (0x04)
                    {
                         0xAB, 0x89, 0x67, 0x45                           // ..gE
                    }, Local1)
            }

            If (LNot (BCMP (Local1, Local0)))
            {
                ERR (TS, Z179, 0x14CF, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (TOB2, 0, NotSerialized)
        {
            OUTP ("Check ToBuffer(\"456789ab\")")
            Store (ToBuffer ("456789ab"), Local0)
            Store (Buffer (0x09)
                {
                    "456789ab"
                }, Local1)
            If (LNot (BCMP (Local1, Local0)))
            {
                ERR (TS, Z179, 0x14D9, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (TOB3, 0, NotSerialized)
        {
            OUTP ("Check ToBuffer(Buffer(4){0x45, 0x67, 0x89, 0xab})")
            Store (ToBuffer (Buffer (0x04)
                    {
                         0x45, 0x67, 0x89, 0xAB                           // Eg..
                    }), Local0)
            Store (Buffer (0x04)
                {
                     0x45, 0x67, 0x89, 0xAB                           // Eg..
                }, Local1)
            If (LNot (BCMP (Local1, Local0)))
            {
                ERR (TS, Z179, 0x14E3, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (TOB4, 0, NotSerialized)
        {
            OUTP ("Check ToBuffer(0x456789ab, Local0)")
            ToBuffer (0x456789AB, Local0)
            If (F64)
            {
                Store (Buffer (0x08)
                    {
                         0xAB, 0x89, 0x67, 0x45                           // ..gE
                    }, Local1)
            }
            Else
            {
                Store (Buffer (0x04)
                    {
                         0xAB, 0x89, 0x67, 0x45                           // ..gE
                    }, Local1)
            }

            If (LNot (BCMP (Local1, Local0)))
            {
                ERR (TS, Z179, 0x14F1, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (TOB5, 0, NotSerialized)
        {
            OUTP ("Check ToBuffer(\"456789ab\", Local0)")
            ToBuffer ("456789ab", Local0)
            Store (Buffer (0x09)
                {
                    "456789ab"
                }, Local1)
            If (LNot (BCMP (Local1, Local0)))
            {
                ERR (TS, Z179, 0x14FB, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (TOB6, 0, NotSerialized)
        {
            OUTP ("Check ToBuffer(Buffer(4){0x45, 0x67, 0x89, 0xab}, Local0)")
            ToBuffer (Buffer (0x04)
                {
                     0x45, 0x67, 0x89, 0xAB                           // Eg..
                }, Local0)
            Store (Buffer (0x04)
                {
                     0x45, 0x67, 0x89, 0xAB                           // Eg..
                }, Local1)
            If (LNot (BCMP (Local1, Local0)))
            {
                ERR (TS, Z179, 0x1505, 0x00, 0x00, Local0, Local1)
            }
        }

        Method (TOB7, 0, Serialized)
        {
            Name (I000, 0x00)
            OUTP ("Check ToBuffer(0x456789ab, i000)")
            ToBuffer (0x456789AB, I000) /* \MS2A.TOB7.I000 */
            If (F64)
            {
                Store (Buffer (0x08)
                    {
                         0xAB, 0x89, 0x67, 0x45                           // ..gE
                    }, Local1)
            }
            Else
            {
                Store (Buffer (0x04)
                    {
                         0xAB, 0x89, 0x67, 0x45                           // ..gE
                    }, Local1)
            }

            Store (ObjectType (I000), Local2)
            If (LNotEqual (Local2, 0x03))
            {
                ERR (TS, Z179, 0x1516, 0x00, 0x00, Local2, 0x03)
            }
            ElseIf (LNot (BCMP (Local1, I000)))
            {
                ERR (TS, Z179, 0x1518, 0x00, 0x00, I000, Local1)
            }
        }

        Method (TOB8, 0, Serialized)
        {
            Name (S000, "s000")
            OUTP ("Check ToBuffer(\"456789ab\", s000)")
            ToBuffer ("456789ab", S000) /* \MS2A.TOB8.S000 */
            Store (Buffer (0x09)
                {
                    "456789ab"
                }, Local1)
            Store (ObjectType (S000), Local2)
            If (LNotEqual (Local2, 0x03))
            {
                ERR (TS, Z179, 0x1525, 0x00, 0x00, Local2, 0x03)
            }
            ElseIf (LNot (BCMP (Local1, S000)))
            {
                ERR (TS, Z179, 0x1527, 0x00, 0x00, S000, Local1)
            }
        }

        Method (TOB9, 0, Serialized)
        {
            Name (B000, Buffer (0x02){})
            OUTP ("Check ToBuffer(Buffer(4){0x45, 0x67, 0x89, 0xab}, b000)")
            ToBuffer (Buffer (0x04)
                {
                     0x45, 0x67, 0x89, 0xAB                           // Eg..
                }, B000) /* \MS2A.TOB9.B000 */
            Store (Buffer (0x04)
                {
                     0x45, 0x67, 0x89, 0xAB                           // Eg..
                }, Local1)
            Store (ObjectType (B000), Local2)
            If (LNotEqual (Local2, 0x03))
            {
                ERR (TS, Z179, 0x1534, 0x00, 0x00, Local2, 0x03)
            }
            ElseIf (LNot (BCMP (Local1, B000)))
            {
                ERR (TS, Z179, 0x1536, 0x00, 0x00, B000, Local1)
            }
        }

        Method (TOBA, 0, NotSerialized)
        {
            Method (M000, 1, Serialized)
            {
                Name (B000, Buffer (0x01)
                {
                     0x3C                                             // <
                })
                Name (B001, Buffer (0x03)
                {
                     0x01, 0x02, 0x03                                 // ...
                })
                If (Arg0)
                {
                    OUTP ("Store(b001, b000)")
                    Store (B001, B000) /* \MS2A.TOBA.M000.B000 */
                    Store (Buffer (0x01)
                        {
                             0x01                                             // .
                        }, Local0)
                    If (LNot (BCMP (B000, Local0)))
                    {
                        ERR (TS, Z179, 0x1548, 0x00, 0x00, B000, Local0)
                    }
                }
                Else
                {
                    OUTP ("Store(b000, b001)")
                    Store (B000, B001) /* \MS2A.TOBA.M000.B001 */
                    Store (Buffer (0x03)
                        {
                             0x3C                                             // <
                        }, Local0)
                    If (LNot (BCMP (B001, Local0)))
                    {
                        ERR (TS, Z179, 0x1550, 0x00, 0x00, B001, Local0)
                    }
                }
            }

            OUTP ("Check if Store fails the same way as ToBuffer optional store")
            M000 (0x00)
            M000 (0x01)
        }

        Method (M000, 0, NotSerialized)
        {
            If (ABUU){}
            Else
            {
                TOB0 ()
                TOB1 ()
                TOB2 ()
                TOB3 ()
                TOB4 ()
                TOB5 ()
                TOB6 ()
                TOB7 ()
                TOB8 ()
                TOB9 ()
            }

            TOBA ()
        }

        If (ABUU){}
        ElseIf (LEqual (SizeOf (F64), 0x08))
        {
            Store (0x01, F64) /* \MS2A.F64_ */
        }

        CH03 (TS, Z179, 0x02A4, 0x1573, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                TOB0 ()
            }
            Case (0x02)
            {
                TOB1 ()
            }
            Case (0x03)
            {
                TOB2 ()
            }
            Case (0x04)
            {
                TOB3 ()
            }
            Case (0x05)
            {
                TOB4 ()
            }
            Case (0x06)
            {
                TOB5 ()
            }
            Case (0x07)
            {
                TOB6 ()
            }
            Case (0x08)
            {
                TOB7 ()
            }
            Case (0x09)
            {
                TOB8 ()
            }
            Case (0x0A)
            {
                TOB9 ()
            }
            Case (0x0B)
            {
                TOBA ()
            }

        }

        CH03 (TS, Z179, 0x02A5, 0x1582, 0x00)
    }

    Method (ATOB, 0, NotSerialized)
    {
        IIN0 ()
        MS2A (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BTOB, 0, NotSerialized)
    {
        IIN0 ()
        MS2A (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CTOB, 0, NotSerialized)
    {
        IIN0 ()
        MS2A (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DTOB, 0, NotSerialized)
    {
        IIN0 ()
        MS2A (0x04)
        Return (POUT) /* \POUT */
    }

    Method (ETOB, 0, NotSerialized)
    {
        IIN0 ()
        MS2A (0x05)
        Return (POUT) /* \POUT */
    }

    Method (FTOB, 0, NotSerialized)
    {
        IIN0 ()
        MS2A (0x06)
        Return (POUT) /* \POUT */
    }

    Method (GTOB, 0, NotSerialized)
    {
        IIN0 ()
        MS2A (0x07)
        Return (POUT) /* \POUT */
    }

    Method (HTOB, 0, NotSerialized)
    {
        IIN0 ()
        MS2A (0x08)
        Return (POUT) /* \POUT */
    }

    Method (ITOB, 0, NotSerialized)
    {
        IIN0 ()
        MS2A (0x09)
        Return (POUT) /* \POUT */
    }

    Method (JTOB, 0, NotSerialized)
    {
        IIN0 ()
        MS2A (0x0A)
        Return (POUT) /* \POUT */
    }

    Method (KTOB, 0, NotSerialized)
    {
        IIN0 ()
        MS2A (0x0B)
        Return (POUT) /* \POUT */
    }

    Method (MS2B, 1, Serialized)
    {
        Name (TS, "ms2b")
        Method (PAC0, 0, Serialized)
        {
            Name (P000, Package (0x05)
            {
                0x01, 
                0x02, 
                0x03
            })
            OUTP ("Check if Package list < explicit size the last is in use")
            Store (SizeOf (P000), Local0)
            If (LNotEqual (Local0, 0x05))
            {
                ERR (TS, Z179, 0x15A3, 0x00, 0x00, Local0, 0x05)
            }
        }

        Method (PAC1, 0, Serialized)
        {
            Name (P000, Package (0x05)
            {
                0x01, 
                0x02, 
                0x03
            })
            OUTP ("Check if Package list < explicit size there are undef elements")
            Store (ObjectType (Index (P000, 0x02)), Local0)
            If (Local0){}
            Else
            {
                ERR (TS, Z179, 0x15B0, 0x00, 0x00, Local0, 0x01)
            }

            Store (ObjectType (Index (P000, 0x03)), Local0)
            If (Local0)
            {
                ERR (TS, Z179, 0x15B5, 0x00, 0x00, Local0, 0x00)
            }
        }

        Method (PAC2, 0, Serialized)
        {
            Name (FOPT, 0x00)
            Name (P000, Package (0x03)
            {
                0x01, 
                0x02, 
                0x03
            })
            OUTP ("Check if Package list > explicit size the former is in use")
            If (FOPT)
            {
                Store (SizeOf (P000), Local0)
            }
            Else
            {
                Store (0x05, Local0)
            }

            If (LNotEqual (Local0, 0x05))
            {
                ERR (TS, Z179, 0x15CA, 0x00, 0x00, Local0, 0x05)
            }
        }

        CH03 (TS, Z179, 0x02AB, 0x15CE, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                PAC0 ()
                PAC1 ()
                PAC2 ()
            }
            Case (0x01)
            {
                PAC0 ()
            }
            Case (0x02)
            {
                PAC1 ()
            }
            Case (0x03)
            {
                PAC2 ()
            }

        }

        CH03 (TS, Z179, 0x02AC, 0x15D5, 0x00)
    }

    Method (APAC, 0, NotSerialized)
    {
        IIN0 ()
        MS2B (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BPAC, 0, NotSerialized)
    {
        IIN0 ()
        MS2B (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CPAC, 0, NotSerialized)
    {
        IIN0 ()
        MS2B (0x03)
        Return (POUT) /* \POUT */
    }

    Method (MS2C, 1, Serialized)
    {
        Name (TS, "ms2c")
        Method (SW00, 0, Serialized)
        {
            Method (M000, 1, Serialized)
            {
                Store (0x00, Local1)
                Switch (ToInteger (Arg0))
                {
                    Case (0x01)
                    {
                        Store (0x01, Local1)
                    }
                    Case (0x02)
                    {
                        Store (0x02, Local1)
                    }

                }

                Return (Local1)
            }

            OUTP ("Check Switch implementation 0: standalone")
            Store (0x02, Local0)
            Store (0x00, Local1)
            Switch (ToInteger (Local0))
            {
                Case (0x01)
                {
                    Store (0x01, Local1)
                }
                Case (0x02)
                {
                    Store (0x02, Local1)
                }

            }

            If (LNotEqual (Local1, 0x02))
            {
                ERR (TS, Z179, 0x1601, 0x00, 0x00, Local1, 0x02)
            }

            Store (M000 (0x01), Local1)
            If (LNotEqual (Local1, 0x01))
            {
                ERR (TS, Z179, 0x1607, 0x00, 0x00, Local1, 0x01)
            }
        }

        Method (SW01, 0, NotSerialized)
        {
            OUTP ("Check While implementation 1: standalone")
            Store (0x02, Local0)
            Store (0x00, Local1)
            While (Local0)
            {
                If (LEqual (Local0, 0x01))
                {
                    Increment (Local1)
                }
                Else
                {
                    Increment (Local1)
                }

                Decrement (Local0)
            }

            If (LNotEqual (Local1, 0x02))
            {
                ERR (TS, Z179, 0x161B, 0x00, 0x00, Local1, 0x02)
            }
        }

        Method (SW02, 0, Serialized)
        {
            OUTP ("Check Switch implementation 2: inside While (1 step)")
            Store (0x01, Local0)
            Store (0x00, Local1)
            Store (0x00, Local2)
            While (Local0)
            {
                Switch (ToInteger (Local0))
                {
                    Case (0x01)
                    {
                        Increment (Local1)
                    }
                    Case (0x02)
                    {
                        Increment (Local2)
                    }

                }

                Decrement (Local0)
            }

            If (LNotEqual (Local1, 0x01))
            {
                ERR (TS, Z179, 0x162F, 0x00, 0x00, Local1, 0x01)
            }

            If (LNotEqual (Local2, 0x00))
            {
                ERR (TS, Z179, 0x1632, 0x00, 0x00, Local2, 0x00)
            }
        }

        Method (SW03, 0, Serialized)
        {
            OUTP ("Check Switch implementation 3: inside While (2 steps)")
            Store (0x02, Local0)
            Store (0x00, Local1)
            Store (0x00, Local2)
            While (Local0)
            {
                Switch (ToInteger (Local0))
                {
                    Case (0x01)
                    {
                        Increment (Local1)
                    }
                    Case (0x02)
                    {
                        Increment (Local2)
                    }

                }

                Decrement (Local0)
            }

            If (LNotEqual (Local1, 0x01))
            {
                ERR (TS, Z179, 0x1646, 0x00, 0x00, Local1, 0x01)
            }

            If (LNotEqual (Local2, 0x01))
            {
                ERR (TS, Z179, 0x1649, 0x00, 0x00, Local2, 0x01)
            }
        }

        Method (SW04, 0, Serialized)
        {
            OUTP ("Check Switch implementation 4: inside While 2, 2 Breaks")
            Store (0x02, Local0)
            Store (0x00, Local1)
            Store (0x00, Local2)
            While (Local0)
            {
                Switch (ToInteger (Local0))
                {
                    Case (0x01)
                    {
                        Increment (Local1)
                        Break
                    }
                    Case (0x02)
                    {
                        Increment (Local2)
                        Break
                    }

                }

                Decrement (Local0)
            }

            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x1663, 0x00, 0x00, Local0, 0x00)
            }

            If (LNotEqual (Local1, 0x01))
            {
                ERR (TS, Z179, 0x1666, 0x00, 0x00, Local1, 0x01)
            }

            If (LNotEqual (Local2, 0x01))
            {
                ERR (TS, Z179, 0x1669, 0x00, 0x00, Local2, 0x01)
            }
        }

        Method (SW05, 0, Serialized)
        {
            OUTP ("Check Switch implementation 5: inside While 1, 2 Breaks")
            Store (0x01, Local0)
            Store (0x00, Local1)
            Store (0x00, Local2)
            While (Local0)
            {
                Switch (ToInteger (Local0))
                {
                    Case (0x01)
                    {
                        Increment (Local1)
                        Break
                    }
                    Case (0x02)
                    {
                        Increment (Local2)
                        Break
                    }

                }

                Decrement (Local0)
            }

            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x1683, 0x00, 0x00, Local0, 0x00)
            }

            If (LNotEqual (Local1, 0x01))
            {
                ERR (TS, Z179, 0x1686, 0x00, 0x00, Local1, 0x01)
            }

            If (LNotEqual (Local2, 0x00))
            {
                ERR (TS, Z179, 0x1689, 0x00, 0x00, Local2, 0x00)
            }
        }

        Method (SW06, 0, Serialized)
        {
            OUTP ("Check Switch implementation 6: inside While 2, 1 Break")
            Store (0x02, Local0)
            Store (0x00, Local1)
            Store (0x00, Local2)
            While (Local0)
            {
                Switch (ToInteger (Local0))
                {
                    Case (0x01)
                    {
                        Increment (Local1)
                    }
                    Case (0x02)
                    {
                        Increment (Local2)
                        Break
                    }

                }

                Decrement (Local0)
            }

            If (LNotEqual (Local0, 0x00))
            {
                ERR (TS, Z179, 0x16A3, 0x00, 0x00, Local0, 0x00)
            }

            If (LNotEqual (Local1, 0x01))
            {
                ERR (TS, Z179, 0x16A6, 0x00, 0x00, Local1, 0x01)
            }

            If (LNotEqual (Local2, 0x01))
            {
                ERR (TS, Z179, 0x16A9, 0x00, 0x00, Local2, 0x01)
            }
        }

        Method (SW07, 0, Serialized)
        {
            OUTP ("Check While implementation 7: Name inside, 1 step")
            Store (0x01, Local0)
            Store (0x00, Local1)
            Name (WHIN, Ones)
            While (Local0)
            {
                If (Local1)
                {
                    CH04 (TS, 0x00, 0xFF, Z179, 0x16B8, 0x00, 0x00)
                }
                Else
                {
                    CH03 (TS, Z179, 0x02BE, 0x16BA, 0x00)
                }

                Store (Local1, WHIN) /* \MS2C.SW07.WHIN */
                Decrement (Local0)
                Increment (Local1)
            }
        }

        Method (SW08, 0, Serialized)
        {
            OUTP ("Check While implementation 8: Name inside, 2 steps")
            Store (0x02, Local0)
            Store (0x00, Local1)
            Name (WHIN, Ones)
            While (Local0)
            {
                If (LGreater (Local1, 0x02))
                {
                    CH04 (TS, 0x00, 0xFF, Z179, 0x16CD, 0x00, 0x00)
                }
                Else
                {
                    CH03 (TS, Z179, 0x02C0, 0x16CF, 0x00)
                }

                Store (Local1, WHIN) /* \MS2C.SW08.WHIN */
                Decrement (Local0)
                Increment (Local1)
            }
        }

        Method (M000, 0, NotSerialized)
        {
            SW00 ()
            SW01 ()
            SW02 ()
            SW03 ()
            If (LAnd (ABUU, LNot (Q00A))){}
            Else
            {
                SW04 ()
                SW05 ()
                SW06 ()
            }

            SW07 ()
            If (ABUU){}
            Else
            {
                SW08 ()
            }
        }

        CH03 (TS, Z179, 0x02C1, 0x16ED, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                SW00 ()
            }
            Case (0x02)
            {
                SW01 ()
            }
            Case (0x03)
            {
                SW02 ()
            }
            Case (0x04)
            {
                SW03 ()
            }
            Case (0x05)
            {
                SW04 ()
            }
            Case (0x06)
            {
                SW05 ()
            }
            Case (0x07)
            {
                SW06 ()
            }
            Case (0x08)
            {
                SW07 ()
            }
            Case (0x09)
            {
                SW08 ()
            }

        }

        CH03 (TS, Z179, 0x02C2, 0x16FA, 0x00)
    }

    Method (ASW0, 0, NotSerialized)
    {
        IIN0 ()
        MS2C (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BSW0, 0, NotSerialized)
    {
        IIN0 ()
        MS2C (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CSW0, 0, NotSerialized)
    {
        IIN0 ()
        MS2C (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DSW0, 0, NotSerialized)
    {
        IIN0 ()
        MS2C (0x04)
        Return (POUT) /* \POUT */
    }

    Method (ESW0, 0, NotSerialized)
    {
        IIN0 ()
        MS2C (0x05)
        Return (POUT) /* \POUT */
    }

    Method (FSW0, 0, NotSerialized)
    {
        IIN0 ()
        MS2C (0x06)
        Return (POUT) /* \POUT */
    }

    Method (GSW0, 0, NotSerialized)
    {
        IIN0 ()
        MS2C (0x07)
        Return (POUT) /* \POUT */
    }

    Method (HSW0, 0, NotSerialized)
    {
        IIN0 ()
        MS2C (0x08)
        Return (POUT) /* \POUT */
    }

    Method (ISW0, 0, NotSerialized)
    {
        IIN0 ()
        MS2C (0x09)
        Return (POUT) /* \POUT */
    }

    Method (MS2D, 1, Serialized)
    {
        Name (TS, "ms2d")
        Name (Y, 0x00)
        Method (M001, 1, NotSerialized)
        {
            Name (X, Zero)
            If (Y)
            {
                If (Y300)
                {
                    CH03 (TS, Z179, 0x03C3, 0x171A, 0x00)
                }
                Else
                {
                    CH04 (TS, 0x00, 0xFF, Z179, 0x171C, 0x00, 0x00)
                }
            }
            Else
            {
                CH03 (TS, Z179, 0x02C4, 0x171F, 0x00)
            }

            Increment (Y)
            Increment (X)
            Decrement (Arg0)
            If (LGreater (Arg0, Zero))
            {
                M001 (Arg0)
            }
        }

        Method (WAC0, 0, NotSerialized)
        {
            OUTP ("Recursive method with local named execution 1")
            Store (0x00, Y) /* \MS2D.Y___ */
            M001 (0x01)
        }

        Method (WAC1, 0, NotSerialized)
        {
            OUTP ("Recursive method with local named execution 2")
            Store (0x00, Y) /* \MS2D.Y___ */
            M001 (0x02)
        }

        Method (WAC2, 0, NotSerialized)
        {
            OUTP ("Recursive method with local named execution 4")
            Store (0x00, Y) /* \MS2D.Y___ */
            M001 (0x04)
        }

        Method (M000, 0, NotSerialized)
        {
            WAC0 ()
            If (ABUU){}
            Else
            {
                WAC1 ()
            }

            If (ABUU){}
            Else
            {
                WAC2 ()
            }
        }

        CH03 (TS, Z179, 0x02C5, 0x1752, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M000 ()
            }
            Case (0x01)
            {
                WAC0 ()
            }
            Case (0x02)
            {
                WAC1 ()
            }
            Case (0x03)
            {
                WAC2 ()
            }

        }

        CH03 (TS, Z179, 0x02C6, 0x1759, 0x00)
    }

    Method (AWAC, 0, NotSerialized)
    {
        IIN0 ()
        MS2D (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BWAC, 0, NotSerialized)
    {
        IIN0 ()
        MS2D (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CWAC, 0, NotSerialized)
    {
        IIN0 ()
        MS2D (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DWAC, 0, NotSerialized)
    {
        IIN0 ()
        MS2D (0x04)
        Return (POUT) /* \POUT */
    }

    Event (EV00)
    Method (MZAC, 1, NotSerialized)
    {
        Name (X, Zero)
        Increment (X)
        OUTP (X)
        If (LGreater (Arg0, Zero))
        {
            Wait (EV00, 0xFFFF)
        }
    }

    Method (ZAC0, 0, NotSerialized)
    {
        OUTP ("Method with local named execution 1: Block")
        MZAC (0x01)
    }

    Method (ZAC1, 0, NotSerialized)
    {
        OUTP ("Method with local named execution 2: Pass")
        MZAC (0x00)
    }

    Method (ZAC2, 0, NotSerialized)
    {
        Sleep (0x1388)
        OUTP ("Method with local named execution 3: Signal")
        Signal (EV00)
    }

    Name (ZACZ, 0x05)
    Method (ZAC3, 0, NotSerialized)
    {
        Sleep (0x03E8)
        Decrement (ZACZ)
        If (LEqual (ZACZ, 0x04))
        {
            ZAC0 ()
        }
        ElseIf (LEqual (ZACZ, 0x02))
        {
            ZAC2 ()
        }
        Else
        {
            ZAC1 ()
        }

        Return (ZACZ) /* \ZACZ */
    }

    Method (AZAC, 0, NotSerialized)
    {
        IIN0 ()
        ZAC0 ()
        Return (POUT) /* \POUT */
    }

    Method (BZAC, 0, NotSerialized)
    {
        IIN0 ()
        ZAC1 ()
        Return (POUT) /* \POUT */
    }

    Method (CZAC, 0, NotSerialized)
    {
        IIN0 ()
        ZAC2 ()
        Return (POUT) /* \POUT */
    }

    Method (DZAC, 0, NotSerialized)
    {
        IIN0 ()
        ZAC3 ()
        Return (POUT) /* \POUT */
    }

    Method (MS2E, 0, Serialized)
    {
        Name (TS, "ms2e")
        Name (BUF0, Buffer (0x0C){})
        OUTP ("Buffer is not shortened on storing short string")
        CH03 (TS, Z179, 0x02C7, 0x17B3, 0x00)
        Store ("ABCD", BUF0) /* \MS2E.BUF0 */
        Store (SizeOf (BUF0), Local0)
        If (LNotEqual (Local0, 0x0C))
        {
            ERR (TS, Z179, 0x17BA, 0x00, 0x00, Local0, 0x0C)
        }

        CH03 (TS, Z179, 0x02C9, 0x17BD, 0x00)
    }

    Method (ABUF, 0, NotSerialized)
    {
        IIN0 ()
        MS2E ()
        Return (POUT) /* \POUT */
    }

    Method (MS2F, 1, Serialized)
    {
        Name (TS, "ms2f")
        Method (B246, 0, Serialized)
        {
            Name (LN00, 0x02)
            OUTP ("Switch implementation can cause AE_ALREADY_EXISTS 1")
            Store (0x00, Local1)
            While (LN00)
            {
                Switch (ToInteger (LN00))
                {
                    Case (0x01)
                    {
                        Add (Local1, 0x01, Local1)
                    }
                    Case (0x02)
                    {
                        Add (Local1, 0x02, Local1)
                    }

                }

                Decrement (LN00)
            }

            If (LNotEqual (Local1, 0x03))
            {
                ERR (TS, Z179, 0x17E2, 0x00, 0x00, Local1, 0x03)
            }
        }

        Method (U246, 0, Serialized)
        {
            Name (LN00, 0x01)
            OUTP ("Switch implementation can cause AE_ALREADY_EXISTS 2")
            Store (0x00, Local1)
            While (LN00)
            {
                Switch (ToInteger (LN00))
                {
                    Case (0x01)
                    {
                        Add (Local1, 0x01, Local1)
                    }
                    Case (0x02)
                    {
                        Add (Local1, 0x02, Local1)
                    }

                }

                Decrement (LN00)
            }

            If (LNotEqual (Local1, 0x01))
            {
                ERR (TS, Z179, 0x17FB, 0x00, 0x00, Local1, 0x01)
            }
        }

        CH03 (TS, Z179, 0x02CC, 0x17FF, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                B246 ()
                U246 ()
            }
            Case (0x01)
            {
                B246 ()
            }
            Case (0x02)
            {
                U246 ()
            }

        }

        CH03 (TS, Z179, 0x02CD, 0x1805, 0x00)
    }

    Method (A246, 0, NotSerialized)
    {
        IIN0 ()
        MS2F (0x01)
        Return (POUT) /* \POUT */
    }

    Method (B246, 0, NotSerialized)
    {
        IIN0 ()
        MS2F (0x02)
        Return (POUT) /* \POUT */
    }

    Method (MS30, 0, Serialized)
    {
        Name (TS, "ms30")
        Method (B247, 0, NotSerialized)
        {
            Method (M000, 4, Serialized)
            {
                Name (LN00, 0x02)
                Name (CH10, 0x00)
                Name (CH11, 0x00)
                Name (CH20, 0x00)
                Name (CH21, 0x00)
                OUTP (Arg0)
                While (0x01)
                {
                    Switch (ToInteger (Arg3))
                    {
                        Case (0x01)
                        {
                            If (Arg1)
                            {
                                Store (0x01, CH10) /* \MS30.B247.M000.CH10 */
                                Break
                            }

                            Store (0x01, CH11) /* \MS30.B247.M000.CH11 */
                        }
                        Case (0x02)
                        {
                            If (Arg2)
                            {
                                Store (0x01, CH20) /* \MS30.B247.M000.CH20 */
                                Break
                            }

                            Store (0x01, CH21) /* \MS30.B247.M000.CH21 */
                        }

                    }

                    Break
                }

                If (LEqual (Arg3, 0x01))
                {
                    If (LNotEqual (CH10, Arg1))
                    {
                        ERR (TS, Z179, 0x183A, 0x00, 0x00, CH10, Arg1)
                    }

                    If (LEqual (CH11, Arg1))
                    {
                        ERR (TS, Z179, 0x183D, 0x00, 0x00, CH11, Arg1)
                    }
                }

                If (LEqual (Arg3, 0x02))
                {
                    If (LNotEqual (CH20, Arg2))
                    {
                        ERR (TS, Z179, 0x1842, 0x00, 0x00, CH20, Arg2)
                    }

                    If (LEqual (CH21, Arg2))
                    {
                        ERR (TS, Z179, 0x1845, 0x00, 0x00, CH21, Arg2)
                    }
                }
            }

            OUTP ("Switch implementation can cause AE_ALREADY_EXISTS 3")
            M000 ("Break 100", 0x00, 0x00, 0x01)
            M000 ("Break 101", 0x00, 0x01, 0x01)
            M000 ("Break 110", 0x01, 0x00, 0x01)
            M000 ("Break 111", 0x01, 0x01, 0x01)
            M000 ("Break 200", 0x00, 0x00, 0x02)
            M000 ("Break 201", 0x00, 0x01, 0x02)
            M000 ("Break 210", 0x01, 0x00, 0x02)
            M000 ("Break 211", 0x01, 0x01, 0x02)
        }

        CH03 (TS, Z179, 0x02D2, 0x1856, 0x00)
        B247 ()
        CH03 (TS, Z179, 0x02D3, 0x1858, 0x00)
    }

    Method (A247, 0, NotSerialized)
    {
        IIN0 ()
        MS30 ()
        Return (POUT) /* \POUT */
    }

    Method (MS31, 1, Serialized)
    {
        Name (TS, "ms31")
        Name (BUF0, Buffer (0x34)
        {
            /* 0000 */  0x53, 0x53, 0x44, 0x54, 0x34, 0x00, 0x00, 0x00,  // SSDT4...
            /* 0008 */  0x02, 0xDE, 0x49, 0x6E, 0x74, 0x65, 0x6C, 0x00,  // ..Intel.
            /* 0010 */  0x4D, 0x61, 0x6E, 0x79, 0x00, 0x00, 0x00, 0x00,  // Many....
            /* 0018 */  0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,  // ....INTL
            /* 0020 */  0x15, 0x12, 0x06, 0x20, 0x14, 0x0F, 0x5C, 0x53,  // ... ..\S
            /* 0028 */  0x53, 0x30, 0x30, 0x00, 0xA4, 0x0D, 0x5C, 0x53,  // S00...\S
            /* 0030 */  0x53, 0x30, 0x30, 0x00                           // S00.
        })
        OperationRegion (IST0, SystemMemory, VMEM, 0x34)
        Field (IST0, ByteAcc, NoLock, Preserve)
        {
            RFU0,   416
        }

        Name (DDBH, 0x00)
        External (\SS00, UnknownObj)
        Method (M000, 0, NotSerialized)
        {
            OUTP ("ldt0: Simple Load/Unload(Field, LocalX) test")
            Store (BUF0, RFU0) /* \MS31.RFU0 */
            Load (RFU0, Local0)
            CH03 (TS, Z179, 0x02D4, 0x1883, 0x00)
            OUTP ("SSDT loaded")
            Unload (Local0)
            CH03 (TS, Z179, 0x02D5, 0x1887, 0x00)
            OUTP ("SSDT unloaded")
        }

        Method (M001, 0, NotSerialized)
        {
            OUTP ("ldt1: Simple Load(OpRegion, LocalX) test")
            Store (BUF0, RFU0) /* \MS31.RFU0 */
            Load (IST0, Local0)
            CH03 (TS, Z179, 0x02D6, 0x1893, 0x00)
            OUTP ("SSDT loaded")
        }

        Method (M002, 0, NotSerialized)
        {
            OUTP ("ldt2: Simple Load/Unload(OpRegion, LocalX) test")
            Store (BUF0, RFU0) /* \MS31.RFU0 */
            Load (IST0, DDBH) /* \MS31.DDBH */
            CH03 (TS, Z179, 0x02D7, 0x189E, 0x00)
            OUTP ("SSDT loaded")
            Unload (DDBH)
            CH03 (TS, Z179, 0x02D8, 0x18A2, 0x00)
            OUTP ("SSDT unloaded")
        }

        Method (M003, 0, NotSerialized)
        {
            OUTP ("ldt3: Simple Load/ObjectType(DDBHandle) test")
            Store (BUF0, RFU0) /* \MS31.RFU0 */
            Load (IST0, Local0)
            CH03 (TS, Z179, 0x02D9, 0x18AD, 0x00)
            OUTP ("SSDT loaded")
            Store (ObjectType (Local0), Local1)
            If (LNotEqual (0x0F, Local1))
            {
                ERR (TS, Z179, 0x18B2, 0x00, 0x00, Local1, 0x0F)
            }

            Unload (DDBH)
            CH03 (TS, Z179, 0x02DB, 0x18B6, 0x00)
            OUTP ("SSDT unloaded")
        }

        Method (M013, 0, NotSerialized)
        {
            OUTP ("ldt13: Simple Load/ObjectType(DDBHandle) test")
            Store (BUF0, RFU0) /* \MS31.RFU0 */
            Load (IST0, Local0)
            CH03 (TS, Z179, 0x02DC, 0x18C2, 0x00)
            OUTP ("SSDT loaded")
            Store (ObjectType (Local0), Local1)
            If (LNotEqual (0x0F, Local1))
            {
                ERR (TS, Z179, 0x18C7, 0x00, 0x00, Local1, 0x0F)
            }
        }

        Method (M004, 0, Serialized)
        {
            Name (DDBH, 0x00)
            OUTP ("ldt4: Simple Load/ObjectType(Named DDBHandle) test")
            Store (BUF0, RFU0) /* \MS31.RFU0 */
            Load (IST0, DDBH) /* \MS31.M004.DDBH */
            CH03 (TS, Z179, 0x02DE, 0x18D4, 0x00)
            OUTP ("SSDT loaded")
            Store (ObjectType (DDBH), Local1)
            If (LNotEqual (0x0F, Local1))
            {
                ERR (TS, Z179, 0x18D9, 0x00, 0x00, Local1, 0x0F)
            }

            Unload (DDBH)
            CH03 (TS, Z179, 0x02E0, 0x18DD, 0x00)
            OUTP ("SSDT unloaded")
        }

        Method (M014, 0, Serialized)
        {
            Name (DDBH, 0x00)
            OUTP ("ldt14: Simple Load/ObjectType(Named DDBHandle) test")
            Store (BUF0, RFU0) /* \MS31.RFU0 */
            Load (IST0, DDBH) /* \MS31.M014.DDBH */
            CH03 (TS, Z179, 0x02E1, 0x18EB, 0x00)
            OUTP ("SSDT loaded")
            Store (ObjectType (DDBH), Local1)
            If (LNotEqual (0x0F, Local1))
            {
                ERR (TS, Z179, 0x18F0, 0x00, 0x00, Local1, 0x0F)
            }
        }

        Method (M005, 0, Serialized)
        {
            Name (PAC0, Package (0x01){})
            OUTP ("ldt5: Simple Load(OpRegion, Indexed DDBHandle) test")
            Store (BUF0, RFU0) /* \MS31.RFU0 */
            Load (IST0, Index (PAC0, 0x00))
            CH03 (TS, Z179, 0x02E3, 0x18FD, 0x00)
            OUTP ("SSDT loaded")
            Store (DerefOf (Index (PAC0, 0x00)), Local0)
            Unload (Local0)
            CH03 (TS, Z179, 0x02E4, 0x1903, 0x00)
            OUTP ("SSDT unloaded")
        }

        Method (M015, 0, Serialized)
        {
            Name (PAC0, Package (0x01){})
            OUTP ("ldt15: Simple Load(OpRegion, Indexed DDBHandle) test")
            Store (BUF0, RFU0) /* \MS31.RFU0 */
            Load (IST0, Index (PAC0, 0x00))
            CH03 (TS, Z179, 0x02E5, 0x1911, 0x00)
            OUTP ("SSDT loaded")
        }

        Method (M006, 0, NotSerialized)
        {
            OUTP ("ldt6: Complex Load(OpRegion, LocalX) - CondRefof test")
            Store (BUF0, RFU0) /* \MS31.RFU0 */
            Store (CondRefOf (\SS00, Local1), Local2)
            OUTP ("CondRefof before Load")
            If (Local2)
            {
                ERR (TS, Z179, 0x191E, 0x00, 0x00, Local2, 0x00)
            }

            Load (IST0, Local0)
            CH03 (TS, Z179, 0x02E7, 0x1922, 0x00)
            Store (CondRefOf (\SS00, Local3), Local4)
            OUTP ("CondRefof after Load")
            If (Local4){}
            Else
            {
                ERR (TS, Z179, 0x1928, 0x00, 0x00, Local4, 0x01)
            }

            Unload (Local0)
            CH03 (TS, Z179, 0x02E9, 0x192C, 0x00)
            Store (CondRefOf (\SS00, Local5), Local6)
            OUTP ("CondRefof after UnLoad")
            If (Local6)
            {
                ERR (TS, Z179, 0x1931, 0x00, 0x00, Local6, 0x00)
            }
        }

        Method (M016, 0, NotSerialized)
        {
            OUTP ("ldt16: Complex Load(OpRegion, LocalX) - CondRefof test")
            Store (BUF0, RFU0) /* \MS31.RFU0 */
            Store (CondRefOf (\SS00, Local1), Local2)
            OUTP ("CondRefof before Load")
            If (Local2)
            {
                ERR (TS, Z179, 0x193F, 0x00, 0x00, Local2, 0x00)
            }

            Load (IST0, Local0)
            CH03 (TS, Z179, 0x02EC, 0x1943, 0x00)
            Store (CondRefOf (\SS00, Local3), Local4)
            OUTP ("CondRefof after Load")
            If (Local4){}
            Else
            {
                ERR (TS, Z179, 0x1949, 0x00, 0x00, Local4, 0x01)
            }
        }

        Method (M010, 0, NotSerialized)
        {
            M000 ()
            If (Y290)
            {
                M002 ()
                M003 ()
                M004 ()
            }

            If (LAnd (Y261, Y290))
            {
                M005 ()
            }

            If (Y290)
            {
                M006 ()
            }
        }

        CH03 (TS, Z179, 0x02EE, 0x1960, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M010 ()
            }
            Case (0x01)
            {
                M000 ()
            }
            Case (0x02)
            {
                M001 ()
            }
            Case (0x03)
            {
                M002 ()
            }
            Case (0x04)
            {
                M003 ()
            }
            Case (0x05)
            {
                M004 ()
            }
            Case (0x06)
            {
                M005 ()
            }
            Case (0x07)
            {
                M006 ()
            }
            Case (0x08)
            {
                M013 ()
            }
            Case (0x09)
            {
                M014 ()
            }
            Case (0x0A)
            {
                M015 ()
            }
            Case (0x0B)
            {
                M016 ()
            }

        }

        CH03 (TS, Z179, 0x02EF, 0x196F, 0x00)
    }

    Method (ALDT, 0, NotSerialized)
    {
        IIN0 ()
        MS31 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BLDT, 0, NotSerialized)
    {
        IIN0 ()
        MS31 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CLDT, 0, NotSerialized)
    {
        IIN0 ()
        MS31 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DLDT, 0, NotSerialized)
    {
        IIN0 ()
        MS31 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (ELDT, 0, NotSerialized)
    {
        IIN0 ()
        MS31 (0x05)
        Return (POUT) /* \POUT */
    }

    Method (FLDT, 0, NotSerialized)
    {
        IIN0 ()
        MS31 (0x06)
        Return (POUT) /* \POUT */
    }

    Method (GLDT, 0, NotSerialized)
    {
        IIN0 ()
        MS31 (0x07)
        Return (POUT) /* \POUT */
    }

    Method (HLDT, 0, NotSerialized)
    {
        IIN0 ()
        MS31 (0x08)
        Return (POUT) /* \POUT */
    }

    Method (ILDT, 0, NotSerialized)
    {
        IIN0 ()
        MS31 (0x09)
        Return (POUT) /* \POUT */
    }

    Method (JLDT, 0, NotSerialized)
    {
        IIN0 ()
        MS31 (0x0A)
        Return (POUT) /* \POUT */
    }

    Method (KLDT, 0, NotSerialized)
    {
        IIN0 ()
        MS31 (0x0B)
        Return (POUT) /* \POUT */
    }

    Method (MS32, 1, Serialized)
    {
        Name (TS, "ms32")
        Method (M000, 0, NotSerialized)
        {
            OUTP ("cnr0: Simple CondRefof() positive test")
            Store (CondRefOf (\_SB.ABBU.IMAX), Local0)
            CH03 (TS, Z179, 0x02F0, 0x198D, 0x00)
        }

        Method (M001, 0, NotSerialized)
        {
            OUTP ("cnr1: Simple CondRefof( , ) positive test 2")
            Store (CondRefOf (\_SB.ABBU._HID, Local1), Local0)
            CH03 (TS, Z179, 0x02F1, 0x1995, 0x00)
            If (Local0){}
            Else
            {
                ERR (TS, Z179, 0x1999, 0x00, 0x00, Local0, 0x01)
            }
        }

        Method (M002, 0, Serialized)
        {
            Name (I000, 0x76543210)
            OUTP ("cnr2: Simple CondRefof( , ) positive test for dynamic object")
            Store (CondRefOf (^M002.I000, Local1), Local0)
            If (Local0)
            {
                Store (DerefOf (Local1), Local2)
                If (LNotEqual (0x76543210, Local2))
                {
                    ERR (TS, Z179, 0x19A7, 0x00, 0x00, Local2, 0x76543210)
                }
            }
            Else
            {
                ERR (TS, Z179, 0x19AA, 0x00, 0x00, Local0, 0x01)
            }
        }

        Method (M003, 0, Serialized)
        {
            OUTP ("cnr3: Simple CondRefof( , ) negative test for dynamic object")
            Store (CondRefOf (^M003.I000, Local1), Local0)
            If (Local0)
            {
                ERR (TS, Z179, 0x19B4, 0x00, 0x00, Local0, 0x01)
            }

            Name (I000, 0x01)
            Store (CondRefOf (^M003.I000, Local1), Local0)
            If (Local0){}
            Else
            {
                ERR (TS, Z179, 0x19BC, 0x00, 0x00, Local0, 0x00)
            }
        }

        Method (M004, 0, NotSerialized)
        {
            OUTP ("cnr4: Simple CondRefof(_OSI, Local0) test")
            OUTP ("if (CondRefOf (_OSI, Local0))")
            If (CondRefOf (_OSI, Local0))
            {
                OUTP ("True")
                OUTP ("_OSI (\"Windows 2001\"):")
                If (\_OSI ("Windows 2001"))
                {
                    OUTP ("True")
                }
                Else
                {
                    OUTP ("False")
                }
            }
            Else
            {
                OUTP ("False")
            }

            CH03 (TS, Z179, 0x02F7, 0x19D2, 0x00)
        }

        Method (M010, 0, NotSerialized)
        {
            M000 ()
            M001 ()
            M002 ()
            M003 ()
            M004 ()
        }

        CH03 (TS, Z179, 0x02F8, 0x19DE, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                M010 ()
            }
            Case (0x01)
            {
                M000 ()
            }
            Case (0x02)
            {
                M001 ()
            }
            Case (0x03)
            {
                M002 ()
            }
            Case (0x04)
            {
                M003 ()
            }
            Case (0x05)
            {
                M004 ()
            }

        }

        CH03 (TS, Z179, 0x02F9, 0x19E7, 0x00)
    }

    Method (ACNR, 0, NotSerialized)
    {
        IIN0 ()
        MS32 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BCNR, 0, NotSerialized)
    {
        IIN0 ()
        MS32 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CCNR, 0, NotSerialized)
    {
        IIN0 ()
        MS32 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DCNR, 0, NotSerialized)
    {
        IIN0 ()
        MS32 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (ECNR, 0, NotSerialized)
    {
        IIN0 ()
        MS32 (0x05)
        Return (POUT) /* \POUT */
    }

    Method (MS33, 1, Serialized)
    {
        Name (TS, "ms33")
        Method (ASDL, 0, NotSerialized)
        {
            If (LOr (ABUU, SLCK))
            {
                CH03 (TS, Z179, 0x02FA, 0x1A05, 0x00)
            }
            Else
            {
                CH04 (TS, 0x00, 0xFF, Z179, 0x1A07, 0x00, 0x00)
            }
        }

        Method (BSDL, 0, NotSerialized)
        {
            If (LOr (ABUU, SLCK))
            {
                Store (ObjectType (Local0), Local1)
                If (LNotEqual (0x06, Local1))
                {
                    ERR (TS, Z179, 0x1A17, 0x00, 0x00, Local1, 0x06)
                }
            }
            Else
            {
                CH04 (TS, 0x00, 0xFF, Z179, 0x1A1A, 0x00, 0x00)
            }
        }

        Method (CSDL, 0, Serialized)
        {
            Device (DLOC)
            {
            }

            If (LOr (ABUU, SLCK))
            {
                Store (ObjectType (Local0), Local1)
                If (LNotEqual (0x06, Local1))
                {
                    ERR (TS, Z179, 0x1A2D, 0x00, 0x00, Local1, 0x06)
                }
                Else
                {
                    OUTP ("Ok: ObjectType succeeded")
                }
            }
            Else
            {
                CH04 (TS, 0x00, 0xFF, Z179, 0x1A32, 0x00, 0x00)
            }
        }

        Method (DSDL, 0, NotSerialized)
        {
            External (\_SB.LNKA, UnknownObj)
            OUTP ("Store _SB.LNKA Device object into LocalX")
            If (CondRefOf (\_SB.LNKA, Local2)){}
            Else
            {
                OUTP ("CondRefof for _SB.LNKA returns FALSE")
                Return (Zero)
            }

            Store (\_SB.LNKA, Local0)
            If (LOr (ABUU, SLCK))
            {
                Store (ObjectType (Local0), Local1)
                If (LNotEqual (0x06, Local1))
                {
                    ERR (TS, Z179, 0x1A47, 0x00, 0x00, Local1, 0x06)
                }
            }
            Else
            {
                CH04 (TS, 0x00, 0xFF, Z179, 0x1A4A, 0x00, 0x00)
            }
        }

        CH03 (TS, Z179, 0x02A2, 0x1A4E, 0x00)
        Switch (ToInteger (Arg0))
        {
            Case (0x00)
            {
                ASDL ()
                BSDL ()
                CSDL ()
                DSDL ()
            }
            Case (0x01)
            {
                ASDL ()
            }
            Case (0x02)
            {
                BSDL ()
            }
            Case (0x03)
            {
                CSDL ()
            }
            Case (0x04)
            {
                DSDL ()
            }

        }

        CH03 (TS, Z179, 0x02A3, 0x1A5B, 0x00)
    }

    Method (ASDL, 0, NotSerialized)
    {
        IIN0 ()
        MS33 (0x01)
        Return (POUT) /* \POUT */
    }

    Method (BSDL, 0, NotSerialized)
    {
        IIN0 ()
        MS33 (0x02)
        Return (POUT) /* \POUT */
    }

    Method (CSDL, 0, NotSerialized)
    {
        IIN0 ()
        MS33 (0x03)
        Return (POUT) /* \POUT */
    }

    Method (DSDL, 0, NotSerialized)
    {
        IIN0 ()
        MS33 (0x04)
        Return (POUT) /* \POUT */
    }

    Method (MSFE, 0, NotSerialized)
    {
        SRMT ("ms10")
        MS10 (0x00)
        SRMT ("ms11")
        MS11 (0x00)
        SRMT ("ms12")
        MS12 ()
        SRMT ("ms13")
        MS13 (0x00)
        SRMT ("ms14")
        MS14 (0x00)
        SRMT ("ms15")
        MS15 (0x00)
        SRMT ("ms16")
        MS16 (0x00)
        SRMT ("ms17")
        MS17 (0x00)
        SRMT ("ms18")
        If (ABUU)
        {
            BLCK ()
        }
        Else
        {
            MS18 ()
        }

        SRMT ("ms19")
        MS19 (0x00)
        SRMT ("ms1a")
        MS1A (0x00)
        SRMT ("ms1b")
        MS1B (0x00)
        SRMT ("ms1c")
        MS1C (0x00)
        SRMT ("ms1d")
        MS1D (0x00)
        SRMT ("ms1e")
        If (ABUU)
        {
            BLCK ()
        }
        Else
        {
            MS1E ()
        }

        SRMT ("ms1f")
        MS1F (0x00)
        SRMT ("ms20")
        MS20 (0x00)
        SRMT ("ms21")
        MS21 (0x00)
        SRMT ("ms22")
        MS22 (0x00)
        SRMT ("ms23")
        MS23 (0x00)
        SRMT ("ms24")
        If (ABUU)
        {
            BLCK ()
        }
        Else
        {
            MS24 ()
        }

        SRMT ("ms25")
        If (ABUU)
        {
            BLCK ()
        }
        Else
        {
            MS25 (0x00)
        }

        SRMT ("ms26")
        If (SMBA)
        {
            MS26 (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("ms27")
        If (SMBA)
        {
            MS27 (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mt27")
        If (SMBA)
        {
            MT27 (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mu27")
        If (SMBA)
        {
            MU27 (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mv27")
        If (SMBA)
        {
            MV27 (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mw27")
        If (SMBA)
        {
            MW27 (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mx27")
        If (SMBA)
        {
            MX27 (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("my27")
        If (SMBA)
        {
            MY27 (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mz27")
        If (SMBA)
        {
            MZ27 (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("ms28")
        If (SMBA)
        {
            MS28 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("ms29")
        MS29 (0x00)
        SRMT ("ms2a")
        MS2A (0x00)
        SRMT ("ms2b")
        MS2B (0x00)
        SRMT ("ms2c")
        MS2C (0x00)
        SRMT ("ms2d")
        MS2D (0x00)
        SRMT ("ms2e")
        MS2E ()
        SRMT ("ms2f")
        MS2F (0x00)
        SRMT ("ms30")
        If (ABUU)
        {
            BLCK ()
        }
        Else
        {
            MS30 ()
        }

        SRMT ("ms31")
        If (ABUU)
        {
            BLCK ()
        }
        Else
        {
            MS31 (0x00)
        }

        SRMT ("ms32")
        MS32 (0x00)
        SRMT ("ms33")
        MS33 (0x00)
    }

    Name (Z161, 0xA1)
    Method (MF00, 0, Serialized)
    {
        Name (TS, "mf00")
        Name (I000, 0xABCD0000)
        Name (I001, 0xABCD0001)
        CopyObject (I000, I001) /* \MF00.I001 */
        If (CHK0)
        {
            If (LNotEqual (I001, 0xABCD0000))
            {
                ERR (TS, Z161, 0x5A, 0x00, 0x00, I001, 0xABCD0000)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF01, 0, Serialized)
    {
        Name (TS, "mf01")
        Name (S000, "qwertyuiop")
        Name (S001, "_sdfghjkl")
        Concatenate (S000, S001, Local0)
        OUTP (Local0)
        If (CHK0)
        {
            If (LNotEqual (Local0, "qwertyuiop_sdfghjkl"))
            {
                ERR (TS, Z161, 0x74, 0x00, 0x00, Local0, "qwertyuiop_sdfghjkl")
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF02, 0, Serialized)
    {
        Name (TS, "mf02")
        Name (S000, "qwertyuiop")
        Name (S001, "_sdfghjkl")
        Store (LEqual ("qwerty", "sdfghj"), Local3)
        If (CHK0)
        {
            If (LEqual ("qwerty", "sdfghj"))
            {
                ERR (TS, Z161, 0x8B, 0x00, 0x00, "qwerty", "sdfghj")
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF03, 0, Serialized)
    {
        Name (TS, "mf03")
        Name (I000, 0x12340001)
        Method (M000, 0, NotSerialized)
        {
            Method (M001, 0, NotSerialized)
            {
                Method (M002, 0, NotSerialized)
                {
                    Return (0x01)
                }

                Return (Add (I000, M002 ()))
            }

            Return (Add (I000, M001 ()))
        }

        M000 ()
        If (CHK1)
        {
            Store (M000 (), Local0)
            If (LNotEqual (Local0, 0x24680003))
            {
                ERR (TS, Z161, 0xAE, 0x00, 0x00, Local0, 0x24680003)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF04, 0, Serialized)
    {
        Name (TS, "mf04")
        Name (I000, 0xABCD0000)
        Method (M000, 0, NotSerialized)
        {
            Store (0x1001, Arg6)
            Return (Add (Arg6, 0x05))
        }

        Method (M001, 0, NotSerialized)
        {
            Store (0x1001, Arg6)
        }

        M001 ()
        If (CHK0)
        {
            Store (M000 (), Local0)
            If (LNotEqual (Local0, 0x1006))
            {
                ERR (TS, Z161, 0xD9, 0x00, 0x00, Local0, 0x1006)
            }

            CH03 (TS, Z161, 0x0B, 0xDB, 0x00)
        }

        Return (POUT) /* \POUT */
    }

    Method (MF05, 0, Serialized)
    {
        Name (TS, "mf05")
        Method (M000, 1, NotSerialized)
        {
            Store (0x1001, Arg0)
            Return (Add (Arg0, 0x05))
        }

        M000 (0xABCD0000)
        If (CHK1)
        {
            Store (M000 (0xABCD0000), Local0)
            If (LNotEqual (Local0, 0x1006))
            {
                ERR (TS, Z161, 0xF8, 0x00, 0x00, Local0, 0x1006)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF06, 0, Serialized)
    {
        Name (TS, "mf06")
        Name (I000, 0xABCD0000)
        Method (M000, 1, NotSerialized)
        {
            Store (0x1001, Arg0)
            Return (Add (Arg0, 0x05))
        }

        Store (M000 (I000), Local0)
        If (CHK1)
        {
            If (LNotEqual (Local0, 0x1006))
            {
                ERR (TS, Z161, 0x0116, 0x00, 0x00, Local0, 0x1006)
            }

            If (LNotEqual (I000, 0xABCD0000))
            {
                ERR (TS, Z161, 0x0119, 0x00, 0x00, I000, 0xABCD0000)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF07, 0, Serialized)
    {
        Name (TS, "mf07")
        Method (M000, 1, NotSerialized)
        {
            Store (0x1001, Arg0)
            Return (Add (Arg0, 0x05))
        }

        Store (0xABCD0000, Local7)
        Store (M000 (Local7), Local0)
        If (CHK1)
        {
            If (LNotEqual (Local0, 0x1006))
            {
                ERR (TS, Z161, 0x0137, 0x00, 0x00, Local0, 0x1006)
            }

            If (LNotEqual (Local7, 0xABCD0000))
            {
                ERR (TS, Z161, 0x013A, 0x00, 0x00, Local7, 0xABCD0000)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF08, 0, Serialized)
    {
        Name (TS, "mf08")
        Name (PR, 0x01)
        Name (I001, 0x00)
        Name (B000, Buffer (0x09)
        {
            /* 0000 */  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,  // ........
            /* 0008 */  0x18                                             // .
        })
        CreateField (B000, 0x00, 0x08, BF00)
        Store (LNotEqual (BF00, 0x80), Local3)
        If (CHK0)
        {
            Store (BF00, Local0)
            Store (LNotEqual (Local0, 0x80), Local3)
            Store (Local0, Local1)
            Store (LNotEqual (Local1, 0x80), Local3)
            If (PR)
            {
                OUTP (Local0)
                OUTP (BF00)
            }

            Store (0x80, BF00) /* \MF08.BF00 */
            If (PR)
            {
                OUTP (BF00)
            }

            Store (0x80, BF00) /* \MF08.BF00 */
            If (LNotEqual (BF00, Buffer (0x01)
                        {
                             0x80                                             // .
                        }))
            {
                ERR (TS, Z161, 0x0170, 0x00, 0x00, BF00, Buffer (0x01)
                    {
                         0x80                                             // .
                    })
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF09, 0, Serialized)
    {
        Name (TS, "mf09")
        Name (S000, "qqqqqqqqqqqqqq")
        Store (0x38, Index (S000, 0x00))
        If (CHK0)
        {
            Store (DerefOf (Index (S000, 0x00)), Local0)
            If (LNotEqual (Local0, 0x38))
            {
                ERR (TS, Z161, 0x0187, 0x00, 0x00, Local0, 0x38)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF0A, 0, Serialized)
    {
        Name (TS, "mf0a")
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32
        }

        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Store (0x20, Arg0)
                Return (Add (Arg0, 0x05))
            }

            Add (Arg0, 0x01, Local0)
            Store (Local0, Arg0)
            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Method (M001, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Return (Add (Arg0, 0x05))
            }

            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (0x12345678, F000) /* \MF0A.F000 */
        Store (M000 (F000), Local0)
        If (CHK1)
        {
            If (LNotEqual (Local0, 0x1234569E))
            {
                ERR (TS, Z161, 0x01B9, 0x00, 0x00, Local0, 0x1234569E)
            }

            If (LNotEqual (F000, 0x12345678))
            {
                ERR (TS, Z161, 0x01BC, 0x00, 0x00, F000, 0x12345678)
            }
        }

        Store (0x12345675, F000) /* \MF0A.F000 */
        Store (M001 (F000), Local0)
        If (CHK1)
        {
            If (LNotEqual (Local0, 0x2468ACEF))
            {
                ERR (TS, Z161, 0x01C4, 0x00, 0x00, Local0, 0x2468ACEF)
            }

            If (LNotEqual (F000, 0x12345675))
            {
                ERR (TS, Z161, 0x01C7, 0x00, 0x00, F000, 0x12345675)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF0B, 0, Serialized)
    {
        Name (TS, "mf0b")
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32, 
            F001,   32
        }

        BankField (R000, F001, 0x00
, ByteAcc, NoLock, Preserve)
        {
            BNK0,   32
        }

        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Store (0x20, Arg0)
                Return (Add (Arg0, 0x05))
            }

            Add (Arg0, 0x01, Local0)
            Store (Local0, Arg0)
            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Method (M001, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Return (Add (Arg0, 0x05))
            }

            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (0x12345678, BNK0) /* \MF0B.BNK0 */
        Store (M000 (BNK0), Local0)
        If (CHK1)
        {
            If (LNotEqual (Local0, 0x1234569E))
            {
                ERR (TS, Z161, 0x01FA, 0x00, 0x00, Local0, 0x1234569E)
            }

            If (LNotEqual (BNK0, 0x12345678))
            {
                ERR (TS, Z161, 0x01FD, 0x00, 0x00, BNK0, 0x12345678)
            }
        }

        Store (0x12345675, BNK0) /* \MF0B.BNK0 */
        Store (M001 (BNK0), Local0)
        If (CHK1)
        {
            If (LNotEqual (Local0, 0x2468ACEF))
            {
                ERR (TS, Z161, 0x0205, 0x00, 0x00, Local0, 0x2468ACEF)
            }

            If (LNotEqual (BNK0, 0x12345675))
            {
                ERR (TS, Z161, 0x0208, 0x00, 0x00, BNK0, 0x12345675)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF0C, 0, Serialized)
    {
        Name (TS, "mf0c")
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32, 
            F001,   32
        }

        IndexField (F000, F001, ByteAcc, NoLock, Preserve)
        {
            IF00,   32
        }

        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Store (0x20, Arg0)
                Return (Add (Arg0, 0x05))
            }

            Add (Arg0, 0x01, Local0)
            Store (Local0, Arg0)
            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Method (M001, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Return (Add (Arg0, 0x05))
            }

            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (0x12345678, IF00) /* \MF0C.IF00 */
        Store (M000 (IF00), Local0)
        If (CHK1)
        {
            If (LNotEqual (Local0, 0x12121238))
            {
                ERR (TS, Z161, 0x023B, 0x00, 0x00, Local0, 0x12121238)
            }

            If (LNotEqual (IF00, 0x12121212))
            {
                ERR (TS, Z161, 0x023E, 0x00, 0x00, IF00, 0x12121212)
            }
        }

        Store (0x12345675, IF00) /* \MF0C.IF00 */
        Store (M001 (IF00), Local0)
        If (CHK1)
        {
            If (LNotEqual (Local0, 0x24242429))
            {
                ERR (TS, Z161, 0x0246, 0x00, 0x00, Local0, 0x24242429)
            }

            If (LNotEqual (IF00, 0x12121212))
            {
                ERR (TS, Z161, 0x0249, 0x00, 0x00, IF00, 0x12121212)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF0D, 0, Serialized)
    {
        Name (TS, "mf0d")
        Name (B000, Buffer (0x10){})
        CreateField (B000, 0x05, 0x20, BF00)
        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Store (0x20, Arg0)
                Return (Add (Arg0, 0x05))
            }

            Add (Arg0, 0x01, Local0)
            Store (Local0, Arg0)
            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (0x12345678, BF00) /* \MF0D.BF00 */
        Store (M000 (BF00), Local0)
        If (CHK0)
        {
            If (LNotEqual (Local0, 0x1234569E))
            {
                ERR (TS, Z161, 0x026F, 0x00, 0x00, Local0, 0x1234569E)
            }

            If (LNotEqual (BF00, Buffer (0x04)
                        {
                             0x78, 0x56, 0x34, 0x12                           // xV4.
                        }))
            {
                ERR (TS, Z161, 0x0272, 0x00, 0x00, BF00, Buffer (0x04)
                    {
                         0x78, 0x56, 0x34, 0x12                           // xV4.
                    })
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF0E, 0, Serialized)
    {
        Name (TS, "mf0e")
        Name (B000, Buffer (0x10){})
        CreateField (B000, 0x05, 0x20, BF00)
        Method (M001, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Return (Add (Arg0, 0x05))
            }

            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (0x12345675, BF00) /* \MF0E.BF00 */
        Store (M001 (BF00), Local0)
        If (CHK0)
        {
            If (LNotEqual (Local0, 0x2468ACEF))
            {
                ERR (TS, Z161, 0x0294, 0x00, 0x00, Local0, 0x2468ACEF)
            }

            If (LNotEqual (BF00, Buffer (0x04)
                        {
                             0x75, 0x56, 0x34, 0x12                           // uV4.
                        }))
            {
                ERR (TS, Z161, 0x0297, 0x00, 0x00, BF00, Buffer (0x04)
                    {
                         0x75, 0x56, 0x34, 0x12                           // uV4.
                    })
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF0F, 0, Serialized)
    {
        Name (TS, "mf0f")
        Name (B000, Buffer (0x10){})
        CreateField (B000, 0x05, 0x20, BF00)
        Method (M000, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Store (0x20, Arg0)
                Return (Add (Arg0, 0x05))
            }

            Add (Arg0, 0x01, Local0)
            Store (Local0, Arg0)
            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Method (M001, 1, NotSerialized)
        {
            Method (M001, 1, NotSerialized)
            {
                Return (Add (Arg0, 0x05))
            }

            Store (Add (Arg0, M001 (Arg0)), Local0)
            Return (Local0)
        }

        Store (0x12345678, BF00) /* \MF0F.BF00 */
        Store (M000 (BF00), Local0)
        If (CHK0)
        {
            If (LNotEqual (Local0, 0x1234569E))
            {
                ERR (TS, Z161, 0x02C9, 0x00, 0x00, Local0, 0x1234569E)
            }

            If (LNotEqual (BF00, Buffer (0x04)
                        {
                             0x78, 0x56, 0x34, 0x12                           // xV4.
                        }))
            {
                ERR (TS, Z161, 0x02CC, 0x00, 0x00, BF00, Buffer (0x04)
                    {
                         0x78, 0x56, 0x34, 0x12                           // xV4.
                    })
            }
        }

        Store (0x12345675, BF00) /* \MF0F.BF00 */
        Store (M001 (BF00), Local0)
        If (CHK0)
        {
            If (LNotEqual (Local0, 0x2468ACEF))
            {
                ERR (TS, Z161, 0x02D4, 0x00, 0x00, Local0, 0x2468ACEF)
            }

            If (LNotEqual (BF00, Buffer (0x04)
                        {
                             0x75, 0x56, 0x34, 0x12                           // uV4.
                        }))
            {
                ERR (TS, Z161, 0x02D7, 0x00, 0x00, BF00, Buffer (0x04)
                    {
                         0x75, 0x56, 0x34, 0x12                           // uV4.
                    })
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF10, 0, Serialized)
    {
        Name (TS, "mf10")
        Name (B000, Buffer (0x10){})
        CreateField (B000, 0x00, 0x20, BF00)
        Method (M000, 1, NotSerialized)
        {
            Return (Arg0)
        }

        OUTP (B000)
        Store (0x12345678, BF00) /* \MF10.BF00 */
        Store (M000 (BF00), Local0)
        OUTP (B000)
        If (LNotEqual (Local0, Buffer (0x04)
                    {
                         0x78, 0x56, 0x34, 0x12                           // xV4.
                    }))
        {
            ERR (TS, Z161, 0x0304, 0x00, 0x00, Local0, Buffer (0x04)
                {
                     0x78, 0x56, 0x34, 0x12                           // xV4.
                })
        }

        If (LNotEqual (BF00, Buffer (0x04)
                    {
                         0x78, 0x56, 0x34, 0x12                           // xV4.
                    }))
        {
            ERR (TS, Z161, 0x0307, 0x00, 0x00, BF00, Buffer (0x04)
                {
                     0x78, 0x56, 0x34, 0x12                           // xV4.
                })
        }

        Return (POUT) /* \POUT */
    }

    Method (MF11, 0, Serialized)
    {
        Name (TS, "mf11")
        Name (B000, Buffer (0x04)
        {
             0x10, 0x11, 0x12, 0x13                           // ....
        })
        Name (B001, Buffer (0x04)
        {
             0x10, 0x11, 0x12, 0x13                           // ....
        })
        Store (LEqual (B000, B001), Local3)
        Return (POUT) /* \POUT */
    }

    Method (MF12, 0, Serialized)
    {
        Name (TS, "mf12")
        Name (I000, 0x00)
        Name (I001, 0x00)
        Name (I002, 0x00)
        Name (I003, 0x00)
        Name (I004, 0x00)
        Name (I005, 0x00)
        Name (I006, 0x00)
        Name (I007, 0x00)
        Name (I008, 0x00)
        Name (I009, 0x00)
        Name (I00A, 0x00)
        Name (I00B, 0x00)
        Name (I00C, 0x00)
        Method (M000, 0, NotSerialized)
        {
            Method (M001, 0, NotSerialized)
            {
                Method (M002, 0, NotSerialized)
                {
                    Method (M003, 0, NotSerialized)
                    {
                        Method (M004, 0, NotSerialized)
                        {
                            Method (M005, 0, NotSerialized)
                            {
                                Method (M006, 0, NotSerialized)
                                {
                                    Method (M007, 0, NotSerialized)
                                    {
                                        Method (M008, 0, NotSerialized)
                                        {
                                            Method (M009, 0, NotSerialized)
                                            {
                                                Method (M00A, 0, NotSerialized)
                                                {
                                                    Method (M00B, 0, NotSerialized)
                                                    {
                                                        Method (M00C, 0, NotSerialized)
                                                        {
                                                            Store (0xABCD000C, I00C) /* \MF12.I00C */
                                                        }

                                                        Store (0xABCD000B, I00B) /* \MF12.I00B */
                                                        M00C ()
                                                    }

                                                    Store (0xABCD000A, I00A) /* \MF12.I00A */
                                                    M00B ()
                                                }

                                                Store (0xABCD0009, I009) /* \MF12.I009 */
                                                M00A ()
                                            }

                                            Store (0xABCD0008, I008) /* \MF12.I008 */
                                            M009 ()
                                        }

                                        Store (0xABCD0007, I007) /* \MF12.I007 */
                                        M008 ()
                                    }

                                    Store (0xABCD0006, I006) /* \MF12.I006 */
                                    M007 ()
                                }

                                Store (0xABCD0005, I005) /* \MF12.I005 */
                                M006 ()
                            }

                            Store (0xABCD0004, I004) /* \MF12.I004 */
                            M005 ()
                        }

                        Store (0xABCD0003, I003) /* \MF12.I003 */
                        M004 ()
                    }

                    Store (0xABCD0002, I002) /* \MF12.I002 */
                    M003 ()
                }

                Store (0xABCD0001, I001) /* \MF12.I001 */
                M002 ()
            }

            Store (0xABCD0000, I000) /* \MF12.I000 */
            M001 ()
        }

        M000 ()
        If (LNotEqual (I000, 0xABCD0000))
        {
            ERR (TS, Z161, 0x037D, 0x00, 0x00, I000, 0xABCD0000)
        }

        If (LNotEqual (I001, 0xABCD0001))
        {
            ERR (TS, Z161, 0x0380, 0x00, 0x00, I001, 0xABCD0001)
        }

        If (LNotEqual (I002, 0xABCD0002))
        {
            ERR (TS, Z161, 0x0383, 0x00, 0x00, I002, 0xABCD0002)
        }

        If (LNotEqual (I003, 0xABCD0003))
        {
            ERR (TS, Z161, 0x0386, 0x00, 0x00, I003, 0xABCD0003)
        }

        If (LNotEqual (I004, 0xABCD0004))
        {
            ERR (TS, Z161, 0x0389, 0x00, 0x00, I004, 0xABCD0004)
        }

        If (LNotEqual (I005, 0xABCD0005))
        {
            ERR (TS, Z161, 0x038C, 0x00, 0x00, I005, 0xABCD0005)
        }

        If (LNotEqual (I006, 0xABCD0006))
        {
            ERR (TS, Z161, 0x038F, 0x00, 0x00, I006, 0xABCD0006)
        }

        If (LNotEqual (I007, 0xABCD0007))
        {
            ERR (TS, Z161, 0x0392, 0x00, 0x00, I007, 0xABCD0007)
        }

        If (LNotEqual (I008, 0xABCD0008))
        {
            ERR (TS, Z161, 0x0395, 0x00, 0x00, I008, 0xABCD0008)
        }

        If (LNotEqual (I009, 0xABCD0009))
        {
            ERR (TS, Z161, 0x0398, 0x00, 0x00, I009, 0xABCD0009)
        }

        If (LNotEqual (I00A, 0xABCD000A))
        {
            ERR (TS, Z161, 0x039B, 0x00, 0x00, I00A, 0xABCD000A)
        }

        If (LNotEqual (I00B, 0xABCD000B))
        {
            ERR (TS, Z161, 0x039E, 0x00, 0x00, I00B, 0xABCD000B)
        }

        If (LNotEqual (I00C, 0xABCD000C))
        {
            ERR (TS, Z161, 0x03A1, 0x00, 0x00, I00C, 0xABCD000C)
        }

        Return (POUT) /* \POUT */
    }

    Method (MF13, 0, Serialized)
    {
        Name (TS, "mf13")
        Name (I000, 0x00)
        Name (I001, 0x00)
        Name (I002, 0x00)
        Name (I003, 0x00)
        Name (I004, 0x00)
        Name (I005, 0x00)
        Name (I006, 0x00)
        Name (I007, 0x00)
        Name (I008, 0x00)
        Name (I009, 0x00)
        Name (I00A, 0x00)
        Name (I00B, 0x00)
        Name (I00C, 0x00)
        Name (I00D, 0x00)
        Name (I00E, 0x00)
        Name (I00F, 0x00)
        Name (I010, 0x00)
        Method (M000, 0, NotSerialized)
        {
            Store (0xABCD0000, I000) /* \MF13.I000 */
        }

        Method (M001, 0, NotSerialized)
        {
            Store (0xABCD0001, I001) /* \MF13.I001 */
            M000 ()
        }

        Method (M002, 0, NotSerialized)
        {
            Store (0xABCD0002, I002) /* \MF13.I002 */
            M001 ()
        }

        Method (M003, 0, NotSerialized)
        {
            Store (0xABCD0003, I003) /* \MF13.I003 */
            M002 ()
        }

        Method (M004, 0, NotSerialized)
        {
            Store (0xABCD0004, I004) /* \MF13.I004 */
            M003 ()
        }

        Method (M005, 0, NotSerialized)
        {
            Store (0xABCD0005, I005) /* \MF13.I005 */
            M004 ()
        }

        Method (M006, 0, NotSerialized)
        {
            Store (0xABCD0006, I006) /* \MF13.I006 */
            M005 ()
        }

        Method (M007, 0, NotSerialized)
        {
            Store (0xABCD0007, I007) /* \MF13.I007 */
            M006 ()
        }

        Method (M008, 0, NotSerialized)
        {
            Store (0xABCD0008, I008) /* \MF13.I008 */
            M007 ()
        }

        Method (M009, 0, NotSerialized)
        {
            Store (0xABCD0009, I009) /* \MF13.I009 */
            M008 ()
        }

        Method (M00A, 0, NotSerialized)
        {
            Store (0xABCD000A, I00A) /* \MF13.I00A */
            M009 ()
        }

        Method (M00B, 0, NotSerialized)
        {
            Store (0xABCD000B, I00B) /* \MF13.I00B */
            M00A ()
        }

        Method (M00C, 0, NotSerialized)
        {
            Store (0xABCD000C, I00C) /* \MF13.I00C */
            M00B ()
        }

        Method (M00D, 0, NotSerialized)
        {
            Store (0xABCD000D, I00D) /* \MF13.I00D */
            M00C ()
        }

        Method (M00E, 0, NotSerialized)
        {
            Store (0xABCD000E, I00E) /* \MF13.I00E */
            M00D ()
        }

        Method (M00F, 0, NotSerialized)
        {
            Store (0xABCD000F, I00F) /* \MF13.I00F */
            M00E ()
        }

        Method (M010, 0, NotSerialized)
        {
            Store (0xABCD0010, I010) /* \MF13.I010 */
            M00F ()
        }

        M010 ()
        If (LNotEqual (I000, 0xABCD0000))
        {
            ERR (TS, Z161, 0x0422, 0x00, 0x00, I000, 0xABCD0000)
        }

        If (LNotEqual (I001, 0xABCD0001))
        {
            ERR (TS, Z161, 0x0425, 0x00, 0x00, I001, 0xABCD0001)
        }

        If (LNotEqual (I002, 0xABCD0002))
        {
            ERR (TS, Z161, 0x0428, 0x00, 0x00, I002, 0xABCD0002)
        }

        If (LNotEqual (I003, 0xABCD0003))
        {
            ERR (TS, Z161, 0x042B, 0x00, 0x00, I003, 0xABCD0003)
        }

        If (LNotEqual (I004, 0xABCD0004))
        {
            ERR (TS, Z161, 0x042E, 0x00, 0x00, I004, 0xABCD0004)
        }

        If (LNotEqual (I005, 0xABCD0005))
        {
            ERR (TS, Z161, 0x0431, 0x00, 0x00, I005, 0xABCD0005)
        }

        If (LNotEqual (I006, 0xABCD0006))
        {
            ERR (TS, Z161, 0x0434, 0x00, 0x00, I006, 0xABCD0006)
        }

        If (LNotEqual (I007, 0xABCD0007))
        {
            ERR (TS, Z161, 0x0437, 0x00, 0x00, I007, 0xABCD0007)
        }

        If (LNotEqual (I008, 0xABCD0008))
        {
            ERR (TS, Z161, 0x043A, 0x00, 0x00, I008, 0xABCD0008)
        }

        If (LNotEqual (I009, 0xABCD0009))
        {
            ERR (TS, Z161, 0x043D, 0x00, 0x00, I009, 0xABCD0009)
        }

        If (LNotEqual (I00A, 0xABCD000A))
        {
            ERR (TS, Z161, 0x0440, 0x00, 0x00, I00A, 0xABCD000A)
        }

        If (LNotEqual (I00B, 0xABCD000B))
        {
            ERR (TS, Z161, 0x0443, 0x00, 0x00, I00B, 0xABCD000B)
        }

        If (LNotEqual (I00C, 0xABCD000C))
        {
            ERR (TS, Z161, 0x0446, 0x00, 0x00, I00C, 0xABCD000C)
        }

        If (LNotEqual (I00D, 0xABCD000D))
        {
            ERR (TS, Z161, 0x0449, 0x00, 0x00, I00D, 0xABCD000D)
        }

        If (LNotEqual (I00E, 0xABCD000E))
        {
            ERR (TS, Z161, 0x044C, 0x00, 0x00, I00E, 0xABCD000E)
        }

        If (LNotEqual (I00F, 0xABCD000F))
        {
            ERR (TS, Z161, 0x044F, 0x00, 0x00, I00F, 0xABCD000F)
        }

        If (LNotEqual (I010, 0xABCD0010))
        {
            ERR (TS, Z161, 0x0452, 0x00, 0x00, I010, 0xABCD0010)
        }

        Return (POUT) /* \POUT */
    }

    Method (MF14, 0, Serialized)
    {
        Name (TS, "mf14")
        Name (I000, 0x00)
        Store (Timer, I000) /* \MF14.I000 */
        OUTP (I000)
        Return (POUT) /* \POUT */
    }

    Method (MF15, 0, Serialized)
    {
        Name (TS, "mf15")
        Store (0x1234567D, Local1)
        Store (0x08, Local2)
        Mod (Local1, Local2, Local0)
        OUTP (Local0)
        If (CHK0)
        {
            If (LNotEqual (Local0, 0x05))
            {
                ERR (TS, Z161, 0x047B, 0x00, 0x00, Local0, 0x05)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF16, 0, Serialized)
    {
        Name (TS, "mf16")
        Name (P000, Package (0x03)
        {
            0xABCD0000, 
            0xABCD0001, 
            0xABCD0003
        })
        Method (M000, 1, NotSerialized)
        {
            Return (Arg0)
        }

        Store (M000 (P000), Local0)
        Store (DerefOf (Index (Local0, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z161, 0x0495, 0x00, 0x00, Local0, 0xABCD0001)
        }

        Return (POUT) /* \POUT */
    }

    Method (MF17, 0, Serialized)
    {
        Name (TS, "mf17")
        Name (P000, Package (0x03)
        {
            0xABCD0000, 
            0xABCD0001, 
            0xABCD0003
        })
        Method (M000, 0, Serialized)
        {
            Name (PP00, Package (0x03)
            {
                0xABCD0000, 
                0xABCD0001, 
                0xABCD0003
            })
            Return (PP00) /* \MF17.M000.PP00 */
        }

        Store (M000 (), Local0)
        Store (DerefOf (Index (Local0, 0x01)), Local0)
        If (LNotEqual (Local0, 0xABCD0001))
        {
            ERR (TS, Z161, 0x04AF, 0x00, 0x00, Local0, 0xABCD0001)
        }

        Return (POUT) /* \POUT */
    }

    Method (MF18, 0, Serialized)
    {
        Name (TS, "mf18")
        Name (S000, "qwertyuiop")
        Name (S001, "qwertyuiop")
        Store (LEqual (S000, S001), Local3)
        If (CHK0)
        {
            Store (LEqual (S000, S001), Local0)
            If (LNot (Local0))
            {
                ERR (TS, Z161, 0x04C5, 0x00, 0x00, Local0, Ones)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF19, 0, Serialized)
    {
        Name (TS, "mf19")
        Name (B000, Buffer (0x04)
        {
             0x10, 0x11, 0x12, 0x13                           // ....
        })
        Name (B001, Buffer (0x04)
        {
             0x10, 0x11, 0x12, 0x13                           // ....
        })
        Store (LEqual (B000, B001), Local3)
        If (CHK0)
        {
            Store (LEqual (B000, B001), Local0)
            If (LNot (Local0))
            {
                ERR (TS, Z161, 0x04DC, 0x00, 0x00, Local0, Ones)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF1A, 0, Serialized)
    {
        Name (TS, "mf1a")
        Name (P000, Package (0x03)
        {
            0xABCD0000, 
            0xABCD0001, 
            0xABCD0003
        })
        Name (PP00, Package (0x03){})
        Store (P000, PP00) /* \MF1A.PP00 */
        If (CHK0)
        {
            Store (DerefOf (Index (PP00, 0x01)), Local0)
            If (LNotEqual (Local0, 0xABCD0001))
            {
                ERR (TS, Z161, 0x04F4, 0x00, 0x00, Local0, 0xABCD0001)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF1B, 0, Serialized)
    {
        Name (TS, "mf1b")
        Name (S000, "12345678")
        Name (S001, "56789012")
        Store (Add (S000, S001), Local3)
        If (CHK0)
        {
            Store (Add (S000, S001), Local0)
            If (LNotEqual (Local0, 0x68ACE68A))
            {
                ERR (TS, Z161, 0x050B, 0x00, 0x00, Local0, 0x68ACE68A)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF1C, 0, Serialized)
    {
        Name (TS, "mf1c")
        Name (B000, Buffer (0x04)
        {
             0x10, 0x11, 0x12, 0x13                           // ....
        })
        Name (B001, Buffer (0x04)
        {
             0x24, 0x35, 0x46, 0x57                           // $5FW
        })
        Store (Add (B000, B001), Local3)
        If (CHK0)
        {
            Store (Add (B000, B001), Local0)
            If (LNotEqual (Local0, 0x6A584634))
            {
                ERR (TS, Z161, 0x0522, 0x00, 0x00, Local0, 0x6A584634)
            }
        }

        Return (POUT) /* \POUT */
    }

    Method (MF1D, 0, Serialized)
    {
        Name (TS, "mf1d")
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32
        }

        Store (0xABCD0000, F000) /* \MF1D.F000 */
        Store (LEqual (F000, 0xABCD0000), Local3)
        Store (LEqual (F000, 0xABCD0000), Local0)
        If (LNot (Local0))
        {
            ERR (TS, Z161, 0x053A, 0x00, 0x00, Local0, Ones)
        }

        Return (POUT) /* \POUT */
    }

    Method (MF1E, 0, Serialized)
    {
        Name (TS, "mf1e")
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32
        }

        Store (0xABCD0000, F000) /* \MF1E.F000 */
        Method (M000, 1, NotSerialized)
        {
            Store (LEqual (Arg0, 0xABCD0000), Local0)
            Return (Local0)
        }

        M000 (F000)
        Store (M000 (F000), Local0)
        If (LNot (Local0))
        {
            ERR (TS, Z161, 0x0557, 0x00, 0x00, Local0, Ones)
        }

        Return (POUT) /* \POUT */
    }

    Method (MF1F, 0, Serialized)
    {
        Name (TS, "mf1f")
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32
        }

        Store (0xABCD0000, F000) /* \MF1F.F000 */
        Method (M000, 1, NotSerialized)
        {
            If (LNotEqual (Arg0, 0xABCD0000))
            {
                ERR (TS, Z161, 0x056D, 0x00, 0x00, Arg0, 0xABCD0000)
            }
        }

        M000 (F000)
        Return (POUT) /* \POUT */
    }

    Method (MF20, 0, Serialized)
    {
        Name (TS, "mf20")
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32
        }

        Store (0xABCD0000, F000) /* \MF20.F000 */
        Store (Add (F000, 0x12), Local3)
        Store (Add (F000, 0x12), Local0)
        If (LNotEqual (Local0, 0xABCD0012))
        {
            ERR (TS, Z161, 0x0587, 0x00, 0x00, Local0, 0xABCD0012)
        }

        Return (POUT) /* \POUT */
    }

    Method (MF21, 0, Serialized)
    {
        Name (TS, "mf21")
        OperationRegion (R000, SystemMemory, 0x0100, 0x0100)
        Field (R000, ByteAcc, NoLock, Preserve)
        {
            F000,   32
        }

        Store (0xABCD0000, F000) /* \MF21.F000 */
        Method (M000, 1, NotSerialized)
        {
            Store (Add (Arg0, 0x12), Local0)
            Return (Local0)
        }

        M000 (F000)
        Store (M000 (F000), Local0)
        If (LNotEqual (Local0, 0xABCD0012))
        {
            ERR (TS, Z161, 0x05A4, 0x00, 0x00, Local0, 0xABCD0012)
        }

        Return (POUT) /* \POUT */
    }

    Method (MF22, 0, Serialized)
    {
        Name (TS, "mf22")
        OperationRegion (R003, SystemMemory, 0x0180, 0x80)
        Field (R003, ByteAcc, NoLock, Preserve)
        {
            F004,   32, 
            F005,   32
        }

        IndexField (F004, F005, ByteAcc, NoLock, Preserve)
        {
            IF02,   32
        }

        Store (0xABCD0000, IF02) /* \MF22.IF02 */
        Method (M000, 1, NotSerialized)
        {
            If (LNotEqual (Arg0, 0xABABABAB))
            {
                ERR (TS, Z161, 0x05BB, 0x00, 0x00, Arg0, 0xABABABAB)
            }
        }

        M000 (IF02)
        Return (POUT) /* \POUT */
    }

    Method (MF23, 0, Serialized)
    {
        Name (TS, "mf23")
        OperationRegion (R003, SystemMemory, 0x0180, 0x80)
        Field (R003, ByteAcc, NoLock, Preserve)
        {
            F004,   32, 
            F005,   32
        }

        IndexField (F004, F005, ByteAcc, NoLock, Preserve)
        {
            IF02,   32
        }

        Store (0xABCD0000, IF02) /* \MF23.IF02 */
        Method (M000, 2, NotSerialized)
        {
            If (LNotEqual (Arg0, 0xABABABAB))
            {
                ERR (TS, Z161, 0x05D5, 0x00, 0x00, Arg0, 0xABABABAB)
            }

            If (LNotEqual (Arg1, 0xABABABAB))
            {
                ERR (TS, Z161, 0x05D8, 0x00, 0x00, Arg1, 0xABABABAB)
            }
        }

        M000 (IF02, IF02)
        Return (POUT) /* \POUT */
    }

    Method (MF24, 0, Serialized)
    {
        Name (TS, "mf24")
        OperationRegion (R003, SystemMemory, 0x0180, 0x80)
        Field (R003, ByteAcc, NoLock, Preserve)
        {
            F004,   32, 
            F005,   32
        }

        IndexField (F004, F005, ByteAcc, NoLock, Preserve)
        {
            IF02,   32
        }

        Store (0xABCD0000, IF02) /* \MF24.IF02 */
        Method (M001, 1, NotSerialized)
        {
            If (LNotEqual (Arg0, 0xABABABAB))
            {
                ERR (TS, Z161, 0x05F2, 0x00, 0x00, Arg0, 0xABABABAB)
            }

            Return (Arg0)
        }

        Method (M002, 2, NotSerialized)
        {
            If (LNotEqual (Arg0, 0xABABABAB))
            {
                ERR (TS, Z161, 0x05F9, 0x00, 0x00, Arg0, 0xABABABAB)
            }

            If (LNotEqual (Arg1, 0xABABABAB))
            {
                ERR (TS, Z161, 0x05FC, 0x00, 0x00, Arg1, 0xABABABAB)
            }

            Return (Arg1)
        }

        Store (M001 (IF02), Local0)
        Store (M002 (IF02, IF02), Local0)
        Return (POUT) /* \POUT */
    }

    Method (MF25, 0, Serialized)
    {
        Return (POUT) /* \POUT */
    }

    Method (MF27, 0, Serialized)
    {
        Return (POUT) /* \POUT */
    }

    Method (MF28, 0, Serialized)
    {
        Return (POUT) /* \POUT */
    }

    Method (MF29, 1, Serialized)
    {
        Return (POUT) /* \POUT */
    }

    Method (MF2A, 1, Serialized)
    {
        Return (POUT) /* \POUT */
    }

    Method (MF2B, 0, Serialized)
    {
        Return (POUT) /* \POUT */
    }

    Method (MF2C, 1, Serialized)
    {
        Return (POUT) /* \POUT */
    }

    Method (MSF0, 0, NotSerialized)
    {
        SRMT ("mf00")
        If (CHK0)
        {
            MF00 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf01")
        MF01 ()
        SRMT ("mf02")
        If (CHK0)
        {
            MF02 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf03")
        MF03 ()
        SRMT ("mf04")
        If (LAnd (CHK0, Y275))
        {
            MF04 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf05")
        MF05 ()
        SRMT ("mf06")
        MF06 ()
        SRMT ("mf07")
        MF07 ()
        SRMT ("mf08")
        If (CHK0)
        {
            MF08 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf09")
        If (CHK0)
        {
            MF09 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf0a")
        MF0A ()
        SRMT ("mf0b")
        MF0B ()
        SRMT ("mf0c")
        MF0C ()
        SRMT ("mf0d")
        If (CHK0)
        {
            MF0D ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf0e")
        If (CHK0)
        {
            MF0E ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf0f")
        If (CHK0)
        {
            MF0F ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf10")
        If (CHK0)
        {
            MF10 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf11")
        If (CHK0)
        {
            MF11 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf12")
        If (CHK0)
        {
            MF12 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf13")
        If (CHK0)
        {
            MF13 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf14")
        If (CHK0)
        {
            MF14 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf15")
        If (CHK0)
        {
            MF15 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf16")
        MF16 ()
        SRMT ("mf17")
        MF17 ()
        SRMT ("mf18")
        If (CHK0)
        {
            MF18 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf19")
        If (CHK0)
        {
            MF19 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf1a")
        If (CHK0)
        {
            MF1A ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf1b")
        If (CHK0)
        {
            MF1B ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf1c")
        If (CHK0)
        {
            MF1C ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf1d")
        MF1D ()
        SRMT ("mf1e")
        MF1E ()
        SRMT ("mf1f")
        MF1F ()
        SRMT ("mf20")
        MF20 ()
        SRMT ("mf21")
        MF21 ()
        SRMT ("mf22")
        MF22 ()
        SRMT ("mf23")
        MF23 ()
        SRMT ("mf24")
        MF24 ()
        SRMT ("mf25")
        If (SLC0)
        {
            MF25 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf26")
        If (LAnd (SLC0, CHK0))
        {
            MF26 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf27")
        If (SLC0)
        {
            MF27 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf28")
        If (SLC0)
        {
            MF28 ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf29")
        If (SLC0)
        {
            MF29 (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf2a")
        If (SLC0)
        {
            MF2A (0x00)
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf2b")
        If (LAnd (SLC0, CHK0))
        {
            MF2B ()
        }
        Else
        {
            BLCK ()
        }

        SRMT ("mf2c")
        If (LAnd (SLC0, CHK0))
        {
            MF2C (0x00)
        }
        Else
        {
            BLCK ()
        }
    }

    Method (RST8, 0, NotSerialized)
    {
        Store (0x00, ERRS) /* \ERRS */
        Store (0x00, RMRC) /* \RMRC */
    }

    Method (IIN0, 0, NotSerialized)
    {
        RST8 ()
        RST9 ()
        IIN1 ()
    }

    Method (OUTC, 1, NotSerialized)
    {
        If (PRT0)
        {
            OUTP (Arg0)
        }
    }

    Method (MAIN, 0, NotSerialized)
    {
        STRT (0x00)
        IIN0 ()
        If (STTT ("Tests applicable to both AcpiExec and MS-abbu utilities", TCLT, 0x00, W019))
        {
            INI0 ()
            INI1 ()
            INI2 ()
            INI3 ()
            INI4 ()
            INI5 ()
            MTFF ()
            MSFF ()
            MSFE ()
            MSF0 ()
            MRFF ()
        }

        FTTT ()
        Store (FNSH (), Local7)
        If (ABUU)
        {
            Return (POUT) /* \POUT */
        }

        Return (Local7)
    }

    Name (POUT, Package (0x01)
    {
        "EMPTY"
    })
    Method (OUTP, 1, NotSerialized)
    {
        Store (Arg0, Debug)
    }

    Method (RST9, 0, NotSerialized)
    {
    }

    Scope (\_SB)
    {
        Device (ABBU)
        {
            Name (_HID, "ACPIABB0")  // _HID: Hardware ID
            Method (ENBL, 0, NotSerialized)
            {
                Return (Zero)
            }

            Method (TEST, 0, NotSerialized)
            {
                Return (Zero)
            }

            Method (TST, 0, NotSerialized)
            {
                Return (TSTS) /* \_SB_.ABBU.TSTS */
            }

            Name (TSTS, Package (0x03)
            {
                "ENBL", 
                "TEST", 
                "TST_"
            })
        }
    }
}

