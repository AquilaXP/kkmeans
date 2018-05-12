cmake_minimum_required(VERSION 3.2)

set(PROJECT_VERSION_PATCH $ENV{TRAVIS_BUILD_NUMBER})

add_subdirectory( ./dlib )
project(kkmeans VERSION 0.0.${PROJECT_VERSION_PATCH})

configure_file(version.h.in version.h @ONLY)

set(SRC
    main.cpp
    )

set(HDR
    )

#program starry_sky
add_executable(starry_sky starry_sky.cpp )

set_target_properties( starry_sky PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wall
)

#program example_data
add_executable(example_data example_data.cpp)
target_link_libraries(example_data dlib::dlib)
target_include_directories(example_data PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${dlib_INCLUDE_DIR} )
target_link_libraries(example_data 
    ${dlib_LIBRARIES}    
)

set_target_properties( example_data PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wall
)

#program viewer_result
add_executable(viewer_result viewer_result.cpp optimal_visualize_size.h)
target_link_libraries(viewer_result dlib::dlib)
target_include_directories(viewer_result PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${dlib_INCLUDE_DIR} )
target_link_libraries(viewer_result 
    ${dlib_LIBRARIES}    
)

set_target_properties( viewer_result PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wall
)

#program kkmeans
add_executable(kkmeans ${SRC} ${HDR})
target_link_libraries(kkmeans dlib::dlib)
target_include_directories(kkmeans 
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties( kkmeans PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wall
)

target_link_libraries(kkmeans 
    dlib::dlib
)

if(UNIX)

set_target_properties( kkmeans PROPERTIES
    COMPILE_OPTIONS -pthread
    COMPILE_OPTIONS -X11
)
target_link_libraries( kkmeans pthread )

endif(UNIX)

add_custom_command(
    TARGET example_data
    COMMENT "Generate data"
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND $<TARGET_FILE:example_data>
    )
    
add_custom_command(
    TARGET starry_sky
    COMMENT "Generate data"
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND $<TARGET_FILE:starry_sky>
    )

install(TARGETS kkmeans RUNTIME DESTINATION bin)

INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/kkmeans_ex.txt DESTINATION /usr/bin )
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/starry_sky.txt DESTINATION /usr/bin )
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/make_img.py DESTINATION /usr/bin )

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT aquila-2004@yandex.ru)

include(CPack)
