
// TicTacToeDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "TicTacToe.h"
#include "TicTacToeDlg.h"
#include "afxdialogex.h"
#include "FileDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTicTacToeDlg ��ȭ ����

CTicTacToeDlg::CTicTacToeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTicTacToeDlg::IDD, pParent)
	, m_startCom(-1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTicTacToeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_UNDO_A, m_undoA);
	DDX_Control(pDX, IDC_BUTTON_UNDO_B, m_undoB);
	DDX_Control(pDX, IDC_COMBO_A, m_comboA);
	DDX_Control(pDX, IDC_COMBO_B, m_comboB);
	DDX_Control(pDX, IDC_EDIT_A, m_listA);
	DDX_Control(pDX, IDC_EDIT_B, m_listB);
	DDX_Radio(pDX, IDC_RADIO_A, m_startCom);
}

BEGIN_MESSAGE_MAP(CTicTacToeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CTicTacToeDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CTicTacToeDlg::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CTicTacToeDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CTicTacToeDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_UNDO_A, &CTicTacToeDlg::OnBnClickedButtonUndoA)
	ON_BN_CLICKED(IDC_BUTTON_UNDO_B, &CTicTacToeDlg::OnBnClickedButtonUndoB)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CTicTacToeDlg �޽��� ó����

BOOL CTicTacToeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_hAccelTable = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));

	GetDlgItem(IDC_BUTTON_UNDO_A)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_UNDO_B)->EnableWindow(false);
	m_BKColor = CreateSolidBrush(RGB(255, 255, 255));

	m_isLoad = 0;
	m_checkUndo = 0;

	SetGame();
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CTicTacToeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

BOOL CTicTacToeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.	 
	if (m_hAccelTable != NULL)
    {
		if (TranslateAccelerator(m_hWnd, m_hAccelTable, pMsg))
		{
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CTicTacToeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CTicTacToeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CTicTacToeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	if(pWnd->GetDlgCtrlID() == IDC_EDIT_A)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_BKColor;
	}

	if(pWnd->GetDlgCtrlID() == IDC_EDIT_B)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_BKColor;
	}
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

void CTicTacToeDlg::OnBnClickedButtonExit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int conclusion;

	if(m_board.state == GameBoard::STATE_PLAY)
	{
		conclusion = MessageBox(L"���� �������Դϴ�.\n������ �ߴ� �Ͻðڽ��ϱ�?", L"���� �ߴ�", MB_OKCANCEL);
		if(conclusion == IDOK)
			m_board.state = GameBoard::STATE_STOP;
	}
	else{
		conclusion = MessageBox(L"������ ���� �Ͻðڽ��ϱ�?", L"���� ����", MB_OKCANCEL);
		if(conclusion == IDOK)
			exit(0);
	}
}

void CTicTacToeDlg::OnBnClickedButtonUndoA()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_checkUndo = 1;
}

void CTicTacToeDlg::OnBnClickedButtonUndoB()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_checkUndo = 1;
}

void CTicTacToeDlg::OnBnClickedButtonStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	StartGame();
}

void CTicTacToeDlg::OnBnClickedButtonInit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	ResetGame();
}

void CTicTacToeDlg::OnBnClickedButtonLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	LoadGame();
}

int CTicTacToeDlg::CheckReady()
{
	UpdateData(TRUE);

	int level_a = m_comboA.GetCurSel();
	int level_b = m_comboB.GetCurSel();

	if(level_a == -1 || level_b == -1)
		return -1;
	else if(m_startCom == -1)
		return 0;
	else
	{
		switch (level_a)
		{
		case 0: m_levelA = 1; break;
		case 1: m_levelA = 2; break;
		case 2: m_levelA = 3; break;
		case 3: m_levelA = 4; break;
		case 4: m_levelA = 5; break;
		case 5: m_levelA = 6; break;
		case 6: m_levelA = 7; break;
		case 7: m_levelA = 8; break;
		}

		switch (level_b)
		{
		case 0: m_levelB = 1; break;
		case 1: m_levelB = 2; break;
		case 2: m_levelB = 3; break;
		case 3: m_levelB = 4; break;
		case 4: m_levelB = 5; break;
		case 5: m_levelB = 6; break;
		case 6: m_levelB = 7; break;
		case 7: m_levelB = 8; break;
		}

		return 1;
	}	
}

