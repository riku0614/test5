//STLデバッグ機能をオフに
#define _SECURE_SCL (0)
#define _HAS_ITERATER_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/DrawFont.h"
#include "GameL/Audio.h"
#include "GameL/DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "ObjClickTitle.h"
#include "GameHead.h"

//コンストラクタ
CSceneTitle::CSceneTitle()
{

}

//デストラクタ
CSceneTitle::~CSceneTitle()
{

}

//ゲームメイン初期化メソッド
void CSceneTitle::InitScene()
{
	//出力させる文字のグラフィック作成
	Font::SetStrTex(L"怪穢");
	Font::SetStrTex(L"～カイエ～");
	Font::SetStrTex(L"最初から");

	//矢印追加
	Draw::LoadImage(L"カーソル.png", 0, TEX_SIZE_512);

	//タイトルオブジェクト作成
	CObjTitle* obj = new CObjTitle();		//タイトルオブジェクト作成
	Objs::InsertObj(obj, OBJ_TITLE, 10);	//タイトルオブジェクト登録

	//クリックタイトルオブジェクト作成
	CObjClickTitle* objb = new CObjClickTitle();	//クリックタイトルオブジェクト作成
	Objs::InsertObj(objb, OBJ_CLICK_TITLE, 11);		//タイトルオブジェクト登録


}

//ゲームメイン実行中メソッド
void CSceneTitle::Scene()
{

}