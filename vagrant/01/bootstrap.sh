#!/usr/bin/env bash

apt-get update
apt-get install -y nginx

if ! [ -L /usr/share/nginx/html ]; then
    rm -rf /usr/share/nginx/html
    ln -fs /vagrant/www /usr/share/nginx/html
fi

