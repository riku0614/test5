//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjTitle.h"
#include "SceneMain.h"
#include "GameL/Audio.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTitle::Init()
{

	//Mouse�̈ʒu�擾�p�ϐ�������
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	//Mouse�̃N���b�N�m�F������
	m_mou_r = false;
	m_mou_l = false;
}

//�A�N�V����
void CObjTitle::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();

	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();

	//�}�E�X�̈ʒu�ƃN���b�N����ꏊ�œ����蔻��
	if (m_mou_x > 230 && m_mou_x < 450 && m_mou_y>400 && m_mou_y < 430)
	{
		//�}�E�X�������ꂽ�烁�C���Ɉڍs
		if (m_mou_r == true || m_mou_l == true)
		{
			Scene::SetScene(new CSceneMain);
		}
	}
}

//�h���[
//Font::StrDraw(L"�o�͂�����������", x�ʒu, y�ʒu, �����̑傫��, color�z��);
void CObjTitle::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"X=%f,Y=%f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 20, c);

	//�����̕\��
	Font::StrDraw(L"���q", 320, 200, 60, c);
	Font::StrDraw(L"�`�J�C�G�`", 317, 270, 25, c);

	
}