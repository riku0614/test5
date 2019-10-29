#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjEnemy : public CObj
{
public:
	CObjEnemy(float x, float y);;
	~CObjEnemy() {};
	void Init();   //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw();   //�h���[
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }
private:
	float m_px;  //�I�u�W�F�N�g�̈ʒuX
	float m_py;  //�I�u�W�F�N�g�̈ʒuY
	float m_vx; //�I�u�W�F�N�g�̈ړ��p�x�N�g��X
	float m_vy; //�I�u�W�F�N�g�̈ړ��p�x�N�g��Y
	float m_posture; //�p��
	bool m_flg;//�Ǐ]�ړ��̊Ǘ��p�t���O

		//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
};