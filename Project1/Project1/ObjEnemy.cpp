//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/HitBoxManager.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "ObjMain.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjEnemy::Init()
{
	m_vx = 1.0f;
	m_vy = 1.0f;
	m_px = 0.0f; //位置
	m_py = 0.0f;

	m_flg = true;
	//移動ベクトルの正規化
	UnitVec(&m_vy, &m_vx);

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);

}

//アクション
void CObjEnemy::Action()
{
	//主人公機と誘導弾丸の角度を取る
	CObjHero* obj = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//主人公機が存在する場合、誘導角度を計算する
	if (obj != nullptr)
	{
		float x = obj->GetX()-m_px;
		float y = obj->GetY()-m_py;
		float ar = GetAtan2Angle(x, -y);

		//弾丸の現在の向いてる角度を取る
		float br = GetAtan2Angle(m_vx, -m_vy);

		float r = 3.14 / 180.0f; //角度１°
		if (ar < br)
		{
			//移動方向に+１°加える
			m_vx = m_vx * cos(r) - m_vy * sin(r);
			m_vy = m_vy * cos(r) + m_vx * sin(r);
		}
		else
		{
			//移動方向に-１°加える
			m_vx = m_vx * cos(-r) - m_vy * sin(-r);
			m_vy = m_vy * cos(-r) + m_vx * sin(-r);
		}
		UnitVec(&m_vx, &m_vy);
		
		

	}
	//追従移動
	if (Input::GetVKey('S') == true &&m_flg == true)
	{
		m_flg = false;
		m_px;
		m_py += m_vy + 5.0f - obj->GetVY();
	}
	else if (Input::GetVKey('W') == true && m_flg == true)
	{
		m_flg = false;
		m_px;
		m_py += m_vy - 5.0f + (-obj->GetVY());
	}
	else if (Input::GetVKey('A') == true && m_flg == true)
	{
		m_flg = false;
		m_px += m_vx - 5.0f + (-obj->GetVX());
		m_py;
	}
	else if (Input::GetVKey('D') == true && m_flg == true)
	{
		m_flg = false;
		m_px += m_vx + 5.0f - obj->GetVX();
		m_py;
	}
	else
	{
		m_flg = true;
		m_px += m_vx;
		m_py += m_vy;
	}
	//hitboxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);

	
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

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0) + m_px;
	dst.m_right = (64 - 64.0f) + m_px ;
	dst.m_bottom = 64.0f + m_py;

	//1番目に登録したグラフィックをsrc.dst.cの情報を元に描画
	Draw::Draw(3, &src, &dst, c, 0.0f);
}