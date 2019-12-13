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
  戻り値　float     :角度（０°〜360°）
  内容
  高さと幅から直角三角形があると仮定しその角度を求める*/
float GetAtan2Angle(float w, float h)
{
	//atan2で角度を求める
	float r = atan2(h, w)*180.0f / 3.14f;

	//-180°〜0°を180°〜360°に変換
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
	p[1] = Save::ExternalDataOpen(L"チーム開発マップ案1.csv", &size);
	p[0] = Save::ExternalDataOpen(L"マップ３.csv", &size);
	p[2] = Save::ExternalDataOpen(L"チーム開発マップ案2.csv", &size);
	
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

void RoomMapChanger(int r_map[ROOM_X][ROOM_Y], unique_ptr<wchar_t>* p,int r)
{

	int size;
	p[1] = Save::ExternalDataOpen(L"教室１右サクラ.csv", &size);
	p[2] = Save::ExternalDataOpen(L"教室２右サクラ.csv", &size);
	p[3] = Save::ExternalDataOpen(L"教室３右サクラ.csv", &size);
	p[4] = Save::ExternalDataOpen(L"教室４右サクラ.csv", &size);
	p[5] = Save::ExternalDataOpen(L"教室５右サクラ.csv", &size);
	p[6] = Save::ExternalDataOpen(L"教室６右サクラ.csv", &size);


	int map[ROOM_X][ROOM_Y];

	int count = 1;

	for (int i = 0; i < ROOM_X; i++)
	{
		for (int j = 0; j < ROOM_Y; j++)
		{
			int w = 0;
			swscanf_s(&p[r].get()[count], L"%d", &w);

			map[i][j] = w;
			count += 3;

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
	if (m == 0)
	{
		return 0.0f;
	}
	else if (m == 1)
	{
		return 64.0 * 30;
	}
	else if (m == 2)
	{
		return 64.0;
	}
	else if (m == 3)
	{
		return 64.0;
	}
	else if (m == 4)
	{
		return 64.0;
	}
	else if (m == 5)
	{
		return 64.0;
	}
	else if (m == 6)
	{
		return 64.0;
	}
	else if (m == 7)
	{
		return 64.0;
	}

}
//HitBoxChanger関数
/*
引数　１　　　int m　               :マップ切り替え管理用変数
引数　２　　　int map[MAP_X][MAP_Y  :マップ情報
戻り値　無し
マップ切り替え時にギミックのヒットボックスを変更する関数
*/

void HitBoxChanger(int m, int m_map[MAP_X][MAP_Y], bool room_in, int r, int r_map[ROOM_X][ROOM_Y])
{

	CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);
	if (room_in == false)
	{
		if (m == 0)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{
						m_map[MAP_X][MAP_Y] = 1;

						CObjGimmick* objg = new CObjGimmick(j*64.0f + main->GetScrollX(), i*64.0f + main->GetScrollY());
						Objs::InsertObj(objg, OBJ_GIMMICK, 11);

						CObjGimmick* gmk = (CObjGimmick*)Objs::GetObj(OBJ_GIMMICK);
						gmk->SetX(i);
						gmk->SetY(j);


					}
				}

			}
		}
		else if (m == 1)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{
						m_map[MAP_X][MAP_Y] = 1;

						CObjGimmick2* objg2 = new CObjGimmick2((j - 1 * 30)*64.0f + -(main->GetScrollX()), i*64.0f + main->GetScrollY());
						Objs::InsertObj(objg2, OBJ_GIMMICK2, 11);

						CObjGimmick2* gmk2 = (CObjGimmick2*)Objs::GetObj(OBJ_GIMMICK2);
						gmk2->SetX(i);
						gmk2->SetY(j);


					}
				}

			}
		}
		else if (m == 2)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{

						//敵オブジェクト作成
						CObjGimmick3* objg3 = new CObjGimmick3(j*64.0f + main->GetScrollX(), i*64.0f + main->GetScrollY());
						Objs::InsertObj(objg3, OBJ_GIMMICK3, 11);

						CObjGimmick3* gmk3 = (CObjGimmick3*)Objs::GetObj(OBJ_GIMMICK3);
						gmk3->SetX(i);
						gmk3->SetY(j);

						m_map[MAP_X][MAP_Y] = 1;
					}
				}

			}
		}
		else if (m == 3)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{

						//敵オブジェクト作成
						CObjGimmick4* objg4 = new CObjGimmick4(j*64.0f + main->GetScrollX(), i*64.0f + main->GetScrollY());
						Objs::InsertObj(objg4, OBJ_GIMMICK4, 11);

						CObjGimmick4* gmk4 = (CObjGimmick4*)Objs::GetObj(OBJ_GIMMICK4);
						gmk4->SetX(i);
						gmk4->SetY(j);

						m_map[MAP_X][MAP_Y] = 1;
					}
				}

			}
		}
		else if (m == 4)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{

						//敵オブジェクト作成
						CObjGimmick5* objg5 = new CObjGimmick5(j*64.0f + main->GetScrollX(), i*64.0f + main->GetScrollY());
						Objs::InsertObj(objg5, OBJ_GIMMICK5, 11);

						CObjGimmick5* gmk5 = (CObjGimmick5*)Objs::GetObj(OBJ_GIMMICK5);
						gmk5->SetX(i);
						gmk5->SetY(j);

						m_map[MAP_X][MAP_Y] = 1;
					}
				}

			}
		}
		else if (m == 5)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{

						//敵オブジェクト作成
						CObjGimmick2* objg2 = new CObjGimmick2(j*64.0f + main->GetScrollX(), i*64.0f + main->GetScrollY());
						Objs::InsertObj(objg2, OBJ_GIMMICK2, 11);

						CObjGimmick2* gmk2 = (CObjGimmick2*)Objs::GetObj(OBJ_GIMMICK2);
						gmk2->SetX(i);
						gmk2->SetY(j);

						m_map[MAP_X][MAP_Y] = 1;
					}
				}

			}
		}
		else if (m == 6)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{

						//敵オブジェクト作成
						CObjGimmick7* objg7 = new CObjGimmick7(j*64.0f + main->GetScrollX(), i*64.0f + main->GetScrollY());
						Objs::InsertObj(objg7, OBJ_GIMMICK7, 11);

						CObjGimmick7* gmk7 = (CObjGimmick7*)Objs::GetObj(OBJ_GIMMICK7);
						gmk7->SetX(i);
						gmk7->SetY(j);

						m_map[MAP_X][MAP_Y] = 1;
					}
				}

			}
		}
		else if (m == 7)
		{
			for (int i = 0; i < MAP_X; i++)
			{
				for (int j = 0; j < MAP_Y; j++)
				{
					if (m_map[i][j] == 7)
					{

						//敵オブジェクト作成
						CObjGimmick8* objg8 = new CObjGimmick8(j*64.0f + main->GetScrollX(), i*64.0f + main->GetScrollY());
						Objs::InsertObj(objg8, OBJ_GIMMICK8, 11);

						CObjGimmick8* gmk8 = (CObjGimmick8*)Objs::GetObj(OBJ_GIMMICK8);
						gmk8->SetX(i);
						gmk8->SetY(j);


					}
				}

			}
		}
	}
	else 
	{
	  if (r == 1||r == 0)
	  {
		  for (int i = 0; i < ROOM_X; i++)
		  {
			  for (int j = 0; j < ROOM_Y; j++)
			  {
				  if (r_map[i][j] == 7)
				  {

					  //敵オブジェクト作成
					  CObjRoomGimmick* objrg = new CObjRoomGimmick(j*64.0f + main->GetScrollX(), i*64.0f + main->GetScrollY());
					  Objs::InsertObj(objrg, OBJ_ROOM_GIMMICK, 11);

					  CObjRoomGimmick* rgmk = (CObjRoomGimmick*)Objs::GetObj(OBJ_ROOM_GIMMICK);
					  rgmk->SetX(i);
					  rgmk->SetY(j);


				  }
			  }
		  }
	  }
 }
}