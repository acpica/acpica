DefinitionBlock("ift.aml", "DSDT", 0x02, "Intel", "Many", 0x00000001)
{
    Method(MAIN) {
        if (1==1)
        { //one is one
	   Name (a, 0)
        }
        else //after else
        {
            //c7
            Name(d,0)//c8
        }//c9
        //c10
        Name(e,0)//c11

        if (1==1)
        {
        //nothing
        }
        //c12
    }
}

