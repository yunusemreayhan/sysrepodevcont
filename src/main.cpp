#include "sysrepo.h"
#include <iostream>
#include <sysrepo_types.h>

class Sysrepo {

  sr_session_ctx_t *session = NULL;
  sr_conn_ctx_t *connection = NULL;

public:
  Sysrepo() {}

  bool connect() {
    int rc = sr_connect(SR_CONN_CACHE_RUNNING, &this->connection);
    if (SR_ERR_OK != rc) {
      std::cout << "sr_connect Error: " << sr_strerror(rc) << std::endl;
      return false;
    }
    int res = sr_session_start(connection, SR_DS_RUNNING, &session);
    if (SR_ERR_OK != res) {
      std::cout << "sr_session_start Error: " << sr_strerror(res) << std::endl;
      return false;
    }
    return true;
  }

  int setItemStr(const char *xpath, const char *value = NULL) {
    // Set a list instance
    std::cout << "Setting item [" << xpath << "] = " << value << std::endl;
    int rc = sr_set_item_str(session, xpath, value, NULL, SR_EDIT_DEFAULT);
    if (rc != SR_ERR_OK) {
      fprintf(stderr, "Error setting item: %s\n", sr_strerror(rc));
    } else {
      std::cout << "Item set OK [" << xpath << "]" << std::endl;
    }

    // Apply the changes
    rc = sr_apply_changes(session, 0);
    if (rc != SR_ERR_OK) {
      fprintf(stderr, "Error applying changes: %s\n", sr_strerror(rc));
    } else {
      std::cout << "Changes applied OK [" << xpath << "]" << std::endl;
    }

    sr_val_t *value_to_receive = NULL;
    rc = sr_get_item(session, xpath, 0, &value_to_receive);
    if (rc != SR_ERR_OK) {
      fprintf(stderr, "Error getting item: %s\n", sr_strerror(rc));
    } else {
      std::cout << "Item received OK [" << xpath
                << "] = " << value_to_receive->data.string_val << std::endl;
    }
    sr_free_val(value_to_receive);
    return rc;
  }

  ~Sysrepo() {
    int rc = sr_session_stop(this->session);
    if (SR_ERR_OK != rc) {
      std::cout << "sr_session_stop Error: " << sr_strerror(rc) << std::endl;
    } else {
      std::cout << "sr_session_stop OK" << std::endl;
    }

    int res = sr_disconnect(this->connection);
    if (SR_ERR_OK != res) {
      std::cout << "sr_disconnect Error: " << sr_strerror(res) << std::endl;
    } else {
      std::cout << "sr_disconnect OK" << std::endl;
    }
  }
};

int main() {
  Sysrepo sysrepo;
  if (!sysrepo.connect()) {
    std::cerr << "Could not connect to sysrepo" << std::endl;
    return 1;
  } else {
    std::cout << "Connected to sysrepo" << std::endl;
  }
  const char *xpath =
      "/example-module:example-container/example-list[name='exampleName3']/value";
  const char *value_str = "exampleValue"; // This is just for illustration
  sysrepo.setItemStr(xpath, value_str);
  // sysrepocfg --export --datastore running --format json -m example-module

  return 0;
}