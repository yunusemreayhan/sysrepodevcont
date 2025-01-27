cmake_minimum_required(VERSION 3.10)

# Proje adını belirle
project(SysrepoProject)

# C++ 11 kullan
set(CMAKE_CXX_STANDARD 11)

# Sysrepo'nun bulunduğu dizini ekle
find_package(PkgConfig REQUIRED)
pkg_check_modules(SYSREPO REQUIRED sysrepo)

# Kaynak dosyasını ekle
add_executable(sysrepo_project main.cpp)

# Sysrepo'yu bağla
target_include_directories(sysrepo_project PRIVATE ${SYSREPO_INCLUDE_DIRS})
target_link_libraries(sysrepo_project PRIVATE ${SYSREPO_LIBRARIES})

# Sysrepo'nun derleme seçeneklerini ekle
target_compile_options(sysrepo_project PRIVATE ${SYSREPO_CFLAGS_OTHER})
