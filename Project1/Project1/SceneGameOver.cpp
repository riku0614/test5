//STL�f�o�b�O�@�\���I�t��
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"
#include "GameL/DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "ObjGameOver.h"
#include "SceneGameOver.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneGameOver::CSceneGameOver()
{

}

//�f�X�g���N�^
CSceneGameOver::~CSceneGameOver()
{

}

//�Q�[�����C�����������\�b�h
void CSceneGameOver::InitScene()
{
	//�I�u�W�F�N�g��o�^
	//CObjMain* p = new CObjMain();
	//Objs::InsertObj(p, OBJ_MAIN, 1);

	Draw::LoadImageW(L"����.png", 0, TEX_SIZE_512);

	//�^�C�g���I�u�W�F�N�g�쐬
	CObjGameOver* objg = new CObjGameOver();		//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
	Objs::InsertObj(objg, OBJ_GAMEOVER, 10);	//�Q�[���I�[�o�[�I�u�W�F�N�g�o�^

}

//�Q�[�����C�����s�����\�b�h
void CSceneGameOver::Scene()
{

}