#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

int main(int argc, char** argv){
	int i,n=5;
	int a[atoi(argv[2])];
	int which = PRIO_PROCESS;
	if(atoi(argv[2])+3!=argc){      // abfrage nach gültiger eingabe
		printf("ungueltige eingabe.\nErst X, dann Anzahl der Kindprozesse und dann die jeweiligen nice-Werte.");
		return 0;
	}

	for(i=0;i<(atoi(argv[2])-1);i++){   // sicherheitshalber
		a[i]=0;
	}

	pid_t pid;

	for(i=0;i<(atoi(argv[2]));i++){       // erstellen der kindprozesse
		if(pid>0){
			pid=fork();
			if(pid==0){
				setpriority(which,getpid(),atoi(argv[i+3]));    // setzen der nice-Werte
				a[i]=getpid();
				if(a[i]==getpid()){          // zur wiedererkennung des prozesses
					n=i;
				}
			}
		}

		if(pid<0){
			printf("Fehler beim Fork!");
			exit(-1);
		}
	}

	//if(pid==0)printf("prio: %i. ",getpriority(which, getpid()));// Zur Kontrolle der nice-Werte

	if(pid<0){
		printf("Fehler beim Fork!");
		exit(-1);
	}else if(pid==0){
		while(1){
			clock_t start = clock(), diff;            // Zeit ermitteln
			for(i=0;i<=(atoi(argv[1]));i++);
			diff = clock() - start;
			int msec = diff * 1000 / CLOCKS_PER_SEC;

			printf("Child process %i - Time: %d.%d seconds\n", n, msec/1000, msec%1000);

		}
		exit(1);
	}else {
		wait(NULL);      // Warten auf Kindprozesse
		printf ("Child Complete");
		exit(0);
	}

	return 1;
}
