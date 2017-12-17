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

	//どっちのターンかを表すための画像　WINも含まれている
	HUDTexture.Load(_T("HUD.png"));
	HUDTexture.SetDivide(4, 1);
}

//描画に必要な情報を含んでいる関数
void GameState::Init()
{
	LoadSprite();
	LoadTexture();
}

//ゲーム遷移
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

//タイトル関数
void GameState::Title()
{
	DirectInput * pDI = DirectInput::GetInstansce();

	if (pDI->MouseButtonJustPressed(MOUSE_BOTTON_LEFT))
	{
		gameSeq = MAIN;
	}
}

//ゲームメイン関数
void GameState::Main()
{
	draw();//描画するための関数

	DirectInput * pDI = DirectInput::GetInstansce();

	Vector2<int> mousePos = pDI->MousePosition();

	int mouseX = mousePos.X();
	int mouseY = mousePos.Y();

	//マウスの座標をピクセルで割ることによって配列の番号を特定
	int MapX = mouseX / PIXEL;
	int MapY = mouseY / PIXEL;

	if (pDI->KeyJustPressed(DIK_A))
	{
	}
	if (pDI->MouseButtonJustPressed(MOUSE_BOTTON_RIGHT))
	{
	}

	//プレイヤーターンを決めるswitch文
	PlayerTurn NextTurn = (playerTurn == BLACK_TURN) ? WHITE_TURN : BLACK_TURN;
	OthelloMap Color = (playerTurn == BLACK_TURN) ? BLACK : WHITE;
	OthelloMap OtherColor = (Color == BLACK) ? WHITE : BLACK;
	switch (playerTurn)
	{
	case SETUP://オセロマップの配列を初期化するために付け加えたもの
		SetUpGame();//この関数でゲーム内容の初期化
		playerTurn = BLACK_TURN;
		break;
	case BLACK_TURN://黒のターンです
	case WHITE_TURN://白のターンです
		pass = true;

		for (int y = 0; y < MAP_MAX; y++)
		{
			for (int x = 0; x < MAP_MAX; x++)
			{
				if (othellomap[y][x] == NONE)
				{
					//for文でNONEコマの周りを見る
					for (int dy = -1; dy < 2; dy++)
					{
						for (int dx = -1; dx < 2; dx++)
						{
							//次のコマが別の色だったら
							if (othellomap[y + dy][x + dx] == OtherColor)
							{
								//またその先を見る
								for (int count = 2; count < 8; count++)
								{
									int CheckY = y + (dy*count);
									int CheckX = x + (dx*count);

									//空白が入ったら
									if (othellomap[CheckY][CheckX] == NONE || othellomap[CheckY][CheckX] == PUTON)
									{
										//チェック中断
										break;
									}
									//配列外じゃなかったら
									else if (8 > CheckY &&CheckY >= 0 && 8 > CheckX&&CheckX >= 0)
									{
										//終着点が自分のターンのコマだったら
										if (othellomap[CheckY][CheckX] == Color)
										{
											//最初に見たNONEコマを置ける場所にする
											othellomap[y][x] = PUTON;
											pass = false;

										}

									}
									else
									{
										break;
									}
								}
							}
						}
					}
				}
			}
		}


		if (pDI->MouseButtonJustPressed(MOUSE_BOTTON_LEFT) && (othellomap[MapY][MapX] == PUTON))
		{
			othellomap[MapY][MapX] = Color;

			//for文で置いたコマの周りを見る
			for (int dy = -1; dy < 2; dy++)
			{
				for (int dx = -1; dx < 2; dx++)
				{
					//次のコマが別の色だったら
					if (othellomap[MapY + dy][MapX + dx] == OtherColor)
					{
						//またその先を見る
						for (int count = 2; count < 8; count++)
						{
							int CheckY = MapY + (dy*count);
							int CheckX = MapX + (dx*count);

							//これは配列外を及ぼさないようにするための処理
							if (8 > CheckY &&CheckY >= 0 && 8 > CheckX&&CheckX >= 0)
							{
								//チェック途中に空があったら
								if (othellomap[CheckY][CheckX] == NONE || othellomap[CheckY][CheckX] == PUTON)
								{
									//チェック中断
									break;
								}
								//もし終着点のコマの色が自分のターンの色だったら
								else if (othellomap[CheckY][CheckX] == Color)
								{
									for (int Change = count - 1; Change > 0; Change--)
									{
										othellomap[MapY + (dy * Change)][MapX + (dx * Change)] = Color;
									}
									break;
								}
							}
							else
							{
								break;
							}
						}
					}
				}
			}
			for (int y = 0; y < MAP_MAX; y++)
			{
				for (int x = 0; x < MAP_MAX; x++)
				{
					if (othellomap[y][x] == PUTON)
					{
						othellomap[y][x] = NONE;
					}
				}
			}

			playerTurn = NextTurn;
		}
		break;
	case RESULT:
		//勝利したほうにWINの文字の表示
		sprite.SetPos(700, 600);
		HUDTexture.SetNum(3, 0);
		sprite.Draw(HUDTexture);
		break;
	}


}

//初期描画のための関数
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
			case BLACK:
				sprite.SetPos(PIXEL / 2 + (PIXEL*x), PIXEL / 2 + (PIXEL*y));
				PieceTexture.SetNum(0, 0);
				sprite.Draw(PieceTexture);
				break;
			case WHITE:
				sprite.SetPos(PIXEL / 2 + (PIXEL*x), PIXEL / 2 + (PIXEL*y));
				PieceTexture.SetNum(1, 0);
				sprite.Draw(PieceTexture);
				break;
			case PUTON:
				sprite.SetPos(PIXEL / 2 + (PIXEL*x), PIXEL / 2 + (PIXEL*y));
				BoadTexture.SetNum(0, 0);
				sprite.Draw(BoadTexture);
				break;
			}
		}
	}

	//今どっちのターンかを示すポイントの描画
	int y = -100;
	switch (playerTurn)
	{
	case BLACK_TURN:
		y = 600;
		break;

	case WHITE_TURN:
		y = 700;
		break;
	}
	sprite.SetPos(700,y);
	HUDTexture.SetNum(2, 0);
	sprite.Draw(HUDTexture);
	//--------------------------------------

	//黒の文字の描画
	sprite.SetPos(800, 600);
	HUDTexture.SetNum(0, 0);
	sprite.Draw(HUDTexture);

	//白の文字の描画
	sprite.SetPos(800, 700);
	HUDTexture.SetNum(1, 0);
	sprite.Draw(HUDTexture);
}