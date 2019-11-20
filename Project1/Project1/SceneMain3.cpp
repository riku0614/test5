//STL�f�o�b�O�@�\���I�t��
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/DrawTexture.h"
#include "GameL/UserData.h"

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjMain.h"
#include "ObjItem.h"
#include "SceneMain3.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


//�R���X�g���N�^
CSceneMain3::CSceneMain3()
{

}

//�f�X�g���N�^
CSceneMain3::~CSceneMain3()
{

}

//�Q�[�����C�����������\�b�h
void CSceneMain3::InitScene()
{
	unique_ptr<wchar_t> p;
	int size;
	p = Save::ExternalDataOpen(L"map2.csv", &size);


	int map[MAP_X][MAP_Y];
	int count = 1;

	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			count += 2;

		}
	}

	Draw::LoadImageW(L"Char2.png", 0, TEX_SIZE_1024);

	Draw::LoadImageW(L"��.png", 1, TEX_SIZE_512);

	Draw::LoadImageW(L"��.png", 2, TEX_SIZE_512);

	Draw::LoadImageW(L"�X�^�~�i�Q�[�W.png", 3, TEX_SIZE_512);

	Draw::LoadImageW(L"��.png", 4, TEX_SIZE_512);

	Draw::LoadImageW(L"�G(��2).png", 5, TEX_SIZE_512);

	Draw::LoadImageW(L"�A�C�e����(��).png", 6, TEX_SIZE_512);

	Draw::LoadImageW(L"�A�C�e��(��).png", 8, TEX_SIZE_512);


	Draw::LoadImageW(L"kaidan.png", 7, TEX_SIZE_512);
	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);


	//UI�I�u�W�F�N�g�쐬
	CObjGameUI* objui = new CObjGameUI();
	Objs::InsertObj(objui, OBJ_GAME_UI, 12);


	//�u���b�N�I�u�W�F�N�g�쐬
	CObjMain* objm = new CObjMain(map);
	Objs::InsertObj(objm, OBJ_MAIN, 8);

	//�A�C�e���I�u�W�F�N�g�쐬
	CObjItem* obji = new CObjItem(map);
	Objs::InsertObj(obji, OBJ_ITEM, 13);

	//5������΁A�G���o��
	CObjEnemy* obje = new CObjEnemy(map);
	Objs::InsertObj(obje, OBJ_ENEMY, 10);

}

//�Q�[�����C�����s�����\�b�h
void CSceneMain3::Scene()
{

}

