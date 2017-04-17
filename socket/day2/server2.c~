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
char str[MAX];

while(1){
		
		read(newsockfd,(char *)msg,sizeof(msg));
		FILE *fp;
		sleep(1);
 			fp = popen(msg, "r");
			  while (fgets(str, sizeof(msg)-1, fp) != NULL) 
			  {
			    write(newsockfd,(char *)str,sizeof(str));
			  }
strcpy(str,"done");
str[4]='\0';
		write(newsockfd,(char *)str,sizeof(str));
		
		memset(str,0,MAX);
		memset(msg,0,MAX);
	sleep(2);
}
return 0;
}


