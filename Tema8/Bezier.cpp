#include "pch.h"
#include "Bezier.h"

unsigned long long Factorial( int n )
{
	return ( n <= 1 ) ? 1 : n * Factorial( n - 1 );
}

double Combination( int n, int k )
{
	return Factorial( n ) / ( Factorial( k ) * Factorial( n - k ) );
}

CPoint Bezier( double t, const std::vector<CPoint>& controlPoints )
{
	CPoint point;
	int n = controlPoints.size() - 1;

	for ( int i = 0; i <= n; i++ )
	{
		double bernstein = Combination( n, i ) * pow( t, i ) * pow( 1 - t, n - i );
		point.x = point.x + controlPoints[i].x * bernstein;
		point.y = point.y + controlPoints[i].y * bernstein;
	}

	return point;
}
