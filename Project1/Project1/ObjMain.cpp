//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"
#include "GameL/HitBoxManager.h"
#include "GameL/UserData.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "ObjMain.h"
#include "UtilityModule.h"



//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjMain::CObjMain(int map[MAP_X][MAP_Y])
{
	memcpy(m_map, map, sizeof(int)*(MAP_X * MAP_Y));
}





//�C�j�V�����C�Y
void CObjMain::Init()
{
	m_scroll_x = 64.0f;
	m_scroll_y = 64.0f;

	map_chg = 0;
	room_chg = 0;
	stop_flg = false;
	spawn_point[7] = NULL;
	room_in = false;
	back_stage = false;
	stop_flg2 = true;
	delete_flg = false;
	stop_flg3=true;
	plane_chg_hole = false;
}

//�A�N�V����
void CObjMain::Action()
{

	if (map_chg == 0 )
	{
		if (room_in == true && stop_flg == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(4, L"4������SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(4);

			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			hero->SetX(20.0f*64.0f);
			hero->SetY(4.0f*64.0f);
			m_scroll_x = -15.0f*64.0f;
			m_scroll_y = -5.0f*64.0f;

			RoomMapChanger(r_map, r,room_chg);

			stop_flg = false;
		}
		else if (back_stage==true&&stop_flg == true)
		{	
			//���y���̓ǂݍ���
			Audio::LoadAudio(5, L"5�}�b�v�؂�ւ�SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(5);

            CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

			hero->SetX(save_x[map_chg][1] );
			hero->SetY(save_y[map_chg][1] );
			main->SetScrollX(save_scroll_x[map_chg][1]);
			main->SetScrollY(save_scroll_y[map_chg][1]);

			MapChanger(map_chg, m_map, p);

			stop_flg = false;

		}

		
	}
	else if (map_chg > 0 && stop_flg == true&&back_stage==false)
	{
		//���y���̓ǂݍ���
		Audio::LoadAudio(5, L"5�}�b�v�؂�ւ�SE.wav", SOUND_TYPE::EFFECT);

		//���y�X�^�[�g
		Audio::Start(5);

		spawn_point[map_chg] = SpawnChanger(map_chg);

		CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
		hero->SetX(spawn_point[map_chg]);
		hero->SetY(0.0f);
		m_scroll_x = spawn_point[map_chg]*-1.0f;
		m_scroll_y = 0.0f;

		MapChanger(map_chg,m_map,p);
		
		stop_flg = false;
	}
	
	back_stage = false;
	//��l���̈ʒu���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();



	//����X�N���[�����C��
	if (hx < 75)
	{
		hero->SetX(75);
		m_scroll_x -= hero->GetVX();
	}

	//�O���X�N���[�����C��
	if (hx > 400)
	{
		hero->SetX(400);
		m_scroll_x -= hero->GetVX();
	}
	//����X�N���[�����C��
	if (hy < 75)
	{
		hero->SetY(75);
		m_scroll_y -= hero->GetVY();
	}

	//�����X�N���[�����C��
	if (hy > 400)
	{
		hero->SetY(400);
		m_scroll_y -= hero->GetVY();


	}


   if (stop_flg2 == true&&room_in==false)
	{
	  

		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 7)
				{

					//�M�~�b�N�I�u�W�F�N�g�쐬
					CObjGimmick* objg = new CObjGimmick((j - 1)*64.0f + m_scroll_x, (i-1)*64.0f + m_scroll_y);
					Objs::InsertObj(objg, OBJ_GIMMICK, 14);

					CObjGimmick* gim = (CObjGimmick*)Objs::GetObj(OBJ_GIMMICK);
					gim->SetY(j);
					gim->SetX(i);

				}
			}

		}
		stop_flg2 = false;
	}
  
   if (stop_flg3 == true)
   {
	   for (int i = 0; i < MAP_X; i++)
	   {
		   for (int j = 0; j < MAP_Y; j++)
		   {
			   if (m_map[i][j] == 5)
			   {

				   //�A�C�e���I�u�W�F�N�g�쐬
				   CObjEnemy* obje = new CObjEnemy((j - 1)*64.0f + m_scroll_x, (i - 1)*64.0f + m_scroll_y);
				   Objs::InsertObj(obje, OBJ_ENEMY, 11);


				   m_map[i][j] = 1;

			   }
		   }

	   }
   }
	
}

