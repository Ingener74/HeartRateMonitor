cmake_minimum_required(VERSION 2.8)

include(ExternalProject)

set(EXT_BOOST ext_boost)
set(EXT_BOOST_VERSION "1.55.0" CACHE STRING "Boost-for-Android version")
set(EXT_BOOST_BINDIR
    ${CMAKE_BINARY_DIR}/3rdparty/boost/${EXT_BOOST}-prefix/src/${EXT_BOOST})

# message(STATUS dst = ${3RDPARTY_INSTALL})

if(ANDROID)
    ExternalProject_Add(
        ${EXT_BOOST}
        GIT_REPOSITORY https://github.com/MysticTreeGames/Boost-for-Android.git
        CONFIGURE_COMMAND ""
        BUILD_COMMAND bash ${EXT_BOOST_BINDIR}/build-android.sh ${ANDROID_NDK} --boost=${EXT_BOOST_VERSION}
        BINARY_DIR ${EXT_BOOST_BINDIR}
        INSTALL_COMMAND cp -R ${EXT_BOOST_BINDIR}/build/include/ ${3RDPARTY_INSTALL} &&
            cp -R ${EXT_BOOST_BINDIR}/build/lib/ ${3RDPARTY_INSTALL}
        )
else()
endif()

set_target_properties(${EXT_BOOST} PROPERTIES EXCLUDE_FROM_ALL "TRUE")
