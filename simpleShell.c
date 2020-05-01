#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#define MAX 500
#define DELIMITER " \n"
//#include <ctype.h>
//#include <limits.h>



void SignalHandler(){
    FILE *f; // pointer to file
    pid_t id;
    int status;
    pid_t temp= waitpid(-1, &status, WNOHANG); //kill any process
    f= fopen("file.log","a+"); //open file and append line

    /*if(!f){
        fprintf(stderr, "Error openning file");
    }*/
    fprintf(f,"Child process with id %d was termintaed\n", id);
    fclose(f);

}

int parse(char *command, char** parameter)
{
    int i = 0;  // iterator of tokens
    int bg = 0;
    char *ptr = strtok(command, DELIMITER); // array of tokens


    while( ptr != NULL )
    {
        parameter[i] = ptr;
        if(strcmp(ptr, "&") == 0){  //check if there is & in command to process
        parameter[i] = NULL;
        bg = i;
        }
        ptr = strtok(NULL, DELIMITER);
        i++;
        }
    parameter[i] = NULL;    //add null at the end

    return bg;
}

void main()
{
    int k;
    int bg; // used in case of &
    char *parameter[32]; //pointer used in separating commands
    char command[MAX]; //array for command input
    int state;
    pid_t child_id;

    for(k=1;k>0;k++)  // start loop
    {
        printf("Nounou>>");     //ready to take command or input
        fgets(command,MAX,stdin);   //read line
        printf("\n");

        bg=parse(command, parameter);
        if(parameter[0]==NULL) ; //null means no command
        else


    signal(SIGCHLD,SignalHandler);  //call interrupt handler



    if(strcasecmp(parameter[0], "exit") == 0)
        exit(0);
    else {

        child_id = fork();  //fork function


        if (child_id < 0)   // error in forking
        {
            printf (stderr, "error while forking\n");
        }

        else if (child_id == 0)    // correct value for child
        {
            //printf("child id is %d",getpid());
            execvp(parameter[0], parameter); //execute program
printf("hamada \n");
            printf ("error while exec or not supported command\n");
        }

        else if(!bg)    // wait for process in background
        {

            while(wait(&state) != child_id);

        }
        else  sleep(1);

    }

    }
}
