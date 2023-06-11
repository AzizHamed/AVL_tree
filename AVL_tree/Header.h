#ifndef _AVL_TREE1
#define _AVL_TREE1
#define INSERT 1
#define DELETE 0
#define LEFT 0
#define RIGHT 1
#define UP 0
#define DOWN 1
#define ROOT 2
#define ROTATE 1
#define	INSERTorDELETE 0

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include <ctype.h>
typedef struct Node {
	int value;
	int BF;
	int newBF;
	int leftTreeHeight;
	int rightTreeHeight;
	struct Node* left;
	struct Node* right;
	struct Node* father;
} Node;
Node* nodeForRoll;
Node** nodeForRoll1;
Node* search(Node* t, int NodeForSearch);
void Insert(Node** t, Node* z);
void updateLaRTree(Node** x);
Node* Delete(Node** x);
Node* rotate(Node** x, int p);
void chooseRoll(Node** x, int p);
void makeLLRotate(Node** x);
void makeLRRotate(Node** x);
void makeRLRotate(Node** x);
void makeRRRotate(Node** x);
void initNewNode(Node** t, Node* z, Node* father, Node* left, Node* right);
void moveAroundTheTree(Node* t);
Node* findMax(Node* t);
Node* findMin(Node* t);
Node* updateBF(Node** x, int rotateOrInsOrDel);
Node* findSuccessor(Node* x);
Node* findPredecessor(Node* x, int whereToSearch);
Node* DeleteNode(Node** x);
void checkAndUpdateFather(Node** t, Node* x);
void BuildSuccessor(Node** t, Node* father);
void InsertorDeleteNode(Node** t, int p, Node* z);
void freeAll(Node** t);
void CheckMalloc(Node* ptr);
#endif
#pragma once
