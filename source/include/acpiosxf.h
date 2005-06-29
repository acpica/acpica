
// File I/O

#define OSD_FILE    char
#ifndef size_t
#define size_t      unsigned long
#endif

OSD_FILE *OsdOpen (const char *filename, const char *mode);
int OsdClose (OSD_FILE *stream);

size_t OsdRead (void *buffer, size_t size, size_t count, OSD_FILE *stream);
size_t OsdWrite (const void *buffer, size_t size, size_t count, OSD_FILE *stream); 

int OsdPrintf (OSD_FILE *stream, const char *format, ...);
int OsdFlushall (void);

// Memory allocation

void *OsdAllocate (unsigned long size);
char *OsdCallocate (unsigned long num, unsigned long size);
void OsdFree (void *mem);

// Memory mapping

char *OsdMapMemory (unsigned long where, unsigned long length);
void OsdUnMapMemory (char * where, unsigned long length);

// Interrupt handlers

void *OsdInstallInterruptHandler (
    unsigned long       InterruptNumber,
    int                 (* Isr)(void),
    unsigned long *     ExceptPtr);


// Misc

int OsdAssert (void *);


