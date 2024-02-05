#include "pch.h"

#include "BSpline.h"

double N( int i, int p, double t, const std::vector<double>& knots )
{
	if ( p == 0 )
	{
		return ( t >= knots[i] && t < knots[i + 1] ) ? 1.0 : 0.0;
	}

	double left = 0.0;
	if ( knots[i + p] - knots[i] != 0 )
	{
		left = ( t - knots[i] ) / ( knots[i + p] - knots[i] ) * N( i, p - 1, t, knots );
	}

	double right = 0.0;
	if ( knots[i + p + 1] - knots[i + 1] != 0 )
	{
		right = ( knots[i + p + 1] - t ) / ( knots[i + p + 1] - knots[i + 1] ) * N( i + 1, p - 1, t, knots );
	}

	return left + right;
}

CPoint BSpline( double t, int degree, const std::vector<CPoint>& points )
{
	std::vector<double> knots;
	for ( int i = 0; i < points.size() + degree + 1; i++ )
	{
		knots.push_back( i );
	}

	// remap t where the points are located
	int min = degree;
	int max = knots.size() - 1 - degree;
	t = t * ( max - min ) + min;

	CPoint result;
	for ( int i = 0; i < points.size(); i++ )
	{
		double basis = N( i, degree, t, knots );
		result.x += basis * points[i].x;
		result.y += basis * points[i].y;
	}

	return result;
}

CPoint BSplineDeBoor( double t, int degree, const std::vector<CPoint>& points )
{
	int dimension = 2;

	// knot vector with n + degree + 2 elements 
	std::vector<double> knots;
	for ( int i = 0; i < points.size() + degree + 1; i++ )
	{
		knots.push_back( i );
	}

	// remap t where the points are located
	int min = degree;
	int max = knots.size() - 1 - degree;
	t = t * ( max - min ) + min;

	// find the spline segment for the t value provided
	int splineSegment;
	for ( splineSegment = min; splineSegment < max; splineSegment++ )
	{
		if ( t >= knots[splineSegment] && t <= knots[splineSegment + 1] )
		{
			break;
		}
	}

	// convert points to homogeneous coordinates
	std::vector<std::vector<double>> homogeneousCoordinates;
	for ( int i = 0; i < points.size(); ++i )
	{
		std::vector<double> temp;
		temp.push_back( points[i].x );
		temp.push_back( points[i].y );
		temp.push_back( 1 );

		homogeneousCoordinates.push_back( temp );
	}

	for ( int level = 1; level <= degree + 1; level++ )
	{
		// build level of the pyramid
		for ( int i = splineSegment; i > splineSegment - degree - 1 + level; i-- )
		{
			double alpha = ( t - knots[i] ) / ( knots[i + degree + 1 - level] - knots[i] );

			// interpolate each component
			for ( int j = 0; j < dimension + 1; j++ )
			{
				homogeneousCoordinates[i][j] = ( 1 - alpha ) * homogeneousCoordinates[i - 1][j] + alpha * homogeneousCoordinates[i][j];
			}
		}
	}

	// convert back to CPoint
	CPoint result;
	result.x = homogeneousCoordinates[splineSegment][0] / homogeneousCoordinates[splineSegment][dimension];
	result.y = homogeneousCoordinates[splineSegment][1] / homogeneousCoordinates[splineSegment][dimension];

	return result;
}