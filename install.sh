#!/bin/bash

set -x 
/usr/bin/python3 -m venv /repos/sysrepodevcont/.venv
export PYTHONUNBUFFERED=1 

source /repos/sysrepodevcont/.venv/bin/activate 

stdbuf -oL -eL python3 -m pip install --upgrade pip
stdbuf -oL -eL python3 -m pip install -r /repos/sysrepodevcont/yang-analysis/requirements.txt

echo 'root:1' | chpasswd

git config --global core.autocrlf true

ls /repos/sysrepodevcont/install-yangs.sh && chmod +x /repos/sysrepodevcont/install-yangs.sh && /repos/sysrepodevcont/install-yangs.sh

sysrepoctl --uninstall ieee802-dot1q-bridge -v3
sysrepoctl --uninstall ieee802-dot1q-vlan-bridge -v3
sysrepoctl --uninstall example-module -v3
sysrepoctl --install /repos/sysrepodevcont/yang/standard/ieee/published/802.1/ieee802-dot1q-bridge.yang \
           --install /repos/sysrepodevcont/yang/standard/ieee/published/802.1/ieee802-dot1q-vlan-bridge.yang \
           --install /repos/sysrepodevcont/src/yang-sample/example-module.yang \
           --search-dirs /repos/sysrepodevcont/yang/standard/ietf/RFC/:/repos/sysrepodevcont/yang/standard/ieee/published/802/:/repos/sysrepodevcont/yang/standard/ieee/published/802.1/:/repos/sysrepodevcont/yang/standard/ieee/published/802.3/:/repos/sysrepodevcont/yang/standard/ieee/published/802.11/:/repos/sysrepodevcont/yang/standard/ieee/published/1588/:/repos/sysrepodevcont/yang/standard/ieee/published/1906.1/ \
            -v3