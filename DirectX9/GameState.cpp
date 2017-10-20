#include"GameState.h"

GameState::GameState()
{
	//コンストラクタ
}
GameState::~GameState()
{
	//デストラクタ
}

//描画に必要なスプライト
void GameState::LoadSprite()
{
	//オセロに必要な素材のスプライト
	sprite.SetAlpha(1);
	sprite.SetAngle(0);
	sprite.SetSize(PIXEL,PIXEL);
}

//描画に必要なテクスチャ
void GameState::LoadTexture()
{
	//白と黒の画像
	PieceTexture.Load(_T("piece.png"));
	PieceTexture.SetDivide(2, 1);

	//盤面とかの画像
	BoadTexture.Load(_T("bord.png"));
	BoadTexture.SetDivide(2, 1);
}
//描画に必要な情報を含んでいる関数
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
	//2次元配列で盤面を描画
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