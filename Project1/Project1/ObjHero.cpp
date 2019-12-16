//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"
#include "UtilityModule.h"
#include "GameL/Audio.h"
#include"ObjGameUI.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_px = 64.0f; //�ʒu
	m_py = 64.0f;
	m_vx = 0.0f; //�ړ��x�N�g��
	m_vy = 0.0f;

	m_hero_life = 30;//��l���̗̑͗p�ϐ�




	peperon_flag = false;
	use_Item_flag = false;
	
	Conflict_flag = false;

	//block�Ƃ̏Փˊm�F�p

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	mi_hit_up = false;
	mi_hit_down = false;
	mi_hit_left = false;
	mi_hit_right = false;

	m_hero_stop = false;

	enemy_flg = false;

	m_block_type = 0;



	m_ani_time = 6;
	m_time = 10;
	m_flg =false;

	m_ani_frame = 1;//�Î~�t���[���������ɂ���

	m_speed_power = 1.0f;
	m_ani_max_time = 6;
	m_ani_move = 0;

	m_posture = 1.0f; //�E����0.0���@������1.0��
	m_stamina_limid = 90.0f;

	m_id = CHAR_HERO;
	k_id = 99;
	h_id = 99;
	b_id = 99;
	hit_flag_x = false;
	hit_flag_y = false;
	//�����蔻��phitbox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_HERO, 2);
}

