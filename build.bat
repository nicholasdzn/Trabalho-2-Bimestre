@echo off
@Rem compile in windows

@Rem cd equivalent to unix pwd
SET default=%cd%\trabalho2.cpp

if "%1" neq "" SET default=%cd%\%1

if not exist %default%  goto :assert
    
g++ -o main.exe  %default%

@Rem run case compile succesfully
if %errorlevel% equ 0 .\main.exe

:assert
echo "Error: Informe um arquivo existente"
exit 1
exit /B 0 
