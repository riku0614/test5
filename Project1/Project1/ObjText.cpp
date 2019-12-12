//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjText.h"
#include "SceneMain.h"
#include "GameL/Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjText::Init()
{
	
}
//�A�N�V����
void CObjText::Action()
{
	//Enter���������Ƃ��̏���
	if (Input::GetVKey(VK_RETURN)==true)
	{
		
	}
}

//�h���[
void CObjText::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`�挳�؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 64.0f;
	dst.m_right = 64.0f;
	dst.m_left =  64.0f;
	dst.m_bottom =  64.0f;

	//�`��ݒ�
	Draw::Draw(0, &src, &dst, c, 0.0f);



	Font::StrDraw(L"������������Ă���̂Ȃ�A�������̊w�Z���瓦����", 64, 64, 64, c);
}