#include "Sha_h.h"

// 전역변수 선언 
static BYTE digest[HDATA] = { 0, };  // 해쉬값 초기화
static int isAddpad = 0;


void Wvalue(BYTE* in, UINT* W)
{
	int i;

	for (i = 0; i < 16; i++)
		W[i] = BTOW(in[i * 4], in[i * 4 + 1], in[i * 4 + 2], in[i * 4 + 3]);

	for (i = 16; i < 80; i++)
		W[i] = CIR_SHIFT((W[i - 16] ^ W[i - 14] ^ W[i - 8] ^ W[i - 3]), 1);

}
/*
int main()
{
	int i;
	BYTE in[64] = { 0, };
	UINT W[80] = { 0, };

	for (i = 0; i < 64; i++)
		in[i] = 'a' + i;

	Wvalue(in, W);

	printf("\n\n W value is \n");
	for (i = 0; i < 80; i++) {
		if (i % 8 == 0) printf("\n");
		printf("%10x", W[i]);
	}

	return 0;
}*/