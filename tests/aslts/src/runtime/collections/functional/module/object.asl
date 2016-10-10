/*
 * Some or all of this work - Copyright (c) 2006 - 2016, Intel Corp.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * Neither the name of Intel Corporation nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Module level execution under Device/Processor/ThermalZone/PowerResource
 */

/*
 * Verify if Type1Opcode (ex., If) is allowed under Device, PowerResource,
 * Processor, or ThermalZone
 *
 * ASL spec state:
 * 1. DeviceTerm supports ObjectList for ACPI 1.0 ~ ACPI 6.1.
 * 2. PwerResTerm supports ObjectList for ACPI 1.0 ~ ACPI 6.1.
 * 3. ProcessorTerm supports ObjectList for ACPI 1.0 ~ ACPI 6.1.
 * 4. ThermalZoneTerm supports ObjectList for ACPI 1.0 ~ ACPI 6.1.
 *
 * AML spec state:
 * 1. DefDevice supports ObjectList for ACPI 1.0 ~ ACPI 6.0.
 * 2. DefPowerRes supports ObjectList for ACPI 1.0 ~ ACPI 6.0.
 * 3. DefProcessor supports ObjectList for ACPI 1.0 ~ ACPI 6.0.
 * 4. DefThermalZone supports ObjectList for ACPI 1.0 ~ ACPI 6.0.
 *
 * It appears the AML interpreter shouldn't support TermList for these
 * objects as both the ASL grammar and AML grammar doesn't allow it. But
 * the real world apears not.
 */

Name(z181, 181)

/* Tests for Type1Opcode */

Name(ml10, 0)
Name(ml11, 0)
Name(ml12, 0)
Name(ml13, 0)

Scope(\_SB)
{
	Device(dev0)
	{
		if (LEqual(ml10, 0)) {
			Store(2, ml10)
		}
		PowerResource(pr00, 1, 0)
		{
			if (LEqual(ml13, 0)) {
				Store(2, ml13)
			}
		}
	}
}
Scope(\_PR)
{
	Processor(cpu0, 0, 0xFFFFFFFF, 0)
	{
		if (LEqual(ml11, 0)) {
			Store(2, ml11)
		}
	}
}
Scope(\_TZ)
{
	ThermalZone(thz0)
	{
		if (LEqual(ml12, 0)) {
			Store(2, ml12)
		}
	}
}

Method(MLO0,, Serialized)
{
	Name(ts, "MLO0")

	Store("TEST: MLO0, Type1Opcode is executable under objects", Debug)

	if (LNotEqual(ml10, 2)) {
		err(ts, z181, 0, z181, 0, ml10, 2)
	}
	if (LNotEqual(ml11, 2)) {
		err(ts, z181, 1, z181, 1, ml11, 2)
	}
	if (LNotEqual(ml12, 2)) {
		err(ts, z181, 2, z181, 2, ml12, 2)
	}
	if (LNotEqual(ml13, 2)) {
		err(ts, z181, 3, z181, 3, ml13, 2)
	}
}
