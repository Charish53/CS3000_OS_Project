#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char* argv[])
{
    int ret;
    char cwd[1000];
    char* path = getcwd(cwd, sizeof(cwd)); // current folder
    char loc_sort[1000]; // location of executable sort1
    strcpy(loc_sort,path);
    strcat(loc_sort,"/myshell");

    char* cmd = loc_sort;
    int id,status = 0;
    id = fork();

    char* args[2];
    args[0] = cmd;
    args[1] = "NULL";
    if(id == 0)
    {
        // open gnome-terminal and hold
        // if you want parent to run, remove --disable-factory argument
        ret = execlp("/usr/bin/gnome-terminal", "gnome-terminal", "--disable-factory", "-e", "./myshell", NULL);
        if(ret==-1)
        {
            perror("Execvp failed :/ \n");
            exit(-1);
        }
    }
    else
    {
        wait(&status);
        printf("+--- Closed shell, exit status = %d\n",status);
    }

}
