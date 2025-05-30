#!/bin/bash
# Copyright 2017 gRPC authors.

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# distributed under the License is distributed on an "AS IS" BASIS,

# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

sudo apt-get update

sudo apt-get install -y openjdk-8-jdk
sudo apt-get install -y unzip lsof

sudo apt-get install -y \
  autoconf \
  autotools-dev \
  build-essential \
  bzip2 \
  ccache \
  curl \
  gcc \
  gcc-multilib \
  git \
  gyp \
  lcov \
  libc6 \
  libc6-dbg \
  libc6-dev \
  libcurl4-openssl-dev \
  libgtest-dev \
  libreadline-dev \
  libssl-dev \
  libtool \
  make \
  strace \
  python-dev \
  python-pip \
  python-setuptools \
  python-yaml \
  python3-dev \
  python3-pip \
  python3-setuptools \
  python3-yaml \
  telnet \
  unzip \
  wget \
  zip \
  zlib1g-dev

sudo apt-get install -y google-perftools libgoogle-perftools-dev

sudo apt-get install -y netperf

sudo apt-get install -y python-psutil python3-psutil

sudo apt-get install -y google-cloud-sdk

sudo apt-get install -y libgtest-dev libc++-dev clang

sudo pip install --upgrade pip==19.3.1
sudo pip install tabulate
sudo pip install google-api-python-client oauth2client
sudo pip install virtualenv

sudo apt-get install -y pypy pypy-dev
curl -O https://bootstrap.pypa.io/get-pip.py
sudo pypy get-pip.py
sudo pypy -m pip install tabulate
sudo pypy -m pip install google-api-python-client oauth2client

sudo pypy -m pip install psutil

touch .profile
curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.25.4/install.sh | bash

source ~/.nvm/nvm.sh
nvm install 0.12 && npm config set cache /tmp/npm-cache
nvm install 4 && npm config set cache /tmp/npm-cache
nvm install 5 && npm config set cache /tmp/npm-cache
nvm alias default 4

sudo apt-get install -y cmake

sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
echo "deb https://download.mono-project.com/repo/ubuntu stable-bionic main" | sudo tee /etc/apt/sources.list.d/mono-official-stable.list
sudo apt-get update
sudo apt-get install -y mono-devel

wget -q https://packages.microsoft.com/config/ubuntu/20.04/packages-microsoft-prod.deb
sudo dpkg -i packages-microsoft-prod.deb

sudo apt-get install -y apt-transport-https
sudo apt-get update
sudo apt-get install -y dotnet-sdk-2.1

wget -q https://download.microsoft.com/download/2/4/A/24A06858-E8AC-469B-8AE6-D0CEC9BA982A/dotnet-ubuntu.16.04-x64.1.0.5.tar.gz
mkdir -p dotnet105_download
tar zxf dotnet-ubuntu.16.04-x64.1.0.5.tar.gz -C dotnet105_download
sudo cp -r dotnet105_download/shared/Microsoft.NETCore.App/1.0.5/ /usr/share/dotnet/shared/Microsoft.NETCore.App/

wget -q http://security.ubuntu.com/ubuntu/pool/main/i/icu/libicu55_55.1-7ubuntu0.4_amd64.deb
sudo dpkg -i libicu55_55.1-7ubuntu0.4_amd64.deb

wget -q -O dotnet_old.tar.gz https://download.visualstudio.microsoft.com/download/pr/b25b5650-0cb8-4699-a347-48d73650da0b/920966211e9bb1907232bbda1faa895a/dotnet-ubuntu.18.04-x64.1.1.10.tar.gz
mkdir -p dotnet_old
tar zxf dotnet_old.tar.gz -C dotnet_old
sudo cp -r dotnet_old/shared/Microsoft.NETCore.App/1.1.10/ /usr/share/dotnet/shared/Microsoft.NETCore.App/

gpg --keyserver hkp://pgp.mit.edu --recv-keys 409B6B1796C275462A1703113804BB82D39DC0E3 7D2BAF1CF37B13E2069D6956105BD0E739499BDB
curl -sSL https://get.rvm.io | bash -s stable --ruby

source ~/.rvm/scripts/rvm

git clone https://github.com/rbenv/rbenv.git ~/.rbenv
export PATH="$HOME/.rbenv/bin:$PATH"
eval "$(rbenv init -)"

git clone https://github.com/rbenv/ruby-build.git ~/.rbenv/plugins/ruby-build
export PATH="$HOME/.rbenv/plugins/ruby-build/bin:$PATH"

rbenv install 2.4.0
rbenv global 2.4.0
ruby -v

gem install bundler

sudo apt-get install -y php7.2 php7.2-dev php-pear unzip zlib1g-dev
sudo wget https://phar.phpunit.de/phpunit-8.5.8.phar && \
    sudo mv phpunit-8.5.8.phar /usr/local/bin/phpunit && \
    sudo chmod +x /usr/local/bin/phpunit
curl -sS https://getcomposer.org/installer | php
sudo mv composer.phar /usr/local/bin/composer

GO_VERSION=1.10
OS=linux
ARCH=amd64
curl -O https://storage.googleapis.com/golang/go${GO_VERSION}.${OS}-${ARCH}.tar.gz
sudo tar -C /usr/local -xzf go$GO_VERSION.$OS-$ARCH.tar.gz

sudo ln -s /usr/local/go/bin/go /usr/bin/go
rm go$GO_VERSION.$OS-$ARCH.tar.gz

sudo apt-get install -y linux-tools-common linux-tools-generic "linux-tools-$(uname -r)"

echo 0 | sudo tee /proc/sys/kernel/perf_event_paranoid

echo 0 | sudo tee /proc/sys/kernel/kptr_restrict

echo 4096 | sudo tee /proc/sys/kernel/perf_event_mlock_kb

git clone -v https://github.com/brendangregg/FlameGraph ~/FlameGraph

sudo apt-get install -y python3-scipy python3-numpy

curl -sSL https://get.docker.com/ | sh

sudo usermod -aG docker kbuilder

sudo tee --append ~kbuilder/.ssh/authorized_keys < kokoro_performance.pub

sudo mkdir /tmpfs
sudo chown kbuilder /tmpfs
touch /tmpfs/READY

sudo sed -i 's/APT::Periodic::Update-Package-Lists "1"/APT::Periodic::Update-Package-Lists "0"/' /etc/apt/apt.conf.d/10periodic
sudo sed -i 's/APT::Periodic::AutocleanInterval "1"/APT::Periodic::AutocleanInterval "0"/' /etc/apt/apt.conf.d/10periodic
sudo sed -i 's/APT::Periodic::Update-Package-Lists "1"/APT::Periodic::Update-Package-Lists "0"/' /etc/apt/apt.conf.d/20auto-upgrades
sudo sed -i 's/APT::Periodic::Unattended-Upgrade "1"/APT::Periodic::Unattended-Upgrade "0"/' /etc/apt/apt.conf.d/20auto-upgrades

echo 'Successfully initialized the linux worker, going for reboot in 10 seconds'
sleep 10
sudo reboot
