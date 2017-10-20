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
	MAIN,
	GAMEOVER,
	GAMECLEAR
};

class GameState
{
private:
	int GameMap[MAP_MAX][MAP_MAX];

	//スプライト
	Sprite sprite;

	//テクスチャ
	Texture PieceTexture;
	Texture BoadTexture;

public:
	GameState();
	~GameState();

	void LoadSprite();
	void LoadTexture();
	void Init();

	void SetUpGame();//ゲームの初期化の関数

	void Main();
};