//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "ObjMain.h"


//使用するネームスペース
using namespace GameL;

CObjMain::CObjMain(int map[100][100])
{
	memcpy(m_map, map, sizeof(int)*(100 * 100));
}



//イニシャライズ
void CObjMain::Init()
{
	m_scroll_x = 0.0f;
	m_scroll_y = 0.0f;
}

//アクション
void CObjMain::Action()
{

	//主人公の位置を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();

	//後方スクロールライン
	if (hx < 80)
	{
		hero->SetX(80);
		m_scroll_x -= hero->GetVX();
	}

	//前方スクロールライン
	if (hx > 500)
	{
		hero->SetX(500);
		m_scroll_x -= hero->GetVX();
	}
	//上方スクロールライン
	if (hy < 10)
	{
		hero->SetY(10);
		m_scroll_y -= hero->GetVY();
	}

	//下方スクロールライン
	if (hy > 500)
	{
		hero->SetY(500);
		m_scroll_y -= hero->GetVY();
	}

	
}





	


//ドロー
void CObjMain::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	
	

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0)
			{
				

				//表示位置の設定
				dst.m_top = i * 64.0f+m_scroll_y;
				dst.m_left = j * 64.0f+m_scroll_x;
				dst.m_right = dst.m_left + 64.0;
				dst.m_bottom = dst.m_top + 64.0;

				

				if (m_map[i][j] == 1|| m_map[i][j] == 3)
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
