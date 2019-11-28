//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"

#include "GameHead.h"
#include "ObjGimmick.h"
#include "GameL/HitBoxManager.h"
#include "UtilityModule.h"


//使用するネームスペース
using namespace GameL;


//コンストラクタ



//イニシャライズ
void CObjGimmick::Init()
{
	//変数初期化
	ix = 0;
	iy = 0;

	m_vx = 0.0f;
	m_vy = 0.0f;

	h_count = 0;
	gimmick_flg = false;
	stop_flg = true;


	//敵出現ラインの列を検索
	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{	//列の中から4を探す
			if (m_map[i][j] == 7)
			{

				pi = i;
				pj = j;

				CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
				float hx = main->GetScrollX();
				float hy = main->GetScrollY();

				ix = j * 64.0f;//アイテムの位置Xをとる
				iy = i * 64.0f;//アイテムの位置Yをとる

				Hits::SetHitBox(this, ix, iy, 64, 64, ELEMENT_BLUE, OBJ_GIMMICK, 1);


			}
		}
	}

}

//アクション
void CObjGimmick::Action()
{


	

	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(ix + main->GetScrollX(), iy + main->GetScrollY());
	

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{

		gimmick_flg = true;

		
	}
	
	
	



}

//ドロー
void CObjGimmick::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//描画切り取り位置
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;

	//メインの位置を取得
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	float hx = main->GetScrollX();
	float hy = main->GetScrollY();

	
		if (gimmick_flg==true)
		{
				//上
				
			if (m_map[pi][pj] == 7&& m_map[pi-1][pj]==10)
			{
					//表示位置の設定
					dst.m_top = pi-0.1f * 64.0f +hy;
					dst.m_left = pj * 64.0f +hx ;
					dst.m_right = dst.m_left + 64.0f;
					dst.m_bottom = dst.m_top + 64.0f;

					gimmick_flg == false;

				}
				//下
				else if (m_map[pi][pj] == 7 && m_map[pi + 1][pj] == 10)
				{
					//表示位置の設定
					dst.m_top = pi+0.1f * 64.0f + hy;
					dst.m_left = pj * 64.0f + hx;
					dst.m_right = dst.m_left + 64.0f;
					dst.m_bottom = dst.m_top + 64.0f;

					gimmick_flg == false;
				}
				//左
				else if (m_map[pi][pj] == 7 && m_map[pi][pj-1] == 10)
				{
					//表示位置の設定
					dst.m_top = pi * 64.0f + hy;
					dst.m_left = pj-0.1f * 64.0f + hx;
					dst.m_right = dst.m_left + 64.0f;
					dst.m_bottom = dst.m_top + 64.0f;

					gimmick_flg == false;
				}
				//右
				else if (m_map[pi][pj] == 7 && m_map[pi][pj+1] == 10)
				{
					//表示位置の設定
					dst.m_top = pi * 64.0f + hy;
					dst.m_left = pj+0.1f * 64.0f + hx;
					dst.m_right = dst.m_left + 64.0f;
					dst.m_bottom = dst.m_top + 64.0f;

					gimmick_flg == false;
			}

				

			Draw::Draw(15, &src, &dst, c, 0.0f);
		}

}