#pragma once

#include "Engine/MiniEngine.h"

namespace Platform
{
    enum EVertexAttributeType
    {
        Float,
        Float2,
        Float3,
        Float4,
        UInt32,
        UInt16,
        UInt8,
        SInt32,
        SInt16,
        SInt8,
    };

    struct VertexAttribute
    {
        HE::UTF8* szName;           // 属性名
        EVertexAttributeType type;  // 属性の型
        HE::Uint32 uOffset;         // バッファ内のオフセット
    };

    struct VertexLayout
    {
        template <size_t N>
        VertexLayout(const std::array<VertexAttribute, N>& a, uint32_t s)
            : attrs(a.begin(), a.end()), stride(s)
        {
        }

        std::vector<VertexAttribute> attrs;
        uint32_t stride;
    };

}  // namespace Platform
