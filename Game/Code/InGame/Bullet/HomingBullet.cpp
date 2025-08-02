/**
 *	@file 	HomingBullet.h
 *	@brief	指定した座標に誘導弾
 *	@author	yuto uchida
 *	@data   2011-01-25
 *	@note 	20120130	ホーミングレーザーが完成したがレーザーの長さの指定ができない
 *						後に修正する
 *
 */
#include "HomingBullet.h"

#include <math.h>

#include "common/Common.h"
#include "common/Man.h"
#include "debug/DebugScreenInterface.h"
#include "directx/Manager.h"
#include "game/GameSystem.h"
#include "tips/Collsion.h"

static float gc_size       = 16.f;
static float gc_half_size  = gc_size / 2.f;
static float gc_speed      = 10.f;
static float gc_turn_speed = 10.f;
static float gc_turn_limit = 10.f;

static const int gc_tree_pos_max = 10;
// #define TEST

C_HomingBullet::C_HomingBullet()
    : mp_tree_pos(NULL),
      m_dir(0.f, 0.f, 0.f),
      m_set_dir(0.f, 0.f, 0.f),
      m_target_pos(1.f, 0.f, 0.f),
      mb_shot(false),
      m_bHoming(false)
{
    mp_tree_pos = new D3DXVECTOR3[gc_tree_pos_max];
    ASSERT(mp_tree_pos);
#ifdef TEST
    mp_tree_pos[0] = D3DXVECTOR3(200.0f, 100.0f, 0.f);
    mp_tree_pos[1] = D3DXVECTOR3(10.0f, 7.0f, 0.f);
#endif
}

C_HomingBullet::~C_HomingBullet()
{
    SAFE_DELETE_ARRAY(mp_tree_pos);
}

void C_HomingBullet::init()
{
    mb_shot   = false;
    m_bHoming = false;
}

void C_HomingBullet::release()
{
}

void C_HomingBullet::update()
{
    if (false == mb_shot)
    {
        return;
    }
#ifndef TEST

    D3DXVECTOR3 pos = mp_tree_pos[0];
    D3DXVECTOR3 dir = m_dir;

    // ターゲット方向に飛ぶ
    if (m_bHoming == true)
    {
        D3DXVECTOR3 vec = m_target_pos - pos;
        D3DXVec3Normalize(&vec, &vec);
        // 二つのベクトル角度算出
        float dot    = D3DXVec3Dot(&dir, &vec);
        float length = D3DXVec3Length(&dir);
        float cosne  = dot / length;
        float sita   = acos(cosne) * 180.f / 3.14f;
        if (sita > gc_turn_limit)
        {
            // スクリーン座標の角度に合わせる
            float target_sita = atan2f(m_target_pos.y - pos.y, m_target_pos.x - pos.x);
            target_sita       = target_sita * 180.f / 3.14f;
            float dir_sita    = atan2f(dir.y, dir.x) * 180.f / 3.14f;
            if (dir_sita > target_sita)
            {
                dir_sita -= gc_turn_speed;
            }
            else if (dir_sita < target_sita)
            {
                dir_sita += gc_turn_speed;
            }
            dir = D3DXVECTOR3(cos(dir_sita * 3.14f / 180.f), sin(dir_sita * 3.14f / 180.f), 0.f);
        }
        else
        {
            dir = vec;
        }
    }

    // オブジェクトツリー座標更新
    for (unsigned i = gc_tree_pos_max - 1; i > 0; --i)
    {
        mp_tree_pos[i] = mp_tree_pos[i - 1];
    }

    pos += (dir * gc_speed);
    mp_tree_pos[0] = pos;
    m_dir          = dir;

    // 対象オブジェクトとの距離をチェックする
    D3DXVECTOR3 chk_vec = pos - m_target_pos;
    if (gc_speed >= D3DXVec3Length(&chk_vec))
    {
        m_bHoming = false;
    }
#endif

    // レーザーが画面害にいるなら削除
    //	画面外かどうかチェック
    INTERSECT_RECT2D_DATA_ST rect(mp_tree_pos[0].x, mp_tree_pos[0].y, gc_size, gc_size);
    if (IsScreenOutScreen2D(rect) == true)
    {
        mb_shot = false;
    }
}
void C_HomingBullet::draw() const
{
    if (false == mb_shot || gc_tree_pos_max <= 1)
    {
        return;
    }

    LPDIRECT3DDEVICE9 device = DirectX::C_Manager::inst()->get_device();
    device->SetVertexShader(NULL);
    device->SetFVF(D3DFVF_XYZRHW);

    // 連結したオブジェクト描画
    D3DXVECTOR3 vertex[gc_tree_pos_max * 2];
    unsigned vertex_max = sizeof(vertex) / sizeof(vertex[0]);
    // 描画する三角形の数
    // 三角形は3点で一つとなる。
    // しかしそれは最初の3点であとは1点を加えるごとに
    // 三角形が一つ増える
    // ストリップの性質
    int primitive_max = (gc_tree_pos_max - 2) * 2 + 2;
    ASSERT(primitive_max > 0);
    D3DXVECTOR3 line_vec(0.f, 0.f, 0.f);
    for (unsigned tree_idx = 0; tree_idx < gc_tree_pos_max; ++tree_idx)
    {
        // 各点の頂点を設定
        if (tree_idx < (gc_tree_pos_max - 1))
        {
            ASSERT((tree_idx + 1) < gc_tree_pos_max);
            D3DXVECTOR3 vec = mp_tree_pos[tree_idx] - mp_tree_pos[tree_idx + 1];
            D3DXVec3Normalize(&vec, &vec);

            // 直行するベクトルを作成
            D3DXVECTOR3 tmp = vec;
            line_vec.x      = tmp.y;
            line_vec.y      = -tmp.x;

            line_vec *= gc_size / 2.0f;
        }

        ASSERT((tree_idx * 2) < vertex_max);
        ASSERT((tree_idx * 2 + 1) < vertex_max);

        vertex[tree_idx * 2]     = mp_tree_pos[tree_idx] + line_vec;
        vertex[tree_idx * 2 + 1] = mp_tree_pos[tree_idx];
    }

    device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, primitive_max, vertex, sizeof(D3DXVECTOR3));
}

