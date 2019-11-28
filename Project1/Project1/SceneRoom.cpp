//STLデバッグ機能をオフに
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"
#include "GameL/DrawTexture.h"
#include "GameL/UserData.h"
//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjRoom.h"
//コンストラクタ
CSceneRoom::CSceneRoom()
{

}

//デストラクタ
CSceneRoom::~CSceneRoom()
{

}

//ゲームメイン初期化メソッド
void CSceneRoom::InitScene()
{

	unique_ptr<wchar_t> pp;
	int size;

	
	pp = Save::ExternalDataOpen(L"教室1サクラ.csv", &size);

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
	Draw::LoadImageW(L"床.png", 1, TEX_SIZE_512);
	//教室
	CObjRoom* obji = new CObjRoom(map);
	Objs::InsertObj(obji, OBJ_ROOM, 20);

}

//ゲームメイン実行中メソッド
void CSceneRoom::Scene()
{

}
void CSceneRoom::Draw()
{

}