/*���ϊ֐�
�@����1,2 float   ax  ,  ay  :A�x�N�g��
  ����3,4 float   bx  ,  by  :B�x�N�g��
  �߂�l�@float   �F�ˉe
  ���e�@A�x�N�g����B�x�N�g���ē��ς��s���ˉe�����߂�*/
float CObjMain::Dot(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * bx + ay * by;

	return t;
}

/*�O�ϊ֐�
�@����1,2 float   ax  ,  ay  :A�x�N�g��
  ����3,4 float   bx  ,  by  :B�x�N�g��
  �߂�l�@float   �F�ˉe
  ���e�@A�x�N�g����B�x�N�g���ē��ς��s���ˉe�����߂�*/
float CObjMain::Cross(float ax, float ay, float bx, float by)
{
	float t = 0.0f;

	t = ax * by - ay * bx;

	return t;
}

//���������߂�}�N��
#define SGN(x) 1-(x<=0)-(x<0)

/*���Ɛ��̌�������֐�
  �����@float 1, 2  a1_x,a1y            :���x�N�g��A�̎n�_
  �����@float 3, 4  a2x,a2y             :���x�N�g��A�̏I�_
  �����@float 5, 6  b1x,b1y             :���x�N�g��A�̎n�_
  �����@float 7, 8  b2x,b2y             :���x�N�g��A�̎n�_
  �����@float 9, 10  out_px,out_py      :���x�N�g��A�̎n�_
  �߂�l�@bool  :true=��_�L��@false=��_����
  ���e�F������A�EB�x�N�g���̌�_�������Aout_px��out_py�̕Ԃ�*/
bool CObjMain::LineCrossPoint(
	float a1x, float a1y, float a2x, float a2y,
	float b1x, float b1y, float b2x, float b2y,
	float* out_px, float* out_py
)
{
	//�G���[�R�[�h
	*out_px = -99999.0f; *out_py = -99999.0f;

	//A�x�N�g���쐬(a2��a1)
	float ax = a2x - a1x;  float ay = a2y - a1y;

	//B�x�N�g���쐬(b2��b1)
	float bx = b2x - b1x;  float by = b2y - b1y;

	//C�x�N�g���쐬(b1��a1)
	float cx = b1x - a1x;  float cy = b1y - a1y;

	//D�x�N�g���쐬(b2��a1)
	float dx = b2x - a1x;  float dy = b2y - a1y;
	//A X C�̎ˉe��A X B�̎ˉe�����߂�
	float t1 = Cross(ax, ay, cx, cy);
	float t2 = Cross(ax, ay, dx, dy);
	//���������������ɂȂ��Ă��邩�ǂ����`�F�b�N
	if (SGN(t1) == SGN(t2))
		return false;
	//�ˉe�̐�Βl��
	t1 = abs(t1);  t2 = abs(t2);

	//��_�����߂�
	float px = bx * (t1 / (t1 + t2)) + b1x;
	float py = by * (t1 / (t1 + t2)) + b1y;

	//AP�x�N�g���i����a1�j
	float apx = px - a1x;  float apy = py - a1y;

	//BP�x�N�g���ip��a2)
	float bpx = px - a2x;  float bpy = py - a2y;

	//A�EAP�̎ˉe��A�EBP�̎ˉe�����߂�
	float w1 = Dot(ax, ay, apx, apy);
	float w2 = Dot(ax, ay, bpx, bpy);

	//�����`�F�b�N
	if (SGN(w1) == SGN(w2))
		return false; //��_���O

	//��_��Ԃ�
	*out_px = px; *out_py = py;

	return true;

}

