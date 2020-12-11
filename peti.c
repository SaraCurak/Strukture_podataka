/*. Za dvije sortirane liste L1 i L2 (mogu se proèitati iz datoteke ili unijeti ruèno, bitno je
samo da su sortirane), napisati program koji stvara novu vezanu listu tako da raèuna:
a) L1?L2,
b) L1?L2.
Liste osim pokazivaèa na slijedeæu strukturu imaju i jedan cjelobrojni element, po
kojem su sortirane.

u uniji neki problemcic, smece nakon nje
bolje unos preko funkcije, nego ovako
uredit!
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node *position;
struct node {
	int  data;
	position next;
};

void InsertionSort(int elem, position Pos);

void PrintList(position Pos);

void DataEntry(int elem, position Pos);

void Union(position L1, position L2, position Pos);

void Intersection(position L1, position L2, position Pos);

int main()
{
	int n=0, m=0, i;
	
	struct node head1;
	head1.next = NULL;	
	
	struct node head2;
	head2.next = NULL;

	struct node headU;
	headU.next = NULL;

	struct node headI;
	headI.next = NULL;


	printf("Koliko clanova u prvoj listi:  ");
	scanf("%d",&n);

	printf("Unesi brojeve:");
	for (i=0; i<n;i++)
	{   int br1;
		scanf("%d",&br1);
 		InsertionSort(br1,&head1);
	}

	printf("Koliko clanova u drugoj listi: ");
	scanf("%d",&m);

	printf("Unesi brojeve: \n");
	for (i=0; i<m;i++)
	{   int br2;
		scanf("%d",&br2);
 		InsertionSort(br2,&head2);
	}	

	printf("\nUnija: ");
	Union(&head1, &head2, &headU);
	PrintList(headU.next);

	printf("\nPresjek: ");
	Intersection(&head1, &head2, &headI);
	PrintList(headI.next);

	system("pause");
	return 0;
}

void InsertionSort(int elem, position Pos) {
	position e;
	while (Pos->next != NULL && Pos->next->data < elem)
				Pos = Pos->next;
				
	e = (position)malloc(sizeof(struct node));

	e->data = elem;
	e->next = Pos->next;
	Pos->next = e;

}

void DataEntry(int elem, position Pos) {
	position e;
	e = (position)malloc(sizeof(struct node));
	e->data = elem;
	e->next = Pos->next;
	Pos->next = e;
}

void PrintList(position Pos) {
	while (Pos != NULL) {
		printf("%d ", Pos->data);
		Pos = Pos->next; 
	}
}

void Union(position L1, position L2, position U) {
	position temp;
	
	while (L1 != NULL && L2 != NULL) {
		if (L1->data < L2->data) {
			DataEntry(L1->data, U);
			L1 = L1->next;
		}
		else if (L1->data > L2->data) {
			DataEntry(L2->data, U);
			L2 = L2->next;	
		}

		else {
			DataEntry(L1->data, U);
			L1 = L1->next;
			L2 = L2->next; 
		}
	}
	if (L1 != NULL) temp = L1;
	else temp = L2;
	while (temp != NULL) {
		DataEntry(temp->data, U);
		temp = temp->next;
	}
}

void Intersection(position L1, position L2, position Pos) {
	while (L1 != NULL && L2 != NULL) {
		if (L1->data < L2->data)
			L1 = L1->next;
		else if (L1->data > L2->data)
			L2 = L2->next;
		else {
			DataEntry(L1->data, Pos);
			L1 = L1->next;
			L2 = L2->next;
		}
	}

}
