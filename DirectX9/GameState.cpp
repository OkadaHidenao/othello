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

	//�ǂ����̃^�[������\�����߂̉摜�@WIN���܂܂�Ă���
	HUDTexture.Load(_T("HUD.png"));
	HUDTexture.SetDivide(4, 1);
}

//�`��ɕK�v�ȏ����܂�ł���֐�
void GameState::Init()
{
	LoadSprite();
	LoadTexture();
}

//�Q�[���J��
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

//�Q�[�����e�������̊֐�
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

//�^�C�g���֐�
void GameState::Title()
{
	DirectInput * pDI = DirectInput::GetInstansce();

	if (pDI->MouseButtonJustPressed(MOUSE_BOTTON_LEFT))
	{
		gameSeq = MAIN;
	}
}

//�Q�[�����C���֐�
void GameState::Main()
{
	draw();//�`�悷�邽�߂̊֐�

	DirectInput * pDI = DirectInput::GetInstansce();

	Vector2<int> mousePos = pDI->MousePosition();

	int mouseX = mousePos.X();
	int mouseY = mousePos.Y();

	//�}�E�X�̍��W���s�N�Z���Ŋ��邱�Ƃɂ���Ĕz��̔ԍ������
	int MapX = mouseX / PIXEL;
	int MapY = mouseY / PIXEL;

	if (pDI->KeyJustPressed(DIK_A))
	{
	}
	if (pDI->MouseButtonJustPressed(MOUSE_BOTTON_RIGHT))
	{
	}

	//�v���C���[�^�[�������߂�switch��
	PlayerTurn NextTurn = (playerTurn == BLACK_TURN) ? WHITE_TURN : BLACK_TURN;
	OthelloMap Color = (playerTurn == BLACK_TURN) ? BLACK : WHITE;
	OthelloMap OtherColor = (Color == BLACK) ? WHITE : BLACK;
	switch (playerTurn)
	{
	case SETUP://�I�Z���}�b�v�̔z������������邽�߂ɕt������������
		SetUpGame();//���̊֐��ŃQ�[�����e�̏�����
		playerTurn = BLACK_TURN;
		break;
	case BLACK_TURN://���̃^�[���ł�
	case WHITE_TURN://���̃^�[���ł�
		pass = true;

		for (int y = 0; y < MAP_MAX; y++)
		{
			for (int x = 0; x < MAP_MAX; x++)
			{
				if (othellomap[y][x] == NONE)
				{
					//for����NONE�R�}�̎��������
					for (int dy = -1; dy < 2; dy++)
					{
						for (int dx = -1; dx < 2; dx++)
						{
							//���̃R�}���ʂ̐F��������
							if (othellomap[y + dy][x + dx] == OtherColor)
							{
								//�܂����̐������
								for (int count = 2; count < 8; count++)
								{
									int CheckY = y + (dy*count);
									int CheckX = x + (dx*count);

									//�󔒂���������
									if (othellomap[CheckY][CheckX] == NONE || othellomap[CheckY][CheckX] == PUTON)
									{
										//�`�F�b�N���f
										break;
									}
									//�z��O����Ȃ�������
									else if (8 > CheckY &&CheckY >= 0 && 8 > CheckX&&CheckX >= 0)
									{
										//�I���_�������̃^�[���̃R�}��������
										if (othellomap[CheckY][CheckX] == Color)
										{
											//�ŏ��Ɍ���NONE�R�}��u����ꏊ�ɂ���
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

			//for���Œu�����R�}�̎��������
			for (int dy = -1; dy < 2; dy++)
			{
				for (int dx = -1; dx < 2; dx++)
				{
					//���̃R�}���ʂ̐F��������
					if (othellomap[MapY + dy][MapX + dx] == OtherColor)
					{
						//�܂����̐������
						for (int count = 2; count < 8; count++)
						{
							int CheckY = MapY + (dy*count);
							int CheckX = MapX + (dx*count);

							//����͔z��O���y�ڂ��Ȃ��悤�ɂ��邽�߂̏���
							if (8 > CheckY &&CheckY >= 0 && 8 > CheckX&&CheckX >= 0)
							{
								//�`�F�b�N�r���ɋ󂪂�������
								if (othellomap[CheckY][CheckX] == NONE || othellomap[CheckY][CheckX] == PUTON)
								{
									//�`�F�b�N���f
									break;
								}
								//�����I���_�̃R�}�̐F�������̃^�[���̐F��������
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
		//���������ق���WIN�̕����̕\��
		sprite.SetPos(700, 600);
		HUDTexture.SetNum(3, 0);
		sprite.Draw(HUDTexture);
		break;
	}


}

//�����`��̂��߂̊֐�
void GameState::draw()
{
	//2�����z��ŔՖʂ�`��
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

	//���ǂ����̃^�[�����������|�C���g�̕`��
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

	//���̕����̕`��
	sprite.SetPos(800, 600);
	HUDTexture.SetNum(0, 0);
	sprite.Draw(HUDTexture);

	//���̕����̕`��
	sprite.SetPos(800, 700);
	HUDTexture.SetNum(1, 0);
	sprite.Draw(HUDTexture);
}