/*��l���ƕǂ̌�������֐�
�@����1,2 float  x,y          :��l���̈ʒu
  ����3,4 float  vx,vy        :��l���̈ړ��x�N�g��
  ����5,6 float* out_px,out_y :Block�Ƃ̌�_
  ����7   float* out          :�ꂩ���_�܂ł̋���
  ��l���̈ʒu�{�ړ��x�N�g���Ɗe�u���b�N�̕ςōD�]�̔�����s��
  �ł��߂���_�̈ʒu�Ƌ�����Ԃ�*/
bool CObjMain::HeroBlockCrossPoint(
	float x, float y, float vx, float vy,
	float *out_px, float *out_py, float *out_len
)

{
	
	bool pb = false;      //��_�m�F�p
	float len = 99999.0f; //��_�Ƃ̋���
	//�u���b�N�̕Ӄx�N�g��
	float edge[4][4] =
	{
		{ 0, 0,64, 0},
		{64, 0,64,64},
		{64,64, 0,64},
		{ 0,64, 0, 0},
	};

	//m_map�̑S�v�f�ɃA�N�Z�X
	if (room_in == false)
	{


		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] > 0 && m_map[i][j] != 5)
				{
					//�u���b�N�̂S�ӂ����_��T��
					for (int k = 0; k < 4; k++)
					{
						//��_��T��
						float px, py;
						bool b;
						float l = 0.0f;
						b = LineCrossPoint
						(x, y, x + vx, y + vy,
							j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],
							&px, &py);

						//��_�`�F�b�N
						if (b == true)
						{
							//��_�Ƃ̋��������߂�
							l = sqrt((px - x)*(px - x) + (py - y)*(py - y));

							//��������_�̒��ōł��������Z�����̂�T��
							if (len > l)
							{
								len = l;
								*out_px = px;
								*out_py = py;
								pb = true;
							}
						}

					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] > 0)
				{
					//�u���b�N�̂S�ӂ����_��T��
					for (int k = 0; k < 4; k++)
					{
						//��_��T��
						float px, py;
						bool b;
						float l = 0.0f;
						b = LineCrossPoint
						(x, y, x + vx, y + vy,
							j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],
							&px, &py);

						//��_�`�F�b�N
						if (b == true)
						{
							//��_�Ƃ̋��������߂�
							l = sqrt((px - x)*(px - x) + (py - y)*(py - y));

							//��������_�̒��ōł��������Z�����̂�T��
							if (len > l)
							{
								len = l;
								*out_px = px;
								*out_py = py;
								pb = true;
							}
						}

					}
				}
			}
		}
	}
	*out_len = len;
	return pb;


}
/*BlockHit�֐�
  �����P�@�@float* x             :������s��object��X�ʒu
  �����Q�@�@float* y             :������s��object��Y�ʒu
  �����R�@�@bool  scroll_on_x    :������s��object�̓X�N���[���ɉe����^���邩�ǂ����itrue=�^����@false=�^���Ȃ��j
  �����T�@�@bool* up             :�㉺���E����̏㕔���ɂ������Ă��邩�ǂ�����Ԃ�
  �����U�@�@bool* down           :�㉺���E����̉������ɂ������Ă��邩�ǂ�����Ԃ�
  �����V�@�@bool* left           :�㉺���E����̍������ɂ������Ă��邩�ǂ�����Ԃ�
  �����W�@�@bool* right          :�㉺���E����̉E�����ɂ������Ă��邩�ǂ�����Ԃ�
  �����X�@�@float* vx            :���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
  �����P�O�@�@float* vy            :�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l��ς��ĕԂ�
  �����P�P�@int* bt            �@:���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
  ������s��object�ƃu���b�N64*64����ŁA�����蔻��Ə㉺���E������s��
  ���̌��ʂ͈����S�`�P�O�ɕԂ�*/

