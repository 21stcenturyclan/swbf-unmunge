project(SWBF-unmunge)


#
# CMake
#

cmake_minimum_required(VERSION 3.9)

#
# Conan
#

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#
# C++
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#
# Paths
#

include_directories(src)


#
# Libraries
#

find_package(fmt)
find_package(GSL)
find_package(glm)
find_package(nlohmann_json)


set(LIBRARIES)  # add linker options here

#
# Includes
#

SET(FILES
        src/fx/gltf.h
        src/app_options.cpp
        src/app_options.hpp
        src/assemble_chunks.cpp
        src/assemble_chunks.hpp
        src/bit_flags.hpp
        src/chunk_handlers.hpp
        src/chunk_processor.cpp
        src/chunk_processor.hpp
        src/DDS.h
        src/explode_chunk.cpp
        src/explode_chunk.hpp
        src/file_saver.cpp
        src/file_saver.hpp
        src/handle_cloth.cpp
        src/handle_collision.cpp
        src/handle_config.cpp
        src/handle_localization.cpp
        src/handle_lvl_child.cpp
        src/handle_misc.cpp
        src/handle_model.cpp
        src/handle_object.cpp
        src/handle_path.cpp
        src/handle_planning.cpp
        src/handle_planning_swbf1.cpp
        src/handle_primitives.cpp
        src/handle_skeleton.cpp
        src/handle_terrain.cpp
        src/handle_texture.cpp
        src/handle_texture_ps2.cpp
        src/handle_texture_xbox.cpp
        src/handle_ucfb.cpp
        src/handle_unknown.cpp
        src/handle_world.cpp
        src/magic_number.hpp
        src/mapped_file.cpp
        src/mapped_file.hpp
        src/math_helpers.hpp
        src/model_basic_primitives.hpp
        src/model_builder.cpp
        src/model_builder.hpp
        src/model_gltf_save.cpp
        src/model_gltf_save.hpp
        src/model_msh_save.cpp
        src/model_msh_save.hpp
        src/model_scene.cpp
        src/model_scene.hpp
        src/model_topology_converter.cpp
        src/model_topology_converter.hpp
        src/save_image.cpp
        src/save_image.hpp
        src/save_image_tga.cpp
        src/save_image_tga.hpp
        src/string_helpers.hpp
        src/swbf_fnv_hashes.cpp
        src/swbf_fnv_hashes.hpp
        src/synced_cout.hpp
        src/terrain_builder.cpp
        src/terrain_builder.hpp
        src/type_pun.hpp
        src/ucfb_builder.cpp
        src/ucfb_builder.hpp
        src/ucfb_reader.cpp
        src/ucfb_reader.hpp
        src/ucfb_writer.hpp
        src/vbuf_reader.cpp
        src/vbuf_reader.hpp
        )

#
# Builds
#

add_executable(${PROJECT_NAME} ${FILES} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt fmt::fmt-header-only)
target_link_libraries(${PROJECT_NAME} PRIVATE GSL::gsl GSL::gslcblas)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)