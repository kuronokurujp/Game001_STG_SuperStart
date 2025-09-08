set(PLUGIN_RHI_NAME HobbyPlugin_RHI)
set(PLUGIN_RHI_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/Inc)
# プロジェクトに登録するファイル群
# ここに全て記載する
set(PLUGIN_RHI_TARGET_COMMON_FILES
    .editorconfig
    LICENSE.txt
    README.md
)
set(PLUGIN_RHI_TARGET_INC_FILES
    Inc/RHIModule.h
)
set(PLUGIN_RHI_TARGET_SRC_FILES
    Src/RHIModule.cpp
)
