#include <iostream>
#include <cstdlib>
#include "sysrepo_manager.h"

// Modül yükleme fonksiyonu
void installModule(const std::string& modulePath) {
    std::string command = "sysrepoctl -i " + modulePath;
    int result = std::system(command.c_str());
    if (result == -1) {
        std::perror("Komut çalıştırılamadı");
    }
}

// Özellik etkinleştirme fonksiyonu
void enableFeature(const std::string& moduleName, const std::string& featureName) {
    std::string command = "sysrepoctl --change " + moduleName + " --enable-feature " + featureName;
    int result = std::system(command.c_str());
    if (result == -1) {
        std::perror("Komut çalıştırılamadı");
    }
}

// Özellik devre dışı bırakma fonksiyonu
void disableFeature(const std::string& moduleName, const std::string& featureName) {
    std::string command = "sysrepoctl --change " + moduleName + " --disable-feature " + featureName;
    int result = std::system(command.c_str());
    if (result == -1) {
        std::perror("Komut çalıştırılamadı");
    }
}

// Modül güncelleme fonksiyonu
void updateModule(const std::string& moduleName) {
    std::string command = "sysrepoctl --update " + moduleName;
    int result = std::system(command.c_str());
    if (result == -1) {
        std::perror("Komut çalıştırılamadı");
    }
}

// Modül silme fonksiyonu
void deleteModule(const std::string& moduleName) {
    std::string command = "sysrepoctl -u " + moduleName;
    int result = std::system(command.c_str());
    if (result == -1) {
        std::perror("Komut çalıştırılamadı");
    }
}

// Modül özelliklerini listeleme fonksiyonu
void listModuleFeatures(const std::string& moduleName) {
    std::string command = "sysrepoctl --list | grep " + moduleName;
    int result = std::system(command.c_str());
    if (result == -1) {
        std::perror("Komut çalıştırılamadı");
    }
}

// Tüm modülleri listeleme fonksiyonu
void listAllModules() {
    std::string command = "sysrepoctl -l";
    int result = std::system(command.c_str());
    if (result == -1) {
        std::perror("Komut çalıştırılamadı");
    }
}
void showModuleDetails(const std::string& moduleName) {
    std::string command = "sysrepoctl --list | grep '^" + moduleName + "'";
    int result = std::system(command.c_str());
    if (result == -1) {
        std::perror("Komut çalıştırılamadı");
    }
}
