//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "SceneMain.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;




CObjEnemy::CObjEnemy(int map[100][100])
{
	memcpy(m_map, map, sizeof(int)*(100 * 100));
}
//イニシャライズ
void CObjEnemy::Init()
{

	m_vx = 1.0f;
	m_vy = 1.0f;
	m_ex = 64.0f; //位置
	m_ey = 64*3.0f;

	m_flg = 0;
	
	
	//blockとの衝突確認用

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	
	//主人公の位置を取得
	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_ex, m_ey, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);


}

//アクション
void CObjEnemy::Action()
{
	
	int km_map[100][100];
	
	if(m_hit_left==true)
	{
		m_flg=1;
	}
	else if (m_hit_down == true)
	{
		m_flg=2;
	}
	else if (m_hit_right == true)
	{
		m_flg=3;
	}
	else if (m_hit_up == true)
	{
		m_flg = 0;
	}
	

	if (m_flg == 0)
	{
		m_ex += 5.0f*2;
		
		
	}
    else if (m_flg == 1)
	{
		m_ey += 5.0f*2;
	}
	else if (m_flg == 2)
	{
		m_ex -= 5.0f*2;
	}
	else if (m_flg == 3)
	{
		m_ey -= 5.0f*2;
	}
	
	//高速移動によるblock判定
	bool b;
	float pxx, pyy, r;
	CObjMain* pbb = (CObjMain*)Objs::GetObj(OBJ_MAIN);

	if (pbb->GetScrollX() > 0)
		pbb->SetScrollX(0);
	if (pbb->GetScrollY() > 0)
		pbb->SetScrollY(0);
	//移動方向にrayを飛ばす
	float vx;
	
	if (m_vx > 0)
		vx = 500 - pbb->GetScrollX();
	else
		vx = 0 - pbb->GetScrollX();

	//ray判定
	b = pbb->HeroBlockCrossPoint(m_ex - pbb->GetScrollX() + 64, m_ey - pbb->GetScrollY() + 64, vx, 0.0f, &pxx, &pyy, &r);

	if (b == true)
	{
		//交点取得
		px = pxx + pbb->GetScrollX();
		py = pyy - pbb->GetScrollY();

		float aa = (m_ex)-px;//A（交点→主人公の位置）ベクトル
		float bb = (m_ex + m_vx) - px;//B（交点→主人公の移動先位置）ベクトル

									  //主人公の幅分オフセット
		if (vx > 0)
			px += -64;
		else
			px += 2;

		//AとBが逆を向いている（主人公が移動先の壁を越えている）
		if (aa*bb < 0)
		{
			//移動ベクトルを（交点→主人公の位置）ベクトルにする
			m_vx = px - m_ex;
		}
	}
	else
	{
		px = 0.0f;
		py = 0.0f;
	}

	//ブロックタイプ検知用の変数がないためのダミー
	int d;
	//ブロックの当たり判定実行
	CObjMain* pb = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	pb->BlockHit(&m_ex, &m_ey, false, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d);

	CObjMain* scroll = (CObjMain*)Objs::GetObj(OBJ_MAIN);
    //自身のhitboxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//hitboxの位置の変更
	hit->SetPos(m_ex + scroll->GetScrollX(), m_ey + scroll->GetScrollY());

	
}

//ドロー
void CObjEnemy::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

				//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	CObjMain* scroll = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	//表示位置の設定
	dst.m_top = 0.0f + m_ey+scroll->GetScrollY();
	dst.m_left = (64.0) + m_ex+scroll->GetScrollX();
	dst.m_right = (64 - 64.0f)+m_ex+scroll->GetScrollX();
	dst.m_bottom = 64.0f + m_ey+scroll->GetScrollY();

	//3番目に登録したグラフィックをsrc.dst.cの情報を元に描画
	Draw::Draw(3, &src, &dst, c, 0.0f);
}
/*マップ情報の取得メゾット
引数１　：要素番号X
引数２　：要素番号Y
戻り値　：要素を返す。要素番号が配列外の場合-1を返す
指定した要素番号のm_mapを返す*/
int CObjEnemy::GetMap(int x, int y)
{

	//x.yが例外的な値の場合、失敗(－1)を返す
	if (x < MAP_MIN)return -1;
	if (y < MAP_MIN)return -1;
	if (x >= 100)return 1;
	if (y >= 100)return 1;

	//要素を返す
	return m_map[y][x];
}

/*マップにBlockのIDを入れるメゾット
引数１　int  x ： 要素番号X
引数２　int  y ： 要素番号Y
引数３　int id ： 要素に入れるID
指定した要素番号のmapにIDを入れる*/
void CObjEnemy::SetMap(int x, int y, int id)
{
	//オーバーフローによる例外処理
	if (x < MAP_MIN)   return;
	if (y < MAP_MIN)   return;
	if (x >= 100) return;
	if (y >= 100) return;

	//IDをMapに入れる
	m_map[y][x] = id;

	return;

}

