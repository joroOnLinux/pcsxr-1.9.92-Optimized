	int quotient;

#ifdef GTE_LOG
	GTE_LOG("GTE RTPT\n");
#endif
	gteFLAG = 0;

	gteSZ0 = gteSZ3;

#ifdef __ARM_NEON
	int16x4_t clearLastOct = vreinterpret_s16_s64(vcreate_s64(0x0000ffffffffffff));
	int16x4_t CP2C_1,CP2C_2,CP2C_3,CP2D;
 
	int32x4_t prodVec1,prodVec2,prodVec3;
 
// uint32x4_t CP2Cr;

// CP2Cr = vld1q_u32(&psxRegs.CP2C.r[5]);
// CP2Cr = vshlq_n_u32(CP2Cr,12);
 
	CP2C_1 = vld1_s16(&psxRegs.CP2C.p[0]);
	CP2C_2 = vld1_s16(&psxRegs.CP2C.p[1].sw.h);
	CP2C_3 = vld1_s16(&psxRegs.CP2C.p[3].sw.l);
	CP2D = vld1_s16(&psxRegs.CP2D.p[0]);

	CP2C_1 = vand_s16(clearLastOct,CP2C_1);
	CP2C_2 = vand_s16(clearLastOct,CP2C_2);
	CP2C_3 = vand_s16(clearLastOct,CP2C_3);
	CP2D = vand_s16(clearLastOct,CP2D);
 
	prodVec1 = vmull_s16(CP2C_1,CP2D);
	prodVec2 = vmull_s16(CP2C_2,CP2D);
	prodVec3 = vmull_s16(CP2C_3,CP2D);

	psxRegs.CP2D.r[25] = A1((((s64)gteTRX << 12) + vaddvq_s32(prodVec1)) >> 12);
	psxRegs.CP2D.r[26] = A2((((s64)gteTRY << 12) + vaddvq_s32(prodVec2)) >> 12);
	psxRegs.CP2D.r[27] = A3((((s64)gteTRZ << 12) + vaddvq_s32(prodVec3)) >> 12);
#else
	gteMAC1 = A1((((s64)gteTRX << 12) + (gteR11 * psxRegs.CP2D.p[0].sw.l) + (gteR12 * psxRegs.CP2D.p[0].sw.h) + (gteR13 * psxRegs.CP2D.p[1].sw.l)) >> 12);
	gteMAC2 = A2((((s64)gteTRY << 12) + (gteR21 * psxRegs.CP2D.p[0].sw.l) + (gteR22 * psxRegs.CP2D.p[0].sw.h) + (gteR23 * psxRegs.CP2D.p[1].sw.l)) >> 12);
	gteMAC3 = A3((((s64)gteTRZ << 12) + (gteR31 * psxRegs.CP2D.p[0].sw.l) + (gteR32 * psxRegs.CP2D.p[0].sw.h) + (gteR33 * psxRegs.CP2D.p[1].sw.l)) >> 12);
#endif

	gteIR1 = limB1(gteMAC1, 0);
	gteIR2 = limB2(gteMAC2, 0);
	gteIR3 = limB3(gteMAC3, 0);
	fSZ(0) = limD(gteMAC3);
	quotient = limE(DIVIDE(gteH, fSZ(0)));
	fSX(0) = limG1(F((s64)gteOFX + ((s64)gteIR1 * quotient)) >> 16);
	fSY(0) = limG2(F((s64)gteOFY + ((s64)gteIR2 * quotient)) >> 16);

#ifdef __ARM_NEON
	CP2D = vld1_s16(&psxRegs.CP2D.p[2]);
	CP2D = vand_s16(clearLastOct,CP2D);

	prodVec1 = vmull_s16(CP2C_1,CP2D);
	prodVec2 = vmull_s16(CP2C_2,CP2D);
	prodVec3 = vmull_s16(CP2C_3,CP2D);

	psxRegs.CP2D.r[25] = A1((((s64)gteTRX << 12) + vaddvq_s32(prodVec1)) >> 12);
	psxRegs.CP2D.r[26] = A2((((s64)gteTRY << 12) + vaddvq_s32(prodVec2)) >> 12);
	psxRegs.CP2D.r[27] = A3((((s64)gteTRZ << 12) + vaddvq_s32(prodVec3)) >> 12);
