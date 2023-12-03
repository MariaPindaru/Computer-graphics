
// EAGCDlg.h : header file
//

#pragma once


// CEAGCDlg dialog
class CEAGCDlg : public CDialogEx
{
// Construction
public:
	CEAGCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EAGC_DIALOG };
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

	void DrawBackground( CPaintDC& deviceContext );
	void DrawHouse( CPaintDC& deviceContext );
	void DrawSun( CPaintDC& deviceContext );
	void DrawBird( CPaintDC& deviceContext, int x, int y );
};