//�A�N�V����
void CObjHero::Action()
{
	//�Q�[�����C���Ƀt���O���Z�b�g����
	CObjMain* Main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	if (m_hero_stop == false)
	{
		//���j���[�L�[
		if (Input::GetVKey('M') == true)
		{
			Scene::SetScene(new CSceneMenu);
		}


		//Z�L�[���͂ő��x�A�b�v
		if (m_stamina_limid >= 10 && Input::GetVKey(VK_LSHIFT) == true ||
			m_stamina_limid >= 10 && Input::GetVKey(VK_RSHIFT) == true)
		{

			//�_�b�V�����̑��x
			m_speed_power = 1.5f;
			m_ani_max_time = 4;

			m_stamina_limid -= 0.5f;
		}
		else
		{
			//�ʏ푬�x
			m_speed_power = 1.0f;
			m_ani_max_time = 4;

			if (m_stamina_limid < 90.0f)
			{
				m_stamina_limid += 0.5f;
			}

		}

		//�L�[�̓��͕���
		
		if (Input::GetVKey('A') == true&&Input::GetVKey('D')!=true)
		{
			m_vx -= m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (Input::GetVKey('W') == true&&Input::GetVKey('S') != true)
		{
			m_vy -= m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (Input::GetVKey('S') == true&&Input::GetVKey('W') != true)
		{
			m_vy += m_speed_power;
			m_posture = 1.0f;
			m_ani_time += 1;
		}
		else if (Input::GetVKey('D') == true && Input::GetVKey('A') != true)
		{
			m_vx += m_speed_power;
			m_posture = 0.0f;
			m_ani_time += 1;
		}
	}
	else if (m_hero_stop==true&&Input::GetVKey(VK_RETURN) == true)
	{

		Main->SetStoryFlag(false);
		Main->SetStoryFlag2(true);
		m_hero_stop = false;
	}

		//��l���̃A�C�e���Ɠ��������t���O�������Ă���
		CObjGameUI* UI = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);


		//1�Ԗڂ̃A�C�e�����Ƃ鏈��
		if (Input::GetVKey('E') == true && mi_hit_left == true && UI->takeItemflag() == false && Main->GetMapItem() == true ||
			Input::GetVKey('E') == true && mi_hit_right == true && UI->takeItemflag() == false && Main->GetMapItem() == true ||
			Input::GetVKey('E') == true && mi_hit_down == true && UI->takeItemflag() == false && Main->GetMapItem() == true ||
			Input::GetVKey('E') == true && mi_hit_up == true && UI->takeItemflag() == false && Main->GetMapItem() == true)
		{
			Main->SetKeyFlag(true);
			peperon_flag = true;
			k_id = ITEM_KEY;
			Main->SetDelete(true);
			
			//Main->GetMapItem() = false;
		}

		//2�Ԗڂ̃A�C�e�����Ƃ鏈��
		if (Input::GetVKey('E') == true && mi_hit_left == true && UI->takeItemflag_2() == false && Main->GetMapItem_2() == true ||
			Input::GetVKey('E') == true && mi_hit_right == true && UI->takeItemflag_2() == false && Main->GetMapItem_2() == true ||
			Input::GetVKey('E') == true && mi_hit_down == true && UI->takeItemflag_2() == false && Main->GetMapItem_2() == true ||
			Input::GetVKey('E') == true && mi_hit_up == true && UI->takeItemflag_2() == false && Main->GetMapItem_2() == true)
		{
			Main->SetHealFlag(true);
			peperon_flag_2 = true;
			h_id = ITEM_HEAL;
			Main->SetDelete(true);
			
			//Main->GetMapItem_2() = false;
		}

		if (Input::GetVKey('E') == true && mi_hit_left == true && UI->takeItemflag_3() == false && Main->GetMapItem_3() == true ||
			Input::GetVKey('E') == true && mi_hit_right == true && UI->takeItemflag_3() == false && Main->GetMapItem_3() == true ||
			Input::GetVKey('E') == true && mi_hit_down == true && UI->takeItemflag_3() == false && Main->GetMapItem_3() == true ||
			Input::GetVKey('E') == true && mi_hit_up == true && UI->takeItemflag_3() == false && Main->GetMapItem_3() == true)
		{
			Main->SetBarFlag(true);
			peperon_flag_3 = true;
			b_id = ITEM_BAR;
			Main->SetDelete(true);
			
			//Main->GetMapItem_2() = false;
		}


		//1�Ԗڂ̃A�C�e�����g������
		if (Input::GetVKey('1') == true && UI->GetItemflag() == true)
		{
			use_Item_flag = true;
			UI->Settakeflag(false);
		}

		//2�Ԗڂ̃A�C�e�����g������
		else if (Input::GetVKey('2') == true && UI->GetItemflag_2() == true)
		{
			if (m_hero_life <= 29)
			{
				use_Item_flag_2 = true;
				m_hero_life = 30;
				UI->Settakeflag_2(false);
			}
			else if (m_hero_life == 30)
			{
				;
			}

		}

		//3�Ԗڂ̃A�C�e�����g������
		else if (Input::GetVKey('3') == true && UI->GetItemflag_3() == true)
		{
			use_Item_flag_3 = true;
			UI->Settakeflag_3(false);
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

		//���C
		m_vx += -(m_vx*0.098f);
		m_vy += -(m_vy*0.098f);

		//�����ړ��ɂ��block����
		bool b;
		float pxx, pyy, r;
		CObjMain* pbb = (CObjMain*)Objs::GetObj(OBJ_MAIN);

		if (pbb->GetScrollX() > 0)
			pbb->SetScrollX(0);

		//�ړ�������ray���΂�
		float vx;
		float vy;

		if (m_vx > 0)
			vx = 500 - pbb->GetScrollX();
		else
			vx = 0 - pbb->GetScrollX();


		//ray����
		b = pbb->HeroBlockCrossPoint(m_px - pbb->GetScrollX() + 32, m_py - pbb->GetScrollY() + 32, vx, 0.0f, &pxx, &pyy, &r);

		if (b == true)
		{
			//��_�擾
			px = pxx + pbb->GetScrollX();
			py = pyy - pbb->GetScrollY();

			float aa = (m_px)-px;//A�i��_����l���̈ʒu�j�x�N�g��
			float bb = (m_px + m_vx) - px;//B�i��_����l���̈ړ���ʒu�j�x�N�g��


			//��l���̕����I�t�Z�b�g
			if (vx > 0)
				px += -64;
			else
				px += 2;


			//A��B���t�������Ă���i��l�����ړ���̕ǂ��z���Ă���j
			if (aa*bb < 0)
			{
				//�ړ��x�N�g�����i��_����l���̈ʒu�j�x�N�g���ɂ���
				m_vx = px - m_px;
			}

		}
		else
		{
			px = 0.0f;
			py = 0.0f;
		}

	Main->BlockHit(&m_px, &m_py, true, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type, &m_id, &k_id
	);

		//���g��hitbox�������Ă���
		CHitBox* hit = Hits::GetHitBox(this);

		//�A�C�e���̓����蔻����s
	Main->ItemHit(&m_px, &m_py, true, true,
		&mi_hit_up, &mi_hit_down, &mi_hit_left, &mi_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;




	//hitbox�̈ʒu�̕ύX
	hit->SetPos(m_px, m_py);

	//�G�Ɠ���������t���O�����Ă�
	CObjGameUI*ui = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);

	
	
	//��l���@�I�u�W�F�N�g�ƐڐG������G�폜
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr&&m_flg==false||
		hit->CheckObjNameHit(OBJ_FASTENEMY) != nullptr&&m_flg == false|| 
		hit->CheckObjNameHit(OBJ_SPWANENEMY) != nullptr&&m_flg == false)
	{
		//���y���̓ǂݍ���
		Audio::LoadAudio(6, L"6�_���[�W��.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(6);

			m_hero_life -= 1;

			m_flg = true;

			if (m_hero_life == 20)
			{
				Conflict_flag = true;
			}

			if (m_hero_life == 10)
			{
				Conflict_flag2 = true;
			}

			if (m_hero_life == 0)
			{

				Scene::SetScene(new CSceneGameOver);
			}

		}

		if (m_flg == true && m_time > 0)
		{
			m_time--;
		}
		else if (m_time == 0)
		{
			m_flg = false;
			m_time = 10;
		}
	
}

void CObjHero::Draw()
{
	int AniData[4] =
	{
		0,1,2,1,

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
		Input::GetVKey(VK_RSHIFT) == true && Input::GetVKey('W') == true && m_stamina_limid > 0)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 192.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64.0f;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0f;
		src.m_bottom = 256.0f;

		
	}
	else if (Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('A') == true && m_stamina_limid > 0 ||
		Input::GetVKey(VK_RSHIFT) == true && Input::GetVKey('A') == true && m_stamina_limid > 0)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 64.0f;
		src.m_left = 0.0f + +AniData[m_ani_frame] * 64.0f;
		src.m_right = 64.0f + +AniData[m_ani_frame] * 64.0f;
		src.m_bottom = 128.0f;
		
	}
	else if (Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('S') == true && m_stamina_limid > 0 ||
		Input::GetVKey(VK_RSHIFT) == true && Input::GetVKey('S') == true && m_stamina_limid > 0)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 128.0f;
		src.m_left = 0.0f + +AniData[m_ani_frame] * 64.0f;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0f;
		src.m_bottom = 192.0f;

	
	}
	else if (Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('D') == true && m_stamina_limid > 0 ||
		Input::GetVKey(VK_RSHIFT) == true && Input::GetVKey('D') == true && m_stamina_limid > 0)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + +AniData[m_ani_frame] * 64.0f;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0f;
		src.m_bottom = 64.0f;
		


	}
	else if (Input::GetVKey('W') == true )
	{
		//�؂���ʒu�ݒ�
		src.m_top = 192.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64.0;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0;
		src.m_bottom = 256.0f;

		


	}
	else if (Input::GetVKey('A') == true)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64.0;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0;
		src.m_bottom = 64.0f;

		

	

	}
	else if (Input::GetVKey('S') == true)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 128.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64.0f;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0f;
		src.m_bottom = 192.0f;

		


	}
	else if (Input::GetVKey('D') == true)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64.0;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0;
		src.m_bottom = 64.0f;

	}
	else
	{
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 64.0;
		src.m_right = 64.0f + AniData[m_ani_frame] * 64.0;
		src.m_bottom = 64.0f;
	}


	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f*m_posture) + m_px;
	dst.m_right = (64 - 64.0f*m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;

	Draw::Draw(11, &src, &dst, c, 0.0f);
}
