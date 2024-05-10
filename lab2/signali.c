/* Operacije nad signalima */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "signali.h"
#include "datoteke.h"
#include <math.h>

/* implementacija funkcija, vec opisanih u lab1 + postavi_signale() */
void postavi_signale() 
{
	struct sigaction act;

	/* 1. maskiranje signala SIGUSR1 */

	/* kojom se funkcijom signal obradjuje */
	act.sa_handler = obradi_dogadjaj;

	/* koje jos signale treba blokirati dok se signal obradjuje */
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGTERM);

	act.sa_flags = 0; /* naprednije mogucnosti preskocene */

	/* maskiranje signala - povezivanje sucelja OS-a */
	sigaction(SIGUSR1, &act, NULL);

	/* 2. maskiranje signala SIGTERM */
	act.sa_handler = obradi_sigterm;
	sigemptyset(&act.sa_mask);
	sigaction(SIGTERM, &act, NULL);

	/* 3. maskiranje signala SIGINT */
	act.sa_handler = obradi_sigint;
	sigaction(SIGINT, &act, NULL);

	printf("Program s PID=%ld krenuo s radom\n", (long) getpid());
}

void obradi_dogadjaj(int sig) 
{
	int broj = pronadji_zadnji_broj();
	printf("Primio signal SIGUSR1, broj je %d\n",(int) sqrt(broj));
}

void obradi_sigterm(int sig) 
{
	printf("Primio signal SIGTERM, pospremam prije izlaska iz programa\n");
	nije_kraj = 0;
}

void obradi_sigint(int sig) 
{
	printf("Primio signal SIGINT, prekidam rad\n");
	exit(1);
}