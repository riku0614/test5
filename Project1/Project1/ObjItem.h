#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���C��
class CObjItem : public CObj
{
public:
	CObjItem(int map[100][100]);
	~CObjItem() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	int m_map[100][100];//�}�b�v���
	//int ix;	//�A�C�e����X�ʒu�ۊǗp
	//int iy; //�A�C�e����Y�ʒu�ۊǗp
};
