
//
// Interfaces to the Generic ACPI Subsystem
//

#define OBJECT_DESCRIPTOR       void
#define ACPI_MODE               1
#define LEGACY_MODE             2
#define DISABLE_KNOWN_EVENTS    8


int 
AcpiInit (char *);

int
AcpiLoadNameSpace (int iDisplayAmlDuringLoad);

int
AcpiExecuteMethod (char * pcMethodName, OBJECT_DESCRIPTOR **ppsReturnValue,
                    OBJECT_DESCRIPTOR **ppsParams);

void
AcpiCleanup (void);

int
AcpiSetMode (int iMode);

int
AcpiModeStatus (void);

int
AcpiModeCapabilities (void);

int
AcpiEnable (char *pcTestName, int iFlags);
