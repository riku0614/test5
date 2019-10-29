//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjHero.h"
#include "UtilityModule.h"

//使用するネームスペース
using namespace GameL;


//イニシャライズ
void CObjHero::Init()
{
	m_px = 0.0f; //位置
	m_py = 0.0f;
	m_vx = 0.0f; //移動ベクトル
	m_vy = 0.0f;

	m_hero_life = 3;//主人公の体力用変数


	//blockとの衝突確認用

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0;

	m_ani_time = 0;
	m_ani_frame = 1;//静止フレームを初期にする

	m_speed_power = 1.0f;
	m_ani_max_time = 6;
	m_ani_move = 0;

	m_posture = 1.0f; //右向き0.0ｆ　左向き1.0ｆ
	m_stamina_limid = 90.0f;


	//当たり判定用hitboxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_PLAYER, OBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	if (Input::GetVKey('M') == true)
	{
		Scene::SetScene(new CSceneMenu);
	}


	//Zキー入力で速度アップ
	if (m_stamina_limid>=0&&Input::GetVKey(VK_LSHIFT) == true&& Input::GetVKey('A') == true||
		m_stamina_limid >= 0 && Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('D') == true||
		m_stamina_limid >= 0 && Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('W') == true||
		m_stamina_limid >= 0 && Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('S') == true)
	{
		
		//ダッシュ時の速度
		m_speed_power = 1.0f;
		m_ani_max_time = 4;

		m_stamina_limid -= 0.3f;
	}
	else
	{
		//通常速度
		m_speed_power = 0.5f;
		m_ani_max_time = 4;

		if (m_stamina_limid < 90.0f)
		{
			m_stamina_limid += 0.3f;
		}

	}

	//キーの入力方向
	if (Input::GetVKey('D') == true)
	{
		m_vx += m_speed_power;
		m_posture = 0.0f;
		m_ani_time += 1;
	}
	else if (Input::GetVKey('A') == true)
	{
		m_vx -= m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	}
	else if (Input::GetVKey('W') == true)
	{
		m_vy -= m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	}
	else if (Input::GetVKey('S') == true)
	{
		m_vy += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	}

	//アニメーションのリセット
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	//アニメーションフレームのリセット
	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}
	//移動ベクトルの正規化
	//UnitVec(&m_vy, &m_vx);

	//摩擦
	m_vx += -(m_vx*0.09);
	m_vy += -(m_vy*0.09);

	//ブロックの当たり判定実行
	CObjMain* pb = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	pb->BlockHit(&m_px, &m_py, true,true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);
	
	//位置の更新
	m_px += m_vx;
	m_py += m_vy;


	//自身のhitboxを持ってくる
	CHitBox* hit = Hits::GetHitBox(this);

	//hitboxの位置の変更
	hit->SetPos(m_px, m_py);

	//主人公機オブジェクトと接触したら敵削除
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		//主人公のライフによる当たり判定の変化
		if (m_hero_life == 0)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);

			Scene::SetScene(new CSceneGameOver);
		}
		else
		{
			m_hero_life -= 1;
			
		}
	}

	

	
}

void CObjHero::Draw()
{
	int AniData[3][6] =
	{
		0,1,2,3,4,0,
		0,1,2,3,4,5,
		0,1,2,3,4,0,
	};

	//描画カラー情報　R=RED　G=Green　B=Blue　A=Alpha（透過情報）
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//スタミナバーの描画
	if (m_stamina_limid > 0 && m_stamina_limid < 90.0)
	{
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 64.0f;

		dst.m_top = 0.0f + m_py+64.0f;
		dst.m_left = 0.0f+ m_px;
		dst.m_right = m_stamina_limid + m_px;
		dst.m_bottom = 64.0f + m_py+64.0f;

		//1番目に登録したグラフィックをsrc.dst.cの情報を元に描画
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}
	
	//主人公のダッシュ時と通常時と静止時の描画
	if (Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('W') == true &&m_stamina_limid>0|| 
		Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('A') == true&&m_stamina_limid > 0 ||
		Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('S') == true && m_stamina_limid > 0 ||
		Input::GetVKey(VK_LSHIFT) == true && Input::GetVKey('D') == true && m_stamina_limid > 0)
	{
		//切り取り位置設定
		src.m_top = 90.0f * 5;
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 90;
		src.m_right = 90.0f + AniData[m_ani_move][m_ani_frame] * 90;
		src.m_bottom = 90.0f * 6;

	}
	else if (Input::GetVKey('W') == true || Input::GetVKey('A') == true||
		Input::GetVKey('S') == true || Input::GetVKey('D') == true)
	{
		//切り取り位置設定
		src.m_top = 90.0f * 9;
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 90;
		src.m_right = 90.0f + AniData[m_ani_move][m_ani_frame] * 90;
		src.m_bottom = 90.0f * 10;
	}
	else
	{
		//切り取り位置設定
		src.m_top = 720.0f;
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 90;
		src.m_right = 90.0f + AniData[m_ani_move][m_ani_frame] * 90;
		src.m_bottom = 810.0f;
	}

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f*m_posture) + m_px;
	dst.m_right = (64 - 64.0f*m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;

	//1番目に登録したグラフィックをsrc.dst.cの情報を元に描画
	Draw::Draw(0, &src, &dst, c, 0.0f);

}
