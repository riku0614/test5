#pragma once


//�v���g�^�C�v�錾
bool UnitVec(float*vx, float*vy);

float GetAtan2Angle(float w, float h); //�����ƕ��Ŋp�����߂�

void MapChanger(int m,int m_map[MAP_X][MAP_Y], unique_ptr<wchar_t>* p);

float SpawnChanger(int m);

void RoomMapChanger(int r_map[ROOM_X][ROOM_Y], unique_ptr<wchar_t>* p);