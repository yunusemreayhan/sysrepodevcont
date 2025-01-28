cmake_minimum_required(VERSION 3.10)
project(sysrepoismail)

# C++ standardını belirleyin
set(CMAKE_CXX_STANDARD 11)

# Kaynak dosyalarının tam yollarını ekleyin
set(SOURCES
    /root/sysrepo-pg/srcismail/src/main.cpp
    /root/sysrepo-pg/srcismail/src/sysrepo_manager.cpp
)

# Başlık dosyaları için tam yol belirtin
include_directories(/root/sysrepo-pg/srcismail/include)

# Yürütülebilir dosyayı oluştur
add_executable(${PROJECT_NAME} ${SOURCES})

# Gerekli kütüphaneleri bul ve bağla
target_include_directories(${PROJECT_NAME} PRIVATE ${SYSREPO_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SYSREPO_LIBRARIES})
