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
#include "ObjGameOver.h"
#include "SceneGameOver.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneMain::CSceneMain()
{

}

//�f�X�g���N�^
CSceneMain::~CSceneMain()
{

}

//�Q�[�����C�����������\�b�h
void CSceneMain::InitScene()
{
	//�I�u�W�F�N�g��o�^
	//CObjMain* p = new CObjMain();
	//Objs::InsertObj(p, OBJ_MAIN, 1);

	//�^�C�g���I�u�W�F�N�g�쐬
	CObjGameOver* objg = new CObjGameOver();		//�^�C�g���I�u�W�F�N�g�쐬
	Objs::InsertObj(objg, OBJ_GAMEOVER, 10);	//�^�C�g���I�u�W�F�N�g�o�^

}

//�Q�[�����C�����s�����\�b�h
void CSceneGameOver::Scene()
{

}