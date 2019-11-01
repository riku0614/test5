#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

#define MAP_MIN   (0)
#define MAP_ERROR (-1)
#define MAP_DRAW_SIZE (64.0f)

#define RESOURCE_TOP  (111.0f)
#define RESOURCE_LEFT (256.0f)

#define BUFFER_MAX         (8)
#define BUFFER_DELETE_DATA (999)
#define BUFFER_NO_DATA     (-1)

#define SEARCH_MAX         (4)
#define SEARCH_MAP_NEXT        (1)

#define KM_MAP_MAX         (9)
#define CONNECTION_DELETE  (1)

#define LINE_LOOP          (1)
#define LINE_STEP_UP       (1)
#define LINE_STEP_X_PLUS   (0)
#define LINE_STEP_Y_PULS   (0)

//オブジェクト：主人公
class CObjEnemy : public CObj
{
public:
	CObjEnemy(int map[100][100]);
	~CObjEnemy() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー
	float GetVY() { return m_vy; }
	float GetVX() { return m_vx; }
	int m_map[100][100];
	int GetMap(int x, int y); //map情報の取得
	void SetMap(int x, int y, int id);//マップにblockのID情報を入れる
private:
	float m_px;  //オブジェクトの位置X
	float m_py;  //オブジェクトの位置Y
	float m_vx; //オブジェクトの移動用ベクトルX
	float m_vy; //オブジェクトの移動用ベクトルY
	float m_posture; //姿勢

	//探索バッファ用構造体
	struct XY
	{
		int x;
		int y;
	};

	bool OverFlowCheck(int x, int y); //オーバーフローチェック
	int BufferCheck(XY b[]);          //バッファチェック

	//4方向サーチ＆登録
	void EveryDirectionSearchSet
	(int set_x, int set_y,
		int c_map[100][100], int km_map[100][100],
		XY buffer[], int* buffer_count);

	//ダイクストラ法
	int Dijkstras(int c_map[100][100], int km_map[100][100],
		int goal_x, int goal_y);

	bool m_flg;//追従移動の管理用フラグ

		//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
};