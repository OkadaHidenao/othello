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


enum OthelloMap
{
	NONE,
	BLACK,
	WHITE
};

class GameState
{
private:
	OthelloMap othellomap[MAP_MAX][MAP_MAX];

	//スプライト
	Sprite sprite;

	//テクスチャ
	Texture PieceTexture;	//黒と白
	Texture BoadTexture;	//盤面

	Sequence gameSeq;
	
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