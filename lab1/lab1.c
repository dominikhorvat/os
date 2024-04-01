#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<math.h>

int broj = 0;
int nije_kraj = 1;

const char* obrada = "obrada.txt";
const char* status = "status.txt";

FILE *fwobrada;
FILE *fwstatus;

void obradi_dogadjaj(int sig)
{
    printf("Primio signal SIGUSR1, broj je %d\n",broj);
}

void obradi_sigterm(int sig)
{
    printf("Primio signal SIGTERM, pospremam prije izlaska iz programa\n");
    fwstatus = fopen(status, "w");
    fprintf(fwstatus, "%d", broj);
    fclose(fwstatus);
    nije_kraj = 0;
}

void obradi_sigint(int sig)
{
    printf("Primio signal SIGINT, prekidam rad\n");
    exit(1);
}

int main()
{
    struct sigaction act;

    /*1. maskiranje signala SIGUSR1 */
    act.sa_handler = obradi_dogadjaj;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGTERM);
    act.sa_flags = 0;
    sigaction(SIGUSR1, &act, NULL);

    /* 2. maskiranje signala SIGTERM */
    act.sa_handler = obradi_sigterm;
    sigemptyset(&act.sa_mask);
    sigaction(SIGTERM, &act, NULL);

    /* 3. maskiranje signala SIGINT */
    act.sa_handler = obradi_sigint;
    sigaction(SIGINT, &act, NULL);

    printf("Program s PID = %ld krenuo s radom\n", (long) getpid());

    FILE *frstatus = fopen(status, "r");
    if(fscanf(frstatus, "%d", &broj) != EOF){
        fclose(frstatus);
        if(broj == 0){
            FILE *frobrada = fopen(obrada, "r");
            int br;

            while(fscanf(frobrada, "%d", &br));
            
            broj = sqrt(br);
            fclose(frobrada);
        }
        broj = broj + 1;
    }

    fwstatus = fopen(status, "w");
    fprintf(fwstatus, "%d", 0);
    fclose(fwstatus);

    while(nije_kraj){
        int x = broj * broj;

        fwobrada = fopen(obrada, "a");
        fprintf(fwobrada, "%d\n", x);
        fclose(fwobrada);

        printf("Program: upisujem broj %d\n", x);
        sleep(5);

        broj = broj + 1;
    }

    return 0;
}