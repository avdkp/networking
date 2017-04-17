#include<stdio.h>
#include<unistd.h>
int main()
{
int ret;

printf("\texecl\n");
//system("kill -2");
//execl ("/home/avd/os/mai", "mai","hello","i'm","avd", NULL);
printf("\texecle\n");
system("PATH=$PATH:/home/avd/os/");
system("export");
//char *env[]={"PATH=/home/avd/os",(char *)0};
system("echo $PATH");
execlp("mai","mai","-l",(char *)0);
return 0;
}
