#pragma once
#include"Direct3D.h"
#include"DirectInput.h"
#include"Sprite.h"
#include"Texture.h"

#define MAP_MAX 8
#define PIXEL 72

//�Q�[���𕪊򂷂邽�߂̗񋓌^
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

	//�X�v���C�g
	Sprite sprite;

	//�e�N�X�`��
	Texture PieceTexture;
	Texture BoadTexture;

public:
	GameState();
	~GameState();

	void LoadSprite();
	void LoadTexture();
	void Init();

	void SetUpGame();//�Q�[���̏������̊֐�

	void Main();
};