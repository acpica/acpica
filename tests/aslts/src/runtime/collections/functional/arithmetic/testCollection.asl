/* top of the 
 * definition block
 */
DefinitionBlock("testCollection.aml", "DSDT", 0x02, "Intel", "Many", 0x00000001) 
{


    Name (/*c00*/ b,/*c01*/ 5/*c02*/)/*c03*/
 
    Method(MAIN) {
        //comment
        /**********************************************************************
         *                                                                    *
         *                     This is a comment                              *
         *                   there are many like it                           *
         *                    but this one is mine!                           *
         *                                                                    *
         **********************************************************************/
        Name (/*c04*/
        c,    /*c05*/
        5     /*c06*/
        )     /*c07*/
        Name (//c08
        d,    //c09
        6     //c10
        )     //c11
        //c
        if(1==1)//thisisareallylongcomment
        {   //c1
            Name(b,0);
        }  //c2
 
 
    }

   //c0
   Name (/*c1*/ a, /*c2*/
       Package(3)/*c4*/
       {/*c5*/
            0x04, /*c6*/
            /*comment*/
            0x05, /*c7*/
            0x06  /*c8*/
       }/*c9*/
   )/*c10*/


    //XXX0
    Method(F1) {
        //XXX1
        Name (t, 
            Package(3)
            {
                0x04, 
                0x05,
                0x06
            }
        )

        //XXX2
   
        Name (/*c08*/
        d1,    /*c09*/
        6     /*c10*/
        )     /*c11*/
 
    }
   
    //XXX3   
    Method(SCOP)
    {
        //XXX4
        Name (a1, 0x04)
    }

    OperationRegion(GNVS,SystemMemory,0xFFFF0000,0xAA55)

    Field(GNVS,AnyAcc,Lock,Preserve)
    {
        //c0
        Offset(0),//comments are 
        OSYS, 8//everywhere
    }


} //comment
/*ending 
  comment*/

