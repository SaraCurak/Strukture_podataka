/*Napisati program koji prvo proèita koliko redaka ima datoteka, tj.koliko ima studenata
zapisanih u datoteci.Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata(ime, prezime, bodovi) i uèitati iz datoteke sve zapise.Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relativan_br_bodova = br_bodova / max_br_bodova * 100 


u svakoj funkciji staviti printf - lakse pracenje gresaka
napraviti datoteku s nekoliko ucenika i bodova (ime prezime bod)
nakon rada u datoteci staviti rewind(fp) da znamo da je na pocetku
zgodno MAX_NAME ograiciti 
napraviti funkciju za brojanje redaka u dat
napraviti funkciju unos
napraviti funkciju ispis
pazi define i include sve ukljucit
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include <malloc.h>
#define ERR (-1)
#define MAX_NAME 256

typedef struct _stud
{
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int bodovi;
}student;

int BrojanjeRedaka();
int Unos(student*, int);
int Ispis(student*, int);

int main() {

	student* a = NULL;
	int br, pom_unos, pom_ispis;
	br = BrojanjeRedaka();

	if (br == ERR)
		printf("Datoteka nije otvorena! \n");

	printf("Broj redaka je: %d\n", br);

	a = (student*)malloc(br * sizeof(student));

	if (a == NULL)
		printf("Alokacija neispravna");

	pom_unos = Unos(a, br);

	if (pom_unos == ERR)
		printf("Datoteka nije otvorena \n");

	pom_ispis = Ispis(a, br);

	if (pom_ispis != 0)
		printf("Ispis neispravan");

	free(a);

	return 0;

}

int BrojanjeRedaka() {

	FILE* fp = fopen("student.txt", "r");
	int brojac = 0;

	if (fp == NULL)
	{
		printf("Ne radi");
		return ERR;
	}
	rewind(fp);

	while (!feof(fp))
	{
		fscanf(fp, "%*s %*s %*d");
		brojac++;
	}
	fclose(fp);

	return brojac;

}

int Unos(student* a, int br) {

	int i;

	FILE* fp = fopen("student.txt", "r");
	int brojac = 0;

	if (fp == NULL)
	{
		printf("Ne radi unos u dat \n");
		return ERR;
	}
	rewind(fp);

	for (i = 0; i < br; i++)
		fscanf(fp, "%s %s %d", a[i].ime, a[i].prezime, &a[i].bodovi);

	fclose(fp);

	return 0;
}

int Ispis(student* a, int br) {
	int i;

	for (i = 0; i < br; i++)
		printf("%s %s %d %.2f\n", a[i].ime, a[i].prezime, a[i].bodovi, ((double)a[i].bodovi/50)*100);

	return 0;
}
