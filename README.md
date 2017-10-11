# Installation Instructions

## On OSX
1. `brew cask install osxfuse`
2. Go to `System Preferences > Sharing > Remote Login` and turn it on
3. Optionally, take note of your Computer Name/Hostname

## On RPi
1. `sudo apt-get install sshfs`
2. `sudo mkdir /mnt/watchme`
3. `sudo sshfs -o allow_other <USER>@<HOST>:/path/to/folder /mnt/watchme`

## Easiest way to develop on OSX and run on RPi
1. Open the Project Generator, import the project, and add ofxIO as well as ofxOMXPlayer to the Addons. Add support for Linux ARMv6 and LinuxARMv7 in the platforms as well (you have to select advanced options).
2. Copy the entire project to the RPi.
3. Remove ofxOMXPlayer from the Project Generator, as well as both the Linux Platforms, and update again.
4. Keep projects in sync with just the src/ folder.

