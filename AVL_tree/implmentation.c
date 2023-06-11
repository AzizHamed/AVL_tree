#include "header.h"

/// <summary>
/// This is a method that insert a new Node.
/// </summary>
/// <param name="t"> Node**.</param>
/// <param name="z">Node *.</param>
/// <returns> Inserts the Node to the tree.</returns>
/// 
void Insert(Node** t, Node* z) {

	//if the tree is NULL
	if ((*t) == NULL) {
		initNewNode(t, z, NULL, NULL, NULL, ROOT);
		return;
	}

	// if the Inserted value is greater than the Node value
	if ((*t)->value > z->value) {
		if ((*t)->left != NULL) {
			Insert(&((*t)->left), z);
			(*t)->leftTreeHeight = max((*t)->left->leftTreeHeight, (*t)->left->rightTreeHeight) + 1;
			(*t)->newBF = (*t)->leftTreeHeight - (*t)->rightTreeHeight;
		}
		else
			initNewNode(t, z, *t, NULL, NULL, LEFT);


	}
	// if the Inserted value is smaller than the Node value
	else {
		if ((*t)->right != NULL) {
			Insert(&((*t)->right), z);
			(*t)->rightTreeHeight = max((*t)->right->leftTreeHeight, (*t)->right->rightTreeHeight) + 1;
			(*t)->newBF = (*t)->leftTreeHeight - (*t)->rightTreeHeight;
		}
		else
			initNewNode(t, z, *t, NULL, NULL, RIGHT);


	}
}


/// <summary>
/// This is a method that sends Parameters to the function that deletes the node .
/// </summary>
/// <param name="x"> Node**.</param>
/// <returns> The father of the deleted Node .</returns>
/// 
Node* Delete(Node** x) {
	Node* deleteNode;
	deleteNode = *x;
	if ((*x) == NULL)
		return;
	//Delete Node
	return DeleteNode(x, (*x)->father);
}


/// <summary>
/// This is a method that updates the pointer of the father after the delete and updates the height of left tree and right tree.
/// </summary>
/// <param name="t"> Node**.</param>
/// <param name="x">Node *.</param>
/// <returns> Only update.</returns>
/// 
void checkAndUpdateFather(Node** t, Node* x) {
	if ((*t)->father != NULL)
		if ((*t)->father->left == (*t)) {
			(*t)->father->left = x;
			(*t)->father->leftTreeHeight--;
		}
		else {
			(*t)->father->right = x;
			(*t)->father->rightTreeHeight--;
		}
}


/// <summary>
/// This is a method that delete the given node.
/// </summary>
/// <param name="t"> Node**.</param>
/// <param name="father">Node *.</param>
/// <returns> The father of the deleted node.</returns>
/// 
Node* DeleteNode(Node** t, Node* father) {
	Node* successor, * nodefordelete;
	if ((*t)->left == NULL && (*t)->right == NULL) {
		checkAndUpdateFather(t, NULL);
		nodefordelete = *t;
		(*t) = (*t)->father;
		free(nodefordelete);
	}
	//if the root has 1 child
	else
		if ((*t)->left == NULL && (*t)->right != NULL) {
			(*t)->right->father = (*t)->father;
			checkAndUpdateFather(t, (*t)->right);
			nodefordelete = *t;
			(*t) = (*t)->father;
			free(nodefordelete);
		}
		else
			if ((*t)->left != NULL && (*t)->right == NULL) {
				(*t)->left->father = (*t)->father;
				checkAndUpdateFather(t, (*t)->left);
				nodefordelete = *t;
				(*t) = (*t)->father;
				free(nodefordelete);
			}
	//if t has 2 childs
			else
				BuildSuccessor(t, father);

	return (*t);

}

