#ifdef HE_USE_SDL2

#pragma once

#include <GL/glew.h>

#include "Engine/MiniEngine.h"

namespace Platform
{
    /// <summary>
    /// インデックスバッファ
    /// </summary>
    class IndexBuffer
    {
    public:
        IndexBuffer(const void* in_pIndices, HE::Uint32 in_uByte)
        {
            // 頂点並びの添え字を作成

            // インデックスバッファ生成
            // GL_ELEMENT_ARRAY_BUFFERでインデックスバッファ専用のが作れる
            glGenBuffers(1, &this->_indexBuffer);
            this->Bind();
            {
                // インデックス情報に書き込むデータサイズ計算
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, in_uByte, in_pIndices, GL_STATIC_DRAW);
            }
            this->Unbind();
        }

        ~IndexBuffer() { glDeleteBuffers(1, &this->_indexBuffer); }

        inline const Core::Common::Handle Handle() const
        {
            return Core::Common::Handle(this->_indexBuffer);
        }

        void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_indexBuffer); }
        void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    private:
        GLuint _indexBuffer;
    }
}  // namespace Platform
#endif
