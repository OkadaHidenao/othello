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

	//�X�v���C�g
	Sprite sprite;

	//�e�N�X�`��
	Texture PieceTexture;	//���Ɣ�
	Texture BoadTexture;	//�Ֆ�

	Sequence gameSeq;
	
public:
	GameState();
	~GameState();

	void LoadSprite();
	void LoadTexture();
	void Init();//LoadSprite�֐���LoadTexture�֐����i�[���邽�߂̊֐�

	void SetUpGame();	//�Q�[���̏������̊֐�
	void Update();		//�Q�[���̍��̏�Ԃ�����֐�

	void Title();
	void Main();

	void draw();
};