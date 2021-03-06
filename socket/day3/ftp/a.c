#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<signal.h>

struct msg{

int type;		//1. successful 2.error, 3. last packet 5,list
char data[256];

};

void send_file(int fd,char *data)
{
	struct msg message;
	FILE *fp = fopen(data,"r+");
	if(fp==NULL)
	{
		message.type=2;
		strcpy(message.data,"File not found");
		strcat(message.data,"\0");
		write(fd,(char*)&message,sizeof(struct msg));
		return;
	}	
	else
	{
		while(1){
			int size = fread(message.data,1,256,fp);
			if(size==256){
				message.type=1;
			}
			else
				message.type=3;
			write(fd,(char*)&message,sizeof(struct msg));
			memset(&message,'\0',sizeof(struct msg));
			if(size<256)
				break;
		}
		printf("File sent successfully\n");
	}
	
}
int main(int argc, char **argv){
int sockfd, newsockfd, portno, clilen;
if(argc < 2){  printf("\nenter: %s [portno]",argv[0]); return 1;}
int n=1;
struct sockaddr_in serv_addr, cli_addr;

sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd < 0) { printf("Error creating socket...."); exit(1); }

bzero(&serv_addr,sizeof(struct sockaddr_in));
portno = atoi(argv[1]);
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(portno);
serv_addr.sin_addr.s_addr = INADDR_ANY;
char str[256];
if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
 { printf("\nBinding Error...."); exit(2);}

listen(sockfd,5);

	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd < 0)
	{
		 printf("Connection failed.......\n");
		_exit(1);
	}
		

//	inet_ntop(AF_INET,&(cli_addr.sin_addr.s_addr),str,sizeof(str));
//	printf("\nSuccesfully connected to %s:%d\n",str,ntohs(cli_addr.sin_port));
	
struct msg message;
//printf("message data size: %d",sizeof(message.data));
while(1)
{
	read(newsockfd,(char*) &message,sizeof(struct msg));
	printf("hello\n%d",message.type);
	if(message.type==4)
		return 0;
	
	if(message.type==5)
	{
		printf("message type is %d",message.type);
		message.type=5;
		FILE *fp1 = popen("ls -lh", "r");
		  while (fgets(message.data, 255, fp1) != NULL) 
		  {
			printf("%s",message.data);
		    write(newsockfd,(char *)&message,sizeof(struct msg));
		  }
		strcpy(message.data,"done");
		message.data[4]='\0';
		write(newsockfd,(char *)&message,sizeof(struct msg));
		fclose(fp1);
	}	
	if(message.type==1)
	send_file(newsockfd,message.data);
	
}	

printf("\n....\n");return 0;
}
                                                                           