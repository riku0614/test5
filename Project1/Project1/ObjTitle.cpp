//使用するヘッダーファイル
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"

#include "GameHead.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle::Init()
{

}

//アクション
void CObjTitle::Action()
{

}

//ドロー
//Font::StrDraw(L"出力したい文字列", x位置, y位置, 文字の大きさ, color配列);
void CObjTitle::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	Font::StrDraw(L"怪穢", 300, 300, 32, c);
}