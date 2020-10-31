/*

Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
a) dinamički dodaje novi element na početak liste,
b) ispisuje listu,
c) dinamički dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše određeni element iz liste,
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

*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX (32)

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
        default:
            printf("\nPogresan unos!");
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
    node* TempNodePrev= nullptr;
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
