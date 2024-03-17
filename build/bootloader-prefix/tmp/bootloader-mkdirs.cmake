# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/fabse/esp/v5.2.1/esp-idf/components/bootloader/subproject"
  "/home/fabse/SDU/Cyber_Physcial_Systems/build/bootloader"
  "/home/fabse/SDU/Cyber_Physcial_Systems/build/bootloader-prefix"
  "/home/fabse/SDU/Cyber_Physcial_Systems/build/bootloader-prefix/tmp"
  "/home/fabse/SDU/Cyber_Physcial_Systems/build/bootloader-prefix/src/bootloader-stamp"
  "/home/fabse/SDU/Cyber_Physcial_Systems/build/bootloader-prefix/src"
  "/home/fabse/SDU/Cyber_Physcial_Systems/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/fabse/SDU/Cyber_Physcial_Systems/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/fabse/SDU/Cyber_Physcial_Systems/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
