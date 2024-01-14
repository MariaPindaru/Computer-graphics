
// Tema4Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Tema4.h"
#include "Tema4Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <algorithm>

#define PI 3.14159265358979323846


// CTema4Dlg dialog

double f( double u ) {
	// elipsa
	return cos( u );

	// spirala
	//return  u * cos( u );

	// parabola
	//return u;
}

double g( double u ) {
	// elipsa
	return 2 * sin( u );

	// spirala
	//return u * sin( u );

	// parabola
	//return u * u;
}

std::vector<Point> generateCurve( double a, double b, int numPoints ) {
	std::vector<Point> points;
	double step = ( b - a ) / numPoints;
	for ( int i = 0; i <= numPoints - 1; ++i ) {
		double u = a + i * step;
		points.push_back( Point( f( u ), g( u ) ) );
	}
	return points;
}

void transformPoints( std::vector<Point>& points, double screenWidth, double screenHeight ) {

	Point origin( 0, 0 );

	// Pasul 1 - translatam punctele Pi
	double dx = std::min_element( points.begin(), points.end(), [] ( const Point& a, const Point& b ) { return a.x < b.x; } )->x;
	double dy = std::min_element( points.begin(), points.end(), [] ( const Point& a, const Point& b ) { return a.y < b.y; } )->y;
	for ( auto& p : points ) {
		p.x -= dx;
		p.y -= dy;
	}

	// Pasul 2 - scalare a punctelor P'i
	double maxX = std::max_element( points.begin(), points.end(), [] ( const Point& a, const Point& b ) { return a.x < b.x; } )->x;
	double maxY = std::max_element( points.begin(), points.end(), [] ( const Point& a, const Point& b ) { return a.y < b.y; } )->y;
	double scaleX = screenWidth / maxX;
	double scaleY = screenHeight / maxY;
	double scale = scaleX < scaleY ? scaleX : scaleY; // min(scaleX, scaleY)
	for ( auto& p : points ) {
		p.x *= scale;
		p.y *= scale;
	}

	// Pasul 3 - translatare in centrul ferestrei
	maxX *= scale;
	maxY *= scale;
	double offsetX = ( screenWidth - maxX ) / 2;
	double offsetY = ( screenHeight - maxY ) / 2;
	for ( auto& p : points ) {
		p.x += offsetX;
		p.y += offsetY;
	}

	// Pasul 4 - simetrie pe verticala
	for ( auto& p : points ) {
		p.y = screenHeight - p.y;
	}
}


CTema4Dlg::CTema4Dlg( CWnd* pParent /*=nullptr*/ )
	: CDialogEx( IDD_TEMA4_DIALOG, pParent )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

void CTema4Dlg::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CTema4Dlg, CDialogEx )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTema4Dlg message handlers

BOOL CTema4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon( m_hIcon, TRUE );			// Set big icon
	SetIcon( m_hIcon, FALSE );		// Set small icon

	// TODO: Add extra initialization here
	SetWindowPos( NULL, 0, 0, 900, 600, SWP_NOMOVE | SWP_NOZORDER );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTema4Dlg::OnPaint()
{
	CPaintDC pdc( this );
	// elipsa
	double a = 0, b = 2 * PI;

	// spirala 
	//double a = 0, b = 20;

	// parabola
	//double a = -5, b = 5;

	int numPoints = 3000;
	double screenWidth = 800;
	double screenHeight = 500;

	m_curvePoints = generateCurve( a, b, numPoints );
	
	// push origin -> tranformations are applied 
	Point origin( 0, 0 );
	m_curvePoints.push_back( origin );
	
	transformPoints( m_curvePoints, screenWidth, screenHeight );

	// get the transformed origin and remove from vector
	origin = m_curvePoints.back();
	m_curvePoints.pop_back();

	// draw xOy
	pdc.MoveTo( origin.x, 0 );
	pdc.LineTo( origin.x, screenHeight );

	pdc.MoveTo( 0, origin.y );
	pdc.LineTo( screenWidth, origin.y );

	POINT* points = new POINT[m_curvePoints.size()];
	for ( size_t i = 0; i < m_curvePoints.size(); ++i )
	{
		points[i].x = m_curvePoints[i].x;
		points[i].y = m_curvePoints[i].y;
	}

	pdc.Polyline( points, m_curvePoints.size() );
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTema4Dlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon );
}

