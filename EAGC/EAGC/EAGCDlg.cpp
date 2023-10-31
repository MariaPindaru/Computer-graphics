
// EAGCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "EAGC.h"
#include "EAGCDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace Colors
{
	constexpr  COLORREF RED RGB( 255, 0, 0 );
	constexpr COLORREF GREEN RGB( 0, 255, 0 );
	constexpr COLORREF BLUE RGB( 137, 207, 240 );
	constexpr COLORREF YELLOW RGB( 255, 255, 0 );
	constexpr COLORREF ORANGE RGB( 255, 165, 0 );
	constexpr COLORREF BROWN RGB( 139, 69, 19 );
	constexpr COLORREF BLACK RGB( 0, 0, 0 );
	constexpr COLORREF WHITE RGB( 255, 255, 255 );
}


CEAGCDlg::CEAGCDlg( CWnd* pParent /*=nullptr*/ )
	: CDialogEx( IDD_EAGC_DIALOG, pParent )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

void CEAGCDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BEGIN_MESSAGE_MAP( CEAGCDlg, CDialogEx )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CEAGCDlg message handlers

BOOL CEAGCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon( m_hIcon, TRUE );			// Set big icon
	SetIcon( m_hIcon, FALSE );		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEAGCDlg::OnPaint()
{
	CPaintDC deviceContext( this ); // device context for painting    

	DrawBackground( deviceContext );
	DrawHouse( deviceContext );
	DrawSun( deviceContext );

	DrawBird( deviceContext, 310, 90 );
	DrawBird( deviceContext, 340, 70 );
	DrawBird( deviceContext, 370, 50 );
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEAGCDlg::OnQueryDragIcon()
{
	return static_cast< HCURSOR >( m_hIcon );
}

void CEAGCDlg::DrawBackground( CPaintDC& deviceContext )
{
	CRect clientRect;
	GetClientRect( &clientRect );

	CRect topRect = clientRect;
	topRect.bottom = clientRect.bottom / 3 * 2;

	CRect bottomRect = clientRect;
	bottomRect.top = clientRect.bottom / 3 * 2;

	// top rectangle
	CBrush blueBrush( Colors::BLUE );
	deviceContext.SelectObject( &blueBrush );
	deviceContext.FillRect( topRect, &blueBrush );

	// bottom rectangle
	CBrush greenBrush( Colors::GREEN );
	deviceContext.SelectObject( &greenBrush );
	deviceContext.FillRect( bottomRect, &greenBrush );
}

void CEAGCDlg::DrawHouse( CPaintDC& deviceContext )
{
	// house
	CBrush houseBrush( Colors::BROWN );
	CRect houseRect( 100, 200, 300, 400 );

	deviceContext.SelectObject( &houseBrush );
	deviceContext.Rectangle( houseRect );

	// roof
	CBrush roofBrush( Colors::ORANGE );
	CPoint roofPoints[3];
	roofPoints[0] = { 100, 200 };
	roofPoints[1] = { 200, 100 };
	roofPoints[2] = { 300, 200 };

	deviceContext.SelectObject( &roofBrush );
	deviceContext.Polygon( roofPoints, 3 );

	// door
	CBrush doorBrush( Colors::BLACK );
	CRect doorRect( 175, 300, 225, 400 );

	deviceContext.SelectObject( &doorBrush );
	deviceContext.Rectangle( doorRect );

	// windows
	CBrush windowBrush( Colors::WHITE );
	CRect leftWindowRect( 120, 220, 170, 270 );
	CRect rightWindowRect( 230, 220, 280, 270 );

	deviceContext.SelectObject( &windowBrush );
	deviceContext.Rectangle( leftWindowRect );
	deviceContext.Rectangle( rightWindowRect );
}

void CEAGCDlg::DrawSun( CPaintDC& deviceContext )
{
	CBrush sunBrush( Colors::YELLOW );
	deviceContext.SelectObject( &sunBrush );

	int sunCenterX = 70;
	int sunCenterY = 50;
	int sunRadius = 30;

	deviceContext.Ellipse(
		sunCenterX - sunRadius, sunCenterY - sunRadius,
		sunCenterX + sunRadius, sunCenterY + sunRadius
	);

	CPen rayPen( PS_SOLID, 2, RGB( 255, 255, 0 ) );
	deviceContext.SelectObject( &rayPen );

	int numRays = 12;
	int rayLength = 30;

	float PI = 3.14;

	for ( int i = 0; i < numRays; i++ )
	{
		double angle = 2 * PI * i / numRays;
		int startX = sunCenterX + int( sunRadius * cos( angle ) );
		int startY = sunCenterY - int( sunRadius * sin( angle ) );
		int endX = startX + int( rayLength * cos( angle ) );
		int endY = startY - int( rayLength * sin( angle ) );
		deviceContext.MoveTo( startX, startY );
		deviceContext.LineTo( endX, endY );
	}
}

void CEAGCDlg::DrawBird( CPaintDC& deviceContext, int x, int y )
{
	CPen birdPen( 0, 5, Colors::BLACK );
	deviceContext.SelectObject( &birdPen );

	CPoint first[8];
	first[0] = CPoint( x, y );
	first[1] = CPoint( x + 10, y - 10 );
	first[2] = CPoint( x + 20, y - 20 );
	first[3] = CPoint( x + 30, y );

	deviceContext.PolyBezier( first, 4 );

	CPoint second[8];
	second[0] = CPoint( x + 30, y );
	second[1] = CPoint( x + 40, y - 10 );
	second[2] = CPoint( x + 50, y - 20 );
	second[3] = CPoint( x + 60, y);

	deviceContext.PolyBezier( second, 4 );

}

