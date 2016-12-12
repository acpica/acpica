DefinitionBlock("testFieldComment.aml", "DSDT", 0x02, "Intel", "Many", 0x00000001) 
{



    OperationRegion(GNVS,SystemMemory,0xFFFF0000,0xAA55)
    Field(GNVS,AnyAcc,Lock,Preserve)
    {//c3
    //c4
    , 0, // 0-bit offset
    OSYS, 8, //c5
    }//c6
 

}

