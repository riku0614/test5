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




CObjEnemy::CObjEnemy(int map[75][75])
{
	memcpy(m_map, map, sizeof(int)*(75 * 75));
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
	
	

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_ex, m_ey, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);


}

//アクション
void CObjEnemy::Action()
{
	
	int km_map[75][75];
	
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
