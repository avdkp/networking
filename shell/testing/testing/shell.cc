#include<bits/stdc++.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>
using namespace std;


std::vector<string> history(21);

void scanline(char str[]){
int i=0;
char ch;
while( (ch = getchar()) != '\n') {str[i] = ch; i++;}
str[i] = '\0';
}


bool redirection(char buff[]){
	for(int i=0;i<strlen(buff);i++) if(buff[i] == '>' || buff[i] == '>') return 1;
	return 0;
}
bool background(char str[]){
	for(int i=0;i<strlen(str);i++) if(str[i] == '&') return 1;
	return 0;
}

void execute_command(char buff[]){
	char str[300];
	FILE *fp = popen(buff,"r");
	if(fp == NULL){ printf("%s failed..\n",buff); exit(1);}
	while(!feof(fp)){
		bzero(str,256);
		fread(str,256,1,fp);
		str[256] = '\0';
		printf("%s",str);
	}
	fflush(stdout); printf("\n");
	pclose(fp);
}

/*Signal Handler, to reap childrens from process table.
	This stops the child processes from becoming ZOMBIES.
	They are reaped off as soon as they exit.....
*/
void sigchld_handler(int sig) {
  int saved_errno = errno;
  while (waitpid((pid_t)(-1), 0, WNOHANG) > 0) {}
  errno = saved_errno;
}

int main(){
	char buff[100];
	char tbuff[100];
	char pwd[100];
	int index=0;
	getcwd(pwd,sizeof(pwd));
	signal(SIGCHLD,sigchld_handler);
	while(1){
		printf("%s>",pwd); fflush(stdout);
		scanline(buff);
		strcpy(tbuff,buff);
		history[index] = (string)buff;
		if(!strncmp(buff,"exit",4)){
			char cmd[100];
			sprintf(cmd,"ps -l | grep %d | wc -l",getpid());
			char str[300];
			FILE *fp = popen(cmd,"r");
			if(fp == NULL){ printf("%s failed..\n",buff); exit(1);}
			fread(str,256,1,fp);
			if(atoi(str) > 2){
				printf("You have %d childrens, first kill them then exit...\n",atoi(str)-2);
				strcpy(buff,"jobs");
			}
			else break;
			fflush(stdout); printf("\n");
			pclose(fp);
		}
		//This prints the jobs, that is processes running in backgroud...
		if(!strncmp(buff,"jobs",4)){
			int pid = getpid();
			sprintf(buff,"pstree -p %d",pid);
			char str[300];
			FILE *fp = popen(buff,"r");
			if(fp == NULL){ printf("%s failed..\n",buff); exit(1);}
			///*
			char ch;
			int flag = 0;
			while(1){
				ch = fgetc(fp);
				if(ch == EOF){
					index = (index+1)%20;
					flag = 1;
					break;
				}
				if(ch == '\n') break;
			}
			if(flag) continue;
			//*/
			while(!feof(fp)){
				bzero(str,256);
				fread(str,256,1,fp);
				str[256] = '\0';
				printf("%s",str);
			}
			fflush(stdout); printf("\n");
			pclose(fp);
			index = (index+1)%20;
			continue;
		}
		//To get previous command use "!-n" where 'n' specifies the 'nth' previous command.
		if(!strncmp(buff,"!",1)){
			int hist_no;
			sscanf(buff+1,"%d",&hist_no);
			hist_no = index+hist_no;
			hist_no = hist_no>=0?hist_no%20:hist_no+20;
			const char *sss  = history[hist_no].c_str();
			strcpy(buff,sss);
			history[index] = (string)buff;
		} 
		if(!strncmp(buff,"history",7)){
			for(int i=0;i<20;i++) cout<<history[i]<<endl;
			index = (index+1)%20;
			continue;
		}
		if(!strncmp(buff,"cd ",3)){
			chdir(buff+3);
            getcwd(pwd,sizeof(pwd));
		}
		else if(redirection(buff)) system(buff);
		else if(background(buff)){
			char nbuff[100];
			bzero(nbuff,256);
			strncpy(nbuff,buff,strlen(buff)-1);
			int pid = fork();
			if(pid == 0){
				execute_command(nbuff);
				exit(1);
			}
			printf("Process created with pid: %d\n",pid);
		}
		else{
			execute_command(buff);
		}
		index = (index+1)%20;
	}

cout<<"Thanks for using this Shell...."<<endl;
return 0;
}
