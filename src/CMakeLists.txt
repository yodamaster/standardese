﻿# Copyright (C) 2016-2017 Jonathan Müller <jonathanmueller.dev@gmail.com>
# This file is subject to the license terms in the LICENSE file
# found in the top-level directory of this distribution.

set(detail_header
        ../include/standardese/detail/entity_container.hpp
        ../include/standardese/detail/parse_utils.hpp
        ../include/standardese/detail/raw_comment.hpp
        ../include/standardese/detail/scope_stack.hpp
        ../include/standardese/detail/sequence_stream.hpp
        ../include/standardese/detail/synopsis_utils.hpp
        ../include/standardese/detail/tokenizer.hpp
        ../include/standardese/detail/wrapper.hpp)
set(header
        ../include/standardese/comment.hpp
        ../include/standardese/config.hpp
        ../include/standardese/cpp_class.hpp
        ../include/standardese/cpp_cursor.hpp
        ../include/standardese/cpp_entity.hpp
        ../include/standardese/cpp_entity_blacklist.hpp
        ../include/standardese/cpp_entity_registry.hpp
        ../include/standardese/cpp_enum.hpp
        ../include/standardese/cpp_function.hpp
        ../include/standardese/cpp_namespace.hpp
        ../include/standardese/cpp_preprocessor.hpp
        ../include/standardese/cpp_template.hpp
        ../include/standardese/cpp_type.hpp
        ../include/standardese/cpp_variable.hpp
        ../include/standardese/doc_entity.hpp
        ../include/standardese/error.hpp
        ../include/standardese/generator.hpp
        ../include/standardese/index.hpp
        ../include/standardese/linker.hpp
        ../include/standardese/md_blocks.hpp
        ../include/standardese/md_custom.hpp
        ../include/standardese/md_entity.hpp
        ../include/standardese/md_inlines.hpp
        ../include/standardese/output.hpp
        ../include/standardese/output_format.hpp
        ../include/standardese/output_stream.hpp
        ../include/standardese/parser.hpp
        ../include/standardese/section.hpp
        ../include/standardese/string.hpp
        ../include/standardese/template_processor.hpp
        ../include/standardese/translation_unit.hpp)
set(src
        detail/parse_utils.cpp
        detail/raw_comment.cpp
        detail/scope_stack.cpp
        detail/synopsis_utils.cpp
        detail/tokenizer.cpp
        comment.cpp
        config.cpp
        cpp_class.cpp
        cpp_entity.cpp
        cpp_entity_blacklist.cpp
        cpp_enum.cpp
        cpp_function.cpp
        cpp_namespace.cpp
        cpp_preprocessor.cpp
        cpp_template.cpp
        cpp_type.cpp
        cpp_variable.cpp
        doc_entity.cpp
        error.cpp
        generator.cpp
        index.cpp
        linker.cpp
        md_blocks.cpp
        md_custom.cpp
        md_entity.cpp
        md_inlines.cpp
        output.cpp
        output_format.cpp
        output_stream.cpp
        parser.cpp
        template_processor.cpp
        translation_unit.cpp)

add_library(standardese ${detail_header} ${header} ${src})
comp_target_features(standardese PRIVATE CPP11)
target_include_directories(standardese PUBLIC
                                $<BUILD_INTERFACE:${STANDARDESE_SOURCE_DIR}/include>
                                $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>
                                $<BUILD_INTERFACE:${_standardese_comp_include}>
                                $<INSTALL_INTERFACE:${include_dest}>
                                $<INSTALL_INTERFACE:${include_dest}/comp>)
target_compile_definitions(standardese PUBLIC
                                STANDARDESE=1
                                STANDARDESE_VERSION_MAJOR=${STANDARDESE_VERSION_MAJOR}
                                STANDARDESE_VERSION_MINOR=${STANDARDESE_VERSION_MINOR}
                                LIBCLANG_SYSTEM_INCLUDE_DIR="${LIBCLANG_SYSTEM_INCLUDE_DIR}"
                                CLANG_BINARY="${CLANG_BINARY}")

# add threading support
find_package(Threads REQUIRED)
target_link_libraries(standardese PUBLIC Threads::Threads)

# link libclang
target_include_directories(standardese PUBLIC ${LIBCLANG_INCLUDE_DIR})
target_link_libraries(standardese PUBLIC ${LIBCLANG_LIBRARY})

# link cmark
target_link_libraries(standardese PUBLIC libcmark_static)

# link Boost
find_package(Boost COMPONENTS filesystem system thread date_time chrono REQUIRED)
target_include_directories(standardese PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(standardese PUBLIC ${Boost_LIBRARIES})

# use tiny-process-library
target_include_directories(standardese PRIVATE ${TINY_PROCESS_LIBRARY_INCLUDE_DIR})

# install library
install(TARGETS standardese EXPORT standardese DESTINATION "${lib_dest}")
install(FILES ${header} DESTINATION "${include_dest}/standardese")
install(FILES ${detail_header} DESTINATION "${include_dest}/standardese/detail")
