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

	Draw::LoadImageW(L"床.png", 1, TEX_SIZE_512);

	
	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);
	
	
	//ブロックオブジェクト作成
	CObjMain* objm = new CObjMain(map);
	Objs::InsertObj(objm, OBJ_MAIN, 9);


}

//ゲームメイン実行中メソッド
void CSceneMain::Scene()
{

}