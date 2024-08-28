# CS_ARCH_AARCH64, 0, None

0x1f,0x22,0x03,0xd5 == esb
0x20,0x53,0x18,0xd5 == msr ERRSELR_EL1, x0
0x20,0x54,0x18,0xd5 == msr ERXCTLR_EL1, x0
0x40,0x54,0x18,0xd5 == msr ERXSTATUS_EL1, x0
0x60,0x54,0x18,0xd5 == msr ERXADDR_EL1, x0
0x00,0x55,0x18,0xd5 == msr ERXMISC0_EL1, x0
0x20,0x55,0x18,0xd5 == msr ERXMISC1_EL1, x0
0x20,0xc1,0x18,0xd5 == msr DISR_EL1, x0
0x20,0xc1,0x1c,0xd5 == msr VDISR_EL2, x0
0x60,0x52,0x1c,0xd5 == msr VSESR_EL2, x0
0x20,0x53,0x38,0xd5 == mrs x0, ERRSELR_EL1
0x20,0x54,0x38,0xd5 == mrs x0, ERXCTLR_EL1
0x40,0x54,0x38,0xd5 == mrs x0, ERXSTATUS_EL1
0x60,0x54,0x38,0xd5 == mrs x0, ERXADDR_EL1
0x00,0x55,0x38,0xd5 == mrs x0, ERXMISC0_EL1
0x20,0x55,0x38,0xd5 == mrs x0, ERXMISC1_EL1
0x20,0xc1,0x38,0xd5 == mrs x0, DISR_EL1
0x20,0xc1,0x3c,0xd5 == mrs x0, VDISR_EL2
0x60,0x52,0x3c,0xd5 == mrs x0, VSESR_EL2
0x00,0x53,0x38,0xd5 == mrs x0, ERRIDR_EL1
0x00,0x54,0x38,0xd5 == mrs x0, ERXFR_EL1