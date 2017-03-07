#include<bits/stdc++.h>
#include<readline/readline.h>
#include<readline/history.h>

using namespace std;

int main()
{
char *line=NULL;
HISTORY_STATE hs;
using_history();

while(1)
{
line=readline("prompt>");
if(line[strlen(line)]=='\0')
	cout<<"yes"<<endl;

cout<<line;
add_history(line);
if(strcmp(line,"history")==0)
{
hs = history_get_history_state();
for(int i=0;i<hs->length;++i)
	cout<<(hs->entries[i])<<endl;

}
free(line);
}
return 0;
}
