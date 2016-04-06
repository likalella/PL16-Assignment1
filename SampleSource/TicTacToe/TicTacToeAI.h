#include "GameBoard.h"

class TicTacToeAI
{
public:
	GameBoard tttBoard;		/* ������ ���� ���� ���� �� */

	int		LAlevel;		/* Look Ahead ���� */
	char	criterion;		/* �� AI �����ϴ� ���� ��ǻ�� */
	int		bestX;			/* ������ X ��ǥ */
	int		bestY;			/* ������ Y ��ǥ */
	Node* root;				/* ����� ��� ����ü */
	Evaluation* evaluation;	/* lika : Eval ����� ����ü */

public :

	TicTacToeAI(GameBoard board);		
	void InitNode(Node* node, int inDepth);		/* AI �⺻������ �ʱ�ȭ */
	Node* GetRootNode();						/* Tree �� ����ϱ����� Node ��ȯ */
	Evaluation* GetEvaluation();				/* lika : GameBoard�� Eval�� ����ϱ� ���� Evaluation ��ȯ */
	void GetBestMove();							/* ������ ��ǥ�� ���� */	
	void GetSymmeticEval();						/* lika: Symmetic�� �κ��� Eval���� ���� */
	int Minimize(struct treeNode* root);		/* Eval ���� Min ���� ���� */	
	int Maximize(struct treeNode* root);		/* Eval ���� Max ���� ���� */
	int CheckSymmetric(GameBoard preBoard, GameBoard newBoard);	/* ���Ӻ��� ��Ī�� �˻� */
	int CheckSameBoard(char (*board1)[3], char (*board2)[3]);	/* ��Ī�� �˻� �� ���尡 ��ġ�ϴ��� �˻� */
	int GetPossibleMove(Position* iList);						/* ���� ������¿��� �����ִ� ��ǥ ���� �˻� */
	int CheckEnd();								/* ������ �������� �˻� */
	int EvaluateBoard(struct treeNode* root);						/* ���� �������� Eval(�򰡰�) ��� */

};