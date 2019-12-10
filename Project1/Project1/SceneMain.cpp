//STLデバッグ機能をオフに
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/DrawTexture.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjMain.h"
#include "ObjItem.h"
#include "ObjRoom.h"

//使用するネームスペース
using namespace GameL;


//コンストラクタ
CSceneMain::CSceneMain()
{

}

//デストラクタ
CSceneMain::~CSceneMain()
{

}

//ゲームメイン初期化メソッド
void CSceneMain::InitScene()
{
	//音楽情報の読み込み
	Audio::LoadAudio(1, L"1廊下BGM.wav", SOUND_TYPE::BACK_MUSIC);

	//音楽スタート
	Audio::Start(1);

	unique_ptr<wchar_t> p;
	int size;
	
	p = Save::ExternalDataOpen(L"チーム開発マップ案1.csv", &size);

	int map[MAP_X][MAP_Y];
	int count = 1;

	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
			
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			count += 3;

		}
	}


	Draw::LoadImageW(L"床.png", 1, TEX_SIZE_512);
	Draw::LoadImageW(L"スタミナゲージ.png", 2, TEX_SIZE_512);
	Draw::LoadImageW(L"壁.png", 3, TEX_SIZE_512);
	Draw::LoadImageW(L"窓.png", 4, TEX_SIZE_512);
	Draw::LoadImageW(L"敵(仮2).png", 5, TEX_SIZE_512);
	Draw::LoadImageW(L"アイテム欄(仮).png", 6, TEX_SIZE_512);
	Draw::LoadImageW(L"kaidan2.png", 7, TEX_SIZE_512);
	Draw::LoadImageW(L"アイテム(仮).png", 8, TEX_SIZE_512);
	Draw::LoadImageW(L"鍵.png", 9, TEX_SIZE_512);
	Draw::LoadImageW(L"扉.png", 10, TEX_SIZE_512);
	Draw::LoadImageW(L"手形1.png", 15, TEX_SIZE_512);
	Draw::LoadImageW(L"呪い.png", 16, TEX_SIZE_512);
	Draw::LoadImageW(L"画面.png", 17, TEX_SIZE_1024);
	Draw::LoadImageW(L"壁（横）.png", 18, TEX_SIZE_512);
	Draw::LoadImageW(L"壁（横）２.png", 19, TEX_SIZE_512);
	Draw::LoadImageW(L"壁２.png", 20, TEX_SIZE_512);
	Draw::LoadImageW(L"ダメージエフェクト1.png", 21, TEX_SIZE_1024);
	Draw::LoadImageW(L"ダメージエフェクト2.png", 22, TEX_SIZE_1024);
	Draw::LoadImageW(L"床穴.png", 21, TEX_SIZE_512);
	Draw::LoadImageW(L"ドット絵　本.png", 33, TEX_SIZE_512);



	Draw::LoadImageW(L"char1.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"char2.png", 12, TEX_SIZE_512);
	Draw::LoadImageW(L"char3.png", 13, TEX_SIZE_512);
	Draw::LoadImageW(L"char4.png", 14, TEX_SIZE_512);

	

	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);


	//UIオブジェクト作成
	CObjGameUI* objui = new CObjGameUI();
	Objs::InsertObj(objui, OBJ_GAME_UI, 12);


	//ブロックオブジェクト作成
	CObjMain* objm = new CObjMain(map);
	Objs::InsertObj(objm, OBJ_MAIN, 8);

	//アイテムオブジェクト作成
	CObjItem* obji = new CObjItem(map);
	Objs::InsertObj(obji, OBJ_ITEM, 13);

	

	
	
}

//ゲームメイン実行中メソッド
void CSceneMain::Scene()
{

}