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

//ゲーム内容初期化の関数
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

	SetUpGame();//この関数でゲーム内容の初期化

	if (pDI->KeyJustPressed(DIK_RETURN))
	{
		gameSeq = MAIN;
	}
}
//ゲームメイン関数
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
	//2次元配列で盤面を描画
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