#include"GameState.h"

GameState::GameState()
{
	//�R���X�g���N�^
}
GameState::~GameState()
{
	//�f�X�g���N�^
}

//�`��ɕK�v�ȃX�v���C�g
void GameState::LoadSprite()
{
	//�I�Z���ɕK�v�ȑf�ނ̃X�v���C�g
	sprite.SetAlpha(1);
	sprite.SetAngle(0);
	sprite.SetSize(PIXEL,PIXEL);
}

//�`��ɕK�v�ȃe�N�X�`��
void GameState::LoadTexture()
{
	//���ƍ��̉摜
	PieceTexture.Load(_T("piece.png"));
	PieceTexture.SetDivide(2, 1);

	//�ՖʂƂ��̉摜
	BoadTexture.Load(_T("bord.png"));
	BoadTexture.SetDivide(2, 1);
}
//�`��ɕK�v�ȏ����܂�ł���֐�
void GameState::Init()
{
	LoadSprite();
	LoadTexture();
}

void GameState::Update()
{
	switch (gameSeq)
	{
	case TITLE:
		GameState::Title();
		break;
	case MAIN:
		GameState::Main();
		break;
	}
}

//�Q�[�����e�������̊֐�
void GameState::SetUpGame()
{
	for (int y = 0; y < MAP_MAX; y++)
	{
		for (int x = 0; x < MAP_MAX; x++)
		{
			if (y==3&&x==3||y==4&&x==4)
			{
				othellomap[y][x] = WHITE;
			}
			else if (y == 3 && x == 4 || y == 4 && x == 3)
			{
				othellomap[y][x] = BLACK;
			}
			else
			{
				othellomap[y][x] = NONE;
			}
		}
	}
}

void GameState::Title()
{
	DirectInput * pDI = DirectInput::GetInstansce();

	SetUpGame();//���̊֐��ŃQ�[�����e�̏�����

	if (pDI->KeyJustPressed(DIK_RETURN))
	{
		gameSeq = MAIN;
	}
}
//�Q�[�����C���֐�
void GameState::Main()
{
	draw();

	DirectInput * pDI = DirectInput::GetInstansce();

	Vector2<int> mousePos = pDI->MousePosition();

	int mX= mousePos.X();
	int mY= mousePos.Y();

	if (pDI->KeyJustPressed(DIK_A))
	{
	}
	if (pDI->MouseButtonJustPressed(MOUSE_BOTTON_RIGHT))
	{
	}

	for (int y = 0; y < MAP_MAX; y++)
	{
		for (int x = 0; x < MAP_MAX; x++)
		{
			if (pDI->KeyJustPressed(DIK_A))
			{
				othellomap[5][6] = WHITE;
			}
		}
	}

}

void GameState::draw()
{
	//2�����z��ŔՖʂ�`��
	for (int y = 0; y < MAP_MAX; y++)
	{
		for (int x = 0; x < MAP_MAX; x++)
		{
			sprite.SetPos(PIXEL / 2 + (PIXEL*x), PIXEL / 2 + (PIXEL*y));
			BoadTexture.SetNum(1, 0);
			sprite.Draw(BoadTexture);
			switch (othellomap[y][x])
			{
			case WHITE:
				sprite.SetPos(PIXEL / 2 + (PIXEL*x), PIXEL / 2 + (PIXEL*y));
				PieceTexture.SetNum(0, 0);
				sprite.Draw(PieceTexture);
				break;
			case BLACK:
				sprite.SetPos(PIXEL / 2 + (PIXEL*x), PIXEL / 2 + (PIXEL*y));
				PieceTexture.SetNum(1, 0);
				sprite.Draw(PieceTexture);
				break;
			}
		}
	}
}