//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


CObjEnemy::CObjEnemy(float x, float y)
{
	m_px = x;
	m_py = y;
}

//�C�j�V�����C�Y
void CObjEnemy::Init()
{
	m_vx = 1.0f;
	m_vy = 1.0f;
	m_px = 0.0f; //�ʒu
	m_py = 0.0f;

	m_flg = true;
	
	//�ړ��x�N�g���̐��K��
	UnitVec(&m_vy, &m_vx);
	
	//block�Ƃ̏Փˊm�F�p

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);

}

//�A�N�V����
void CObjEnemy::Action()
{
	//��l���ƗU���̊p�x�����
	CObjHero* obj = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//��l�������݂���ꍇ�A�U���p�x���v�Z����
	if (obj != nullptr)
	{
		float x = obj->GetX()-m_px;
		float y = obj->GetY()-m_py;
		float ar = GetAtan2Angle(x, -y);

		//�e�ۂ̌��݂̌����Ă�p�x�����
		float br = GetAtan2Angle(m_vx, -m_vy);

		float r = 3.14 / 180.0f; //�p�x�P��
		if (ar < br)
		{
			//�ړ�������+�P��������
			m_vx = m_vx * cos(r) - m_vy * sin(r);
			m_vy = m_vy * cos(r) + m_vx * sin(r);
		}
		else
		{
			//�ړ�������-�P��������
			m_vx = m_vx * cos(-r) - m_vy * sin(-r);
			m_vy = m_vy * cos(-r) + m_vx * sin(-r);
		}
		UnitVec(&m_vx, &m_vy);
		
		

	}
	//��l���ւ̒Ǐ]�ړ�
	if (Input::GetVKey('S') == true &&m_flg == true)
	{
		m_flg = false;
		m_px;
		m_py += m_vy + 1.0f - obj->GetVY();
	}
	else if (Input::GetVKey('W') == true && m_flg == true)
	{
		m_flg = false;
		m_px;
		m_py += m_vy - 1.0f + (-obj->GetVY());
	}
	else if (Input::GetVKey('A') == true && m_flg == true)
	{
		m_flg = false;
		m_px += m_vx - 1.0f + (-obj->GetVX());
		m_py;
	}
	else if (Input::GetVKey('D') == true && m_flg == true)
	{
		m_flg = false;
		m_px += m_vx + 1.0f - obj->GetVX();
		m_py;
	}
	else
	{
		m_flg = true;
		m_px += m_vx;
		m_py += m_vy;
	}

	//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	int d;

	//�u���b�N�̓����蔻����s
	CObjMain* pb = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	pb->BlockHit(&m_px, &m_py, true, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);

	//hitbox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);

	
}

//�h���[
void CObjEnemy::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

				//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0) + m_px;
	dst.m_right = (64 - 64.0f) + m_px ;
	dst.m_bottom = 64.0f + m_py;

	//3�Ԗڂɓo�^�����O���t�B�b�N��src.dst.c�̏������ɕ`��
	Draw::Draw(3, &src, &dst, c, 0.0f);
}