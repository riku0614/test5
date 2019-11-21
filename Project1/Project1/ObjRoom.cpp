//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRoom.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;
CObjRoom::CObjRoom(int map[25][25])
{
	memcpy(m_map, map, sizeof(int)*(25 * 25));
}


//�C�j�V�����C�Y
void CObjRoom::Init()
{

}

//�A�N�V����
void CObjRoom::Action()
{

}

//�h���[
void CObjRoom::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

		//���C���̈ʒu���擾
	//CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//float hx = hero->GetX();
	//float hy = hero->GetY();

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (m_map[i][j] > 0)
			{


				//�\���ʒu�̐ݒ�
				dst.m_top = i * 64.0f + m_scroll_y;
				dst.m_left = j * 64.0f + m_scroll_x;
				dst.m_right = dst.m_left + 64.0;
				dst.m_bottom = dst.m_top + 64.0;

				
				//���e�N�X�`��
				if (m_map[i][j] == 1 || m_map[i][j] == 5 || m_map[i][j] == 7 || m_map[i][j] == 8 || m_map[i][j] == 6)
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



