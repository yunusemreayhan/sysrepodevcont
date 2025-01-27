#ifndef SYSREPO_MANAGER_H
#define SYSREPO_MANAGER_H

#include <string>

// Modül yükleme fonksiyonu
void installModule(const std::string& modulePath);

// Özellik etkinleştirme fonksiyonu
void enableFeature(const std::string& moduleName, const std::string& featureName);

// Özellik devre dışı bırakma fonksiyonu
void disableFeature(const std::string& moduleName, const std::string& featureName);

// Modül güncelleme fonksiyonu
void updateModule(const std::string& moduleName);

// Modül silme fonksiyonu
void deleteModule(const std::string& moduleName);

// Belirli bir modülün özelliklerini listeleme fonksiyonu
void listModuleFeatures(const std::string& moduleName);

// Sistemdeki tüm modülleri listeleme fonksiyonu
void listAllModules();

void showModuleDetails(const std::string& moduleName);

#endif // SYSREPO_MANAGER_H