void CObjMain::BlockHit(
	float *x, float *y, bool scroll_on_x, bool scroll_on_y,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, int *bt, int *c_id, int *k_id
)
{
	
	//��l���̏Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���u���b�N�̎�ނ̏�����
	*bt = 0;

	CObjItem* item = (CObjItem*)Objs::GetObj(OBJ_ITEM);
	CObjGimmick* gmk = (CObjGimmick*)Objs::GetObj(OBJ_GIMMICK);
	//m=map�̑S�v�f�ɃA�N�Z�X
	if (room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{


				if (m_map[i][j] <= 99 && m_map[i][j] > 4&&m_map[i][j]!=7  || m_map[i][j]==3)
				{
					//�v�f�ԍ������W�ɕύX
					float bx = j * 64.0f;
					float by = i * 64.0f;

					//�X�N���[���̉e��
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//��l���ƃu���b�N�̓����蔻��
					if ((*x + (-scroll_x) + 64.0f > bx) && (*x + (-scroll_x) < bx + 64.0f) && (*y + (-scroll_y) + 64.0f > by) && (*y + (-scroll_y) < by + 64.0f))
					{
						//�㉺���E����

						//vector�̍쐬
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//���������߂�
						float len = sqrt(rvx*rvx + rvy * rvy);


						//�p�x�����߂�
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//len��������̒����̂��Z���ꍇ����ɓ���
						if (len < 88.0f)
						{
							//�p�x�ō��E�𔻒�
							if ((r < 45 && r >= 0) || r > 315)
							{
								//�E
								*right = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*x = bx + 64.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�]
								if (m_map[i][j] == 13)
								{
									plane_chg_hole = true;
								}
							
								if (m_map[i][j] == 3 && *c_id == CHAR_HERO && *k_id == ITEM_KEY)
								{
									stop_flg = true;
									map_chg++;

									

									if (map_chg == 1)
									{
										Scene::SetScene(new CSceneGameClear);
									}

									//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									save_x[map_chg][1] = hero->GetX();
									save_y[map_chg][1] = hero->GetY();
									save_scroll_x[map_chg][1] = main->GetScrollX();
									save_scroll_y[map_chg][1] = main->GetScrollY();
									map_chg++;
								}
								else if (m_map[i][j] == 5)
								{
									stop_flg = true;
									back_stage = true;
								   

								
									map_chg--;
								}
								else if (m_map[i][j] == 6 && *c_id == CHAR_HERO)
								{
									if (room_in == false)
									{
										room_in = true;
										stop_flg = true;
										
										room_chg++;
								
										//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);



										save_x[map_chg][0] = hero->GetX();
										save_y[map_chg][0] = hero->GetY();
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();
									}

								}
								*vx = -(*vx)*0.1f;//-VX*�����W��
							}
							if (r > 45 && r < 135)
							{
								//��
								*down = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*y = by - 64.0f + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
								if (m_map[i][j] == 2)
									*bt = m_map[i][j];
								if (m_map[i][j] == 3 && *c_id == CHAR_HERO && *k_id == ITEM_KEY)
								{
									if (map_chg == 1)
									{
										Scene::SetScene(new CSceneGameClear);
									}

									stop_flg = true;
									
								
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
									save_x[map_chg][1] = hero->GetX();
									save_y[map_chg][1] = hero->GetY();
									save_scroll_x[map_chg][1] = main->GetScrollX();
									save_scroll_y[map_chg][1] = main->GetScrollY();
									map_chg++;
								}
								else if (m_map[i][j] == 5)
								{
									
									stop_flg = true;
									back_stage = true;
									map_chg--;
									
								}
								else if (m_map[i][j] == 6 && *c_id == CHAR_HERO)
								{
									if (room_in == false)
									{
										room_in = true;
										room_chg++;

										
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
										save_x[map_chg][0] = hero->GetX();
										save_y[map_chg][0] = hero->GetY();
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();
									}

								}
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//��
								*left = true;//��l�����猩�āA�E�̕������Փ˂��Ă���
								*x = bx - 64.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								if (m_map[i][j] == 3 && *c_id == CHAR_HERO && *k_id == ITEM_KEY)
								{
									stop_flg = true;
									
									
									

									if (map_chg == 1)
									{
										Scene::SetScene(new CSceneGameClear);
									}

									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
									save_x[map_chg][1] = hero->GetX();
									save_y[map_chg][1] = hero->GetY();
									save_scroll_x[map_chg][1] = main->GetScrollX();
									save_scroll_y[map_chg][1] = main->GetScrollY();

									map_chg++;
								}
								else if (m_map[i][j] == 5)
								{
									stop_flg = true;
									back_stage = true;
									

									
									map_chg--;
								}
								else if (m_map[i][j] == 6 && *c_id == CHAR_HERO)
								{
									if (room_in == false)
									{
										room_in = true;
										stop_flg = true;

										//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										save_x[map_chg][0] = hero->GetX();
										save_y[map_chg][0] = hero->GetY();
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();
									}

								}
								*vx = -(*vx)*0.1f;//-VX*�����W��
							}
							if (r > 225 && r < 315)
							{
								//��
								*up = true;//��l�����猩�āA��̕������Փ˂��Ă���
								*y = by + 64.0f + (scroll_y);//�u���b�N�̈ʒu-��l����
								if (m_map[i][j] == 3 && *c_id == CHAR_HERO && *k_id == ITEM_KEY)
								{
									stop_flg = true;
									stop_flg2 = true;
									
									if (map_chg == 1)
									{
										Scene::SetScene(new CSceneGameClear);
									}

									//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									save_x[map_chg][1] = hero->GetX();
									save_y[map_chg][1] = hero->GetY();
									save_scroll_x[map_chg][1] = main->GetScrollX();
									save_scroll_y[map_chg][1] = main->GetScrollY();
									map_chg++;
								}
								else if (m_map[i][j] == 5)
								{

									stop_flg = true;
									back_stage = true;




									map_chg--;
								}
								else if (m_map[i][j] == 6 && *c_id == CHAR_HERO)
								{
									if (room_in == false)
									{

										room_in = true;
										stop_flg = true;
										room_chg++;

										//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										save_x[map_chg][0] = hero->GetX();
										save_y[map_chg][0] = hero->GetY();
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();
									}

								}
								if (*vy < 0)
								{
									*vy = 0.0f;
								}
							
			
							

							}
						}


					}

				}
			}
		}
	}
	else
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{


				if (r_map[i][j] <= 99 && r_map[i][j] >4 && r_map[i][j] != 7 ||r_map[i][j]==3)
				{
					//�v�f�ԍ������W�ɕύX
					float bx = j * 64.0f;
					float by = i * 64.0f;

					//�X�N���[���̉e��
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//��l���ƃu���b�N�̓����蔻��
					if ((*x + (-scroll_x) + 64.0f > bx) && (*x + (-scroll_x) < bx + 64.0f) && (*y + (-scroll_y) + 64.0f > by) && (*y + (-scroll_y) < by + 64.0f))
					{
						//�㉺���E����

						//vector�̍쐬
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//���������߂�
						float len = sqrt(rvx*rvx + rvy * rvy);


						//�p�x�����߂�
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//len��������̒����̂��Z���ꍇ����ɓ���
						if (len < 88.0f)
						{
							//�p�x�ō��E�𔻒�
							if ((r < 45 && r >= 0) || r > 315)
							{
								//�E
								*right = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*x = bx + 64.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�]
								if (r_map[i][j] == 6 && *c_id == CHAR_HERO)
								{
									if (room_in == true)
									{
										room_in = false;
										stop_flg = true;

										//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										hero->SetX(save_x[map_chg][0] + hero->GetVX());
										hero->SetY(save_y[map_chg][0] + hero->GetVY());
										main->SetScrollX(save_scroll_x[map_chg][0]);
										main->SetScrollY(save_scroll_y[map_chg][0]);
									}

								}
								*vx = -(*vx)*0.1f;//-VX*�����W��
							}
							if (r > 45 && r < 135)
							{
								//��
								*down = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*y = by - 64.0f + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
								if (r_map[i][j] == 2)
									*bt = m_map[i][j];
							
								if (r_map[i][j] == 6 && *c_id == CHAR_HERO)
								{
									if (room_in == true)
									{
										room_in = false;
										stop_flg = true;

										//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										hero->SetX(save_x[map_chg][0] + hero->GetVX());
										hero->SetY(save_y[map_chg][0] + hero->GetVY());
										main->SetScrollX(save_scroll_x[map_chg][0]);
										main->SetScrollY(save_scroll_y[map_chg][0]);
									}

								}
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//��
								*left = true;//��l�����猩�āA�E�̕������Փ˂��Ă���
								*x = bx - 64.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								if (r_map[i][j] == 6 && *c_id == CHAR_HERO)
								{
									if (room_in == true)
									{
										room_in = false;
										stop_flg = true;
										stop_flg2 = true;

										//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										hero->SetX(save_x[map_chg][0] + hero->GetVX());
										hero->SetY(save_y[map_chg][0] + hero->GetVY());
										main->SetScrollX(save_scroll_x[map_chg][0]);
										main->SetScrollY(save_scroll_y[map_chg][0]);
									}

								}
								*vx = -(*vx)*0.1f;//-VX*�����W��
							}
							if (r > 225 && r < 315)
							{
								//��
								*up = true;//��l�����猩�āA��̕������Փ˂��Ă���
								*y = by + 64.0f + (scroll_y);//�u���b�N�̈ʒu-��l����
								if (r_map[i][j] == 6 && *c_id == CHAR_HERO)
								{
									if (room_in == true)
									{
										room_in = false;
										stop_flg = true;

										//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										hero->SetX(save_x[map_chg][0] + hero->GetVX());
										hero->SetY(save_y[map_chg][0] + hero->GetVY());
										main->SetScrollX(save_scroll_x[map_chg][0]);
										main->SetScrollY(save_scroll_y[map_chg][0]);
									}

								}
								if (*vy < 0)
								{
									*vy = 0.0f;
								}


							}
						}


					}

				}
			}
		}
	}
}

