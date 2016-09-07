DefinitionBlock("testFieldComment.aml", "DSDT", 0x02, "Intel", "Many", 0x00000001) 
{



    OperationRegion(GNVS,SystemMemory,0xFFFF0000,0xAA55)
    Field(GNVS,AnyAcc,Lock,Preserve)
    {//c3
    //c4
    Offset(0),      OSYS, 8, //c5
    Offset(2),      ABCD, 8, //c6
    }//c7
 

}