void CTicTacToeDlg::SetGame()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_comboA.AddString(L"Level 1");
	m_comboA.AddString(L"Level 2");
	m_comboA.AddString(L"Level 3");
	m_comboA.AddString(L"Level 4");
	m_comboA.AddString(L"Level 5");
	m_comboA.AddString(L"Level 6");
	m_comboA.AddString(L"Level 7");
	m_comboA.AddString(L"Level 8");

	m_comboB.AddString(L"Level 1");
	m_comboB.AddString(L"Level 2");
	m_comboB.AddString(L"Level 3");
	m_comboB.AddString(L"Level 4");
	m_comboB.AddString(L"Level 5");
	m_comboB.AddString(L"Level 6");
	m_comboB.AddString(L"Level 7");
	m_comboB.AddString(L"Level 8");

	GetDlgItem(IDC_EDIT_A)->SetWindowTextW(L"<���� Ʈ��>");
	GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"<���� Ʈ��>");

	m_levelA = 0;
	m_levelB = 0;
}

/**
	�� �� : StartGame()
	�� �� : ���� ���� ��ư�� �������� �����ϴ� �Լ��ν�, �⺻������
			������ ���۵Ǳ��� �ɼ� ������ �غ�Ǿ����� üũ�ϰ�, �߰������� �ҷ��� 
			���������� ���θ� �˻��ؼ� �������� �ʱ�ȭ ������. 
			������ �Ϸ�Ǹ� ������ ���������� �������� ���� ��
*/
void CTicTacToeDlg::StartGame()
{
	int checkErr;				/* ���� ������ �˷��ִ� ���� */

	checkErr = CheckReady();	/* ������ ������ �غ� �Ǿ����� �˻� */
	if(checkErr == 1)			/* ���ϰ��� 1�̸� �غ� �Ϸ� */
	{
		if(m_isLoad!=0)			/* �ҷ��� �����̶��, */
		{						/* �ҷ��� ���� ������ ������ �ʱ�ȭ */
			m_board.InitBoard(m_startCom, m_isLoad, m_levelA, m_levelB);	
			m_isLoad = 0;
		}
		else
			m_board.InitBoard(m_startCom, 0, m_levelA, m_levelB);	/* �ƴ϶��, ���ο� ������ �ʱ�ȭ */

		UpdateGame();
		m_board.state = GameBoard::STATE_PLAY;						/* ������ ���¸� �÷��� ������ ���� */

 		while(m_board.state == GameBoard::STATE_PLAY)		/* ���� ���̶�� */
		{
			TicTacToeAI* tttAI = new TicTacToeAI(m_board);	/* ���ο� AI ��ü�� ���� */

			tttAI->GetBestMove();							/* ������ ��ǥ�� ���� */

			Evaluation* eval = tttAI->GetEvaluation();		/* lika : ���忡 Eval����ϱ� ���� Evaluaton ��ȯ */
			this->PrintEval(eval);							/* lika : ���忡 Eval ��� */

			m_board.DoMove(tttAI->bestX, tttAI->bestY);		/* �ش� ��ǥ�� ���� �� */
			
			Node* node = tttAI->GetRootNode();			/* ������ ��ǥ�� ���ϴµ��� ������ Ʈ�� �� ��Ʈ��� ��ȯ */
			this->PrintTreeNode(node);					/* Ʈ�� ��� */
			
			UpdateGame();							/* ������ ������Ʈ */
		
			while(WaitUndo())							/* ������ ��ٸ� */
			{
				m_board.RandomMove();	/* �����ִ� ��ǥ�� ������ ������ ���� �� */
				UpdateGame();						/* ������ ������Ʈ */
			}

			delete tttAI;
			delete eval;		/* lika : delete eval �Ҵ��� �޸� ���� */
			delete node;

			m_board.CheckState();			/* ������ ���¸� ���� */
			if(m_board.state != GameBoard::STATE_PLAY)
				EndGame();					/* �÷��� ���� �ƴ� ���¸� ���� ���� */
		}
		UpdateGame();	/* ���� �����ǿ��� ��� */
	}
	else if(checkErr == -1)	/* ���� ������ �ȵǾ������� ���� ��� */
	{
		MessageBox(L"ERROR : LA-Level ������ Ȯ���ϼ���!", L"Error!", MB_ICONERROR);
	}
	else					/* ���� ���� ������ �ȵǾ������� ���� ��� */
		MessageBox(L"ERROR : ���ۼ��� ������ Ȯ���ϼ���!", L"Error!", MB_ICONERROR);
}

