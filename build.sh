#!/bin/bash

if [ ! -d "./vcpkg" ] ; then
  # shallow clone vcpkg repo
  git clone --depth 1 "https://github.com/microsoft/vcpkg.git"

  # bootstrap vcpkg install
  ./vcpkg/bootstrap-vcpkg.sh

  # remove vcpkg .git directory
  rm -rf ./vcpkg/.git

  # install project dependencies from vcpkg.json file in project root
  #  ./vcpkg/vcpkg install

# if the user already has vcpkg
else
  echo "vcpkg already exists"
  echo "using existing vcpkg"
  
# install project dependencies from vcpkg.json file in project root
  #  ./vcpkg/vcpkg install
fi


