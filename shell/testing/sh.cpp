#include<iostream>
#include <cstdio>		//g++ -o sh sh.cpp -lreadline
#include <cstdlib>
#include<cstring>
#include<unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<vector>


using namespace std;

int main()
{
char prompt[50];
vector <pair<int,char *> >hist;

while(1)
{
	strcpy(prompt,"\navd@ubuntu$ ");
    	char *cmd =  readline( prompt ) ;
	printf("%s",cmd);
//	if(cmd[0]=='!')
//		get_old_cmd(cmd,hist);

//	add_hist(hist,cmd);
	
//	execute(cmd);
}
return 0;
}
