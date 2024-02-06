#include "pch.h"

#include "Transformation2D.h"


Transformation2D::Transformation2D() :
	m_matrix { {
		{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0}
	} }
{}

Transformation2D::Transformation2D( std::array<std::array<double, SIZE>, SIZE> matrix )
	: m_matrix( matrix )
{
}

std::array<double, SIZE> Transformation2D::Product( const std::array<double, SIZE>& point )
{
	std::array<double, SIZE> result = { 0.0, 0.0, 0.0 };

	for ( size_t row_index = 0; row_index < SIZE; ++row_index ) {
		for ( size_t column_index = 0; column_index < SIZE; ++column_index ) {
			result[row_index] += m_matrix[row_index][column_index] * point[column_index];
		}
	}

	return result;
}

std::array<std::array<double, SIZE>, SIZE> Transformation2D::Product( const std::array<std::array<double, SIZE>, SIZE>& matrix )
{
	std::array<std::array<double, SIZE>, SIZE> result;

	for ( int i = 0; i < SIZE; ++i ) {
		for ( int j = 0; j < SIZE; ++j ) {
			result[i][j] = 0;
			for ( int k = 0; k < SIZE; ++k ) {
				result[i][j] += m_matrix[i][k] * matrix[k][j];
			}
		}
	}

	return result;
}

void Transformation2D::Compose( const std::array<std::array<double, SIZE>, SIZE>& otherMatrix )
{
	m_matrix = Product( otherMatrix );
}

void Transformation2D::Translate( double dx, double dy )
{
	std::array<std::array<double, SIZE>, SIZE> translationMatrix {
		{
			{1.0, 0.0, dx},
			{0.0, 1.0, dy},
			{0.0, 0.0, 1.0}
		} };

	Compose( translationMatrix );
}

void Transformation2D::RotateOrigin( double cosineAlpha, double sineAlpha )
{
	std::array<std::array<double, SIZE>, SIZE> rotationMatrix {
		{
			{cosineAlpha, -sineAlpha, 0.0},
			{sineAlpha, cosineAlpha, 0.0},
			{0.0, 0.0, 1.0}
		} };

	Compose( rotationMatrix );
}

void Transformation2D::ScaleOrigin( double x, double y )
{
	std::array<std::array<double, SIZE>, SIZE> scalingMatrix { {
			{x, 0.0, 0.0},
			{0.0, y, 0.0},
			{0.0, 0.0, 1.0}
		} };

	Compose( scalingMatrix );
}

void Transformation2D::RotatePoint( double xp, double yp, double cosineAlpha, double sineAlpha )
{
	Translate( xp, yp );
	RotateOrigin( cosineAlpha, sineAlpha );
	Translate( -xp, -yp );
}

void Transformation2D::SymmetryPoint( double xp, double yp )
{
	Translate( xp, yp );
	ScaleOrigin( -1, -1 );
	Translate( -xp, -yp );
}

void Transformation2D::SymmetryLine( double startX, double startY, double endX, double endY )
{
	double length = sqrt( ( endX - startX ) * ( endX - startX ) + ( endY - startY ) * ( endY - startY ) );

	if ( length != 0 ) {
		// rotation
		double cosineAlpha = ( endX - startX ) / length;
		double sineAlpha = ( endY - startY ) / length;

		Translate( startX, startY );
		RotateOrigin( cosineAlpha, sineAlpha );
		ScaleOrigin( 1, -1 );
		RotateOrigin( cosineAlpha, -sineAlpha );
		Translate( -startX, -startY );
	}
}
