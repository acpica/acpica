
/*
 * Generation of ACPICA with MS Visual Studio 2008
 */

ACPICA generates with all language extensions disabled, since the code
is meant to be highly portable.

There are a couple of include files in MS Visual Studio 2008 that
contain // comments. These will be flagged as warnings. To eliminate
these warnings, modify these include files:


1) \Program Files\Microsoft Visual Studio 9.0\VC\include\sal.h

Add this to the start of the file:

#pragma warning( disable : 4001 ) /* no warning about "//" comments */

Add this to the end of the file:

#pragma warning( default : 4001 )


2) \Program Files\Microsoft Visual Studio 9.0\VC\include\stdlib.h

Line 773: Change // comment to a /* */ comment

