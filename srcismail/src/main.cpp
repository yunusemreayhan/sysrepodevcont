#include <iostream>
#include <string>
#include "sysrepo_manager.h"

void showMenu() {
    std::cout << "\nYapılacak işlemi seçiniz:\n";
    std::cout << "1. Modül Yükle (install)\n";
    std::cout << "2. Özellik Etkinleştir (enable)\n";
    std::cout << "3. Özellik Devre Dışı Bırak (disable)\n";
    std::cout << "4. Modül Güncelle (update)\n";
    std::cout << "5. Modül Kaldır (delete)\n";
    std::cout << "6. Tüm Modülleri Listele (list)\n";
    std::cout << "7. Belirli Bir Modülü Görüntüle (show)\n";
    std::cout << "0. Çıkış\n";
    std::cout << "Seçiminiz: ";
}

int main() {
    int operation;
    std::string moduleName;
    std::string featureName;

    while (true) {
        showMenu();
        std::cin >> operation;
        std::cin.ignore(); // Giriş tamponunu temizle

        try {
            switch (operation) {
                case 1:
                    std::cout << "YANG dosyasının yolunu giriniz: ";
                    std::getline(std::cin, featureName);
                    if (featureName.empty()) {
                        throw std::runtime_error("YANG dosyasının yolu boş bırakılamaz.");
                    }
                    installModule(featureName);
                    break;
                case 2:
                    std::cout << "Modül adını giriniz: ";
                    std::getline(std::cin, moduleName);
                    if (moduleName.empty()) {
                        throw std::runtime_error("Modül adı boş bırakılamaz.");
                    }
                    listModuleFeatures(moduleName);
                    std::cout << "Etkinleştirilecek özelliğin adını giriniz: ";
                    std::getline(std::cin, featureName);
                    if (featureName.empty()) {
                        throw std::runtime_error("Özellik adı boş bırakılamaz.");
                    }
                    enableFeature(moduleName, featureName);
                    break;
                case 3:
                    std::cout << "Modül adını giriniz: ";
                    std::getline(std::cin, moduleName);
                    if (moduleName.empty()) {
                        throw std::runtime_error("Modül adı boş bırakılamaz.");
                    }
                    listModuleFeatures(moduleName);
                    std::cout << "Devre dışı bırakılacak özelliğin adını giriniz: ";
                    std::getline(std::cin, featureName);
                    if (featureName.empty()) {
                        throw std::runtime_error("Özellik adı boş bırakılamaz.");
                    }
                    disableFeature(moduleName, featureName);
                    break;
                case 4:
                    std::cout << "Modül adını giriniz: ";
                    std::getline(std::cin, moduleName);
                    if (moduleName.empty()) {
                        throw std::runtime_error("Modül adı boş bırakılamaz.");
                    }
                    updateModule(moduleName);
                    break;
                case 5:
                    std::cout << "Modül adını giriniz: ";
                    std::getline(std::cin, moduleName);
                    if (moduleName.empty()) {
                        throw std::runtime_error("Modül adı boş bırakılamaz.");
                    }
                    deleteModule(moduleName);
                    break;
                case 6:
                    listAllModules();
                    break;
                case 7:
                    std::cout << "Görüntülemek istediğiniz modülün adını giriniz: ";
                    std::getline(std::cin, moduleName);
                    if (moduleName.empty()) {
                        throw std::runtime_error("Modül adı boş bırakılamaz.");
                    }
                    showModuleDetails(moduleName);
                    break;
                case 0:
                    std::cout << "Programdan çıkılıyor...\n";
                    return 0;
                default:
                    std::cout << "Geçersiz seçim: " << operation << std::endl;
                    break;
            }
        } catch (const std::exception& e) {
            std::cerr << "Hata: " << e.what() << "\nLütfen tekrar deneyin." << std::endl;
        }
    }

    return 0;
}