/**
	lika
	�� �� : PrintEval(Evaluation* eval)
	�� �� : Board�� Eval���� �������.
*/
void CTicTacToeDlg::PrintEval(Evaluation* eval){
	int count = 0;
	int comButton = 0;
	int temp[3][3] = { 0 };
	DWORD dwStart;
	dwStart = GetTickCount();
	CString str;

	for (int i = 0; i < eval->possible; i++){
		temp[eval->x[i]][eval->y[i]] = eval->eval[i];
	}

	if (m_board.moveCnt % 2 == 1)
	{
		if (m_board.starterCom == 'X')
			comButton = IDC_B1;
		else
			comButton = IDC_A1;
	}
	else
	{
		if (m_board.starterCom == 'X')
			comButton = IDC_A1;
		else
			comButton = IDC_B1;
	}

	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if (m_board.board[i][j] == 'X')
				SetDlgItemText(comButton + count, L"X");
			else if (m_board.board[i][j] == 'O')
				SetDlgItemText(comButton + count, L"O");
			else
			{
				str.Format(L"%d", temp[i][j]);
				SetDlgItemText(comButton + count, str);
				if (m_board.moveCnt < 3 && i == 1 && j == 1){ /* lika : 4��° �� ������ (1,1)�� Eval����� 'B'��� */
					str.Format(L"%c", 'B');
					SetDlgItemText(comButton + count, str);
				}
			}
			count++;
		}
	}

	while (GetTickCount() - dwStart < 3000); /* Board�� Eval���� 3�ʰ� ��� */
}

/**
	�� �� : PrintTreeNode(Node* root)
	�� �� : AI�� ���ؼ� ������ ��ǥ�� ���ϴµ����� Eval ���� ������ ����� ������
		   Ʈ���� �ڷᱸ�� ť�� �̿��� �ʺ�켱 Ž������ Edit Box�� ������ִ� �Լ�
*/
void CTicTacToeDlg::PrintTreeNode(Node* root)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int preDepth = 0 ;			/* ���� ����� ���� */
	bool preParent = false;		/* �θ� ������ ���� ���� */
	Node *pNode = root;			/* ��Ʈ��带 ���� */
	CString temp, temp2;	
	queue <Node* > que;			/* ť ���� */

	que.push(pNode);			/* ť�� ��Ʈ��带 �ְ� */
	while(!que.empty())			/* ť�� ������� �� ���� ��� */
	{		
		pNode = que.front();	/* �տ��� ������ */
		que.pop();
		if(pNode != NULL)		/* NULL ���� �ƴϰ� */
		{
			if( preDepth != pNode->depth )	/* ���� ��尪�� ���̰� �ٸ��� */
				temp = temp + (L"\r\n");	/* ���� */

			if(preParent)					/* �θ��尡 ������ */
				temp = temp + (L", ");		/* �̾ ��� */
			else
				temp = temp + (L"(");		/* �ٸ��� '(' �� ���� */
			
			temp2.Format(L"%d", pNode->eval);
			temp = temp + temp2;			

			preParent = true;				

			if(pNode->childCnt != 0)		/* �ڽĳ�� ������ 0�� �ƴϸ� */
			{
				que.push(NULL);				/* NULL ������ �θ��� ���� ���ְ� */
				for(int j=0; j < pNode->childCnt; j++)
					que.push(pNode->next[j]);		/* �ڽĳ�带 ť�� ���� */
				
			}
			preDepth = pNode->depth;				/* ��� ���̸� ���� */
		}
		else							/* ť���� ������ NULL �� �̶�� */
		{
			if (!que.empty()){	/* lika : ')'�� �ѹ� �� ��µǴ� ���� ó�� */
				temp = temp + (L")"); /* ')' �� �θ��带 ���� */
				preParent = false;
			}
		}
	}
	temp = temp + (L")");

	if(m_board.moveCnt % 2 == 1)
	{
		if(m_board.starterCom == 'X')
		{
			GetDlgItem(IDC_EDIT_A)->SetWindowTextW(temp);
			GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"<���� Ʈ��>");
		}	
		else
		{
			GetDlgItem(IDC_EDIT_A)->SetWindowTextW(L"<���� Ʈ��>");
			GetDlgItem(IDC_EDIT_B)->SetWindowTextW(temp);
		}
	}
	else
	{
		if(m_board.starterCom == 'X')
		{
			GetDlgItem(IDC_EDIT_B)->SetWindowTextW(temp);
			GetDlgItem(IDC_EDIT_A)->SetWindowTextW(L"<���� Ʈ��>");
		}	
		else
		{
			GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"<���� Ʈ��>");
			GetDlgItem(IDC_EDIT_A)->SetWindowTextW(temp);
		}
	}
}

