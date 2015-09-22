#!/bin/sh
/bin/echo -n "Is Homebrew installed? "
which brew
if [ $? -gt 0 ];then
  /bin/echo -n "no, proceed with installation? [Y/n] "
  read -n 1 answer
  if [ "$answer" == "n" ];then
    exit 1
  fi
  ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
fi

brew install qt5
brew install cmake

