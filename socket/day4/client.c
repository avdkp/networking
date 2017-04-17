#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<signal.h>
#define HELP printf("\nCommands available: getlist,disconnect,name_<name>,send_<cli_id>,help");
#define CKSM 4

struct addr{
	int id;
	char name[25];
};

struct msg{
	int fun; //1 getlist 2.naming 3.killing closed clients 4.Broadcasting 5.Newconnection 
	char message[256];
	struct addr dstn;
	struct addr src;
	char checksum[CKSM];
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

	char str[25];

	struct msg *data;
	data = (struct msg *)malloc(sizeof(struct msg));
	printf("Enter your name:");
	scanf("%s",data->src.name);
	data->fun = 5;
	data->dstn.id = 0;
	strcpy(data->dstn.name,"server");
	write(sockfd,(char *)data,sizeof(struct msg));
	struct msg *data1=(struct msg *)malloc(sizeof(struct msg));





	/*
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 5000;
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(sockfd+1,&fds);
	if(select(sockfd+1,&fds,NULL,NULL,&tv))

	*/

	while(1){// Getting Client id...
		if(read(sockfd,(char*)data1,sizeof(struct msg)) > 0)
		data->src.id = atoi(data1->message);
		if(data->src.id > 0) break;
		else printf("\nWaiting to get client id...");
	}
		printf("\nCongratulation your are connected your client id is %d",data->src.id);

	HELP
	int pid = fork();
	int n=0;
	
	

	
	while(1){

		if(pid == 0){
			printf("\ncommand:");scanf("%s",str);
			if(!strcmp(str,"getlist")){
				data->fun = 1;
				data->dstn.id = -1;
				strcpy(data->message,"getlist");
				
				write(sockfd,(char *)data,sizeof(struct msg));
			}

			else if(sscanf(str,"name_%s",data->src.name)){
				data->fun = 2;
				data->dstn.id = -1;
				write(sockfd,(char *)data,sizeof(struct msg));
			}


			else if(sscanf(str,"send_%d",&data->dstn.id) > 0) 
			while(1){printf(":");
				data->fun = 0;
				memset(data->message,'\0',sizeof(data->message))
;
				memset(data->checksum,'\0',sizeof(data->checksum));
				fflush(stdin); scanf("%s",data->message);
				printf("check sum :%s",data->checksum);
				if(!strcmp(data->message,"disconnect")) break;
			//	data->message[strlen(data->message)-1]='\0';
			//	check_sum(&data);
			//	memset(&data,'\0',sizeof(struct msg));
			//	strcpy(data.message,"10101011");
				check_sum(data);
				data->checksum[CKSM]='\0';
				printf("checksum is :%s",data->checksum);
				int x;
				printf("please specify the bit to corrupt:");
				scanf("%d",&x);
				corrupt(data,x);
				printf("data is : %s",data->checksum);
				if( write(sockfd,(char *)data,sizeof(struct msg)) < 0 ) 
				printf("\nSorry Message could not be sent..");
			}
			else HELP
		}

		

		if(pid > 0){
			//char str[sizeof(struct msg)];
			
			//bzero(str,sizeof(str));
			bzero((char *)data1,sizeof(struct msg));
			if(read(sockfd,(char*)data1,sizeof(struct msg)) > 0 ) 
			{
				//data1 = (struct msg *)str;
				printf("\n(\x1b[32m%d\x1b[0m)\x1b[32m%s\x1b[0m: \x1b[32m%s\x1b[0m\n",data1->src.id,data1->src.name,data1->message);}
			else{
				 printf("\nServer Disconnected....");
				 kill(pid,SIGKILL);
				 break;
			}
		}


	}


	
	printf("\n....\n"); return 0;
}







