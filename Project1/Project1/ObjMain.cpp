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

CObjMain::CObjMain(int map[100][100])
{
	memcpy(m_map, map, sizeof(int)*(100 * 100));
}



//�C�j�V�����C�Y
void CObjMain::Init()
{
	m_scroll_x = 0.0f;
	m_scroll_y = 0.0f;
}

//�A�N�V����
void CObjMain::Action()
{

	//��l���̈ʒu���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//����X�N���[�����C��
	if (hx < 80)
	{
		hero->SetX(80);
		m_scroll_x -= hero->GetVX();
	}

	//�O���X�N���[�����C��
	if (hx > 500)
	{
		hero->SetX(500);
		m_scroll_x -= hero->GetVX();
	}
	//����X�N���[�����C��
	if (hy < 10)
	{
		hero->SetY(10);
		m_scroll_y -= hero->GetVY();
	}

	//�����X�N���[�����C��
	if (hy > 500)
	{
		hero->SetY(500);
		m_scroll_y -= hero->GetVY();
	}

	
}





	


//�h���[
void CObjMain::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	
	

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0)
			{
				

				//�\���ʒu�̐ݒ�
				dst.m_top = i * 64.0f+m_scroll_y;
				dst.m_left = j * 64.0f+m_scroll_x;
				dst.m_right = dst.m_left + 64.0;
				dst.m_bottom = dst.m_top + 64.0;

				

				if (m_map[i][j] == 1|| m_map[i][j] == 3)
				{
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = src.m_left + 64.0f;
					src.m_bottom = src.m_top + 64.0f;

					Draw::Draw(1, &src, &dst, c, 0.0f);
				}
				
				
			}
		}

	}
}
