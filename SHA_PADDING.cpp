#include "Sha_h.h"
// �������� ���� 
static BYTE digest[HDATA] = { 0, };  // �ؽ��� �ʱ�ȭ
static int isAddpad = 0;
void padding(BYTE* in, UINT64 msg_len)
{
	int i;
	BYTE* ptr = (BYTE*)&msg_len;
	UINT64 length = 0;

	length = msg_len % HBLOCK;
	// ������ �޼����� bit ���̰� 8*56 = 448 ���� ���� ���
	if (length < 56) {
		for (i = length; i < HBLOCK; i++) {
			in[i] = 0;
		}
		in[msg_len % HBLOCK] = 0x80;
		msg_len *= 8;                     // msg_len ���� ����Ʈ�� msg_len*8 ���� bit ���� ��ȯ�ؼ� ����Ѵ�. 

		for (i = 0; i < 8; i++)
			in[HBLOCK - i - 1] = *(ptr + i);
	}

	else {                                // ������ �޼����� bit ���̰� 8*56 = 448 �̻��� ��� 
		length = msg_len % HBLOCK;
		for (i = length; i < 2 * HBLOCK; i++) {
			in[i] = 0;
		}

		in[msg_len % HBLOCK] = 0x80;
		msg_len *= 8;

		// isAddpad = 1;                    ���� ó�� !!

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