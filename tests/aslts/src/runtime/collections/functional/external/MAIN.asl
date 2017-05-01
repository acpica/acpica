/*
 * Some or all of this work - Copyright (c) 2006 - 2017, Intel Corp.
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

DefinitionBlock(
	"external.aml",   // Output filename
	"SSDT",     // Signature
	0x02,       // DSDT Revision
	"Intel",    // OEMID
	"Many",     // TABLE ID
	0x00000001  // OEM Revision
	) {
	// Name(EX00, UnknownObj)

        Name(E000, 0)
	Name(E001, 1)
	Name(E002, "test string")

	Name (E003, Buffer(1){0})
	Name (E004, Package(){})

	OperationRegion (E010, PCI_Config, Zero, 0xFF)
	Field (E010, AnyAcc, NoLock, Preserve)
	{
		E005, 8
	}

	Device(E006){}
	Event(E007)
	Method (E008)
	{
		return (500)
	}
	Mutex(E009, 0)
	PowerResource(E011, 0, 0){}
	Processor(E012, 0, 1, 2){}
	ThermalZone(E013){}
	CreateBitField(E003, 0, E014)
}

DefinitionBlock(
	"external.aml",   // Output filename
	"DSDT",     // Signature
	0x02,       // DSDT Revision
	"Intel",    // OEMID
	"Many",     // TABLE ID
	0x00000001  // OEM Revision
	) {

	// All declarations
	Include("../../../../runtime/cntl/DECL.asl")
	Include("../../../../runtime/collections/functional/external/DECL.asl")

	Method(MAIN) {

		// Initialization
		STRT(0)

		// Run verification methods
		Include("../../../../runtime/collections/functional/external/RUN.asl")

		// Final actions
		Store(FNSH(), Local7)

		return (Local7)
	}
}


