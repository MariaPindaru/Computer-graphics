#include "pch.h"

#include "Transformation2D.h"

Transformation2D::Transformation2D() :
	m_matrix { {
		{1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0}
	} }
{}

std::array<double, 3> Transformation2D::Product( const std::array<double, 3>& point )
{
	std::array<double, 3> result = { 0.0, 0.0, 0.0 };

	for ( int row_index = 0; row_index < 3; ++row_index ) {
		for ( int column_index = 0; column_index < 3; ++column_index ) {
			result[row_index] += m_matrix[row_index][column_index] * result[column_index];
		}
	}

	return result;
}

std::array<std::array<double, 3>, 3> Transformation2D::Product( const std::array<std::array<double, 3>, 3>& matrix )
{
	std::array<std::array<double, 3>, 3> result;

	for ( int i = 0; i < 3; ++i ) {
		for ( int j = 0; j < 3; ++j ) {
			result[i][j] = 0;
			for ( int k = 0; k < 3; ++k ) {
				result[i][j] += m_matrix[i][k] * matrix[k][j];
			}
		}
	}

	return result;
}

void Transformation2D::Compose( const std::array<std::array<double, 3>, 3>& otherMatrix )
{
	m_matrix = Product( otherMatrix );
}

void Transformation2D::Translate( double dx, double dy )
{
	std::array<std::array<double, 3>, 3> translationMatrix { {
			{1.0, 0.0, dx},
			{0.0, 1.0, dy},
			{0.0, 0.0, 1.0}
		} };

	Compose( translationMatrix );
}

void Transformation2D::RotateOrigin( double cosineAlpha, double sineAlpha )
{
	std::array<std::array<double, 3>, 3> rotationMatrix { {
			{cosineAlpha, -sineAlpha, 0.0},
			{sineAlpha, cosineAlpha, 0.0},
			{0.0, 0.0, 1.0}
		} };

	Compose( rotationMatrix );
}

void Transformation2D::ScaleOrigin( double Sx, double Sy )
{
	std::array<std::array<double, 3>, 3> scalingMatrix { {
			{Sx, 0.0, 0.0},
			{0.0, Sy, 0.0},
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

void Transformation2D::SymmetryLine( double xp, double yp, double vx, double vy )
{
	double length = sqrt( vx * vx + vy * vy );
	if ( length != 0 ) {
		double cosineAlpha = vx / length;
		double sineAlpha = vy / length;

		Translate( xp, yp );
		RotateOrigin( cosineAlpha, sineAlpha );
		ScaleOrigin( 1, -1 );
		RotateOrigin( cosineAlpha, -sineAlpha );
		Translate( -xp, -yp );
	}
}
