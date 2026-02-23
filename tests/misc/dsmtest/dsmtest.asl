DefinitionBlock ("", "DSDT", 2, "TEST", "DSMTEST", 0x00000001)
{
    Scope (\_SB)
    {
        Device (DUT0)
        {
            Name (_HID, "ACPI0001")

            Name (PKG0, Package () { One })
            Name (STR0, "X")
            Name (BUF0, Buffer () { 0x5A })
            Name (INT0, 0x1234)

            Method (_DSM, 4, NotSerialized)
            {
                Return (ObjectType (Arg3))
            }

            Method (TDSM, 0, NotSerialized)
            {
                Local0 = Zero

                If (LEqual (_DSM (ToUUID ("00112233-4455-6677-8899-AABBCCDDEEFF"),
                            One, Zero, PKG0), ObjectType (PKG0)))
                {
                    Or (Local0, 0x1, Local0)
                }

                If (LEqual (_DSM (ToUUID ("00112233-4455-6677-8899-AABBCCDDEEFF"),
                            One, One, STR0), ObjectType (STR0)))
                {
                    Or (Local0, 0x2, Local0)
                }

                If (LEqual (_DSM (ToUUID ("00112233-4455-6677-8899-AABBCCDDEEFF"),
                            One, 0x02, BUF0), ObjectType (BUF0)))
                {
                    Or (Local0, 0x4, Local0)
                }

                If (LEqual (_DSM (ToUUID ("00112233-4455-6677-8899-AABBCCDDEEFF"),
                            One, 0x03, INT0), ObjectType (INT0)))
                {
                    Or (Local0, 0x8, Local0)
                }

                Return (Local0)
            }
        }
    }
}
