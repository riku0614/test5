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
#include "ObjText.h"
#include "UtilityModule.h"



//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjMain::CObjMain(int map[ROOM_X][ROOM_Y])
{
	memcpy(r_map, map, sizeof(int)*(ROOM_X * ROOM_Y));
}





//�C�j�V�����C�Y
void CObjMain::Init()
{
	m_scroll_x = 64.0f;
	m_scroll_y = 64.0f;

	map_chg = 0;
	room_chg = 0;
	stop_flg = true;
	spawn_point[7] = NULL;
	room_in = true;
	delete_flg = false;
	first_stop = true;

	
	map_Item = false;
	map_Item_2 = false;
	pepepe = false;
	pepepe_2 = false;
	room_chg_stop = false;

	nothing_flg = false;
	open_flg = false;
	m_time = 0;

	//�����}�b�v�f�[�^
	r[1] = Save::ExternalDataOpen(L"�����P�E�T�N��.csv", &size);
	r[2] = Save::ExternalDataOpen(L"�����Q�E�T�N��.csv", &size);
	r[3] = Save::ExternalDataOpen(L"�����R�E�T�N��.csv", &size);
	r[4] = Save::ExternalDataOpen(L"�����S�E�T�N��.csv", &size);
	r[5] = Save::ExternalDataOpen(L"�����T�E�T�N��.csv", &size);
	r[6] = Save::ExternalDataOpen(L"�����U�E�T�N��.csv", &size);

	//�L���}�b�v�f�[�^
	p[0] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��1.csv", &size);
	p[1] = Save::ExternalDataOpen(L"�}�b�v�R.csv", &size);
	p[2] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��2.csv", &size);
	p[3] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��3.csv", &size);
    p[4] = Save::ExternalDataOpen(L"�`�[���J���}�b�v�ĂS.csv", &size);
	p[5] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��5.csv", &size);
    p[6] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��6.csv", &size);
	p[7] = Save::ExternalDataOpen(L"�`�[���J���}�b�v��7.csv", &size);
	
	
}

