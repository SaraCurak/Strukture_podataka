/*9. Napisati program koji omoguæava rad s binarnim stablom pretraživanja. Treba
omoguæiti unošenje novog elementa u stablo, Print elemenata, brisanje i pronalaženje
nekog elementa.

uredit napravit switch case da moze po zelji, a ne sve odjednom
unos smislit malo drugacije

ili livo min ili d max

sluc za 1 i 0 djece
sluc za 2 djece

*/


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct stablo* Pos;
struct stablo {
	int el;
	Pos d;
	Pos l;
};

Pos Insert(int, Pos);
Pos Find(int, Pos);
Pos Previous(int, Pos, Pos);
void Print(Pos);
Pos Delete(int, Pos);
Pos Min(root);

int main() {
	Pos root = NULL;

	root = Insert(7, root);
	root = Insert(4, root);
	root = Insert(9, root);
	root = Insert(3, root);

	Print(root);
	puts("");

	Find(3, root);

	Delete(4, root);

	Print(root);
	puts("");

	system("pause");
	return 0;
}

Pos Insert(int x, Pos root) {
	if (NULL == root) {
		root = (Pos)malloc(sizeof(struct stablo));
		root->el = x;
		root->d = NULL;
		root->l = NULL;
	}
	else {
		if (x < root->el)
			root->l = Insert(x, root->l);
		else
			root->d = Insert(x, root->d);
	}
	return root;
}

Pos Find(int x, Pos root) {
	if (root == NULL)
		return NULL;
	if (root->el == x) {
		printf("Nasao sam %d\n", root->el);
		return root;
	}
	else if (x < root->el)
		return Find(x, root->l);
	else if (x > root->el)
		return Find(x, root->d);
}

Pos Previous(int x, Pos root, Pos prev) {
	if (root == NULL)
		return NULL;
	if (root->el == x) {
		return prev;
	}
	else if (x < root->el)
		return Previous(x, root->l, root);
	else if (x > root->el)
		return Previous(x, root->d, root);
}

void Print(Pos root) {
	if (root != NULL) {
		Print(root->l);
		printf("%d", root->el);
		Print(root->d);
	}
}

Pos Min(Pos root) {
	if (root->l != NULL) {
		return Min(root->l);
	}
	return root;
}

Pos Delete(int a, Pos root) {
	Pos pret = Previous(a, root, root);
	
	Pos min, temp;
	if (root == NULL)
		printf("nema elementa kojeg trazite \n");
	else if (a < root->el)
		root->l = Delete(a, root->l);
	else if (a > root->el)
		root->d = Delete(a, root->d);
	else {
		if (root->d != NULL && root->l != NULL) {
		
			temp = Min(root->d);
			root->el = temp->el;
			root->d = Delete(root->el, root->d);
		}
		else {
			
			temp = root;
			if (root->d == NULL)
				root = root->l;
			else if (root->l == NULL)
				root = root->d;
			free(temp);
		}
	}
	return root;
}