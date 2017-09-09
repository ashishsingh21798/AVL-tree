#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct avlnode
{
	int key,height;
	struct  avlnode *left;
	struct avlnode *right;
}avlnode;

int max(int a,int b)
{
	return a>b?a:b;
}

int height(avlnode *node)
{
	if(node==NULL)
	{
		return 0;
	}
	return node->height;
}

int balancefactor(avlnode *node)
{
	if(node==NULL)
	{
		return 0;
	}
	return height(node->left) - height(node->right);
}

avlnode* createnode(int key)
{
	avlnode *node = (avlnode*)malloc(sizeof(avlnode));

	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;

	return node;
}

avlnode* leftrotation(avlnode *x)
{
	avlnode *y = x->right;
	avlnode *t = y->left;

	//perform rotation
	y->left = x;
	x->right = t;

	//update height
	x->height = max(height(x->left),height(x->right))+1;
	y->height = max(height(y->left),height(y->right))+1;

	return y;
}

avlnode* rightrotation(avlnode *y)
{
	avlnode *x = y->left;
	avlnode *t = x->right;

	//perform rotation
	x->right = y;
	y->left = t;

	//update height
	y->height = max(height(y->left),height(y->right))+1;
	x->height = max(height(x->left),height(x->right))+1;

	return x;
}

avlnode* insert(avlnode *node,int key)
{
	if(node == NULL)
	{
		return createnode(key);
	}
	else if(key < node->key)
	{
		node->left = insert(node->left,key);
	}
	else if(key > node->key)
	{
		node->right = insert(node->right,key);
	}
	else
	{
		return node;
	}

	node->height = 1 + max(height(node->left),height(node->right));

	int balance = balancefactor(node);

	//LL case
	if(balance > 1 && key < node->left->key)
	{
		return rightrotation(node);
	}

	//RR case
	if(balance < 1 && key > node->right->key)
	{
		return leftrotation(node);
	}

	//LR case
	if(balance > 1 && key > node->left->key)
	{
		node->left = leftrotation(node->left);
		return rightrotation(node);
	}

	//RL case
	if(balance < 1 && key < node->right->key)
	{
		node->right = rightrotation(node->right);
		return leftrotation(node);
	}

	return node;
}

avlnode* mvn_in_rst(avlnode *node)
{
	avlnode *c = node;

	while(c->left != NULL)
	{
		c = c->left;
	}
	return c;
}


avlnode* delete(avlnode *node,int key)
{
	if(node == NULL)
	{
		return node;
	}
	else if(key < node->key)
	{
		node->left = delete(node->left,key);
	}
	else if(key > node->key)
	{
		node->right = delete(node->right,key);
	}
	else
	{
		if(node->left == NULL || node->right == NULL)
		{
			avlnode *c = node->left ? node->left : node->right;

			if(c==NULL)
			{
				c = node;
				node = NULL;
			}
			else
			{
				*node = *c;
			}

			free(c);
		}
		else
		{
			avlnode *c = mvn_in_rst(node->right);

			node->key = c->key;

			node->right = delete(node->right,c->key);
		}
	}

	if(node == NULL)
	{
		return node;
	}

	node->height = 1 + max(height(node->left),height(node->right));

	int balance = balancefactor(node);

	//LL csae
	if (balance > 1 && balancefactor(node->left) >= 0)
        return rightrotation(node);
 
    // LR case
    if (balance > 1 && balancefactor(node->left) < 0)
    {
        node->left =  leftrotation(node->left);
        return rightrotation(node);
    }
 
    // RR case
    if (balance < -1 && balancefactor(node->right) <= 0)
        return leftrotation(node);
 
    // RL case
    if (balance < -1 && balancefactor(node->right) > 0)
    {
        node->right = rightrotation(node->right);
        return leftrotation(node);
    }
 

	return node;
}



void preorder(avlnode *node)
{
	if(node != NULL)
	{
		printf("%d ",node->key);
		preorder(node->left);
		preorder(node->right);
	}
}


void postorder(avlnode *node)
{
	if(node != NULL)
	{
		postorder(node->left);
		postorder(node->right);
		printf("%d ",node->key);
	}
}

void inorder(avlnode *node)
{
	if(node != NULL)
	{
		inorder(node->left);
		printf("%d ",node->key);
		inorder(node->right);
	}
}


int main()
{
	printf("IT IS AN AVL TREE\n");
	avlnode *root = NULL;

	int i,j;

	for(i=1;i<19;i++)
	{
		root = insert(root,i);
	}
	printf("\n");
	printf("preorder travesal\n");
	preorder(root);
	printf("\n");
	printf("postorder travesal\n");
	postorder(root);
	printf("\n");
	printf("inorder travesal\n");
	inorder(root);
	printf("\n");

	/*
	printf("deletion of 10 in avl\n");
	root = delete(root,10);
	printf("preorder travesal after deletion of 10\n");
	preorder(root);
	*/
	for(i=1;i<19;i++)
	{
		root = delete(root,i);
		printf("\n");
		printf("preorder travesal\n");
		preorder(root);
		printf("\n");
		printf("postorder travesal\n");
		postorder(root);
		printf("\n");
		printf("inorder travesal\n");
		inorder(root);
		printf("\n");
	}
	

	return 0;
}