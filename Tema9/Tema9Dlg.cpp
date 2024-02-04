
// Tema9Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Tema9.h"
#include "Tema9Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DOT_SIZE 7

// CTema9Dlg dialog



CTema9Dlg::CTema9Dlg( CWnd* pParent /*=nullptr*/ )
	: CDialogEx( IDD_TEMA9_DIALOG, pParent )
	, m_bCollectingPoints( true )
	, m_pSelectedPoint( nullptr )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

void CTema9Dlg::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CTema9Dlg, CDialogEx )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()

	ON_WM_RBUTTONDOWN()

	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CTema9Dlg message handlers

BOOL CTema9Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon( m_hIcon, TRUE );			// Set big icon
	SetIcon( m_hIcon, FALSE );		// Set small icon

	SetWindowPos( NULL, 0, 0, 700, 600, SWP_NOMOVE | SWP_NOZORDER );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTema9Dlg::OnPaint()
{
	CPaintDC dc( this );

	for ( const auto& point : m_controllPoints )
	{
		CBrush redBrush( RGB( 255, 0, 0 ) );
		dc.SelectObject( &redBrush );
		dc.Ellipse( point.x - DOT_SIZE, point.y - DOT_SIZE, point.x + DOT_SIZE, point.y + DOT_SIZE );
	}

	if ( !m_bCollectingPoints )
	{
		DrawCurve( &dc );
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTema9Dlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon );
}

void CTema9Dlg::OnRButtonDown( UINT nFlags, CPoint point )
{
	if ( m_controllPoints.size() > 1 && m_bCollectingPoints )
	{
		m_bCollectingPoints = false;
		Invalidate();
	}

	CDialogEx::OnRButtonDown( nFlags, point );
}

void CTema9Dlg::OnLButtonDown( UINT nFlags, CPoint point )
{
	if ( m_bCollectingPoints )
	{
		m_controllPoints.push_back( point );
	}
	else
	{
		for ( size_t index = 0; index < m_controllPoints.size(); ++index )
		{
			if ( abs( point.x - m_controllPoints[index].x ) < DOT_SIZE && abs( point.y - m_controllPoints[index].y ) < DOT_SIZE )
			{
				m_pSelectedPoint = &m_controllPoints[index];
				break;
			}
		}
	}

	Invalidate();
	CDialogEx::OnLButtonDown( nFlags, point );
}

void CTema9Dlg::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_pSelectedPoint = nullptr;
}

void CTema9Dlg::OnMouseMove( UINT nFlags, CPoint point )
{
	if ( !m_pSelectedPoint )
		return;

	m_pSelectedPoint->x = point.x;
	m_pSelectedPoint->y = point.y;

	Invalidate();
}

// Calculate the blend value for a given t, i (control point index), and degree
double N( int i, int degree, double t, const std::vector<double>& knotVector )
{
	if ( degree == 0 ) 
	{
		return ( knotVector[i] <= t && t < knotVector[i + 1] ) ? 1.0 : 0.0;
	}
	else 
	{
		double a = 0.0, b = 0.0;
		double denom1 = knotVector[i + degree] - knotVector[i];
		double denom2 = knotVector[i + degree + 1] - knotVector[i + 1];

		if ( denom1 > 0 ) 
			a = ( t - knotVector[i] ) / denom1 * N( i, degree - 1, t, knotVector );
		if ( denom2 > 0 )
			b = ( knotVector[i + degree + 1] - t ) / denom2 * N( i + 1, degree - 1, t, knotVector );

		return a + b;
	}
}

// Calculate a point on the B-spline curve for a given t
CPoint calculateBSplinePoint( double t, const std::vector<CPoint>& controlPoints, const std::vector<double>& knotVector, int degree )
{
	CPoint point( 0.0, 0.0 );
	int n = controlPoints.size() - 1;

	for ( int i = 0; i <= n; i++ ) 
	{
		double blend = N( i, degree, t, knotVector );
		point.x = point.x + controlPoints[i].x * blend;
		point.y = point.y + controlPoints[i].y * blend;
	}

	return point;
}


void CTema9Dlg::DrawCurve( CDC* pDC )
{
	CPen blackPen( 0, 3, RGB( 0, 0, 0 ) );
	pDC->SelectObject( &blackPen );

	// Example usage
	m_controllPoints = {
		{0, 0}, {1, 2}, {3, 3}, {4, 0}, {5, -1}, {6, 2} // Define your control points here
	};

	int degree = 3; // Degree of the B-spline. For cubic, it's 3.
	// For a uniform cubic B-spline with n+1 control points, you need a knot vector with n+degree+2 elements.
	std::vector<double> knotVector = { 0, 0, 0, 0, 1, 2, 3, 3, 3, 3 }; // Example uniform knot vector

	//double t = 2.5; // Parameter value to evaluate the curve at, should be within the domain defined by the knot vector


	// start from the first point 
	pDC->MoveTo( m_controllPoints.front() );

	for ( double t = 0.5; t <= 1; t += 0.01 )
	{
		CPoint curvePoint = calculateBSplinePoint( t, m_controllPoints, knotVector, degree );

		pDC->LineTo( curvePoint );
		// prepare for next one
		pDC->MoveTo( curvePoint );
	}
}

