#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;


//�}�N��
#define MAP_X  (75)
#define MAP_Y  (75)
#define ROOM_X (30)
#define ROOM_Y (30)
#define MAP_NUMBER (8)

//�I�u�W�F�N�g�F���C��
class CObjMain : public CObj
{
	public:
		CObjMain(int map[MAP_X][MAP_Y]);
		~CObjMain() {};
		void Init();	//�C�j�V�����C�Y
		void Action();	//�A�N�V����
		void Draw();	//�h���[
		void SetScrollX(float s) { m_scroll_x = s; }//X�����̃X�N���[��
		float GetScrollX() { return m_scroll_x; }
		void SetScrollY(float r) { m_scroll_y = r; }//Y�����ւ̃X�N���[��
		float GetScrollY() { return m_scroll_y; }
		void SetDelete(bool b) { delete_flg = b; }
		int MapData() { return m_map[MAP_X][MAP_Y]; }
		bool RoomFlag() { return room_in; }
		int RoomMapData() { return r_map[ROOM_X][ROOM_Y]; }
		int MapChangeData() { return map_chg; }

		int m_map[MAP_X][MAP_Y];//�}�b�v���u���b�N���iX���V�T�AY=�V�T�j
		int r_map[ROOM_X][ROOM_Y];//�}�b�v���u���b�N���iX��30�AY=30�j

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

		bool stop_flg;   //�}�b�v�؂�ւ�����x��������
		bool room_in;    //�����}�b�v�ւ̐؂�ւ��̃t���O
		bool back_stage; //�O�̃}�b�v�ɖ߂邽�߂̃t���O
		bool delete_flg;

		int map_chg;     //�}�b�v�؂�ւ����Ǘ����邽�߂̕ϐ�

		float spawn_point[MAP_NUMBER]; //map���̏����l���֐���������p�̕ϐ�
		int jx;
		int jy;
		
		unique_ptr<wchar_t> p[MAP_NUMBER]; //���[�U�[�f�[�^�̃��C���}�b�v�f�[�^��ۑ����邽�߂̕ϐ�
		unique_ptr<wchar_t> r[MAP_NUMBER]; //���[�U�[�f�[�^�̋����}�b�v�f�[�^��ۑ����邽�߂̕ϐ�


		float m_scroll_x;   //���E�X�N���[���p
		float m_scroll_y;   //�㉺�X�N���[���p


		float Dot(float ax, float ay, float bx, float by);
		float Cross(float ax, float ay, float bx, float by);
		//���Ɛ��̌�������
		bool LineCrossPoint(
			float a1x, float a1y, float a2x, float a2y,
			float b1x, float b1y, float b2x, float b2y,
			float* out_px, float* out_py
		);

};