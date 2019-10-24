//STLデバッグ機能をオフに
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "ObjGameOver.h"
#include "SceneGameOver.h"
#include "GameHead.h"

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
	//オブジェクトを登録
	//CObjMain* p = new CObjMain();
	//Objs::InsertObj(p, OBJ_MAIN, 1);

	//タイトルオブジェクト作成
	CObjGameOver* objg = new CObjGameOver();		//タイトルオブジェクト作成
	Objs::InsertObj(objg, OBJ_GAMEOVER, 10);	//タイトルオブジェクト登録

}

//ゲームメイン実行中メソッド
void CSceneGameOver::Scene()
{

}