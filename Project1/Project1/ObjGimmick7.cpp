//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjGimmick3.h"
#include "GameL/HitBoxManager.h"
#include "UtilityModule.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;



CObjGimmick7::CObjGimmick7(float x, float y)
{
	gx = x;
	gy = y;
}


//�C�j�V�����C�Y
void CObjGimmick7::Init()
{


	m_vx = 0.0f;
	m_vy = 0.0f;

	h_count = 0;
	stop_flg = true;
	gimmick_chg = false;

	pi = 0;
	pj = 0;




}

//�A�N�V����
void CObjGimmick7::Action()
{
	CHitBox* hit = Hits::GetHitBox(this);
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	memcpy(m_map, main->m_map, sizeof(int)*(MAP_X * MAP_Y));

	if (main->GetFlug() == true)
	{

		Hits::DeleteHitBox(this);

		stop_flg == true;

	}



	if (stop_flg == true && main->MapChangeData() == 6)
	{
		Hits::SetHitBox(this, gx, gy, 64, 64, ELEMENT_BLUE, OBJ_GIMMICK7, 1);

		stop_flg = false;
	}

	//HitBox�̈ʒu�̕ύX

	if (hit != nullptr)
	{

		hit->SetPos(gx + main->GetScrollX(), gy + main->GetScrollY());

		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(7, L"7�M�~�b�NSE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(7);
			if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
			{

				gimmick_flg = true;


			}
			else
			{
				gimmick_flg = false;
			}
		}

	}

}

//�h���[
void CObjGimmick7::Draw()
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


	if (gimmick_flg == true)
	{
		//��

		if (m_map[pi][pj] == 7 && m_map[pi - 1][pj] == 9)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = (pi - 1) * 64.0f + hy;
			dst.m_left = pj * 64.0f + hx;
			dst.m_right = dst.m_left + 64.0f;
			dst.m_bottom = dst.m_top + 64.0f;

			Hits::DeleteHitBox(this);

		}
		//��
		else if (m_map[pi][pj] == 7 && m_map[pi + 1][pj] == 12)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = (pi + 1) * 64.0f + hy;
			dst.m_left = pj * 64.0f + hx;
			dst.m_right = dst.m_left + 64.0f;
			dst.m_bottom = dst.m_top + 64.0f;

			Hits::DeleteHitBox(this);
		}
		//��
		else if (m_map[pi][pj] == 7 && m_map[pi][pj - 1] == 11)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = pi * 64.0f + hy;
			dst.m_left = (pj - 1) * 64.0f + hx;
			dst.m_right = dst.m_left + 64.0f;
			dst.m_bottom = dst.m_top + 64.0f;

			Hits::DeleteHitBox(this);
		}
		//�E
		else if (m_map[pi][pj] == 7 && m_map[pi][pj + 1] == 10)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = pi * 64.0f + hy;
			dst.m_left = (pj + 1) * 64.0f + hx;
			dst.m_right = dst.m_left + 64.0f;
			dst.m_bottom = dst.m_top + 64.0f;

			Hits::DeleteHitBox(this);
		}

		Draw::Draw(16, &src, &dst, c, 0.0f);
	}

}