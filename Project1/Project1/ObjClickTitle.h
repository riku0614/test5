#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l��
class CObjClickTitle : public CObj
{
public:
	CObjClickTitle() {};
	~CObjClickTitle() {};
	void Init();   //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw();   //�h���[
private:
	float m_yj;	//���ړ��ϐ�
	bool m_f;	//��󐧌�p
};