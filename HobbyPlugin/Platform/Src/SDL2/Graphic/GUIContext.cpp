// GUIContext.h

#ifdef HE_USE_SDL2

#include "Platform/Graphic/GUIContext.h "

#include "Engine/Common/CustomMap.h"

// 内部限定参照
#include "./IndexBuffer.hpp"
#include "./Mesh.hpp"
#include "./Texture.hpp"
#include "./VertexBuffer.hpp"

// パッケージ
#include "GL/glew.h"
#include "SDL2/SDL.h"

namespace Platform
{
    namespace Local
    {
        static Core::Common::FixedMap<HE::Uint32, Core::Memory::SharedPtr<TextureBase>, 128>
            s_mTextureMap;
        static Core::Common::FixedMap<HE::Uint32, Core::Memory::SharedPtr<VertexBuffer>, 128>
            s_mVertexBufferMap;
        static Core::Common::FixedMap<HE::Uint32, Core::Memory::SharedPtr<IndexBuffer>, 128>
            s_mIndexBufferMap;
        static Core::Common::FixedMap<HE::Uint32, Core::Memory::SharedPtr<Mesh>, 128>
            s_mMeshBufferMap;
        static HE::Uint32 s_uMeshIndex = 0;

    }  // namespace Local

    GUIContext::GUIContext(const InitDesc& in_rDesc)
    {
        this->_initDesc = in_rDesc;
    }

    GUIContext::~GUIContext()
    {
        for (auto it = Local::s_mIndexBufferMap.Begin(); it != Local::s_mIndexBufferMap.End(); ++it)
        {
            it->_data.reset();
        }
        Local::s_mIndexBufferMap.Clear();

        for (auto it = Local::s_mVertexBufferMap.Begin(); it != Local::s_mVertexBufferMap.End();
             ++it)
        {
            it->_data.reset();
        }
        Local::s_mVertexBufferMap.Clear();

        for (auto it = Local::s_mTextureMap.Begin(); it != Local::s_mTextureMap.End(); ++it)
        {
            it->_data.reset();
        }
        Local::s_mTextureMap.Clear();
    }

