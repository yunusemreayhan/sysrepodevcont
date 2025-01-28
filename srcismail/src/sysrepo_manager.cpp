#include <iostream>
#include <cstdlib>
#include "sysrepo_manager.h"

using namespace std;

// Modül yükleme fonksiyonu
void installModule(const string& modulePath) {
    string command = "sysrepoctl -i " + modulePath;
    int result = system(command.c_str());
    if (result == -1) perror("Komut çalıştırılamadı");
}

// Özellik etkinleştirme fonksiyonu
void enableFeature(const string& moduleName, const string& featureName) {
    string command = "sysrepoctl --change " + moduleName + " --enable-feature " + featureName;
    int result = system(command.c_str());
    if (result == -1) perror("Komut çalıştırılamadı");
}

// Özellik devre dışı bırakma fonksiyonu
void disableFeature(const string& moduleName, const string& featureName) {
    string command = "sysrepoctl --change " + moduleName + " --disable-feature " + featureName;
    int result = system(command.c_str());
    if (result == -1) perror("Komut çalıştırılamadı");
}

// Modül güncelleme fonksiyonu
void updateModule(const string& moduleName) {
    string command = "sysrepoctl --update " + moduleName;
    int result = system(command.c_str());
    if (result == -1) perror("Komut çalıştırılamadı");
}

// Modül silme fonksiyonu
void deleteModule(const string& moduleName) {
    string command = "sysrepoctl -u " + moduleName;
    int result = system(command.c_str());
    if (result == -1) perror("Komut çalıştırılamadı");
}

// Modül özelliklerini listeleme fonksiyonu
void listModuleFeatures(const string& moduleName) {
    string command = "sysrepoctl --list | grep " + moduleName;
    int result = system(command.c_str());
    if (result == -1) perror("Komut çalıştırılamadı");
}

// Tüm modülleri listeleme fonksiyonu
void listAllModules() {
    string command = "sysrepoctl -l";
    int result = system(command.c_str());
    if (result == -1) perror("Komut çalıştırılamadı");
}

// Belirli bir modülü gösterme fonksiyonu
void showModuleDetails(const string& moduleName) {
    string command = "sysrepoctl --list | grep '^" + moduleName + "'";
    int result = system(command.c_str());
    if (result == -1) perror("Komut çalıştırılamadı");
}

// `sysrepocfg` ile edit işlemi yapma fonksiyonu
void editConfig(const string& editFile, const string& datastore, const string& format, const string& module) {
    string command = "sysrepocfg --edit=" + editFile + " --datastore=" + datastore + " --format=" + format + " --module=" + module;
    int result = system(command.c_str());
    if (result == -1) perror("sysrepocfg komutu çalıştırılamadı");
}

void exportConfig(const string& datastore, const string& moduleName) {
    string command = "sysrepocfg --export --datastore=" + datastore + " --module=" + moduleName;
    
    int result = system(command.c_str());
    if (result == -1) perror("sysrepocfg export komutu çalıştırılamadı");
}
