# CS_ARCH_AARCH64, 0, None

0x20,0x0c,0x22,0x5e == sqadd b0, b1, b2
0x6a,0x0d,0x6c,0x5e == sqadd h10, h11, h12
0xb4,0x0e,0xa2,0x5e == sqadd s20, s21, s2
0xf1,0x0f,0xe8,0x5e == sqadd d17, d31, d8
0x20,0x0c,0x22,0x7e == uqadd b0, b1, b2
0x6a,0x0d,0x6c,0x7e == uqadd h10, h11, h12
0xb4,0x0e,0xa2,0x7e == uqadd s20, s21, s2
0xf1,0x0f,0xe8,0x7e == uqadd d17, d31, d8
0x20,0x2c,0x22,0x5e == sqsub b0, b1, b2
0x6a,0x2d,0x6c,0x5e == sqsub h10, h11, h12
0xb4,0x2e,0xa2,0x5e == sqsub s20, s21, s2
0xf1,0x2f,0xe8,0x5e == sqsub d17, d31, d8
0x20,0x2c,0x22,0x7e == uqsub b0, b1, b2
0x6a,0x2d,0x6c,0x7e == uqsub h10, h11, h12
0xb4,0x2e,0xa2,0x7e == uqsub s20, s21, s2
0xf1,0x2f,0xe8,0x7e == uqsub d17, d31, d8
0xd3,0x39,0x20,0x5e == suqadd b19, b14
0xf4,0x39,0x60,0x5e == suqadd h20, h15
0x95,0x39,0xa0,0x5e == suqadd s21, s12
0xd2,0x3a,0xe0,0x5e == suqadd d18, d22
0xd3,0x39,0x20,0x7e == usqadd b19, b14
0xf4,0x39,0x60,0x7e == usqadd h20, h15
0x95,0x39,0xa0,0x7e == usqadd s21, s12
0xd2,0x3a,0xe0,0x7e == usqadd d18, d22