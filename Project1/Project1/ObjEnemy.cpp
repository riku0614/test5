//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "SceneMain.h"
#include "UtilityModule.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjEnemy::CObjEnemy(float x,float y)
{
	m_ex = x;
	m_ey = y;
}
//�C�j�V�����C�Y
void CObjEnemy::Init()
{

	m_vx = 0.0f;
	m_vy = 0.0f;
	
	
	m_flg = 0;

	m_id = CHAR_ENEMY;
	k_id = 1;
	m_time = 0;
	damage_time = 0.0f;

	boost_flag = false;


	
	//block�Ƃ̏Փˊm�F�p

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_ex, m_ey, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);


}

//�A�N�V����
void CObjEnemy::Action()
{

	//�}�b�v���̎擾
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	if (main->RoomFlag() == false && main->GetFlug() == true)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_ex, m_ey, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);
	}
	if (main->GetFlug() == true&&main->FirstFlag()==true)
	{
		//�����蔻��pHitBox���쐬
		Hits::SetHitBox(this, m_ex, m_ey, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);
	}

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	float scrollx = main->GetScrollX();
	float scrolly = main->GetScrollY();
	memcpy(m_map, main->m_map, sizeof(int)*(MAP_X * MAP_Y));

	//��ʓ��ɓ���Ǝ�l����Ǐ]����
	if (m_ex<(WINDOW_MAX_X + -(scrollx)) && m_ex>(WINDOW_MIN_X + -(scrollx)) &&
		    m_ey<(WINDOW_MAX_Y + -(scrolly)) && m_ey>(WINDOW_MIN_Y + -(scrolly)))
	{
		m_vx = (hx + -(scrollx) - m_ex) ;
		m_vy = (hy + -(scrolly) - m_ey) ;
	}
	//��ʊO�ɐ��b����Ǝ�l���̋߂��Ƀ��[�v����
	else
	{
		m_time++;

		m_vx = (hx + -(scrollx)-m_ex);
		m_vy = (hy + -(scrolly)-m_ey);

	
		if (m_time > 300)
		{
			
			CObjEnemy* enemy = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);
			m_time = 0;
			
			m_ex = hx + -(scrollx)+(64.0f * 2);
			m_ey = hy + -(scrolly)+(64.0f * 2);
			
		}
	}
	//�ړ��x�N�g���̐��K��
	UnitVec(&m_vy, &m_vx);

	m_ex += m_vx*3.0f;
	m_ey += m_vy*3.0f;

	//�����ړ��ɂ��block����
	bool b;
	float pxx, pyy, r;
	
	CObjMain* pbb = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	if (pbb->GetScrollX() > 0)
		pbb->SetScrollX(0);
	if (pbb->GetScrollY() > 0)
		pbb->SetScrollY(0);
	//�ړ�������ray���΂�
	float vx;
	
	if (m_vx > 0)
		vx = 500 - pbb->GetScrollX();
	else
		vx = 0 - pbb->GetScrollX();

	//ray����
	b = pbb->HeroBlockCrossPoint(m_ex - pbb->GetScrollX() + 64, m_ey - pbb->GetScrollY() + 64, vx, 0.0f, &pxx, &pyy, &r);

	if (b == true)
	{
		//��_�擾
		px = pxx + pbb->GetScrollX();
		py = pyy - pbb->GetScrollY();

		float aa = (m_ex)-px;//A�i��_����l���̈ʒu�j�x�N�g��
		float bb = (m_ex + m_vx) - px;//B�i��_����l���̈ړ���ʒu�j�x�N�g��

									  //��l���̕����I�t�Z�b�g
		if (vx > 0)
			px += -64;
		else
			px += 2;

		//A��B���t�������Ă���i��l�����ړ���̕ǂ��z���Ă���j
		if (aa*bb < 0)
		{
			//�ړ��x�N�g�����i��_����l���̈ʒu�j�x�N�g���ɂ���
			m_vx = px - m_ex;
		}
	}
	else
	{
		px = 0.0f;
		py = 0.0f;
	}

	//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	int d;
	//�u���b�N�̓����蔻����s
	CObjMain* pb = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	pb->BlockHit(&m_ex, &m_ey, false, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d, &m_id,&k_id);


	CObjMain* scroll = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	
	//���g��hitbox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);
	if (hit != nullptr)
	{
		//hitbox�̈ʒu�̕ύX
		hit->SetPos(m_ex + scroll->GetScrollX(), m_ey + scroll->GetScrollY());
	}

	if (main->RoomFlag()==true)
	{
		Hits::DeleteHitBox(this);
	}
	if (main->GetFlug2() == true)
	{
		this->SetStatus(false);    //���g�ɍ폜���߂��o��
		Hits::DeleteHitBox(this);
	}
}

//�h���[
void CObjEnemy::Draw()
{
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	if (main->RoomFlag() == false)
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
		dst.m_top = 0.0f + m_ey + main->GetScrollY();
		dst.m_left = (64.0) + m_ex + main->GetScrollX();
		dst.m_right = (64 - 64.0f) + m_ex + main->GetScrollX();
		dst.m_bottom = 64.0f + m_ey + main->GetScrollY();

		//3�Ԗڂɓo�^�����O���t�B�b�N��src.dst.c�̏������ɕ`��
		Draw::Draw(5, &src, &dst, c, 0.0f);
	}
}





