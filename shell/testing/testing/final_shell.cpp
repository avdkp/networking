#include<bits/stdc++.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>

#define MAX_SIZE 1000
#define MAX_PIPES 50 
using namespace std;

int std_in,std_out;
void* execute(void* cmd);
void pipe_execute(char all[][MAX_SIZE],int,int);
void process(char *);
int get_all(char *,char all[][MAX_SIZE]);
int main(int argc, char *argv[])
{
	std_in = dup(fileno(stdin));
	std_out = dup(fileno(stdout));
	while(1)
	{
		char *buffer = readline("avd@MyShell$ ");

		if (buffer) {
		    if(buffer&&*buffer&&*buffer!='\n')
			{
				add_history(buffer);
				int aa = fork();
				if(aa==0)
				process(buffer);
				else
				{
					wait(NULL);
				}
			}
			dup2(std_in,0);
			free(buffer);
		}
		
	}
    return 0;
}
int get_all(char *cmd,char all[][MAX_SIZE])
{
	int i=0;
	char *t;
	t=strtok(cmd,"|");
	do
	{
		strcpy(all[i],t);
		i++;
		t=strtok(NULL,"|");
	}while(t);
return i;
}
void process(char *cmd)
{
	char all[MAX_PIPES][MAX_SIZE]={'\0'};
	int n = get_all(cmd,all);
//	for(int i=0;i<n;++i)
//		cout<<i+1<<" "<<all[i]<<endl;
	char cm[100]={'\0'};
	
	pipe_execute(all,1,n);
}
void pipe_execute(char all[][MAX_SIZE],int i,int n)
{
	if(i==n)
	{
		int err;
		pthread_t tid;
		char *to_send=all[i-1];
		err = pthread_create(&tid, NULL, execute,to_send);
		usleep(100000);
		close(fileno(stdin));
	}
	else
	{
		int fd[2];
		char cmd1[100];
		pipe(fd);
		pid_t pid = fork();
		if(pid==0)
		{
			dup2(fd[1],fileno(stdout));
			strcpy(cmd1,all[i-1]);
			execute(all[i-1]);
			close(fileno(stdout));
		}
		else
		{
			int c,status;
		wait(NULL);
			dup2(fd[0],fileno(stdin));
			pipe_execute(all,i+1,n);
		}
	}
}
void * execute(void *cmd2)
{
	char *cmd = (char*)cmd2;	
	char cmd1[MAX_SIZE];
	strcpy(cmd1,cmd);
	system(cmd1);	
	exit(1);
}










