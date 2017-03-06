if( NOT TARGET CoC-Scene )
    get_filename_component( COC-SCENE_SOURCE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../src" ABSOLUTE )

    FILE(GLOB_RECURSE COC-SCENE_SOURCES ${COC-SCENE_SOURCE_PATH}/*.cpp)

    add_library( CoC-Scene ${COC-SCENE_SOURCES} )
    target_include_directories( CoC-Scene PUBLIC
            "${COC-SCENE_SOURCE_PATH}"
            "${COC-SCENE_SOURCE_PATH}/graph"
            "${COC-SCENE_SOURCE_PATH}/loader" )

    # If Cinder included from this block:

    target_include_directories( CoC-Scene SYSTEM BEFORE PUBLIC "${CINDER_PATH}/include" )

    if( NOT TARGET cinder )
        include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
        find_package( cinder REQUIRED PATHS
                "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
                "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
    endif()

    # Add CoC-Core block as a dependency
    get_filename_component( COC-CORE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../CoC-Core/proj/cmake" ABSOLUTE )
    find_package( CoC-Core REQUIRED PATHS "${COC-CORE_MODULE_PATH}" )
    if (CoC-Core_FOUND)
        add_dependencies( CoC-Scene CoC-Core )
        target_link_libraries( CoC-Scene PUBLIC CoC-Core)
    endif()

    # Add CoC-Assets block as a dependency
    get_filename_component( COC-ASSETS_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../CoC-Assets/proj/cmake" ABSOLUTE )
    find_package( CoC-Assets REQUIRED PATHS "${COC-ASSETS_MODULE_PATH}" )
    if (CoC-Assets_FOUND)
        add_dependencies( CoC-Scene CoC-Assets )
        target_link_libraries( CoC-Scene PUBLIC CoC-Assets)
    endif()

    target_link_libraries( CoC-Scene PRIVATE cinder)

endif()