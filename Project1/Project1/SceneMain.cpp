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

//�g�p����l�[���X�y�[�X
using namespace GameL;


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
	unique_ptr<wchar_t> p;
	int size;
	p = Save::ExternalDataOpen(L"map.csv", &size);

	int map[100][100];
	int count = 1;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			count += 2;

		}
	}

	Draw::LoadImageW(L"Char2.png", 0, TEX_SIZE_1024);

	Draw::LoadImageW(L"��.png", 1, TEX_SIZE_512);
	
	Draw::LoadImageW(L"�X�^�~�i�Q�[�W.png", 2, TEX_SIZE_512);

	Draw::LoadImageW(L"�G(��).png", 3, TEX_SIZE_512);

	Draw::LoadImageW(L"�G(��1).png", 4, TEX_SIZE_512);

	Draw::LoadImageW(L"�G(��2).png", 5, TEX_SIZE_512);

	Draw::LoadImageW(L"�A�C�e����(��).png", 6, TEX_SIZE_512);

	Draw::LoadImageW(L"kaidan.png", 7, TEX_SIZE_512);
	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);


	//�G�I�u�W�F�N�g�쐬
	CObjGameUI* objui = new CObjGameUI();
	Objs::InsertObj(objui, OBJ_GAME_UI, 12);
	
	
	//�u���b�N�I�u�W�F�N�g�쐬
	CObjMain* objm = new CObjMain(map);
	Objs::InsertObj(objm, OBJ_MAIN, 8);
	
}

//�Q�[�����C�����s�����\�b�h
void CSceneMain::Scene()
{

}