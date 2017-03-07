#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>



char *stripwhite ();
char * dupstr (char *s);
void execute_line (char *line);
void execute(char *line);

int done;

int main ()
{
  char *line, *s,*t;
  for ( ; done == 0; )
    {
      line = readline ("avd@MyShell: ");
      if (!line)
        continue;
      t=line;
      printf("%s\n",line);
      s = line;
      if (*s)
        {
          add_history (s);
          execute_line(s);
        }
      free(t);
    }
return 0;
}

char * dupstr (char *s)
{
  char *r;

  r = (char *)malloc (strlen (s) + 1);
  strcpy (r, s);
  return (r);
}
/*void execute(char *line)
{
  printf("full line is :%s\n",line);
  char l[1000];
  strcpy(l,line);
  char *tok = strtok(l,";");
  while(tok)
  {
    printf("command : %s\n",tok);
    execute_line(tok);
    tok=strtok(NULL,";");
  }
  printf("command : %s\n",tok);
}*/
void doit(char *l)
{
 char path[100];	
	FILE *fp = popen(l, "r");
	if (fp != NULL)
	    /* Handle error */;


	while (fgets(path, 100, fp) != NULL)
		    printf("%s", path);
    pclose( fp );
    
}
void execute_line (char *line)
{
  int i;
  char *cmd;

  /* Isolate the command word. */
  cmd = line;
  char temp[100];
  strcpy(temp,cmd);

  char *tok = strtok(temp," ");
  if(strcmp(tok,"cd")==0)
  {
      tok = strtok(NULL," ");
      chdir(tok);   
  }
  else if (strcmp(tok,"quit")==0)
  {
      done=1;
  }
  else if (strcmp(tok,"jobs")==0)
  {
    int pid = getpid();
    char cmd[100];
    printf("pid : %d",pid);
    sprintf(cmd,"pstree -p %d\0",pid);
    doit(cmd); 
  }
  else 
  {
    doit(cmd);
  }
  return;
}

char *stripwhite (char *string)
{
  char *s, *t;
  for (s = string; *s==' '; s++);
  if (*s == 0)
    return (s);
  t = s + strlen (s) - 1;
  while (t > s && *t)
    t--;
  *++t = '\0';
  return s;

}
