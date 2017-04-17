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
#define MAX 100
char * process(char msg[]);
int main(int argc, char **argv){

int sockfd, newsockfd, portno, clilen;
if(argc < 2){  printf("\nenter: %s [portno]",argv[0]); return 1;}
int n=1;
struct sockaddr_in serv_addr, cli_addr;

sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd < 0) { printf("Error creating socket...."); exit(1); }

bzero(&serv_addr,sizeof(struct sockaddr_in));
portno = atoi(argv[1]);
char str[256];
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(portno);
serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
 { printf("\nBinding Error...."); exit(2);}
listen(sockfd,5);
int i=0;
clilen = sizeof(cli_addr);
newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
if(newsockfd<0)
{
	printf("hello%d",newsockfd);
	exit(1);
}
char msg[MAX];
while(1){
		
		read(newsockfd,(char *)msg,sizeof(msg));
		char *a = process(msg);
		printf("\nsending :%s\n",a);
		sleep(1);
		
		write(newsockfd,(char *)a,sizeof(msg));
		if(strlen(a)<2)
		{
			printf("Done\n");
			break;
		}
		memset(a,0,MAX);
		memset(msg,0,MAX);
}
return 0;
}

char * process(char msg[])
{
	int j=0,sum=0,i=0;
	char *temp;
	temp = (char *)malloc(MAX*sizeof(char));
	printf("\n-data:%s\n",msg);
	while(msg[j])
	{
		if(msg[j]-(int)'0'<0||msg[j]-(int)'0'>9)
		{
			printf("%c",msg[j]);
			strcpy(temp,"invalid input !!!");
			return temp;
		}
		sum += msg[j]-(int)'0';
		j++;
	}
sprintf(temp,"%d%c",sum,'\0');
return temp;
}
