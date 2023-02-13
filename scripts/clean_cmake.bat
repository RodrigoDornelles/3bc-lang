@echo off
del /f /q Makefile >nul 2>&1
del /f /q cmake_install.cmake >nul 2>&1
del /f /q CMakeCache.txt >nul 2>&1
rmdir /s /q bin >nul 2>&1
rmdir /s /q _deps >nul 2>&1
rmdir /s /q vendor_* >nul 2>&1
rmdir /s /q Testing >nul 2>&1
rmdir /s /q CMakeFiles >nul 2>&1

