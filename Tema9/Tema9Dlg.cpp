
// Tema9Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Tema9.h"
#include "Tema9Dlg.h"
#include "afxdialogex.h"

#include "BSpline.h"

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

	for ( const auto& point : m_controlPoints )
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
	if ( m_controlPoints.size() > 1 && m_bCollectingPoints )
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
		m_controlPoints.push_back( point );
	}
	else
	{
		for ( size_t index = 0; index < m_controlPoints.size(); ++index )
		{
			if ( abs( point.x - m_controlPoints[index].x ) < DOT_SIZE && abs( point.y - m_controlPoints[index].y ) < DOT_SIZE )
			{
				m_pSelectedPoint = &m_controlPoints[index];
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

void CTema9Dlg::DrawCurve( CDC* pDC )
{
	CPen blackPen( 0, 3, RGB( 0, 0, 0 ) );
	pDC->SelectObject( &blackPen );

	int degree = 2;

	CPoint firstPoint = BSpline( 0.0, degree, m_controlPoints );
	pDC->MoveTo( firstPoint );

	for ( double t = 0.01; t < 1.0; t += 0.01 )
	{
		CPoint curvePoint = BSpline( t, degree, m_controlPoints );
		pDC->LineTo( curvePoint );
		// prepare for next one
		pDC->MoveTo( curvePoint );
	}
}

