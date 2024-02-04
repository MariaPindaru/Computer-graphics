
// Tema7Dlg.h : header file
//

#pragma once

#include <vector>

// CTema7Dlg dialog
class CTema7Dlg : public CDialogEx
{
// Construction
public:
	CTema7Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEMA7_DIALOG };
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
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnMouseMove( UINT nFlags, CPoint point );
	DECLARE_MESSAGE_MAP()

private:
	void DrawCurve( CDC* pDC );

private:
	std::vector<CPoint> m_points;
	CPoint* m_selectedPoint;
};
