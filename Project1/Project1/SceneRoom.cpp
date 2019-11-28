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
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjRoom.h"
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
	int size;

	
	pp = Save::ExternalDataOpen(L"����1�T�N��.csv", &size);

	int map[25][25];
	int count = 1;
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			int w = 0;
			swscanf_s(&pp.get()[count], L"%d", &w);

			map[i][j] = w;
			count += 2;


		}
	}
	Draw::LoadImageW(L"Char2.png", 0, TEX_SIZE_1024);
	Draw::LoadImageW(L"��.png", 1, TEX_SIZE_512);
	//����
	CObjRoom* obji = new CObjRoom(map);
	Objs::InsertObj(obji, OBJ_ROOM, 20);

}

//�Q�[�����C�����s�����\�b�h
void CSceneRoom::Scene()
{

}
void CSceneRoom::Draw()
{

}