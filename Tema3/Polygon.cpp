#include "pch.h"
#include "Polygon.h"

void CPolygon::AddCoordinate( CPoint& point )
{
	m_points.push_back( point );
}

const std::vector<CPoint> CPolygon::GetCoordinates()
{
	return m_points;
}

bool CPolygon::IsValid()
{
	return m_points.size() >= 2;
}

void CPolygon::Transform()
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

void CPolygon::Translate( double dx, double dy )
{
	Transformation2D transformation;
	transformation.Translate( dx, dy );
	ApplyTransformationOnCoordinates( transformation );
}

void CPolygon::Rotate( double dx, double dy, double cosineAlpha, double sineAlpha )
{
	Transformation2D transformation;
	transformation.RotatePoint( dx, dy, cosineAlpha, sineAlpha );
	ApplyTransformationOnCoordinates( transformation );
}

void CPolygon::Scale( float factor )
{
	Transformation2D transformation;
	transformation.ScaleOrigin( factor, factor );
	ApplyTransformationOnCoordinates( transformation );
}


void CPolygon::Symmetry( const CPoint& start, const CPoint& end )
{
	Transformation2D transformation;
	transformation.SymmetryLine( start.x, start.y, end.x, end.y );
	ApplyTransformationOnCoordinates( transformation );
}

CPoint CPolygon::GetCenter() const
{
	{
		double sumX = 0.0, sumY = 0.0;
		int count = m_points.size();

		for ( const auto& vertex : m_points )
		{
			sumX += vertex.x;
			sumY += vertex.y;
		}

		if ( count )
			return CPoint( static_cast< int >( sumX / count ),
				static_cast< int >( sumY / count ) );

		return CPoint( 0, 0 );
	}
}

void CPolygon::ApplyTransformationOnCoordinates( Transformation2D& transformation )
{
	for ( auto& currentPoint : m_points )
	{
		auto coordinate = std::array<double, SIZE>{ ( double ) currentPoint.x, ( double ) currentPoint.y, 1.0 };
		auto result = transformation.Product( coordinate );
		currentPoint.x = result[0];
		currentPoint.y = result[1];
	}
}