/// <summary>
/// This is a method builds the successor of the node that we want to delete, the successor is in the tree but this generate a new one with updated pointers and heights.
/// </summary>
/// <param name="t"> Node**.</param>
/// <param name="father">Node *.</param>
/// <returns> Builds the successor and free the old one.</returns>
/// 
void BuildSuccessor(Node** t, Node* father) {
	Node* successor;

	successor = findSuccessor((*t)->right);
	successor->left = (*t)->left;

	if (successor == (*t)->right)
		successor->right = NULL;
	else
		successor->right = (*t)->right;

	if (successor->father->left == successor)
		successor->father->left = NULL;
	else
		successor->father->right = NULL;
	successor->father = (*t)->father;

	(**t) = *successor;

	if (father != NULL && father->left == (*t))
		(*t)->father->left = (*t);
	if (father != NULL && father->right == (*t))
		(*t)->father->right = (*t);
	free(successor);
}

/// <summary>
/// This is a method that find a successor of specific node.
/// </summary>
/// <param name="x"> Node*.</param>
/// <returns> The successor.</returns>
/// 
Node* findSuccessor(Node* x) {
	if (x == NULL)
		return NULL;
	if (x->left == NULL)
		return x;
	return findSuccessor(x->left);
}


/// <summary>
/// This is a method that find a predecessor of specific node.
/// </summary>
/// <param name="x"> Node**.</param>
/// <param name="whereToSearch">int.</param>
/// <returns> Returns the Predecessor .</returns>
/// 
Node* findPredecessor(Node* x, int whereToSearch) {
	if (x == NULL)
		return;
	if (whereToSearch == DOWN) {
		if (x->right == NULL)
			return x;
		return findPredecessor(x->right, whereToSearch);
	}
	else {
		if (x->father->right == x)
			return x->father;
		return findPredecessor(x->father, whereToSearch);
	}
}

/// <summary>
/// This is a method that find the maximum in the tree.
/// </summary>
/// <param name="x"> Node*.</param>
/// <returns> Returns the maximum .</returns>
/// 
Node* findMax(Node* x) {
	if (x == NULL)
		return;
	if (x->right == NULL)
		return x;
	return findMax(x->right);
}

/// <summary>
/// This is a method that find the minimum in the tree.
/// </summary>
/// <param name="x"> Node*.</param>
/// <returns> Returns the minimum .</returns>
/// 
Node* findMin(Node* x) {
	if (x == NULL)
		return;
	if (x->left == NULL)
		return x;
	return findMin(x->left);
}

/// <summary>
/// This is a method that search on a node around the tree.
/// </summary>
/// <param name="t"> Node*.</param>
/// <param name="NodeForSearch"> int.</param>
/// <returns> Returns the wanted node if found .</returns>
/// 
Node* search(Node* t, int NodeForSearch) {
	if (t == NULL) {
		printf("Node not found!\n");
		return NULL;
	}
	if (t->value > NodeForSearch)
		return  search(t->left, NodeForSearch);
	if (t->value < NodeForSearch)
		return search(t->right, NodeForSearch);
	return t;
}


/// <summary>
/// This is a method that inits the new node parameters and insert it in the tree.
/// </summary>
/// <param name="t"> Node*.</param>
/// <param name="z"> Node*.</param>
/// <param name="father"> Node*.</param>
/// <param name="left"> Node*.</param>
/// <param name="right"> Node*.</param>
/// <param name="side"> int.</param>
/// <returns> Insert the node .</returns>
/// 
void initNewNode(Node** t, Node* z, Node* father, Node* left, Node* right, int side) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	CheckMalloc(newNode);
	newNode->left = left;
	newNode->right = right;
	newNode->father = father;
	newNode->value = z->value;
	newNode->BF = 0;
	newNode->newBF = 0;
	newNode->leftTreeHeight = 0;
	newNode->rightTreeHeight = 0;
	if (side == LEFT) {
		(*t)->left = newNode;
		nodeForRoll1 = (*t)->left;
		nodeForRoll = *t;
		(*t)->leftTreeHeight++;
		(*t)->newBF++;
	}
	if (side == RIGHT) {
		(*t)->right = newNode;
		nodeForRoll1 = (*t)->right;
		nodeForRoll = *t;
		(*t)->rightTreeHeight++;
		(*t)->newBF--;
	}
	if (side == ROOT) {
		(*t) = newNode;
		nodeForRoll1 = NULL;
		nodeForRoll = NULL;
	}

}

