
// Tema7Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Tema7.h"
#include "Tema7Dlg.h"
#include "afxdialogex.h"

#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DOT_SIZE 7

// CTema7Dlg dialog



CTema7Dlg::CTema7Dlg( CWnd* pParent /*=nullptr*/ )
	: CDialogEx( IDD_TEMA7_DIALOG, pParent )
	, m_selectedPoint( nullptr )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

void CTema7Dlg::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CTema7Dlg, CDialogEx )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()

	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CTema7Dlg message handlers

BOOL CTema7Dlg::OnInitDialog()
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

void CTema7Dlg::OnPaint()
{
	CPaintDC dc( this );

	for ( const auto& point : m_points ) {
		CBrush redBrush( RGB( 255, 0, 0 ) );
		dc.SelectObject( &redBrush );
		dc.Ellipse( point.x - DOT_SIZE, point.y - DOT_SIZE, point.x + DOT_SIZE, point.y + DOT_SIZE );
	}

	if ( m_points.size() == 4 )
	{
		DrawCurve( &dc );
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTema7Dlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon );
}

void CTema7Dlg::OnLButtonDown( UINT nFlags, CPoint point )
{
	if ( m_points.size() < 4 )
	{
		m_points.push_back( point );
	}
	else
	{
		for ( size_t index = 0; index < m_points.size(); ++index )
		{
			if ( abs( point.x - m_points[index].x ) < DOT_SIZE &&
				abs( point.y - m_points[index].y ) < DOT_SIZE )
			{
				m_selectedPoint = &m_points[index];
				break;
			}
		}
	}

	Invalidate();

	CDialogEx::OnLButtonDown( nFlags, point );
}

void CTema7Dlg::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_selectedPoint = nullptr;
}

void CTema7Dlg::OnMouseMove( UINT nFlags, CPoint point )
{
	if ( !m_selectedPoint )
		return;

	m_selectedPoint->x = point.x;
	m_selectedPoint->y = point.y;

	Invalidate();
}

CPoint hermite( const CPoint& p0, const CPoint& p1, const CPoint& p2, const CPoint& p3, double u ) {
	CPoint m0 = p1 - p0;
	CPoint m1 = p3 - p2;

	double h1 = 2 * pow( u, 3 ) - 3 * pow( u, 2 ) + 1;
	double h2 = -2 * pow( u, 3 ) + 3 * pow( u, 2 );
	double h3 = pow( u, 3 ) - 2 * pow( u, 2 ) + u;
	double h4 = pow( u, 3 ) - pow( u, 2 );

	CPoint result;
	result.x = p0.x * h1 + p2.x * h2 + m0.x * h3 + m1.x * h4;
	result.y = p0.y * h1 + p2.y * h2 + m0.y * h3 + m1.y * h4;

	return result;
}

void CTema7Dlg::DrawCurve( CDC* pDC )
{
	CPen blackPen( 0, 3, RGB( 0, 0, 0 ) );
	pDC->SelectObject( &blackPen );

	pDC->MoveTo( m_points[0] );
	pDC->LineTo( m_points[1] );

	pDC->MoveTo( m_points[2] );
	pDC->LineTo( m_points[3] );

	CPen redPen( 0, 3, RGB( 255, 0, 0 ) );
	pDC->SelectObject( &redPen );

	// start curve drawing
	pDC->MoveTo( m_points[0] );

	for ( float u = 0; u <= 1; u += 0.01 )
	{
		CPoint p = hermite( m_points[0], m_points[1], m_points[2], m_points[3], u );

		pDC->LineTo( p );
		//prepare for next one
		pDC->MoveTo( p );
	}

}

