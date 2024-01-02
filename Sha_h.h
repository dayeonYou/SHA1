#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Define constants 

#define HBLOCK  64   // Hash Block  : 512 bits = 64 bytes * 8 bits 
#define HDATA   20   // Hash result : 160 bits = 20 bytes * 8 bits 

// Definre Type
typedef unsigned char BYTE;
typedef unsigned int  UINT;
typedef unsigned long long UINT64;

// Set IV(Initial Vector) Value 

#define H0 0x67452301
#define H1 0xEFCDAB89
#define H2 0x98BADCFE
#define H3 0x10325476
#define H4 0xC3D2E1F0

// Set Round constans K value
#define K0 0x5A827999
#define K1 0x6ED9EBA1
#define K2 0x8F1BBCDC
#define K3 0xCA62C1D6

// Define macro function
#define BTOW(a,b,c,d) (((a << 24) + (b << 16) + (c << 8) + d))  // creation 4 bytes -> 1 word 
#define CIR_SHIFT(x,n) (((x) << (n) | ((x) >> (32-(n)))))

// 기약 논리함수
#define F1(b,c,d) (((b) &(c)) | ((~b) & (d)))
#define F2(b,c,d) (((b) ^ (c) ^ (d)))
#define F3(b,c,d) (((b) & (c)) | ((b) & (d)) | ((c) &(d)))



void padding(BYTE* in, UINT64 msg_len);
void Wvalue(BYTE* in, UINT* W);
void Hdigest(BYTE* in, UINT* Hregister);
UINT cal_fvalue(UINT B, UINT C, UINT D, int i);