/// <summary>
/// This is a method that decide if we have to do rotate or not.
/// </summary>
/// <param name="x"> Node**.</param>
/// <param name="p"> int.</param>
/// <returns> Returns the lowest node after the rotation or null if we don't rotate .</returns>
/// 
Node* rotate(Node** x, int p) {
	Node** k;
	if ((*x) == NULL) {
		return NULL;
	}
	if ((*x)->father == NULL && (*x)->BF == (*x)->newBF)
		return NULL;

	//if the BF[y] < 2 and his height does not changed
	if ((*x)->newBF == (*x)->BF)
		return NULL;

	if ((*x)->newBF != (*x)->BF && abs((*x)->newBF) < 2)
		return p == INSERT ? rotate(&(*x)->father, INSERT ) : rotate(&(*x)->father, DELETE);

	if (abs((*x)->newBF) == 2) {
		chooseRoll(x, p);
	}

	return *x;

}

/// <summary>
/// This is a method that choose the rotation kind (LL,LR,RL,RR).
/// </summary>
/// <param name="x"> Node**.</param>
/// <param name="p"> int.</param>
/// <returns> only choose the rotation .</returns>
/// 
void chooseRoll(Node** x, int p) {
	if (p == INSERT) {
		//LL rotate
		if ((*x)->newBF == 2 && (*x)->left->newBF == 1)
			makeLLRotate(x);

		//LR rotate
		if ((*x)->newBF == 2 && (*x)->left->newBF == -1)
			makeLRRotate(x);

		//RL rotate
		if ((*x)->newBF == -2 && (*x)->right->newBF == 1)
			makeRLRotate(x);

		//RR rotate
		if ((*x)->newBF == -2 && (*x)->right->newBF == -1)
			makeRRRotate(x);
	}
	if (p == DELETE) {

		//LL rotate
		if ((*x)->newBF == 2 && ((*x)->left->newBF == 1 || (*x)->left->newBF == 0))
			makeLLRotate(x);

		//LR rotate
		if ((*x)->newBF == 2 && (*x)->left->newBF == -1)
			makeLRRotate(x);

		//RL rotate
		if ((*x)->newBF == -2 && (*x)->right->newBF == 1)
			makeRLRotate(x);

		//RR rotate
		if ((*x)->newBF == -2 && ((*x)->right->newBF == -1 || (*x)->right->newBF == 0))
			makeRRRotate(x);
	}
}

/// <summary>
/// This is a method that make RR rotation and update the heights of the left and right trees for the suitable nodes.
/// </summary>
/// <param name="x"> Node**.</param>
/// <returns> Make the rotation .</returns>
/// 
void makeRRRotate(Node** x) {
	Node* newA = (Node*)malloc(sizeof(Node));
	CheckMalloc(newA);
	Node* newB = (Node*)malloc(sizeof(Node));
	CheckMalloc(newB);
	Node* deleteNode;

	//set new nodes parameters
	newA->left = (*x)->left;
	newA->right = (*x)->right->left;
	newA->father = newB;
	newA->value = (*x)->value;

	newA->leftTreeHeight = (*x)->leftTreeHeight;
	newA->rightTreeHeight = (*x)->right->leftTreeHeight;
	newA->BF = newA->leftTreeHeight - newA->rightTreeHeight;
	newA->newBF = newA->BF;

	newB->leftTreeHeight = max(newA->leftTreeHeight, newA->rightTreeHeight) + 1;
	newB->rightTreeHeight = (*x)->right->rightTreeHeight;
	newB->BF = newB->leftTreeHeight - newB->rightTreeHeight;
	newB->newBF = newB->BF;

	newB->left = newA;
	newB->right = (*x)->right->right;
	newB->father = (*x)->father;
	newB->value = (*x)->right->value;

	if (newA->right != NULL)
		newA->right->father = newA;

	if (newA->left != NULL)
		newA->left->father = newA;

	if (newB->right != NULL)
		newB->right->father = newB;


	if ((*x)->father != NULL)
		if ((*x)->father->left == (*x))
			newB->father->left = newB;
		else newB->father->right = newB;

	//update BF,newBF,leftTreeHeight and rightTreeHeight
	

	


	//free old B

	deleteNode = (*x);

	//update
	free(deleteNode->right);
	free(deleteNode);
	(*x) = newA;


}


