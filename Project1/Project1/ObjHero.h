#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define Status (8)

//�I�u�W�F�N�g�F��l��
class CObjHero : public CObj
{
public:
	CObjHero() {};
	~CObjHero() {};
	void Init();   //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw();   //�h���[

	float GetX() { return m_px; }    //��l���̈ʒu��n��
	float GetY() { return m_py; }

	float GetVY() { return m_vy; }   //��l���̃x�N�g����n��
	float GetVX() { return m_vx; }

	int GetLife() { return m_hero_life; }

	int GetBT() { return m_block_type; }//�������Ă���u���b�N�̎�ނ�n��



	void SetUp(bool b) { m_hit_up = b; }      //�㉺���E�̃u���b�N�̓����蔻��̃t���O 
	void SetDown(bool b) { m_hit_down = b; }
	void SetLeft(bool b) { m_hit_left = b; }
	void SetRight(bool b) { m_hit_right = b; }

	void SetBT(int t) { m_block_type = t; }   //�������Ă���u���b�N�̎�ނ�ݒ肷��

	void SetX(float x) { m_px = x; }       //��l���̈ʒu��ݒ�
	void SetY(float y) { m_py = y; }
	void SetVY(float vy) { m_vy = vy; }    //��l���̃x�N�g����ݒ�
	void SetVX(float vx) { m_vx = vx; }

	void SetHeroStop(bool f) { m_hero_stop = f; }

	bool Getflag() { return peperon_flag;}
	void SetFlug(bool f) { peperon_flag = f; }
	bool Getflag_2() { return peperon_flag_2; }
	void SetFlug_2(bool f) { peperon_flag_2 = f; }
	bool Getflag_3() { return peperon_flag_3; }
	void SetFlug_3(bool f) { peperon_flag_3 = f; }

	bool SetItemflag() { return use_Item_flag; }
	bool SetItemflag_2() { return use_Item_flag_2; }
	bool SetItemflag_3() { return use_Item_flag_3; }

	bool action_flag() { return Conflict_flag; }
	bool action_flag2() { return Conflict_flag2; }

	int GetKeyID() { return m_id; }
	int GatHealID() { return h_id; }
	bool GetEnemyFlag() { return enemy_flg; }
	int GetBarID() { return b_id; }

	void SetHitFlagX(bool h) { hit_flag_x = h; }
	void SetHitFlagY(bool h) { hit_flag_y = h; }
private:
	float save[Status][2];

	int k_id;//�A�C�e���i���j��ID
	int h_id;//�񕜃A�C�e����ID
	int b_id;//�o�[����ID
	int m_id;//�L�����N�^�[ID
	float m_px; //�ʒu
	float m_py;
	float m_vx; //�ړ��x�N�g��
	float m_vy;
	float m_posture; //�p��
	float m_stamina_limid;//�X�^�~�i�̌��E�l

	int m_hero_life;//��l���̗̑�
	int m_ani_time;  //�A�j���[�V�����t���[������Ԋu
	int m_ani_frame; //�`��t���[��

	bool m_hero_stop;

	float m_speed_power;        //�X�s�[�h�p���[
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l

	int m_ani_move;//�L�����N�^�[�̓���
	
    //block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//�A�C�e���Ƃ̏Փˊm�F�p
	bool mi_hit_up;
	bool mi_hit_down;
	bool mi_hit_left;
	bool mi_hit_right;

	int m_time;//���G����
	bool m_flg;//���G�t���O

	//����ł���u���b�N�̎�ފm�F�p
	int m_block_type;

	bool peperon_flag; //�A�C�e��1�ԏ����t���O�p
	bool peperon_flag_2; //�A�C�e��2�ԏ����t���O�p
	bool peperon_flag_3; //�A�C�e��3�ԏ����t���O�p

	bool use_Item_flag; //�A�C�e��1�Ԏg�p�t���O
	bool use_Item_flag_2;//�A�C�e��2�Ԏg�p�t���O
	bool use_Item_flag_3;//�A�C�e��3�Ԏg�p�t���O

	bool Conflict_flag; //�G�Ɠ����������𔻒f����t���O
	bool Conflict_flag2; 

	float px, py;//��_

	bool stey_flg1;
	bool stey_flg2;
	bool stey_flg3;

	bool enemy_flg;

	bool hit_flag_x;

	bool hit_flag_y;
};