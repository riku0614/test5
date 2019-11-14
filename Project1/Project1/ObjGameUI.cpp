//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjGameUI.h"
//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjGameUI::Init()
{
	
}

//アクション
void CObjGameUI::Action()
{

}

//ドロー
void CObjGameUI::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f};
	RECT_F src;//描画元切り取り位置
	RECT_F dst;

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 22.0f;
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 22.0f;
	dst.m_bottom = 64.0f;

	//1番目に登録したグラフィックをsrc.dst.cの情報を元に描画
	Draw::Draw(0, &src, &dst, c, 0.0f);
}