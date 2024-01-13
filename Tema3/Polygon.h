#pragma once

#include <vector>

#include "Transformation2D.h"

class CPolygon
{

public:
	void AddCoordinate( CPoint& point )
	{
		m_points.push_back( point );
	}

	const std::vector<CPoint> GetCoordinates()
	{
		return m_points;
	}

	bool IsValid()
	{
		return m_points.size() >= 2;
	}

	void Transform()
	{
		Transformation2D transformation;
	/*	Transformation2D transformation(
			{ {
			{0.5, 0.0, 0.0},
			{0.0, 1.0, 0.0},
			{0.0, 0.0, 1.0}
			} }
		);*/
		ApplyTransformationOnCoordinates( transformation );
	}

	void Translate( double dx, double dy )
	{
		Transformation2D transformation;
		transformation.Translate( dx, dy );
		ApplyTransformationOnCoordinates( transformation );
	}

	void Rotate( double dx, double dy, double cosineAlpha, double sineAlpha )
	{
		Transformation2D transformation;
		transformation.RotatePoint( dx, dy, cosineAlpha, sineAlpha );
		ApplyTransformationOnCoordinates( transformation );
	}

	void Scale( float factor )
	{
		Transformation2D transformation;
		transformation.ScaleOrigin( factor, factor );
		ApplyTransformationOnCoordinates( transformation );
	}

	CPoint GetCenter() const 
	{
		double sumX = 0.0, sumY = 0.0;
		int numVertices = m_points.size();

		for ( const auto& vertex : m_points ) 
		{
			sumX += vertex.x;
			sumY += vertex.y;
		}

		if ( numVertices )
		{
			return CPoint( static_cast< int >( sumX / numVertices ), static_cast< int >( sumY / numVertices ) );
		}

		return CPoint( 0, 0 ); // default point if the polygon has 0 coordinates
	}

private:

	void ApplyTransformationOnCoordinates( Transformation2D& transformation )
	{
		for ( auto& currentPoint : m_points )
		{
			auto coordinate = std::array<double, SIZE>{ ( double ) currentPoint.x, ( double ) currentPoint.y, 1.0 };
			auto result = transformation.Product( coordinate );
			currentPoint.x = result[0];
			currentPoint.y = result[1];
		}
	}

private:
	std::vector<CPoint> m_points;
};

