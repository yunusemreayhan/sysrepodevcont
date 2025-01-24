#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sleep için
#include <sysrepo.h>

/* Sysrepo Bağlantısını Başlatan Fonksiyon */
sr_conn_ctx_t* start_sysrepo_connection() {
    sr_conn_ctx_t *connection = NULL;
    int rc = sr_connect(0, &connection);
    if (rc != SR_ERR_OK) {
        printf("Error: Unable to connect to Sysrepo (%s)\n", sr_strerror(rc));
        return NULL;
    }
    printf("Connected to Sysrepo.\n");
    return connection;
}

/* Sysrepo Bağlantısını Sonlandıran Fonksiyon */
void stop_sysrepo_connection(sr_conn_ctx_t *connection) {
    if (connection != NULL) {
        sr_disconnect(connection);
        printf("Disconnected from Sysrepo.\n");
    }
}

/* YANG Dosyasını Sysrepo'ya Yükleyen Fonksiyon */
int install_yang_module(sr_conn_ctx_t *connection, const char *yang_path, const char *search_dirs) {
    if (connection == NULL) {
        printf("Error: Connection to Sysrepo is not established.\n");
        return SR_ERR_INTERNAL;
    }

    int rc = sr_install_module(connection, yang_path, search_dirs, NULL);
    if (rc != SR_ERR_OK) {
        printf("Error: Unable to install YANG module (%s)\n", sr_strerror(rc));
        return rc;
    }
    printf("YANG module installed: %s\n", yang_path);

    return SR_ERR_OK;
}

/* Sysrepo'daki Modülü Güncelleyen Fonksiyon */
int update_yang_module(sr_conn_ctx_t *connection, const char *yang_path, const char *search_dirs) {
    if (connection == NULL) {
        printf("Error: Connection to Sysrepo is not established.\n");
        return SR_ERR_INTERNAL;
    }

    int rc = sr_update_module(connection, yang_path, search_dirs);
    if (rc != SR_ERR_OK) {
        printf("Error: Unable to update YANG module from file '%s' (%s)\n", yang_path, sr_strerror(rc));
        return rc;
    }
    printf("YANG module updated successfully from: %s\n", yang_path);

    return SR_ERR_OK;
}

/* Ana Fonksiyon */
int main() {
    const char *initial_yang_path = "/root/src/sysrepo_c_project/yang/ismailemre.yang";
    const char *update_yang_path = "/root/src/sysrepo_c_project/yang/ismailemre@2025-02-01.yang";
    const char *search_dirs = "/root/src/sysrepo_c_project/yang";

    /* Sysrepo Bağlantısını Başlat */
    sr_conn_ctx_t *connection = start_sysrepo_connection();
    if (connection == NULL) {
        return EXIT_FAILURE;
    }

    /* İlk YANG Dosyasını Sysrepo'ya Yükle */
    printf("Installing the initial YANG module...\n");
    int rc = install_yang_module(connection, initial_yang_path, search_dirs);
    if (rc != SR_ERR_OK) {
        printf("Failed to install the initial YANG module. Error code: %d\n", rc);
        stop_sysrepo_connection(connection);
        return EXIT_FAILURE;
    }

    /* Yükleme sonrası Sysrepo Bağlantısını Yenile */
    stop_sysrepo_connection(connection);
    sleep(1); // Bağlamın oturması için 2 saniye bekle
    connection = start_sysrepo_connection();
    if (connection == NULL) {
        return EXIT_FAILURE;
    }

    /* Güncellenen YANG Dosyasını Sysrepo'daki Modüle Uygula */
    printf("Updating the YANG module in Sysrepo...\n");
    rc = update_yang_module(connection, update_yang_path, search_dirs);
    if (rc != SR_ERR_OK) {
        printf("Failed to update YANG module. Error code: %d\n", rc);
        stop_sysrepo_connection(connection);
        return EXIT_FAILURE;
    }

    /* Sysrepo Bağlantısını Sonlandır */
    stop_sysrepo_connection(connection);

    return EXIT_SUCCESS;
}
