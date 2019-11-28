#include "GameHead.h"
#include "UtilityModule.h"
#include "GameL/UserData.h"


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
	p[0] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��1.csv", &size);
	p[1] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��2.csv", &size);
	

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

void RoomMapChanger(int r_map[ROOM_X][ROOM_Y], unique_ptr<wchar_t>* p)
{

	int size;
	p[0] = Save::ExternalDataOpen(L"����1�i.csv", &size);


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
//SpawnChanger�֐�
/*
�����P�@int m     :map�؂�ւ��p�ϐ�
�߂�l�@float
�X�e�[�W���Ƃ̎�l���̏����ʒu��Ԃ��ϐ�
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
