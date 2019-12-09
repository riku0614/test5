#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���C��
class CObjItem : public CObj
{
public:
	CObjItem(float x, float y);
	~CObjItem() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	//void SetFlag(bool b) { stop_flg = b; }
	
private:
	int m_map[MAP_X][MAP_Y];//�}�b�v���
	int ix;	//�A�C�e����X�ʒu�ۊǗp
	int iy; //�A�C�e����Y�ʒu�ۊǗp
	float m_scroll_x;   //���E�X�N���[���p
	float m_scroll_y;   //�㉺�X�N���[���p

	int r_map[ROOM_X][ROOM_Y];
	float m_px;  //�I�u�W�F�N�g�̈ʒuX
	float m_py;  //�I�u�W�F�N�g�̈ʒuY
	float m_vx; //�I�u�W�F�N�g�̈ړ��p�x�N�g��X
	float m_vy; //�I�u�W�F�N�g�̈ړ��p�x�N�g��Y

		//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	bool stop_flg;
	//bool hit_flg;

};
