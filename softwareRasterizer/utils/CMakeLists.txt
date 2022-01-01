set(TARGET utils)
add_library(${TARGET} STATIC
            src/Eigen3DUtil.cpp
            )

target_include_directories(${TARGET}
        PUBLIC
        include
        )