option(CPP_STARTER_BUILD_CONCEPTS "Enable compilation of Concepts examples" ON)

# Concepts
if(CPP_STARTER_BUILD_CONCEPTS)
  message("Concepts samples on")
  add_subdirectory(concepts)
endif()

# Generic test that uses conan libs
add_executable(intro main.cpp)
target_link_libraries(
  intro
  PRIVATE project_options
          project_warnings
          CONAN_PKG::docopt.cpp
          CONAN_PKG::fmt
          CONAN_PKG::spdlog)
