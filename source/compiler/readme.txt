
Instructions for integrating iASL compiler into MS VC++ 6.0 environment.

This procedure adds the iASL compiler as a custom tool that can be used
to compile ASL source files.  The output is sent to the VC output 
window.

1) Select Tools->Customize.

2) Select the "Tools" tab.

3) Scroll down to the bottom of the "Menu Contents" window.  There you
   will see an empty rectangle.  Click in the rectangle to enter a 
   name for this tool.

4) Type "iASL Compiler" in the box and hit enter.  You can now edit
   the other fields for this new custom tool.

5) Enter the following into the fields:

   Command:             C:\Acpi\iasl.exe
   Arguments:           -e $(FilePath)
   Initial Directory    $(FileDir)
   Use Output Window    <Check this option>

   "Command" must be the path to wherever you copied the compiler.
   "-e" instructs the compiler to produce messages appropriate for VC.

6) Select "Close".

These steps will add the compiler to the tools menu as a custom tool.
By enabling "Use Output Window", you can click on error messages in
the output window and the source file and source line will be
automatically displayed by VC.  Also, you can use F4 to step through
the messages and the corresponding source line(s).