#else
	gteMAC1 = A1((((s64)gteTRX << 12) + (gteR11 * psxRegs.CP2D.p[2].sw.l) + (gteR12 * psxRegs.CP2D.p[2].sw.h) + (gteR13 * psxRegs.CP2D.p[3].sw.l)) >> 12);
	gteMAC2 = A2((((s64)gteTRY << 12) + (gteR21 * psxRegs.CP2D.p[2].sw.l) + (gteR22 * psxRegs.CP2D.p[2].sw.h) + (gteR23 * psxRegs.CP2D.p[3].sw.l)) >> 12);
	gteMAC3 = A3((((s64)gteTRZ << 12) + (gteR31 * psxRegs.CP2D.p[2].sw.l) + (gteR32 * psxRegs.CP2D.p[2].sw.h) + (gteR33 * psxRegs.CP2D.p[3].sw.l)) >> 12);
#endif

	gteIR1 = limB1(gteMAC1, 0);
	gteIR2 = limB2(gteMAC2, 0);
	gteIR3 = limB3(gteMAC3, 0);
	fSZ(1) = limD(gteMAC3);
	quotient = limE(DIVIDE(gteH, fSZ(1)));
	fSX(1) = limG1(F((s64)gteOFX + ((s64)gteIR1 * quotient)) >> 16);
	fSY(1) = limG2(F((s64)gteOFY + ((s64)gteIR2 * quotient)) >> 16);

#ifdef __ARM_NEON
	CP2D = vld1_s16(&psxRegs.CP2D.p[4]);
	CP2D = vand_s16(clearLastOct,CP2D);

	prodVec1 = vmull_s16(CP2C_1,CP2D);
	prodVec2 = vmull_s16(CP2C_2,CP2D);
	prodVec3 = vmull_s16(CP2C_3,CP2D);

	psxRegs.CP2D.r[25] = A1((((s64)gteTRX << 12) + vaddvq_s32(prodVec1)) >> 12);
	psxRegs.CP2D.r[26] = A2((((s64)gteTRY << 12) + vaddvq_s32(prodVec2)) >> 12);
	psxRegs.CP2D.r[27] = A3((((s64)gteTRZ << 12) + vaddvq_s32(prodVec3)) >> 12);
#else
	gteMAC1 = A1((((s64)gteTRX << 12) + (gteR11 * psxRegs.CP2D.p[4].sw.l) + (gteR12 * psxRegs.CP2D.p[4].sw.h) + (gteR13 * psxRegs.CP2D.p[5].sw.l)) >> 12);
	gteMAC2 = A2((((s64)gteTRY << 12) + (gteR21 * psxRegs.CP2D.p[4].sw.l) + (gteR22 * psxRegs.CP2D.p[4].sw.h) + (gteR23 * psxRegs.CP2D.p[5].sw.l)) >> 12);
	gteMAC3 = A3((((s64)gteTRZ << 12) + (gteR31 * psxRegs.CP2D.p[4].sw.l) + (gteR32 * psxRegs.CP2D.p[4].sw.h) + (gteR33 * psxRegs.CP2D.p[5].sw.l)) >> 12);
#endif

	gteIR1 = limB1(gteMAC1, 0);
	gteIR2 = limB2(gteMAC2, 0);
	gteIR3 = limB3(gteMAC3, 0);
	fSZ(2) = limD(gteMAC3);
	quotient = limE(DIVIDE(gteH, fSZ(2)));
	fSX(2) = limG1(F((s64)gteOFX + ((s64)gteIR1 * quotient)) >> 16);
	fSY(2) = limG2(F((s64)gteOFY + ((s64)gteIR2 * quotient)) >> 16);

