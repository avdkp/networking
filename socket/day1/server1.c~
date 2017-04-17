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
while(i<2){

newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd>=0)
	{
	i++;
char inbuffer[100];
char str[100];
	int pid = fork();
		if(pid==0)
		{
			while(1)
			{
				memset(str,0,sizeof(str));
				scanf("%[^\n]%*c",str);
	
			write(newsockfd,(char *)str,sizeof(str));
			
			sleep(1);

				


			}
		
		}
		else
		{
			
			while(1)
			{
int quant = read (newsockfd, inbuffer, sizeof(inbuffer));
		printf ("Received: %*.*s\n", quant, quant, inbuffer);
		//printf("family:%d\nport:%d\nip:%d",cli_addr.sin_family,cli_addr.sin_port,cli_addr.sin_addr.s_addr);
		fflush(stdout);
		memset(inbuffer,0,sizeof(inbuffer));
		sleep(1);
			}
		}

	}
}
return 0;
}
