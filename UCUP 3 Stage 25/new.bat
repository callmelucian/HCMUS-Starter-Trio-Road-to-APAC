@echo off
for %%i in (%*) do (
    if not exist "%%i" md "%%i"
    if not exist "%%i\%%i.cpp" type nul > "%%i\%%i.cpp"
    if not exist "%%i\%%i.in" type nul > "%%i\%%i.in"
)