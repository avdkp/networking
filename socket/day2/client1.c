#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<signal.h>
#define MAX 100
void process(char str[]);
int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));


	sockfd = socket(AF_INET,SOCK_STREAM,0);	
	if(sockfd <0 )
	{ 
		printf("Error creating socket...");
		return 1; 
	}

	if( connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
		printf("\nError connecting to server...."); 
		return 1; 
	}
	char msg[MAX];
	scanf("%s",msg);
	fflush(stdin);
	int i=0;
		while(1)
		{
			
			write(sockfd,(char *)msg,sizeof(msg));
			sleep(1);
			memset(msg,'\0',sizeof(msg));
			read(sockfd,(char *)msg,sizeof(msg));
			printf("%s\n",msg);
			//process(msg);
			if(msg[0]=='i')
			{
				printf("Invalid input : %s",msg);
				break;
			}
			if(strlen(msg)<2)
			{
				printf("Result is : %d",atoi(msg));
				break;
			}			
		}


return 0;
}
void process(char str[])
{
	int i;
	for(i=0;i<MAX;++i)
	{
		if(str[i]>=48&&str[i]<57)
			continue;
		else
		{
			str[i]='\0';
			break;
		}
	}

}
