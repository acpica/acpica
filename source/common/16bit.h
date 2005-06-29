 
 

#define GET_SEGMENT(ptr)            ((UINT16)(_segment)(ptr))
#define GET_OFFSET(ptr)             ((UINT16)(UINT32) (ptr))
#define GET_PHYSICAL_ADDRESS(ptr)   (((((UINT32)GET_SEGMENT(ptr)) << 4)) + GET_OFFSET(ptr))
#define PTR_OVL_BUILD_PTR(p,b,o)    {p.ovl.base=b;p.ovl.offset=o;}

typedef union ptr_ovl
{
    void                *ptr;
    UINT32              dword;
    struct
    {
        UINT16              offset;
        UINT16              base;
    } ovl;

} PTR_OVL;


 
int
FlatMove (
    UINT32              Dest,
    UINT32              Src,
    UINT32              Size);


NATIVE_INT
AfWriteBuffer (
    char                *Filename,
    char                *Buffer,
    UINT32              Length);

char *
AfGenerateFilename (char *TableId);


ACPI_STATUS
AfFindDsdt(
    UINT8               **DsdtPtr,
    UINT32              *DsdtLength);

void
AfDumpTables (void);

