//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
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
	float c[4] = { 1.0f,1.0f,1.0f,1.0f};
	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 22.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 22.0f;
	dst.m_bottom = 64.0f;

	//1�Ԗڂɓo�^�����O���t�B�b�N��src.dst.c�̏������ɕ`��
	Draw::Draw(0, &src, &dst, c, 0.0f);
}