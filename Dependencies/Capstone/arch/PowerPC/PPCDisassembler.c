/* Capstone Disassembly Engine, http://www.capstone-engine.org */
/* By Nguyen Anh Quynh <aquynh@gmail.com>, 2013-2022, */
/*    Rot127 <unisono@quyllur.org> 2022-2023 */
/* Automatically translated source file from LLVM. */

/* LLVM-commit: <commit> */
/* LLVM-tag: <tag> */

/* Only small edits allowed. */
/* For multiple similar edits, please create a Patch for the translator. */

/* Capstone's C++ file translator: */
/* https://github.com/capstone-engine/capstone/tree/next/suite/auto-sync */

//===------ PPCDisassembler.cpp - Disassembler for PowerPC ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <capstone/platform.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../LEB128.h"
#include "../../MCDisassembler.h"
#include "../../MCFixedLenDisassembler.h"
#include "../../MCInst.h"
#include "../../MCInstPrinter.h"
#include "../../MCInstrDesc.h"
#include "../../MCRegisterInfo.h"
#include "../../SStream.h"
#include "../../utils.h"
#include "PPCLinkage.h"
#include "PPCMapping.h"
#include "PPCMCTargetDesc.h"
#include "PPCPredicates.h"

#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a##_##b

DEFINE_PPC_REGCLASSES

#define DEBUG_TYPE "ppc-disassembler"

DecodeStatus getInstruction(csh ud, const uint8_t *Bytes, size_t BytesLen,
			    MCInst *MI, uint16_t *Size, uint64_t Address,
			    void *Info);
// end anonymous namespace

static DecodeStatus decodeCondBrTarget(MCInst *Inst, unsigned Imm,
				       uint64_t Address, const void *Decoder)
{
	MCOperand_CreateImm0(Inst, (SignExtend32((Imm), 14)));
	return MCDisassembler_Success;
}

static DecodeStatus decodeDirectBrTarget(MCInst *Inst, unsigned Imm,
					 uint64_t Address, const void *Decoder)
{
	int32_t Offset = SignExtend32((Imm), 24);
	MCOperand_CreateImm0(Inst, (Offset));
	return MCDisassembler_Success;
}

// FIXME: These can be generated by TableGen from the existing register
// encoding values!

static DecodeStatus decodeRegisterClass(MCInst *Inst, uint64_t RegNo,
					const MCPhysReg *Regs)
{
	MCOperand_CreateReg0(Inst, (Regs[RegNo]));
	return MCDisassembler_Success;
}

static DecodeStatus DecodeCRRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					    uint64_t Address,
					    const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, CRRegs);
}

static DecodeStatus DecodeCRBITRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					       uint64_t Address,
					       const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, CRBITRegs);
}

static DecodeStatus DecodeF4RCRegisterClass(MCInst *Inst, uint64_t RegNo,
					    uint64_t Address,
					    const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, FRegs);
}

static DecodeStatus DecodeF8RCRegisterClass(MCInst *Inst, uint64_t RegNo,
					    uint64_t Address,
					    const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, FRegs);
}

static DecodeStatus DecodeVFRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					    uint64_t Address,
					    const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, VFRegs);
}

static DecodeStatus DecodeVRRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					    uint64_t Address,
					    const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, VRegs);
}

static DecodeStatus DecodeVSRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					    uint64_t Address,
					    const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, VSRegs);
}

static DecodeStatus DecodeVSFRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					     uint64_t Address,
					     const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, VSFRegs);
}

static DecodeStatus DecodeVSSRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					     uint64_t Address,
					     const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, VSSRegs);
}

static DecodeStatus DecodeGPRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					    uint64_t Address,
					    const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, RRegs);
}

static DecodeStatus DecodeGPRC_NOR0RegisterClass(MCInst *Inst, uint64_t RegNo,
						 uint64_t Address,
						 const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, RRegsNoR0);
}

static DecodeStatus DecodeG8RCRegisterClass(MCInst *Inst, uint64_t RegNo,
					    uint64_t Address,
					    const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, XRegs);
}

static DecodeStatus DecodeG8pRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					     uint64_t Address,
					     const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, XRegs);
}

static DecodeStatus DecodeG8RC_NOX0RegisterClass(MCInst *Inst, uint64_t RegNo,
						 uint64_t Address,
						 const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, XRegsNoX0);
}

#define DecodePointerLikeRegClass0 DecodeGPRCRegisterClass
#define DecodePointerLikeRegClass1 DecodeGPRC_NOR0RegisterClass

