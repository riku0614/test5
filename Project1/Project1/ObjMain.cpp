//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/UserData.h"

#include "GameHead.h"
#include "ObjMain.h"


//使用するネームスペース
using namespace GameL;

CObjMain::CObjMain(int map[MAP_X][MAP_Y])
{
	memcpy(m_map, map, sizeof(int)*(MAP_X * MAP_Y));
}





//イニシャライズ
void CObjMain::Init()
{
	m_scroll_x = 64.0f;
	m_scroll_y = 64.0f;

	map_chg = 0;
	stop_flg = false;
}

//アクション
void CObjMain::Action()
{
	if (map_chg == 0)
	{
		;
	}
	else if (map_chg >= 1 && stop_flg == true)
	{
		unique_ptr<wchar_t> p[7];
		int size;
		p[0] = Save::ExternalDataOpen(L"マップ2.csv", &size);


		int map[MAP_X][MAP_Y];
		int count = 1;

		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				int w = 0;
				swscanf_s(&p[map_chg-1].get()[count], L"%d", &w);

				map[i][j] = w;
				count += 2;

			}
		}
		memcpy(m_map, map, sizeof(int)*(MAP_X * MAP_Y));
		stop_flg = false;
	}

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
	if (hy < 80)
	{
		hero->SetY(80);
		m_scroll_y -= hero->GetVY();
	}

	//下方スクロールライン
	if (hy > 500)
	{
		hero->SetY(500);
		m_scroll_y -= hero->GetVY();


	}



	
	
	
}

/*内積関数
　引数1,2 float   ax  ,  ay  :Aベクトル
  引数3,4 float   bx  ,  by  :Bベクトル
  戻り値　float   ：射影
  内容　AベクトルとBベクトルて内積を行い射影を求める*/
float CObjMain::Dot(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * bx + ay * by;

	return t;
}

/*外積関数
　引数1,2 float   ax  ,  ay  :Aベクトル
  引数3,4 float   bx  ,  by  :Bベクトル
  戻り値　float   ：射影
  内容　AベクトルとBベクトルて内積を行い射影を求める*/
float CObjMain::Cross(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * by - ay * bx;

	return t;
}

//符号を求めるマクロ
#define SGN(x) 1-(x<=0)-(x<0)

/*線と線の交差判定関数
  引数　float 1, 2  a1_x,a1y            :軸ベクトルAの始点
  引数　float 3, 4  a2x,a2y             :軸ベクトルAの終点
  引数　float 5, 6  b1x,b1y             :軸ベクトルAの始点
  引数　float 7, 8  b2x,b2y             :軸ベクトルAの始点
  引数　float 9, 10  out_px,out_py      :軸ベクトルAの始点
  戻り値　bool  :true=交点有り　false=交点無し
  内容：引数のA・Bベクトルの交点を見つけ、out_pxとout_pyの返す*/
bool CObjMain::LineCrossPoint(
	float a1x, float a1y, float a2x, float a2y,
	float b1x, float b1y, float b2x, float b2y,
	float* out_px, float* out_py
)
{
	//エラーコード
	*out_px = -99999.0f; *out_py = -99999.0f;

	//Aベクトル作成(a2←a1)
	float ax = a2x - a1x;  float ay = a2y - a1y;

	//Bベクトル作成(b2←b1)
	float bx = b2x - b1x;  float by = b2y - b1y;

	//Cベクトル作成(b1←a1)
	float cx = b1x - a1x;  float cy = b1y - a1y;

	//Dベクトル作成(b2←a1)
	float dx = b2x - a1x;  float dy = b2y - a1y;
	//A X Cの射影とA X Bの射影を求める
	float t1 = Cross(ax, ay, cx, cy);
	float t2 = Cross(ax, ay, dx, dy);
	//符号が同じ方向になっているかどうかチェック
	if (SGN(t1) == SGN(t2))
		return false;
	//射影の絶対値化
	t1 = abs(t1);  t2 = abs(t2);

	//交点を求める
	float px = bx * (t1 / (t1 + t2)) + b1x;
	float py = by * (t1 / (t1 + t2)) + b1y;

	//APベクトル（ｐ←a1）
	float apx = px - a1x;  float apy = py - a1y;

	//BPベクトル（p←a2)
	float bpx = px - a2x;  float bpy = py - a2y;

	//A・APの射影とA・BPの射影を求める
	float w1 = Dot(ax, ay, apx, apy);
	float w2 = Dot(ax, ay, bpx, bpy);

	//符号チェック
	if (SGN(w1) == SGN(w2))
		return false; //交点が外

	//交点を返す
	*out_px = px; *out_py = py;

	return true;

}

