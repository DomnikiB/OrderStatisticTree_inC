#include <stdio.h>
#include <stdlib.h>

typedef struct tn *tp;
struct tn 
{
	int key, size;
	char color;	//r for red, b for black
	tp left, right, parent;
};



void DEFINE_NODE(tp *new)
{
	int data;
	
	*new=(tp)malloc(sizeof(struct tn));
	printf("\n Give me the KEY of new node \n");
	scanf("%d", &data);
	getchar();
	(*new)->key=data;
	(*new)->size=1;	//SIZE, diafora apo RBT
	(*new)->color='r';
	(*new)->left=NULL;
	(*new)->right=NULL;
	(*new)->parent=NULL;
}

void FIND_NODE(tp *root, tp *nill, int nkey, tp *current)
{
	if (*root==*nill)
	{
		printf("\n The node doesn't exist \n");
	}
	else 
	{
		*current=*root;
		if ((*root)->key<nkey)
		{
			FIND_NODE(&(*root)->right, nill, nkey, current);
		}
		if ((*root)->key>nkey)
		{
			FIND_NODE(&(*root)->left, nill, nkey, current);
		}
		if ((*root)->key==nkey)
		{
			printf("\n The node has been found in color %c.\n", (*root)->color);
			
		}
	}
}

void LEFT_ROTATE(tp *root, tp *nill, tp *new)
{
	tp temp,aux;
	
	aux=(*new);

	temp = aux->right; //temp to deksi paidi tou komvou gia rotate

	aux->right = temp->left; //deksi tou komvou gia rotate to aristero tou temp

	if (temp->left!=(*nill))
	{
		temp->left->parent=aux; //amfidromi tou ^
	}
	
	temp->parent = aux->parent;

	if (aux->parent == *nill) //an o komvos gia rotate einai i riza
	{
		*root=temp;
	}
	else if (aux->parent->left==aux)//an o komvos gia rotate einai aristero paidi
	{
		aux->parent->left=temp;
	}
	else if (aux->parent->right==aux)	//an o komvos gia rotate einai deksi paidi
	{
		aux->parent->right=temp;
	}

	temp->left=aux;
	aux->parent=temp;
	
	temp->size=aux->size;	//prosarmogi tou SIZE sta rotation
	aux->size=aux->left->size + aux->right->size + 1;
}

void RIGHT_ROTATE(tp *root, tp *nill, tp *new)
{
	tp temp, aux;
	
	aux=(*new);
	
	temp=aux->left; //temp to aristero paidi tou komvou gia rotate
	
	aux->left=temp->right; //aristero tou komvou gia rotate to deksi tou temp
	
	if (temp->right!=(*nill))
	{
		temp->right->parent=aux; //amfidromi tou ^
	}
	
	temp->parent=aux->parent;
	
	if (aux->parent==*nill) //an o komvos gia rotate einai i riza
	{
		*root=temp;
	}
	else if (aux->parent->right==aux)	//an o komvos gia rotate einai deksi paidi
	{
		aux->parent->right=temp;
	}
	else if (aux->parent->left==aux)	//an o komvos gia rotate einai aristero paidi
	{
		aux->parent->left=temp;
	}
	temp->right=aux;
	aux->parent=temp;
	
	temp->size=aux->size; //prosarmogi tou SIZE sta rotation
	aux->size=aux->left->size + aux->right->size + 1;
}

