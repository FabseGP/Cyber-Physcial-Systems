# Setup of ESP32-toolchain for VSCode

A rudimentary step-by-step guide to run the included "blink"-project within the ESP32-toolchain, any missing step may please be directed to include it here.

# Table of Contents

* [Prerequisites](#prerequisites)
* [Installing the toolchain](#installing-the-toolchain)
* [Running the included "blink" project](#running-the-included-"blink"-project)
* [Checklist on creating, building and flashing a new project](#checklist-on-creating,-building-and-flashing-a-new-project)

# Prerequisites

* [Visual Studio Code](https://code.visualstudio.com/)
  * I would highly recommend [VSCodium](https://vscodium.com/) instead, a open source clone of VSCode with all telemetry/tracking removed. Oh, did I mention it was open source too?
* [Drivers for the builtin USB-to-UART-bridge](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads), the universal driver package should be chosen
  * There's no automatic driver install, so installing the drivers means connecting the ESP32-microcontroller to your computer, open device manager and manually install the driver for the bridge (usually one of the first devices)
    * Generic guide: https://helpdeskgeek.com/how-to/how-to-manually-install-a-driver-in-windows-11-10/
* [Git for Windows](https://gitforwindows.org/)
  * Not strictly needed, but VSCode will prompt you for installing git manually from the site when you try to initialize a git-repo, if not installed
* [clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd)
  * Opinionated code formatting, check [this comment](https://stackoverflow.com/a/62532674) on how to enable autoformat on save

# Installing the toolchain

1. Launch VSCode (Visual Studio Code)
2. Open the **Extensions** view either by: 
    1. The Extension icon in the Activity Bar on the left side
    2. Top menu bar &rarr; "View" &rarr; "Extensions"
    3. Ctrl+Shift+X
3. Search and install the "ESP-IDF Extension", should match [this icon](https://marketplace.visualstudio.com/items?itemName=espressif.esp-idf-extension)
4. Open the **Command Palette** either by:
    1. Top menu bar &rarr; "View" &rarr; "Command Palette"
    2. Ctrl+Shift+P
5. Type "configure esp-idf extension" and choose the **"ESP-IDF: Configure ESP-IDF Extension"** option
6. Choose **EXPRESS** as the setup mode (advanced mostly only adds options for where to install the needed utilities)
7. Choose **"v5.2.1 (release version)"** (or newer if there's any) as the version and click on **Install** (the default paths don't need to be changed)
8. Watch all One Piece episodes while you wait for the install to be over, maybe also Pokemon too if you finish it quickly
9. Congratulations, you have earned ![this badge](https://img.shields.io/badge/I_can_install_programs-windows_edition-blue)

# Running the included "blink"-example project
1. Launch VSCode if not already
2. Open the **Command Palette** either by:
    1. Top menu bar &rarr; "View" &rarr; "Command Palette"
    2. Ctrl+Shift+P
3. Type "show examples projects" and choose the **"ESP-IDF: Show Examples Projects"** option
4. Choose the "blink"-project under "get-started" and click on **"Create project using example blink"**

![example](https://github.com/espressif/vscode-esp-idf-extension/raw/master/media/tutorials/basic_use/blink_example.png)

5. Choose a directory of your choice to save the project too
    * **MUST** not be within folders that have empty space in their name (i.e. "4. semester"), the compiler will error out if so; instead "4_semester" will work
6. Open the **Command Palette**, type "set espressif device target" and choose the **"ESP-IDF: Set Espressif Device Target"** option
    * For our project you should choose **"esp32s2"**, then afterwards the option with **"USB Bridge"**
7. *Optional: Configure the project using the **"ESP-IDF: SDK Configuration Editor"** command, that is not needed for this project*
8. Build the project using either the **"ESP-IDF: Build your Project"** command (again through the **Command Palette**) or the shortcut: Ctrl+E (first) B (afterwards)
9. Choose the serial port of the device either by using the **"ESP-IDF: Select Port to Use"** command or the shortcut: Ctrl+E (first) P (afterwards)
    * By unplugging and plugging the microcontroller, you should be able to find the COM-port in device manager (the one that wasn't there before)
10. Flash the project using either the **"ESP-IDF: Flash your Project"** command or the shortcut: Ctrl+E (first) F (afterwards)
    * If asked on the flash mode, choose **"UART"**
    * If you're not seeing "Flash done" at the end of the terminal, you may have missed a step
11. Congratulations, you have earned ![this badge](https://img.shields.io/badge/I_can_make_a_led_blink-4th_semester_moment-blue)

# Checklist on creating, building and flashing a new project

1. Choose the correct target
2. If needed (say memory or fuses changes) configure the project using the **"ESP-IDF: SDK Configuration Editor"** command
3. Choose the correct port to flash to, including the correct flash mode
