#include "StdAfx.h"
#include "TicTacToeAI.h"

/**
	�� �� : TicTacToeAI(GameBoard board)
	�� �� : ���� �������� �Ѱܹ޴� ������ �Լ�
*/
TicTacToeAI::TicTacToeAI(GameBoard board)
{
	tttBoard = board;
	root = new Node;
	evaluation = new Evaluation;	/* lika : evaluation �߰� */
	InitNode(root, 0);

	if(tttBoard.moveCnt % 2 == 0)
	{
		LAlevel = tttBoard.startLevel;
		criterion = tttBoard.starterCom;
	}
	else
	{
		LAlevel = tttBoard.oppLevel;
		criterion = tttBoard.oppnentCom;
	}
};

/**
	�� �� : InitNode(Node* node, int inDepth)
	�� �� : ����� ��带 ����, eval�� ������ �ʱ�ȭ
*/
void TicTacToeAI::InitNode(Node* node, int inDepth)
{
	node->depth = inDepth;
	node->eval = 0;
	node->childCnt = 0;

	for(int i=0; i<9; i++)
		node->next[i] = NULL;
};

/**
	�� �� : GetRootNode()
	�� �� : ��Ʈ��带 ��ȯ
*/
Node* TicTacToeAI::GetRootNode()
{
	return root;
};

/**
	lika
	�� �� : GetEvaluation()
	�� �� : ���忡 ����� Evaluation ��ȯ
*/
Evaluation* TicTacToeAI::GetEvaluation()
{
	this->GetSymmetricEval();
	return evaluation;
}

/**
	�� �� : GetBestMove()
	�� �� : ������ ��ǥ�� Minimax �˰����� ���� ����
*/
void TicTacToeAI::GetBestMove()
{
	Position iList[9];				/* ���� �����ǿ��� ���� �� �ִ� ��ǥ ����, ��ġ ���� */
	int	bestValue = -10000;			/* besteval �� ���� */
	int	possible = 0;				/* ������ ���� ���� ���� */

	possible = GetPossibleMove(iList);	/*���� ������ �� ��ǥ, ���� ���� */
	evaluation->possible = possible; /* lika : evaluation�� ���� ������ �� ��ǥ�� ���� ���� */

	for (int i = 0, j = 0; i < possible; i++, j++)				/* ������ �� ��ŭ Minimax �˰����� ����Ͽ� ���� ��� */
	{
		if (tttBoard.moveCnt < 3 && iList[i].x == 1 && iList[i].y == 1){	/* lika : 4��° ������ (1,1)�� �� �� ���� ����ó��*/
			evaluation->possible--;
			j--;
			continue;
		}
		root->next[j] = new Node;					/* ���ο� ��� ���� */
		InitNode(root->next[j], (root->depth) + 1);	/* ��� �ʱ�ȭ */
		tttBoard.DoMove(iList[i].x, iList[i].y);	/* ������ ���� �� */
		evaluation->x[j] = iList[i].x;				/* lika : evaluation�� �� �� �ִ� ��ǥ�� x(������) ���� */
		evaluation->y[j] = iList[i].y;				/* lika : evaluation�� �� �� �ִ� ��ǥ�� y(������) ���� */
		int newValue = Minimize(root->next[j]);		/* Min�Լ�ȣ��� ���� ���ؼ� */
		root->next[j]->eval = newValue;				/* ��忡 ���� */
		evaluation->eval[j] = newValue;				/* lika : evaluation�� �� �� �ִ� ��ǥ�� eval�� ���� */
		tttBoard.UndoMove();						/* �ξ��� ���� ���� */

		if (newValue > bestValue)		/* ���� eval���� best������ ũ�ٸ� */
		{
			bestValue = newValue;		/* ���� �����ϰ� �ش� �������� ���� */
			bestX = iList[i].x;
			bestY = iList[i].y;
			root->eval = bestValue;		/* ��忡 ���� ���� */
		}
	}
	root->childCnt = possible;			/* �ڽ� ��� ���� ���� */
};

