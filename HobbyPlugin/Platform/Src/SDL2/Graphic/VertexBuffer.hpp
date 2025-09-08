#ifdef HE_USE_SDL2

#pragma once

#include <GL/glew.h>

#include "Engine/MiniEngine.h"

namespace Platform
{
    // xyzとuvの５つのfloat型データフォーマット
    class VertexBuffer
    {
        const unsigned int ItemMax = 8;

    public:
        VertexBuffer(const void* in_pVerts, const HE::Uint32 in_uByte)
        {
            // 頂点リストオブジェクトを作成して使用可能にする
            {
                glGenVertexArrays(1, &this->_uVertexArray);
            }

            // 頂点情報を作成
            this->Bind();
            {
                glGenBuffers(1, &this->_uVertexBuffer);
                // 頂点情報を格納するバッファ生成
                // GL_ARRAY_BUFFERで指定
                glBindBuffer(GL_ARRAY_BUFFER, this->_uVertexBuffer);

                // GenBufferで作成したデータ領域に書き込むサイズを計算
                glBufferData(GL_ARRAY_BUFFER, in_uByte, in_pVerts, GL_STATIC_DRAW);
            }
            this->UnBind();
        }

        ~VertexBuffer()
        {
            glDeleteBuffers(1, &this->_uVertexBuffer);
            glDeleteVertexArrays(1, &this->_uVertexArray);
        }

        void Bind() { glBindVertexArray(this->_uVertexArray); }
        void UnBind() { glBindVertexArray(0); }

        inline const Core::Common::Handle Handle() const
        {
            return Core::Common::Handle(this->_uVertexArray);
        }

    private:
        GLuint _uVertexBuffer;
        GLuint _uVertexArray;
    }
}  // namespace Platform
#endif
