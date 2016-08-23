/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160729-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembling to symbolic ASL+ operators
 *
 * Disassembly of test.aml, Tue Aug 23 13:38:00 2016
 *
 * Original Table Header:
 *     Signature        "DSDT"
 *     Length           0x00000043 (67)
 *     Revision         0x02
 *     Checksum         0xE3 **** Incorrect checksum, should be 0x64
 *     OEM ID           "Intel"
 *     OEM Table ID     "Many"
 *     OEM Revision     0x00000001 (1)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20160729 (538314537)
 */
DefinitionBlock ("", "DSDT", 2, "Intel", "Many", 0x00000001)
{
    Method (MAIN, 0, NotSerialized)
    { 
        Name (D, "abcdef")
    }
}