void INSERT_FIXUP(tp *root, tp *nill, tp *new)
{
	tp uncle;
	
	while ((*new)->parent->color=='r')
	{
		if ((*new)->parent==(*new)->parent->parent->left)	//an o pateras tou neou komvou einai aristero paidi 
		{
			uncle=(*new)->parent->parent->right;	//uncle tou new
			if (uncle->color=='r')
			{
				printf("\nINSERT FIXUP case 1a\n");
				(*new)->parent->color='b';
				uncle->color='b';
				(*new)->parent->parent->color='r';
				(*new)=(*new)->parent->parent;	
			}
			else 
			{
				if ((*new)==(*new)->parent->right)		//an uncle==black kai new einai deksi paidi
				{
					printf("\nINSERT FIXUP case 1b\n");
					(*new)=(*new)->parent;
					LEFT_ROTATE(root, nill, new);
				}
				printf("\nINSERT FIXUP case 1c\n");
				(*new)->parent->color='b'; //an uncle==black kai new einai aristero paidi	
				(*new)->parent->parent->color='r';
				RIGHT_ROTATE(root, nill, &(*new)->parent->parent);
			}
		}
		else if ((*new)->parent==(*new)->parent->parent->right)		//an o pateras tou neou komvou einai deksi paidi
		{
			uncle=(*new)->parent->parent->left;	//uncle tou new
			if (uncle->color=='r')
			{
				printf("\nINSERT FIXUP case 2a\n");
				(*new)->parent->color='b';
				uncle->color='b';
				(*new)->parent->parent->color='r';
				(*new)=(*new)->parent->parent;	
			}
			else 
			{
				if ((*new)==(*new)->parent->left)		//an uncle==black kai new einai aristero paidi
				{
					printf("\nINSERT FIXUP case 2b\n");
					(*new)=(*new)->parent;
					RIGHT_ROTATE(root, nill, new);
				}
				printf("\nINSERT FIXUP case 2c\n");			
				(*new)->parent->color='b';	//an uncle==black kai new einai deksi paidi
				(*new)->parent->parent->color='r';
				LEFT_ROTATE(root, nill, &(*new)->parent->parent);
			}
		}
	}
	(*root)->color='b'; 
}

void INSERT_NODE(tp *root, tp *nill, tp *new, tp *current)     //diagrafw case (*new)->key=(*current)->key giati sto ost den peirazei na exoyme komvous me idio key
{
	tp aux; 
	DEFINE_NODE(new);
	FIND_NODE(root, nill, (*new)->key, current);
	if (*root==*nill)	//an to dentro einai keno
	{
		*root=*new;
		(*new)->parent=(*nill);
	}
	else if ((*new)->key<(*current)->key)
	{
		(*current)->left=(*new);
		(*new)->parent=(*current);
	}
	else if ((*new)->key>=(*current)->key)
	{
		(*current)->right=(*new);
		(*new)->parent=(*current);
	}
	aux=(*new)->parent;
	while(aux!=(*nill))	//anadromi tou dentrou pros ta panw gia auksisi tou SIZE
	{
		aux->size=aux->left->size + aux->right->size + 1;
		aux=aux->parent;
	}
	
	(*new)->left=(*nill);
	(*new)->right=(*nill);
	INSERT_FIXUP(root, nill, new);
}

void TRANSPLANT(tp *root, tp *nill, tp *aux, tp *auxchild)
{

	if ((*aux)->parent==(*nill))	
	{
		*root=*auxchild;
	}
	else if (*aux==(*aux)->parent->left)
	{
		(*aux)->parent->left=*auxchild;
	}
	else
	{
		(*aux)->parent->right=*auxchild;
	}
	(*auxchild)->parent=(*aux)->parent;
	
}

tp TREEMINIMUM(tp *root, tp *nill, tp x)
{	
	while (x->left!=*nill)
	{
		x=x->left;
	}
	return x;
}

