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
	

	//�X�v���C�g
	Sprite sprite;

	//�e�N�X�`��
	Texture PieceTexture;	//���Ɣ�
	Texture BoadTexture;	//�Ֆ�
	Texture HUDTexture;		//�ǂ����̃^�[������`�悷�邽�߂̃e�N�X�`��
	
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
	void Init();//LoadSprite�֐���LoadTexture�֐����i�[���邽�߂̊֐�

	void SetUpGame();	//�Q�[���̏������̊֐�
	void Update();		//�Q�[���̍��̏�Ԃ�����֐�

	void Title();
	void Main();

	void draw();
};