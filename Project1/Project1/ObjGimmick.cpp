//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjGimmick.h"
#include "GameL/HitBoxManager.h"
#include "UtilityModule.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;


//�R���X�g���N�^



//�C�j�V�����C�Y
void CObjGimmick::Init()
{
	//�ϐ�������
	ix = 0;
	iy = 0;

	m_vx = 0.0f;
	m_vy = 0.0f;

	h_count = 0;
	gimmick_flg = false;
	stop_flg = true;


	//�G�o�����C���̗������
	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{	//��̒�����4��T��
			if (m_map[i][j] == 7)
			{

				pi = i;
				pj = j;

				CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
				float hx = main->GetScrollX();
				float hy = main->GetScrollY();

				ix = j * 64.0f;//�A�C�e���̈ʒuX���Ƃ�
				iy = i * 64.0f;//�A�C�e���̈ʒuY���Ƃ�

				Hits::SetHitBox(this, ix, iy, 64, 64, ELEMENT_BLUE, OBJ_GIMMICK, 1);


			}
		}
	}

}

//�A�N�V����
void CObjGimmick::Action()
{


	

	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(ix + main->GetScrollX(), iy + main->GetScrollY());
	

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{

		gimmick_flg = true;

		
	}
	
	
	



}

//�h���[
void CObjGimmick::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�`��؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;

	//���C���̈ʒu���擾
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	float hx = main->GetScrollX();
	float hy = main->GetScrollY();

	
		if (gimmick_flg==true)
		{
				//��
				
			if (m_map[pi][pj] == 7&& m_map[pi-1][pj]==10)
			{
					//�\���ʒu�̐ݒ�
					dst.m_top = pi-0.1f * 64.0f +hy;
					dst.m_left = pj * 64.0f +hx ;
					dst.m_right = dst.m_left + 64.0f;
					dst.m_bottom = dst.m_top + 64.0f;

					gimmick_flg == false;

				}
				//��
				else if (m_map[pi][pj] == 7 && m_map[pi + 1][pj] == 10)
				{
					//�\���ʒu�̐ݒ�
					dst.m_top = pi+0.1f * 64.0f + hy;
					dst.m_left = pj * 64.0f + hx;
					dst.m_right = dst.m_left + 64.0f;
					dst.m_bottom = dst.m_top + 64.0f;

					gimmick_flg == false;
				}
				//��
				else if (m_map[pi][pj] == 7 && m_map[pi][pj-1] == 10)
				{
					//�\���ʒu�̐ݒ�
					dst.m_top = pi * 64.0f + hy;
					dst.m_left = pj-0.1f * 64.0f + hx;
					dst.m_right = dst.m_left + 64.0f;
					dst.m_bottom = dst.m_top + 64.0f;

					gimmick_flg == false;
				}
				//�E
				else if (m_map[pi][pj] == 7 && m_map[pi][pj+1] == 10)
				{
					//�\���ʒu�̐ݒ�
					dst.m_top = pi * 64.0f + hy;
					dst.m_left = pj+0.1f * 64.0f + hx;
					dst.m_right = dst.m_left + 64.0f;
					dst.m_bottom = dst.m_top + 64.0f;

					gimmick_flg == false;
			}

				

			Draw::Draw(15, &src, &dst, c, 0.0f);
		}

}