# How to add a new ACPI table support to ACPICA
This file describes how to add support for a new table and its subtables to
ACPICA. While it tries to be as specific as possible some details or corner
cases might not be present here - in such situations try looking at how similar
tables are implemented in the files that are mentioned.

## Naming convention
To make things generic here the X will signify the new table name. So for the
MADT table the ACPI_X_OFFSET() macro will mean ACPI_MADT_OFFSET().

## Table header definitions
You need to add the header fields from the main table and the subtables (if they
exist in your case) to one of the actbl*.h files. There are three such numbered
files and there isn't a clear idea on how they are split at this point. For a
while now new tables have been added to actbl2.h, so that's where it's
recommended to add new ones.

Generally use other already defined tables for guidance on how to add new ones
to these header files. But additionally remember to:

1. Use ACPI_TABLE_HEADER for the type of the common part of the main header.
2. Define sub-tables separately from the main table.
3. If a table is not from ACPI spec, note down in a comment where the
   specification came from.
4. Add ACPI_SIG_X entry for your table, it will later be used to connect
   compile and dump functions.

## Common part - setup
### ACPI_X_OFFSET
Go to the source/include/actbinfo.h file to add a new ACPI_X_OFFSET. Main table
offset definitions are located at the top of the file. The subtable definitions
are located further into the file. Match the ACPI_X_OFFSET() to the table you
added in actbl2.h or actbl3.h.

### Sub-table
Add sub-table names in source/common/dmtable.c by creating an AcpiDmXSubnames[]
array with full names of the subtables. This will come in handy when handling
table dumping for human readability.

Remember to add one additional entry for an unknown subtable, specifically in
this format:
```C
    "Unknown Subtable Type"         /* Reserved */
```

## Disassembler part
### DMTABLE
You need to create entries for the main table and subtables. Analogously to
actbl*.h it needs to happen in source/common/dmtbinfo*.c. Just create entries in
the format of 'AcpiDmTableInfoX'. Try to fit the new entries in the correct
dmtbinfo*.c file so it's alphabetical.

Don't forget to add a ACPI_DMT_TERMINATOR at the end of each ACPI_DMTABLE_INFO
you add.

Add the newly added AcpiDmTableInfoX to source/include/acdisasm.h with the
extern keyword - keep the array names alphabetical.

If any of your fields have a special type that defines some unique values you
need to specify a new ACPI entry type. For further instructions on adding a new special
type look to the chapters below.

### Special Dump Table function
Go to source/common/dmtbdumpY.c where Y is either 1, 2 or 3. Pick the file based
on where your table fits alphabetically in these files. Then add an AcpiDmDumpX()
function, and add its header to source/include/acdisasm.h.

This function is supposed to utilize AcpiDmDumpTable() calls on main table and
subtables, catch errors or print more custom information that doesn't fit into
table definitions. For specific cases look at tables with a similar layout and
how they handle this custom dumping function.

## Compiler part
### Special Compile function
In source/compiler/dtcompiler.h declare DtCompileX(). Afterwards write the
function body in source/compiler/dttableY.c where Y is either 1 or 2. Pick one
based on where your table fits alphabetically.

In the function body use DtCompileTable() to compile the table formats you
previously created. To connect tables with subtables use DtPeekSubtable() and
DtInsertSubtable(). You can insert custom compilation paths based on the ASL
format read from PFieldList for example. You can insert data into table elements
based on the compilation process (for example counting how many subtables there
are and setting the subtable counter field). For details on how to connect
subtables to the main table or how to modify table elements browse the
dttable*.c files.

## Common part - plugging functions
### Connection signature
Go to source/common/ahtable.c and using the ACPI_SIG_X entry you added in the
beginning, add an entry to the AcpiGbl_SupportedTables[] array.

### Connect functions to the signature
In source/common/dmtable.c go to the AcpiDmTableData[] and add an entry using
your ACPI_SIG_X signature. Don't fill out the last column (Template) just yet,
it's used for testing/browsing table formats and we'll have to come back to this
point at the end.