    void GUIContext::BeginFrame()
    {
        // カラーバッファをクリアする
        ::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GUIContext::EndFrame()
    {
    }

    void GUIContext::Present()
    {
        // ウィンドウの描画バッファを切り替える
        SDL_GL_SwapWindow(reinterpret_cast<SDL_Window*>(this->_initDesc.windowHandle));
    }

    TextureHandle GUIContext::CreateTexture(HE::Uint32 in_uWidth, HE::Uint32 in_uHeight,
                                            void* in_pPixels)
    {
        auto pTex = HE_MAKE_CUSTOM_SHARED_PTR((TextureSurface), GL_TEXTURE_2D, GL_TEXTURE0,
                                              in_pPixels, in_uWidth, in_uHeight);
        Local::s_mTextureMap.Add(pTex->Handle(), pTex);

        return TextureHandle{pTex->Handle()};
    }

    VertexBufferHandle GUIContext::CreateVertexBuffer(const HE::Uint32 in_uBytes,
                                                      const void* in_pData)
    {
        auto pVertexBuffer = HE_MAKE_CUSTOM_SHARED_PTR((VertexBuffer), in_pData, in_uBytes);

        Local::s_mVertexBufferMap.Add(pVertexBuffer->Handle(), pVertexBuffer);

        return VertexBufferHandle{pVertexBuffer->Handle()};
    }

    IndexBufferHandle GUIContext::CreateIndexBuffer(const HE::Uint32 in_uBytes,
                                                    const void* in_pData)
    {
        auto pBuffer = HE_MAKE_CUSTOM_SHARED_PTR((IndexBuffer), in_pData, in_uBytes);

        Local::s_mIndexBufferMap.Add(pBuffer->Handle(), pBuffer);

        return IndexBufferHandle{pBuffer->Handle()};
    }

/*
    MeshHandle GUIContext::CreateMesh(const VertexLayout in_layout,
                                      const VertexBufferHandle in_vertexHandle,
                                      const IndexBufferHandle in_indexHandle)
    {
        auto pIndexBuffer  = Local::s_mIndexBufferMap.FindKey(in_indexHandle.handle);
        auto pVertexBuffer = Local::s_mVertexBufferMap.FindKey(in_vertexHandle.handle);

        auto pMesh = HE_MAKE_CUSTOM_SHARED_PTR((Mesh), in_layout, pVertexBuffer, pIndexBuffer);

        Core::Common::Handle h;
        h.SetIndex(Local::s_uMeshIndex);
        ++Local::s_uMeshIndex;

        Local::s_mMeshBufferMap.Add(h, pMesh);

        return MeshHandle{h};
    }
    */

    PipelineHandle GUIContext::CreatePipeline(const PipelineDesc, const VertexLayout)
    {
        return PipelineHandle();
    }

    void GUIContext::Destroy(TextureHandle in_handle)
    {
        if (Local::s_mTextureMap.Contains(in_handle.handle))
        {
            Local::s_mTextureMap.FindKey(in_handle.handle)->_data.reset();
            Local::s_mTextureMap.Erase(in_handle.handle);
        }
    }

    void GUIContext::Destroy(VertexBufferHandle in_handle)
    {
        if (Local::s_mVertexBufferMap.Contains(in_handle.handle))
        {
            Local::s_mVertexBufferMap.FindKey(in_handle.handle)->_data.reset();
            Local::s_mVertexBufferMap.Erase(in_handle.handle);
        }
    }

    void GUIContext::Destroy(IndexBufferHandle in_handle)
    {
        if (Local::s_mIndexBufferMap.Contains(in_handle.handle))
        {
            Local::s_mIndexBufferMap.FindKey(in_handle.handle)->_data.reset();
            Local::s_mIndexBufferMap.Erase(in_handle.handle);
        }
    }

/*
    void GUIContext::Destroy(MeshHandle in_handle)
    {
        if (Local::s_mMeshBufferMap.Contains(in_handle.handle))
        {
            Local::s_mMeshBufferMap.FindKey(in_handle.handle)->_data.reset();
            Local::s_mMeshBufferMap.Erase(in_handle.handle);
        }
    }
    */

    void GUIContext::Destroy(PipelineHandle)
    {
    }

    void GUIContext::SetRenderTarget(RenderTargetHandle rt)
    {
    }

    void GUIContext::SetViewport(HE::Uint32 x, HE::Uint32 y, HE::Uint32 w, HE::Uint32 h)
    {
    }

    void GUIContext::SetScissor(HE::Uint32 x, HE::Uint32 y, HE::Uint32 w, HE::Uint32 h)
    {
    }

    void GUIContext::SetPipeline(PipelineHandle)
    {
    }

    void GUIContext::SetVertexBuffers(HE::Uint32 slot, VertexBufferHandle vb, HE::Uint32 offset)
    {
        auto pV = Local::s_mVertexBufferMap.FindKey(vb.handle)->_data;
        pV->Bind();
    }

    void GUIContext::SetIndexBuffer(IndexBufferHandle ib, HE::Uint32 offset, HE::Bool index16)
    {
        auto pV = Local::s_mIndexBufferMap.FindKey(ib.handle)->_data;
        pV->Bind();
    }

    void GUIContext::DrawIndexed(HE::Uint32 indexCount, HE::Uint32 startIndex,
                                 HE::Uint32 baseVertex)
    {
        ::glDrawElements(0, indexCount, GL_UNSIGNED_INT, nullptr);
    }

    void GUIContext::DrawVertexd(HE::Uint32 in_uVertexCount, HE::Uint32 in_bFirstVertex)
    {
        ::glDrawArrays(0, 0, in_uVertexCount);
    }

    void GUIContext::PushClipRect(HE::Float32 l, HE::Float32 t, HE::Float32 r, HE::Float32 b)
    {
    }

    void GUIContext::PopClipRect()
    {
    }

    FrameStats GUIContext::GetFrameStats() const
    {
        return FrameStats();
    }

}  // namespace Platform

#endif