void DELETE_FIXUP(tp *root, tp *nill, tp *aux)
{
	tp node, sibling;
	node=*aux;
	
	while (node!=(*root) && node->color=='b')
	{
		if (node==node->parent->left)
		{
			sibling=node->parent->right;
			if (sibling->color=='r')	//aderfos einai RED
			{
				printf("\n DELETE FIXUP case 1a \n");
				sibling->color='b';
				node->parent->color='r';
				LEFT_ROTATE(root, nill, &node->parent);
				sibling=node->parent->right;
			}	
			if (sibling->left->color=='b' && sibling->right->color=='b') //aderfos einai BLACK kai paidia aderfou einai BLACK
			{
				printf("\n DELETE FIXUP case 1b \n");
				sibling->color='r';
				node=node->parent;
			}
			else 
			{
				if (sibling->right->color=='b') //aderfos einai BLACK kai aristero paidi aderfou einai RED, deksi paidi BLACK
				{
					printf("\n DELETE FIXUP case 1c \n");
					sibling->left->color='b';
					sibling->color='r';
					RIGHT_ROTATE(root, nill, &sibling);
					sibling=node->parent->right;
				}
				printf("\n DELETE FIXUP case 1d \n"); //aderfos einai BLACK kai deksi paidi aderfou einai RED
				sibling->color=node->parent->color;
				node->parent->color='b';
				sibling->right->color='b';
				LEFT_ROTATE(root, nill, &node->parent);
				node=*root;
			}
		}
		else 
		{
			sibling=node->parent->left;
			if (sibling->color=='r')	//aderfos einai RED
			{
				printf("\n DELETE FIXUP case 2a \n");
				sibling->color='b';
				node->parent->color='r';
				RIGHT_ROTATE(root, nill, &node->parent);
				sibling=node->parent->left;
			}	
			if (sibling->right->color=='b' && sibling->left->color=='b') //aderfos einai BLACK kai paidia aderfou einai BLACK
			{
				printf("\n DELETE FIXUP case 2b \n");
				sibling->color='r';
				node=node->parent;
			}
			else 
			{
				if (sibling->left->color=='b') //aderfos einai BLACK kai deksi paidi aderfou einai RED, aristero paidi BLACK
				{
					printf("\n DELETE FIXUP case 2c \n");	
					sibling->right->color='b';
					sibling->color='r';
					LEFT_ROTATE(root, nill, &sibling);
					sibling=node->parent->left;
				}
				printf("\n DELETE FIXUP case 2d \n"); //aderfos einai BLACK kai aristero paidi aderfou einai RED
				sibling->color=node->parent->color;
				node->parent->color='b';
				sibling->left->color='b';
				RIGHT_ROTATE(root, nill, &node->parent);
				node=*root;
			}
		}
	}
	node->color='b';
}

void DELETE(tp *root, tp *nill, tp *aux)
{
	tp temp, node, tobedeleted, decrem;
	char temp_original_color;
	
	tobedeleted=*aux;
		
	temp=*aux;
	temp_original_color=temp->color;
	
	decrem=(*aux)->parent;		//afairei 1 SIZE apo thn apli diadromi pou kataligei ston komvo poy tha diagrafei
	while (decrem!=(*nill))
	{
		decrem->size=decrem->size - 1;
		decrem=decrem->parent;
	}
	
	
	if (tobedeleted->left==*nill)
	{
		node=tobedeleted->right;
		TRANSPLANT(root, nill, &tobedeleted, &tobedeleted->right);
	}
	else if (tobedeleted->right==*nill)
	{
		node=tobedeleted->left;
		TRANSPLANT(root, nill, &tobedeleted, &tobedeleted->left);
	}
	else 
	{
		temp=TREEMINIMUM(root, nill, tobedeleted->right);
		temp_original_color=temp->color;
		
		node=temp->right;
		
		if (temp->parent==tobedeleted)
		{
			node->parent=temp;
		}
		else
		{
			TRANSPLANT(root, nill, &temp, &temp->right);
			temp->right=tobedeleted->right;
			temp->right->parent=temp;
			temp->parent->size=temp->parent->right->size + temp->parent->left->size + 1;	//otan allazei o komvos, metaferetai kai to swsto SIZE ston apo panw komvo
		}
		TRANSPLANT(root, nill, &tobedeleted, &temp);
		temp->left=tobedeleted->left;
		temp->left->parent=temp;
		temp->color=tobedeleted->color;
		temp->size=temp->right->size + temp->left->size + 1;	//otan allazei o komvos, metaferetai kai to swsto SIZE (periptwsi diagrafis root)
	}
	if (temp_original_color=='b')
	{
		DELETE_FIXUP(root, nill, &node);
	}
	free(tobedeleted);
	tobedeleted->parent=NULL;
	tobedeleted->left=NULL;
	tobedeleted->right=NULL;
}

