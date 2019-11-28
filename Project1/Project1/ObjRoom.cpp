//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjRoom.h"


//使用するネームスペース
using namespace GameL;
CObjRoom::CObjRoom(int map[25][25])
{
	memcpy(m_map, map, sizeof(int)*(25 * 25));
}


//イニシャライズ
void CObjRoom::Init()
{

}

//アクション
void CObjRoom::Action()
{

}

//ドロー
void CObjRoom::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

		//メインの位置を取得
	//CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//float hx = hero->GetX();
	//float hy = hero->GetY();

	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			if (m_map[i][j] > 0)
			{


				//表示位置の設定
				dst.m_top = i * 64.0f + m_scroll_y;
				dst.m_left = j * 64.0f + m_scroll_x;
				dst.m_right = dst.m_left + 64.0;
				dst.m_bottom = dst.m_top + 64.0;

				
				//床テクスチャ
				if (m_map[i][j] == 1 || m_map[i][j] == 5 || m_map[i][j] == 7 || m_map[i][j] == 8 || m_map[i][j] == 6)
				{
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = src.m_left + 64.0f;
					src.m_bottom = src.m_top + 64.0f;

					Draw::Draw(1, &src, &dst, c, 0.0f);

				}


			}
		}

	}
}



