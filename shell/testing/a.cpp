#include<bits/stdc++.h>	
#include <stdio.h>
#include<unistd.h>
#include<readline/readline.h>
#include <readline/history.h>
using namespace std;
int main( int argc, char **argv)
{
	while(1)
	{
	char *a = readline("avd@ubuntu$ ");
	system(a);
	add_history(a);
	free(a);
	}

return 0;
}
