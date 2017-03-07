#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<signal.h>

struct msg{

int type;
char data[1024];

};
void getfile(int sockfd,char out[])
{
	char out1[30];
	strcpy(out1,"download/");
	strcat(out1,out);
	FILE *fp = fopen(out1,"w");
	if(fp==NULL)
	{
		printf("File creation Failed\n");
		return;
	}
	struct msg message;
	int count=0;
	do
	{
		memset(&message,'\0',sizeof(message));
		count=read(sockfd,(char*)&message,sizeof(message));
		printf("%s",message.data);
		if(message.type==4)
		{
			printf("Error :%s",message.data);
			return;
		}
		int len = fwrite(message.data,1,count,fp);
		memset(&message,'\0',sizeof(message));
printf(message.data);

	}while(count>=sizeof(message));
	fclose(fp);
}
void printdata(int sockfd)
{
	struct msg message;
	while(1)
	{
		memset(&message,'\0',sizeof(message));
		read(sockfd,(char *)&message,sizeof(message));
		if(strcmp(message.data,"done"))
			printf("%s",message.data);	
		else
			break;
	}
}
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
	printf("\n1. get list of files\n2. Download file\n3. Disconnect\n");
	//printf("1. get list of files\n2. Download file\n3. Disconnect\n");
	while(1)
	{
		
		struct msg message;
		scanf("%d",&message.type);
		char *l = NULL;
		size_t len = sizeof(message.data);
		switch(message.type)
		{
		case 1: while(1)
			{
				printf("avd@kali#");
			//gets(message.data);
				fflush(stdin);
				memset(message.data,'\0',sizeof(message.data));
				char c; 
				//c = getchar();
				//printf("char is :%c",c);
				//scanf("%s",message.data);
				//char *L = NULL;
				int a = getline(&l,&len,stdin); 
				strcpy(message.data,l);			
				printf("%s",message.data);
					if(strncmp(message.data,"exit",4)==0)
						break;
				write(sockfd,(char*)&message,sizeof(message));
				printdata(sockfd);
				
			
			}
			break;
		case 2: printf("\nfile to download:");
			scanf("%s",message.data);
			char out[30];
			printf("output file:");
			scanf("%s",out);
			write(sockfd,(char *)&message,sizeof(message));
			getfile(sockfd,out);
			break;
		case 3: write(sockfd,(char *)&message,sizeof(message));
			return;
		default: printf("invalid input\n");
			break;
		}	
	}
return 0;
}