/*主人公と壁の交差判定関数
　引数1,2 float  x,y          :主人公の位置
  引数3,4 float  vx,vy        :主人公の移動ベクトル
  引数5,6 float* out_px,out_y :Blockとの交点
  引数7   float* out          :一から交点までの距離
  主人公の位置＋移動ベクトルと各ブロックの変で好転の判定を行い
  最も近い交点の位置と距離を返す*/
bool CObjMain::HeroBlockCrossPoint(
	float x, float y, float vx, float vy,
	float *out_px, float *out_py, float *out_len
)

{

	bool pb = false;      //交点確認用
	float len = 99999.0f; //交点との距離
	//ブロックの辺ベクトル
	float edge[4][4] =
	{
		{ 0, 0,64, 0},
		{64, 0,64,64},
		{64,64, 0,64},
		{ 0,64, 0, 0},
	};

	//m_mapの全要素にアクセス

		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] > 0 && m_map[i][j] != 5)
				{
					//ブロックの４辺から交点を探す
					for (int k = 0; k < 4; k++)
					{
						//交点を探す
						float px, py;
						bool b;
						float l = 0.0f;
						b = LineCrossPoint
						(x, y, x + vx, y + vy,
							j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],
							&px, &py);

						//交点チェック
						if (b == true)
						{
							//交点との距離を求める
							l = sqrt((px - x)*(px - x) + (py - y)*(py - y));

							//見つけた交点の中で最も距離が短いものを探す
							if (len > l)
							{
								len = l;
								*out_px = px;
								*out_py = py;
								pb = true;
							}
						}

					}
				}
			}
		}
	
	*out_len = len;
	return pb;


}
/*BlockHit関数
  引数１　　float* x             :判定を行うobjectのX位置
  引数２　　float* y             :判定を行うobjectのY位置
  引数３　　bool  scroll_on_x    :判定を行うobjectはスクロールに影響を与えるかどうか（true=与える　false=与えない）
  引数５　　bool* up             :上下左右判定の上部分にあたっているかどうかを返す
  引数６　　bool* down           :上下左右判定の下部分にあたっているかどうかを返す
  引数７　　bool* left           :上下左右判定の左部分にあたっているかどうかを返す
  引数８　　bool* right          :上下左右判定の右部分にあたっているかどうかを返す
  引数９　　float* vx            :左右判定時の反発による移動方向・力の値を変えて返す
  引数１０　　float* vy            :上下判定時による自由落下運動の移動方向・力の値を変えて返す
  引数１１　int* bt            　:下部分判定時、特殊なブロックのタイプを返す
  判定を行うobjectとブロック64*64限定で、当たり判定と上下左右判定を行う
  その結果は引数４～１０に返す*/

