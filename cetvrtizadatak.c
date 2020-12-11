/*4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se
èitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani. 

Sum i Multi

ZNACI IMAMO 3 SLUCAJA I JEDAN LUDI
a) eksponenti iz listi su jednaki
		onda zbrojimo koeficijente njihove
b) prvi eksponent je veci
	vatam veceg, zasad manjeg ignoriram
c) prvi eksponent je manji
	opet vatam veceg samo
d) tzv. LUDI SLUCAJ ako su 0, nema tog polinoma, idem dalje

Nisam zadovoljna izgledom.
Zelim smanjit main i koristit vise funkcija opcenito
moze ovo puno glade
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct polinom* position;
struct polinom {
	int coef;
	int pow;
	position next;
};

int DataFirst(position);
int DataSecond(position);
int PrintList(position);
int Sum(position, position, position);
int Multi(position, position, position);

int main() 
{
	
	struct polinom Head1;
	Head1.next = NULL;
	
	struct polinom Head2;
	Head2.next = NULL;
	
	struct polinom HeadSum;
	HeadSum.next = NULL;
	
	struct polinom HeadMulti;
	HeadMulti.next = NULL;

	DataFirst(&Head1);
	DataSecond(&Head2);
	
	printf("Prvi polinom:\n");
	PrintList(Head1.next);
	
	printf("Drugi polinom:\n");
	PrintList(Head2.next);
	
	Sum(&Head1, &Head2, &HeadSum);
	printf("Zbroj:\n");
	PrintList(HeadSum.next);
	
	Multi(&Head1, &Head2, &HeadMulti);
	printf("Umnozak:\n");
	PrintList(HeadMulti.next);
	
	return 0;
}

int DataFirst(position Pos)
{
	FILE* fp = NULL;
	fp = fopen("pol1.txt", "r");
	if (fp == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return 1;
	}
	
	while (!feof(fp))
	{
		position e = NULL;
		e = (position)malloc(sizeof(struct polinom));
		if (e == NULL)
		{
			printf("Neuspjesna alokacija memorije!\n");
			return 1;
		}
		position pret, temp;
		temp = Pos->next;
		pret = Pos;
		fscanf(fp, "%d %d", &e->coef, &e->pow);
		
		while (temp != NULL && temp->pow < e->pow)
		{
			pret = temp;
			temp = temp->next;
		}
		pret->next = e;
		if (temp != NULL)
			e->next = temp;
		else
			e->next = NULL;
	}
	return 0;
}


int DataSecond(position Pos)
{
	FILE* fp = NULL;
	fp = fopen("pol2.txt", "r");
	if (fp == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return 1;
	}
	while (!feof(fp))
	{
		position e = NULL;
		e = (position)malloc(sizeof(struct polinom));
		if (e == NULL)
		{
			printf("Neuspjesna alokacija memorije!\n");
			return 1;
		}
		position pret, temp;
		temp = Pos->next;
		pret = Pos;
		fscanf(fp, "%d %d", &e->coef, &e->pow);
		while (temp != NULL && temp->pow < e->pow)
		{
			pret = temp;
			temp = temp->next;
		}
		
		pret->next = e;
		if (temp != NULL)
			e->next = temp;
		else
			e->next = NULL;
	}
	
	return 0;
}

int PrintList(position Pos)
{
	while (Pos != NULL)
	{
		printf("coef je: %d pow je: %d\n", Pos->coef, Pos->pow);
		Pos = Pos->next;
	}
	return 0;
}

int Sum(position Pos, position e, position r)
{
	while (Pos->next != NULL && e->next != NULL)
	{
		position s = NULL;
		s = (position)malloc(sizeof(struct polinom));
		if (s == NULL)
		{
			printf("Neuspjesna alokacija memorije!\n");
			return 1;
		}
		s->next = NULL;

		if (Pos->next->pow < e->next->pow)
		{
			s->pow = Pos->next->pow;
			s->coef = Pos->next->coef;
			Pos = Pos->next;
		}
		else if (Pos->next->pow > e->next->pow)
		{
			s->pow = e->next->pow;
			s->coef = e->next->coef;
			e = e->next;
		}
		else
		{
			s->pow = Pos->next->pow;
			s->coef =(Pos->next->coef + e->next->coef);
			Pos = Pos->next;
			e = e->next;
		}
		r->next = s;
		r = s;
	}
	position temp;
	if (Pos->next == NULL)
		temp = e->next;
	else
		temp = Pos->next;
	while (temp != NULL)
	{
		position s = NULL;
		s = (position)malloc(sizeof(struct polinom));
		if (s == NULL)
		{
			printf("Neuspjesna alokacija memorije!\n");
			return 1;
		}
		s->next = NULL;
		s->pow = temp->pow;
		s->coef = temp->coef;
		r->next = s;
		r = s;
		temp = temp->next;
	}
	return 0;
}


int Multi(position Pos, position e, position r)
{
	position first = Pos->next;
	position second = e->next;
	struct polinom P;
	position s = NULL;
	s = (position)malloc(sizeof(struct polinom));
	if (s == NULL)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return 1;
	}
	s->next = NULL;
	P.next = s;
	while (first != NULL)
	{
		second = e->next;
		while (second != NULL)
		{

			s->coef = first->coef * second->coef;
			s->pow = first->pow + second->pow;

			Sum(&P, r, r);
			second = second->next;
		}
		first = first->next;
	}

	return 0;
}
