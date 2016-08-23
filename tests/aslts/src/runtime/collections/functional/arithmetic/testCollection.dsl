/*
 * Intel ACPI Component Architecture
 * AML/ASL+ Disassembler version 20160729-64
 * Copyright (c) 2000 - 2016 Intel Corporation
 * 
 * Disassembling to symbolic ASL+ operators
 *
 * Disassembly of testCollection.aml, Tue Aug 23 09:29:03 2016
 *
 * Original Table Header:
 *     Signature        "DSDT"
 *     Length           0x000004C1 (1217)
 *     Revision         0x02
 *     Checksum         0x6B **** Incorrect checksum, should be 0x3E
 *     OEM ID           "Intel"
 *     OEM Table ID     "Many"
 *     OEM Revision     0x00000001 (1)
 *     Compiler ID      "INTL"
 *     Compiler Version 0x20160729 (538314537)
 */
/* top of the 
 * definition block
 */
DefinitionBlock ("", "DSDT", 2, "Intel", "Many", 0x00000001)
{
    Name (/*c00*/ B, /*c01*/0x05 /*c02*/)/*c03*/
    Method (MAIN, 0, NotSerialized)
    { 
        //comment
        /**********************************************************************
         *                                                                    *
         *                     This is a comment                              *
         *                   there are many like it                           *
         *                    but this one is mine!                           *
         *                                                                    *
         **********************************************************************/
        Name (/*c04*/ C,     /*c05*/0x05      /*c06*/)     /*c07*/
        Name (//c08 D,     //c090x06      //c10)     //c11
        //c
        If (0x01 == 0x01)//thisisareallylongcomment
        { 
            //c1
            Name (B, 0x00)
        }   //c2
    }

    //c0
    Name (/*c1*/ A,  /*c2*/Package (0x03)
    { 
        /*c5*/
        0x04,  /*c6*/
        /*comment*/
        0x05,  /*c7*/
        0x06   /*c8*/
    } /*c9*/)/*c10*/
    //XXX0
    Method (F1, 0, NotSerialized)
    { 
        //XXX1
        Name (T, Package (0x03)
        { 
            0x04, 
            0x05, 
            0x06
        })
        //XXX2
        Name (/*c08*/ D1,     /*c09*/0x06      /*c10*/)     /*c11*/
    }

    //XXX3   
    Method (SCOP, 0, NotSerialized)
    { 
        //XXX4
        Name (A1, 0x04)
    }

    OperationRegion (GNVS, SystemMemory, 0xFFFF0000, 0xAA55)
    Field (GNVS, AnyAcc, Lock, Preserve)
    { 
        //c0
        Offset (0x00),  //comments are 
        OSYS,    8 //everywhere
    }
}  //comment
/*ending 
 comment*/


