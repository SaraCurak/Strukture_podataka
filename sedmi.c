/*Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna
rezultat. Stog je potrebno realizirati preko vezane liste.

probati doma pomocu buffera i sscanf - puno krace i elegantnije nego fscanf
proguglati MEMSET

koristiti switch case ili if, ja cu if
prelazim po datoteci i ako naletim na znak vrsim 2 popa 
a u stog vracam rezultat
prolazi kroz sve i vidi je li operacija, na kraju jedan else 
znaci ako nije nijedna operacija, onda je broj
njega pamtim, odnosno stavljam na stog
sad imam problem moram string prebacit u int
za to cu iskoristit atoi funkciju, koja radi tocno sto meni treba

pop
push
printlist
data - on dozivljava datoteku postfix kao const char, pazi
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *position;

struct node
{
    int number;
    position next;
};

int Push(position *, int);
int Pop(position *);
int printList(position);
int Data(const char[], position *);

int main()
{

    position head = NULL;
    Data("postfix.txt", &head);
    printList(head);
    
	system("pause");
    return 0;
}

int Push(position *head_ref, int value)
{
    position Pos = *head_ref;

    Pos = (position)malloc(sizeof(struct node));

    if (Pos == NULL)
    {
        printf("Problem s alokacijom ");
        return -1;
    }

    Pos->number = value;
	Pos->next = *(head_ref);
    *(head_ref) = Pos;

    return 0;
}

int Pop(position *head_ref)
{
    position Pos = *head_ref;
    int value;

    *head_ref = Pos->next;
    value = Pos->number;

    free(Pos);

    return value;
}

int Data(const char postfix[], position *head_ref)
{
    FILE *fptr = NULL;
    int num;
    int num1, num2;
    int result;
    char operation[10];

    fptr = fopen(postfix, "r");

    if (fptr == NULL)
    {
        printf("Nije otvorilo datoteku ");
        return -1;
    }

    while (!feof(fptr))
    {

        fscanf(fptr, "%s ", operation);

        if (strcmp(operation, "+") == 0)
        {
            num1 = Pop(head_ref);
            num2 = Pop(head_ref);
			result = num2 + num1;

            Push(head_ref, result);
        }
        else if (strcmp(operation, "-") == 0)
        {
            num1 = Pop(head_ref);
            num2 = Pop(head_ref);
			result = num2 - num1;

            Push(head_ref, result);
        }
        else if (strcmp(operation, "*") == 0)
        {
            num1 = Pop(head_ref);
            num2 = Pop(head_ref);
			result = num2 * num1;

            Push(head_ref, result);
        }
        else if (strcmp(operation, "/") == 0)
        {
            num1 = Pop(head_ref);
            num2 = Pop(head_ref);
			result = num2 / num1;

            Push(head_ref, result);
        }
        else
        {
            num = atoi(operation);
			Push(head_ref, num);
        }
   
    }

    fclose(fptr);

    return 0;
}

int printList(position head)
{
    printf("%d", head->number);

    return 0;
}
