#pragma once

#include <vector>
#include <array>

//Membrii clasei( private ) :
//	-Produs de doua matrici
//	Functiile clasei( publice ) :
//	-Produs cu un vector de lungime 3 de double( "Produs cu un punct" )
//	- Compunere( transformare curenta cu alta transformare = > noua transformare )
//	- Rotatie( primeste cos si sin pentru un unghi si construieste o matrice corespunzatoare rotatiei respective fata de origine pe care o compunem cu transformarea curenta )
//	- Scalare( primeste 2 valori Sx si Sy )
//	- Simetrie fata de origine( nu primeste parametrii )
//	- Simetrie fata de OX
//	- Simetrie fata de OY
//	- Translatie( primeste 2 valori dx si dy )
//	- Rotatie fata de un punct P( primim coordonatele x, y, sin alpha, cos alpha )
//	- Simetrie fata de un punct P( primim x, y )
//	- Simetrie fata de o dreapta( primim dx, dy, vx, vy )
//	- Scalare fata de un punct P

#define SIZE 3

class Transformation2D
{
public:
	Transformation2D();
	Transformation2D( std::array<std::array<double, SIZE>, SIZE> matrix);

public:

	std::array<double, SIZE> Product( const std::array<double, SIZE>& point );
	void Compose( const std::array<std::array<double, SIZE>, SIZE>& otherMatrix );

	void Translate( double dx, double dy );
	void RotateOrigin( double cosineAlpha, double sineAlpha );
	void ScaleOrigin( double Sx, double Sy );
	void RotatePoint( double xp, double yp, double cosineAlpha, double sineAlpha );
	void SymmetryPoint( double xp, double yp );
	void SymmetryLine( double xp, double yp, double vx, double vy );

private:
	std::array<std::array<double, SIZE>, SIZE> Product( const std::array<std::array<double, SIZE>, SIZE>& matrix );

private:
	std::array<std::array<double, SIZE>, SIZE> m_matrix;

};
