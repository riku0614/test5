//STL�f�o�b�O�@�\���I�t��
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"
#include "GameL/DrawTexture.h"
#include "GameL/UserData.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneRoom.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneRoom::CSceneRoom()
{

}

//�f�X�g���N�^
CSceneRoom::~CSceneRoom()
{

}

//�Q�[�����C�����������\�b�h
void CSceneRoom::InitScene()
{
	
	unique_ptr<wchar_t> pp;
	int size1;

	pp = Save::ExternalDataOpen(L"����1�T�N��.csv", &size1);

	int room[25][25];
	int count = 1;
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			int w = 0;
			swscanf_s(&pp.get()[count], L"%d", &w);

			room[i][j] = w;
			count += 2;



		}
	}
	Draw::LoadImageW(L"Char2.png", 0, TEX_SIZE_1024);

	Draw::LoadImageW(L"��.png", 1, TEX_SIZE_512);

	CObjRoom* objroom = new CObjRoom(room);
	Objs::InsertObj(objroom, OBJ_ROOM, 17);

	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);

}

//�Q�[�����C�����s�����\�b�h
void CSceneRoom::Scene()
{

}
void CSceneRoom::Draw() 
{

}