//�A�N�V����
void CObjMain::Action()
{

	//�����}�b�v���U��񂵂���Z�[�u�����}�b�v�ւ̃��[�h�ɐ؂�ւ���
	if (room_chg >= 7)
	{
		room_chg = 1;
		room_chg_stop = true;
	}
	//�W�K�̃}�b�v�̏���
	if (map_chg == 0)
	{
		//�L���}�b�v���狳���}�b�v�ւ̐؂�ւ�����
		if (room_chg >= 1 && room_in == true && stop_flg == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(4, L"4������SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(4);

			//��l���̏����ʒu��ύX
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			hero->SetX(20.0f*64.0f);
			hero->SetY(4.0f*64.0f);
			m_scroll_x = -15.0f*64.0f;
			m_scroll_y = -5.0f*64.0f;

			//�V�K�Ƀ}�b�v�����[�h���邷�鏈���ƃZ�[�u�����}�b�v�����[�h���鏈���̐؂�ւ�
			if (room_chg_stop == false)
			{
				RoomMapChanger(r_map, r, room_chg);
			}
			else
			{
				for (int i = 0; i < ROOM_X; i++)
				{
					for (int j = 0; j < ROOM_Y; j++)
					{
						r_map[i][j] = save_room_map[i][j][room_chg];

					}
				}

			}
		}
		//�����̋�������L���ւ̃}�b�v�؂�ւ��i�P�x�����񂳂Ȃ��j
		if (room_in == false && stop_flg == true && first_stop == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(5, L"5�}�b�v�؂�ւ�SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(5);

			//�}�b�v�؂�ւ��֐����Ăяo��
			MapChanger(map_chg, m_map, p);

			//��l���̏����ʒu��ύX
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			hero->SetX(0.0f);
			hero->SetY(64.0f * 3);
			m_scroll_x = 0.0f;
			m_scroll_y = 0.0f;

			


			first_stop = false;
		}
		else if (room_in == false && stop_flg == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(5, L"5�}�b�v�؂�ւ�SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(5);

			
		}

	}
	//�V�K�ȍ~�̃}�b�v�̏���
	if (map_chg >= 1)
	{
		if (map_chg > 0 && stop_flg == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(5, L"5�}�b�v�؂�ւ�SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(5);
			if (stop_flg2 == true)
			{
				//�}�b�v�؂�ւ��֐����Ăяo��
				MapChanger(map_chg, m_map, p);
				stop_flg = false;
			}
			else
			{
				memcpy(m_map, save_map, sizeof(int)*(MAP_X*MAP_Y));
			}
			//��l���̏����ʒu�̒l���֐��Ŏw�肷��
			spawn_point[map_chg] = SpawnChanger(map_chg);

			//��l���̏����ʒu��ύX
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			hero->SetX(spawn_point[map_chg]);
			hero->SetY(0.0f);
			m_scroll_x = spawn_point[map_chg] * 1.0f;
			m_scroll_y = 0.0f;
			
		

			

		}
		//�L���}�b�v����}�b�v�ւ̐؂�ւ�����
		else if (room_in == false && stop_flg == true)
		{
			//���y���̓ǂݍ���
			Audio::LoadAudio(5, L"5�}�b�v�؂�ւ�SE.wav", SOUND_TYPE::EFFECT);

			//���y�X�^�[�g
			Audio::Start(5);

			//��l���̏����ʒu��ύX
			CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
			hero->SetX(20.0f*64.0f);
			hero->SetY(4.0f*64.0f);
			m_scroll_x = -15.0f*64.0f;
			m_scroll_y = -5.0f*64.0f;
			//�V�K�Ƀ}�b�v�����[�h���邷�鏈���ƃZ�[�u�����}�b�v�����[�h���鏈���̐؂�ւ�
			if (room_chg_stop == false)
			{
				RoomMapChanger(r_map, r, room_chg);
			}
			else
			{
				for (int i = 0; i < ROOM_X; i++)
				{
					for (int j = 0; j < ROOM_Y; j++)
					{
						r_map[i][j] = save_room_map[i][j][room_chg];

					}
				}
			}
		}


	}


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

	//�M�~�b�N�̃q�b�g�{�b�N�X���}�b�v���ƂɕύX���鏈��
	if (stop_flg == true)
	{
		HitBoxChanger(map_chg, m_map, room_in, room_chg, r_map);
		stop_flg2 = false;

	}

	//�G�L�����̐����i�L���p�j
	if (stop_flg == true)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 5)
				{

					//�G�I�u�W�F�N�g�쐬
					CObjEnemy* obje = new CObjEnemy((j - 1)*64.0f + m_scroll_x, (i - 1)*64.0f + m_scroll_y);
					Objs::InsertObj(obje, OBJ_ENEMY, 11);




				}
			}

		}
	}

	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
			if (m_map[i][j] == 34)
			{
				if ((j*64.0f) + 64.0f >= hero->GetX() && (j * 64.0f) - 64.0f <= hero->GetX())
				{

					//�t���O�𓥂񂾂�G���o������I�u�W�F�N�g�쐬
					CObjSpwanEnemy* objf = new CObjSpwanEnemy(hx + -(m_scroll_x), hy + (5 * 64.0f) + -(m_scroll_y));
					Objs::InsertObj(objf, OBJ_SPWANENEMY, 38);

					m_map[i][j] = 1;
				}
			}
		}
	}
	for (int i = 0; i < ROOM_X; i++)
	{
		for (int j = 0; j < ROOM_Y; j++)
		{
			if (r_map[i][j] == 34)
			{
				if ((j*64.0f) + 64.0f >= hero->GetX() && (j * 64.0f) - 64.0f <= hero->GetX())
				{

					//�t���O�𓥂񂾂�G���o������I�u�W�F�N�g�쐬
					CObjSpwanEnemy* objf = new CObjSpwanEnemy(hx + -(m_scroll_x), hy + (5 * 64.0f) + -(m_scroll_y));
					Objs::InsertObj(objf, OBJ_SPWANENEMY, 38);

					r_map[i][j] = 1;
				}
			}
		}
	}
	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
			if (m_map[i][j] == 35)
			{
				if ((i*64.0f) + 64.0f >= hero->GetY() && (i * 64.0f) - 64.0f <= hero->GetY())
				{

					//�t���O�𓥂񂾂�G���o������I�u�W�F�N�g�쐬
					CObjSpwanEnemy* objf = new CObjSpwanEnemy(hx + -(m_scroll_x), hy + (5 * 64.0f) + -(m_scroll_y));
					Objs::InsertObj(objf, OBJ_SPWANENEMY, 38);

					m_map[i][j] = 1;
				}
			}
		}
	}
	for (int i = 0; i < ROOM_X; i++)
	{
		for (int j = 0; j < ROOM_Y; j++)
		{
			if (r_map[i][j] == 35)
			{
				if ((i*64.0f) + 64.0f >= hero->GetY() && (i * 64.0f) - 64.0f <= hero->GetY())
				{

					//�t���O�𓥂񂾂�G���o������I�u�W�F�N�g�쐬
					CObjSpwanEnemy* objf = new CObjSpwanEnemy(hx + -(m_scroll_x), hy + (5 * 64.0f) + -(m_scroll_y));
					Objs::InsertObj(objf, OBJ_SPWANENEMY, 38);

					r_map[i][j] = 1;
				}
			}
		}
	}
	//�A�C�e���u���v�̕\�������F�����p
	if (stop_flg == true && room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 4)
				{

					//�A�C�e���I�u�W�F�N�g�쐬
					CObjItem * obji = new CObjItem(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(obji, OBJ_ITEM, 16);

				}
			}
		}
	}

	if (hero->GetEnemyFlag() == true)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 25)
				{

					//�����Ƃ�����o������G�I�u�W�F�N�g�쐬
					CObjFastEnemy* objf = new CObjFastEnemy(hx + -(m_scroll_x), hy + (5 * 64.0f) + -(m_scroll_y));
					Objs::InsertObj(objf, OBJ_FASTENEMY, 13);

					m_map[i][j] = 1;

				}
			}
		}
	}

	//�A�C�e���u���v�̕\�������F�����p

	//�A�C�e���u�����p�v�̕\�������F�L���p
	if (stop_flg == true && room_in == true)
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == 4)
				{

					//�A�C�e���I�u�W�F�N�g�쐬
					CObjItem * obji = new CObjItem(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(obji, OBJ_ITEM, 16);




				}
			}

		}

	}
	//�A�C�e���u���v�̕\�������F�L���p
	if (stop_flg == true && room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 4)
				{

					//�A�C�e���I�u�W�F�N�g�쐬
					CObjItem * objir = new CObjItem(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objir, OBJ_ITEM, 16);




				}
			}

		}
	}
	//�A�C�e���u��v�̕\�������F�L���p
	if (room_in == false && stop_flg == true)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 21)
				{

					//�A�C�e���I�u�W�F�N�g�쐬
					CObjheal * objh = new CObjheal(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objh, OBJ_HEAL, 16);




				}
			}

		}

	}




	//�A�C�e���u��v�̕\�������F�����p
	if (room_in == true && stop_flg == false)
	{

		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == 5)
				{

					//�A�C�e���I�u�W�F�N�g�쐬
					CObjheal * objh = new CObjheal(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objh, OBJ_HEAL, 16);




				}
			}

		}

	}
	//�A�C�e���u�o�[���̂悤�Ȃ��́v�̕\�������F�L���p
	if (stop_flg == true && room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 26)
				{

					//�A�C�e���I�u�W�F�N�g�쐬
					CObjbar * objba = new CObjbar(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objba, OBJ_BAR, 16);




				}
			}

		}
	}
	//�A�C�e���u�o�[���̂悤�Ȃ��́v�̕\�������F�����p
	if (room_in == true && stop_flg == true)
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == 26)
				{

					//�A�C�e���I�u�W�F�N�g�쐬
					CObjbar * objba = new CObjbar(j*64.0f - m_scroll_x, i*64.0f - m_scroll_y);
					Objs::InsertObj(objba, OBJ_BAR, 16);




				}
			}

		}

	}

		stop_flg = false;

	
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
	//�L���p
	if (room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] > 0)
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
	//�����p
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
						(x, y, x + vx, y + vy,j * 64 + edge[k][0], i * 64 + edge[k][1], j * 64 + edge[k][2], i * 64 + edge[k][3],&px, &py);

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
	//�L���p
	if (room_in == false)
	{
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{


				if (m_map[i][j] <= 99 && m_map[i][j] >=3  && m_map[i][j] != 7 && m_map[i][j] != 21 && m_map[i][j] != 25 && m_map[i][j] != 26 && m_map[i][j] != 34 && m_map[i][j] != 35 )
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

						if(r <= 0.0f)
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
								if (m_map[i][j] == 3 && *c_id == CHAR_HERO && *k_id == ITEM_KEY)
								{
									stop_flg = true;
									map_chg++;
									stop_flg2 = true;
									first_stop = true;
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									*k_id = 99;

									hero->SetFlug(false);
									if (map_chg == 7)
									{
										Scene::SetScene(new CSceneGameClear);
									}


									//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									save_x[map_chg][1] = hero->GetX();
									save_y[map_chg][1] = hero->GetY();
									save_scroll_x[map_chg][1] = main->GetScrollX();
									save_scroll_y[map_chg][1] = main->GetScrollY();
									map_chg++;
								}
								else if (m_map[i][j] == 17  && *c_id == CHAR_HERO)
								{
									if (room_in == false)
									{
										room_in = true;
										stop_flg = true;

										//item->SetFlag(true);
										
										room_chg++;
								
										//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);



										save_x[map_chg][0] = hero->GetX()+32.0f;
										save_y[map_chg][0] = hero->GetY();
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();

										memcpy(save_map, m_map, sizeof(int)*(MAP_X * MAP_Y));
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
									if (map_chg == 7)
									{
										Scene::SetScene(new CSceneGameClear);
									}

									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									*k_id = 99;

									hero->SetFlug(false);

									stop_flg = true;
									stop_flg2 = true;
									first_stop = true;
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
									save_x[map_chg][1] = hero->GetX();
									save_y[map_chg][1] = hero->GetY();
									save_scroll_x[map_chg][1] = main->GetScrollX();
									save_scroll_y[map_chg][1] = main->GetScrollY();
									map_chg++;
								}
								else if (m_map[i][j] == 16  && *c_id == CHAR_HERO)
								{
									if (room_in == false)
									{
										room_in = true;
										room_chg++;
								;
										
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
										save_x[map_chg][0] = hero->GetX();
										save_y[map_chg][0] = hero->GetY() + 32.0f;
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();

										memcpy(save_map, m_map, sizeof(int)*(MAP_X * MAP_Y));
									}

								}
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//��
								*left = true;//��l�����猩�āA�E�̕������Փ˂��Ă���
								*x = bx - 64.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								*vx = -(*vx)*0.1f;//-VX*�����W��
								if (m_map[i][j] == 3 && *c_id == CHAR_HERO && *k_id == ITEM_KEY&&Input::GetVKey('E')==true)
								{
									stop_flg = true;
									stop_flg2 = true;
									
									first_stop = true;
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									*k_id = 99;

									hero->SetFlug(false);

									if (map_chg == 7)
									{
										Scene::SetScene(new CSceneGameClear);
									}

									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
									save_x[map_chg][1] = hero->GetX() ;
									save_y[map_chg][1] = hero->GetY();
									save_scroll_x[map_chg][1] = main->GetScrollX();
									save_scroll_y[map_chg][1] = main->GetScrollY();

									map_chg++;
								}
								else if (m_map[i][j] == 18&& *c_id == CHAR_HERO)
								{
									if (room_in == false)
									{
										room_in = true;
										stop_flg = true;

										//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����B
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										save_x[map_chg][0] = hero->GetX() - 32.0f;
										save_y[map_chg][0] = hero->GetY();
										save_scroll_x[map_chg][0] = main->GetScrollX();
										save_scroll_y[map_chg][0] = main->GetScrollY();

										memcpy(save_map, m_map, sizeof(int)*(MAP_X * MAP_Y));
									}

								}
								
							}
							if (r > 225 && r < 315)
							{
								//��
								*up = true;//��l�����猩�āA��̕������Փ˂��Ă���
								*y = by + 64.0f + (scroll_y);//�u���b�N�̈ʒu-��l����
								if (*vy < 0)
								{
									*vy = 0.0f;
								}
								if (m_map[i][j] == 3 && *c_id == CHAR_HERO && *k_id == ITEM_KEY)
								{
									stop_flg = true;
									stop_flg2 = true;
									first_stop = true;
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									*k_id = 99;

									hero->SetFlug(false);
									if (map_chg == 7)
									{
										Scene::SetScene(new CSceneGameClear);
									}

									//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����
									CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

									save_x[map_chg][1] = hero->GetX();
									save_y[map_chg][1] = hero->GetY() - 32.0f;
									save_scroll_x[map_chg][1] = main->GetScrollX();
									save_scroll_y[map_chg][1] = main->GetScrollY();
									map_chg++;
								}
							
								else if (m_map[i][j] == 15 && *c_id == CHAR_HERO)
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

										memcpy(save_map, m_map, sizeof(int)*(MAP_X * MAP_Y));
									}

								}
								

							}
						}
					}

				}
			}
		}
	}
	//�����p
	else
	{
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{


				if (r_map[i][j] <= 99 && r_map[i][j] > 1 && r_map[i][j] != 7 && r_map[i][j] != 26 && r_map[i][j] != 34 && r_map[i][j] != 35 )
				{
					//�v�f�ԍ������W�ɕύX
					float bx = j * 64.0f;
					float by = i * 64.0f;

					//�X�N���[���̉e��
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//��l���ƃu���b�N�̓����蔻��
					if ((*x + (-scroll_x) + BLOCK_SIZE_X > bx) && (*x + (-scroll_x) < bx + BLOCK_SIZE_X) && (*y + (-scroll_y) + BLOCK_SIZE_Y > by) && (*y + (-scroll_y) < by + BLOCK_SIZE_Y))
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
							if ((r < 45 && r > 0) || r > 315)
							{
								//�E
								*right = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*x = bx + 64.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								*vx = -(*vx)*0.1f;//-VX*�����W��
								
								if (r_map[i][j] == 31 && Input::GetVKey('E') == true)
								{
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									font_story_flg = true;
									hero->SetHeroStop(true);
								}
								//�ʏ�̎�
								else if (r_map[i][j] == 17 && *c_id == CHAR_HERO)
								{
									if (room_in == true && room_chg >= 1)
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

										if (room_chg >= 1)
										{
											for (int i = 0; i < ROOM_X; i++)
											{
												for (int j = 0; j < ROOM_Y; j++)
												{
													save_room_map[i][j][room_chg] = r_map[i][j];
												}
											}
										}
									}
									//�����̕����Ńo�[�����g��Ȃ��ƊJ���Ȃ�����
									else if (room_in == true && room_chg == 0)
									{
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										if (hero->Getflag_3() == true && Input::GetVKey('E'))
										{
											CObjGameUI* gui = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);
											hero->SetFlug_3(false);
											gui->SetID(99);

											room_in = false;
											stop_flg = true;


										}
									}
								}
								

							}
						}

						if (r > 45 && r < 135)
						{
							//��
							*down = true;//��l�����猩�āA���̕������Փ˂��Ă���
							*y = by - 64.0f + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
							if (r_map[i][j] == 2)
								*bt = m_map[i][j];
							*vy = 0.0f;
							if (r_map[i][j] == 31 && Input::GetVKey('E') == true)
							{
								CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
								font_story_flg = true;
								hero->SetHeroStop(true);
							}
							//�ʏ�̎�
							else if (r_map[i][j] == 16 && *c_id == CHAR_HERO)
							{
								if (room_in == true && room_chg >= 1)
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

									if (room_chg >= 1)
									{
										for (int i = 0; i < ROOM_X; i++)
										{
											for (int j = 0; j < ROOM_Y; j++)
											{
												save_room_map[i][j][room_chg] = r_map[i][j];
											}
										}
									}
								}
								//�����̕����Ńo�[�����g��Ȃ��ƊJ���Ȃ�����
								else if (room_in == true && room_chg == 0)
								{
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									if (hero->Getflag_3() == true && Input::GetVKey('E'))
									{
										CObjGameUI* gui = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);
										hero->SetFlug_3(false);
										gui->SetID(99);

										room_in = false;
										stop_flg = true;

									}

								}
							}
							

							
						}
							if (r > 135 && r < 225)
							{
								//��
								*left = true;//��l�����猩�āA�E�̕������Փ˂��Ă���
								*x = bx - 64.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�]
								*vx = -(*vx)*0.1f;//-VX*�����W��

								if (r_map[i][j] == 31 && Input::GetVKey('E') == true)
								{
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									font_story_flg = true;
									hero->SetHeroStop(true);
								}
								//�ʏ�̎�
								else if (r_map[i][j] == 18 && *c_id == CHAR_HERO)
								{
									if (room_in == true && open_flg==true)
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

										if (room_chg >= 1)
										{
											for (int i = 0; i < ROOM_X; i++)
											{
												for (int j = 0; j < ROOM_Y; j++)
												{
													save_room_map[i][j][room_chg] = r_map[i][j];
												}
											}
										}
									}
									else if (room_in == true && open_flg == false)
									{
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										
										if (hero->Getflag_3() == true && Input::GetVKey('E'))
										{
											CObjGameUI* gui = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);
											hero->SetFlug_3(false);
											gui->SetID(99);

											hero->SetX(hero->GetX() - 32.0f);

											open_flg = true;
											font_open_flg = true;

											hero->SetHeroStop(true);
										}
										else if (Input::GetVKey('E') == true)
										{
											font_close_flg = true;
										}
									    
									}

								}
								

							}
							if (r > 225 && r < 315)
							{
								//��
								*up = true;//��l�����猩�āA��̕������Փ˂��Ă���
								*y = by + 64.0f + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
								if (*vy < 0)
								{
									*vy = 0.0f;
								}

								//�{�I���献����鏈��
								if (r_map[i][j] == 19 && Input::GetVKey(VK_RETURN) == true&&nothing_flg==false)
								{

									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									*k_id = ITEM_KEY;

									hero->SetFlug(true);

									font_key_flg = true;

									nothing_flg = true;
								}
								else if (r_map[i][j] == 19 && Input::GetVKey(VK_RETURN) == true && nothing_flg == true)
								{
									font_nothing_flg = true;
								}
								else if (r_map[i][j] == 31 && Input::GetVKey('E') == true)
								{
									CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
									font_story_flg = true;
									hero->SetHeroStop(true);
								}

								//�ʏ�̎�
								else if (r_map[i][j] == 15 && *c_id == CHAR_HERO)
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

										if (room_chg >= 1)
										{
											for (int i = 0; i < ROOM_X; i++)
											{
												for (int j = 0; j < ROOM_Y; j++)
												{
													save_room_map[i][j][room_chg] = r_map[i][j];
												}
											}
										}
									}
									//�����̕����Ńo�[�����g��Ȃ��ƊJ���Ȃ�����
									else if (room_in == true && room_chg == 0)
									{
										CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
										if (hero->Getflag_3() == true && Input::GetVKey('E'))
										{
											CObjGameUI* gui = (CObjGameUI*)Objs::GetObj(OBJ_GAME_UI);
											hero->SetFlug_3(false);
											gui->SetID(99);

										}
										

										room_in = false;
										stop_flg = true;

										//��l�����K�i�ɓ��������u�ԂɈʒu�ƃX�N���[������ۑ�����
										CObjMain* main = (CObjMain*)Objs::GetObj(OBJ_MAIN);

										hero->SetX(save_x[map_chg][0] + hero->GetVX());
										hero->SetY(save_y[map_chg][0] + hero->GetVY());
										main->SetScrollX(save_scroll_x[map_chg][0]);
										main->SetScrollY(save_scroll_y[map_chg][0]);

										memcpy(save_room_map[room_chg], r_map, sizeof(int)*(ROOM_X * ROOM_Y));

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
	
	if (room_in == false)
	{
		//m=map�̑S�v�f�ɃA�N�Z�X
		for (int i = 0; i < MAP_X; i++)
		{
			for (int j = 0; j < MAP_Y; j++)
			{
				if (m_map[i][j] == 4 || m_map[i][j] == 21 || m_map[i][j] == 26)
				{



					//�v�f�ԍ������W�ɕύX
					float bx = j * 64.0f;
					float by = i * 64.0f;

					//�X�N���[���̉e��
					float scroll_x = scroll_on_x ? m_scroll_x : 0;
					float scroll_y = scroll_on_y ? m_scroll_y : 0;
					//��l���ƃu���b�N�̓����蔻��
					if ((*x + (-scroll_x) + 64.0f > bx) && (*x + (-scroll_x) < bx + ITEM_SIZE_X) && (*y + (-scroll_y) + 64.0f > by) && (*y + (-scroll_y) < by + ITEM_SIZE_Y))
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
							if ((r < 45 && r>=0) || r > 315)
							{
								//�E
								*right = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*x = bx + ITEM_SIZE_X + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								ix = bx / 64;
								iy = by / 64;

								//�A�C�e�����擾�����ۂɃA�C�e������������
								if (delete_flg == true)
								{
									m_map[iy][ix] = 1;

									delete_flg = false;
								}

								*vx = -(*vx)*0.1f;//-VX*�����W��
							}
							if (r > 45 && r < 135)
							{
								//��
								*down = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*y = by - 64.0f + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
								ix = bx / 64;
								iy = by / 64;

								//�A�C�e�����擾�����ۂɃA�C�e������������
								if (delete_flg == true)
								{
									m_map[iy][ix] = 1;

									delete_flg = false;
								}
								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//��
								*left = true;//��l�����猩�āA�E�̕������Փ˂��Ă���
								*x = bx - 64.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								ix = bx / 64;
								iy = by / 64;

								//�A�C�e�����擾�����ۂɃA�C�e������������
								if (delete_flg == true)
								{
									m_map[iy][ix] = 1;

									delete_flg = false;
								}
								*vx = -(*vx)*0.1f;//-VX*�����W��
							}
							if (r > 225 && r < 315)
							{
								//��
								*up = true;//��l�����猩�āA��̕������Փ˂��Ă���
								*y = by + ITEM_SIZE_Y + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
								ix = bx / 64;
								iy = by / 64;
								//�A�C�e�����擾�����ۂɃA�C�e������������
								if (delete_flg == true)
								{
									m_map[iy][ix] = 1;

									delete_flg = false;
								}
								if (*vy < 0)
								{
									*vy = 0.0f;
								}


							}
							//��
							if (m_map[i][j] == 4)
							{
								map_Item = true;
							}
							//��
							if (m_map[i][j] == 21)
							{
								map_Item_2 = true;
							}
							//�o�[��
							if (m_map[i][j] == 26)
							{
								map_Item_3 = true;
							}


						}


					}


				}

			}

		}
	}
	//�����p
	if(room_in==true)
	{
		//m=map�̑S�v�f�ɃA�N�Z�X
		for (int i = 0; i < ROOM_X; i++)
		{
			for (int j = 0; j < ROOM_Y; j++)
			{
				if (r_map[i][j] == 4 || r_map[i][j] == 21 || r_map[i][j] == 26)
				{



					//�v�f�ԍ������W�ɕύX
					float bx = j * 64.0f;
					float by = i * 64.0f;

				//�X�N���[���̉e��
				float scroll_x = scroll_on_x ? m_scroll_x : 0;
				float scroll_y = scroll_on_y ? m_scroll_y : 0;
				//��l���ƃu���b�N�̓����蔻��
				if ((*x + (-scroll_x) + 64.0f > bx) && (*x + (-scroll_x) < bx + ITEM_SIZE_X) && (*y + (-scroll_y) + 64.0f > by) && (*y + (-scroll_y) < by + ITEM_SIZE_Y))
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
						 if ((r < 45 && r>=0) || r > 315)
						 {
							//�E
							*right = true;//��l�����猩�āA���̕������Փ˂��Ă���
							*x = bx + ITEM_SIZE_X + (scroll_x);//�u���b�N�̈ʒu-��l����
							ix = bx / 64;
							iy = by / 64;

								if (delete_flg == true)
								{
									r_map[iy][ix] = 1;

									delete_flg = false;
								}
								*vx = -(*vx)*0.1f;//-VX*�����W��

							}
							if (r > 45 && r < 135)
							{
								//��
								*down = true;//��l�����猩�āA���̕������Փ˂��Ă���
								*y = by - 64.0f + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
								ix = bx / 64;
								iy = by / 64;

								if (delete_flg == true)
								{
									r_map[iy][ix] = 1;

									delete_flg = false;
								}

								*vy = 0.0f;
							}
							if (r > 135 && r < 225)
							{
								//��
								*left = true;//��l�����猩�āA�E�̕������Փ˂��Ă���
								*x = bx - 64.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
								ix = bx / 64.0f;
								iy = by / 64.0f;

								if (delete_flg == true)
								{
									r_map[iy][ix] = 1;

								delete_flg = false;
							}
							*vx = -(*vx)*0.1f;//-VX*�����W��
						}
						if (r > 225 && r < 315)
						{
							//��
							*up = true;//��l�����猩�āA��̕������Փ˂��Ă���
							*y = by + ITEM_SIZE_Y + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
							ix = bx / 64;
							iy = by / 64;

								if (delete_flg == true)
								{
									r_map[iy][ix] = 1;

									delete_flg = false;
								}
								if (*vy < 0)
								{
									*vy = 0.0f;
								}


						}
						//��
						if (r_map[i][j] == 4)
						{
							map_Item = true;
						}
						//��
						if (r_map[i][j] == 21)
						{
							map_Item_2 = true;
						}
						//�o�[���̂悤�Ȃ���
						if (r_map[i][j] == 26)
						{
							map_Item_3 = true;
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

	//��l���I�u�W�F�N�g�̃A�h���X
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

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
					if (m_map[i][j] == 1 || m_map[i][j] == 4 || m_map[i][j] == 7 || m_map[i][j] == 13 || m_map[i][j] == 21||m_map[i][j]==25 || m_map[i][j] == 26)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(1, &src, &dst, c, 0.0f);
					}
					//13���Ȃ���΁@��
				
					if (m_map[i][j] == 34||m_map[i][j]==35)				
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(39, &src, &dst, c, 0.0f);
					}
					//�K�i�e�N�X�`��
					if (m_map[i][j] == 3)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(7, &src, &dst, c, 0.0f);
					}
					//�ǃe�N�X�`���S��
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
					}//�ǃe�N�X�`���S��

					//���e�N�X�`���S��
					if (m_map[i][j] == 15)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(25, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 16)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(26, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 17)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(28, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 18)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(27, &src, &dst, c, 0.0f);
					}//���e�N�X�`���S��
					 //�Ǌp4��
					if (m_map[i][j] == 27)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(34, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 28)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(35, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 29)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(36, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 30)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(37, &src, &dst, c, 0.0f);
					}//�p��4��

					 //�Ǌp�Q�E4��
					if (m_map[i][j] == 31)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(38, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 32)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(39, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 33)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(40, &src, &dst, c, 0.0f);
					}
					if (m_map[i][j] == 34)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(41, &src, &dst, c, 0.0f);
					}//�p�ǂQ�E4��
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
					if (r_map[i][j] >= 1&&r_map[i][j]<= 8|| r_map[i][j] == 5||r_map[i][j]==7|| r_map[i][j] == 8|| r_map[i][j] == 13||r_map[i][j]==31||r_map[i][j]==26)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(1, &src, &dst, c, 0.0f);
					}
					//���܂Ƃ�
					if(r_map[i][j]==2)
					{
						src.m_top = 100.0f;
						src.m_left = 350.0f;
						src.m_right = src.m_left + 200.0f;
						src.m_bottom = src.m_top + 200.0f;

						Draw::Draw(30, &src, &dst, c, 0.0f);
					}
					//�֎q�܂Ƃ�
					if(r_map[i][j]==3)
					{
						src.m_top = 50.0f;
						src.m_left = 320.0f;
						src.m_right = src.m_left + 180.0f;
						src.m_bottom = src.m_top + 180.0f;

						Draw::Draw(31, &src, &dst, c, 0.0f);
					}
					//�G�̏o����
					if (r_map[i][j] == 34 || r_map[i][j] == 35)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(43, &src, &dst, c, 0.0f);
					}
					//�ǃe�N�X�`��4��
					if (r_map[i][j] == 9||r_map[i][j]==19)
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

						Draw::Draw(19, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 11)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(18, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 12)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(20, &src, &dst, c, 0.0f);
					}//�ǃe�N�X�`���S��

					//���e�N�X�`��4��
					if (r_map[i][j] == 15)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(26, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 16)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(25, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 17)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(28, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 18)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 50.0f;
						src.m_bottom = src.m_top + 50.0f;

						Draw::Draw(27, &src, &dst, c, 0.0f);
					}//���S��
					
					 //�Ǌp4��
					if (r_map[i][j] == 27)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(34, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 28)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(35, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 29)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(36, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 30)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 63.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(37, &src, &dst, c, 0.0f);
					}//�p��4��2
						
					//�A�C�e���i���j
					if (r_map[i][j] == 4)
					{

							//�`��؂���ʒu
							src.m_top = 17.0f;
							src.m_left = 20.0f;
							src.m_right = src.m_left + 25.0f;
							src.m_bottom = src.m_top + 30.0f;
							
							//�\���ʒu�̐ݒ�
							dst.m_top = i * 64.0f + m_scroll_y;
							dst.m_left = j * 64.0f + m_scroll_x;
							dst.m_right = dst.m_left + ITEM_SIZE_X;
							dst.m_bottom = dst.m_top + ITEM_SIZE_Y;

							Draw::Draw(8, &src, &dst, c, 0.0f);
					}
					//�{�I
					if (r_map[i][j] == 19)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;
						
						Draw::Draw(29, &src, &dst, c, 0.0f);
					}
					if (r_map[i][j] == 31)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(33, &src, &dst, c, 0.0f);
					}
					//�{
					if (r_map[i][j] == 30)
					{
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						Draw::Draw(33, &src, &dst, c, 0.0f);
					}
					//����
					if (r_map[i][j] == 13)
					{

						//�`��؂���ʒu
						src.m_top = 0.0f;
						src.m_left = 0.0f;
						src.m_right = src.m_left + 64.0f;
						src.m_bottom = src.m_top + 64.0f;

						
						Draw::Draw(40, &src, &dst, c, 0.0f);
					}
				}
			}
		}

	}if (font_close_flg == true && m_time <= 100)
	{

		Font::StrDraw(L"�J���Ȃ�... ��������K�v��", 270.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_close_flg == true && m_time > 100)
	{
		font_close_flg = false;

		m_time = 0;

		hero->SetHeroStop(false);
	}

	else if (font_open_flg == true && m_time <= 90)
	{

		Font::StrDraw(L"�o�[�����g����...", 340.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_open_flg == true && m_time > 90)
	{
		font_open_flg = false;

		m_time = 0;

		hero->SetHeroStop(false);
	}
	else if (font_nothing_flg == true && m_time <= 150)
	{

		Font::StrDraw(L"���������Ȃ�...", 340.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_nothing_flg == true && m_time > 150)
	{
		font_nothing_flg = false;

		m_time = 0;
	}
	//�{�I���献����肵���ۂ̃e�L�X�g�̕\���ƈ�莞�Ԃ�������e�L�X�g����������
	else if (font_key_flg == true && m_time <= 150)
	{

		Font::StrDraw(L"������肵��...", 350.0f,530.0f, 25, c);

		m_time++;
	}
	else if(font_key_flg==true&&m_time>150)
	{
		font_key_flg = false;

		m_time = 0;
	}

	//��̃A�C�e���i���j�o�[�W����
	else if (font_key_flg2 == true && m_time <= 150)
	{


		Font::StrDraw(L"������肵��...", 350.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_key_flg2 == true && m_time > 150)
	{
		font_key_flg2 = false;

		m_time = 0;
	}

	//��̃A�C�e���i�K�т��o�[���̂悤�Ȃ��́j�o�[�W����
	else if (font_bar_flg == true && m_time <= 150)
	{
		Font::StrDraw(L"�K�т��o�[���̂悤�Ȃ��̂���肵��...", 230.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_bar_flg == true && m_time > 150)
	{
		font_bar_flg = false;

		m_time = 0;
	}

	//��̃A�C�e���i��j�o�[�W����
	else if (font_heal_flg == true && m_time <= 150)
	{

		Font::StrDraw(L"�����肵��...", 350.0f, 530.0f, 25, c);

		m_time++;
	}
	else if (font_heal_flg == true && m_time > 150)
	{
		font_heal_flg = false;

		m_time = 0;
	}

	//���炷����ǂ񂾍ۂ̌�̃Z���t
	else if (font_story_flg2 == true && m_time <= 200)
	{
		Font::StrDraw(L"����������E�o���Ȃ���΁I", 270.0f, 530.0f, 25, c);
		m_time++;
	}
	else if (font_story_flg2 == true && m_time <= 400)
	{
		Font::StrDraw(L"�܂��͂����̔����J���铹���T����", 250.0f, 530.0f, 25, c);
		m_time++;
	}
	else if(font_story_flg2 == true && m_time > 400)
	{
		font_story_flg2 = false;

		m_time = 0;
	}
}
	


