//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjItem.h"
#include "GameL/HitBoxManager.h"
#include "UtilityModule.h"


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
	ix = 0;
	iy = 0;

	//m_px = 0.0f;
	//m_py = 0.0f;
	m_vx = 0.0f;
	m_vy = 0.0f;


	//m_scroll_x = -2850.0f;
	//m_scroll_y = -64.0f;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] == 5)
			{

				
				//メインの位置を取得
				CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
				float hx = main->GetScrollX();
				float hy = main->GetScrollY();

				ix = j * 64.0f;//アイテムの位置Xをとる
				iy = i * 64.0f;//アイテムの位置Yをとる

				//当たり判定用hitboxを作成
				Hits::SetHitBox(this, ix, iy, 32, 32, ELEMENT_ITEM, OBJ_ITEM, 1);

				
			}
		}
	}
	

}

//アクション
void CObjItem::Action()
{

	

	//メインの位置を取得
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(ix + main->GetScrollX(), iy + main->GetScrollY());

	//主人公のアイテムと当たったフラグを持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//アイテムに当たって、なおかつ'E'を押したときにアイテムが消える処理
	if (hero->Getflag() == true)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
	}

	
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

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] == 5)
			{
				//表示位置の設定
				dst.m_top = i * 64.0f + hy;
				dst.m_left = j * 64.0f + hx;
				dst.m_right = dst.m_left + 32.0f;
				dst.m_bottom = dst.m_top + 32.0f;

				Draw::Draw(8, &src, &dst, c, 0.0f);
			}
		}
	}
	
}