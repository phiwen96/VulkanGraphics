
cmake_minimum_required(VERSION  3.17.1)
project(Hej)
 include(cmake/CPM.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_BUILD_TYPE Release)
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)



# cmake -GNinja .. . -G "Xcode" && open Hej.xcodeproj


# include(FetchContent)

# FetchContent_Declare(json
#   GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
#   INSTALL_COMMAND ""
#   GIT_TAG v3.9.1)

# FetchContent_GetProperties(json)
# if(NOT json_POPULATED)
#   FetchContent_Populate(json)
#   add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
# endif()






FetchContent_Declare(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  INSTALL_COMMAND ""
  )

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
  FetchContent_Populate(glfw)
  add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()







FetchContent_Declare(glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  INSTALL_COMMAND ""
  )

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
  FetchContent_Populate(glm)
  add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()




# include(ExternalProject)



# CPMAddPackage(
#     NAME matplotplusplus
#     GITHUB_REPOSITORY alandefreitas/matplotplusplus
#     GIT_TAG origin/master # or whatever tag you want
# )




# FetchContent_Declare(
#   simdjson
#   GIT_REPOSITORY https://github.com/simdjson/simdjson.git
#   INSTALL_COMMAND ""
#   GIT_TAG  v0.5.0
#   GIT_SHALLOW TRUE)

# set(SIMDJSON_JUST_LIBRARY ON CACHE INTERNAL "")
# set(SIMDJSON_BUILD_STATIC ON CACHE INTERNAL "")

# FetchContent_Populate(simdjson)



# find_package(Vuh)



  



set(MY_LIBRARIES_DIR
    libs
)

set(MY_LIBRARIES
common
data_structures
algorithms
)







find_package(Vulkan REQUIRED)




foreach(LIBRARY ${MY_LIBRARIES})
    add_subdirectory("${MY_LIBRARIES_DIR}/${LIBRARY}")
endforeach(LIBRARY)












file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.hpp pch.pch)






add_executable(${PROJECT_NAME}
${HEADERS}
${SOURCES}
)




target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)


target_precompile_headers(${PROJECT_NAME} PUBLIC pch.pch)




add_subdirectory(externalLibraries/constexpr-master)

target_link_libraries(${PROJECT_NAME} 
 PUBLIC 
  common
  algorithms
 
   ${Vulkan_LIBRARIES}
 
  # matplot
  glfw
  glm
 
  # nlohmann_json::nlohmann_json
 
  # ${MPI_CXX_LIBRARIES}
  # ${Vuh_LIBRARIES}
  # ${Simdjson_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  common
  algorithms
  # matplot

  include

  ${Vulkan_INCLUDE_DIR}

  glfw
  glm
)

#vuh_compile_shader(example_shader
#   SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/data/example.comp
#   TARGET ${CMAKE_CURRENT_BINARY_DIR}/example.spv
#)
#add_dependencies(${PROJECT_NAME} example_shader)



