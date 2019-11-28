#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���C��
class CObjRoom : public CObj
{
public:
	CObjRoom(int map[25][25]);
	~CObjRoom() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void SetScrollX(float s) { m_scroll_x = s; }//X�����̃X�N���[��
	float GetScrollX() { return m_scroll_x; }
	void SetScrollY(float r) { m_scroll_y = r; }//Y�����ւ̃X�N���[��
	float GetScrollY() { return m_scroll_y; }
	int m_map[25][25];//�}�b�v���u���b�N���iX=�P�Q�AY=�P�O�j



private:

	float m_scroll_x;   //���E�X�N���[���p
	float m_scroll_y;   //�㉺�X�N���[���p



};