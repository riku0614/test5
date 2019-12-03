//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjGameClear.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjGameClear::Init()
{
	m_time = 0;
}

//�A�N�V����
void CObjGameClear::Action()
{
	m_time++;	//���Ԃɂ���ĉ摜��\�����邽�߂̕ϐ�
}

//�h���[
void CObjGameClear::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//�����̕\��
	//Font::StrDraw(L"�`�Q�[���N���A�`",240, 240, 40, c);

	RECT_F src;
	RECT_F dst;

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 640.0f;
	src.m_bottom = 480.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 0.0f;
	dst.m_right = 800.0f;
	dst.m_left = 0.0f;
	dst.m_bottom = 600.0f;

	//�`��ݒ�
	Draw::Draw(0, &src, &dst, c, 0.0f);

	//ED1�\��
	if (m_time > 60 && m_time < 300)
	{
		float f[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src;
		RECT_F dst;

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 640.0f;
		src.m_bottom = 480.0f;

		//�\���ʒu�ݒ�
		dst.m_top = 0.0f;
		dst.m_right = 800.0f;
		dst.m_left = 0.0f;
		dst.m_bottom = 600.0f;

		Draw::Draw(1, &src, &dst, f, 0.0f);
	}

	//ED2�\��
	if (m_time > 360 && m_time < 600)
	{
		float f[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src;
		RECT_F dst;

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 640.0f;
		src.m_bottom = 480.0f;

		//�\���ʒu�ݒ�
		dst.m_top = 0.0f;
		dst.m_right = 800.0f;
		dst.m_left = 0.0f;
		dst.m_bottom = 600.0f;

		Draw::Draw(2, &src, &dst, f, 0.0f);
	}

	//ED3�\��
	if (m_time > 660 && m_time < 900)
	{
		float f[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src;
		RECT_F dst;

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 640.0f;
		src.m_bottom = 480.0f;

		//�\���ʒu�ݒ�
		dst.m_top = 0.0f;
		dst.m_right = 800.0f;
		dst.m_left = 0.0f;
		dst.m_bottom = 600.0f;

		Draw::Draw(3, &src, &dst, f, 0.0f);
	}

	//ED�摜��\��������A�^�C�g����ʂֈڍs
	if (m_time > 930)
	{
		Scene::SetScene(new CSceneTitle);
	}

}