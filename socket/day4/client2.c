#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
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
	struct msg data;
	fflush(stdin);
	int i=0;
		while(1)
		{
			memset(&data,'\0',sizeof(data));

			printf("Enter the data:");
			scanf("%s",data.message);


			check_sum(&data);
				data.checksum[CKSM]='\0';
				printf("checksum is :%s",data.checksum);
				int x;
				printf("\nplease specify the bit to corrupt:");
				scanf("%d",&x);
				corrupt(&data,x);
				printf("data is : %s",data.message);
			int a = write(sockfd,(char *)&data,sizeof(data));
			printf("%d",a);
			//sleep(1);	
		}


return 0;
}