/**
	�� �� : ResetGame()
	�� �� : �������� �� �ʱ�ȭ ��Ű�� �Լ�
*/
void CTicTacToeDlg::ResetGame()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString tempStr, str;
	int count = 0;

	m_startCom = -1;
	UpdateData(FALSE);

	m_board.state = GameBoard::STATE_INIT;
	m_board.InitBoard(m_startCom, 0, m_levelA, m_levelB);	

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			str.Format(L"%c", 'B');	/* lika : 'B'�� ��� */
			SetDlgItemText(1001+count, str);
			SetDlgItemText(1011+count, str);
			count++;
		}
	}

	GetDlgItem(IDC_EDIT_A)->SetWindowTextW(L"<���� Ʈ��>");
	GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"<���� Ʈ��>");
	m_undoA.EnableWindow(FALSE);
	m_undoB.EnableWindow(FALSE);
	m_comboA.SetCurSel(-1);
	m_comboB.SetCurSel(-1);
}

/**
	�� �� : EndGame()
	�� �� : ������ �����Ű�� �ش� ������ ���¿����� Edit Box�� �������
		    ������ִ� �Լ� 
*/
void CTicTacToeDlg::EndGame()
{
	switch(m_board.state)
	{
	case GameBoard::STATE_WINA :
		GetDlgItem(IDC_EDIT_A)->SetWindowTextW(L"���ӿ� �̰���ϴ�.");
		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"���ӿ� �����ϴ�.");
		break;

	case GameBoard::STATE_WINB :
		GetDlgItem(IDC_EDIT_A)->SetWindowTextW(L"���ӿ� �����ϴ�.");
		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"���ӿ� �̰���ϴ�.");
		break;
		
	case GameBoard::STATE_DRAW :
		GetDlgItem(IDC_EDIT_A)->SetWindowTextW(L"���ӿ� �����ϴ�.");
		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"���ӿ� �����ϴ�.");
		break;

	case GameBoard::STATE_INIT :
		GetDlgItem(IDC_EDIT_A)->SetWindowTextW(L"<���� Ʈ��>");
		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"<���� Ʈ��>");
		break;
	
	case GameBoard::STATE_STOP :
		GetDlgItem(IDC_EDIT_A)->SetWindowTextW(L"������ �ߴ܉���ϴ�.");
		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"������ �ߴ܉���ϴ�.");
		break;		
	}
	m_undoA.EnableWindow(FALSE);
	m_undoB.EnableWindow(FALSE);
}

/**
	�� �� : WaitUndo()
	�� �� : ��ǻ�Ͱ� ���� �ش� ��ǥ�� ���� �����⸦ �ϱ���� 5�ʵ��� ��ٸ���
			�Լ�. �����⸦ �����ϸ� 1�� �����ϰ� �׷��� ������ 0�� ����
*/
int CTicTacToeDlg::WaitUndo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	if(m_board.moveCnt % 2 == 1)
	{
		if(m_board.starterCom == 'X')
		{
			m_undoA.EnableWindow(TRUE);
			m_undoB.EnableWindow(FALSE);
		}
		else
		{
			m_undoA.EnableWindow(FALSE);
			m_undoB.EnableWindow(TRUE);
		}
	}
	else
	{
		if(m_board.starterCom == 'X')
		{
			m_undoA.EnableWindow(FALSE);
			m_undoB.EnableWindow(TRUE);
		}
		else
		{
			m_undoA.EnableWindow(TRUE);
			m_undoB.EnableWindow(FALSE);
		}
	}

	while(GetTickCount() - dwStart < 5000)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			PreTranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(m_checkUndo == 1)		/* �����⸦ �����ߴٸ� */
		{
			m_checkUndo = 0;		/* üũ���� 0���� �ٲ۵� 1�� ��ȯ */
			return 1;
		}
	}
	return 0;						/* �ƴ϶��, 0�� ��ȯ */
}

