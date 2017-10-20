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

void GameState::SetUpGame()
{
	for (int y = 0; y < MAP_MAX; y++)
	{
		for (int x = 0; x < MAP_MAX; x++)
		{
			GameMap[y][x] = 0;
		}
	}
}
void GameState::Main()
{
	//2�����z��ŔՖʂ�`��
	for (int y = 0; y < MAP_MAX; y++)
	{
		for (int x = 0; x < MAP_MAX; x++)
		{
			sprite.SetPos(PIXEL / 2 + (PIXEL*x), PIXEL / 2 + (PIXEL*y));
			BoadTexture.SetNum(1, 0);
			sprite.Draw(BoadTexture);
		}
	}
}