#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���C��
class CObjMain : public CObj
{
	public:
		CObjMain(int map[10][10]);
		~CObjMain() {};
		void Init();	//�C�j�V�����C�Y
		void Action();	//�A�N�V����
		void Draw();	//�h���[
	private:
		int m_map[10][10];   //�}�b�v���
		void BlockDraw(float x, float y, RECT_F* dst, float c[]);
		
};