/// <summary>
/// This is a method that make RL rotation and update the heights of the left and right trees for the suitable nodes.
/// </summary>
/// <param name="x"> Node**.</param>
/// <returns> Make the rotation .</returns>
/// 
void makeRLRotate(Node** x) {
	Node* newA = (Node*)malloc(sizeof(Node));
	CheckMalloc(newA);
	Node* newB = (Node*)malloc(sizeof(Node));
	CheckMalloc(newB);
	Node* newC = (Node*)malloc(sizeof(Node));
	CheckMalloc(newC);
	Node* deleteNode;


	//update BF,newBF,leftTreeHeight and rightTreeHeight

	newA->leftTreeHeight = (*x)->leftTreeHeight;
	newA->rightTreeHeight = (*x)->right->left->leftTreeHeight;
	newA->BF = newA->leftTreeHeight - newA->rightTreeHeight;
	newA->newBF = newA->BF;

	newC->leftTreeHeight = (*x)->right->left->rightTreeHeight;
	newC->rightTreeHeight = (*x)->right->rightTreeHeight;
	newC->BF = newC->leftTreeHeight - newC->rightTreeHeight;
	newC->newBF = newC->BF;

	newB->leftTreeHeight = max(newA->leftTreeHeight, newA->rightTreeHeight) + 1;
	newB->rightTreeHeight = max(newC->leftTreeHeight, newC->rightTreeHeight) + 1;
	newB->BF = newB->leftTreeHeight - newB->rightTreeHeight;
	newB->newBF = newB->BF;


	//set new nodes parameters
	newA->left = (*x)->left;
	newA->right = (*x)->right->left->left;
	newA->father = newB;
	newA->value = (*x)->value;
	


	newB->left = newA;
	newB->right = newC;
	newB->father = (*x)->father;
	newB->value = (*x)->right->left->value;

	newC->left = (*x)->right->left->right;
	newC->right = (*x)->right->right;
	newC->father = newB;
	newC->value = (*x)->right->value;

	if (newA->left != NULL)
		newA->left->father = newA;

	if (newA->right != NULL)
		newA->right->father = newA;


	if ((*x)->father != NULL)
		if ((*x)->father->left == (*x))
			newB->father->left = newB;
		else
			newB->father->right = newB;

	

	if (newC->left != NULL)
		newC->left->father = newC;
	if (newC->right != NULL)
		newC->right->father = newC;

	
	


	

	
	deleteNode = (*x);

	free(deleteNode->right->left);
	free(deleteNode->right);
	free(deleteNode);

	(*x) = newB;


}

