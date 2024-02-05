
// Tema8Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Tema8.h"
#include "Tema8Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Bezier.h"

#define DOT_SIZE 7

// CTema8Dlg dialog



CTema8Dlg::CTema8Dlg( CWnd* pParent /*=nullptr*/ )
	: CDialogEx( IDD_TEMA8_DIALOG, pParent )
	, m_selectedPoint( nullptr )
	, m_bCollectingPoints( true )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

void CTema8Dlg::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CTema8Dlg, CDialogEx )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()

	ON_WM_RBUTTONDOWN()

	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CTema8Dlg message handlers

BOOL CTema8Dlg::OnInitDialog()
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

void CTema8Dlg::OnPaint()
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
HCURSOR CTema8Dlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon );
}

void CTema8Dlg::OnRButtonDown( UINT nFlags, CPoint point )
{
	if ( m_controllPoints.size() > 1 && m_bCollectingPoints )
	{
		m_bCollectingPoints = false;
		Invalidate();
	}

	CDialogEx::OnRButtonDown( nFlags, point );
}

void CTema8Dlg::OnLButtonDown( UINT nFlags, CPoint point )
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
				m_selectedPoint = &m_controllPoints[index];
				break;
			}
		}
	}

	Invalidate();
	CDialogEx::OnLButtonDown( nFlags, point );
}

void CTema8Dlg::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_selectedPoint = nullptr;
}

void CTema8Dlg::OnMouseMove( UINT nFlags, CPoint point )
{
	if ( !m_selectedPoint )
		return;

	m_selectedPoint->x = point.x;
	m_selectedPoint->y = point.y;

	Invalidate();
}

void CTema8Dlg::DrawCurve( CDC* pDC )
{
	CPen blackPen( 0, 3, RGB( 0, 0, 0 ) );
	pDC->SelectObject( &blackPen );

	// start from the first point 
	pDC->MoveTo( m_controllPoints.front() );

	for ( double t = 0.0; t <= 1; t += 0.01 )
	{
		CPoint curvePoint = Bezier( t, m_controllPoints );

		pDC->LineTo( curvePoint );
		// prepare for next one
		pDC->MoveTo( curvePoint );
	}
}