static DecodeStatus DecodeSPERCRegisterClass(MCInst *Inst, uint64_t RegNo,
					     uint64_t Address,
					     const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, SPERegs);
}

static DecodeStatus DecodeACCRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					     uint64_t Address,
					     const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, ACCRegs);
}

static DecodeStatus DecodeWACCRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					      uint64_t Address,
					      const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, WACCRegs);
}

static DecodeStatus DecodeWACC_HIRCRegisterClass(MCInst *Inst, uint64_t RegNo,
						 uint64_t Address,
						 const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, WACC_HIRegs);
}

// TODO: Make this function static when the register class is used by a new
//       instruction.
DecodeStatus DecodeDMRROWRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					 uint64_t Address, const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, DMRROWRegs);
}

static DecodeStatus DecodeDMRROWpRCRegisterClass(MCInst *Inst, uint64_t RegNo,
						 uint64_t Address,
						 const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, DMRROWpRegs);
}

static DecodeStatus DecodeDMRRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					     uint64_t Address,
					     const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, DMRRegs);
}

// TODO: Make this function static when the register class is used by a new
//       instruction.
DecodeStatus DecodeDMRpRCRegisterClass(MCInst *Inst, uint64_t RegNo,
				       uint64_t Address, const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, DMRpRegs);
}

static DecodeStatus DecodeVSRpRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					      uint64_t Address,
					      const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, VSRpRegs);
}

#define DecodeQSRCRegisterClass DecodeQFRCRegisterClass
#define DecodeQBRCRegisterClass DecodeQFRCRegisterClass

static DecodeStatus DecodeQFRCRegisterClass(MCInst *Inst, uint64_t RegNo,
					    uint64_t Address,
					    const void *Decoder)
{
	return decodeRegisterClass(Inst, RegNo, QFRegs);
}

#define DEFINE_decodeUImmOperand(N) \
	static DecodeStatus CONCAT(decodeUImmOperand, \
				   N)(MCInst * Inst, uint64_t Imm, \
				      int64_t Address, const void *Decoder) \
	{ \
		MCOperand_CreateImm0(Inst, (Imm)); \
		return MCDisassembler_Success; \
	}
DEFINE_decodeUImmOperand(5) DEFINE_decodeUImmOperand(16)
	DEFINE_decodeUImmOperand(6) DEFINE_decodeUImmOperand(10)
		DEFINE_decodeUImmOperand(8) DEFINE_decodeUImmOperand(7)
			DEFINE_decodeUImmOperand(12)

#define DEFINE_decodeSImmOperand(N) \
	static DecodeStatus CONCAT(decodeSImmOperand, \
				   N)(MCInst * Inst, uint64_t Imm, \
				      int64_t Address, const void *Decoder) \
	{ \
		MCOperand_CreateImm0(Inst, (SignExtend64(Imm, N))); \
		return MCDisassembler_Success; \
	}
				DEFINE_decodeSImmOperand(16)
					DEFINE_decodeSImmOperand(5)
						DEFINE_decodeSImmOperand(34)

							static DecodeStatus
	decodeImmZeroOperand(MCInst *Inst, uint64_t Imm, int64_t Address,
			     const void *Decoder)
{
	if (Imm != 0)
		return MCDisassembler_Fail;
	MCOperand_CreateImm0(Inst, (Imm));
	return MCDisassembler_Success;
}

static DecodeStatus decodeVSRpEvenOperands(MCInst *Inst, uint64_t RegNo,
					   uint64_t Address,
					   const void *Decoder)
{
	if (RegNo & 1)
		return MCDisassembler_Fail;
	MCOperand_CreateReg0(Inst, (VSRpRegs[RegNo >> 1]));
	return MCDisassembler_Success;
}

static DecodeStatus decodeMemRIOperands(MCInst *Inst, uint64_t Imm,
					int64_t Address, const void *Decoder)
{
	// Decode the memri field (imm, reg), which has the low 16-bits as the
	// displacement and the next 5 bits as the register #.

	uint64_t Base = Imm >> 16;
	uint64_t Disp = Imm & 0xFFFF;

	switch (MCInst_getOpcode(Inst)) {
	default:
		break;
	case PPC_LBZU:
	case PPC_LHAU:
	case PPC_LHZU:
	case PPC_LWZU:
	case PPC_LFSU:
	case PPC_LFDU:
		// Add the tied output operand.
		MCOperand_CreateReg0(Inst, (RRegsNoR0[Base]));
		break;
	case PPC_STBU:
	case PPC_STHU:
	case PPC_STWU:
	case PPC_STFSU:
	case PPC_STFDU:
		MCInst_insert0(Inst, 0,
			       MCOperand_CreateReg1(Inst, RRegsNoR0[Base]));
		break;
	}

	MCOperand_CreateImm0(Inst, (SignExtend64(Disp, 16)));
	MCOperand_CreateReg0(Inst, (RRegsNoR0[Base]));
	return MCDisassembler_Success;
}

