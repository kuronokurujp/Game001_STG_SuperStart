/**
 */
#include "LaserBullet.h"

#include "common/Man.h"
#include "directx/Manager.h"
#include "game/GameSystem.h"
#include "tips/Collsion.h"
#include "tips/Primitive.h"

// ���[�U�[�̃T�C�Y
const float gc_size       = 32.0f;
const float gc_add_length = 10.0f;

C_LaserBullet::C_LaserBullet()
    : m_pos(0.f, 0.f, 0.f), m_dir(1.f, 0.f, 0.f), m_length(1.f), mb_shot(false)
{
}
C_LaserBullet::~C_LaserBullet()
{
}

void C_LaserBullet::init()
{
    // ������
    m_length = 0;
    mb_shot  = false;
}
void C_LaserBullet::release()
{
}
void C_LaserBullet::update()
{
    if (mb_shot == false)
    {
        // ���[�U���c���Ă���Ȃ獪����������Ă���
        if (m_length > 0.f)
        {
            m_length -= gc_add_length;
        }
        else
        {
            m_length = 0.f;
        }
        return;
    }

    GameLib::C_GameSystem& g = GameLib::C_GameSystem::inst();

    if ((m_pos.x + m_length) < g.getScreenWidth())
    {
        m_length += gc_add_length;
    }
    else
    {
        m_length = g.getScreenWidth() - m_pos.x;
    }
    mb_shot = false;
}
void C_LaserBullet::draw() const
{
    if (m_length <= 0.f)
    {
        return;
    }

    PRIMITIVE_VERTEX_COLOR_ST aVertex[4];
    D3DXVECTOR3 vec_pnt[4];

    // ���S���W����4�_�����߂�
    // ��	�����̒��_���W�n�͂R�c���W�n�ƍl����
    //		�f�J���g���W�n�ł͂Ȃ�
    // �E��
    vec_pnt[0] = D3DXVECTOR3(m_length, gc_size, 0.f);
    // ����
    vec_pnt[1] = D3DXVECTOR3(0.f, gc_size, 0.f);
    // �E��
    vec_pnt[2] = D3DXVECTOR3(m_length, -gc_size, 0.f);
    // ����
    vec_pnt[3] = D3DXVECTOR3(0.f, -gc_size, 0.f);

    // �X�N���[�����W�ɕϊ�
    for (int i = 0; i < 4; ++i)
    {
        D3DXVECTOR3 tmp = vec_pnt[i];
        vec_pnt[i].x    = tmp.x * m_dir.x - tmp.y * m_dir.y;
        vec_pnt[i].y    = tmp.x * m_dir.y + tmp.y * m_dir.x;

        aVertex[i].Rhw   = 1.f;
        aVertex[i].Vec   = D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z) + vec_pnt[i];
        aVertex[i].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    //	�`��
    DrawPrimitive2DSVertexQuad(aVertex);
}

/*
        @brief	�łp�x
        @param	�p�x�w��
*/
void C_LaserBullet::setBulletAngle(float i_angle)
{
    m_dir.x = cos(i_angle * ANGLE_TO_RADIAN);
    m_dir.y = sin(i_angle * ANGLE_TO_RADIAN);
    m_dir.z = 0.f;
}

bool C_LaserBullet::isIntersected(const D3DXVECTOR3& i_cpos, float i_size_x, float i_size_y)
{
    if (m_length <= 0.f)
    {
        return false;
    }

    //	�Փ˔���
    INTERSECT_RECT2D_DATA_ST chr01(i_cpos.x, i_cpos.y, i_size_x, i_size_y);

    //	���[�U�[�̐��̒��S�ʒu��
    INTERSECT_RECT2D_DATA_ST chr02(m_pos.x + m_length / 2.f, m_pos.y, m_length, gc_size);
    return isIntersectedRect2D(chr01, chr02);
}

void C_LaserBullet::shot(const D3DXVECTOR3& i_spos)
{
    m_pos   = i_spos;
    mb_shot = true;
}
