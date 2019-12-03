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
	//�A�C�e�����g������A�C�e������������
	if (hero->SetItemflag() == true) //�A�C�e������1�Ԗ�
	{
		hero->SetFlug(false);
		m_id = 0;
	}

	
	/*
	if (hero->SetItemflag_2() == true) //�A�C�e������2�Ԗ�
	{
		hero->SetFlug_2(false);
		m_id = 0;
	}

	if (hero->SetItemflag_3() == true) //�A�C�e������3�Ԗ�
	{
		hero->SetFlug_3(false);
		m_id = 0;
	}*/
}

//�h���[
void CObjGameUI::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

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

	/*�_���[�W�G�t�F�N�g*/
	
		/*//�؂���ʒu�̐ݒ�
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

		Draw::Draw(21, &src, &dst, c, 0.0f);*/
	
	
	//�؂���ʒu�̐ݒ�
	/*src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 680.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left + 800.0f;
	dst.m_bottom = dst.m_top + 600.0f;

	//�`��ݒ�

	Draw::Draw(22, &src, &dst, c, 0.0f);*/
	
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
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//�A�C�e���̕\���i1�ԁj
	if (hero->Getflag() == true)
	{
		RECT_F src2;	//�`�挳�؂���ʒu
		RECT_F dst2;	//�`���\���ʒu

		src2.m_top = 10.0f;
		src2.m_left = 10.0f;
		src2.m_right = 40.0f;
		src2.m_bottom = 40.0f;

	
		//�\���ʒu�ݒ�
		dst2.m_top = 562.0f;
		dst2.m_left = 686.0f;
		dst2.m_right = dst.m_left + 40.0f;
		dst2.m_bottom = dst.m_top + 45.0f;
		
		//�`��ݒ�
		Draw::Draw(9, &src2, &dst2, c, 0.0f);

		take_flag = true; //1�Ԗڂ̃A�C�e���������Ă��邩�ǂ����̃t���O��true�ɂ��遨��l���ɂăA�C�e�����g�p�ł��邩�ǂ����̔���


	}

	//2�Ԃ̃A�C�e���\��
	/*
	if (hero->Getflag_2() == true && take_flag == true)
	{
		RECT_F src3;	//�`�挳�؂���ʒu
		RECT_F dst3;	//�`���\���ʒu

		src3.m_top = 10.0f;
		src3.m_left = 10.0f;
		src3.m_right = 48.0f;
		src3.m_bottom = 50.0f;


		//�\���ʒu�ݒ�
		dst3.m_top = 559.0f;
		dst3.m_left = 724.0f;
		dst3.m_right = dst.m_left + 38.0f;
		dst3.m_bottom = dst.m_top + 40.0f;

		//�`��ݒ�
		Draw::Draw(9, &src3, &dst3, c, 0.0f);

		take_flag_2 = true; //2�Ԗڂ̃A�C�e���������Ă��邩�ǂ����̃t���O��true�ɂ��遨��l���ɂăA�C�e�����g�p�ł��邩�ǂ����̔���
	}

	//3�Ԃ̃A�C�e���\��
	if (hero->Getflag_3() == true && take_flag == true && take_flag_2 == true)
	{
		RECT_F src4;	//�`�挳�؂���ʒu
		RECT_F dst4;	//�`���\���ʒu

		src4.m_top = 10.0f;
		src4.m_left = 10.0f;
		src4.m_right = 48.0f;
		src4.m_bottom = 50.0f;


		//�\���ʒu�ݒ�
		dst4.m_top = 559.0f;
		dst4.m_left = 762.0f;
		dst4.m_right = dst.m_left + 38.0f;
		dst4.m_bottom = dst.m_top + 40.0f;

		//�`��ݒ�
		Draw::Draw(9, &src4, &dst4, c, 0.0f);

		take_flag_3 = true; //3�Ԗڂ̃A�C�e���������Ă��邩�ǂ����̃t���O��true�ɂ��遨��l���ɂăA�C�e�����g�p�ł��邩�ǂ����̔���
	}*/
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
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