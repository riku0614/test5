#pragma once
//使用するヘッダー
#include "GameL/SceneObjManager.h"


//使用するネームスペース
using namespace GameL;


//マクロ
#define MAP_X  (75)
#define MAP_Y  (75)
#define ROOM_X (30)
#define ROOM_Y (30)
#define MAP_NUMBER (8)

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
		void SetDelete(bool b) { delete_flg = b; }
		int MapData() { return m_map[MAP_X][MAP_Y]; }
		bool RoomFlag() { return room_in; }
		int RoomMapData() { return r_map[ROOM_X][ROOM_Y]; }
		int MapChangeData() { return map_chg; }

		int m_map[MAP_X][MAP_Y];//マップ情報ブロック数（X＝７５個、Y=７５個）
		int r_map[ROOM_X][ROOM_Y];//マップ情報ブロック数（X＝30個、Y=30個）

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
		
		float save_x[MAP_NUMBER][2];//マップを行き来する用の主人公の位置を登録する配列
		float save_y[MAP_NUMBER][2];
		float save_scroll_x[MAP_NUMBER][2];//マップを行き来する用のスクロール情報を登録する配列
		float save_scroll_y[MAP_NUMBER][2];

		bool stop_flg;   //マップ切り替えを一度だけしか
		bool room_in;    //教室マップへの切り替えのフラグ
		bool back_stage; //前のマップに戻るためのフラグ
		bool delete_flg;

		int map_chg;     //マップ切り替えを管理するための変数

		float spawn_point[MAP_NUMBER]; //map毎の初期値を関数から入れる用の変数
		int jx;
		int jy;
		
		unique_ptr<wchar_t> p[MAP_NUMBER]; //ユーザーデータのメインマップデータを保存するための変数
		unique_ptr<wchar_t> r[MAP_NUMBER]; //ユーザーデータの教室マップデータを保存するための変数


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