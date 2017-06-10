
Debian
====================
This directory contains files used to package Fortcoind/Fortcoin-qt
for Debian-based Linux systems. If you compile Fortcoind/Fortcoin-qt yourself, there are some useful files here.

## Fortcoin: URI support ##


Fortcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install Fortcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your Fortcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/Fortcoin128.png` to `/usr/share/pixmaps`

Fortcoin-qt.protocol (KDE)

