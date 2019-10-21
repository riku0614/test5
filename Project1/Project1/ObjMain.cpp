//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjMain.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjMain::CObjMain(int map[10][10])
{
	memcpy(m_map, map, sizeof(int)*(10 * 10));
}

//�C�j�V�����C�Y
void CObjMain::Init()
{
	
}

//�A�N�V����
void CObjMain::Action()
{
	
}

//�h���[
void CObjMain::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	for (int i = 0; i < 10; i++)
	{



		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//�\���ʒu�̐ݒ�
				dst.m_top = i * 64.0f;
				dst.m_left = j * 64.0f;
				dst.m_right = dst.m_left + 64.0;
				dst.m_bottom = dst.m_top + 64.0;
				if (m_map[i][j] == 2)
				{
					//�X�^�[�g�u���b�N
					BlockDraw(320.0f + 64.0f, 0.0f, &dst, c);
				}
				else if (m_map[i][j] == 3)
				{
					//�S�[���u���b�N
					BlockDraw(320.0f + 64.0f, 64.0f, &dst, c);
				}
				else if (m_map[i][j] == 4)
				{
					;
				}
				else
				{
					BlockDraw(320.0f, 0.0f, &dst, c);

				}
			}
		}

	}
}
