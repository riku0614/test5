//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjClickTitle.h"
#include "SceneMain.h"
#include "GameL/Audio.h"
#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjClickTitle::Init()
{
	m_yj = 0.0f;
	m_f = true;

}
//�A�N�V����
void CObjClickTitle::Action()
{
	if (Input::GetVKey('M'))
	{
		;
	}
	//Enter���������Ƃ��̏���
	if (m_yj == 0.0f && Input::GetVKey(VK_RETURN))
	{
		Scene::SetScene(new CSceneMain);
	}
	
	//'W'key�����������̖�󏈗�
	if (Input::GetVKey('W') == true)
	{ 
		//m_f��true�̏ꍇ...
		if (m_f == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(2, L"2�J�[�\��SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(2);

			//m_yj��0.0f(�����ʒu)�������ꍇ�̏���
			if (m_yj <= 0.0f)
			{
			m_yj = m_yj + 150.0f;
			}
			//m_yj��0�ȏ�̏ꍇ
			if (m_yj > 0.0f)
			{
			m_yj -= 50.0f;//3�I���ł���悤�̂��邽�߁A+�̒l�̎O���̈�̐���������i-y�j�ɓ�����
			}

			m_f = false;//m_f��false�Ɂ�'W'�����������Ă��J�[�\���������Ȃ��悤�ɂ���
		}
	}

	//'S'key�����������̖�󏈗�
	else if (Input::GetVKey('S') == true)
	{
		//m_f��true�̏ꍇ...
		if (m_f == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(2, L"2�J�[�\��SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(2);

			//m_yj��100.0f(�ő�l�̈ʒu)�������ꍇ�̏���
			if (m_yj >= 100.0f)
			{
				m_yj = m_yj - 150.0f;
			}
			//m_yj��100�ȉ��̏ꍇ
			if (m_yj <= 100.0f)
			{
				m_yj += 50.0f;//3�I���ł���悤�̂��邽�߁A-�̒l�̎O���̈�̐���������i+y�j�ɓ�����
			}

			m_f = false;//m_f��false�Ɂ�'W','S'�����������Ă��J�[�\���������Ȃ��悤�ɂ���
		}
	}
	//'W','S'����x����������
	else
	{
		m_f = true;//m_f��true��
	}
}

//�h���[
void CObjClickTitle::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	
	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu


		//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 607.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 0.0f;
	dst.m_right = 799.0f;
	dst.m_left = 0.0f;
	dst.m_bottom = dst.m_top + 599.0f;

	//�`��ݒ�
	Draw::Draw(1, &src, &dst, c, 0.0f);

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 335.0f + m_yj;
	dst.m_right = 450.0f;
	dst.m_left = dst.m_right + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	//�`��ݒ�
	Draw::Draw(0, &src, &dst, c, 0.0f);



	//�N���b�N����ꏊ
	//�Q�[�����n�߂�ꏊ

	float cc[4] = { 1.0f,0.5f,0.5f,0.7f };
	Font::StrDraw(L"�ŏ�����", 320, 350, 30, cc);
	Font::StrDraw(L"��������", 320, 400, 30, cc);
	Font::StrDraw(L"�Q�[���I��", 300, 450, 30, cc);

}
