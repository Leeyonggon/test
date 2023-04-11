#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void print_char(int ch);

int main(){
    pid_t pid;
    int i,j;

    pid = fork();

    if(pid<0){
        fprintf(stderr,"Fork Failed\n");
        exit(-1);
    }
    else if(pid == 0){
        print_char('-');
        exit();
    }
    else {
        print_char('0');    
        exit(0);
    }


}

void print_char(int ch){
    int i,j;
    for(i=0; i<100, i++){
        putchar(ch);
        fflush(stdout);
        for(j=0; j<100; j++)
                ;
    }

}