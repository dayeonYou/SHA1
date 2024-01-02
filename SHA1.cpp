#include "Sha_h.h"

int main()
{
    // 파일명 입력 받기
    char file_name[64] = { 0, };
    printf("\n Print the PATH of input file : ");

    if (scanf_s("%s", file_name, sizeof(file_name)) == -1) {
        printf("\n Error occurring during reading file_name \n");
        exit(0);
    }

    // 파일 열기
    FILE* fp;
    fopen_s(&fp, file_name, "rb"); // "rb" 모드로 열어야 이진 파일도 읽을 수 있습니다.

    if (fp == NULL) {
        printf("\n File Open Fail");
        exit(1);
    }

    // 변수 및 배열 선언
    size_t size = 0;
    BYTE msg[HBLOCK * 2] = { 0, };
    UINT64 f_size = 0;
    UINT Hregister[5] = { H0, H1, H2, H3, H4 }; // 초기 H register 값 설정

    // 파일 읽기
    while ((size = fread(msg, sizeof(BYTE), HBLOCK, fp))) {
        f_size += size;

        // 마지막 블록에 패딩 추가
        if (size < HBLOCK) {
            padding(msg, f_size);
        }

        // 해시 계산
        Hdigest(msg, Hregister);
    }

    // 파일 닫기
    fclose(fp);

    // 해시 결과 출력
    printf("\n\n SHA-1 Hash Value: ");
    for (int i = 0; i < 5; i++) {
        printf("%08x", Hregister[i]);
    }

    printf("\n");

    return 0;
}
