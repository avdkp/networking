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
#define CKSM 4
struct msg{
char message[256];
char checksum[CKSM+1];

};

void corrupt(struct msg *data ,int i)
{
	data->message[i] = (data->message[i]=='1'?'0':'1');	
}
void getsum(char *c,char *a,char b)
{
//	printf("data: %c,%c,%c\n",*c,*a,b);
	if(*c=='1'&&*a=='1'&&b=='1')
	{	
		*a = '1';
		*c = '1';
	}
	else if((*c=='1'&&*a=='1'&&b=='0')||(*c=='1'&&*a=='0'&&b=='1')||(*c=='0'&&*a=='1'&&b=='1'))
	{
		*c = '1';
		*a = '0';
	}
	else if((*c=='1'&&*a=='0'&&b=='0')||(*c=='0'&&*a=='1'&&b=='0')||(*c=='0'&&*a=='0'&&b=='1'))
	{	
		*c = '0';
		*a = '1';
	}
	else if(*c=='0'&&*a=='0'&&b=='0')
	{
		*c = '0';
		*a = '0';
	}
	else
	{
		printf("Invalid input... sum aborted:%c,%c,%c",*c,*a,b);
	}
}
void check_sum(struct msg *data)
{
	memset(data->checksum,'\0',sizeof(data->checksum));
	int i=0;
	int l = strlen(data->message);
	if(l%CKSM!=0)
	{
		printf("DATA is :%s",data->message);
		printf("check sum can not be calculated bcz CKSM is %d and message_length is %d",CKSM,l);
		return;
	}
	while(data->message[i])
	{
		if(data->message[i]!='0'&&data->message[i]!='1')
		{
			printf("data is invalid ...checksum aborted!!\n");
			return;
		}
		i++;
	}
	int x;
	for(x=0;x<CKSM;++x)
		data->checksum[x]=data->message[x];
	
	i = CKSM;
	int j;
	while(i<l)
	{
		char c='0';
		for(j=i+CKSM-1;j>=i;--j)
		{
		//	printf("loop1:j=%d\n",j);
			getsum(&c,&(data->checksum[j%CKSM]),data->message[j]);
		//	printf("checksum:%s\n",data->checksum);
		//	sleep(1);
		}
		for(j=CKSM-1;j>=0;--j)
		{
			getsum(&c,&(data->checksum[j]),'0');
		}
		i+=CKSM;
	}
	i=-1;
	while(++i<CKSM) data->checksum[i] = data->checksum[i]=='1'?'0':'1';
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
printf("connected\n");
struct msg data;
while(1){
		memset(&data,'\0',sizeof(data));
		read(newsockfd,(char *)&data,sizeof(data));
		printf("Data is :%s\n",data.message);
		char old[CKSM];
		strcpy(old,data.checksum);
		check_sum(&data);
		//sleep(1);
		printf("old:%s,new:%s\n",old,data.checksum);
		old[CKSM]=data.checksum[CKSM]='\0';
		if(strcmp(old,data.checksum)!=0)
		{
			printf("data is corrupt\n");
			continue;
		}
		//write(newsockfd,(char *)&data,sizeof(data));
}
return 0;
}

