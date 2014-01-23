cmake_minimum_required(VERSION 2.8)

set(EXT_GTEST ext_gtest)
set(EXT_GTEST_BINDIR 
    ${CMAKE_BINARY_DIR}/3rdparty/gtest/${EXT_GTEST}-prefix/src/${EXT_GTEST}-build)
set(EXT_GTEST_SRCDIR 
    ${CMAKE_BINARY_DIR}/3rdparty/gtest/${EXT_GTEST}-prefix/src/${EXT_GTEST})

if(ANDROID)
else()
    ExternalProject_Add(
        ${EXT_GTEST}
        URL ${CMAKE_CURRENT_LIST_DIR}/gtest-1.7.0.zip
        INSTALL_COMMAND 
            # ls ${EXT_GTEST_BINDIR}/lib* && 
            cp ${EXT_GTEST_BINDIR}/libgtest.a ${3RDPARTY_INSTALL}/lib/ && 
            cp ${EXT_GTEST_BINDIR}/libgtest_main.a ${3RDPARTY_INSTALL}/lib/ && 
            cp -R ${EXT_GTEST_SRCDIR}/include/ ${3RDPARTY_INSTALL}
        )
endif()

