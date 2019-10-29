//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_px = 0.0f; //�ʒu
	m_py = 0.0f;
	m_vx = 0.0f; //�ړ��x�N�g��
	m_vy = 0.0f;

	m_hero_life = 3;//��l���̗̑͗p�ϐ�


	//block�Ƃ̏Փˊm�F�p

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0;

	m_ani_time = 0;
	m_ani_frame = 1;//�Î~�t���[���������ɂ���

	m_speed_power = 1.0f;
	m_ani_max_time = 6;
	m_ani_move = 0;

	m_posture = 1.0f; //�E����0.0���@������1.0��
	m_stamina_limid = 90.0f;


	//�����蔻��phitbox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//�A�N�V����
void CObjHero::Action()
{
	if (Input::GetVKey('M') == true)
	{
		Scene::SetScene(new CSceneMenu);
	}


	//Z�L�[���͂ő��x�A�b�v
	if (m_stamina_limid>=0&&Input::GetVKey(VK_LSHIFT) == true&& Input::GetVKey('A') == true||
		m_stamina_limid >= 0 && Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('D') == true||
		m_stamina_limid >= 0 && Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('W') == true||
		m_stamina_limid >= 0 && Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('S') == true)
	{
		
		//�_�b�V�����̑��x
		m_speed_power = 1.0f;
		m_ani_max_time = 4;

		m_stamina_limid -= 0.3f;
	}
	else
	{
		//�ʏ푬�x
		m_speed_power = 0.5f;
		m_ani_max_time = 4;

		if (m_stamina_limid < 90.0f)
		{
			m_stamina_limid += 0.3f;
		}

	}

	//�L�[�̓��͕���
	if (Input::GetVKey('D') == true)
	{
		m_vx += m_speed_power;
		m_posture = 0.0f;
		m_ani_time += 1;
	}
	else if (Input::GetVKey('A') == true)
	{
		m_vx -= m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	}
	else if (Input::GetVKey('W') == true)
	{
		m_vy -= m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	}
	else if (Input::GetVKey('S') == true)
	{
		m_vy += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	}

	//�A�j���[�V�����̃��Z�b�g
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//�A�j���[�V�����t���[���̃��Z�b�g
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}
	//�ړ��x�N�g���̐��K��
	//UnitVec(&m_vy, &m_vx);

	//���C
	m_vx += -(m_vx*0.09);
	m_vy += -(m_vy*0.09);

	//�u���b�N�̓����蔻����s
	CObjMain* pb = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	pb->BlockHit(&m_px, &m_py, true,true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);
	
	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;


	//���g��hitbox�������Ă���
	CHitBox* hit = Hits::GetHitBox(this);

	//hitbox�̈ʒu�̕ύX
	hit->SetPos(m_px, m_py);

	//��l���@�I�u�W�F�N�g�ƐڐG������G�폜
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		//��l���̃��C�t�ɂ�铖���蔻��̕ω�
		if (m_hero_life == 0)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);

			Scene::SetScene(new CSceneGameOver);
		}
		else
		{
			m_hero_life -= 1;
			
		}
	}

	

	
}

void CObjHero::Draw()
{
	int AniData[3][6] =
	{
		0,1,2,3,4,0,
		0,1,2,3,4,5,
		0,1,2,3,4,0,
	};

	//�`��J���[���@R=RED�@G=Green�@B=Blue�@A=Alpha�i���ߏ��j
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�X�^�~�i�o�[�̕`��
	if (m_stamina_limid > 0 && m_stamina_limid < 90.0)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 0.0f + m_py+64.0f;
		dst.m_left = 0.0f+ m_px;
		dst.m_right = m_stamina_limid + m_px;
		dst.m_bottom = 64.0f + m_py+64.0f;

		//1�Ԗڂɓo�^�����O���t�B�b�N��src.dst.c�̏������ɕ`��
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}
	
	//��l���̃_�b�V�����ƒʏ펞�ƐÎ~���̕`��
	if (Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('W') == true &&m_stamina_limid>0|| 
		Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('A') == true&&m_stamina_limid > 0 ||
		Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('S') == true && m_stamina_limid > 0 ||
		Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('D') == true && m_stamina_limid > 0)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 90.0f * 5;
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 90;
		src.m_right = 90.0f + AniData[m_ani_move][m_ani_frame] * 90;
		src.m_bottom = 90.0f * 6;

	}
	else if (Input::GetVKey('W') == true || Input::GetVKey('A') == true||
		Input::GetVKey('S') == true || Input::GetVKey('D') == true)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 90.0f * 9;
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 90;
		src.m_right = 90.0f + AniData[m_ani_move][m_ani_frame] * 90;
		src.m_bottom = 90.0f * 10;
	}
	else
	{
		//�؂���ʒu�ݒ�
		src.m_top = 720.0f;
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 90;
		src.m_right = 90.0f + AniData[m_ani_move][m_ani_frame] * 90;
		src.m_bottom = 810.0f;
	}

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f*m_posture) + m_px;
	dst.m_right = (64 - 64.0f*m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;

	//1�Ԗڂɓo�^�����O���t�B�b�N��src.dst.c�̏������ɕ`��
	Draw::Draw(0, &src, &dst, c, 0.0f);

}
