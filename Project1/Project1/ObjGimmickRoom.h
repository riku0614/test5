#pragma once
#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���C��
class CObjGimmickRoom : public CObj
{
public:
	CObjGimmickRoom(float x, float y);
	~CObjGimmickRoom() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void SetY(int y) { pj = y; }
	void SetX(int x) { pi = x; }


private:

	int r_map[ROOM_X][ROOM_Y];//�}�b�v���
	int gx;	//�A�C�e����X�ʒu�ۊǗp
	int gy; //�A�C�e����Y�ʒu�ۊǗp

	float m_vx; //�I�u�W�F�N�g�̈ړ��p�x�N�g��X
	float m_vy; //�I�u�W�F�N�g�̈ړ��p�x�N�g��Y

	bool gimmick_flg;
	bool stop_flg;

	int pi;
	int pj;

	int h_count;
};
