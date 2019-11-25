//STLデバッグ機能をオフに
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/DrawTexture.h"
#include "GameL/UserData.h"

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjMain.h"
#include "ObjItem.h"

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
	unique_ptr<wchar_t> p;
	int size;
	p = Save::ExternalDataOpen(L"チーム開発マップ案1.csv", &size);

	int map[75][75];
	int count = 1;
	for (int i = 0; i < 75; i++)
	{
		for (int j = 0; j < 75; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			count += 2;

		}
	}

	Draw::LoadImageW(L"Char2.png", 0, TEX_SIZE_1024);

	Draw::LoadImageW(L"床.png", 1, TEX_SIZE_512);
	
	Draw::LoadImageW(L"スタミナゲージ.png", 2, TEX_SIZE_512);

	Draw::LoadImageW(L"敵(仮).png", 3, TEX_SIZE_512);

	Draw::LoadImageW(L"敵(仮1).png", 4, TEX_SIZE_512);

	Draw::LoadImageW(L"敵(仮2).png", 5, TEX_SIZE_512);

	Draw::LoadImageW(L"アイテム欄(仮).png", 6, TEX_SIZE_512);

	Draw::LoadImageW(L"アイテム(仮).png", 8, TEX_SIZE_512);

	
	Draw::LoadImageW(L"kaidan.png", 7, TEX_SIZE_512);
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

	//5があれば、敵を出現
	CObjEnemy* obje = new CObjEnemy(map);
	Objs::InsertObj(obje, OBJ_ENEMY, 10);
	
}

//ゲームメイン実行中メソッド
void CSceneMain::Scene()
{

}