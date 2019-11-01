//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SceneObjManager.h"

#include "GameHead.h"
#include "ObjMain.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjMain::CObjMain(int map[100][100])
{
	memcpy(m_map, map, sizeof(int)*(100 * 100));
}



//�C�j�V�����C�Y
void CObjMain::Init()
{
	m_scroll_x = -2850.0f;
	m_scroll_y = -64.0f;
}

//�A�N�V����
void CObjMain::Action()
{

	//��l���̈ʒu���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float hx = hero->GetX();
	float hy = hero->GetY();



	//����X�N���[�����C��
	if (hx < 300)
	{
		hero->SetX(300);
		m_scroll_x -= hero->GetVX();
	}

	//�O���X�N���[�����C��
	if (hx > 350)
	{
		hero->SetX(350);
		m_scroll_x -= hero->GetVX();
	}
	//����X�N���[�����C��
	if (hy < 250)
	{
		hero->SetY(250);
		m_scroll_y -= hero->GetVY();
	}

	//�����X�N���[�����C��
	if (hy > 300)
	{
		hero->SetY(300);
		m_scroll_y -= hero->GetVY();


	}


	//�G�o�����C���̗������
	/*/for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			//�}�b�v�̒�����5��T��
			if (m_map[i][j] == 5)
			{
				//5������΁A�G���o��
				CObjEnemy* obje = new CObjEnemy(j,i);
				Objs::InsertObj(obje, OBJ_ENEMY, 10);

				//�G�̏o���ꏊ�̒l��1�ɂ���
				m_map[i][j] = 1;

			}
		}
	}*/

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
	float *x, float *y, bool scroll_on_x,bool scroll_on_y,
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
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] == 9||m_map[i][j]==3)
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
						if ((r < 45 && r>0) || r > 315)
						{
							//�E
							*right = true;//��l�����猩�āA���̕������Փ˂��Ă���
							*x = bx + 64.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�]
							if (m_map[i][j] == 3)
								Scene::SetScene(new CSceneGameClear);
							*vx = -(*vx)*0.1f;//-VX*�����W��
						}
						if (r > 45 && r < 135)
						{
							//��
							*down = true;//��l�����猩�āA���̕������Փ˂��Ă���
							*y = by - 64.0f + (scroll_y);//�u���b�N�̈ʒu-��l���̕�
							if (m_map[i][j] == 2)
								*bt = m_map[i][j];
							else if(m_map[i][j]==3)
								Scene::SetScene(new CSceneGameClear);
							*vy = 0.0f;
						}
						if (r > 135 && r < 225)
						{
							//��
							*left = true;//��l�����猩�āA�E�̕������Փ˂��Ă���
							*x = bx - 64.0f + (scroll_x);//�u���b�N�̈ʒu-��l���̕�
							if (m_map[i][j] == 3)
								Scene::SetScene(new CSceneGameClear);
							*vx = -(*vx)*0.1f;//-VX*�����W��
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
	
	

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j] > 0)
			{
				

				//�\���ʒu�̐ݒ�
				dst.m_top = i * 64.0f+m_scroll_y;
				dst.m_left = j * 64.0f+m_scroll_x;
				dst.m_right = dst.m_left + 64.0;
				dst.m_bottom = dst.m_top + 64.0;

				
				//���e�N�X�`��
				if (m_map[i][j] == 1 || m_map[i][j] >= 4&&m_map[i][j]<9)
				{
					src.m_top = 0.0f;
					src.m_left = 0.0f;
					src.m_right = src.m_left + 64.0f;
					src.m_bottom = src.m_top + 64.0f;

					Draw::Draw(1, &src, &dst, c, 0.0f);
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
				
				
			}
		}

	}
}
