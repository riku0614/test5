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
}

//�h���[
void CObjGameOver::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"GAME OVER", 260, 250, 60, c);

	if (Title_flag == true)
	{
		Scene::SetScene(new CSceneTitle);
	}
	else if (GO_time > 300)
	{
		Scene::SetScene(new CSceneTitle);
	}
}