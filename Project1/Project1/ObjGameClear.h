#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���C��
class CObjGameClear : public CObj
{
public:
	CObjGameClear() {};
	~CObjGameClear() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:

	int m_time;	//�e���b�v�o���p
	//bool ED;	//ED1�o���p
};