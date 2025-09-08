#ifdef HE_USE_SDL2

#pragma once

#include "Platform/Graphic/GUIVertex.h"

// 内部参照
#include "./IndexBuffer.hpp"
#include "./VertexBuffer.hpp"
#include "GL/glew.h"
#include "SDL2/SDL.h"

namespace Platform
{
    class Mesh
    {
    public:
        Mesh(const VertexLayout in_layout, Core::Memory::SharedPtr<VertexBuffer> in_pVer,
             Core::Memory::SharedPtr<IndexBuffer> in_pIndex)
            : _layout(in_layout)
        {
            this->_pVer   = in_pVer;
            this->_pIndex = in_pIndex;
        }

        void DrawByVertexOnly(const HE::Uint32 in_uMode, const HE::Uint32 in_uVertCount)
        {
            this->_pVer->Bind();


            this->_pVer->UnBind();
        }

        void Draw(const HE::Uint32 in_uMode, const HE::Uint32 in_uIndex)
        {
            this->_pVer->Bind();
            this->_pIndex->Bind();

            //::glDrawElements(in_uMode, in_uIndex, GL_UNSIGNED_INT, nullptr);

            this->_pIndex->Unbind();
            this->_pVer->UnBind();
        }

    private:
        Core::Memory::SharedPtr<VertexBuffer> _pVer;
        Core::Memory::SharedPtr<IndexBuffer> _pIndex;
        VertexLayout _layout;
    }
}  // namespace Platform
#endif
