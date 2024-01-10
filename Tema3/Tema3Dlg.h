
// Tema3Dlg.h : header file
//

#pragma once

#include <vector>

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

	void OnLButtonDown( UINT, CPoint );
	void OnLButtonUp( UINT, CPoint );
	void OnMouseMove( UINT, CPoint );
	void OnRButtonDown( UINT, CPoint );

	DECLARE_MESSAGE_MAP()

private:
	std::vector<CPoint> m_selectedPoints;
	CPoint m_dragLastPosition;
	bool m_bPolygonIsFinished;
	bool m_bIsDragging;
};
