#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���C��
class CObjMain : public CObj
{
	public:
		CObjMain(int map[100][100]);
		~CObjMain() {};
		void Init();	//�C�j�V�����C�Y
		void Action();	//�A�N�V����
		void Draw();	//�h���[
		void SetScrollX(float s) { m_scroll_x = s; }
		float GetScrollX() { return m_scroll_x; }
		void SetScrollY(float r) { m_scroll_y = r; }
		float GetScrollY() { return m_scroll_y; }
		
		void BlockHit(
			float *x, float *y, bool scroll_on_x,bool scroll_on_y,
			bool *up, bool *down, bool *left, bool *right,
			float *vx, float *vy, int *bt
		);
	private:
		int m_map[100][100];   //�}�b�v���
		float m_scroll_x;   //���E�X�N���[���p
		float m_scroll_y;   //�㉺�X�N���[���p
};