#include<bits/stdc++.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#define MAX_SIZE 1000
#define MAX_PIPES 50 
using namespace std;

int std_in,std_out;
void execute(char cmd[MAX_SIZE]);
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
				process(buffer);
			}
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
	//	cout<<"was here"<<all[i-1]<<endl;
		execute(all[i-1]);
	}
	else
	{
		int fd[2];
		pipe(fd);
		pid_t pid = fork();
		if(pid==0)
		{
	//		cout<<"came here"<<all[i-1]<<endl;
			dup2(fd[1],fileno(stdout));
			execute(all[i-1]);
		}
		else
		{
	//		cout<<"wating...."<<endl;
			
			int c,status;
		wait(&status);
			sleep(1);
	//	system("echo test23 >> a");
	//		cout<<"wait over .."<<endl;
			dup2(fd[0],fileno(stdin));
			pipe_execute(all,i+1,n);
		}
	}
}
void execute(char cmd[])
{
	char cmd1[MAX_SIZE];
	dup2(fileno(stdout),std_out);
	strcpy(cmd1,cmd);
	char *a = strtok(cmd," ");
	char *b = strtok(NULL," ");
	
	int pid = fork();
	if(pid==0)
	{
		execlp(a,a,b,(char*)0);
	}
	else
	{
			int c,status;
			//wait(&status);
			usleep(100000);
//			cout<<-1;
//			system("echo hi >>a");
			return;
	}
	
}










