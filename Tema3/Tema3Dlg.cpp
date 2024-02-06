
// Tema3Dlg.cpp : implementation file
//

#include <cmath>

#include "pch.h"
#include "framework.h"
#include "Tema3.h"
#include "Tema3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.14159265358979323846

// CTema3Dlg dialog

bool isCoordinateValid( const CPoint& point )
{
	return point.x != 0 && point.y != 0;
}

bool isLineValid( const std::pair<CPoint, CPoint>& line )
{
	return isCoordinateValid( line.first ) && isCoordinateValid( line.second );
}

CTema3Dlg::CTema3Dlg( CWnd* pParent /*=nullptr*/ ) :
	CDialogEx( IDD_TEMA3_DIALOG, pParent ),
	m_bPolygonIsFinished( false )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
	m_symmetryLine = std::make_pair( CPoint(), CPoint() );
}

void CTema3Dlg::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CTema3Dlg, CDialogEx )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()

	ON_WM_RBUTTONDOWN()

	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CTema3Dlg message handlers

BOOL CTema3Dlg::OnInitDialog()
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

void CTema3Dlg::OnPaint()
{
	CPaintDC dc( this ); // device context for painting

	if ( m_polygon.IsValid() )
	{
		CPen pen( PS_SOLID, 2, RGB( 0, 0, 0 ) );
		CPen* pOldPen = dc.SelectObject( &pen );

		CBrush brush( RGB( 194, 26, 17 ) );
		CBrush* pOldBrush = dc.SelectObject( &brush );

		std::vector<CPoint> coordinates = m_polygon.GetCoordinates();
		POINT* points = new POINT[coordinates.size()];
		for ( size_t i = 0; i < coordinates.size(); ++i )
		{
			points[i] = coordinates[i];
		}

		dc.Polygon( points, static_cast< int >( coordinates.size() ) );

		if ( isLineValid( m_symmetryLine ) )
		{
			dc.MoveTo( m_symmetryLine.first );
			dc.LineTo( m_symmetryLine.second );
		}

		// clean up
		delete[] points;
		dc.SelectObject( pOldBrush );
		dc.SelectObject( pOldPen );
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTema3Dlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon );
}

void CTema3Dlg::OnLButtonDown( UINT nFlags, CPoint point )
{
	if ( isLineValid( m_symmetryLine ) )
	{
		return;
	}

	if ( m_bCreatingSymmetryLine )
	{
		if ( !isCoordinateValid( m_symmetryLine.first ) )
		{
			m_symmetryLine.first = point;
		}
		else
		{
			m_symmetryLine.second = point;
			m_polygon.Symmetry( m_symmetryLine.first, m_symmetryLine.second );
		}
	}

	else if ( m_bPolygonIsFinished )
	{
		m_lastPoint = point;
	}

	else
	{
		m_polygon.AddCoordinate( point );
		m_polygon.Transform();
	}

	Invalidate();
}

void CTema3Dlg::OnMouseMove( UINT nFlags, CPoint point )
{
	if ( !m_bPolygonIsFinished )
		return CDialogEx::OnMouseMove( nFlags, point );

	if ( ( nFlags & MK_CONTROL ) && ( nFlags & MK_LBUTTON ) )
	{
		CPoint center = m_polygon.GetCenter();
		CSize offset = point - m_lastPoint; // n pixels
		double angle = static_cast< double >( offset.cx ) / 100.0;  // n/100 radians

		m_polygon.Rotate( center.x, center.y, cos( angle ), sin( angle ) );
		Invalidate();
		m_lastPoint = point;
	}

	else if ( nFlags & MK_LBUTTON )
	{
		CSize offset = point - m_lastPoint;
		m_polygon.Translate( offset.cx, offset.cy );
		Invalidate();
		m_lastPoint = point;
	}
}

void CTema3Dlg::OnRButtonDown( UINT nFlags, CPoint point )
{
	if ( !m_bPolygonIsFinished )
		m_bPolygonIsFinished = true;

	else if ( m_bPolygonIsFinished && !isLineValid( m_symmetryLine ) )
		m_bCreatingSymmetryLine = true;
}

BOOL CTema3Dlg::OnMouseWheel( UINT nFlags, short zDelta, CPoint point )
{
	if ( nFlags & MK_CONTROL )
	{
		float scaleFactor = zDelta > 0 ? 1.1f : 0.9f;
		m_polygon.Scale( scaleFactor );
		Invalidate();
	}

	return CDialogEx::OnMouseWheel( nFlags, zDelta, point );
}

