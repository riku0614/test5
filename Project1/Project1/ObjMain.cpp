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

/*BlockHit関数
  引数１　　float* x             :判定を行うobjectのX位置
  引数２　　float* y             :判定を行うobjectのY位置
  引数３　　bool  scroll_on      :判定を行うobjectはスクロールに影響を与えるかどうか（true=与える　false=与えない）
  引数４　　bool* up             :上下左右判定の上部分にあたっているかどうかを返す
  引数５　　bool* down           :上下左右判定の下部分にあたっているかどうかを返す
  引数６　　bool* left           :上下左右判定の左部分にあたっているかどうかを返す
  引数７　　bool* right          :上下左右判定の右部分にあたっているかどうかを返す
  引数８　　float* vx            :左右判定時の反発による移動方向・力の値を変えて返す
  引数９　　float* vy            :上下判定時による自由落下運動の移動方向・力の値を変えて返す
  引数１０　int* bt            　:下部分判定時、特殊なブロックのタイプを返す
  判定を行うobjectとブロック64*64限定で、当たり判定と上下左右判定を行う
  その結果は引数４～１０に返す*/

void CObjMain::BlockHit(
	float *x, float *y, bool scroll_on,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, int *bt
)
{
	//主人公の衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるブロックの種類の初期化
	*bt = 0;

	//m=mapの全要素にアクセス
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] ==2)
			{
				//要素番号を座標に変更
				float bx = j * 64.0f;
				float by = i * 64.0f;

				//スクロールの影響
				float scroll = scroll_on ? m_scroll_x : 0;
				//主人公とブロックの当たり判定
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 64.0f > by) && (*y < by + 64.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;

					//長さを求める
					float len = sqrt(rvx*rvx + rvy * rvy);


					//角度を求める
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					//lenがある一定の長さのより短い場合判定に入る
					if (len < 88.0f)
					{
						//角度で左右を判定
						if ((r < 45 && r>0) || r > 315)
						{
							//右
							*right = true;//主人公から見て、左の部分が衝突している
							*x = bx + 64.0f + (scroll);//ブロックの位置-主人公の幅
							*vx = -(*vx)*0.1f;//-VX*反発係数
						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;//主人公から見て、下の部分が衝突している
							*y = by - 64.0f;//ブロックの位置-主人公の幅
							if (m_map[i][j] == 2)
								*bt = m_map[i][j];
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;//主人公から見て、右の部分が衝突している
							*x = bx - 64.0f + (scroll);//ブロックの位置-主人公の幅
							*vx = -(*vx)*0.1f;//-VX*反発係数
						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//主人公から見て、上の部分が衝突している
							*y = by + 64.0f;//ブロックの位置-主人公の幅
							if (*vy < 0)
							{
								*vy = 0.0f;
							}


						}
					}


				}


			}
		}
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
