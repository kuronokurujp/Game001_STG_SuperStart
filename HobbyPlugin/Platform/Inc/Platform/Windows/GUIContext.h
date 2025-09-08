// GUIContext.h
#pragma once

#include "Engine/MiniEngine.h"
#include "Platform/Graphic/GUIVertex.h"

namespace Platform
{
    struct InitDesc
    {
        void* windowHandle         = nullptr;  // HWND, NSWindow*, etc.
        HE::Uint32 width           = 1280;
        HE::Uint32 height          = 720;
        HE::Bool enableDebug       = false;
        HE::Uint32 backBufferCount = 3;
    };

    struct PipelineDesc
    {
    };

    struct TextureHandle
    {
        Core::Common::Handle handle;
    };

    struct VertexBufferHandle
    {
        Core::Common::Handle handle;
    };

    struct IndexBufferHandle
    {
        Core::Common::Handle handle;
    };

    struct MeshHandle
    {
        Core::Common::Handle handle;
    };

    struct PipelineHandle
    {
        HE::Uint32 id;
    };

    struct RenderTargetHandle
    {
        HE::Uint32 id;
    };

    struct FrameStats
    {
        HE::Float32 cpuFrameMs = 0.0;
        HE::Float32 gpuFrameMs = 0.0;
        HE::Uint32 drawCalls   = 0;
        HE::Uint32 triangles   = 0;
    };

    /// <summary>
    /// GUIのコンテキスト
    /// 低レベルでの描画APIを提供
    /// </summary>
    class GUIContext
    {
        HE_CLASS_COPY_NG(GUIContext);

    public:
        GUIContext(const InitDesc&);
        ~GUIContext();

        // ---- frame ----------------------------------------------------------------
        void BeginFrame();
        void EndFrame();
        void Present();  // vsync は InitDesc で指定しても良い

        // ---- resource -------------------------------------------------------------
        TextureHandle CreateTexture(HE::Uint32 in_uWidth, HE::Uint32 in_uHeight, void* in_pPixels);
        VertexBufferHandle CreateVertexBuffer(const HE::Uint32 in_uBytes, const void* in_pData);
        IndexBufferHandle CreateIndexBuffer(const HE::Uint32 in_uBytes, const void* in_pData);
        /*

        MeshHandle CreateMesh(const VertexLayout, const VertexBufferHandle,
                              const IndexBufferHandle);
                              */

        PipelineHandle CreatePipeline(const PipelineDesc, const VertexLayout);
        void Destroy(TextureHandle);
        void Destroy(VertexBufferHandle);
        void Destroy(IndexBufferHandle);
        // void Destroy(MeshHandle);
        void Destroy(PipelineHandle);

        // ---- state ----------------------------------------------------------------
        void SetRenderTarget(RenderTargetHandle rt);
        void SetViewport(HE::Uint32 x, HE::Uint32 y, HE::Uint32 w, HE::Uint32 h);
        void SetScissor(HE::Uint32 x, HE::Uint32 y, HE::Uint32 w, HE::Uint32 h);
        void SetPipeline(PipelineHandle);

        // ----- bind -------------------------------------------------------------------
        void SetVertexBuffers(HE::Uint32 slot, VertexBufferHandle vb, HE::Uint32 offset = 0);

        void SetIndexBuffer(IndexBufferHandle ib, HE::Uint32 offset = 0, HE::Bool index16 = false);

        // ----- draw -------------------------------------------------------------------
        void DrawIndexed(HE::Uint32 indexCount, HE::Uint32 startIndex = 0,
                         HE::Uint32 baseVertex = 0);
        void DrawVertexd(HE::Uint32 in_uVertexCount, HE::Uint32 in_bFirstVertex = 0);

        /*
                void DrawInstanced(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex
           = 0, int32_t baseVertex = 0, uint32_t firstInstance = 0);
                                   */

        // ----- indirect ---------------------------------------------------------------
        // void DrawIndexedIndirect(BufferHandle argBuffer, uint64_t argOffset);

        // ---- utilities ------------------------------------------------------------
        void PushClipRect(HE::Float32 l, HE::Float32 t, HE::Float32 r, HE::Float32 b);
        void PopClipRect();

        // ---- info -----------------------------------------------------------------
        FrameStats GetFrameStats() const;

    private:
        InitDesc _initDesc;
    };
}  // namespace Platform
