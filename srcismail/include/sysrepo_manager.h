#ifndef SYSREPO_MANAGER_H
#define SYSREPO_MANAGER_H

#include <string>

using namespace std;

// Modül yönetimi fonksiyonları
void installModule(const string& modulePath);
void enableFeature(const string& moduleName, const string& featureName);
void disableFeature(const string& moduleName, const string& featureName);
void updateModule(const string& moduleName);
void deleteModule(const string& moduleName);
void listModuleFeatures(const string& moduleName);
void listAllModules();
void showModuleDetails(const string& moduleName);

// `sysrepocfg` ile edit işlemi fonksiyonu
void editConfig(const string& editFile, const string& datastore, const string& format, const string& module);
void exportConfig(const string& datastore, const string& moduleName);

#endif // SYSREPO_MANAGER_H
