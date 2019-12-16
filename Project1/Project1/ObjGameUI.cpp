//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/DrawFont.h"

#include "GameHead.h"
#include "ObjGameUI.h"
#include"ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjGameUI::Init()
{
	item_flag = false;
	item_flag_2 = false;
	item_flag_3 = false;

	take_flag = false;
	take_flag_2 = false;
	take_flag_3 = false;


	m_id = 0;
	h_id = 0;
	b_id = 0;
}

//�A�N�V����
void CObjGameUI::Action()
{
	item_flag = true;//�A�C�e�����g�����߂̃t���O,��l���ɂĎg�p
	item_flag_2 = true;
	item_flag_3 = true;

		//��l���̃A�C�e�����g�����t���O�������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	
	m_id = hero->GetKeyID();
	h_id = hero->GatHealID();
	b_id = hero->GetBarID();
	
	//�A�C�e�����g������A�C�e������������
	if (hero->SetItemflag() == true) //�A�C�e������1�Ԗ�
	{
		hero->SetFlug(false);
		m_id = 0;
	}


	if (hero->SetItemflag_2() == true) //�A�C�e������2�Ԗ�
	{
		hero->SetFlug_2(false);
		h_id = 0;
	}
	
	if (hero->SetItemflag_3() == true) //�A�C�e������3�Ԗ�
	{
		hero->SetFlug_3(false);
		b_id = 0;
	}
}