static DecodeStatus decodeMemRIXOperands(MCInst *Inst, uint64_t Imm,
					 int64_t Address, const void *Decoder)
{
	// Decode the memrix field (imm, reg), which has the low 14-bits as the
	// displacement and the next 5 bits as the register #.

	uint64_t Base = Imm >> 14;
	uint64_t Disp = Imm & 0x3FFF;

	if (MCInst_getOpcode(Inst) == PPC_LDU)
		// Add the tied output operand.
		MCOperand_CreateReg0(Inst, (RRegsNoR0[Base]));
	else if (MCInst_getOpcode(Inst) == PPC_STDU)
		MCInst_insert0(Inst, 0,
			       MCOperand_CreateReg1(Inst, RRegsNoR0[Base]));

	MCOperand_CreateImm0(Inst, (SignExtend64(Disp << 2, 16)));
	MCOperand_CreateReg0(Inst, (RRegsNoR0[Base]));
	return MCDisassembler_Success;
}

static DecodeStatus decodeMemRIHashOperands(MCInst *Inst, uint64_t Imm,
					    int64_t Address,
					    const void *Decoder)
{
	// Decode the memrix field for a hash store or hash check operation.
	// The field is composed of a register and an immediate value that is 6 bits
	// and covers the range -8 to -512. The immediate is always negative and 2s
	// complement which is why we sign extend a 7 bit value.
	const uint64_t Base = Imm >> 6;
	const int64_t Disp = SignExtend64((Imm & 0x3F) + 64, 7) * 8;

	MCOperand_CreateImm0(Inst, (Disp));
	MCOperand_CreateReg0(Inst, (RRegs[Base]));
	return MCDisassembler_Success;
}

static DecodeStatus decodeMemRIX16Operands(MCInst *Inst, uint64_t Imm,
					   int64_t Address, const void *Decoder)
{
	// Decode the memrix16 field (imm, reg), which has the low 12-bits as the
	// displacement with 16-byte aligned, and the next 5 bits as the register #.

	uint64_t Base = Imm >> 12;
	uint64_t Disp = Imm & 0xFFF;

	MCOperand_CreateImm0(Inst, (SignExtend64(Disp << 4, 16)));
	MCOperand_CreateReg0(Inst, (RRegsNoR0[Base]));
	return MCDisassembler_Success;
}

static DecodeStatus decodeMemRI34PCRelOperands(MCInst *Inst, uint64_t Imm,
					       int64_t Address,
					       const void *Decoder)
{
	// Decode the memri34_pcrel field (imm, reg), which has the low 34-bits as
	// the displacement, and the next 5 bits as an immediate 0.
	uint64_t Base = Imm >> 34;
	uint64_t Disp = Imm & 0x3FFFFFFFFUL;

	MCOperand_CreateImm0(Inst, (SignExtend64(Disp, 34)));
	return decodeImmZeroOperand(Inst, Base, Address, Decoder);
}

static DecodeStatus decodeMemRI34Operands(MCInst *Inst, uint64_t Imm,
					  int64_t Address, const void *Decoder)
{
	// Decode the memri34 field (imm, reg), which has the low 34-bits as the
	// displacement, and the next 5 bits as the register #.
	uint64_t Base = Imm >> 34;
	uint64_t Disp = Imm & 0x3FFFFFFFFUL;

	MCOperand_CreateImm0(Inst, (SignExtend64(Disp, 34)));
	MCOperand_CreateReg0(Inst, (RRegsNoR0[Base]));
	return MCDisassembler_Success;
}

static DecodeStatus decodeSPE8Operands(MCInst *Inst, uint64_t Imm,
				       int64_t Address, const void *Decoder)
{
	// Decode the spe8disp field (imm, reg), which has the low 5-bits as the
	// displacement with 8-byte aligned, and the next 5 bits as the register #.

	uint64_t Base = Imm >> 5;
	uint64_t Disp = Imm & 0x1F;

	MCOperand_CreateImm0(Inst, (Disp << 3));
	MCOperand_CreateReg0(Inst, (RRegsNoR0[Base]));
	return MCDisassembler_Success;
}

