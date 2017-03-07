#include<bits/stdc++.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;
int main()
{
int fd[2];
pipe(fd);
int id =fork();
if(id==0)
{
//	sleep(1);
	system("history");
	int a;
	char buff[100],x[100];
	strcpy(x,"aaaaaaaa>aa >>bbbbbbb");
	char *t = strtok(x,">>");
	t = strtok(NULL,">>");
	cout<<t<<endl;
	sleep(1);
	
//	char buff[100];
	write(fd[1],x,100);
	dup2(fd[0],fileno(stdin));
	cin>>buff;
	cout<<buff<<endl;
	while(1);
//	a = dup(fileno(stdout));
//	dup2(fd[1],fileno(stdout));
//	cout<<"hello"<<endl;
//	dup2(a,fileno(stdin));
	
//	cout<<x<<endl;
//	char str[10];
//	read(fd[0],str,10);
//	dup2(fileno(stdout),a);
//	cout<<"xxxx"<<str<<endl;



}
else
{

	while(1);
	
//	int a;
//	char str[2]={'a','\0'};
//	write(0,str,2);
}
return 0;
}
