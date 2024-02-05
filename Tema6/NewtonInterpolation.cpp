#include "pch.h"
#include "NewtonInterpolation.h"

std::vector<double> ComputeNewtonCoefficients( const std::vector<double>& x, const std::vector<double>& y )
{
	int pointsCount = x.size();
	std::vector<std::vector<double>> a( pointsCount, std::vector<double>( pointsCount ) );


	//  i = j  => aij = Y[i]i
	for ( int i = 0; i < pointsCount; ++i )
	{
		a[i][i] = y[i];
	}

	//	i != j => aij = a[i + 1][j] - a[i][j - 1] / x[j] - x[i], 0 <= i <= j <= n
	for ( int i = pointsCount - 1; i >= 0; --i )
	{
		for ( size_t j = i + 1; j < pointsCount; ++j )
		{
			a[i][j] = ( a[i + 1][j] - a[i][j - 1] ) / ( x[j] - x[i] );
		}
	}

	std::vector<double> coefficients;
	for ( int j = 0; j < pointsCount; ++j )
	{
		coefficients.push_back( a[0][j] );
	}

	return coefficients;
}

double NewtonInterpolation( const std::vector<double>& x, const std::vector<double>& coefficients, double xInterpolate )
{
	double result = 0;
	double product = 1;

	for ( int i = 0; i < x.size(); ++i )
	{
		result += coefficients[i] * product;
		product *= ( xInterpolate - x[i] );
	}

	return result;
}