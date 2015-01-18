#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>

int start_child(char* x,int p_numb){
    pid_t child_id;
    char p_numb_str[10];
    sprintf(p_numb_str,"%i",p_numb);
    char* arg[] ={"./child",x,p_numb_str,NULL};
    child_id=fork ();
    if  (child_id != 0){
        return child_id;
    }
    else{
        execvp("./child",arg);
    }
    return 0;
}

int main (int argc,char *argv[]){
    pid_t child_id;
    int i,n,nice_val;
    int status;

    n=atoi(argv[1]);

    if(argc>1){
        for(i=0;i<n;i++){
            child_id=start_child(argv[2],i);
            nice_val=atoi(argv[3+i]);
            printf("nv %i \n",nice_val);

            setpriority(PRIO_PROCESS,child_id,nice_val);
            nice_val=getpriority(PRIO_PROCESS,child_id);
            printf("nv %i \n",nice_val);
            printf("%i \n",(int)child_id);

        }
        wait(&status);

    }
    else{
        printf("brauche argumente");
        return -1;
    }
return  0;
}