static DecodeStatus decodeSPE4Operands(MCInst *Inst, uint64_t Imm,
				       int64_t Address, const void *Decoder)
{
	// Decode the spe4disp field (imm, reg), which has the low 5-bits as the
	// displacement with 4-byte aligned, and the next 5 bits as the register #.

	uint64_t Base = Imm >> 5;
	uint64_t Disp = Imm & 0x1F;

	MCOperand_CreateImm0(Inst, (Disp << 2));
	MCOperand_CreateReg0(Inst, (RRegsNoR0[Base]));
	return MCDisassembler_Success;
}

static DecodeStatus decodeSPE2Operands(MCInst *Inst, uint64_t Imm,
				       int64_t Address, const void *Decoder)
{
	// Decode the spe2disp field (imm, reg), which has the low 5-bits as the
	// displacement with 2-byte aligned, and the next 5 bits as the register #.

	uint64_t Base = Imm >> 5;
	uint64_t Disp = Imm & 0x1F;

	MCOperand_CreateImm0(Inst, (Disp << 1));
	MCOperand_CreateReg0(Inst, (RRegsNoR0[Base]));
	return MCDisassembler_Success;
}

static DecodeStatus decodeCRBitMOperand(MCInst *Inst, uint64_t Imm,
					int64_t Address, const void *Decoder)
{
	// The cr bit encoding is 0x80 >> cr_reg_num.

	unsigned Zeros = CountTrailingZeros_32(Imm);
	if (Zeros >= 8)
		return MCDisassembler_Fail;

	MCOperand_CreateReg0(Inst, (CRRegs[7 - Zeros]));
	return MCDisassembler_Success;
}

#include "PPCGenDisassemblerTables.inc"

DecodeStatus getInstruction(csh ud, const uint8_t *Bytes, size_t BytesLen,
			    MCInst *MI, uint16_t *Size, uint64_t Address,
			    void *Info)
{
	// If this is an 8-byte prefixed instruction, handle it here.
	// Note: prefixed instructions aren't technically 8-byte entities - the
	// prefix
	//       appears in memory at an address 4 bytes prior to that of the base
	//       instruction regardless of endianness. So we read the two pieces and
	//       rebuild the 8-byte instruction.
	// TODO: In this function we call decodeInstruction several times with
	//       different decoder tables. It may be possible to only call once by
	//       looking at the top 6 bits of the instruction.
	if (PPC_getFeatureBits(MI->csh->mode, PPC_FeaturePrefixInstrs) &&
	    BytesLen >= 8) {
		uint32_t Prefix = readBytes32(MI, Bytes);
		uint32_t BaseInst = readBytes32(MI, Bytes + 4);
		uint64_t Inst = BaseInst | (uint64_t)Prefix << 32;
		DecodeStatus result =
			decodeInstruction_4(DecoderTable64, MI, Inst, Address);
		if (result != MCDisassembler_Fail) {
			*Size = 8;
			return result;
		}
	}

	// Get the four bytes of the instruction.
	*Size = 4;
	if (BytesLen < 4) {
		*Size = 0;
		return MCDisassembler_Fail;
	}

	// Read the instruction in the proper endianness.
	uint64_t Inst = readBytes32(MI, Bytes);

	if (PPC_getFeatureBits(MI->csh->mode, PPC_FeatureQPX)) {
		DecodeStatus result = decodeInstruction_4(DecoderTableQPX32, MI,
							  Inst, Address);
		if (result != MCDisassembler_Fail)
			return result;
	} else if (PPC_getFeatureBits(MI->csh->mode, PPC_FeatureSPE)) {
		DecodeStatus result = decodeInstruction_4(DecoderTableSPE32, MI,
							  Inst, Address);
		if (result != MCDisassembler_Fail)
			return result;
	} else if (PPC_getFeatureBits(MI->csh->mode, PPC_FeaturePS)) {
		DecodeStatus result = decodeInstruction_4(DecoderTablePS32, MI,
							  Inst, Address);
		if (result != MCDisassembler_Fail)
			return result;
	}

	return decodeInstruction_4(DecoderTable32, MI, Inst, Address);
}

DecodeStatus PPC_LLVM_getInstruction(csh handle, const uint8_t *Bytes,
				     size_t BytesLen, MCInst *MI,
				     uint16_t *Size, uint64_t Address,
				     void *Info)
{
	return getInstruction(handle, Bytes, BytesLen, MI, Size, Address, Info);
}