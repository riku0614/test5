//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjItem.h"
#include "GameL/HitBoxManager.h"


//使用するネームスペース
using namespace GameL;

CObjItem::CObjItem(int map[75][75])
{
	memcpy(m_map, map, sizeof(int)*(75 * 75));
}

//イニシャライズ
void CObjItem::Init()
{
	//変数初期化
	//ix = 0;
	//iy = 0;

	//メインの位置を取得
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	for (int i = 0; i < 75; i++)
	{
		for (int j = 0; j < 75; j++)
		{
			if (m_map[i][j] == 4)
			{

				//当たり判定用hitboxを作成
				Hits::SetHitBox(this, j-main->GetScrollY(), i-main->GetScrollX(), 64, 64, ELEMENT_ITEM, OBJ_ITEM, 1);
			}
		}
	}

}

//アクション
void CObjItem::Action()
{
	


	
}

//ドロー
void CObjItem::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//描画切り取り位置
	src.m_top = 17.0f;
	src.m_left = 20.0f;
	src.m_right = src.m_left + 25.0f;
	src.m_bottom = src.m_top + 30.0f;

	//メインの位置を取得
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	float hx = main->GetScrollX();
	float hy = main->GetScrollY();

	for (int i = 0; i < 75; i++)
	{
		for (int j = 0; j < 75; j++)
		{
			if (m_map[i][j] == 4)
			{
				//表示位置の設定
				dst.m_top = i * 64.0f + hy;
				dst.m_left = j * 64.0f + hx;
				dst.m_right = dst.m_left + 20.0;
				dst.m_bottom = dst.m_top + 20.0;

				Draw::Draw(8, &src, &dst, c, 0.0f);
			}
		}
	}
	
}