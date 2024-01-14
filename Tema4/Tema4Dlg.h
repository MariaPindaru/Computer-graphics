
// Tema4Dlg.h : header file
//

#pragma once

#include <vector>

struct Point {
	double x, y;

	Point( double xVal, double yVal ) : x( xVal ), y( yVal ) {}
};


// CTema4Dlg dialog
class CTema4Dlg : public CDialogEx
{
// Construction
public:
	CTema4Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEMA4_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	std::vector<Point> m_curvePoints;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