/// <summary>
/// This is a method that make LR rotation and update the heights of the left and right trees for the suitable nodes.
/// </summary>
/// <param name="x"> Node**.</param>
/// <returns> Make the rotation .</returns>
/// 
void makeLRRotate(Node** x) {
	Node* newA = (Node*)malloc(sizeof(Node));
	CheckMalloc(newA);
	Node* newB = (Node*)malloc(sizeof(Node));
	CheckMalloc(newB);
	Node* newC = (Node*)malloc(sizeof(Node));
	CheckMalloc(newC);
	Node* deleteNode;

	//update BF,newBF,leftTreeHeight and rightTreeHeight
	newA->leftTreeHeight = (*x)->left->leftTreeHeight;
	newA->rightTreeHeight = (*x)->left->right->leftTreeHeight;
	newA->BF = newA->leftTreeHeight - newA->rightTreeHeight;
	newA->newBF = newA->BF;

	newC->leftTreeHeight = (*x)->left->right->rightTreeHeight;
	newC->rightTreeHeight = (*x)->rightTreeHeight;
	newC->BF = newC->leftTreeHeight - newC->rightTreeHeight;
	newC->newBF = newC->BF;

	newB->leftTreeHeight = max(newA->leftTreeHeight, newA->rightTreeHeight) + 1;
	newB->rightTreeHeight = max(newC->leftTreeHeight, newC->rightTreeHeight) + 1;
	newB->BF = newB->leftTreeHeight - newB->rightTreeHeight;
	newB->newBF = newB->BF;


	//set new A node parameters
	newA->left = (*x)->left->left;
	newA->right = (*x)->left->right->left;
	newA->father = newB;
	newA->value = (*x)->left->value;


	//set new B node parameters
	newB->left = newA;
	newB->right = newC;
	newB->father = (*x)->father;
	newB->value = (*x)->left->right->value;

	//set new C node parameters
	newC->left = (*x)->left->right->right;
	newC->right = (*x)->right;
	newC->father = newB;
	newC->value = (*x)->value;

	//update fathers for Bl and Br
	if (newA->right != NULL)
		newA->right->father = newA;

	if (newA->left != NULL)
		newA->left->father = newA;
	if (newC->left != NULL)
		newC->left->father = newC;

	if (newC->right != NULL)
		newC->right->father = newC;

	//update C father left or right to B
	if ((*x)->father != NULL)
		if ((*x)->father->left == (*x))
			newB->father->left = newB;
		else
			newB->father->right = newB;

	


	deleteNode = (*x);
	free(deleteNode->left->right);
	free(deleteNode->left);
	free(deleteNode);

	//update
	(*x) = newB;



}

/// <summary>
/// This is a method that make LL rotation and update the heights of the left and right trees for the suitable nodes.
/// </summary>
/// <param name="x"> Node**.</param>
/// <returns> Make the rotation .</returns>
/// 
void makeLLRotate(Node** x) {
	Node* newA = (Node*)malloc(sizeof(Node));
	CheckMalloc(newA);
	Node* newB = (Node*)malloc(sizeof(Node));
	CheckMalloc(newB);
	Node* deleteNode = NULL;

	//update BF, newBF, leftTreeHeight and rightTreeHeight
	newB->leftTreeHeight = (*x)->left->rightTreeHeight;
	newB->rightTreeHeight = (*x)->rightTreeHeight;
	newB->newBF = newB->leftTreeHeight - newB->rightTreeHeight;
	newB->BF = newB->newBF;

	newA->leftTreeHeight = (*x)->left->leftTreeHeight;
	newA->rightTreeHeight = max(newB->rightTreeHeight, newB->leftTreeHeight) + 1;
	newA->newBF = newA->leftTreeHeight - newA->rightTreeHeight;
	newA->BF = newA->newBF;

	


	newA->left = (*x)->left->left;
	newA->right = newB;
	newA->father = (*x)->father;
	newA->value = (*x)->left->value;

	newB->left = (*x)->left->right;
	newB->right = (*x)->right;
	newB->father = newA;
	newB->value = (*x)->value;

	if (newA->left != NULL)
		newA->left->father = newA;

	if ((*x)->father != NULL)
		if ((*x)->father->left == (*x))
			newA->father->left = newA;
		else newA->father->right = newA;

	if (newB->left != NULL)
		newB->left->father = newB;
	if (newB->right != NULL)
		newB->right->father = newB;


	
	//free old A

	deleteNode = (*x);
	free(deleteNode->left);
	free(deleteNode);

	//update 
	(*x) = newB;


}


/// <summary>
/// This is a method that move around the tree in preOrder.
/// </summary>
/// <param name="t"> Node*.</param>
/// <returns> Prints the values .</returns>
/// 
void moveAroundTheTree(Node* t) {
	if (t == NULL)
		return;
	printf("(%d,%d)\n", t->value, t->newBF);
	moveAroundTheTree(t->left);
	moveAroundTheTree(t->right);
}

