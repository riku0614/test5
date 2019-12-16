#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/DrawTexture.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjMain.h"
#include "ObjItem.h"


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
	//����
	m_time=0;

	
	//���y���̓ǂݍ���
	Audio::LoadAudio(1, L"1�L��BGM.wav", SOUND_TYPE::BACK_MUSIC);

	//���y�X�^�[�g
	Audio::Start(1);

	unique_ptr<wchar_t> p;
	int size;
	
	p = Save::ExternalDataOpen(L"����1�T�N��.csv", &size);

	int map[ROOM_X][ROOM_Y];
	int count = 1;

	for (int i = 0; i < ROOM_X; i++)
	{
		for (int j = 0; j < ROOM_Y; j++)
		{
			
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			count += 3;

			
		
			
		}
	}


	Draw::LoadImageW(L"��.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"�X�^�~�i�Q�[�W.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"��.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"��.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"�G(��2).png", 5, TEX_SIZE_512);
	Draw::LoadImageW(L"�A�C�e����(��).png", 6, TEX_SIZE_512);
	Draw::LoadImageW(L"kaidan2.png", 7, TEX_SIZE_512);
	Draw::LoadImageW(L"�A�C�e��(��).png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"��.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"��.png", 10, TEX_SIZE_512);

	Draw::LoadImageW(L"��l���܂Ƃ�.png", 11, TEX_SIZE_512);

	Draw::LoadImageW(L"��`1.png", 15, TEX_SIZE_512);
	Draw::LoadImageW(L"��.png", 16, TEX_SIZE_512);
	Draw::LoadImageW(L"���.png", 17, TEX_SIZE_1024);
	Draw::LoadImageW(L"�ǁi���j.png", 18, TEX_SIZE_512);
	Draw::LoadImageW(L"�ǁi���j�Q.png", 19, TEX_SIZE_512);
	Draw::LoadImageW(L"�ǂQ.png", 20, TEX_SIZE_512);                     //20
	Draw::LoadImageW(L"��.png", 21, TEX_SIZE_512);
	Draw::LoadImageW(L"�_���[�W�G�t�F�N�g1.png", 22, TEX_SIZE_1024);
	Draw::LoadImageW(L"�_���[�W�G�t�F�N�g2.png", 23, TEX_SIZE_1024);
	Draw::LoadImageW(L"����.png", 24, TEX_SIZE_512);
	Draw::LoadImageW(L"��1.png", 25, TEX_SIZE_512);
	Draw::LoadImageW(L"���i���j1.png", 26, TEX_SIZE_512);
	Draw::LoadImageW(L"���i�E�j1.png", 27, TEX_SIZE_512);
	Draw::LoadImageW(L"���i���j1.png", 28, TEX_SIZE_512);
	Draw::LoadImageW(L"�{�I.png", 29, TEX_SIZE_512);
	Draw::LoadImageW(L"���܂Ƃ�.png", 30, TEX_SIZE_1024);                             //30
	Draw::LoadImageW(L"�֎q�܂Ƃ�.png", 31, TEX_SIZE_1024);
	Draw::LoadImageW(L"�G���F(��).png", 32, TEX_SIZE_512);
	Draw::LoadImageW(L"�h�b�g�G�@�{.png", 33, TEX_SIZE_512);
	Draw::LoadImageW(L"�Ǎ���.png", 34, TEX_SIZE_512);
	Draw::LoadImageW(L"�ǉE��.png", 35, TEX_SIZE_512);
	Draw::LoadImageW(L"�ǉE��.png", 36, TEX_SIZE_512);
	Draw::LoadImageW(L"�Ǎ���.png", 37, TEX_SIZE_512);
	Draw::LoadImageW(L"�G�ԐF(��).png", 38, TEX_SIZE_512);
	Draw::LoadImageW(L"����.png", 39, TEX_SIZE_512);
	Draw::LoadImageW(L"�Ǌp�Q�E��.png", 38, TEX_SIZE_512);
	Draw::LoadImageW(L"�Ǌp�Q����.png", 39, TEX_SIZE_512);
	Draw::LoadImageW(L"�Ǌp�Q����.png", 40, TEX_SIZE_512);                       //40
	Draw::LoadImageW(L"�Ǌp�Q�E��.png", 41, TEX_SIZE_512);
	Draw::LoadImageW(L"�G�ԐF(��).png", 42, TEX_SIZE_512);
	Draw::LoadImageW(L"����.png", 43, TEX_SIZE_512);
	Draw::LoadImageW(L"�o�[���̂悤�Ȃ���.png", 44, TEX_SIZE_1024);
	Draw::LoadImageW(L"����.png", 45, TEX_SIZE_512);
	Draw::LoadImageW(L"black.png", 46, TEX_SIZE_1024);
	Draw::LoadImageW(L"�_���[�W�G�t�F�N�g1.png", 47, TEX_SIZE_1024);
	Draw::LoadImageW(L"�_���[�W�G�t�F�N�g2.png", 48, TEX_SIZE_1024);
	


	//�o�͂����镶���̃O���t�B�b�N�쐬
	Font::SetStrTex(L"������肵��...");

	//��l���I�u�W�F�N�g�쐬
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);


	//UI�I�u�W�F�N�g�쐬
	CObjGameUI* objui = new CObjGameUI();
	Objs::InsertObj(objui, OBJ_GAME_UI, 12);
	
	
	//�u���b�N�I�u�W�F�N�g�쐬
	CObjMain* objm = new CObjMain(map);
	Objs::InsertObj(objm, OBJ_MAIN, 8);

	////�A�C�e���I�u�W�F�N�g�쐬
	//CObjItem* obji = new CObjItem(map);
	//Objs::InsertObj(obji, OBJ_ITEM, 13);

	
	
}

//�Q�[�����C�����s�����\�b�h
void CSceneMain::Scene()
{

}