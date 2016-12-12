DefinitionBlock(
	"MAIN1.aml",
	"DSDT", 
	0x02,    
	"Intel",  
	"Many",    
	0x00000001  
	) {
    // include for test1
    Include("test1.asl")
    Include("test6.asl")

    Method(MAIN) 
    {
        // include for test 8
        Include("test8.asl")
        return (2)
    }
}
