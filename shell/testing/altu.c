#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


main()
{
	char buff[100];
	memset(buff,'\0',100);
	int fp[2];
	pipe(fp);
	pid_t pid1 = fork();
	if(pid1==0)
	{
		close(fp[1]);
		read(fp[0],buff,100);
		printf("data recieved is :%s\n",buff);
	}
	else
	{
		printf("Enter data to send:");
		fflush(stdout);
		scanf("%s",buff);
		close(fp[0]);
		write(fp[1],buff,100);
	}

}
