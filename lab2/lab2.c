/* Glavna datoteka za lab2 s funkcijom main */

#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "signali.h"
#include "datoteke.h"

//globalne varijable; koriste se (ili će se koristiti) u funkcijama i obradama signala
char *dat_status, *dat_obrada, *dat_mreza;
int broj = 0;
int nije_kraj = 1;

/* funkcije koje rade dretve */
void *mreza(void *);
void *obrada(void *);

int main(int argc, char *argv[])
{
	if (argc < 4) {
		fprintf(stderr, "Koristenje: %s <status-datoteka> "
		 "<datoteka-s-podacima> <cjevovod>\n", argv[0]);
		exit(1);
	}
	dat_status = argv[1];
	dat_obrada = argv[2];
	dat_mreza = argv[3];

	postavi_signale();

    /* dohvati prvi broj i zapisi 0 u status */
	broj = procitaj_status();
	zapisi_status(0);
    
    /* stvori dretve: radnu i mreznu */

	pthread_t opisnik[2];
	int id[2];

    id[0]=0;
    id[1]=1;

	if(pthread_create(&opisnik[0], NULL, obrada, &id[0]))
    {
        fprintf(stderr, "Ne mogu stvoriti dretvu!\n");
        exit(1);
	}

	if(pthread_create(&opisnik[1], NULL, mreza, &id[1]))
    {
        fprintf(stderr, "Ne mogu stvoriti dretvu!\n");
        exit(1);
	}

    int br_konzole;
	while(nije_kraj)
    {
		if(scanf("%d", &br_konzole) > 0)
        {
			if(br_konzole > 0)
	            broj = br_konzole;
			else 
                nije_kraj = 0;
		}
	}
    //cekaj na kraj dretve obrada, ali ne i one druge mrezne
	pthread_join(opisnik[0], NULL);


	return 0;
}

void *obrada(void *p)
{
    /* slicno kao u lab1 */
	int x;
	broj = procitaj_status();
    
	if (broj == 0) 
    {
		broj = pronadji_zadnji_broj();
		broj = sqrt(broj);
	}

	zapisi_status(0);

	while(nije_kraj)
    {
		broj = broj + 1;
		x = broj * broj;
		dodaj_broj(x);
		printf("Program: upisujem broj %d\n", x);
		sleep(5);
	}

	zapisi_status(broj);

	return NULL;
}


void *mreza(void *p)
{
    //u petlji cekaj da se nesto pojavi u cijevi
	//ako je procitano > 0 onda ga postavi u broj
    int br_mrez;
	while(nije_kraj){
        br_mrez = dohvati_iz_cijevi();
        if(br_mrez>0){
            broj = br_mrez;
            printf("Procitan broj iz cijevi: %d\n", broj);
       	 }
	}
	return NULL;
}
