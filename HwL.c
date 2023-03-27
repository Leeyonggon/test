#include <stdio.h>
#include <stdlib.h>


#define B_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *src_file, *dst_file;  
    char buffer[B_SIZE];   
    size_t b_read, b_written; 

    // 명령행 인수가 3개가 아니면 사용법을 출력 후 프로그램을 종료.
    if (argc != 3) {
        printf("파일: %s <소스F> <도착F>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

   
    src_file = fopen(argv[1], "rb");
    if (src_file == NULL) { // 만약 파일 열기에 실패하면 에러 메시지를 출력하고 프로그램을 종료합니다.
        printf("Error: Cannot open file '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    
    dst_file = fopen(argv[2], "wb");
    if (dst_file == NULL) { // 만약 파일 열기에 실패하면 에러 메시지를 출력하고 소스 파일을 닫고 프로그램을 종료합니다.
        printf("Error: Cannot open file '%s'\n", argv[2]);
        fclose(src_file);
        exit(EXIT_FAILURE);
    }


    while ((b_read = fread(buffer, 1, B_SIZE, src_file)) > 0) {
        b_written = fwrite(buffer, 1, b_read, dst_file); 
        if (b_written != b_read) { // 만약 쓰기 도중 에러가 발생하면 에러 메시지를 출력하고 소스 파일과 대상 파일을 닫고 프로그램을 종료.
            printf("Error: Failed to write to file '%s'\n", argv[2]);
            fclose(src_file);
            fclose(dst_file);
            exit(EXIT_FAILURE);
        }
    }

    if (ferror(src_file)) { // 만약 파일에서 읽기 도중 에러가 발생하면 에러 메시지를 출력하고 소스 파일과 대상 파일을 닫고 프로그램을 종료.
        printf("Error: Failed to read file '%s'\n", argv[1]);
        fclose(src_file);
        fclose(dst_file);
        exit(EXIT_FAILURE);
    }

    fclose(src_file); // 소스 파일과 대상 파일을 닫습니다.
    fclose(dst_file);

    printf("success!.\n"); // 파일 복사가 완료되었음을 출력합니다.

    return 0; 