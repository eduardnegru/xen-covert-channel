#!/bin/bash

#copy executables on the 2 VMs and execute them.

g++ load.cpp -o load
g++ iterations.cpp -o iterations

mydomain="192.168.42.100"
mydomain2="192.168.42.109"

scp load iterations root@$mydomain:./xen-covert-channel/xen
scp load iterations root@$mydomain2:./xen-covert-channel/xen

ssh root@$mydomain2 './xen-covert-channel/xen/iterations ./xen-covert-channel/xen/no_load 50'

ssh root@$mydomain './xen-covert-channel/xen/load </dev/null >/dev/null 2>&1 &' 
sleep 5
ssh root@$mydomain2 './xen-covert-channel/xen/iterations ./xen-covert-channel/xen/with_load 50'

scp root@$mydomain2:./xen-covert-channel/xen/no_load root@$mydomain2:./xen-covert-channel/xen/with_load ./
scp ./no_load ./with_load root@$mydomain:./xen-covert-channel/xen/

rm load iterations
