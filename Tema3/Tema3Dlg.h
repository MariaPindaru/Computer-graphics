
// Tema3Dlg.h : header file
//

#pragma once

#include <vector>
#include "Transformation2D.h"
#include "Polygon.h"


// CTema3Dlg dialog
class CTema3Dlg : public CDialogEx
{
// Construction
public:
	CTema3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEMA3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

private:
	void OnLButtonDown( UINT, CPoint );
	void OnMouseMove( UINT, CPoint );
	void OnRButtonDown( UINT, CPoint );
	BOOL OnMouseWheel( UINT, short, CPoint );

private:
	std::pair<CPoint, CPoint> m_symmetryLine;

	CPolygon m_polygon;
	CPoint m_lastPoint;

	bool m_bPolygonIsFinished;
	bool m_bCreatingSymmetryLine;
};
