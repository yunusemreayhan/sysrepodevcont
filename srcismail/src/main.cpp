#include <iostream>
#include <string>
#include "sysrepo_manager.h"

using namespace std;

void showMenu() {
    cout << "\nYapılacak işlemi seçiniz:\n";
    cout << "1. Modül Yükle (install)\n";
    cout << "2. Özellik Etkinleştir (enable)\n";
    cout << "3. Özellik Devre Dışı Bırak (disable)\n";
    cout << "4. Modül Güncelle (update)\n";
    cout << "5. Modül Kaldır (delete)\n";
    cout << "6. Tüm Modülleri Listele (list)\n";
    cout << "7. Belirli Bir Modülü Görüntüle (show)\n";
    cout << "8. Yapılandırma Düzenle (sysrepocfg edit-config)\n";
    cout << "9. Yapılandırma Export Et (sysrepocfg export)\n"; 
    cout << "0. Çıkış\n";
    cout << "Seçiminiz: ";
}

int main() {
    int operation;
    string moduleName, featureName, editFile, datastore, format;

    while (true) {
        showMenu();
        cin >> operation;
        cin.ignore(); // Giriş tamponunu temizle

        try {
            switch (operation) {
                case 1:
                    cout << "YANG dosyasının yolunu giriniz: ";
                    getline(cin, featureName);
                    if (featureName.empty()) throw runtime_error("YANG dosyasının yolu boş bırakılamaz.");
                    installModule(featureName);
                    break;
                case 2:
                    cout << "Modül adını giriniz: ";
                    getline(cin, moduleName);
                    if (moduleName.empty()) throw runtime_error("Modül adı boş bırakılamaz.");
                    listModuleFeatures(moduleName);
                    cout << "Etkinleştirilecek özelliğin adını giriniz: ";
                    getline(cin, featureName);
                    if (featureName.empty()) throw runtime_error("Özellik adı boş bırakılamaz.");
                    enableFeature(moduleName, featureName);
                    break;
                case 3:
                    cout << "Modül adını giriniz: ";
                    getline(cin, moduleName);
                    if (moduleName.empty()) throw runtime_error("Modül adı boş bırakılamaz.");
                    listModuleFeatures(moduleName);
                    cout << "Devre dışı bırakılacak özelliğin adını giriniz: ";
                    getline(cin, featureName);
                    if (featureName.empty()) throw runtime_error("Özellik adı boş bırakılamaz.");
                    disableFeature(moduleName, featureName);
                    break;
                case 4:
                    cout << "Modül adını giriniz: ";
                    getline(cin, moduleName);
                    if (moduleName.empty()) throw runtime_error("Modül adı boş bırakılamaz.");
                    updateModule(moduleName);
                    break;
                case 5:
                    cout << "Modül adını giriniz: ";
                    getline(cin, moduleName);
                    if (moduleName.empty()) throw runtime_error("Modül adı boş bırakılamaz.");
                    deleteModule(moduleName);
                    break;
                case 6:
                    listAllModules();
                    break;
                case 7:
                    cout << "Görüntülemek istediğiniz modülün adını giriniz: ";
                    getline(cin, moduleName);
                    if (moduleName.empty()) throw runtime_error("Modül adı boş bırakılamaz.");
                    showModuleDetails(moduleName);
                    break;
                case 8:
                    cout << "Edit yapılacak dosyanın yolunu giriniz: ";
                    getline(cin, editFile);
                    if (editFile.empty()) throw runtime_error("Edit dosyası boş bırakılamaz.");
                    cout << "Datastore seçin (running/candidate/startup): ";
                    getline(cin, datastore);
                    if (datastore.empty()) throw runtime_error("Datastore boş bırakılamaz.");
                    cout << "Format seçin (xml/json): ";
                    getline(cin, format);
                    if (format.empty()) throw runtime_error("Format boş bırakılamaz.");
                    cout << "Modül adını giriniz: ";
                    getline(cin, moduleName);
                    if (moduleName.empty()) throw runtime_error("Modül adı boş bırakılamaz.");
                    editConfig(editFile, datastore, format, moduleName);
                    break;
                
               case 9: // **Yeni eklenen export işlemi**
                    cout << "Export edilecek datastore'u seçin (running/candidate/startup): ";
                    getline(cin, datastore);
                    if (datastore.empty()) throw runtime_error("Datastore boş bırakılamaz.");
                    
                    cout << "Export edilecek modül adını giriniz: ";
                    getline(cin, moduleName);
                    if (moduleName.empty()) throw runtime_error("Modül adı boş bırakılamaz.");

                    // Export işlemi başlat
                    exportConfig(datastore, moduleName);
                    
                    cout << "Export işlemi tamamlandı!" << endl;
                    break;

                case 0:
                    cout << "Programdan çıkılıyor...\n";
                    return 0;
                default:
                    cout << "Geçersiz seçim: " << operation << endl;
                    break;
            }
        } catch (const exception& e) {
            cerr << "Hata: " << e.what() << "\nLütfen tekrar deneyin." << endl;
        }
    }

    return 0;
}