/**
	�� �� : UpdateGame()
	�� �� : �ش� �������� ȭ������ ������Ʈ ���ִ� �Լ�
*/
void CTicTacToeDlg::UpdateGame()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int count = 0;
	int comButton = 0;
	CString str;
	
	if(m_board.moveCnt % 2 == 1)
	{
		if(m_board.starterCom == 'X')
			comButton = IDC_A1;
		else
			comButton = IDC_B1;
	}
	else
	{
		if(m_board.starterCom == 'X')
			comButton = IDC_B1;
		else
			comButton = IDC_A1;
	}

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(m_board.board[i][j] == 'X')
				SetDlgItemText(comButton+count, L"X");
			else if(m_board.board[i][j] == 'O')
				SetDlgItemText(comButton+count, L"O");
			else
			{
				str.Format(L"%c", 'B');	/* lika : 'B'�� ��� */
				SetDlgItemText(comButton+count, str);
			}
			count++;
		}
	}

	count = 0;
	if(m_board.state != GameBoard::STATE_PLAY)
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(m_board.board[i][j] == 'X')
				{
					SetDlgItemText(IDC_A1+count, L"X");
					SetDlgItemText(IDC_B1+count, L"X");
				}
				else if(m_board.board[i][j] == 'O')
				{
					SetDlgItemText(IDC_A1+count, L"O");
					SetDlgItemText(IDC_B1+count, L"O");
				}
				else
				{
					str.Format(L"%c", 'B');	/* lika : 'B'�� ��� */
					SetDlgItemText(IDC_A1+count, str);
					SetDlgItemText(IDC_B1+count, str);
				}
				count++;
			}
		}
	}
}

/**
	�� �� : LoadGame()
	�� �� : ������ �ҷ������� �ش� ������ ������ ȭ�鿡 ������Ʈ ���ִ� �Լ�
*/
void CTicTacToeDlg::LoadGame()
{
	CFileDlg dlg;

	if(m_board.state == GameBoard::STATE_PLAY)	/* �ҷ����� ������ ������������ �˻� */
	{
		MessageBox(L"������ �������Դϴ�! �����ϰ� �õ��ϼ���.", L"�� ��", MB_ICONEXCLAMATION);
		return;
	}

	if(dlg.DoModal()==IDOK)
	{		
		FILE *fp;						/* ���� ������ ���� */
		CStringA name(dlg.m_fileStr);

		if(!(fp = fopen(name, "r")))
		{
			MessageBox(L"������ �� �� �����ϴ�! ���ϸ��� Ȯ���ϼ���.", L"ERROR", MB_ICONERROR);
			return;
		}
		else		/* ����� ���� �����̶�� */
		{
			int i, j, stoneCount=0;
			int Acnt = 0 , Bcnt = 0;
			char temp[4];

			for(i=0; i<3; i++)
			{
				fscanf_s(fp, "%s", temp, 4);	/* �ش����Ͽ��� ������ ������ */
				for(j=0; j<3; j++)				/* ���ڿ� �°� �����ǿ� �Է� */
				{				
					if(temp[j] == 'X')			
					{
						m_board.board[i][j] = 'X';
						Acnt++;
					}						
					else if(temp[j] == 'O')
					{
						m_board.board[i][j] = 'O';
						Bcnt++;
					}
					else
						m_board.board[i][j] = ' ';
				}
			}

			if(Acnt < Bcnt)			/* 'X'�� 'O' ���� ������ �� */
				m_startCom = 1;		/* A�� ������ B�� ���� ��ǻ�� */
			else					/* �����ϸ�, A�� ���� ��ǻ�� */
				m_startCom = 0;

			UpdateData(FALSE);
			m_isLoad = Acnt + Bcnt;
			UpdateGame();
			GetDlgItem(IDC_EDIT_A)->SetWindowTextW(L"<���� Ʈ��>");
			GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"<���� Ʈ��>");
			fclose(fp);
		}
	}
}
