//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjMain.h"


//使用するネームスペース
using namespace GameL;

CObjMain::CObjMain(int map[10][10])
{
	memcpy(m_map, map, sizeof(int)*(10 * 10));
}

//イニシャライズ
void CObjMain::Init()
{
	
}

//アクション
void CObjMain::Action()
{
	
}

//ドロー
void CObjMain::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	for (int i = 0; i < 10; i++)
	{



		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0 && m_map[i][j] != 4)
			{
				//表示位置の設定
				dst.m_top = i * 64.0f;
				dst.m_left = j * 64.0f;
				dst.m_right = dst.m_left + 64.0;
				dst.m_bottom = dst.m_top + 64.0;
				if (m_map[i][j] == 2)
				{
					//スタートブロック
					BlockDraw(320.0f + 64.0f, 0.0f, &dst, c);
				}
				else if (m_map[i][j] == 3)
				{
					//ゴールブロック
					BlockDraw(320.0f + 64.0f, 64.0f, &dst, c);
				}
				else if (m_map[i][j] == 4)
				{
					;
				}
				else
				{
					BlockDraw(320.0f, 0.0f, &dst, c);

				}
			}
		}

	}
}
