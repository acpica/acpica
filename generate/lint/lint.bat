"C:\Program Files\Lint\Lint-nt"  +v  -i"C:\Acpi\Generate\Lint"  std64.lnt  -os(C:\Acpi\Generate\Lint\LintOut.txt) %1 %2 %3 %4 %5 %6 %7 %8 %9
echo "64-bit lint completed" >> c:\acpi\Generate\lint\LintOut.txt
"C:\Program Files\Lint\Lint-nt"  +v  -i"C:\Acpi\Generate\Lint"  std32.lnt  +os(C:\Acpi\Generate\Lint\LintOut.txt) %1 %2 %3 %4 %5 %6 %7 %8 %9
echo "32-bit lint completed" >> c:\acpi\Generate\lint\LintOut.txt
"C:\Program Files\Lint\Lint-nt"  +v  -i"C:\Acpi\Generate\Lint"  std16.lnt  +os(C:\Acpi\Generate\Lint\LintOut.txt) %1 %2 %3 %4 %5 %6 %7 %8 %9
echo "16-bit lint completed" >> c:\acpi\Generate\lint\LintOut.txt
@echo off
echo ---
echo  output placed in C:\Acpi\Generate\Lint\LintOut.txt