/*
        @brief	ホーミング対象の座標指定
        @param	i_target_pos	:	対象座標
*/
void C_HomingBullet::setTargetPos(const D3DXVECTOR3& i_target_pos)
{
    m_target_pos = i_target_pos;
}
/*
        @brief	打つ角度
        @param	角度指定
*/
void C_HomingBullet::setBulletAngle(float i_angle)
{
    m_set_dir.x = cos(i_angle * ANGLE_TO_RADIAN);
    m_set_dir.y = sin(i_angle * ANGLE_TO_RADIAN);
    m_set_dir.z = 0.f;
}

/*
        @brief	弾を撃つ
        @param	i_spos	:	弾の初期座標
*/
void C_HomingBullet::shot(const D3DXVECTOR3& i_spos)
{
    if (false == mb_shot)
    {
        mb_shot = true;
#ifndef TEST
        for (unsigned i = 0; i < gc_tree_pos_max; ++i)
        {
            mp_tree_pos[i] = i_spos;
        }
#endif
        m_bHoming = true;
        m_dir     = m_set_dir;
    }
}

/*
        @brief	交差判定
        @param	i_cpos		:	オブジェクトの中心座標
        @param	i_size_x	:	横サイズ
        @param	i_size_y	:	縦サイズ
        @return	衝突[true]	/	非衝突[false]
*/
bool C_HomingBullet::isIntersected(const D3DXVECTOR3& i_cpos, float i_size_x, float i_size_y)
{
    for (unsigned i = 0; i < gc_tree_pos_max; ++i)
    {
        INTERSECT_RECT2D_DATA_ST chr01(i_cpos.x, i_cpos.y, i_size_x, i_size_y);
        INTERSECT_RECT2D_DATA_ST chr02(mp_tree_pos[i].x, mp_tree_pos[i].y, gc_size, gc_size);

        if (isIntersectedRect2D(chr01, chr02) == true)
        {
            return true;
        }
    }

    return false;
}

//	デバッグ設定用
void C_HomingBullet::setDebug(int in_DebugSceneHandle)
{
    //	ビームの太さ
    DBG_SCENE_FLOAT_ITEM_INPUT(in_DebugSceneHandle, "HomingSize", &gc_size, 16.f, 16.f, 30.f, 1.0f);
    DBG_SCENE_FLOAT_ITEM_INPUT(in_DebugSceneHandle, "Speed", &gc_speed, 10.f, 10.f, 30.f, 0.1f);
    DBG_SCENE_FLOAT_ITEM_INPUT(in_DebugSceneHandle, "TurnSpeed", &gc_turn_speed, 10.f, 0.f, 30.f,
                               0.1f);
    DBG_SCENE_FLOAT_ITEM_INPUT(in_DebugSceneHandle, "TurnLimig", &gc_turn_limit, 10.f, 0.f, 30.f,
                               0.1f);
}
