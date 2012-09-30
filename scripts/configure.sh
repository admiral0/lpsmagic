#!/bin/sh

if [ ! -d /scratchbox/users/$USER/home/$USER/lpsmagic/build ]; then
  mkdir /scratchbox/users/$USER/home/$USER/lpsmagic/build
fi
/scratchbox/login -d $HOME/lpsmagic/build cmake ..