void CObjMain::BlockHit(
	float *x, float *y, bool scroll_on_x,bool scroll_on_y,
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
	
	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{


			if (m_map[i][j] <= 9 && m_map[i][j] >= 3)
			{
				//要素番号を座標に変更
				float bx = j * 64.0f;
				float by = i * 64.0f;

				//スクロールの影響
				float scroll_x = scroll_on_x ? m_scroll_x : 0;
				float scroll_y = scroll_on_y ? m_scroll_y : 0;
				//主人公とブロックの当たり判定
				if ((*x + (-scroll_x) + 64.0f > bx) && (*x + (-scroll_x) < bx + 64.0f) && (*y + (-scroll_y) + 64.0f > by) && (*y + (-scroll_y) < by + 64.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scroll_x)) - bx;
					float rvy = (*y + (-scroll_y)) - by;

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
						if ((r < 45 && r >= 0) || r > 315)
						{
							//右
							*right = true;//主人公から見て、左の部分が衝突している
							*x = bx + 64.0f + (scroll_x);//ブロックの位置-主人公の幅]
							if (m_map[i][j] == 3)
							{
								stop_flg = true;
								map_chg++;
							}
							*vx = -(*vx)*0.1f;//-VX*反発係数
						}
						if (r > 45 && r < 135)
						{
							//上
							*down = true;//主人公から見て、下の部分が衝突している
							*y = by - 64.0f + (scroll_y);//ブロックの位置-主人公の幅
							if (m_map[i][j] == 2)
								*bt = m_map[i][j];
							if (m_map[i][j] == 3)
							{
								stop_flg = true;
								map_chg++;
							}
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//左
							*left = true;//主人公から見て、右の部分が衝突している
							*x = bx - 64.0f + (scroll_x);//ブロックの位置-主人公の幅
							if (m_map[i][j] == 3)
							{
								stop_flg = true;
								map_chg++;
							}
							*vx = -(*vx)*0.1f;//-VX*反発係数
						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;//主人公から見て、上の部分が衝突している
							*y = by + 64.0f + (scroll_y);//ブロックの位置-主人公の幅
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
/*ItemHit関数
  引数１　　float* x             :判定を行うobjectのX位置
  引数２　　float* y             :判定を行うobjectのY位置
  引数３　　bool  scroll_on_x    :判定を行うobjectはスクロールに影響を与えるかどうか（true=与える　false=与えない）
  引数５　　bool* up             :上下左右判定の上部分にあたっているかどうかを返す
  引数６　　bool* down           :上下左右判定の下部分にあたっているかどうかを返す
  引数７　　bool* left           :上下左右判定の左部分にあたっているかどうかを返す
  引数８　　bool* right          :上下左右判定の右部分にあたっているかどうかを返す
  引数９　　float* vx            :左右判定時の反発による移動方向・力の値を変えて返す
  引数１０　　float* vy            :上下判定時による自由落下運動の移動方向・力の値を変えて返す
  引数１１　int* bt            　:下部分判定時、特殊なブロックのタイプを返す
  判定を行うobjectとブロック64*64限定で、当たり判定と上下左右判定を行う
  その結果は引数４～１０に返す*/

void CObjMain::ItemHit(
	float *x, float *y, bool scroll_on_x, bool scroll_on_y,
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
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 5)
				{
					//要素番号を座標に変更
					float bx = j * 64.0f;
					float by = i * 64.0f;

					//スクロールの影響
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//主人公とブロックの当たり判定
					if ((*x + (-scroll_x) + 64.0f > bx) && (*x + (-scroll_x) < bx + 32.0f) && (*y + (-scroll_y) + 64.0f > by) && (*y + (-scroll_y) < by + 32.0f))
					{
						//上下左右判定

						//vectorの作成
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

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
								*x = bx + 32.0f + (scroll_x);//ブロックの位置-主人公の幅
								*vx = -(*vx)*0.25f;//-VX*反発係数
							}
							if (r > 45 && r < 135)
							{
								//上
								*down = true;//主人公から見て、下の部分が衝突している
								*y = by - 64.0f + (scroll_y);//ブロックの位置-主人公の幅
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//左
								*left = true;//主人公から見て、右の部分が衝突している
								*x = bx - 64.0f + (scroll_x);//ブロックの位置-主人公の幅
								*vx = -(*vx)*0.1f;//-VX*反発係数
							}
							if (r > 225 && r < 315)
							{
								//下
								*up = true;//主人公から見て、上の部分が衝突している
								*y = by + 32.0f + (scroll_y);//ブロックの位置-主人公の幅
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
	
	

		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] > 0)
				{


					//表示位置の設定
					dst.m_top = i * 64.0f + m_scroll_y;
					dst.m_left = j * 64.0f + m_scroll_x;
					dst.m_right = dst.m_left + 64.0;
					dst.m_bottom = dst.m_top + 64.0;


					//床テクスチャ
					if (m_map[i][j] == 1 || m_map[i][j] == 5)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(1, &src, &dst, c, 0.0f);
					}
					//階段テクスチャ
					if (m_map[i][j] == 3)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(7, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 4)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(3, &src, &dst, c, 0.0f);
					}
				}
			}

		}
	
}
