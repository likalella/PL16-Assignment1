#include "StdAfx.h"
#include "GameBoard.h"

/**
	�� �� : GameBoard()
	�� �� : GameBoard Ŭ������ ������, ������ �������, 
			���� �� ���� �迭�� �������� �޸� �Ҵ�����
*/
GameBoard::GameBoard()
{
	preMoves = new Position[9];
	board = new char*[3];
	
	for(int i=0; i<3; i++)
	{
		board[i] = new char[3];
	}
};

/**
	�� �� : GameBoard(const GameBoard& copy)
	�� �� : ���� �����ڷν�, ��Ī�� �˻翡�� �������� �����Ҷ�,
			���� �Ҵ��� ����� ���� ���縦 �� ���ְ� ����
*/
GameBoard::GameBoard(const GameBoard& copy)
{
	preMoves = new Position[9];
	board = new char*[3];
	
	for(int i=0; i<3; i++)
	{
		board[i] = new char[3];
	}

	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			board[i][j] = copy.board[i][j];

	for(int i=0; i<9; i++)
	{
		preMoves[i].x = copy.preMoves[i].x;
		preMoves[i].y = copy.preMoves[i].y;
	}

	moveCnt = copy.moveCnt;
	state = copy.state;
	starterCom = copy.starterCom;
	oppnentCom = copy.oppnentCom;
	startLevel = copy.startLevel;
	oppLevel = copy.oppLevel;
};

/**
	�� �� : GetBoardStat()
	�� �� : ������ ���� ��ȯ
*/
int GameBoard::GetBoardStat()
{
	return state;
};

/**
	�� �� : InitBoard(int startCom, int movedCnt, int nlevelA, int nlevelB)
	�� �� : �ʱ�ȭ�� �ʿ��� ������ ���ڸ� �߽����� �������� �ʱ�ȭ���ִ� �Լ�
*/
void GameBoard::InitBoard(int startCom, int movedCnt, int nlevelA, int nlevelB)
{
	moveCnt = movedCnt;		/* ��� ° ���� ���� */

	if(startCom == 0)		/* ���� ��ǻ�Ϳ� ��ǻ�� ������ ���� */
	{	
		starterCom = 'X';		oppnentCom = 'O';
		startLevel = nlevelA;	oppLevel = nlevelB;			
	}
	else				
	{
		starterCom = 'O';		oppnentCom = 'X';
		startLevel = nlevelB;	oppLevel = nlevelA;
	}

	if(movedCnt == 0)		/* �ҷ��� �������� ���θ� �˻��ؼ� ������ �ʱ�ȭ */
	{
		for(int i=0; i<3; i++)
			for(int j=0; j<3; j++)
				board[i][j] = ' ';
	}
};

/**
	�� �� : RandomMove()
	�� �� : �����⸦ ���������� ������ ���Ҵ� ���� �ٸ����� ������ �����ϰ� ��ǥ����
*/
void GameBoard::RandomMove()
{
	int newX, newY;
	int preX, preY;
	bool overlap = true;
	srand(GetTickCount());
	
	UndoMove();
	preX = preMoves[moveCnt].x;
	preY = preMoves[moveCnt].y;

	while(overlap)
	{
		newX = rand()%3;
		newY = rand()%3;

		if (moveCnt < 3 && newX == 1 && newY == 1) /* lika : 4��° ���� ������ (1,1)�� �Ѽ� ���� ��. */
			continue;

		if(moveCnt <= 7)	/* �� ��ǥ�� 2�� �̻��϶� */
		{
			if((newX != preX) && (newY != preY))	/* �������λ����� ��ǥ�� ������ǥ�� ���ϰ� */
				if(board[newX][newY] == ' ')		/* �ش� ��ǥ�� ����ִ� �������� �˻� */
					overlap = false;
		}
		else
		{
			if(board[newX][newY] == ' ')
				overlap = false;
		}			
	}		
	DoMove(newX, newY);
};

/**
	�� �� : DoMove(int x, int y)
	�� �� :	�Է¹��� ��ǥ������ �����ǿ� ���� ��
*/
void GameBoard::DoMove(int x, int y)
{
	if( moveCnt%2 == 0 )			/* ���� �������� �˻� */
		board[x][y] = starterCom;
	else
		board[x][y] = oppnentCom;
	
	preMoves[moveCnt].x = x;
	preMoves[moveCnt].y = y;

	moveCnt++;						/* ���� ���� ���� ��Ŵ */
};

/**
	�� �� : UndoMove()
	�� �� : ���Ҵ� ���� �Ѵܰ� �������·� �������� �Լ�
*/
void GameBoard::UndoMove()
{
	moveCnt--;
	board[preMoves[moveCnt].x][preMoves[moveCnt].y] = ' ';
}

/**
	�� �� : CheckState()
	�� �� : ���� �������� ����, �����̰����, �������� �˻��ؼ� ���°��� �������ִ� �Լ�
*/
void GameBoard::CheckState()
{
	char temp[3][3];
	int i;
	
	for(i=0; i<3; i++)				/* ���� ������ �˻� */
	{	
		if(board[i][0]!=' ')
		{
			if((board[i][0]=='X') && (board[i][1]=='X') && (board[i][2]=='X'))
			{
				state = STATE_WINA;
				return;
			}
			if((board[i][0]=='O') && (board[i][1]=='O') && (board[i][2]=='O'))
			{
				state = STATE_WINB;
				return;
			}
		}
		if(board[0][i]!=' ')		/* ���� ������ �˻� */
		{
			if((board[0][i]=='X') && (board[1][i]=='X') && (board[2][i]=='X'))
			{
				state = STATE_WINA;
				return;
			}
			if((board[0][i]=='O') && (board[1][i]=='O') && (board[2][i]=='O'))
			{
				state = STATE_WINB;
				return;
			}
		}
	}
		
	if((board[0][0]!=' ')&&(board[0][0]==board[1][1])&&(board[0][0]==board[2][2]))	/* ù��° �밢�� �˻� */
	{
		if(board[0][0]=='X')
		{
			state = STATE_WINA;
			return;
		}
		else
		{
			state = STATE_WINB;
			return;
		}
	}
	
	if((board[0][2]!=' ')&&(board[0][2]==board[1][1])&&(board[0][2]==board[2][0])) /* �ι�° �밢�� �˻� */
	{
		if(board[0][2]=='X')
		{
			state = STATE_WINA;
			return;
		}
		else
		{
			state = STATE_WINB;
			return;
		}
	}

	if( moveCnt > 8 )
	{
		state = STATE_DRAW;		/* ����� �� */
	}
};