#!/bin/bash

sysrepoctl --install /root/sysrepo-pg/yang/standard/ieee/published/802.1/ieee802-dot1q-bridge.yang \
           --install /root/sysrepo-pg/yang/standard/ieee/published/802.1/ieee802-dot1q-vlan-bridge.yang \
           --install /root/sysrepo-pg/src/yang-sample/example-module.yang \
           --search-dirs /root/sysrepo-pg/yang/standard/ietf/RFC/:/root/sysrepo-pg/yang/standard/ieee/published/802/:/root/sysrepo-pg/yang/standard/ieee/published/802.1/:/root/sysrepo-pg/yang/standard/ieee/published/802.3/:/root/sysrepo-pg/yang/standard/ieee/published/802.11/:/root/sysrepo-pg/yang/standard/ieee/published/1588/:/root/sysrepo-pg/yang/standard/ieee/published/1906.1/ \
            -v3