tp SELECT(tp *aux, int i)
{
	int r;
	r=(*aux)->left->size + 1;
	
	if (i==r)
	{
		return (*aux);
	}
	else if (i<r)
	{
		SELECT(&(*aux)->left, i);
	}
	else
	{
		SELECT(&(*aux)->right, i-r);
	}
}

int RANK(tp *root, tp *node)
{
	int r;
	tp aux;
	
	r=(*node)->left->size + 1;
	aux=*node;
	
	while (aux!=(*root))
	{
		if (aux==aux->parent->right)
		{
			r=r+aux->parent->left->size +1;
		}
		aux=aux->parent;
	}
	return r;
}

void PRINT_TREE(tp *root, tp *nill, int i)
{
	if (*root!=*nill)
	{
		printf("\n TreeNode[%d]=%d in color %c with size %d. \n", i, (*root)->key, (*root)->color, (*root)->size);
		
		PRINT_TREE(&(*root)->left, nill, 2*i+1);
		PRINT_TREE(&(*root)->right, nill, 2*i+2);
		
	}
}

void PRINT2D_TREE(tp *root, tp *nill, int space)
{
	int i, NUM;
	NUM=10;
	
	if (*root!=*nill)
	{
		space+=NUM;
		PRINT2D_TREE(&(*root)->right, nill, space);
		printf("\n");
		for (i=NUM; i<space; ++i)
		{
			printf(" ");
		}
		printf("%d%c\n", (*root)->key, (*root)->color);
		PRINT2D_TREE(&(*root)->left, nill, space);
	}
}

int main ()
{
	char c;
	int nkey, i, rank;
	tp nill, new, root, current, selected;
	
	nill=(tp)malloc(sizeof(struct tn));	//default komvos fyllwn 
	nill->key=0;
	nill->size=0;
	nill->color='b';
	nill->left=NULL;
	nill->right=NULL;
	nill->parent=NULL;
	
	root=nill;
	new=NULL;
	current=NULL;
	selected=NULL;
		
	c='*';
	while(c!='q')
	{
		printf("\n Find node (f), Insert new node (i), Delete defined node (d), Select the i-th smallest key (s), Find the position of a node in linear order (r), Print tree (p), Print tree in 2D (b), Quit (q) \n");
		scanf(" %c", &c);
		getchar();
		if (c =='f')
		{
			printf("\n FIND NODE \n");
			printf("\n Give me the key of node to look for \n");
			scanf("%d", &nkey);
			FIND_NODE(&root, &nill, nkey, &current);
		}
		else if (c =='i')
		{
			printf("\n INSERT NEW NODE \n");
			INSERT_NODE(&root, &nill, &new, &current);
		}
		else if (c =='d')
		{
			printf("\n DELETE NODE \n");
			printf("\n Give me the node's key \n");
			scanf("%d", &nkey);
			FIND_NODE(&root, &nill, nkey, &current);
			DELETE(&root, &nill, &current);
		}
		else if (c=='s')
		{
			printf("\n SELECT NODE \n");
			printf("\n Give me the i-th smallest node to look for \n");
			scanf("%d", &i);
			selected=SELECT(&root, i);
			printf("\n Selected has key %d\n", selected->key);
			
		}
		else if (c=='r')
		{
			printf("\n RANK NODE \n");
			printf("\n Give me the node's key \n");
			scanf("%d", &nkey);
			FIND_NODE(&root, &nill, nkey, &current);
			rank=RANK(&root, &current);
			printf("\n The position of node with key %d is %d-th in rank.\n", nkey, rank);
		}
		else if (c =='p')
		{
			PRINT_TREE(&root, &nill, 0);
		}
		else if (c =='b')
		{
			PRINT2D_TREE(&root, &nill, 0);
		}
		printf("\n Press any key to continue...\n");
	}
return 0;
}
