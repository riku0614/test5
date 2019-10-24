//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjGameClear.h"


//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjGameClear::Init()
{

}

//アクション
void CObjGameClear::Action()
{

}

//ドロー
void CObjGameClear::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//文字の表示
	Font::StrDraw(L"～ゲームクリア～",240, 240, 40, c);
}