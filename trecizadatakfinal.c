/*
Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
a) dinamièki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamièki dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.
MAX postavit ali 256 pari malo previse
2 structa, jedan da cuva podatke, jedan za unos
trebat ce neki izbornik, da korisnik bira sta zeli
switch case, switch po izboru u while petlji, 0 je izlaz
taj izbornik se treba otvarat nakon svakog unosa
postavit izbor na nesto sta nije 0,1,2,3,4,5
a) nac 1. el, alocirat prostor, unit podatak, postavit pokazivace, stavit da je taj novi sad head
b) ispis liste
c) na kraj malo, kompleksnije, nego pod a, while dok nije NULL
d) nac osobu po prezimenu proc po listi if i strcmp
 ako su dvi osobe istog prezimena NE RADI, vata prvu na koju naleti
 POPRAVIT
e) nije bitno samo tu osobu izbrisat nego i memoriju koju je zauzimala
  free ima na predavanju
Nisam bila na prve dvije vjezbe, tako da iskreno nije sve moje.
Kombinirala sam predavanja i internet, za neke stvari sto mi nisu padale na pamet.

Prethodnom zadatku dodati funkcije:
a) dinamièki dodaje novi element iza odreðenog elementa,
b) dinamièki dodaje novi element ispred odreðenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) èita listu iz datoteke.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (128)
#define MAX_ROW (128)


typedef struct _osoba
{
    char ime[MAX];
    char prezime[MAX];
    int godiste;
} osoba;

typedef struct _node
{
    osoba podatci;
    struct _node* next;
} node;

int DodajPocetak(node**);
int DodajKraj(node**);
int UnosPodataka(node*);
node* KreirajNode();
int PronalaziPrezime(node**);
int Ispis(node*);
int brisanje(node**);
int IspisiIzbornik();
int IspisiOsobu(node*);

int DodajIza(node**);
int DodajIspred(node**);
node* PronalaziPredhodnika(node**);
int UpisUdat(node**);
int CitajDat();
int sortiranje(node**);
int zamijeni(node*, node*);
int provjeraZamjene(node*);

int main()
{
    node* head = NULL;
    int izbor = -1;

    while (izbor != 0)
    {
        IspisiIzbornik();
        scanf("%d", &izbor);
        switch (izbor)
        {
        case 1:
            DodajPocetak(&head);
            break;
        case 2:
            DodajKraj(&head);
            break;
        case 3:
            brisanje(&head);
            break;
        case 4:
            PronalaziPrezime(&head);
            break;
        case 5:
            Ispis(head);
            break;
        case 6:
			DodajIza(&head);
			break;
		case 7:
			DodajIspred(&head);
			break;
		case 8:
		    UpisUdat(&head);
			break;
		case 9:
		    CitajDat();
		    break;
    case 10:
        sortiranje(&head);
        break;
        default:
            printf("\nPogresan unos!\n");
        }
    }

    return 0;
}

int UnosPodataka(node* Temp)
{
    printf("Unesi ime prezime godiste: ");
    scanf("%s %s %d", Temp->podatci.ime, Temp->podatci.prezime, &Temp->podatci.godiste);
    Temp->next = NULL;
    return 0;
}

node* KreirajNode()
{
    node* TempNode = (node*)malloc(sizeof(node));
    if (TempNode) {
        UnosPodataka(TempNode);
        return TempNode;
    }
    else {
        printf("Problem s alokacijom.");
        return NULL;
    }
}

int DodajPocetak(node** head)
{
    node* TempNode = KreirajNode();
    TempNode->next = (*head);
    (*head) = TempNode;
    return 0;
}

int DodajKraj(node** head)
{
    node* TempKraj = *head;

    node* TempNode = KreirajNode();

    if (*head == NULL) {
        *head = TempNode;
        return 0;
    }

    while (TempKraj->next != NULL)
    {
        TempKraj = TempKraj->next;
    }

    TempKraj->next = TempNode;
    return 0;
}

int Ispis(node* head)
{
    node* TempIspis = head;

    puts("\nISPIS\n ");

    while (TempIspis != NULL)
    {
        IspisiOsobu(TempIspis);
        TempIspis = TempIspis->next;
    }

    puts("\n ");

    return 0;
}


int PronalaziPrezime(node** head)
{
    node* TempNode = *head;
    char TempPrez[MAX];

    printf("\nUnesi trazeno prezime: ");
    scanf("%s", TempPrez);

    while (TempNode != NULL)
    {
        if (strcmp(TempNode->podatci.prezime, TempPrez) == 0) {
            IspisiOsobu(TempNode);
            return 0;
        }
        TempNode = TempNode->next;
    }

    printf("Ne postoji trazena osoba, unesite drugu.\n");
    return 0;
}

int brisanje(node** head)
{
    node* TempNode = *head;
    node* TempNodePrev= NULL;
    char TempPrez[MAX];

    if (TempNode == NULL) {
        printf("Lista je prazna.\n");
        return 0;
    }

    printf("\nBRISANJE\n\nUnesi prezime osobe: ");
    scanf("%s", TempPrez);

    if (strcmp(TempNode->podatci.prezime, TempPrez) == 0)
    {
        *head = TempNode->next;
        free(TempNode);
        return 0;
    }

    while (TempNode != NULL)
    {
        if (strcmp(TempNode->podatci.prezime, TempPrez) == 0) {
            TempNodePrev->next = TempNode->next;
            free(TempNode);
            return 0;
        }

        TempNodePrev = TempNode;
        TempNode = TempNode->next;
    }

    printf("Ne postoji trazena osoba, unesite drugu.\n");
    return 0;
}

int IspisiIzbornik()
{

    printf("1-Dodaj na pocetak liste\n");
    printf("2-Dodaj na kraj liste\n");
    printf("3-Brisanje osobe\n");
    printf("4-Pronalazak osobe\n");
    printf("5-Ispis liste\n\n");
    printf("6-Dodaj Iza\n");
    printf("7-DodajIspred\n");
	printf("8-Upis u datoteku\n");
  	printf("9-Iscitaj iz datoteke\n");
  	printf("10-Sortiraj po prezimenima\n");
    return 0;
}

int IspisiOsobu(node* Temp) {
    if (!Temp)
    {
        return -1;
    }
    printf("\n%s %s %d\n", Temp->podatci.ime, Temp->podatci.prezime, Temp->podatci.godiste);
    return 0;
}

int DodajIza(node** head)
{
	node* TempNode = *head;
	node* Temp;
	char TempPrez[MAX];

	printf("\nUnesi trazeno prezime: ");
	scanf("%s", TempPrez);

	while (TempNode != NULL)
	{
		if (strcmp(TempNode->podatci.prezime, TempPrez) == 0) {

			Temp = KreirajNode();
			Temp->next = TempNode->next;
			TempNode->next = Temp;
			return 0;
		}
		TempNode = TempNode->next;
	}

	printf("Ne postoji trazena osoba, unesite drugu.\n");
	return 0;
}

node* PronalaziPredhodnika(node** head)
{
    node* TempNode = *head;
	node* TempNodePrev;
	char TempPrez[MAX];

	if (TempNode == NULL) {
		printf("Lista je prazna.\n");
		return 0;
	}

	printf("\nUnesi prezime trazene osobe: ");
	scanf("%s",TempPrez);

    if (strcmp(TempNode->podatci.prezime, TempPrez) == 0)
	{
		return NULL;
	}

    while (TempNode != NULL)
	{
		if (strcmp(TempNode->podatci.prezime, TempPrez) == 0) {
		    printf("\n%s %s %d\n",TempNodePrev->podatci.ime,TempNodePrev->podatci.prezime,TempNodePrev->podatci.godiste);
			return TempNodePrev;
		}
		TempNodePrev = TempNode;
		TempNode = TempNode->next;
	}
	printf("Ne postoji trazena osoba.\n");
	return 0;
}

int DodajIspred(node** head)
{
    node* TempNode;
    node* Temp;

    TempNode=PronalaziPredhodnika(head);

    if(TempNode==NULL)
    {
        DodajPocetak(head);
        return 0;
    }
    else
    {
        Temp = KreirajNode();
        Temp->next=TempNode->next;
        TempNode->next=Temp;
        return 0;
    }
}

int UpisUdat(node** head)
{
    node* TempNode=*head;
    FILE *ulz;
    if(ulz == NULL)
    {
        printf("\nGreska 0tvaranja datoteke\n");
        return 0;
    }

    ulz=fopen("treci.txt","a");

    while(TempNode!=NULL)
    {
        fprintf(ulz,"%s %s %d\n",TempNode->podatci.ime,TempNode->podatci.prezime,TempNode->podatci.godiste);
        TempNode=TempNode->next;
    }
    fclose(ulz);
    printf("\nOsobe upisane!\n");
    return 0;
}

int CitajDat()
{
    FILE *ilz;
    char row[MAX_ROW];

    if(ilz == NULL)
    {
        printf("\nGreska otvaranja datoteke\n");
        return 0;
    }

    ilz = fopen("treci.txt","r");

    while( fgets(row, 100, ilz) )
    {
        printf("%s",row);
    }
    fclose(ilz);
    return 0;
}

int sortiranje(node** head) {
  int zamijenjen = 1;
  node *temp;
  node *najveciTemp = NULL;

  if (*head == NULL) {
      printf("Lista prazna.\n");
      return 1;
  }

  while (zamijenjen) {
    temp = *head;
    zamijenjen = 0;

    while (temp->next != najveciTemp)
      {
          zamijenjen = provjeraZamjene(temp);
          temp = temp->next;
      }

      najveciTemp = temp;

  }

  printf("Lista je sortirana.\n");
  return 0;
}

int provjeraZamjene (node* temp) {
  if ( strcmp(temp->podatci.prezime, temp->next->podatci.prezime) > 0 )
  {
    zamijeni(temp, temp->next);
    return 1;
  }
  else {
    return 0;
  }
}

int zamijeni(node* a, node * b)
{
  osoba temp = a->podatci;
  a->podatci = b->podatci;
  b->podatci = temp;
}

