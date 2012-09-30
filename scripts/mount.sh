#!/bin/sh

sudo /scratchbox/sbin/sbox_ctl start
sudo /scratchbox/sbin/sbox_sync
if [ ! -d /scratchbox/users/$USER/home/$USER/lpsmagic ]; then
  mkdir /scratchbox/users/$USER/home/$USER/lpsmagic
fi
sudo mount -o bind $HOME/projects/lpsmagic /scratchbox/users/$USER/home/$USER/lpsmagic
