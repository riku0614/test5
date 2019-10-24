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

/*BlockDrawMethod関数
  引数１　float   x   :リソース切り取り位置X
  引数２　float   y   :リソース切り取り位置Y
  引数３　RECT_F* dst :描画位置
  引数４　float   c[] :カラー情報
  ブロックを64X64限定描画用。リソース切り取り位置のみx,yで
  設定できる*/



	


//ドロー
void CObjMain::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (m_map[i][j] > 0)
			{
				//表示位置の設定
				dst.m_top = i * 64.0f;
				dst.m_left = j * 64.0f;
				dst.m_right = dst.m_left + 64.0;
				dst.m_bottom = dst.m_top + 64.0;

				if (m_map[i][j] == 1)
				{
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = src.m_left + 64.0f;
					src.m_bottom = src.m_top + 64.0f;

					Draw::Draw(0, &src, &dst, c, 0.0f);
				}
				
			}
		}

	}
}
