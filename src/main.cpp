#include "sysrepo.h"
#include <bits/stdint-intn.h>
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
    std::cout << "======================================" << std::endl;
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
    } else if (strcmp(value_to_receive->data.string_val, value) == 0) {
      std::cout << "Item received as expected [" << xpath
                << "] = " << value_to_receive->data.string_val << std::endl;
    } else {
      std::cout << "Item received as not expected [" << xpath << "] = ["
                << value_to_receive->data.string_val << "], [" << value << "]"
                << std::endl;
    }
    sr_free_val(value_to_receive);
    return rc;
  }

  int setItemInt(const char *xpath, const int32_t value) {
    // Set a list instance
    std::cout << "======================================" << std::endl;
    std::cout << "Setting item [" << xpath << "] = " << value << std::endl;
    sr_val_t val;
    val.type = SR_INT32_T;
    val.data.int32_val = value;
    int rc = sr_set_item(session, xpath, &val, SR_EDIT_DEFAULT);
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
    } else if (value_to_receive->data.int32_val== value) {
      std::cout << "Item received as expected [" << xpath
                << "] = " << value_to_receive->data.int32_val << std::endl;
    } else {
      std::cout << "Item received as not expected [" << xpath << "] = ["
                << value_to_receive->data.int32_val << "], [" << value << "]"
                << std::endl;
    }
    sr_free_val(value_to_receive);
    return rc;
  }

  ~Sysrepo() {
    std::cout << "======================================" << std::endl;
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
  const char *xpath = "/example-module:example-container/"
                      "example-list[name='exampleName6']/value";
  const char *value_str = "exampleValue6"; // This is just for illustration
  const char *xpathip =
      "/example-module:example-container/example-list[name='exampleName6']/ip";
  const char *valueip_str = "192.168.1.64"; // This is just for illustration
  const char *xpathport =
      "/example-module:example-container/example-list[name='exampleName6']/port";
  const int32_t valueport_str = 8080; // This is just for illustration
  sysrepo.setItemStr(xpath, value_str);
  sysrepo.setItemStr(xpathip, valueip_str);
  sysrepo.setItemInt(xpathport, valueport_str);

  
  const char *sublistdirect =
      "/example-module:example-container/example-list[name='exampleName7']/sub-list[name='sublistName7']/value";
  const char* sublistdirectval = "sublist value"; // This is just for illustration
  // sysrepocfg --export --datastore running --format json -m example-module
  sysrepo.setItemStr(sublistdirect, sublistdirectval);

  

  
  const char *subsublistdirect =
      "/example-module:example-container/example-list[name='exampleName8']/sub-list[name='sublistName8']/sub-sub-list[name='subsublistName8']/value";
  const char* subsublistdirectval = "sublist value 8"; // This is just for illustration
  // sysrepocfg --export --datastore running --format json -m example-module
  sysrepo.setItemStr(subsublistdirect, subsublistdirectval);

  return 0;
}
