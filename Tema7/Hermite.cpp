#include "pch.h"
#include "Hermite.h"

CPoint Hermite( const CPoint& p0, const CPoint& p1, const CPoint& p2, const CPoint& p3, double u )
{
	CPoint m0 = p1 - p0;
	CPoint m1 = p3 - p2;

	double h1 = 2 * pow( u, 3 ) - 3 * pow( u, 2 ) + 1;
	double h2 = -2 * pow( u, 3 ) + 3 * pow( u, 2 );
	double h3 = pow( u, 3 ) - 2 * pow( u, 2 ) + u;
	double h4 = pow( u, 3 ) - pow( u, 2 );

	CPoint result;
	result.x = p0.x * h1 + p2.x * h2 + m0.x * h3 + m1.x * h4;
	result.y = p0.y * h1 + p2.y * h2 + m0.y * h3 + m1.y * h4;

	return result;
}