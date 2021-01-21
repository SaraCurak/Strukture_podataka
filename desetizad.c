/*10. Napisati program koji iz datoteke èita postfiks izraz i zatim stvara stablo proraèuna. Iz
gotovog stabla proraèuna upisati u datoteku infiks izraz.

prvo radit funkcije, a zadnje se bavit citanjem iz datoteke

*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#define SIZE (11)
#define MAX_NAME (1024)

struct _treeNode;
typedef struct _treeNode* PositionT;
typedef struct _treeNode {
	PositionT left;
	PositionT right;
	char data[SIZE];
}TreeNode;

struct _listNode;
typedef struct _listNode* PositionL;
typedef struct _listNode {
	PositionL next;
	PositionT treeNode;
}ListNode;

int main(void) {

	PositionT root = NULL;
	char filename[MAX_NAME] = { 0 };

	printf("umetnite naziv datoteke: ");
	scanf("%s", filename);

	root = readFromFile(filename);
	printInOrder(root);
	return EXIT_SUCCESS;
}

PositionT createNode(char* data);
int pushFront(PositionL head, PositionT treeNode);
PositionT popFront(PositionL head);
PositionT readFromFile(char* filename);
int isNumber(char* str);
void printInOrder(PositionT current);

void printInOrder(PositionT current) {
	if (NULL == current)
		return;

	printf("(");
	printInOrder(current->left);
	printf("%s", current->data);
	printInOrder(current->right);
	printf(")");
}
PositionT createNode(char* data) {
	PositionT node = NULL;

	node = (PositionT)malloc(sizeof(TreeNode));

	if (!node) {
		printf("Problem u alokaciji ");
		return NULL;
	}

	strcpy(node->data, data);
	node->data;
}

int pushFront(PositionL head, PositionT treeNode) {

	PositionL node = NULL;

	node = (PositionL)malloc(sizeof(ListNode));

	if (!node) {
		printf("Problem u alokaciji ");
		return -1;
	}
	node->treeNode = treeNode;
	node->next = head->next;
	head->next = node;

	return 0;
}

PositionT popFront(PositionL head) {
	PositionL first = head->next;
	PositionT result = NULL;

	if (!first) {
		return NULL;
	}

	head->next = first->next;
	result = first->treeNode;
	free(first);

	return result;

}

PositionT readFromFile(char* filename) {
	ListNode head;
	FILE* fp = NULL;

	head.next = NULL;

	fp = fopen(filename, "r");

	if (!fp) {
		printf("datoteka %s ne postoji ili nemate pristup ", filename);
		return NULL;
	}

	while (!feof(fp)) {
		char data[SIZE] = { 0 };
		PositionT node = NULL;

		fscanf(fp, " %s ", data);

		if (strlen(data) == 0) {
			break;
		}
		node = createNode(data);

		if (!node) {
			fclose(fp);
			return NULL;
		}

		if (isNumber(data)) {
			pushFront(&head, node);
		}

		else{
			node->right = popFront(&head);

			if (!node->right) {

				printf("Postfiks %s nije ispravan ", filename);
				fclose(fp);
				return NULL;

			node->left = popFront(&head);

				if (!node->left) {

					printf("Postfiks %s nije ispravan ", filename);
					fclose(fp);
					return NULL;
				}
				pushFront(&head, node);
			}
			}
		fclose(fp);

		result = popFront(&head);

		if(!result){
			printf("Prazna datoteka %s ", filename);
			return NULL;
		}


		if(popFront(&head) != NULL){
			printf("Postfiks %s nije ispravan ", filename);
			fclose(fp);
			return NULL;
		}

		return result;
	}
}

int isNumber(char* str) {
	int number = 0;

	if (scanf(str, "%d", &number) == 1)
		return 1;

	return 0;
}