cmake_minimum_required(VERSION 3.16)
project(auv_bringup)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(gz-sim8 REQUIRED)
find_package(gz-plugin2 REQUIRED COMPONENTS register)

add_library(SauvcFlareRecovery SHARED src/FlareRecovery.cc)
target_compile_features(SauvcFlareRecovery PUBLIC cxx_std_17)
target_include_directories(SauvcFlareRecovery PRIVATE include)
target_link_libraries(SauvcFlareRecovery PRIVATE gz-sim8::gz-sim8 gz-plugin2::gz-plugin2)

install(TARGETS SauvcFlareRecovery LIBRARY DESTINATION lib)

install(
  DIRECTORY launch config worlds
  DESTINATION share/${PROJECT_NAME}/
)

install(PROGRAMS scripts/generate_sauvc.py DESTINATION share/${PROJECT_NAME}/scripts)

ament_package()
