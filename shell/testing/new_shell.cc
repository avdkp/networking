#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#define MAX_SIZE 1000

char **auto_completion(const char *, int, int);
char *auto_generator(const char *, int);
void populate_auto_list();
char *auto_list[MAX_SIZE];

void populate_auto_list(char *path)
{
	for(int i=0;i<MAX_SIZE;++i)
		free(auto_list[i]);
	FILE *fp=popen("ls","r");
	if(fp==NULL) return;	
	int i=0;
	size_t len = 256;
	while(i<256 && getline(&auto_list[i],&len,fp)>0) 
	{
		auto_list[i][strlen(auto_list[i])-1]='\0';
		i++;
	}
}

int main(int argc, char *argv[])
{
	//char
    rl_attempted_completion_function = auto_completion;

	while(1)
	{
		populate_auto_list();
		char *buffer = readline("avd@ubuntu$ ");
		if (buffer) {
		    printf("You entered: %s\n", buffer);
		    free(buffer);
		}
	}
    return 0;
}

char ** auto_completion(const char *text, int start, int end)
{
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, auto_generator);
}

char * auto_generator(const char *text, int state)
{
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    while ((name = auto_list[list_index++])) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }
    return NULL;
}
