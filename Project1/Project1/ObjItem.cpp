//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjItem.h"


//使用するネームスペース
using namespace GameL;

CObjItem::CObjItem(int map[100][100])
{
	memcpy(m_map, map, sizeof(int)*(100 * 100));
}

//イニシャライズ
void CObjItem::Init()
{
	//変数初期化
	//ix = 0;
	//iy = 0;
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

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] == 3)
			{
				//描画設定位置
				dst.m_top = 64.0f;
				dst.m_left = 64.0f;
				dst.m_right = dst.m_left + 10.0f;
				dst.m_bottom = dst.m_top + 10.0f;

				Draw::Draw(7, &src, &dst, c, 0.0f);
			}
		}
	}
	
}