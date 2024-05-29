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
int broj_dretvi = 1;
int postavljeni_broj_dretvi = 1;

pthread_mutex_t m; //monitor
pthread_cond_t red; //red uvjeta

/* funkcije koje rade dretve -> za lab3 */
void *kontrola_broja_dretvi(void *);
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

    /* dohvati prvi broj...*/
	broj = procitaj_status();

    //provjera je li broj=0
    if(broj == 0)
    {
        broj = pronadji_zadnji_broj();
        broj = (int)sqrt(broj);
    }

    /*...i zapisi 0 u status*/
	zapisi_status(0);

    //odgovarajuca poruka
    printf("Krecem s radom, zadnji broj je bio: %d \n", broj);
	
    /* stvaramo dretve */
    pthread_t kontrola;
    pthread_t radna;

    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&red, NULL);

	if(pthread_create(&kontrola, NULL, kontrola_broja_dretvi, NULL))
	{
		fprintf(stderr, "Ne mogu stvoriti kontrolnu dretvu!\n");
		exit(1);
	}

	if(pthread_create(&radna, NULL, obrada, NULL))
	{
		fprintf(stderr, "Ne mogu stvoriti radnu dretvu!\n");
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

    zapisi_status(broj);
	
	pthread_join(radna, NULL);
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&red);

	return 0;
}

//napravljeno prema skici rjesenja s web-a
void *kontrola_broja_dretvi(void *p)
{
    while(nije_kraj)
    {
        // x = dohvati_novi_broj_dretvi() => dohvacamo iz cijevi
        int x = dohvati_iz_cijevi();
        if(x >= 1 && x <= 100)
        {
            pthread_mutex_lock(&m);
            postavljeni_broj_dretvi = x;
            while(broj_dretvi < postavljeni_broj_dretvi)
            {
                pthread_t t_obrada;
                if(pthread_create(&t_obrada, NULL, obrada, NULL))
                {
                    fprintf(stderr, "Ne mogu stvoriti radnu dretvu!\n");
                    exit(1);
                }
                //odgovarajuca poruka
                printf("Stvorena je dretva!\n");
                broj_dretvi++;
            }
            pthread_mutex_unlock(&m);
        }
    }
    return NULL;
}

void *obrada(void *p)
{
	pthread_mutex_lock(&m);
    while(nije_kraj)
    {
        if(broj_dretvi > postavljeni_broj_dretvi)
        {
            broj_dretvi--;
            //odgovarajuca poruka
            printf("Obrisana je dretva!\n");
            pthread_mutex_unlock(&m);
            pthread_exit(NULL);
        }
        
        broj++; // da se izbjegne npr. pri prvom pokretanju dupla 1
		int moj_broj = broj;
		
		pthread_mutex_unlock(&m);

		//odgovarajuca poruka
		printf("Trenutni broj na obradi: %d\n", moj_broj);

		int x = moj_broj * moj_broj;
		sleep(5);

		pthread_mutex_lock(&m);
		dodaj_broj(x);
		printf("Program: upisujem broj %d\n", x);

        /* Kod s "varanjem":
        broj++; 
        int moj_broj = broj;
        printf("Obradjujem broj: %d\n", moj_broj);
        
        int x = moj_broj * moj_broj;
        dodaj_broj(x);
        printf("Program: upisujem broj %d\n", x);
        
        pthread_mutex_unlock(&m);
        
        sleep(5);
        
        pthread_mutex_lock(&m);
         */
    }

    pthread_mutex_unlock(&m);
    
    return NULL;
}
