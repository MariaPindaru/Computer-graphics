#pragma once

#include <vector>

#include "Transformation2D.h"

class CPolygon
{

public:
	void AddCoordinate( CPoint& point );
	const std::vector<CPoint> GetCoordinates();

	bool IsValid();

	void Transform();
	void Translate( double dx, double dy );
	void Rotate( double dx, double dy, double cosineAlpha, double sineAlpha );
	void Scale( float factor );

	CPoint GetCenter() const;

private:
	void ApplyTransformationOnCoordinates( Transformation2D& transformation );

private:
	std::vector<CPoint> m_points;
};