/**
	�� �� : Minimize(struct treeNode* root)
	�� �� : ���� �ڽ� ���� eval���߿��� ���� ���� ������ �����ϴ� �Լ�
*/
int TicTacToeAI::Minimize(struct treeNode* root)
{
	Position iList[9];			/* ���� �����ǿ��� ���� �� �ִ� ��ǥ ����, ��ġ ���� */
	int	possible = 0;			/* �Ѽ��ִ� ���� ���� ���� */
	int	bestValue = 10000;		/* besteval �� ���� */

	possible = GetPossibleMove(iList); /*���� ������ �� ��ǥ, ���� ���� */
		
	if( possible == 0 || CheckEnd() || root->depth == LAlevel ) /* �����Ѽ� ���ų�, ��������� eval ���� ����Ͽ� ���� */
	{
		return EvaluateBoard(root);
	}		

	for( int i = 0; i < possible; i++ ) /* ������ �� ��ŭ Minimax �˰����� ����Ͽ� ���� ��� */
	{
		root->next[i] = new Node;					/* ��� ���� �� �ʱ�ȭ */
		InitNode(root->next[i], root->depth+1);

		tttBoard.DoMove(iList[i].x , iList[i].y);	/* ������ ���� �� */
		int newValue = Maximize(root->next[i]);		/* Max�Լ�ȣ��� ���� ���ؼ� */
		root->next[i]->eval = newValue;				/* ��忡 ���� */
		tttBoard.UndoMove();						/* �ξ��� ���� ���� */

		if( newValue < bestValue )	/* ���� eval���� best������ �۴ٸ� */
		{				
			bestValue = newValue;	/* ���� �����ϰ� �ش簪���� ��尪�� ���� */
			root->eval = bestValue;
		}
	}
	root->childCnt = possible;		/* �ڽ� ��尳�� ���� */
	return bestValue;				/* bestValue �� ��ȯ */
};

/**
	�� �� : Maximize(struct treeNode* root)
	�� �� : ���� �ڽ� ���� eval���߿��� ���� ū ������ �����ϴ� �Լ�
*/
int TicTacToeAI::Maximize(struct treeNode* root)
{
	Position iList[9];			/* ���� �����ǿ��� ���� �� �ִ� ��ǥ ����, ��ġ ���� */
	int	bestValue = -10000;		/* besteval �� ���� */
	int	possible;				/* �Ѽ��ִ� ���� ���� ���� */
		
	possible = GetPossibleMove(iList);	/*���� ������ �� ��ǥ, ���� ���� */
		
	if( possible == 0 || CheckEnd() || root->depth == LAlevel )	/* �����Ѽ� ���ų�, ��������� eval ���� ����Ͽ� ���� */
	{
		return EvaluateBoard(root);
	}		

	for( int i = 0; i < possible; i++ )	/* ������ �� ��ŭ Minimax �˰����� ����Ͽ� ���� ��� */
	{
		root->next[i] = new Node;					/* ��� ���� �� �ʱ�ȭ */
		InitNode(root->next[i], root->depth+1);

		tttBoard.DoMove(iList[i].x , iList[i].y);	/* ������ ���� �� */		
		int newValue = Minimize(root->next[i]);		/* Min�Լ�ȣ��� ���� ���ؼ� */
		root->next[i]->eval = newValue;				/* ��忡 ���� */
		tttBoard.UndoMove();						/* �ξ��� ���� ���� */

		if( newValue > bestValue )				/* ���� eval���� best������ ũ�ٸ� */
		{				
			bestValue = newValue;				/* ���� �����ϰ� �ش簪���� ��尪�� ���� */
			root->eval = bestValue;	
		}		
	}
	root->childCnt = possible;					/* �ڽ� ��尳�� ���� */
	return bestValue;							/* bestValue �� ��ȯ */
};

/**
	lika
	�� �� : GetSymmetricEval()
	�� �� : Symmetric�� �κ��� Eval���� ���ϴ� �Լ�.
*/
void TicTacToeAI::GetSymmetricEval()
{
	int	check = 0;	/* ��Ī�� �˻� ���� */
	int k = 0;
	int temp = evaluation->possible;

	GameBoard tempBoard = tttBoard;	/* ������ ���� */

	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if (tttBoard.board[i][j] == ' ')
			{
				check = 0;
				for (int k = 0; k<temp; k++)
				{
					if (evaluation->x[k] == i && evaluation->y[k] == j)
						continue;
					tttBoard.DoMove(i, j);
					tempBoard.DoMove(evaluation->x[k], evaluation->y[k]);
					check = CheckSymmetric(tempBoard, tttBoard);	/* ��Ī�� �˻� */
					tempBoard.UndoMove();
					tttBoard.UndoMove();
					if (check == 1){		/* ��Ī�� �κ� �̶�� */
						evaluation->possible++;
						evaluation->x[evaluation->possible - 1] = i;
						evaluation->y[evaluation->possible - 1] = j;
						evaluation->eval[evaluation->possible - 1] = evaluation->eval[k];
					}
				}
			}
		}
	}
};