If your table has a simple non-dynamic structure, then only the TableInfo
(second column) is required - third and fourth columns are not needed. However
if your table has subtables or a more complex structure (like a non-static
amount of data at the end of the main table) then the third and fourth columns
are likely both needed. They connect custom compile and decompile functions that
can handle more complex table layouts.

Usually you'll need to add both, in rare exceptions you might need only one of
the two AND the second column entry (TableInfo). This is in case a table is for
example simple to dump (size determines the trailing data) but compiling needs
custom code. UEFI is such an example.

## Tools support
Add all the structures you created in actbl*.h to
source/tools/acpisrc/astable.c. Remember to keep the alphabetical order of
entries.

## Adding ACPI ENTRY TYPES
Add an *enum* for that type in ACPI_ENTRY_TYPES (located in
source/include/acdisasm.h).

### Dump table code
Go to source/common/dmtable.c and modify AcpiDmDumpTable():

#### Set byte length
Add a case to the switch where the ByteLength variable is set

#### Printing
Add a case to the switch where the dumping/printing part happens. If it's a
number type (like a flag) just print it using AcpiOsPrintf(). If for example
the type signifies subtable types, print the subtable names from a
complementary AcpiDmXSubnames[] name array. Generally this part depends on
what the type is - look for similarities to your type in other cases in this
switch statement.

One common thing is clamping down subtable type using the
'Unknown Subtable Type' string in the Subnames string array. It can look like
this:

```C
Temp8 = *Target;
if (Temp8 > ACPI_X_RESERVED)
{
    Temp8 = ACPI_X_RESERVED;
}
```

The ACPI_X_RESERVED fits into the actbl*.h file where you list the subtable
types - so if you didn't add it before add it now.

### Compiler support
Go to source/compiler/dtutils.c and modify DtGetFieldLength():
1. Add a case to the switch where the ByteLength variable is set

## Adding the hex template
After adding support for the compiler and decompiler you should generate a
hex representation of the new table. It can be later used in automatic testing
that the compiler and decompiler remain consistent and don't mess up data when
moving in a circle between ASL and AML.

First write a field list .asl file with the new table based on the documentation
of your new table and in the format of one line per field :
"[ByteLength] FieldName : HexValue"

Some things to remember:
- FieldName strings should match the strings you wrote in the ACPI_DMTABLE_INFO
  entries.
- Signature field is the table name.
- Table Length and Checksum should be 0 - iasl will set it during compilation.
- Add all the trailing data there can be to maximize test coverage.

A field list source example can look like this (main table and trailing
sub-table pointer data):
```asl
[0004]                          Signature : "XXXX"
[0004]                       Table Length : 00000000
[0001]                           Revision : 01
[0001]                           Checksum : 00
[0006]                             Oem ID : "YYYYY "
[0008]                       Oem Table ID : "Template"
[0004]                       Oem Revision : 00000001
[0004]                    Asl Compiler ID : "ZZZZ"
[0004]              Asl Compiler Revision : 00000000

[0004]               Number of Sub-tables : 00000001

[0001]                     Sub-table Type : 00
[0007]                           Reserved : 00 00 00 00 00 00 00
[0008]         Sub-table Physical Address : 0000000012340000
```

Then build the project and use the newly built iasl binary to compile the field
list table file into a hex format:
```bash
iasl -tc table_file.asl
```

Afterwards open the output table_file.hex and from there copy the unsigned char
array. Paste it into source/compiler/dttemplate.h. and rename to
'const unsigned char TemplateX[]'. Remember to keep the file in alphabetical
order based on the table name.

After adding the template to the header file you can now go back to
source/common/dmtable.c and add the template to the AcpiDmTableData[] entry for
your table. Also declare the template with an extern keyword in
source/compiler/dtcompiler.h so it can be linked elsewhere.
