#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���C��
class CObjGimmick : public CObj
{
public:
	CObjGimmick(int map[MAP_X][MAP_Y]);
	~CObjGimmick() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[


private:
	int m_map[MAP_X][MAP_Y];//�}�b�v���
	int ix;	//�A�C�e����X�ʒu�ۊǗp
	int iy; //�A�C�e����Y�ʒu�ۊǗp

	float m_px;  //�I�u�W�F�N�g�̈ʒuX
	float m_py;  //�I�u�W�F�N�g�̈ʒuY
	float m_vx; //�I�u�W�F�N�g�̈ړ��p�x�N�g��X
	float m_vy; //�I�u�W�F�N�g�̈ړ��p�x�N�g��Y

	bool gimmick_flg;
	bool stop_flg;

	int pi;
	int pj;

	int h_count;
};
