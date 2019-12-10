#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���C��
class CObjGimmick : public CObj
{
public:
	CObjGimmick(float x, float y);
	~CObjGimmick() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void SetY(int y) { pj = y; }
	void SetX(int x) { pi = x; }
	void SetGimmickChange(bool b) { stop_flg2 = b; }
	
private:
	int m_map[MAP_X][MAP_Y];
	int gx;	//�A�C�e����X�ʒu�ۊǗp
	int gy; //�A�C�e����Y�ʒu�ۊǗp

	float m_vx; //�I�u�W�F�N�g�̈ړ��p�x�N�g��X
	float m_vy; //�I�u�W�F�N�g�̈ړ��p�x�N�g��Y

	bool gimmick_flg;
	bool gimmick_chg;
	bool stop_flg;
	bool stop_flg2;
	

	int pi;
	int pj;

	int h_count;
};
