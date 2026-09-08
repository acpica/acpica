/*
 * Minimal namespace shadowing repro for ACPICA runtime diagnostics.
 *
 * Compile with iasl and load with acpiexec to observe the warning emitted when
 * \_SB.ASMI is created while \ASMI already exists in an ancestor scope.
 */
DefinitionBlock ("namespace-shadowing.aml", "DSDT", 2, "TEST", "NSWARN", 0)
{
    Method (ASMI, 1, NotSerialized)
    {
        Return (Arg0)
    }

    Scope (\_SB)
    {
        Method (ASMI, 1, NotSerialized)
        {
            Return (\ASMI (Arg0))
        }
    }
}
