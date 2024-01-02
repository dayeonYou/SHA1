#include "Sha_h.h"
// 전역변수 선언 
static BYTE digest[HDATA] = { 0, };  // 해쉬값 초기화
static int isAddpad = 0;

UINT cal_fvalue(UINT B, UINT C, UINT D, int i)
{
	UINT fvalue = 0;

	if (i < 20)                fvalue = F1(B, C, D) + K0;
	if ((i >= 20) && (i < 40)) fvalue = F2(B, C, D) + K1;
	if ((i >= 40) && (i < 60)) fvalue = F3(B, C, D) + K2;
	if (i >= 60)               fvalue = F2(B, C, D) + K3;

	return(fvalue);
}


void Hdigest(BYTE* in, UINT* Hregister)
{
	int i;
	UINT W[80] = { 0, };
	UINT Hregister1[5] = { 0 };
	UINT A, B, C, D, E;
	UINT fvalue = 0;

	Wvalue(in, W);
	// 입력 H register 보존한다. 
	for (i = 0; i < 5; i++)
		Hregister1[i] = Hregister[i];

	for (i = 0; i < 80; i++) {
		A = Hregister[0];
		B = Hregister[1];
		C = Hregister[2];
		D = Hregister[3];
		E = Hregister[4];

		fvalue = cal_fvalue(B, C, D, i);

		Hregister[0] = E + fvalue + CIR_SHIFT(A, 5) + W[i];
		Hregister[1] = A;
		Hregister[2] = CIR_SHIFT(B, 30);
		Hregister[3] = C;
		Hregister[4] = D;
	}

	Hregister[0] += Hregister1[0];
	Hregister[1] += Hregister1[1];
	Hregister[2] += Hregister1[2];
	Hregister[3] += Hregister1[3];
	Hregister[4] += Hregister1[4];
}
/*
int main()
{
	int i;
	BYTE in[64] = { 0, };
	UINT Hregister[5] = { 0, };

	Hregister[0] = H0;
	Hregister[1] = H1;
	Hregister[2] = H2;
	Hregister[3] = H3;
	Hregister[4] = H4;

	for (i = 0; i < 64; i++)
		in[i] = 'a' + i;

	Hdigest(in, Hregister);

	printf("\n\n W Hregisterlue is \n");

	for (i = 0; i < 5; i++) {
		printf("\n Hregister = %x ", Hregister[i]);
	}

	return 0;
}*/