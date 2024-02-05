#include "pch.h"
#include "LagrangeInterpolation.h"

double LagrangeInterpolation( const std::vector<double>& x, const std::vector<double>& y, double xInterpolate )
{
	double result = 0.0;
	int pointsCount = x.size();

	for ( size_t i = 0; i < pointsCount; ++i )
	{
		double temp = y.at( i );
		for ( size_t j = 0; j < pointsCount; ++j )
		{
			if ( i != j )
			{
				temp *= ( xInterpolate - x.at( j ) ) / ( x.at( i ) - x.at( j ) );
			}
		}

		result += temp;
	}

	return result;
}
