//STL�f�o�b�O�@�\���I�t��
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "ObjMenu.h"
#include "SceneMenu.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneMenu::CSceneMenu()
{

}

//�f�X�g���N�^
CSceneMenu::~CSceneMenu()
{

}

//�Q�[�����C�����������\�b�h
void CSceneMenu::InitScene()
{
	

	//���j���[�I�u�W�F�N�g�쐬
	CObjMenu* objmenu = new CObjMenu();		//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
	Objs::InsertObj(objmenu, OBJ_MENU, 10);	//�Q�[���I�[�o�[�I�u�W�F�N�g�o�^

}

//�Q�[�����C�����s�����\�b�h
void CSceneMenu::Scene()
{

}