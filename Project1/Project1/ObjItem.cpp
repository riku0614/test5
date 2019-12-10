//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjItem.h"
#include "GameL/HitBoxManager.h"
#include "UtilityModule.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjItem::CObjItem(float x,float y)
{
	ix = x;
	iy = y;
}


//�C�j�V�����C�Y
void CObjItem::Init()
{
	//�ϐ�������
	

	//m_px = 0.0f;
	//m_py = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;

	//hit_flg = true;
	

			
	//�����蔻��phitbox���쐬
	//Hits::SetHitBox(this, ix, iy, 32, 32, ELEMENT_ITEM, OBJ_ITEM, 1);


	//m_scroll_x = -2850.0f;
	//m_scroll_y = -64.0f;

	stop_flg = false;
	
}

//�A�N�V����
void CObjItem::Action()
{
	//���C���̈ʒu���擾
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	//�}�b�v�̃f�[�^���R�s�[���āA�A�C�e����\��������
	memcpy(m_map, main->m_map, sizeof(int)*(MAP_X * MAP_Y));
	memcpy(r_map, main->r_map, sizeof(int)*(ROOM_X * ROOM_Y));

	//��l���̃A�C�e���Ɠ��������t���O�������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	/*hit->SetPos(ix + main->GetScrollX(), iy + main->GetScrollY());*/
	//�A�C�e���ɓ������āA�Ȃ�����'E'���������Ƃ��ɃA�C�e���������鏈��

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

	//���C���̈ʒu���擾
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	float hx = main->GetScrollX();
	float hy = main->GetScrollY();

	if (main->RoomFlag() == true)
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == 4)
				{
					//�\���ʒu�̐ݒ�
					dst.m_top = i * 64.0f + hy;
					dst.m_left = j * 64.0f + hx;
					dst.m_right = dst.m_left + 32.0f;
					dst.m_bottom = dst.m_top + 32.0f;

					Draw::Draw(8, &src, &dst, c, 0.0f);
				}
			}
		}
	}

	if (main->RoomFlag() == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 4)
				{
					//�\���ʒu�̐ݒ�
					dst.m_top = i * 64.0f + hy;
					dst.m_left = j * 64.0f + hx;
					dst.m_right = dst.m_left + 32.0f;
					dst.m_bottom = dst.m_top + 32.0f;

					Draw::Draw(8, &src, &dst, c, 0.0f);
				}
			}
		}
	}
}