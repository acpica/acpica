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
	"mt_mutex.aml", // Output filename
	"DSDT",     // Signature
	0x02,       // DSDT Revision
	"Intel",    // OEMID
	"Many",     // TABLE ID
	0x00000001  // OEM Revision
	) {

	// All declarations
	Include("../../../../runtime/cntl/MT_DECL.asl")
	Include("../../../../runtime/common/TCI/tcicmd.asl")
	Include("../../../../runtime/common/mx_objects.asl")
	Include("../../../../runtime/collections/mt/mutex/common.asl")
	Include("../../../../runtime/collections/mt/mutex/service.asl")
	Include("../../../../runtime/collections/mt/mutex/tests.asl")
	Include("../../../../runtime/collections/mt/mutex/mutex.asl")
	Include("../../../../runtime/collections/mt/mutex/mxs.asl")
	Include("../../../../runtime/collections/mt/mutex/example0.asl")
	Include("../../../../runtime/collections/mt/mutex/slave_thr.asl")

	/*
	 * Arguments passed to MAIN method are:
	 *
	 *   arg0 - number of threads.
	 *   arg1 - ID of current thread.
	 *   arg2 - Index of current thread inside all participating threads.
	 *          The thread of Index 0 is considered as Control Thread.
	 */
	Method(MAIN, 3) {

		if (LEqual(arg1, "AML Debugger"))
		{
			Store("Either the Threads command is old,", Debug)
			Store("or even some another command was initiated.", Debug)
			return (0)
		}

		/* Non-zero Local0 means the current thread is a Control Thread */

		Store(1, Local0)
		if (arg2) {
			/* Wait for Control thread saying 'go further' */
			m116(arg2)
			Store(0, Local0)
		} else {

			/* Control thread */

			// Initialization
			STRT(0)
		}

		// Run verification methods

		Include("../../../../runtime/collections/mt/mutex/RUN.asl")

		Store(0, Local7)
		if (Local0) {
			// Final actions
			Store(FNSH(), Local7)
		}

		return (Local7)
	}
}