/**
	�� �� :	CheckSymmetric(GameBoard preBoard, GameBoard newBoard)
	�� �� : �Լ� ��Ī���� �˻��ϴ� �Լ�
*/
int TicTacToeAI::CheckSymmetric(GameBoard preBoard, GameBoard newBoard)
{
	int i, j, k, check = 0;

	char newboard[3][3];	/* �˻� ��� �������� ������ ���� */
	char copy[3][3];		
	char temp[3][3];

	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
		{
			copy[i][j] = preBoard.board[i][j];		/* ���� �������� ���� */
			newboard[i][j] = newBoard.board[i][j];	/* �˻� ��� �������� ���� */
		}

	 /* copy �������� �������� ȸ��, �� 3�� ȸ�� */
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)            
			for(k=0; k<3; k++)
				temp[j][k]=copy[j][k];

		for(j=0; j<3; j++)       
			for(k=0; k<3; k++)
				copy[2-k][j]=temp[j][k];
			
		if(CheckSameBoard(copy, newboard))	/* �ѹ� ȸ���Ҷ����� ������ �˻� */
			return 1;						/* ������ 1 ��ȯ */
	}

	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			temp[i][j]=copy[i][j];
	
	 /* copy �������� �¿�� ��Ī */
	for(i=0;i<3;i++)
	{
		copy[i][0]=temp[i][2];
		copy[i][2]=temp[i][0];
	}

	if(CheckSameBoard(copy, newboard))	/* ��Ī�� ������ �˻� */
		return 1;						/* ������ 1 ��ȯ */
	

	/* copy �������� �������� ȸ��, �� 3�� ȸ�� */
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)               
			for(k=0; k<3; k++)
				temp[j][k]=copy[j][k];

		for(j=0; j<3; j++)
			for(k=0; k<3; k++)
				copy[2-k][j]=temp[j][k];
			
		if(CheckSameBoard(copy, newboard))	/* �ѹ� ȸ���Ҷ����� ������ �˻� */
			return 1;						/* ������ 1 ��ȯ */
	}
	return 0;
};

/**
	�� �� : CheckSameBoard(char (*board1)[3], char (*board2)[3])
	�� �� :	���� �����ǰ� �˻��� �������� �޾ƿͼ� ��ġ�ϴ��� ���� �˻�
*/
int TicTacToeAI::CheckSameBoard(char (*board1)[3], char (*board2)[3])
{
	int i, j;
	int count = 0;

	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
			if(board1[i][j] == board2[i][j])
				count++;

	if(count == 9)	
		return 1;    /* ������ 1 ��ȯ */
	else			
		return 0;    /* �ٸ��� 0 ��ȯ */
};

/**
	�� �� : GetPossibleMove(Position* iList)
	�� �� : ���� �����ǿ��� ���� �Ѷ� �Ѽ��ִ� ���� ��ǥ��, �� ������ ����
*/
int TicTacToeAI::GetPossibleMove(Position* iList)
{
	int	iNum = 0;	/* ������ �� ���� ������ ���� */
	int	check = 0;	/* ��Ī�� �˻� ���� */
	int k=0;

	GameBoard tempBoard = tttBoard;	/* ������ ���� */
		
	for(int i=0; i<3; i++ )
	{
		for(int j=0; j<3; j++)
		{
			if( tttBoard.board[i][j] == ' ' )
			{
				check = 0;
				for(int k=0; k<iNum; k++)
				{
					tttBoard.DoMove(i, j);
					tempBoard.DoMove(iList[k].x, iList[k].y);
					check =	CheckSymmetric(tempBoard, tttBoard);	/* ��Ī�� �˻� */
					tempBoard.UndoMove();
					tttBoard.UndoMove();
					if(check == 1)		/* ��Ī�ȴٸ� ��ŵ */
						break;
				}
				
				if(!check)				/* �ƴ϶��, */
				{
					iList[iNum].x = i;		/* ���� x��ǥ, y��ǥ ���� */
					iList[iNum].y = j;
					iNum++;					/* ���� ���� */				
				}
			}
		}
	}			
	return iNum;	/* ���� ��ȯ */
};

