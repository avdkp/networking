#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<signal.h>


int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));


	sockfd = socket(AF_INET,SOCK_STREAM,0);	
	if(sockfd == -1)
	{ 
		printf("Error creating socket...");
		return 1; 
	}

	if( connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
		printf("\nError connecting to server...."); 
		return 1; 
	}
char msg[100];
char inbuffer[100];
	int pid = fork();
	if(pid==0)
	{
		while(1)
		{
			
			scanf("%[^\n]%*c",msg);
			fflush(stdin);
			write(sockfd,(char *)msg,strlen(msg));
			memset(msg,0,sizeof(msg));
			sleep(1);
		}
	}
	else
	{
	
		while(1)
		{
			//read(sockfd,(char *)str,sizeof(str));
			int quant = read(sockfd, inbuffer, sizeof(inbuffer));
			printf ("Received: %*.*s\n", quant, quant, inbuffer);
			fflush(stdout);
			memset(inbuffer,0,sizeof(inbuffer));
			sleep(1);
		}
	}
return 0;
}