/*マップオーバーフローチェックメゾット
引数１　int x :マップ要素番号x
引数２　int y :マップ要素番号y
戻り値　bool 領域外＝false　領域内＝true
要素番号のオーバーフローチェックをします。*/
bool CObjEnemy::OverFlowCheck(int x, int y)
{
	if (x < MAP_MIN)         return false;
	if (y < MAP_MIN)         return false;
	if (x >= 100)         return false;
	if (y >= 100)         return false;

	return true;

}

/*探索バッファチェック用メゾット
引数１　int x :マップ要素番号x
戻り値　データがある場所*/
int CObjEnemy::BufferCheck(XY b[])
{
	for (int i = 0; i < BUFFER_MAX; i++)
	{
		if (b[i].x != BUFFER_NO_DATA && b[i].x != BUFFER_DELETE_DATA)
			return i;
	}
	return -1;


}

/*4方向サーチ＆登録メゾット
引数１　int  set_x 　　　　　：検索出発のX位置
引数２　int  set_y 　　　　　：検索出発のY位置
引数３　int[][] c_map  　　　：キャラクターブロックマップ
引数４  int[][] km_map 　　　：距離を入れるマップ
引数５　XY[] buffer    　　　：バッファ
引数６　int* buffer_count    ：バッファカウント
戻り値　　：なし
検索出発位置から４方向の要素を調べて距離を登録する*/
void CObjEnemy::EveryDirectionSearchSet
(int set_x, int set_y,
	int c_map[100][100], int km_map[100][100],
	XY buffer[], int *buffer_count
)
{
	//検索方向用配列（上下左右）
	const XY search[SEARCH_MAX] = { { 1,0 },{ -1,0 },{ 0,-1 },{ 0,1 } };

	//キャラクターID取得　このIDのみ検索する
	int c_id = 2;

	//ゴールの上下左右の配列を検索して同じIDがあるかどうか調べる
	int count = BufferCheck(buffer);
	for (int i = 0; i < SEARCH_MAX; i++)
	{
		//バッファもつ位置から検索方向の要素番号を出す
		int x = search[i].x + buffer[count].x;
		int y = search[i].y + buffer[count].y;

		//オーバーフローチェック
		if (OverFlowCheck(x, y) == false)
			continue;

		//隣接ノードがあったらバッファ・距離地の更新
		if (c_map[y][x] == c_id)
		{
			if (km_map[y][x] > km_map[set_y][set_x] + SEARCH_MAP_NEXT)
			{
				km_map[y][x] = km_map[set_y][set_x] + SEARCH_MAP_NEXT;
				(*buffer_count)++;
				buffer[*buffer_count].x = x;
				buffer[*buffer_count].y = y;


			}
		}

	}

	//検索したのでデータを破棄で上書き
	buffer[count].x = BUFFER_DELETE_DATA;
	buffer[count].y = BUFFER_DELETE_DATA;
	return;
}

/*ダイクストラ法メゾット
引数１　int[][] c_map  　　　：キャラクターブロック用マップ配列
引数２  int[][] km_map 　　　：距離を入れるマップ配列
引数３　int    goal_x　　　　：ゴールノードの要素番号X
引数４　int    goal_y    　　：ゴールノードの要素番号Y
戻り値　int    :探索数*/
int CObjEnemy::Dijkstras(int c_map[100][100], int km_map[100][100],
	int goal_x, int goal_y)
{
	//バッファカウント用
	int buffer_count = 0;
	int point = 0;

	//探索バッファ
	XY buffer[BUFFER_MAX];
	memset(buffer, 0xFF, sizeof(XY) * BUFFER_MAX);

	//オーバーフローとゴールブロックにならないID例外処理
	if (OverFlowCheck(goal_x, goal_y) == false) return 0;
	if (c_map[goal_y][goal_x] == 9) return 0;
	if (c_map[goal_y][goal_x] == 3) return 0;

	//ゴールの設置
	int c_id = c_map[goal_y][goal_x];//キャラクターID取得　このIDのみ検索する
	km_map[goal_y][goal_x] = 0;
	buffer[buffer_count].x = goal_x;//ゴールノード位置をバッファ登録
	buffer[buffer_count].y = goal_y;

	//検索する位置の上下左右の配列を検索して同じIDがあるかどうか調べる
	int search_count = 0;//検索したノード数
	do
	{
		EveryDirectionSearchSet(buffer[point].x, buffer[point].y, c_map, km_map, buffer, &buffer_count);
		point = BufferCheck(buffer);
		search_count++;
	} while (point != BUFFER_NO_DATA);

	return search_count;
}

