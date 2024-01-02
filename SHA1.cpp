#include "Sha_h.h"

int main()
{
    // ���ϸ� �Է� �ޱ�
    char file_name[64] = { 0, };
    printf("\n Print the PATH of input file : ");

    if (scanf_s("%s", file_name, sizeof(file_name)) == -1) {
        printf("\n Error occurring during reading file_name \n");
        exit(0);
    }

    // ���� ����
    FILE* fp;
    fopen_s(&fp, file_name, "rb"); // "rb" ���� ����� ���� ���ϵ� ���� �� �ֽ��ϴ�.

    if (fp == NULL) {
        printf("\n File Open Fail");
        exit(1);
    }

    // ���� �� �迭 ����
    size_t size = 0;
    BYTE msg[HBLOCK * 2] = { 0, };
    UINT64 f_size = 0;
    UINT Hregister[5] = { H0, H1, H2, H3, H4 }; // �ʱ� H register �� ����

    // ���� �б�
    while ((size = fread(msg, sizeof(BYTE), HBLOCK, fp))) {
        f_size += size;

        // ������ ��Ͽ� �е� �߰�
        if (size < HBLOCK) {
            padding(msg, f_size);
        }

        // �ؽ� ���
        Hdigest(msg, Hregister);
    }

    // ���� �ݱ�
    fclose(fp);

    // �ؽ� ��� ���
    printf("\n\n SHA-1 Hash Value: ");
    for (int i = 0; i < 5; i++) {
        printf("%08x", Hregister[i]);
    }

    printf("\n");

    return 0;
}
