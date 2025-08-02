/**
 *	@file 	D:/ProgramStady/Game/bom_panic/source/title/shot_sample/src/LaserBullet.cpp
 *	@brief
 *	@author	yuto uchida
 *	@data   2011-01-25
 *	@note
 *
 */
#include "LaserBullet.h"

#include "common/Man.h"
#include "directx/Manager.h"
#include "game/GameSystem.h"
#include "tips/Collsion.h"
#include "tips/Primitive.h"

// レーザーのサイズ
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
    // 初期化
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
        // レーザが残っているなら根元から消していく
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

    // 中心座標から4点を求める
    // ※	ここの頂点座標系は３Ｄ座標系と考える
    //		デカルト座標系ではない
    // 右上
    vec_pnt[0] = D3DXVECTOR3(m_length, gc_size, 0.f);
    // 左上
    vec_pnt[1] = D3DXVECTOR3(0.f, gc_size, 0.f);
    // 右下
    vec_pnt[2] = D3DXVECTOR3(m_length, -gc_size, 0.f);
    // 左下
    vec_pnt[3] = D3DXVECTOR3(0.f, -gc_size, 0.f);

    // スクリーン座標に変換
    for (int i = 0; i < 4; ++i)
    {
        D3DXVECTOR3 tmp = vec_pnt[i];
        vec_pnt[i].x    = tmp.x * m_dir.x - tmp.y * m_dir.y;
        vec_pnt[i].y    = tmp.x * m_dir.y + tmp.y * m_dir.x;

        aVertex[i].Rhw   = 1.f;
        aVertex[i].Vec   = D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z) + vec_pnt[i];
        aVertex[i].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
    }

    //	描画
    DrawPrimitive2DSVertexQuad(aVertex);
}

/*
        @brief	打つ角度
        @param	角度指定
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

    //	衝突判定
    INTERSECT_RECT2D_DATA_ST chr01(i_cpos.x, i_cpos.y, i_size_x, i_size_y);

    //	レーザーの線の中心位置へ
    INTERSECT_RECT2D_DATA_ST chr02(m_pos.x + m_length / 2.f, m_pos.y, m_length, gc_size);
    return isIntersectedRect2D(chr01, chr02);
}

void C_LaserBullet::shot(const D3DXVECTOR3& i_spos)
{
    m_pos   = i_spos;
    mb_shot = true;
}
