#!/bin/sh

#
#  Copyright 2013 Nathan Wehr. All Rights Reserved.
#

INSTALL_PATH="/usr/local/include/kick"

# Remove old installation
rm -Rf $INSTALL_PATH

# Copy new files to the installation path
mkdir $INSTALL_PATH
cp -R ./* $INSTALL_PATH

# Set permissions on the new installation
chown -R root:wheel $INSTALL_PATH
chmod -R u=rwx,go=rx $INSTALL_PATH
