#include <stdio.h>
#include <stdlib.h>

struct _point
{
	int pos ;
	int incA ;
	int incB ;
} ;

struct _point points[401000] ;

int Comp( const void *p1, const void *p2 )
{
	return ((struct _point *)p1)->pos - ( (struct _point *)p2)->pos ;
} 

int main()
{
	int i, k ;
	int n, m ;
	scanf( "%d %d", &n, &m ) ;
	k = 0 ;
	for ( i = 0 ; i < n ; ++i )
	{
		int a, b ;
		scanf( "%d %d", &a, &b ) ;
		
		points[k].pos = a ;
		points[k].incA = 1 ;
		points[k].incB = 0 ;
		++k ;
		
		points[k].pos = b ;
		points[k].incA = -1 ;
		points[k].incB = 0 ;
		++k ;
	}
	for ( i = 0 ; i < m ; ++i )
	{
		int a, b ;
		scanf( "%d %d", &a, &b ) ;
		
		points[k].pos = a ;
		points[k].incA = 0 ;
		points[k].incB = 1 ;
		++k ;
		
		points[k].pos = b ;
		points[k].incA = 0 ;
		points[k].incB = -1 ;
		++k ;
	}
	n = k ;
	
	qsort( points, n, sizeof( points[0] ), Comp ) ;

	// Coalesce the same point.
	k = 0 ;
	for ( i = 1 ; i < n ; ++i )
	{
		if ( points[k].pos == points[i].pos )
		{
			points[k].incA += points[i].incA ;
			points[k].incB += points[i].incB ;
		}
		else
		{
			++k ;
			points[k] = points[i] ;
		}
	}
	n = k + 1 ;
	
	// Scan the points and get the result.
	int result = 0 ;
	int cntA = points[0].incA ;
	int cntB = points[0].incB ;
	for ( i = 1 ; i < n ; ++i )
	{
		if ( cntB == 0 && cntA > 0 )
			result += points[i].pos - points[i - 1].pos ;
		cntA += points[i].incA ;
		cntB += points[i].incB ;
	}
	printf( "%d\n", result ) ;
	
	return 0 ;
}