/**
	�� �� : CheckEnd()
	�� �� : ���� ������ ���¸� ���� �ϴ� �Լ� 
*/
int TicTacToeAI::CheckEnd()
{
	tttBoard.CheckState();		
	if( tttBoard.state != GameBoard::STATE_PLAY )
	{
		tttBoard.state = GameBoard::STATE_PLAY;
		return 1;
	}
	else
		return 0;
}

/**
	�� �� : EvaluateBoard()
	�� �� : �ش� �����ǿ��� �̱���ִ� ������ �˻��ؼ� �򰡰��� ��ȯ���ִ� �Լ� 
*/
int TicTacToeAI::EvaluateBoard(struct treeNode* root)
{
	char calBoard[3][3];
	int eval = 0, k = 0;		
	int comA = 0, comB = 0;

	tttBoard.CheckState();
	if( tttBoard.state != GameBoard::STATE_PLAY )
	{
		if(tttBoard.state == GameBoard::STATE_WINA)
		{
			if(this->criterion == 'X')
				eval = 100 - root->depth;
			else
				eval = -100 + root->depth;
			tttBoard.state = GameBoard::STATE_PLAY;

			return eval;
		}
		else if(tttBoard.state == GameBoard::STATE_WINB)
		{
			if(this->criterion == 'X')
				eval = -100 + root->depth;
			else
				eval = 100 - root->depth;
			tttBoard.state = GameBoard::STATE_PLAY;

			return eval;
		}		
	}
	
	for(int i=0; i<3; i++)
		for(int j=0; j<3; j++)
			calBoard[i][j] = tttBoard.board[i][j];

	/* ���� 3��, ���� 3���� ���� X, O�� �̱���ִ� ���� ��� */
	for(int i=0;i<3;i++)
	{
		if( (calBoard[i][0]=='X' || calBoard[i][0]==' ') && 
			(calBoard[i][1]=='X' || calBoard[i][1]==' ') && 
			(calBoard[i][2]=='X' || calBoard[i][2]==' '))
			comA++;
		if( (calBoard[i][0]=='O' || calBoard[i][0]==' ') && 
			(calBoard[i][1]=='O' || calBoard[i][1]==' ') && 
			(calBoard[i][2]=='O' || calBoard[i][2]==' '))
			comB++;
		if( (calBoard[0][i]=='X' || calBoard[0][i]==' ') && 
			(calBoard[1][i]=='X' || calBoard[1][i]==' ') && 
			(calBoard[2][i]=='X' || calBoard[2][i]==' '))
			comA++;
		if( (calBoard[0][i]=='O' || calBoard[0][i]==' ') && 
			(calBoard[1][i]=='O' || calBoard[1][i]==' ') && 
			(calBoard[2][i]=='O' || calBoard[2][i]==' '))
			comB++;
	}
	
	/* ����, ������ �밢������ �̱���ִ� ���� ��� */
	if( (calBoard[0][0]=='X' || calBoard[0][0]==' ') && 
		(calBoard[1][1]=='X' || calBoard[1][1]==' ') && 
		(calBoard[2][2]=='X' || calBoard[2][2]==' ') )
		comA++;
	if( (calBoard[0][0]=='O' || calBoard[0][0]==' ') && 
		(calBoard[1][1]=='O' || calBoard[1][1]==' ') && 
		(calBoard[2][2]=='O' || calBoard[2][2]==' ') )
		comB++;

	if( (calBoard[0][2]=='X' || calBoard[0][2]==' ') && 
		(calBoard[1][1]=='X' || calBoard[1][1]==' ') && 
		(calBoard[2][0]=='X' || calBoard[2][0]==' ') )
		comA++;
	if( (calBoard[0][2]=='O' || calBoard[0][2]==' ') && 
		(calBoard[1][1]=='O' || calBoard[1][1]==' ') && 
		(calBoard[2][0]=='O' || calBoard[2][0]==' ') )
		comB++;

	/* ���� AI������ ��ǻ�� A���� B������ ���� �̱���ִ� ���� ����ؼ� ��ȯ */
	if(criterion == 'X')
		eval = comA-comB;
	else
		eval = comB-comA; 
	return eval;
};