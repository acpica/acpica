DefinitionBlock("test.aml", "DSDT", 0x02, "Intel", "Many", 0x00000001) 
{
    Name (ABC,0)
    include ("test2.asl")
    include ("test3.asl")
    Name (DEF,0)
}
