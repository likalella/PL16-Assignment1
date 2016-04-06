
// TicTacToeDlg.h : ��� ����
//

#pragma once

#include "TicTacToeAI.h"
#include <iostream>
#include <queue>

using namespace std;
// CTicTacToeDlg ��ȭ ����
class CTicTacToeDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CTicTacToeDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TICTACTOE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonUndoA();
	afx_msg void OnBnClickedButtonUndoB();
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	HACCEL m_hAccelTable;
	CButton m_undoA;
	CButton m_undoB;	
	CComboBox m_comboA;
	CComboBox m_comboB;
	CEdit m_listA;
	CEdit m_listB;
	HBRUSH m_BKColor;

	/* ����� ���� �Լ� */

	void SetGame();			/* ���� �ʱ� ȭ�� ���� */
	int CheckReady();		/* ���� ���� �غ� ���¸� �˻� */
	int WaitUndo();			/* �����⸦ ��ٸ� */
	void UpdateGame();		/* ���� ���� ȭ�鿡 ������Ʈ */
	void ResetGame();		/* �������� �ٽ� �ʱ�ȭ */
	void PrintTreeNode(Node* root);	/* eval �� ������ ��� */
	void StartGame();			/* ���� ���� */
	void EndGame();				/* ���� ���� */
	void LoadGame();			/* ���� �ҷ����� */

	/*	����� ���� ���� */

	GameBoard m_board;		/* ���� ���� ���� */
	int m_levelA;			/* ��ǻ�� A�� LA-level */
	int m_levelB;			/* ��ǻ�� B�� LA-level */
	int m_startCom;			/* �����ϴ� COM ���� */
	int m_isLoad;			/* ������ �ε� �� ���� ���� */
	int m_checkUndo;		/* �����⸦ �ߴ��� ���� ���� */
};
