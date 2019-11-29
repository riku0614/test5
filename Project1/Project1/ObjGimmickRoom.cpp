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
CObjGimmickRoom::CObjGimmickRoom(float x, float y)
{
	gx = x;
	gy = y;
}


//�C�j�V�����C�Y
void CObjGimmickRoom::Init()
{


	m_vx = 0.0f;
	m_vy = 0.0f;

	h_count = 0;
	gimmick_flg = false;
	stop_flg = true;

	pi = 0;
	pj = 0;

	Hits::SetHitBox(this, gx, gy, 64, 64, ELEMENT_BLUE, OBJ_GIMMICK_ROOM, 1);



}

//�A�N�V����
void CObjGimmickRoom::Action()
{

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	if (stop_flg == false)
	{
		Hits::SetHitBox(this, gx, gy, 64, 64, ELEMENT_BLUE, OBJ_GIMMICK_ROOM, 1);

		stop_flg = true;
	}
	if (main->RoomFlag() == true)
	{

		memcpy(r_map, main->r_map, sizeof(int)*(ROOM_X * ROOM_Y));



		
	


		if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
		{

			gimmick_flg = true;


		}
		else
		{
			gimmick_flg = false;
		}

		if (main->RoomFlag() == false && stop_flg == true)
		{

			Hits::DeleteHitBox(this);

			main->SetStopFlag(true);

			stop_flg = false;

		}

	}
	

	hit->SetPos(gx + -(main->GetScrollX()), gy + -(main->GetScrollY()));

}

//�h���[
void CObjGimmickRoom::Draw()
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

		if (r_map[pi][pj] == 7 && r_map[pi - 1][pj] == 9)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = (pi - 1) * 64.0f + hy;
			dst.m_left = pj * 64.0f + hx;
			dst.m_right = dst.m_left + 64.0f;
			dst.m_bottom = dst.m_top + 64.0f;



		}
		//��
		else if (r_map[pi][pj] == 7 && r_map[pi + 1][pj] == 12)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = (pi + 1) * 64.0f + hy;
			dst.m_left = pj * 64.0f + hx;
			dst.m_right = dst.m_left + 64.0f;
			dst.m_bottom = dst.m_top + 64.0f;


		}
		//��
		else if (r_map[pi][pj] == 7 && r_map[pi][pj - 1] == 11)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = pi * 64.0f + hy;
			dst.m_left = (pj - 1) * 64.0f + hx;
			dst.m_right = dst.m_left + 64.0f;
			dst.m_bottom = dst.m_top + 64.0f;


		}
		//�E
		else if (r_map[pi][pj] == 7 && r_map[pi][pj + 1] == 10)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = pi * 64.0f + hy;
			dst.m_left = (pj + 1) * 64.0f + hx;
			dst.m_right = dst.m_left + 64.0f;
			dst.m_bottom = dst.m_top + 64.0f;


		}

		Draw::Draw(16, &src, &dst, c, 0.0f);
	}

}