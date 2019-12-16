#include "GameHead.h"
#include "UtilityModule.h"
#include "GameL/UserData.h"
#include <stdio.h>
#include <stdlib.h>

//---UnitVec�֐�
/*�����P float* vx  ; �x�N�g����X�����̃|�C���^
�@�����Q float* vy  ; �x�N�g����Y�����̃|�C���^
  �߂�l�@bool�@�@�@; true=�v�Z�����@false=�v�Z���s
  ���e
  �����x�N�g���𐳋K�������̒l��vx,vy�ɕύX���܂��B*/
bool UnitVec(float* vx, float* vy)
{
	//�x�N�g���̒��������߂�i�O�����̒藝�j
	float r = 0.0f;
	r = (*vx)*(*vx) + (*vy)*(*vy);
	r = sqrt(r);//r�����[�g�����߂�


	//�������O���ǂ������ׂ�
	if (r == 0.0f)
	{
		//�O�Ȃ�v�Z���s
		return false;
	}
	else
	{
		//���K�����s��
		(*vx) = 1.0f / r * (*vx);
		(*vy) = 1.0f / r * (*vy);

	}

	return true;
}
//GetAtan2Angle�֐�
/*�����P�@float w   :��
�@�����Q�@float h   :����
  �߂�l�@float     :�p�x�i�O���`360���j
  ���e
  �����ƕ����璼�p�O�p�`������Ɖ��肵���̊p�x�����߂�*/
float GetAtan2Angle(float w, float h)
{
	//atan2�Ŋp�x�����߂�
	float r = atan2(h, w)*180.0f / 3.14f;

	//-180���`0����180���`360���ɕϊ�
	if (r < 0)
	{
		r = 360 - abs(r);
	}

	return r;
}


//MapChange�֐�
/*
�����P�@int m     :map�؂�ւ��p�ϐ�
�����Q�@int m_map :�؂�ւ���}�b�v�f�[�^���Ԃ����ރ��C���}�b�v�ϐ�
�߂�l�@����
�؂�ւ��p�̃}�b�v�����C���}�b�v�ϐ��ɂԂ����ފ֐�
*/
void MapChanger(int m ,int m_map[MAP_X][MAP_Y], unique_ptr<wchar_t>* p)
{
	
	int size;

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
//RoomMapChange�֐�
/*
�����P�@int m     :map�؂�ւ��p�ϐ�
�����Q�@int m_map :�؂�ւ���}�b�v�f�[�^���Ԃ����ރ��C���}�b�v�ϐ�
�߂�l�@����
�؂�ւ��p�̋����}�b�v�����C�������}�b�v�ϐ��ɂԂ����ފ֐�
*/

void RoomMapChanger(int r_map[ROOM_X][ROOM_Y], unique_ptr<wchar_t>* p,int r)
{

	int size;


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
//SpawnChanger�֐�
/*
�����P�@int m     :map�؂�ւ��p�ϐ�
�߂�l�@float
�X�e�[�W���Ƃ̎�l���̏����ʒu��Ԃ��ϐ�
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
//HitBoxChanger�֐�
/*
�����@�P�@�@�@int m�@               :�}�b�v�؂�ւ��Ǘ��p�ϐ�
�����@�Q�@�@�@int map[MAP_X][MAP_Y  :�}�b�v���
�߂�l�@����
�}�b�v�؂�ւ����ɃM�~�b�N�̃q�b�g�{�b�N�X��ύX����֐�
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

						//gimmick�I�u�W�F�N�g�쐬
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

						//gimmick�I�u�W�F�N�g�쐬
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

						//gimmick�I�u�W�F�N�g�쐬
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

						//gimmick�I�u�W�F�N�g�쐬
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

						//gimmick�I�u�W�F�N�g�쐬
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

						//gimmick�I�u�W�F�N�g�쐬
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

						//gimmick�I�u�W�F�N�g�쐬
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

						//gimmick�I�u�W�F�N�g�쐬
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
		if (r == 1 || r == 0)
		{
			for (int i = 0; i < ROOM_X; i++)
			{
				for (int j = 0; j < ROOM_Y; j++)
				{
					if (r_map[i][j] == 7)
					{

					  //gimmick�I�u�W�F�N�g�쐬
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