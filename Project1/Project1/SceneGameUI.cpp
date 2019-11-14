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
#include "ObjGameUI.h"
#include "SceneGameUI.h"
#include "GameHead.h"

//コンストラクタ
CSceneGameUI::CSceneGameUI()
{

}

//デストラクタ
CSceneGameUI::~CSceneGameUI()
{

}
//ゲームUI初期化メゾット
void CSceneGameUI::InitScene()
{
	Draw::LoadImage(L"アイテム欄.png",0,TEX_SIZE_512);

	CObjGameUI*obj = new CObjGameUI();
	Objs::InsertObj(obj, OBJ_GAMEUI, 1);



}
//ゲームUI実行メゾット
void CSceneGameUI::Scene()
{

}