/*ItemHit�֐�
  �����P�@�@float* x             :������s��object��X�ʒu
  �����Q�@�@float* y             :������s��object��Y�ʒu
  �����R�@�@bool  scroll_on_x    :������s��object�̓X�N���[���ɉe����^���邩�ǂ����itrue=�^����@false=�^���Ȃ��j
  �����T�@�@bool* up             :�㉺���E����̏㕔���ɂ������Ă��邩�ǂ�����Ԃ�
  �����U�@�@bool* down           :�㉺���E����̉������ɂ������Ă��邩�ǂ�����Ԃ�
  �����V�@�@bool* left           :�㉺���E����̍������ɂ������Ă��邩�ǂ�����Ԃ�
  �����W�@�@bool* right          :�㉺���E����̉E�����ɂ������Ă��邩�ǂ�����Ԃ�
  �����X�@�@float* vx            :���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
  �����P�O�@�@float* vy            :�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l��ς��ĕԂ�
  �����P�P�@int* bt            �@:���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
  ������s��object�ƃu���b�N64*64����ŁA�����蔻��Ə㉺���E������s��
  ���̌��ʂ͈����S�`�P�O�ɕԂ�*/

void CObjMain::ItemHit(
	float *x, float *y, bool scroll_on_x, bool scroll_on_y,
	bool *up, bool *down, bool *left, bool *right,
	float *vx, float *vy, int *bt
)
{
	//��l���̏Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	

	//����ł���u���b�N�̎�ނ̏�����
	*bt = 0;
	
	//m=map�̑S�v�f�ɃA�N�Z�X
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 4)
				{
					

					
					//�v�f�ԍ������W�ɕύX
					float bx = j * 64.0f;
					float by = i * 64.0f;

					//�X�N���[���̉e��
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//��l���ƃu���b�N�̓����蔻��
					if ((*x + (-scroll_x) + 64.0f > bx) && (*x + (-scroll_x) < bx + 32.0f) && (*y + (-scroll_y) + 64.0f > by) && (*y + (-scroll_y) < by + 32.0f))
					{
						//�㉺���E����

						//vector�̍쐬
						float rvx = (*x + (-scroll_x)) - bx;
						float rvy = (*y + (-scroll_y)) - by;

						//���������߂�
						float len = sqrt(rvx*rvx + rvy * rvy);


						//�p�x�����߂�
						float r = atan2(rvy, rvx);
						r = r * 180.0f / 3.14f;

						if (r <= 0.0f)
							r = abs(r);
						else
							r = 360.0f - abs(r);

						//len��������̒����̂��Z���ꍇ����ɓ���
						if (len < 88.0f)
						{
							//�p�x�ō��E�𔻒�
							if ((r < 45 && r>0) || r > 315)
							{
								//�E
								*right = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*x = bx + 32.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								if (delete_flg == true)
								{
									m_map[i][j] = 1;
									delete_flg = false;
								}
								*vx = -(*vx)*0.25f;//-VX*�����W��
							}
							if (r > 45 && r < 135)
							{
								//��
								*down = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*y = by - 64.0f + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
								if (delete_flg == true)
								{
									m_map[i][j] = 1;
									delete_flg = false;
								}
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//��
								*left = true;//��l�����猩�āA�E�̕������Փ˂��Ă���
								*x = bx - 64.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								if (delete_flg == true)
								{
									m_map[i][j] = 1;
									delete_flg = false;
								}
								*vx = -(*vx)*0.1f;//-VX*�����W��
							}
							if (r > 225 && r < 315)
							{
								//��
								*up = true;//��l�����猩�āA��̕������Փ˂��Ă���
								*y = by + 32.0f + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
								if (delete_flg == true)
								{
									m_map[i][j] = 1;
									delete_flg = false;
								}
								if (*vy < 0)
								{
									*vy = 0.0f;
								}
								

							}
							
							
						}


					}


				}

			}

		}
	
}


	


