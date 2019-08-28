cmake_minimum_required(VERSION 3.14)
project(ProtoTest)

set(CMAKE_CXX_STANDARD 14)

file(GLOB proto_files "${PROJECT_SOURCE_DIR}/proto/*.proto")

set(proto_gen_cpp_dir ${PROJECT_SOURCE_DIR}/proto)

if(NOT EXISTS ${proto_gen_cpp_dir})
    file(MAKE_DIRECTORY ${proto_dir})
else()
    message(STATUS "proto_gen_cpp dir is existing")
endif()

# Create lists of files to be generated.
set(proto_gen_cpp_files "")

foreach(proto_file ${proto_files})
    get_filename_component(proto_name ${proto_file} NAME_WE)
    list(APPEND proto_gen_cpp_files ${proto_gen_cpp_dir}/${proto_name}.pb.cc)
    list(APPEND proto_gen_cpp_files ${proto_gen_cpp_dir}/${proto_name}.pb.h)

endforeach(proto_file ${proto_files})

message(STATUS "Generated proto files: ${proto_gen_cpp_files}")

add_custom_command(
        OUTPUT ${proto_gen_cpp_files}
        COMMAND protoc -I=${PROJECT_SOURCE_DIR}/proto --cpp_out=${proto_gen_cpp_dir}  ${proto_files}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${proto_files}

)

set_source_files_properties(${proto_gen_cpp_files} PROPERTIES GENERATED TRUE)

add_executable(ProtoTest main.cpp ${proto_gen_cpp_files})
