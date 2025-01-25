#include <iostream>
#include <sysrepo_types.h>
#include "sysrepo.h"

class Sysrepo {

    sr_session_ctx_t *session = NULL;
    sr_conn_ctx_t *connection = NULL;    
    public:
    Sysrepo() {
        
    }

    bool connect() {
        int rc = sr_connect(SR_CONN_CACHE_RUNNING, &this->connection);
        if (SR_ERR_OK != rc) {
            std::cout << "sr_connect Error: " << rc << std::endl;
            return false;
        }
        int res = sr_session_start(connection, SR_DS_RUNNING, &session);
        if (SR_ERR_OK != res) {
            std::cout << "sr_session_start Error: " << res << std::endl;
            return false;
        }
        return true;
    }

    ~Sysrepo() {
        int rc = sr_session_stop(this->session);
        if (SR_ERR_OK != rc) {
            std::cout << "sr_session_stop Error: " << rc << std::endl;
        } else {
            std::cout << "sr_session_stop OK" << std::endl;
        }

        int res = sr_disconnect(this->connection);
        if (SR_ERR_OK != res) {
            std::cout << "sr_disconnect Error: " << res << std::endl;
        } else {
            std::cout << "sr_disconnect OK" << std::endl;
        }
    }
};

int main() {
    Sysrepo sysrepo;
    if (!sysrepo.connect()){ 
        std::cerr << "Could not connect to sysrepo" << std::endl;
        return 1;
    } else {
        std::cout << "Connected to sysrepo" << std::endl;
    }
    return 0;
}