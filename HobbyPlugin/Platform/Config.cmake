set(PLUGIN_PLATFORM_NAME HobbyPlugin_Platform)
set(PLUGIN_PLATFORM_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/Inc)

set(PLUGIN_PLATFORM_TARGET_COMMON_FILES
    .editorconfig
    LICENSE.txt
    README.md
    ThirdPartyNotices.txt
)

set(PLUGIN_PLATFORM_TARGET_INC_FILES
    Inc/PlatformModule.h

    Inc/Platform/Interface/File.h
#    Inc/Platform/Interface/Font.h
    Inc/Platform/Interface/Windows.h
    Inc/Platform/Interface/Input.h
    Inc/Platform/Interface/System.h
    Inc/Platform/Interface/Time.h
    Inc/Platform/Windows/FrameBase.h
    Inc/Platform/Windows/FrameConfig.h
)

# SDL2プラットフォーム用
set(PLUGIN_PLATFORM_TARGET_INC_FILES

    Inc/Platform/Core/SDL2/File.h
#    Inc/Platform/Core/SDL2/Font.h
    Inc/Platform/Core/SDL2/Input.h
    Inc/Platform/Core/SDL2/Windows.h
    Inc/Platform/Core/SDL2/System.h
    Inc/Platform/Core/SDL2/Time.h
    Inc/Platform/Core/SDL2/Windows/Frame.h
)


set(PLUGIN_PLATFORM_TARGET_SRC_FILES
    Src/PlatformModule.cpp
    Src/Windows/FrameBase.cpp
    Src/Windows/FrameConfig.cpp
)

# SDL2プラットフォーム用
set(PLUGIN_PLATFORM_TARGET_SRC_FILES

    Src/SDL2/File.cpp
#    Src/SDL2/Font.cpp
    Src/SDL2/Input.cpp
    Src/SDL2/Graphic.cpp
    Src/SDL2/System.cpp
    Src/SDL2/Time.cpp

#    Src/SDL2/Graphic/GUIContext.cpp
    Src/SDL2/Windows/Frame.cpp
#    Src/SDL2/Graphic/Mesh.hpp
#    Src/SDL2/Graphic/Texture.hpp
#    Src/SDL2/Graphic/VertexBuffer.hpp
#    Src/SDL2/Graphic/IndexBuffer.hpp
)
# TODO: プラットフォーム(SDL2/Dx12など切り替え)
function(setup_sdl2)
    # SDL2のプラットフォームタイプをマクロ設定
    message(Platform Type: HE_USE_SDL2)
    add_compile_definitions(HE_USE_SDL2)
endfunction()

# includeと同時に実行
setup_sdl2()
