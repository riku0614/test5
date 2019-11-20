#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"


//使用するネームスペース
using namespace GameL;


//マクロ
#define MAP_X  (75)
#define MAP_Y  (75)
#define ROOM_X (25)
#define ROOM_Y (25)


//オブジェクト：メイン
class CObjMain : public CObj
{
	public:
		CObjMain(int map[MAP_X][MAP_Y]);
		~CObjMain() {};
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//ドロー
		void SetScrollX(float s) { m_scroll_x = s; }//X方向のスクロール
		float GetScrollX() { return m_scroll_x; }
		void SetScrollY(float r) { m_scroll_y = r; }//Y方向へのスクロール
		float GetScrollY() { return m_scroll_y; }
		
		
		int m_map[MAP_X][MAP_Y];//マップ情報ブロック数（X=１２個、Y=１０個）
		int r_map[ROOM_X][ROOM_Y];

		void BlockHit(
			float *x, float *y, bool scroll_on_x,bool scroll_on_y,
			bool *up, bool *down, bool *left, bool *right,
			float *vx, float *vy, int *bt, int *c_id
		);
		
		void ItemHit(
			float *x, float *y, bool scroll_on_x, bool scroll_on_y,
			bool *up, bool *down, bool *left, bool *right,
			float *vx, float *vy, int *bt
		);
		//主人公と壁の交差判定
		bool HeroBlockCrossPoint(
			float x, float y, float vx, float vy,
			float *out_px, float *out_py, float *out_len
		);
	private:
		
		bool stop_flg;
		bool room_in;

		int map_chg;

		float spawn_point[7];
		int jx;
		int jy;
		
		unique_ptr<wchar_t> p[7];
		unique_ptr<wchar_t> r[7];

		float m_scroll_x;   //左右スクロール用
		float m_scroll_y;   //上下スクロール用

		float Dot(float ax, float ay, float bx, float by);
		float Cross(float ax, float ay, float bx, float by);
		//線と線の交差判定
		bool LineCrossPoint(
			float a1x, float a1y, float a2x, float a2y,
			float b1x, float b1y, float b2x, float b2y,
			float* out_px, float* out_py
		);

};