#!/bin/sh

/scratchbox/login -d $HOME/lpsmagic dpkg-buildpackage
cp /scratchbox/users/$USER/home/$USER/lpsmagic*_armel.deb .
