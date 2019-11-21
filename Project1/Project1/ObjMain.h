#pragma once
//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;


//�}�N��
#define MAP_X  (75)
#define MAP_Y  (75)
#define ROOM_X (25)
#define ROOM_Y (25)


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
		
		
		int m_map[MAP_X][MAP_Y];//�}�b�v���u���b�N���iX=�P�Q�AY=�P�O�j
		int r_map[ROOM_X][ROOM_Y];

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
		
		bool stop_flg;
		bool room_in;

		int map_chg;

		float spawn_point[7];
		int jx;
		int jy;
		
		unique_ptr<wchar_t> p[7];
		unique_ptr<wchar_t> r[7];

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