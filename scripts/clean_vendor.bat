@echo off
rmdir /s /q vendor >nul 2>&1
rmdir /s /q vendor_* >nul 2>&1
rmdir /s /q CMakeFiles/git_*_cache >nul 2>&1
