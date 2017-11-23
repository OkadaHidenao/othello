#pragma once

template <class T>
class Vector2
{
private:
	T x;
	T y;

public:

	Vector2()
	{

	}

	//�l�̐ݒ�֐�
	void Set(T x_, T y_)
	{
		x = x_;
		y = y_;
	}

	//�l�̎擾�̊֐�
	T& X() { return x; }	
	T& Y() { return y; }

	//���Z�q�̃I�[�o�[���[�h
	//���������̂ݒ�`

	//������const�́@���̃����o�֐������s���邱�Ƃɂ����
	//�N���X���̃����o�ϐ��̒l�ɕύX���N���Ȃ����Ƃ�ۏ؂���
	//�t�Ɍ����Ƃ��̊֐����Ń����o�ϐ��̕ύX���֎~�����
	//�@�N���X�C���X�^���X��const�t���Ő錾����Ă���Ƃ�
	//�@����const�����������o�֐��������s�ł��Ȃ��Ȃ�
	//�@����ɂ����const�̐����̃f�[�^�̒萔�����ۂ����
	const Vector2<T> operator+(const Vector2<T>& other)const
	{
		Vector2<T> tmp;//��Ɨp�̈ꎞ�ϐ��@���������ʂ�����

		//�����Z����
		tmp.Set(x + other.x, y + other.y);
		return tmp;
	}

	const Vector2<T> operator - (const Vector2<T>& other)const
	{
		Vector2<T>tmp;
		tmp.Set(x - other.x, y - other.y);
		return tmp;
	}

	//���Z���
	const Vector2<T> operator += (const Vector2<T>& other)const
	{
		x += other.x;
		y += other.y;

		return *(this);
	}
	const Vector2<T> operator -= (const Vector2<T>& other)const
	{
		x -= other.x;
		y -= other.y;

		return *(this);
	}

	//�������f
	const bool operator == (const Vector2<T> other)const
	{
		return (x == ohter.x&&y == other.y);
	}
};