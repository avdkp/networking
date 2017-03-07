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

int type;	//1 getlist --- 2 download file----3 disconnect --- 4 error
char data[1024];

};
char log_loc[100];
void logger(struct timeval *t1,struct timeval *t2,char *mesg)
{
	printf("PATH:%s",log_loc);
	FILE *fp = fopen(log_loc,"a+");
	if(fp==NULL)
	{
		printf("logging failed ! \n");
		return;
	}
	fprintf(fp,"Started at %llds %lldus\t: total time \t%lld sec %lld usec %s\n",t1->tv_sec,t1->tv_usec,t2->tv_sec - t1->tv_sec,t2->tv_usec - t1->tv_usec,mesg);
	fclose(fp);
}
void getlist(int newsockfd,char *command)
{
	struct timeval t1,t2;
	char *ln = NULL;
	struct msg message;
	memset(&message,'\0',sizeof(message));
	message.type=2;
	size_t len = sizeof(message.data);
	gettimeofday(&t1,NULL);
	char temp[50],path[50],cd[50];
	memset(temp,'\0',sizeof(temp));
	strcpy(temp,command);
	sscanf(temp,"%s %s",cd,path);
	if(strcmp(cd,"cd")==0)
	{
		int n = chdir(path);
		printf("path:%s\n",path);
		FILE *f = popen("pwd","r");
		getline(&ln,&len,f);
		strcpy(message.data,ln);
		//usleep(100);
		write(newsockfd,(char*)&message,sizeof(message));
		usleep(100);
		memset(message.data,'\0',sizeof(message.data));
		strcpy(message.data,"done");
		write(newsockfd,(char*)&message,sizeof(message));
		return;
	}
	printf("hello\n");
	FILE *fp = popen(command,"r");
	while (getline(&ln, &len, fp) != -1)
   	{
		strcpy(message.data,ln);
		fputs(message.data, stdout);
		write(newsockfd,(char *)&message,sizeof(message));
		memset(&message,'\0',sizeof(message));
	}
	strcpy(message.data,"done");
	write(newsockfd,(char *)&message,sizeof(message));
	gettimeofday(&t2,NULL);
	
	logger(&t1,&t2,"list sent successfully");

}
void sendfile(int newsockfd,char *file)
{
	char fileloc[30];
	//strcpy(fileloc,"data/");
	//strcat(file,file);
	FILE *fp = fopen(file,"r");
	struct msg message;	
	if(fp==NULL)
	{
		message.type=4;
		strcpy(message.data,"File not found !!!");
		return;
	}
	int len=0;
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);
	message.type=2;
	long long int data=0;
	do
	{
		len = fread(message.data,1,sizeof(message.data),fp);
		printf("%s",message.data);
		int send = write(newsockfd,(char *)&message,len+sizeof(message.type));
printf(message.data);
		data += len;
		memset(message.data,'\0',sizeof(message.data));	
	}while(len==sizeof(message.data));
		strcpy(message.data,"done");
		write(newsockfd,(char *)&message,sizeof(message));
	
	gettimeofday(&t2,NULL);
	char mesg[100];
	sprintf(mesg,"%lld bytes of data sent:\tDownloaded file:\t%s",data,file);
	logger(&t1,&t2,mesg);

}
void error(int newsockfd,char *mesg)
{
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);
	gettimeofday(&t2,NULL);
	logger(&t1,&t2,mesg);
	struct msg message;
	message.type=4;
	strcpy(message.data,mesg);
	write(newsockfd,(char*)&message,sizeof(message));
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
serv_addr.sin_addr.s_addr = INADDR_ANY;

if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
{ 
 	printf("\nBinding Error...."); 
	exit(2);
}
FILE *fp = popen("pwd","r");
char *l = NULL;
size_t len = 50;
getline(&l,&len,fp);
memset(log_loc,'\0',sizeof(log_loc));
strcpy(log_loc,l);
log_loc[strlen(log_loc)-1]='\0';
strcat(log_loc,"/log.txt");
listen(sockfd,5);
//	getlist(5);
        //sleep(5);
       // continue;

while(1)
{
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd<0)
	{	
		printf("failed ..\n");
		continue;
	}
	struct timeval t1,t2;
	gettimeofday(&t1,NULL);
	gettimeofday(&t2,NULL);
	char mesg[100];
	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET,&(cli_addr.sin_addr), str,INET_ADDRSTRLEN );
	sprintf(mesg,"Client id:%d ip:%s connected on port %d",getpid(),str,ntohs(cli_addr.sin_port));
	logger(&t1,&t2,mesg);
	int pid = fork();
	if(pid>0)
	{
		struct msg message; 
		while(1)
		{
			memset(&message,'\0',sizeof(struct msg));
			int size = read(newsockfd,(char *)&message,sizeof(struct msg));
			if(message.type==3)
			{
				close(newsockfd);
				break;
			}
			switch(message.type)
			{
			case 1: getlist(newsockfd,message.data);
				break;
			case 2: sendfile(newsockfd,message.data);
				break;
			}
		
		}


	}
	


}


return 0;
}
