//STL�f�o�b�O�@�\���I�t��
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "ObjGameUI.h"
#include "SceneGameUI.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneGameUI::CSceneGameUI()
{

}

//�f�X�g���N�^
CSceneGameUI::~CSceneGameUI()
{

}
//�Q�[��UI���������\�b�h
void CSceneGameUI::InitScene()
{


	Draw::LoadImage(L"�A�C�e����.png",0,TEX_SIZE_512);

	//Draw::LoadImageW(L"��.png", 9, TEX_SIZE_512);

	CObjGameUI*obj = new CObjGameUI();
	Objs::InsertObj(obj, OBJ_GAME_UI, 1);



}
//�Q�[��UI���s���\�b�h
void CSceneGameUI::Scene()
{
	
}
