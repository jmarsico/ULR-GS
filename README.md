## Easiest way to develop on OSX and run on RPi
1. Open the Project Generator, import the project, and add ofxIO as well as ofxOMXPlayer to the Addons. Add support for Linux ARMv6 and LinuxARMv7 in the platforms as well (you have to select advanced options).
2. Copy the entire project to the RPi.
3. Remove ofxOMXPlayer from the Project Generator, as well as both the Linux Platforms, and update again.
4. Keep projects in sync with just the src/ folder.

