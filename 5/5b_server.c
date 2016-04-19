#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           
#include <unistd.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define MAX 1000

int main(void) {
	char input[1000],output[1000],c;
	int i = 0,num,fd1,fd2;
	mkfifo("firstfifo",0644);
	fd1 = open("firstfifo",O_WRONLY);
	printf("\nSERVER | READY TO SEND...\n");
	printf("\nSERVER | TYPE DATA (` to stop)...\n");
	while((c = getc(stdin)) != '`')
		input[i++] = c;
	input[i] = '\0';
	printf("\nSERVER | INPUT IS : \n%s", input);
	write(fd1,input,strlen(input));
	printf("\nSERVER | SENT!\n");
	fd2 = open("firstfifo",O_RDONLY);
	while((num = read(fd2,output,MAX)) > 0) {
		output[num] = '\0';
		printf("\nRECIEVED :\n%s", output);
		fflush(stdout);
		break;
	}
}