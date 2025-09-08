// SDL2プラットフォームの機能
#ifdef HE_USE_SDL2

#include "Platform/Core/SDL2/System.h"

#include <time.h>

#include <random>

// SDL2のヘッダーファイル
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

namespace Platform::SDL2
{
    namespace Local
    {
        static std::mt19937 rng;

#ifdef HE_ENGINE_DEBUG
        /// <summary>
        /// OpenGLのバグが起きた時のメッセージ
        /// </summary>
        void GLAPIENTRY _ShowMessageFromGLError(GLenum in_source, GLenum in_type, GLuint in_id,
                                                GLenum in_severity, GLsizei in_length,
                                                const GLchar* in_pMessage,
                                                const void* in_pUserParam)
        {
            HE_LOG_LINE(HE_STR_TEXT("OpenGL Debug Message: %s"), in_pMessage);
        }
#endif

    }  // namespace Local

    System::System()
    {
        // SDLの初期化
        // 初期化にも色々な種類があるが、いったんVideoのみで
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        {
            HE_LOG_LINE(HE_STR_TEXT("Error: SDL_Init Message= %s"), SDL_GetError());
            HE_ASSERT_RETURN(FALSE && "SDLの初期化に失敗");
        }

        // SDLのフォント初期化
        if (TTF_Init() == -1)
        {
            HE_LOG_LINE(HE_STR_TEXT("Error: TTF_Init Message= %s"), TTF_GetError());

            SDL_Quit();
            HE_ASSERT_RETURN(FALSE && "SDL2_TTFの初期化失敗");
        }

        // openglの属性設定をする
        // windowを作成する前にしないといけない
        {
            // コア機能を有効にする
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            // コンテキストのバージョン設定
            // OpenGL3.3を使用
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

            // RGBAそれぞれに割り当てるビットサイズ指定
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
            // デプスバッファのビット数を設定
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

            // 描画のダブルバッファリングを有効にする
            // これで描画くずれが防げる
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            // 描画計算をGPU任せにする(0ならCPU任せになる)
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        }

        // ウィンドウズのWinAPIを使えるようにする
#ifdef HE_WIN
        SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
#endif

        {
#ifdef HE_ENGINE_DEBUG
            const GLubyte* pVersion = ::glGetString(GL_VERSION);
            HE_LOG_LINE(HE_STR_TEXT("OpenGL Version(%d)"), *pVersion);

            GLint maxTextureSize;
            ::glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);
            HE_LOG_LINE(HE_STR_TEXT("Max texture size: %d"), maxTextureSize);

            // テクスチャユニット数
            GLint textureUnits = 0;
            ::glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnits);
            HE_LOG_LINE(HE_STR_TEXT("GPU TextureUnitNum %d"), textureUnits);

#endif
        }

        {
#ifdef HE_ENGINE_DEBUG
            ::glEnable(GL_DEBUG_OUTPUT);
            ::glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(Local::_ShowMessageFromGLError, NULL);
#endif
        }
    }

    System::~System()
    {
        ::TTF_Quit();
        ::SDL_Quit();
    }

    HE::Uint32 System::VGetRand(const HE::Uint32 in_uMax)
    {
        // 0からin_uMax間の値を取得
        return static_cast<HE::Uint32>(rand() % (in_uMax + 1));
    }

    HE::Bool System::VSetSeedRand(const HE::Uint32 in_uVal)
    {
        // 乱数の種を初期化
        srand(static_cast<unsigned int>(in_uVal));

        return TRUE;
    }

    HE::Float32 System::VGetRandByFloat(const HE::Float32 in_fMin, const HE::Float32 in_fMax)
    {
        // 一様実数分布
        std::uniform_real_distribution uniform(in_fMin, in_fMax);
        return uniform(Local::rng);
    }

    HE::Bool System::VSetSeedRandByFloat()
    {
        Local::rng = std::mt19937(::SDL_GetTicks());
        return TRUE;
    }

}  // namespace Platform::SDL2
#endif
