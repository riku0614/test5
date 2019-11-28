#include "GameHead.h"
#include "UtilityModule.h"
#include "GameL/UserData.h"


//---UnitVec関数
/*引数１ float* vx  ; ベクトルのX成分のポインタ
　引数２ float* vy  ; ベクトルのY成分のポインタ
  戻り値　bool　　　; true=計算成功　false=計算失敗
  内容
  引数ベクトルを正規化しその値をvx,vyに変更します。*/
bool UnitVec(float* vx, float* vy)
{
	//ベクトルの長さを決める（三平方の定理）
	float r = 0.0f;
	r = (*vx)*(*vx) + (*vy)*(*vy);
	r = sqrt(r);//rをルートを求める


	//長さが０かどうか調べる
	if (r == 0.0f)
	{
		//０なら計算失敗
		return false;
	}
	else
	{
		//正規化を行う
		(*vx) = 1.0f / r * (*vx);
		(*vy) = 1.0f / r * (*vy);

	}

	return true;
}

//GetAtan2Angle関数
/*引数１　float w   :幅
　引数２　float h   :高さ
  戻り値　float     :角度（０°～360°）
  内容
  高さと幅から直角三角形があると仮定しその角度を求める*/
float GetAtan2Angle(float w, float h)
{
	//atan2で角度を求める
	float r = atan2(h, w)*180.0f / 3.14f;

	//-180°～0°を180°～360°に変換
	if (r < 0)
	{
		r = 360 - abs(r);
	}

	return r;
}
//MapChange関数
/*
引数１　int m     :map切り替え用変数
引数２　int m_map :切り替えるマップデータをぶち込むメインマップ変数
戻り値　無し
切り替え用のマップをメインマップ変数にぶち込む関数
*/
void MapChanger(int m ,int m_map[MAP_X][MAP_Y], unique_ptr<wchar_t>* p)
{
	
	int size;
	p[0] = Save::ExternalDataOpen(L"チーム開発マップ案1.csv", &size);
	p[1] = Save::ExternalDataOpen(L"チーム開発マップ案2.csv", &size);
	

	int map[MAP_X][MAP_Y];

	int count = 1;

	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
			int w = 0;
			swscanf_s(&p[m].get()[count], L"%d", &w);

			map[i][j] = w;
			count += 3;

		}
	}
	memcpy(m_map, map, sizeof(int)*(MAP_X * MAP_Y));
	
}
//RoomMapChange関数
/*
引数１　int m     :map切り替え用変数
引数２　int m_map :切り替えるマップデータをぶち込むメインマップ変数
戻り値　無し
切り替え用の教室マップをメイン教室マップ変数にぶち込む関数
*/

void RoomMapChanger(int r_map[ROOM_X][ROOM_Y], unique_ptr<wchar_t>* p)
{

	int size;
	p[0] = Save::ExternalDataOpen(L"教室1段.csv", &size);


	int map[ROOM_X][ROOM_Y];

	int count = 1;

	for (int i = 0; i < ROOM_X; i++)
	{
		for (int j = 0; j < ROOM_Y; j++)
		{
			int w = 0;
			swscanf_s(&p[0].get()[count], L"%d", &w);

			map[i][j] = w;
			count += 2;

		}
	}
	memcpy(r_map, map, sizeof(int)*(ROOM_X * ROOM_Y));

}
//SpawnChanger関数
/*
引数１　int m     :map切り替え用変数
戻り値　float
ステージごとの主人公の初期位置を返す変数
*/
float SpawnChanger(int m)
{
	if (m = 0)
	{
		return 0.0f;
	}
	else if (m = 1)
	{
		return 64.0 * 30;
	}
	else if (m = 2)
	{
		return 64.0;
	}
	else if (m = 3)
	{
		return 64.0;
	}
	else if (m = 4)
	{
		return 64.0;
	}
	else if (m = 5)
	{
		return 64.0;
	}
	else if (m = 6)
	{
		return 64.0;
	}
	else if (m = 7)
	{
		return 64.0;
	}

}
