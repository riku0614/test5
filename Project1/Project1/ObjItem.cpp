//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjItem.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjItem::CObjItem(int map[100][100])
{
	memcpy(m_map, map, sizeof(int)*(100 * 100));
}

//�C�j�V�����C�Y
void CObjItem::Init()
{
	//�ϐ�������
	//ix = 0;
	//iy = 0;
}

//�A�N�V����
void CObjItem::Action()
{
	
}

//�h���[
void CObjItem::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�`��؂���ʒu
	src.m_top = 17.0f;
	src.m_left = 20.0f;
	src.m_right = src.m_left + 25.0f;
	src.m_bottom = src.m_top + 30.0f;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] == 3)
			{
				//�`��ݒ�ʒu
				dst.m_top = 64.0f;
				dst.m_left = 64.0f;
				dst.m_right = dst.m_left + 10.0f;
				dst.m_bottom = dst.m_top + 10.0f;

				Draw::Draw(7, &src, &dst, c, 0.0f);
			}
		}
	}
	
}