#include	<stdio.h>
#include	<unistd.h>
#include	<sys/types.h>
#include	<string.h>

#define BUFFER_SIZE 32

int main(void) {
    char write_msg[BUFFER_SIZE] = "Hello Pipe Message";
    char read_msg[BUFFER_SIZE];
    pid_t pid;
    int fd[2]; // 0: read end, 1: write end

    if(pipe(fd) == -1){
        fprintf(stderr,"Pipe failed");
        return 1;
    }

    //자식 프로세스 생성
    pid = fork();

    if(pid < 0) {
        fprintf(stderr, "Fork failed");
        return 1;
    }else if(pid > 0 ){
        close(fd[0]);
        write(fd[1], write_msg, strlen(write_msg)+1);
        close(fd[1]);
    } else{
        close(fd[1]);
        read(fd[0], read_msg, BUFFER_SIZE);
        printf("child read message = %s\n",read_msg);
        close(fd[0]);
    }

    return 0;

}