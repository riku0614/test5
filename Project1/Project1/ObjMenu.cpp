//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjMenu.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMenu::Init()
{
	m_enter_flag = false;
}

//�A�N�V����
void CObjMenu::Action()
{
	if (Input::GetVKey(VK_SPACE) == true)
	{
		if (m_enter_flag == false)
		{
			Scene::SetScene(new CSceneTitle);
		}
		m_enter_flag = true;
	}

	else
	{
		m_enter_flag = false;
	}

	if (Input::GetVKey('E') == true)
	{
		Scene::SetScene(new CSceneMain);
	}



}

//�h���[
void CObjMenu::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"space�L�[�Ń^�C�g���֖߂�", 200, 250, 32, c);
}