/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160527-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembling to symbolic ASL+ operators
 *
 * Disassembly of test.aml, Fri Aug 12 17:38:02 2016
 *
 * Original Table Header:
 *     Signature        "DSDT"
 *     Length           0x0000008F (143)
 *     Revision         0x02
 *     Checksum         0xC5 **** Incorrect checksum, should be 0x42
 *     OEM ID           "Intel"
 *     OEM Table ID     "Many"
 *     OEM Revision     0x00000001 (1)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20160527 (538314023)
 */
DefinitionBlock ("", "DSDT", 2, "Intel", "Many", 0x00000001)
{
    Name (ABC, 0x00)
    Include ("test2.dsl")
    Include ("test3.dsl")
    Name (DEF, 0x00)
}

