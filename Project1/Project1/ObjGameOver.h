#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���C��
class CObjGameOver : public CObj
{
public:
	CObjGameOver() {};
	~CObjGameOver() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	int GO_time;	//GameOver�p�̃^�C���ϐ�
	bool Title_flag;	//�L�[����������Title�ɖ߂�p�̃t���O
};