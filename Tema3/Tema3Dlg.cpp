
// Tema3Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Tema3.h"
#include "Tema3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Transformation2D.h"


// CTema3Dlg dialog


CTema3Dlg::CTema3Dlg( CWnd* pParent /*=nullptr*/ )
	: CDialogEx( IDD_TEMA3_DIALOG, pParent )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
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
	SetWindowPos( NULL, 0, 0, 700, 600, SWP_NOMOVE | SWP_NOZORDER );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTema3Dlg::OnPaint()
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTema3Dlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon );
}

void CTema3Dlg::OnLButtonDown( UINT nFlags, CPoint point )
{
	if ( m_bPolygonIsFinished )
	{
		Transformation2D transformation;

		for ( auto& currentPoint: m_selectedPoints )
		{
			auto coordinate = std::array<double, 3>{ ( double ) currentPoint.x, ( double ) currentPoint.y, 0.0 };
			auto result = transformation.Product( coordinate );
			currentPoint.x = result[0];
			currentPoint.y = result[1];
		}

		Invalidate();
	}
	else
	{
		// collect point coordinates
		m_selectedPoints.push_back( point );
		Invalidate();
	}
}

void CTema3Dlg::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_bIsDragging = false;
}

void CTema3Dlg::OnMouseMove( UINT nFlags, CPoint point )
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

void CTema3Dlg::OnRButtonDown( UINT nFlags, CPoint point )
{
	m_bPolygonIsFinished = true;
}

