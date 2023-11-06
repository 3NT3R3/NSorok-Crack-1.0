#!/bin/sh

#Install requirements library 
current_user=$(whoami)

if [ "$current_user" != "root" ]; then
echo "You must be root !"
exit 1

fi

echo "You are root"

apt update 
apt install libmysqlcppconn-dev

echo "Lib to C++ was installed";

mkdir exec
chmod 777 ./compilate.sh
./compilate.sh
cp nsorok-crackv10 exec/

echo "PATH="$PATH":"$PWD"/exec"  >> ~/.bashrc

exec bash # && nsorok-crackv10

