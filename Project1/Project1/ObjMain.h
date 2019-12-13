#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"


//使用するネームスペース
using namespace GameL;

//a

//マクロ
#define MAP_X  (75)
#define MAP_Y  (75)
#define ROOM_X (25)
#define ROOM_Y (25)
#define MAP_NUMBER (8)
#define BAR (26)
#define BLOCK_SIZE_X (64.0f)
#define BLOCK_SIZE_Y (64.0f)
#define ITEM_SIZE_X (32.0f)
#define ITEM_SIZE_Y (32.0f)
#define ROOM_NUMBER (7)

//オブジェクト：メイン
class CObjMain : public CObj
{
	public:
		CObjMain(int map[ROOM_X][ROOM_Y]);
		~CObjMain() {};
		void Init();	//イニシャライズ
		void Action();	//アクション
		void Draw();	//ドロー
		void SetScrollX(float s) { m_scroll_x = s; }//X方向のスクロール
		float GetScrollX() { return m_scroll_x; }
		void SetScrollY(float r) { m_scroll_y = r; }//Y方向へのスクロール
		float GetScrollY() { return m_scroll_y; }
		void SetDelete(bool b) { delete_flg = b; }
		bool RoomFlag() { return room_in; }
		int RoomMapData() { return r_map[ROOM_X][ROOM_Y]; }
		int MapChangeData() { return map_chg; }
		bool GetFlug() { return stop_flg; }
		bool GetFlug2() { return stop_flg2; }
		int GetHitboxCount1() { return g_count1; }
		int GetHitboxCount2() { return g_count2; }


		void SetMapItem(bool mi) { map_Item; }
		bool GetMapItem() { return map_Item; }
		void SetMapItem_2(bool mi) { map_Item_2; }
		bool GetMapItem_2() { return map_Item_2; }
		void SetMapItem_3(bool mi) { map_Item_3; }
		bool GetMapItem_3() { return map_Item_3; }

		int m_map[MAP_X][MAP_Y];//マップ情報ブロック数（X＝７５個、Y=７５個）
		int r_map[ROOM_X][ROOM_Y];//マップ情報ブロック数（X＝30個、Y=30個）

		void BlockHit(
			float *x, float *y, bool scroll_on_x,bool scroll_on_y,
			bool *up, bool *down, bool *left, bool *right,
			float *vx, float *vy, int *bt, int *c_id, int *k_id
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
		
		float save_x[MAP_NUMBER][2];//マップを行き来する用の主人公の位置を登録する配列
		float save_y[MAP_NUMBER][2];
		float save_scroll_x[MAP_NUMBER][2];//マップを行き来する用のスクロール情報を登録する配列
		float save_scroll_y[MAP_NUMBER][2];
		int save_map[MAP_X][MAP_Y];
		int save_room_map[ROOM_X][ROOM_Y][ROOM_NUMBER];

		bool stop_flg;//マップ切り替えを一度だけしか
		bool stop_flg2;
		bool first_stop;
		bool first_stop2;
		bool room_in;    //教室マップへの切り替えのフラグ
		bool delete_flg;
		bool plane_chg_hole;
		bool pepepe;
		bool pepepe_2;
		bool room_chg_stop;

		bool font_flg;

		int g_count1;
		int g_count2;
		int map_chg;     //マップ切り替えを管理するための変数
		int room_chg;
		int ix;
		int iy;
		int size;
		int m_time;

		float spawn_point[MAP_NUMBER]; //map毎の初期値を関数から入れる用の変数
		int jx;
		int jy;
		
		unique_ptr<wchar_t> p[MAP_NUMBER]; //ユーザーデータのメインマップデータを保存するための変数
		unique_ptr<wchar_t> r[MAP_NUMBER]; //ユーザーデータの教室マップデータを保存するための変数


		float m_scroll_x;   //左右スクロール用
		float m_scroll_y;   //上下スクロール用

		bool map_Item;//マップ上のアイテム情報
		bool map_Item_2;//マップ上のアイテム情報2!
		bool map_Item_3;//マップ上のアイテム情報3!


		float Dot(float ax, float ay, float bx, float by);
		float Cross(float ax, float ay, float bx, float by);
		//線と線の交差判定
		bool LineCrossPoint(
			float a1x, float a1y, float a2x, float a2y,
			float b1x, float b1y, float b2x, float b2y,
			float* out_px, float* out_py
		);

		
};