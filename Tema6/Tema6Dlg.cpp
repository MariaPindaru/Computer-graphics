
// Tema6Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Tema6.h"
#include "Tema6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "NewtonInterpolation.h"

#define DOT_SIZE 7

// CTema6Dlg dialog



CTema6Dlg::CTema6Dlg( CWnd* pParent /*=nullptr*/ )
	: CDialogEx( IDD_TEMA6_DIALOG, pParent )
	, m_bCollectingPoints( true )
	, m_selectedPoint( nullptr )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

void CTema6Dlg::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CTema6Dlg, CDialogEx )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()

	ON_WM_RBUTTONDOWN()

	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CTema6Dlg message handlers

BOOL CTema6Dlg::OnInitDialog()
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

void CTema6Dlg::OnPaint()
{
	CPaintDC dc( this );

	for ( const auto& point : m_points ) 
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
HCURSOR CTema6Dlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon );
}

void CTema6Dlg::OnRButtonDown( UINT nFlags, CPoint point )
{
	if ( m_points.size() > 1 && m_bCollectingPoints )
	{
		m_bCollectingPoints = false;
		Invalidate();
	}

	CDialogEx::OnRButtonDown( nFlags, point );
}

void CTema6Dlg::OnLButtonDown( UINT nFlags, CPoint point )
{
	if ( m_bCollectingPoints )
	{
		if ( m_points.empty() || point.x > m_points.back().x ) 
		{
			m_points.push_back( point );
		}
	}
	else
	{
		for ( size_t index = 0; index < m_points.size(); ++index )
		{
			if ( abs( point.x - m_points[index].x ) < DOT_SIZE && abs( point.y - m_points[index].y ) < DOT_SIZE )
			{
				m_selectedPoint = &m_points[index];
				break;
			}
		}
	}

	Invalidate();

	CDialogEx::OnLButtonDown( nFlags, point );
}

void CTema6Dlg::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_selectedPoint = nullptr;
}

void CTema6Dlg::OnMouseMove( UINT nFlags, CPoint point )
{
	if ( !m_selectedPoint )
		return;

	if ( m_selectedPoint != &m_points.front() )
	{
		CPoint* prev = ( m_selectedPoint - 1 );
		if ( prev->x > point.x )
			return;
	}

	if ( m_selectedPoint != &m_points.back() )
	{
		CPoint* next = ( m_selectedPoint + 1 );
		if ( next->x < point.x )
			return;
	}

	m_selectedPoint->x = point.x;
	m_selectedPoint->y = point.y;

	Invalidate();
}

void CTema6Dlg::DrawCurve( CDC* pDC )
{
	std::vector<double> xCoordinates, yCoordinates;
	xCoordinates.reserve( m_points.size() );
	yCoordinates.reserve( m_points.size() );

	for ( CPoint point : m_points )
	{
		xCoordinates.push_back( point.x );
		yCoordinates.push_back( point.y );
	}

	CPen pen( 0, 3, RGB( 0, 0, 0 ) );
	pDC->SelectObject( &pen );

	// start from the first point 
	pDC->MoveTo( m_points.front() );

	const std::vector<double> coefficients = ComputeNewtonCoefficients( xCoordinates, yCoordinates );

	for ( double xInterpolate = xCoordinates.front(); xInterpolate <= xCoordinates.back(); xInterpolate += 0.1 )
	{
		double yInterpolate = NewtonInterpolation( xCoordinates, coefficients, xInterpolate );

		pDC->LineTo( xInterpolate, yInterpolate );
		// prepare for next one
		pDC->MoveTo( xInterpolate, yInterpolate );
	}
}