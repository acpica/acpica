/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160729-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembling to symbolic ASL+ operators
 *
 * Disassembly of test.aml, Mon Aug 22 15:58:45 2016
 *
 * Original Table Header:
 *     Signature        "DSDT"
 *     Length           0x0000007B (123)
 *     Revision         0x02
 *     Checksum         0xBB **** Incorrect checksum, should be 0x82
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
        If ( //c6 0x01 == 0x01){ }
        Else
        { 
            //c7
            Name (D, 0x00)//c8
        } //c9

        //c10
        Name (E, 0x00)//c11
    }
}

