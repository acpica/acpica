/*
 * Configuration constants for the ACPI subsystem
 */

#ifndef _CONFIG_H
#define _CONFIG_H

#define VERBOSE_DEBUG /* TEMP!!! */

/* 
 * All scary-looking constants should go here!!! 
 * 
 * Some of these should be fixed or at least made run-time configurable.
 *
 */

#define WHYBUF_SIZE                 512     /* Runtime error message communication */

#define MAX_STRING_LENGTH           512

/*
 * AML Interpreter
 */

#define MAX_ACPI_TABLE_SIZE         49152   /* For phys to logical mapping */
#define AML_PKG_MAX_NEST            100     /* Max depth of package nesting */
#define AML_METHOD_MAX_NEST         10      /* Max depth of nested method calls */
#define INITIAL_NAME_BUF_SIZE       32
#define AML_EXPR_MAX_NEST           100     /* Max stack depth parsing expressions */


/* 
 * NameSpace Table sizes
 * 
 * If USE_HASHING is #defined, these must be prime numbers and
 * should be large enough that the tables never get terribly full.
 *
 * The root NT was made bigger than others in the possibly erroneous
 * expectation that there might be quite a few entries in the root.
 */

#ifdef USE_HASHING
#define ROOTSIZE                    101     /* # of slots in root table */
#define TABLSIZE                    53      /* # of slots per table below the root */

#else
#define ROOTSIZE                    40      /* initial # of slots in root table */
#define TABLSIZE                    20      /* initial # of slots per table below the root */
#endif

#define MAXNEST                     15      /* Max nesting of name scopes, used for sizing stacks */


/* 
 * Defining FETCH_VALUES enables AcpiExecuteMethod() to "execute"
 * a name which is not a Method by fetching and returning its value.
 */
#define FETCH_VALUES

#endif /* _CONFIG_H */

