cmake_minimum_required(VERSION 3.10)
project(Mat)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -pthread -mavx")

aux_source_directory(src DIR_SRC)

add_executable(${PROJECT_NAME} ${DIR_SRC})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)


