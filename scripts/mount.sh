#!/bin/sh

sudo /scratchbox/sbin/sbox_ctl start
sudo /scratchbox/sbin/sbox_sync
sudo mount -o bind $HOME/projects/lpsmagic /scratchbox/users/$USER/home/$USER/lpsmagic
