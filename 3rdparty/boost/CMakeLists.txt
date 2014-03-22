cmake_minimum_required(VERSION 2.8)

set(EXT_BOOST ext_boost)
set(EXT_BOOST_VERSION "1.55.0" CACHE STRING "Boost-for-Android version")
set(EXT_BOOST_SRCDIR
    ${CMAKE_BINARY_DIR}/3rdparty/boost/${EXT_BOOST}-prefix/src/${EXT_BOOST})

if(ANDROID)
    ExternalProject_Add(
        ${EXT_BOOST}
        # GIT_REPOSITORY https://github.com/MysticTreeGames/Boost-for-Android.git
        URL ${CMAKE_CURRENT_LIST_DIR}/Boost-for-Android-master.zip
        CONFIGURE_COMMAND ""
        BUILD_COMMAND bash ${EXT_BOOST_SRCDIR}/build-android.sh ${ANDROID_NDK} --boost=${EXT_BOOST_VERSION}
        BINARY_DIR ${EXT_BOOST_SRCDIR}
        INSTALL_COMMAND 
            cp -R ${EXT_BOOST_SRCDIR}/build/include/boost-1_55/boost ${3RDPARTY_INSTALL}/include &&
            cp -R ${EXT_BOOST_SRCDIR}/build/lib/ ${3RDPARTY_INSTALL}
        )
    set_target_properties(${EXT_BOOST} PROPERTIES EXCLUDE_FROM_ALL "TRUE")
endif()

