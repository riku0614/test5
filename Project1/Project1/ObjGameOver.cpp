//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjGameOver.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjGameOver::Init()
{
	GO_time = 0;
	Title_flag = false;
}

//�A�N�V����
void CObjGameOver::Action()
{
	GO_time++;//�^�C���̌o�߂ɂ���ă^�C�g���Ɉڍs���邽�߁A��u�C���N�������g�Œl�𑝂₵�Ă���

	//�^�C���̌o�߂Ƃ͕ʂɁA'Z'�L�[���������ꍇ�Ƀ^�C�g���Ɉڍs����悤�ɂ���
	if (Input::GetVKey('Z') == true)
	{
		Title_flag = true;	//�^�C�g���Ɉڍs���邽�߂̃t���O���I����
	}

	if (Title_flag == true)
	{
		Scene::SetScene(new CSceneTitle);
	}
	else if (GO_time > 300)
	{
		Scene::SetScene(new CSceneTitle);
	}
}

//�h���[
void CObjGameOver::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	
	RECT_F src;
	RECT_F dst;

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 256.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 0.0f;
	dst.m_right = 800.0f;
	dst.m_left = 0.0f;
	dst.m_bottom = 600.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);

}