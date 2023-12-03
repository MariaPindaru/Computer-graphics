
// Tema2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Tema2.h"
#include "Tema2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTema2Dlg dialog



CTema2Dlg::CTema2Dlg( CWnd* pParent /*=nullptr*/ )
	: CDialogEx( IDD_TEMA2_DIALOG, pParent ),
	m_bPolygonIsFinished( false )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

void CTema2Dlg::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CTema2Dlg, CDialogEx )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()

	ON_WM_RBUTTONDOWN()

	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CTema2Dlg message handlers

BOOL CTema2Dlg::OnInitDialog()
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

void CTema2Dlg::OnPaint()
{
	CPaintDC dc( this ); // device context for painting

	if ( m_selectedPoints.size() )
	{
		CPen pen( PS_SOLID, 2, RGB( 0, 0, 0 ) );
		CPen* pOldPen = dc.SelectObject( &pen );

		CBrush brush( RGB( 194, 26, 17 ) );
		CBrush* pOldBrush = dc.SelectObject( &brush );

		POINT* points = new POINT[m_selectedPoints.size()];
		for ( size_t i = 0; i < m_selectedPoints.size(); ++i )
		{
			points[i] = m_selectedPoints[i];
		}

		dc.Polygon( points, static_cast< int >( m_selectedPoints.size() ) );

		// clean up
		delete[] points;
		dc.SelectObject( pOldBrush );
		dc.SelectObject( pOldPen );
	}
}

void CTema2Dlg::OnLButtonDown( UINT nFlags, CPoint point )
{
	if ( m_bPolygonIsFinished )
	{
		// move the polygon
		m_bIsDragging = true;
		m_dragLastPosition = point;
	}
	else
	{
		// collect point coordinates
		m_selectedPoints.push_back( point );
		RedrawWindow();
	}
}

void CTema2Dlg::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_bIsDragging = false;
}

void CTema2Dlg::OnMouseMove( UINT nFlags, CPoint point )
{
	if ( m_bIsDragging )
	{
		// calculate the offset between the current position and the previous position of the drag
		CSize offset = point - m_dragLastPosition;
		m_dragLastPosition = point;

		for ( size_t i = 0; i < m_selectedPoints.size(); ++i )
		{
			m_selectedPoints[i] += offset;
		}

		Invalidate();
	}
}

void CTema2Dlg::OnRButtonDown( UINT nFlags, CPoint point )
{
	m_bPolygonIsFinished = true;
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTema2Dlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon );
}

