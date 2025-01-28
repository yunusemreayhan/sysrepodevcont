#!/bin/bash

SYSREPOCTL="/usr/bin/sysrepoctl"
SYSREPOCFG="/usr/bin/sysrepocfg"

# Genel hata kontrol fonksiyonu
check_success() {
    if [ $? -eq 0 ]; then
        echo "✅ İşlem başarılı!"
    else
        echo "❌ İşlem başarısız!"
        exit 1
    fi
}

# YANG Modülü Yükleme Fonksiyonu
install_module() {
    MODULE_PATH=$1
    echo "🔄 YANG modülü yükleniyor: $MODULE_PATH"
    $SYSREPOCTL --install --yang="$MODULE_PATH"
    check_success
}

# Özellik Etkinleştirme Fonksiyonu
enable_feature() {
    MODULE_NAME=$1
    FEATURE_NAME=$2
    echo "🔄 $MODULE_NAME modülünde $FEATURE_NAME özelliği etkinleştiriliyor..."
    $SYSREPOCTL --change "$MODULE_NAME" --enable-feature "$FEATURE_NAME"
    check_success
}

# Özellik Devre Dışı Bırakma Fonksiyonu
disable_feature() {
    MODULE_NAME=$1
    FEATURE_NAME=$2
    echo "🔄 $MODULE_NAME modülünde $FEATURE_NAME özelliği devre dışı bırakılıyor..."
    $SYSREPOCTL --change "$MODULE_NAME" --disable-feature "$FEATURE_NAME"
    check_success
}

# Modül Güncelleme Fonksiyonu
update_module() {
    MODULE_PATH=$1
    echo "🔄 YANG modülü güncelleniyor: $MODULE_PATH"
    $SYSREPOCTL --update "$MODULE_PATH"
    check_success
}

# Modül Silme Fonksiyonu
delete_module() {
    MODULE_NAME=$1
    echo "🗑️  $MODULE_NAME modülü kaldırılıyor..."
    $SYSREPOCTL --uninstall "$MODULE_NAME"
    check_success
}

# Modül Özelliklerini Listeleme Fonksiyonu
list_module_features() {
    MODULE_NAME=$1
    echo "📜 $MODULE_NAME modül özellikleri listeleniyor..."
    $SYSREPOCTL --list | grep "$MODULE_NAME"
    check_success
}

# Tüm Modülleri Listeleme Fonksiyonu
list_all_modules() {
    echo "📜 Tüm YANG modülleri listeleniyor..."
    $SYSREPOCTL --list
    check_success
}

# Belirli Bir Modülü Gösterme Fonksiyonu
show_module_details() {
    MODULE_NAME=$1
    echo "📜 $MODULE_NAME modül detayları gösteriliyor..."
    $SYSREPOCTL --list | grep "^$MODULE_NAME"
    check_success
}

# `sysrepocfg` ile Edit İşlemi Yapma Fonksiyonu
edit_config() {
    EDIT_FILE=$1
    DATASTORE=$2
    FORMAT=$3
    MODULE=$4
    echo "📝 $MODULE modülü için $EDIT_FILE dosyası kullanılarak konfigürasyon güncelleniyor..."
    $SYSREPOCFG --edit="$EDIT_FILE" --datastore="$DATASTORE" --format="$FORMAT" --module="$MODULE"
    check_success
}

# Yapılandırmayı Dışa Aktarma Fonksiyonu
export_config() {
    DATASTORE=$1
    MODULE_NAME=$2
    echo "📥 $MODULE_NAME modülü için $DATASTORE veri deposundaki yapılandırma dışa aktarılıyor..."
    $SYSREPOCFG --export --datastore="$DATASTORE" --module="$MODULE_NAME"
    check_success
}

# Kullanıcıdan gelen komutu al ve ilgili fonksiyonu çağır
COMMAND=$1
shift  # İlk argümanı atla, geri kalan argümanları al

case "$COMMAND" in
    install) install_module "$@" ;;
    enable-feature) enable_feature "$@" ;;
    disable-feature) disable_feature "$@" ;;
    update) update_module "$@" ;;
    delete) delete_module "$@" ;;
    list-features) list_module_features "$@" ;;
    list-modules) list_all_modules ;;
    show-module) show_module_details "$@" ;;
    edit-config) edit_config "$@" ;;
    export-config) export_config "$@" ;;
    *)
        echo "⚠️ Geçersiz komut! Kullanım:"
        echo "  ./sysrepo_manager.sh install <YANG_DOSYASI>"
        echo "  ./sysrepo_manager.sh enable-feature <MODÜL_ADI> <ÖZELLİK_ADI>"
        echo "  ./sysrepo_manager.sh disable-feature <MODÜL_ADI> <ÖZELLİK_ADI>"
        echo "  ./sysrepo_manager.sh update <YANG_DOSYASI>"
        echo "  ./sysrepo_manager.sh delete <MODÜL_ADI>"
        echo "  ./sysrepo_manager.sh list-features <MODÜL_ADI>"
        echo "  ./sysrepo_manager.sh list-modules"
        echo "  ./sysrepo_manager.sh show-module <MODÜL_ADI>"
        echo "  ./sysrepo_manager.sh edit-config <DOSYA> <DATASTORE> <FORMAT> <MODÜL>"
        echo "  ./sysrepo_manager.sh export-config <DATASTORE> <MODÜL_ADI>"
        exit 1
        ;;
esac
