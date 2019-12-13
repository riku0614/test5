#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//a

//�}�N��
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

//�I�u�W�F�N�g�F���C��
class CObjMain : public CObj
{
	public:
		CObjMain(int map[ROOM_X][ROOM_Y]);
		~CObjMain() {};
		void Init();	//�C�j�V�����C�Y
		void Action();	//�A�N�V����
		void Draw();	//�h���[
		void SetScrollX(float s) { m_scroll_x = s; }//X�����̃X�N���[��
		float GetScrollX() { return m_scroll_x; }
		void SetScrollY(float r) { m_scroll_y = r; }//Y�����ւ̃X�N���[��
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

		int m_map[MAP_X][MAP_Y];//�}�b�v���u���b�N���iX���V�T�AY=�V�T�j
		int r_map[ROOM_X][ROOM_Y];//�}�b�v���u���b�N���iX��30�AY=30�j

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
		//��l���ƕǂ̌�������
		bool HeroBlockCrossPoint(
			float x, float y, float vx, float vy,
			float *out_px, float *out_py, float *out_len
		);
	private:
		
		float save_x[MAP_NUMBER][2];//�}�b�v���s��������p�̎�l���̈ʒu��o�^����z��
		float save_y[MAP_NUMBER][2];
		float save_scroll_x[MAP_NUMBER][2];//�}�b�v���s��������p�̃X�N���[������o�^����z��
		float save_scroll_y[MAP_NUMBER][2];
		int save_map[MAP_X][MAP_Y];
		int save_room_map[ROOM_X][ROOM_Y][ROOM_NUMBER];

		bool stop_flg;//�}�b�v�؂�ւ�����x��������
		bool stop_flg2;
		bool first_stop;
		bool first_stop2;
		bool room_in;    //�����}�b�v�ւ̐؂�ւ��̃t���O
		bool delete_flg;
		bool plane_chg_hole;
		bool pepepe;
		bool pepepe_2;
		bool room_chg_stop;

		bool font_flg;

		int g_count1;
		int g_count2;
		int map_chg;     //�}�b�v�؂�ւ����Ǘ����邽�߂̕ϐ�
		int room_chg;
		int ix;
		int iy;
		int size;
		int m_time;

		float spawn_point[MAP_NUMBER]; //map���̏����l���֐���������p�̕ϐ�
		int jx;
		int jy;
		
		unique_ptr<wchar_t> p[MAP_NUMBER]; //���[�U�[�f�[�^�̃��C���}�b�v�f�[�^��ۑ����邽�߂̕ϐ�
		unique_ptr<wchar_t> r[MAP_NUMBER]; //���[�U�[�f�[�^�̋����}�b�v�f�[�^��ۑ����邽�߂̕ϐ�


		float m_scroll_x;   //���E�X�N���[���p
		float m_scroll_y;   //�㉺�X�N���[���p

		bool map_Item;//�}�b�v��̃A�C�e�����
		bool map_Item_2;//�}�b�v��̃A�C�e�����2!
		bool map_Item_3;//�}�b�v��̃A�C�e�����3!


		float Dot(float ax, float ay, float bx, float by);
		float Cross(float ax, float ay, float bx, float by);
		//���Ɛ��̌�������
		bool LineCrossPoint(
			float a1x, float a1y, float a2x, float a2y,
			float b1x, float b1y, float b2x, float b2y,
			float* out_px, float* out_py
		);

		
};