//�h���[
void CObjMain::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu


	if(room_in==false)
	{ 
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] > 0)
				{


					//�\���ʒu�̐ݒ�
					dst.m_top = i * 64.0f + m_scroll_y;
					dst.m_left = j * 64.0f + m_scroll_x;
					dst.m_right = dst.m_left + 64.0;
					dst.m_bottom = dst.m_top + 64.0;


					//���e�N�X�`��
					if (m_map[i][j] == 1||m_map[i][j]==4 ||m_map[i][j]==7||m_map[i][j]==13)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(1, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 13 && plane_chg_hole == false)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(1, &src, &dst, c, 0.0f);
					}
					else if (m_map[i][j] == 13 && plane_chg_hole == true)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(21, &src, &dst, c, 0.0f);
					}
					//�K�i�e�N�X�`��
					if (m_map[i][j] == 3/*||m_map[i][j]==5*/)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(7, &src, &dst, c, 0.0f);
					}
					//�ǃe�N�X�`��
					if (m_map[i][j] == 9)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(3, &src, &dst, c, 0.0f);
					}
					if(m_map[i][j]==10)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(18, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 11)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(19, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 12)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(20, &src, &dst, c, 0.0f);
					}
					//���e�N�X�`��
					if (m_map[i][j] == 6)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(10, &src, &dst, c, 0.0f);
					}
				}
			}

		}
	}
	else 
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] > 0)
				{


					//�\���ʒu�̐ݒ�
					dst.m_top = i * 64.0f + m_scroll_y;
					dst.m_left = j * 64.0f + m_scroll_x;
					dst.m_right = dst.m_left + 64.0;
					dst.m_bottom = dst.m_top + 64.0;


					//���e�N�X�`��
					if (r_map[i][j] == 1 || r_map[i][j] == 5||r_map[i][j]==7)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(1, &src, &dst, c, 0.0f);
					}
					//�ǃe�N�X�`��
					if (r_map[i][j] == 9)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(3, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 10)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(18, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 11)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(19, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 12)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(20, &src, &dst, c, 0.0f);
					}
					//���e�N�X�`��
					if (r_map[i][j] == 6)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(10, &src, &dst, c, 0.0f);
					}
				}
			}
		}

	}
}
	


