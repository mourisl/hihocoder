#include <stdio.h>
#include <stdlib.h>

struct _treap
{
	int val ;
	int weight ;
	struct _treap *left, *right, *father ;
} ;

struct _treap *root ;

void RotateLeft( struct _treap *node )
{
	struct _treap *r = node->right ;
	node->right = r->left ;
	r->left = node ;
	if ( node->father != NULL )
	{
		if ( node->father->left == node )
			node->father->left = r ;
		else
			node->father->right = r ;
	}	

	r->father = node->father ;
	if ( node->right != NULL )
		node->right->father = node ;
	node->father = r ;

	if ( r->father == NULL )
		root = r ;
}

void RotateRight( struct _treap *node )
{
	struct _treap *l = node->left ;
	node->left = l->right ;
	l->right = node ;
	if ( node->father != NULL )
	{
		if ( node->father->left == node )
			node->father->left = l ;
		else
			node->father->right = l ;
	}	
	l->father = node->father ;
	if ( node->left != NULL )
		node->left->father = node ;
	node->father = l ;

	if ( l->father == NULL )
		root = l ;
} 

void Insert( int val )
{
	struct _treap *node = new struct _treap ;
	node->left = NULL ;
	node->right = NULL ;
	node->father = NULL ;
	node->val = val ;
	node->weight = rand() ;
	if ( root == NULL )
	{
		root = node ;
		return ;
	}
	struct _treap *p = root ;
	struct _treap *prev = p ;
	while ( p != NULL )
	{
		prev = p ;
		if ( p->val < val )
			p = p->right ;
		else 
			p = p->left ;
	}

	if ( prev->val < val )
	{
		prev->right = node ;
		node->father = prev ;
	}	
	else
	{
		prev->left = node ;
		node->father = prev ;
	}

	// Heapify
	while ( node->father != NULL )
	{
		if ( node->weight < node->father->weight )
			break ;
		//printf( "before: %d %d %d\n", val, node->father, node->father->val ) ;
		if ( node->father->left == node )
		{
			RotateRight( node->father ) ;
		}
		else 
		{
			RotateLeft( node->father ) ;
		}
		//printf( "after: %d %d %d\n", node->father, node->right, node->right->val ) ;
	}
}

int Query( int val )
{
	struct _treap *p = root ;
	int ret ;
	while ( p != NULL )
	{
		if ( p->val < val )
		{
			ret = p->val ;
			p = p->right ;
		}
		else if ( p->val > val )
			p = p->left ;
		else
			return p->val ;	
	}
	return ret ;
}

int main()
{
	srand( 17 ) ;
	char op[10] ;
	int i, val ;
	int n ;
	scanf( "%d", &n ) ;
	for ( i = 0 ; i < n ; ++i )
	{
		scanf( "%s %d", op, &val ) ;
		if ( op[0] == 'I' )
		{
			Insert( val ) ;
		}
		else if ( op[0] == 'Q' )
		{
			int ret = Query( val ) ;
			printf( "%d\n", ret ) ;
		}
	}
	return 0 ;
}

