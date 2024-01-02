#include "Sha_h.h"
// 전역변수 선언 
static BYTE digest[HDATA] = { 0, };  // 해쉬값 초기화
static int isAddpad = 0;
void padding(BYTE* in, UINT64 msg_len)
{
	int i;
	BYTE* ptr = (BYTE*)&msg_len;
	UINT64 length = 0;

	length = msg_len % HBLOCK;
	// 마지막 메세지의 bit 길이가 8*56 = 448 보다 작은 경우
	if (length < 56) {
		for (i = length; i < HBLOCK; i++) {
			in[i] = 0;
		}
		in[msg_len % HBLOCK] = 0x80;
		msg_len *= 8;                     // msg_len 개의 바이트를 msg_len*8 개의 bit 수로 변환해서 기록한다. 

		for (i = 0; i < 8; i++)
			in[HBLOCK - i - 1] = *(ptr + i);
	}

	else {                                // 마지막 메세지의 bit 길이가 8*56 = 448 이상인 경우 
		length = msg_len % HBLOCK;
		for (i = length; i < 2 * HBLOCK; i++) {
			in[i] = 0;
		}

		in[msg_len % HBLOCK] = 0x80;
		msg_len *= 8;

		// isAddpad = 1;                    추후 처리 !!

		for (i = 0; i < 8; i++)
			in[HBLOCK * 2 - i - 1] = *(ptr + i);
	}
}
/*
int main()
{
	int i;
	size_t size = 0;
	BYTE msg[HBLOCK * 2] = { 0, };
	UINT64 f_size = 0;

	char file_name[64] = { 0, };      // The name of Input File 
	FILE* fp;                         // the pointer for input file 

	printf("\n Print the path of input file : ");

	if (scanf_s("%s", file_name, sizeof(file_name)) == -1) {
		printf("\n Error occurring during reading file_name \n");
		exit(0);
	}

	fopen_s(&fp, file_name, "r");
	if (fp == NULL) {
		printf("\n File Open Fail");
		exit(1);
	}


	while ((size = fread(msg, sizeof(BYTE), HBLOCK, fp))) {

		printf("\n size = %u \n", size);
		for (i = 0; i < HBLOCK; i++)
			printf("%c", msg[i]);

		f_size += size;

		if (size < HBLOCK) {
			padding(msg, f_size);
		}
	}

	printf("\n\n f_size = %llu \n ", f_size);
	for (i = 0; i < 2 * HBLOCK; i++)
		printf("%c", msg[i]);

	fclose(fp);

	return 0;
}*/