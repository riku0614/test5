//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

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

/*BlockDrawMethod�֐�
  �����P�@float   x   :���\�[�X�؂���ʒuX
  �����Q�@float   y   :���\�[�X�؂���ʒuY
  �����R�@RECT_F* dst :�`��ʒu
  �����S�@float   c[] :�J���[���
  �u���b�N��64X64����`��p�B���\�[�X�؂���ʒu�̂�x,y��
  �ݒ�ł���*/



	


//�h���[
void CObjMain::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_map[i][j] > 0)
			{
				//�\���ʒu�̐ݒ�
				dst.m_top = i * 64.0f;
				dst.m_left = j * 64.0f;
				dst.m_right = dst.m_left + 64.0;
				dst.m_bottom = dst.m_top + 64.0;

				if (m_map[i][j] == 1)
				{
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = src.m_left + 64.0f;
					src.m_bottom = src.m_top + 64.0f;

					Draw::Draw(0, &src, &dst, c, 0.0f);
				}
				
			}
		}

	}
}
