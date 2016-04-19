#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>           
#include <unistd.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#define MAX 1000

int main(void) {
	char input[MAX],output[MAX],a[100],c;
	int i = 0,n,fd1,fd2,words = 0,lines = 0,chars = 0;
	FILE *fp;
	fd1 = open("firstfifo", O_RDONLY);
	while((n = read(fd1,input,MAX)) > 0) {
		input[n] = '\0';
		printf("\nCLIENT | THE CONTENTS RECIEVED FROM FIFO ARE : \n%s", input);
		fflush(stdout);
		break;
	}
	for(i = 0;i < strlen(input);i++) {
		if(isalnum(input[i]))
			chars++;
		if(isspace(input[i]))
			words++;
		if(input[i] == '\n')
			lines++;
	}
	fp = fopen("stats.txt","w+");
	fprintf(fp, "THE STATISTICS ARE AS FOLLOWS :\n");
	fprintf(fp, "\nNUMBER OF CHARACTERS : %d", chars);
	fprintf(fp, "\nNUMBER OF WORDS : %d", words);
	fprintf(fp, "\nNUMBER OF LINES : %d", lines);
	rewind(fp);
	for(i = 0;fgets(a,sizeof(a),fp) != NULL;i++)
		strcat(output,a);
	fd2 = open("firstfifo", O_WRONLY);
	printf("\nCLIENT : \n%s", output);	
	write(fd2, output, strlen(output));	
	fclose(fp);
}