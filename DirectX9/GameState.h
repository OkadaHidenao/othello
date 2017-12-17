#pragma once
#include"Direct3D.h"
#include"DirectInput.h"
#include"Sprite.h"
#include"Texture.h"

#define MAP_MAX 8
#define PIXEL 72

//ゲームを分岐するための列挙型
enum Sequence
{
	TITLE,
	MAIN
};

enum PlayerTurn
{
	SETUP,
	BLACK_TURN,
	WHITE_TURN,
	RESULT
};

enum OthelloMap
{
	NONE,
	BLACK,
	WHITE,
	PUTON
};

class GameState
{
private:
	

	//スプライト
	Sprite sprite;

	//テクスチャ
	Texture PieceTexture;	//黒と白
	Texture BoadTexture;	//盤面
	Texture HUDTexture;		//どっちのターンかを描画するためのテクスチャ
	
	OthelloMap othellomap[MAP_MAX][MAP_MAX];
	Sequence gameSeq=TITLE;

	PlayerTurn playerTurn=SETUP;

	int othelloFlag[MAP_MAX][MAP_MAX];

	int Mx, My;
	bool pass;
	
public:
	GameState();
	~GameState();

	void LoadSprite();
	void LoadTexture();
	void Init();//LoadSprite関数とLoadTexture関数を格納するための関数

	void SetUpGame();	//ゲームの初期化の関数
	void Update();		//ゲームの今の状態を見る関数

	void Title();
	void Main();

	void draw();
};