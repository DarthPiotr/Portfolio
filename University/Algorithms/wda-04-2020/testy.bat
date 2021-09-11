@echo off

:loop
invgen
invcnt < test.txt > restest.txt
fc /b restest.txt result.txt > nul
if errorlevel 1 goto ending
echo test OK
goto loop

:ending
