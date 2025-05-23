#include <stdio.h>
#include <string.h>
#include "datoteke.h"
#include "disk.h"

//neka u simulaciji (radi jednostavnosti) datotečna tablica bude u memoriji
static struct opisnik datotecna_tablica[MAX_DATOTEKA];

//slobodni blokovi na disku
static char slobodni_blokovi[BLOCKS];

void inicijaliziraj_prazni_disk()
{
	int i, j;

	memset(datotecna_tablica, 0, sizeof(struct opisnik) * MAX_DATOTEKA);
	for (i = 0; i < MAX_DATOTEKA; i++) {
		datotecna_tablica[i].kazaljka = -1;
		for (j = 0; j < BLOCKS; j++)
			datotecna_tablica[i].blokovi[j] = -1;
	}
	memset(slobodni_blokovi, 0, BLOCKS);
}
int otvori_datoteku(char *ime, int nacin)
{
	int i, slobodni_opisnik = -1;
	if (nacin != ZA_CITANJE && nacin != ZA_PISANJE) {
		fprintf(stderr, "'nacin' mora biti ZA_CITANJE ili ZA_PISANJE!\n");
		return -1;
	}
	for (i = 0; i < MAX_DATOTEKA; i++)
		if (datotecna_tablica[i].ime[0] == 0)
			slobodni_opisnik = i;
		else if (!strncmp(datotecna_tablica[i].ime, ime, IME_DULJINA))
			break;
	if (i < MAX_DATOTEKA) { //postoji, otvori je kako je zadano
		if (datotecna_tablica[i].kazaljka > -1) {
			fprintf(stderr, "Datoteka je vec otvorena!\n");
			return -1;
		}
		datotecna_tablica[i].kazaljka = 0;
		datotecna_tablica[i].nacin_rada = nacin;
		return i;
	}
	else if (nacin == ZA_CITANJE) {
		fprintf(stderr, "Datoteka ne postoji, ne moze se citati!\n");
		return -1;
	}
	else { //nacin == ZA_PISANJE
		if (slobodni_opisnik >= 0) {
			fprintf(stdout, "Datoteka ne postoji, stvaram novu!\n");
			i = slobodni_opisnik;
			strncpy(datotecna_tablica[i].ime, ime, IME_DULJINA);
			datotecna_tablica[i].velicina = 0;
			datotecna_tablica[i].kazaljka = 0;
			datotecna_tablica[i].nacin_rada = nacin;
			//ne treba inicijalizirati "blokove"
			return i;
		}
		else {
			fprintf(stderr, "Nema mjesta za novu datoteku\n");
			return -1;
		}
	}
	return i; //ne bi trebao nikada doci do tu...
}
int zatvori_datoteku(int id)
{
	datotecna_tablica[id].kazaljka = -1;

	return 0;
}

int procitaj(int id, void *p, size_t koliko)
{
	char buffer[BLOCK_SIZE];

	if (id < 0 || id >= MAX_DATOTEKA ||
		datotecna_tablica[id].ime[0] == 0 ||
		datotecna_tablica[id].kazaljka == -1)
	{
		fprintf(stderr, "Krivi id\n");
		return -1;
	}

	size_t blok_datoteke = datotecna_tablica[id].kazaljka / BLOCK_SIZE;
	size_t blok_diska = datotecna_tablica[id].blokovi[blok_datoteke];
	size_t jos = koliko;

    while(jos > 0 && datotecna_tablica[id].kazaljka < datotecna_tablica[id].velicina && blok_diska >= 0)
    {
		dohvati_blok(blok_diska, buffer);
		size_t kopirati;
		/* kopirati = min(još, dat.veličina - dat.kazaljka,
		VEL_BLOKA - dat.kazaljka % VEL_BLOKA)*/
		
		if(jos < (datotecna_tablica[id].velicina - datotecna_tablica[id].kazaljka))
		{
			if((BLOCK_SIZE - datotecna_tablica[id].kazaljka % BLOCK_SIZE) < jos)
				kopirati = BLOCK_SIZE - datotecna_tablica[id].kazaljka % BLOCK_SIZE;
			else
				kopirati = jos;
        }
        else
		{
			if((BLOCK_SIZE - datotecna_tablica[id].kazaljka % BLOCK_SIZE) < (datotecna_tablica[id].velicina - datotecna_tablica[id].kazaljka))
				kopirati = BLOCK_SIZE - datotecna_tablica[id].kazaljka % BLOCK_SIZE;
			else
				kopirati = datotecna_tablica[id].velicina - datotecna_tablica[id].kazaljka;
		}

		memcpy(p, buffer + datotecna_tablica[id].kazaljka % BLOCK_SIZE, kopirati);

		p =(char*)p + kopirati;
		datotecna_tablica[id].kazaljka += kopirati;
		jos -= kopirati;
		blok_datoteke++;
		blok_diska = datotecna_tablica[id].blokovi[blok_datoteke];
	}
	return koliko - jos;
}

int zapisi(int id, void *p, size_t koliko)
{
	char buffer[BLOCK_SIZE];

	if (id < 0 || id >= MAX_DATOTEKA ||
		datotecna_tablica[id].ime[0] == 0 ||
		datotecna_tablica[id].kazaljka == -1)
	{
		fprintf(stderr, "Krivi id\n");
		return -1;
	}
	size_t blok_datoteke = datotecna_tablica[id].kazaljka / BLOCK_SIZE;
	//size_t blok_diska = datotecna_tablica[id].blokovi[blok_datoteke];
	size_t jos = koliko;
	size_t max_vel_datoteke = BLOCK_SIZE * BLOCKS;

	while(jos > 0 && datotecna_tablica[id].kazaljka < max_vel_datoteke)
	{
		if(datotecna_tablica[id].blokovi[blok_datoteke] == -1)
		{
			int slobodni = 1;
			for(int i = 0; i < BLOCKS; i++)
			{
				if(slobodni_blokovi[i] == 0)
				{
					slobodni_blokovi[i] = 1;
					datotecna_tablica[id].blokovi[blok_datoteke] = i;
					slobodni = 0;
					break;
				}
			}
			if(slobodni == 1)
			{
				break;
			}
		}

		dohvati_blok(datotecna_tablica[id].blokovi[blok_datoteke], buffer);
		size_t kopirati;
		/* kopirati = min(još, VEL_BLOKA - dat.kazaljka % VEL_BLOKA) */
		if(jos < BLOCK_SIZE - datotecna_tablica[id].kazaljka % BLOCK_SIZE)
		{
			kopirati = jos;
        }
		else
		{
			kopirati =  BLOCK_SIZE - datotecna_tablica[id].kazaljka % BLOCK_SIZE;
		}
		memcpy(buffer + datotecna_tablica[id].kazaljka % BLOCK_SIZE, p, kopirati);

        pohrani_blok(datotecna_tablica[id].blokovi[blok_datoteke], buffer);
		
		p = (char*)p + kopirati;
		datotecna_tablica[id].kazaljka += kopirati;
		jos -= kopirati;
		blok_datoteke++;
    }
	/* dat.veličina = max(dat.kazaljka, prethodna veličina datoteke) */
	if(datotecna_tablica[id].velicina < datotecna_tablica[id].kazaljka)
	{
		datotecna_tablica[id].velicina = datotecna_tablica[id].kazaljka;
	}

	return koliko - jos;;
}