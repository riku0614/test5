//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjGameUI.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjGameUI::Init()
{

}

//�A�N�V����
void CObjGameUI::Action()
{

}

//�h���[
void CObjGameUI::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

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


}