/// <summary>
/// This is a method that updates the BF after the insert, delete and rotation.
/// </summary>
/// <param name="x"> Node**.</param>
/// <param name="rotateOrInsOrDel"> Int.</param>
/// <returns> Returns the root .</returns>
/// 
Node* updateBF(Node** x, int rotateOrInsOrDel) {
	if ((*x) == NULL) 
		return;
	
	updateLaRTree(x);
	(*x)->newBF = (*x)->leftTreeHeight - (*x)->rightTreeHeight;
	if (rotateOrInsOrDel == ROTATE)
		if(abs((*x)->newBF) < 2)
		(*x)->BF = (*x)->newBF;
	if ((*x)->father == NULL)
		return *x;

	return(updateBF(&(*x)->father, rotateOrInsOrDel));
}

/// <summary>
/// This is a method that updates the left and right tree after insert, delete and rotation.
/// </summary>
/// <param name="x"> Node**.</param>
/// <returns> Returns the root .</returns>
/// 
void updateLaRTree(Node** x) {

	if ((*x)->left != NULL && (*x)->right != NULL) {
		(*x)->leftTreeHeight = max((*x)->left->leftTreeHeight, (*x)->left->rightTreeHeight) + 1;
		(*x)->rightTreeHeight = max((*x)->right->leftTreeHeight, (*x)->right->rightTreeHeight) + 1;
	}
	else
		if ((*x)->left == NULL && (*x)->right != NULL) {
			(*x)->leftTreeHeight = 0;
			(*x)->rightTreeHeight = max((*x)->right->leftTreeHeight, (*x)->right->rightTreeHeight) + 1;
		}
		else
			if ((*x)->left != NULL && (*x)->right == NULL) {
				(*x)->rightTreeHeight = 0;
				(*x)->leftTreeHeight = max((*x)->left->leftTreeHeight, (*x)->left->rightTreeHeight) + 1;
			}
			else {
				(*x)->rightTreeHeight = 0;
				(*x)->leftTreeHeight = 0;
			}
}

/// <summary>
/// This is a method manage the insertion and deletion of a node.
/// </summary>
/// <param name="t"> Node**.</param>
/// <param name="p"> Int.</param>
/// <param name="z"> Node*.</param>
/// <returns> void .</returns>
/// 
void InsertorDeleteNode(Node** t, int p, Node* z) {
	Node* root = NULL,*k =NULL;
	int i = 0;
	if (p == INSERT) {
		Insert(t, z);
		//nodeForRoll = *t;
		*t = updateBF(t, INSERTorDELETE);
		//if((*t)->father!=NULL)
		root = *t;
		*t = nodeForRoll;
		*t = rotate(t, INSERT);
		if (*t == NULL)
			*t = root;
		*t = updateBF(t, ROTATE);
		//*t = root;
	}
	else {
		*t = Delete(t);
		nodeForRoll = *t;
		*t = updateBF(t, INSERTorDELETE);
		root = *t;
		while (nodeForRoll != NULL) {
			*t = nodeForRoll;
			k = rotate(t, DELETE);
			*t = updateBF(t, ROTATE);
			nodeForRoll = *t;
			if (nodeForRoll->father != NULL)
				nodeForRoll = nodeForRoll->father;
			else
				if (abs(nodeForRoll->newBF) < 2)
					nodeForRoll = nodeForRoll->father;
		}
	}


}

/// <summary>
/// This is a method free all the mallocs of the tree when the user decide to end.
/// </summary>
/// <param name="t"> Node**.</param>
/// <returns> void .</returns>
/// 
void freeAll(Node** t) {
	if (*t == NULL)
		return;

	freeAll(&((*t)->left));
	freeAll(&((*t)->right));
	free(*t);
	*t = NULL;
}

/// <summary>
/// This is a method to check the malloc function.
/// </summary>
/// <param name="ptr"> Node*.</param>
/// <returns> void .</returns>
/// 
void CheckMalloc(Node* ptr) {
	if (ptr == NULL) {
		printf("Cannot allocate memory\n");
		exit(1);
	}
}
