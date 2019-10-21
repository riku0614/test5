//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

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
	m_posture = 1.0f; //�E����0.0���@������1.0��
	m_stamina_limid = 600.0f;
}

//�A�N�V����
void CObjHero::Action()
{
	

	//Z�L�[���͂ő��x�A�b�v
	if (m_stamina_limid>=0&&Input::GetVKey(VK_LSHIFT) == true&& 
		Input::GetVKey('A') == true||Input::GetVKey('D') == true)
	{
		
		//�_�b�V�����̑��x
		m_speed_power = 2.0f;
		m_stamina_limid -= 1.0f;
	}
	else
	{
		//�ʏ푬�x
		m_speed_power = 1.0f;

		if (m_stamina_limid < 600.0f)
		{
			m_stamina_limid += 1.0f;
		}

	}
	//�L�[�̓��͕���
	if (Input::GetVKey('A') == true)
	{
		m_vx += 1.0f;
		m_posture = 1.0f;
	}
	else if (Input::GetVKey('D') == true)
	{
		m_vx -= 1.0f;
		m_posture = 0.0f;
	}
	else if (Input::GetVKey('W') == true)
	{
		m_vy -= 1.0f;
		
	}
	else if (Input::GetVKey('S') == true)
	{
		m_vy += 1.0f;
	}

	//�ړ��x�N�g���̐��K��
	UnitVec(&m_vy, &m_vx);

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

}

void CObjHero::Draw()
{
	//�`��J���[���@R=RED�@G=Green�@B=Blue�@A=Alpha�i���ߏ��j
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
	dst.m_left = (64.0f*m_posture) + m_px;
	dst.m_right = (64 - 64.0f*m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;

	//1�Ԗڂɓo�^�����O���t�B�b�N��src.dst.c�̏������ɕ`��
	Draw::Draw(0, &src, &dst, c, 0.0f);

}
