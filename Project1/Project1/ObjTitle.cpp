//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjTitle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTitle::Init()
{

}

//�A�N�V����
void CObjTitle::Action()
{

}

//�h���[
//Font::StrDraw(L"�o�͂�����������", x�ʒu, y�ʒu, �����̑傫��, color�z��);
void CObjTitle::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"���q", 320, 200, 60, c);
	Font::StrDraw(L"�`�J�C�G�`", 317, 270, 25, c);
}