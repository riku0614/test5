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
#include "SceneMain.h"
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

	//タイトルオブジェクト作成
	CObjTitle* obj = new CObjTitle();		//タイトルオブジェクト作成
	Objs::InsertObj(obj, OBJ_TITLE, 10);	//タイトルオブジェクト登録


}

//ゲームメイン実行中メソッド
void CSceneTitle::Scene()
{

}