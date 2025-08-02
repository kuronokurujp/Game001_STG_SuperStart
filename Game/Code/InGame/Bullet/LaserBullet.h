/**
 *	@file 	D:/ProgramStady/Game/bom_panic/source/title/shot_sample/src/LaserBullet.h
 *	@brief	一本の太いレーザを右から発射
 *	@author	yuto uchida
 *	@data   2011-01-25
 *	@note
 *
 */
#ifndef __LASERBULLET_H__
#define __LASERBULLET_H__

#include "InterfaceBullet.h"
#include "common/Common.h"

class C_LaserBullet : public I_InterfaceBullet
{
public:
    C_LaserBullet();
    virtual ~C_LaserBullet();

    void init();
    void release();
    void update();
    void draw() const;

    /*
            @brief	打つ角度
            @param	角度指定
    */
    void setBulletAngle(float i_angle);

    /*
            @brief	弾を撃つ
            @param	i_spos	:	弾の初期座標
    */
    void shot(const D3DXVECTOR3& i_spos);

    /*
            @brief	交差判定
            @param	i_cpos		:	オブジェクトの中心座標
            @param	i_size_x	:	横サイズ
            @param	i_size_y	:	縦サイズ
            @return	衝突[true]	/	非衝突[false]
    */
    bool isIntersected(const D3DXVECTOR3& i_cpos, float i_size_x, float i_size_y);

private:
    // 始点の座標
    D3DXVECTOR3 m_pos;
    D3DXVECTOR3 m_dir;
    // レーザーの長さ
    float m_length;
    bool mb_shot;
};

#endif  // __LASERBULLET_H__
