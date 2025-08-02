# 初回設定
function(vcpkg_configuration)

	message("configuration vcpkg")

	# --- vcpkg ルートを決定 -------------------------------------------------

	if (EXISTS "${CMAKE_SOURCE_DIR}/ThirdParty/vcpkg")
		# TODO:参照パス先が分かるので何か対策が必要かも
		set(VCPKG_ROOT "${CMAKE_SOURCE_DIR}/ThirdParty/vcpkg" PARENT_SCOPE)
	elseif(DEFINED ENV{VCPKG_ROOT} AND NOT "$ENV{VCPKG_ROOT}" STREQUAL "")
		# 環境変数がセットされていればそれを優先
		set(VCPKG_ROOT "$ENV{VCPKG_ROOT}" CACHE PATH "Path to vcpkg root" PARENT_SCOPE)
	endif()

	# 環境変数からvcpkgのパスを取得してツールチェインを設定
	set(TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

	# OS に応じて vcpkg 実行ファイル名を出し分け
	if (WIN32)
		set(VCPKG_COMMAND "${VCPKG_ROOT}/vcpkg.exe" PARENT_SCOPE)
	else()
		set(VCPKG_COMMAND "${VCPKG_ROOT}/vcpkg" PARENT_SCOPE)
	endif()
endfunction()

# VCPKGのライブラリをインストール
function(vcpkg_install_package install_dir vcpkg_triplet)

	message("install vcpkg")
	message(STATUS "Using vcpkg command: ${VCPKG_COMMAND}")

	# すでにvcpkgがインストール済みかどうかチェック
	# statusファイルのパス
	# vcpkg.jsonで記述したパッケージは全てインストールしているという前提でのチェック
	# 特定のパッケージだけoptionalにした場合はチェック方法が変わるので注意
	#set(STATUS_FILE "${install_dir}/ThirdParty/VcPkg/vcpkg/status")
	execute_process(
		COMMAND ${VCPKG_COMMAND} list --x-json
		OUTPUT_VARIABLE _pkgs
	)
	string(JSON _dummy ERROR_VARIABLE _err LIST LENGTH _pkgs)
	if(NOT _err STREQUAL "")
		message(STATUS "vcpkgパッケージはすでにインストールされています。")
		return()
	endif()
	# statusファイルの存在を確認
	#if(EXISTS "${STATUS_FILE}")
	#	message(STATUS "vcpkgパッケージはすでにインストールされています。")
	#	return()
	#endif()

	# 一旦vcpkg関連のファイルを削除
	# これはvcpkgを入れなおしたら環境再構築するため
	if(EXISTS ${install_dir}/vcpkg-configuration.json)
		file(REMOVE ${install_dir}/vcpkg-configuration.json)
	endif()

	if(EXISTS ${install_dir}/vcpkg.json)
		file(REMOVE ${install_dir}/vcpkg.json)
	endif()

	# プラグインが用意した.vcpkg.jsonがあればvcpkg管理のライブラリをインストールする
	if(EXISTS ${install_dir}/.vcpkg.json)
		file(SIZE ${install_dir}/.vcpkg.json VCPKG_FILE_SIZE)
		if (VCPKG_FILE_SIZE GREATER 0)
			# vcpkgの環境を構築
			execute_process(
				COMMAND cmd /c "${VCPKG_COMMAND}" "--vcpkg-root=${VCPKG_ROOT}" new --application
				WORKING_DIRECTORY ${install_dir}
				OUTPUT_VARIABLE CMD_OUTPUT
				ERROR_VARIABLE CMD_ERROR
				RESULT_VARIABLE CMD_RESULT
			)

			# プラグインが用意した.vcpkg.jsonをvcpkg.jsonにコピー
			configure_file(${install_dir}/.vcpkg.json ${install_dir}/vcpkg.json COPYONLY)

			execute_process(
				COMMAND cmd /c "${VCPKG_COMMAND}" "--vcpkg-root=${VCPKG_ROOT}" install --clean-after-build "--x-manifest-root=${install_dir}" "--x-install-root=${install_dir}/ThirdParty/VcPkg" "--triplet=${vcpkg_triplet}"
				WORKING_DIRECTORY ${install_dir}
				OUTPUT_VARIABLE CMD_OUTPUT
				ERROR_VARIABLE CMD_ERROR
				RESULT_VARIABLE CMD_RESULT
			)

			message(STATUS "Command Output: ${CMD_OUTPUT}")
			message(STATUS "Command Error: ${CMD_ERROR}")
			message(STATUS "Command Result: ${CMD_RESULT}")

		endif()
	else()
		message(STATUS ".vcpkg.jsonファイルがありません。")
	endif()

endfunction()

# includeで取り込んで初回実行
vcpkg_configuration()

