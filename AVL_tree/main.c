#include "header.h"

int main() {
	Node* t = NULL, z, * k, * treeForMove = NULL, * successor,*root;
	treeForMove = (Node*)malloc(sizeof(Node));
	int i = -1, b = 0;
	int choice = 0, deleteNode = 0, searchNode = 0;
	treeForMove = t;
	printf("Enter the tree that you want to build : ");
	int arr[28] = { 100,30,200,15,50,180,300,10,20,40,70,170,185,250,350,7,12,18,22,160,175,182,187,225,275,325,400,6 };
	//
	for (b = 0; b < 28; b++) {
		z.value = arr[b];
		InsertorDeleteNode(&t, INSERT, &z);
	}
	//while (i!=0) {
	//	scanf("%d", &i);
	//	z.value = i;
	//	if(i!=0)
	//	InsertorDeleteNode(&t, INSERT, &z);
	//	//*treeForMove = *t;
	//}
	treeForMove = t;
	while (choice != 12) {

		printf("Press 1 --------> Enter new Node\n");
		printf("Press 2 --------> Delete Node\n");
		printf("Press 3 --------> Search Node\n");
		printf("Press 4 --------> Find Maximum\n");
		printf("Press 5 --------> Find Minimum\n");
		printf("Press 6 --------> Find Successor\n");
		printf("Press 7 --------> Find Predecessor\n");
		printf("Press 8 --------> Move around the tree\n");
		printf("Press 9 --------> Go Left\n");
		printf("Press 10 --------> Go right\n");
		printf("Press 11 --------> Go father\n");
		printf("Press 12 --------> End\n");
		/*t = search(t, 12);
		InsertorDeleteNode(&t, DELETE, &z);
		t = search(t, 6);
		InsertorDeleteNode(&t, DELETE, &z);
		t = search(t, 10);
		InsertorDeleteNode(&t, DELETE, &z);
		t = search(t, 18);
		InsertorDeleteNode(&t, DELETE, &z);
		t = search(t, 7);
		InsertorDeleteNode(&t, DELETE, &z);
		t = search(t, 15);
		InsertorDeleteNode(&t, DELETE, &z);
		t = search(t, 22);
		InsertorDeleteNode(&t, DELETE, &z);
		t = search(t, 20);
		InsertorDeleteNode(&t, DELETE, &z);
		t = search(t, 70);
		InsertorDeleteNode(&t, DELETE, &z);
		moveAroundTheTree(t);*/
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			scanf("%d", &z.value);
			InsertorDeleteNode(&t, INSERT, &z);
			break;

		case 2:
			printf("Which Node you want to delete ? ");
			scanf("%d", &deleteNode);
			root = t;
			t = search(t, deleteNode);
			if (t != NULL)
				InsertorDeleteNode(&t, DELETE, &z);
			else
				t = root;
			//treeForMove = t;
			break;

		case 3:
			printf("Which Node to search ? ");
			scanf("%d", &searchNode);
			k = search(t, searchNode);
			if (k != NULL) {
				printf("%d Node found\n", searchNode);
				if (k->father == NULL)
					printf("Father = NULL\n");
				else
					printf("Father = %d\n", k->father->value);

				if (k->left == NULL)
					printf("Left = NULL\n");
				else
					printf("Left = %d\n", k->left->value);

				if (k->right == NULL)
					printf("Right = NULL\n");
				else
					printf("Right = %d\n", k->right->value);
			}
			break;

		case 4:
			printf("Maximum = %d\n", findMax(t)->value);
			break;

		case 5:
			printf("Minimum = %d\n", findMin(t)->value);
			break;


		case 6:
			if (treeForMove == findMax(t))
				printf("%d the Maximum\n", treeForMove->value);
			else {
				if (findSuccessor(treeForMove->right) == NULL)
					printf("Successor = %d\n", treeForMove->father->value);
				else
					printf("Successor = %d\n", findSuccessor(treeForMove->right)->value);
			}
			break;


		case 7:
			if (treeForMove == findMin(t))
				printf("%d the Minimum\n", treeForMove->value);
			else
				if (treeForMove->left == NULL)
					printf("Predecessor = %d\n", findPredecessor(treeForMove, UP)->value);
				else
					printf("Predecessor = %d\n", findPredecessor(treeForMove->left, DOWN)->value);
			break;


		case 8:
			moveAroundTheTree(t);
			break;


		case 9:
			if (treeForMove->left != NULL) {
				printf("Left = %d\n", treeForMove->left->value);
				treeForMove = treeForMove->left;
			}
			else
				printf("Left =NULL\n");
			break;

		case 10:
			if (treeForMove->right != NULL) {
				printf("Right = %d\n", treeForMove->right->value);
				treeForMove = treeForMove->right;
			}
			else
				printf("right =NULL\n");
			break;


		case 11:
			if (treeForMove->father != NULL) {
				printf("Father = %d\n", treeForMove->father->value);
				treeForMove = treeForMove->father;
			}
			else
				printf("Father = NULL\n");
			break;

		case 12:
			freeAll(&t);

		}
		
	}
}