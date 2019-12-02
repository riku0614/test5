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
#include "ObjGameClear.h"
#include "SceneGameClear.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneGameClear::CSceneGameClear()
{

}

//�f�X�g���N�^
CSceneGameClear::~CSceneGameClear()
{

}

//�Q�[�����C�����������\�b�h
void CSceneGameClear::InitScene()
{
	//���y���̓ǂݍ���
	Audio::LoadAudio(8, L"8EDBGM.wav", SOUND_TYPE::EFFECT);

	//���y�X�^�[�g
	Audio::Start(8);

	//�I�u�W�F�N�g��o�^
	//CObjMain* p = new CObjMain();
	//Objs::InsertObj(p, OBJ_MAIN, 1);

	Draw::LoadImageW(L"ED��� �w�i�p.png", 0, TEX_SIZE_1024);

	Draw::LoadImageW(L"ED���1.png", 1, TEX_SIZE_1024);

	Draw::LoadImageW(L"ED���2.png", 2, TEX_SIZE_1024);

	Draw::LoadImageW(L"ED���3.png", 3, TEX_SIZE_1024);

	//�^�C�g���I�u�W�F�N�g�쐬
	CObjGameClear* objc = new CObjGameClear();		//�Q�[���N���A�I�u�W�F�N�g�쐬
	Objs::InsertObj(objc, OBJ_GAMECLEAR, 10);	//�Q�[���N���A�I�u�W�F�N�g�o�^

}

//�Q�[�����C�����s�����\�b�h
void CSceneGameClear::Scene()
{
	
}