//�h���[
void CObjGameUI::Draw()
{
	
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };


	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//��l���̃A�C�e���Ɠ��������t���O�������Ă���
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	if (main->GetStoryFlag() == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		//�\���ʒu�ݒ�
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 800.0f;
		dst.m_bottom = dst.m_top + 600.0f;

		//�`��ݒ�
		Draw::Draw(46, &src, &dst, c, 0.0f);

		Font::StrDraw(L"������������Ă���Ȃ�A�������̊w�Z���瓦����B", 10, 20, 20, c);
		Font::StrDraw(L"�����̊w�Z�Ȃ�Ȃ�Ă��Ɩ����񂾁B�����̊w�Z����Ȃ����炱��Ȃ��̂��c�����񂾁B", 10,60 , 20, c);
		Font::StrDraw(L"������������B���������B", 10, 100, 20, c);
		Font::StrDraw(L"�������������B���������������掷�X�ɒǂ��Ă���B", 10, 140, 20, c);
		Font::StrDraw(L"���͂��ꂾ������Ȃ��B�K�w�̐������������B8�K���B�΂��邾��H", 10, 180, 20, c);
		Font::StrDraw(L"�����瑁��������B����ȋ������ꏊ�ɂ����炨�������Ȃ邼�B", 10, 220, 20, c);
		Font::StrDraw(L"���͂���ŋ��b�Ă��}�����B�������ɂȂ��`�}��", 10, 260, 20, c);
		Font::StrDraw(L"����͂̓n�n�ȃn�n���̓n��n��n", 10, 320, 20, c);

		
	}
	else 
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 1024.0f;
		src.m_bottom = 680.0f;

		//�\���ʒu�ݒ�
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 800.0f;
		dst.m_bottom = dst.m_top + 600.0f;

		//�`��ݒ�
		Draw::Draw(17, &src, &dst, c, 0.0f);

		//��l���̃A�C�e���Ɠ��������t���O�������Ă���
		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

		/*�_���[�W�G�t�F�N�g*/
		if (hero->action_flag() == true && hero->GetLife() <= 20)
		{
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1024.0f;
			src.m_bottom = 680.0f;

			//�\���ʒu�ݒ�
			dst.m_top = 0.0f;
			dst.m_left = 0.0f;
			dst.m_right = dst.m_left + 800.0f;
			dst.m_bottom = dst.m_top + 600.0f;

			//�`��ݒ�

			Draw::Draw(47, &src, &dst, c, 0.0f);
		}
		if (hero->action_flag2() == true && hero->GetLife() <= 10)
		{
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1024.0f;
			src.m_bottom = 680.0f;

			//�\���ʒu�ݒ�
			dst.m_top = 0.0f;
			dst.m_left = 0.0f;
			dst.m_right = dst.m_left + 800.0f;
			dst.m_bottom = dst.m_top + 600.0f;

			//�`��ݒ�

			Draw::Draw(48, &src, &dst, c, 0.0f);
		}

		//�؂���ʒu�̐ݒ�
		src.m_top = 19.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 38.0f;

		//�\���ʒu�ݒ�
		dst.m_top = 559.0f;
		dst.m_left = 686.0f;
		dst.m_right = dst.m_left + 64.0f + 50.0f;
		dst.m_bottom = dst.m_top + 21.0f + 20.0f;

		//�`��ݒ�
		Draw::Draw(6, &src, &dst, c, 0.0f);

		//��l���̃A�C�e���Ɠ��������t���O�������Ă���
		CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

		if (main)

			//�A�C�e���̕\���i1�ԁj
			if (hero->Getflag() == true)
			{
				RECT_F src;	//�`�挳�؂���ʒu
				RECT_F dst;	//�`���\���ʒu

				src.m_top = 10.0f;
				src.m_left = 10.0f;
				src.m_right = 40.0f;
				src.m_bottom = 40.0f;


				//�\���ʒu�ݒ�
				dst.m_top = 562.0f;
				dst.m_left = 686.0f;
				dst.m_right = dst.m_left + 40.0f;
				dst.m_bottom = dst.m_top + 45.0f;

				//�`��ݒ�
				Draw::Draw(9, &src, &dst, c, 0.0f);

				take_flag = true; //1�Ԗڂ̃A�C�e���������Ă��邩�ǂ����̃t���O��true�ɂ��遨��l���ɂăA�C�e�����g�p�ł��邩�ǂ����̔���


			}

		//2�Ԃ̃A�C�e���\��
		if (hero->Getflag_2() == true)
		{
			RECT_F src;	//�`�挳�؂���ʒu
			RECT_F dst;	//�`���\���ʒu

			src.m_top = 32.0f;
			src.m_left = 32.0f;
			src.m_right = 224.0f;
			src.m_bottom = 224.0f;


			//�\���ʒu�ݒ�
			dst.m_top = 559.0f;
			dst.m_left = 725.0f;
			dst.m_right = dst.m_left + 38.0f;
			dst.m_bottom = dst.m_top + 45.0f;

			//�`��ݒ�
			Draw::Draw(21, &src, &dst, c, 0.0f);

			take_flag_2 = true; //2�Ԗڂ̃A�C�e���������Ă��邩�ǂ����̃t���O��true�ɂ��遨��l���ɂăA�C�e�����g�p�ł��邩�ǂ����̔���
		}

		//3�Ԃ̃A�C�e���\��
		if (hero->Getflag_3() == true)
		{
			RECT_F src;	//�`�挳�؂���ʒu
			RECT_F dst;	//�`���\���ʒu

			src.m_top = 0.0f;
			src.m_left = 100.0f;
			src.m_right = 400.0f;
			src.m_bottom = 512.0f;


			//�\���ʒu�ݒ�
			dst.m_top = 559.0f;
			dst.m_left = 762.0f;
			dst.m_right = dst.m_left + 38.0f;
			dst.m_bottom = dst.m_top + 45.0f;

		//�`��ݒ�
		Draw::Draw(44, &src, &dst, c, 0.0f);

			take_flag_3 = true; //3�Ԗڂ̃A�C�e���������Ă��邩�ǂ����̃t���O��true�ɂ��遨��l���ɂăA�C�e�����g�p�ł��邩�ǂ����̔���

		}
		if (main->MapChangeData() == 0)
		{
			//�K�̕\��
			Font::StrDraw(L"8�K", 730, 10, 30, c);
		}
		else if (main->MapChangeData() == 1)
		{
			//�K�̕\��
			Font::StrDraw(L"1�K", 730, 10, 30, c);
		}
	}
}