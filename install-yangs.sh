#!/bin/bash
sysrepoctl --uninstall ieee802-dot1q-bridge -v3
sysrepoctl --uninstall ieee802-dot1q-vlan-bridge -v3
sysrepoctl --uninstall example-module -v3
sysrepoctl --install /repos/sysrepo-pg/yang/standard/ieee/published/802.1/ieee802-dot1q-bridge.yang \
           --install /repos/sysrepo-pg/yang/standard/ieee/published/802.1/ieee802-dot1q-vlan-bridge.yang \
           --install /repos/sysrepo-pg/src/yang-sample/example-module.yang \
           --search-dirs /repos/sysrepo-pg/yang/standard/ietf/RFC/:/repos/sysrepo-pg/yang/standard/ieee/published/802/:/repos/sysrepo-pg/yang/standard/ieee/published/802.1/:/repos/sysrepo-pg/yang/standard/ieee/published/802.3/:/repos/sysrepo-pg/yang/standard/ieee/published/802.11/:/repos/sysrepo-pg/yang/standard/ieee/published/1588/:/repos/sysrepo-pg/yang/standard/ieee/published/1906.1/ \
            -v3