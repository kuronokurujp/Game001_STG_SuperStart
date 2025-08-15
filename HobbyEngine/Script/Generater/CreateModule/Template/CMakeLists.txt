cmake_minimum_required(VERSION 3.26)

# プロジェクトの共通処理
include(${CMAKE_SOURCE_DIR}/HobbyEngine/cmake/Project.cmake NO_POLICY_SCOPE)
# エンジン設定
include(${CMAKE_SOURCE_DIR}/HobbyEngine/Config.cmake NO_POLICY_SCOPE)
# プラグインビルドの共通処理
include(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake NO_POLICY_SCOPE)

message("build ${PLUGIN___MODULE_UPPER_NAME___NAME} plugin lib!")

# 静的ライブラリの設定
project_configure_static_lib_target(${PLUGIN___MODULE_UPPER_NAME___NAME})

# プロジェクトの設定
project_configure_target(${PLUGIN___MODULE_UPPER_NAME___NAME})

# ターゲットへファイル群の設定
project_configure_files_target(${PLUGIN___MODULE_UPPER_NAME___NAME}
    ${PLUGIN___MODULE_UPPER_NAME___TARGET_COMMON_FILES}
    ${PLUGIN___MODULE_UPPER_NAME___TARGET_SRC_FILES}
    ${PLUGIN___MODULE_UPPER_NAME___TARGET_INC_FILES}
)

# エンジンのインクルードパス
target_include_directories(${PLUGIN___MODULE_UPPER_NAME___NAME} PUBLIC ${ENGINE_INC_DIR})

# プロジェクトが参照できるインクルードディレクトリのパス
target_include_directories(${PLUGIN___MODULE_UPPER_NAME___NAME} PUBLIC ${PLUGIN___MODULE_UPPER_NAME___INC_DIR})

# 依存ライブラリのリンク
target_link_libraries(${PLUGIN___MODULE_UPPER_NAME___NAME}
    PUBLIC
        ${ENGINE_NAME}
)

# テスト用サブディレクトリを追加
add_subdirectory(Test)
