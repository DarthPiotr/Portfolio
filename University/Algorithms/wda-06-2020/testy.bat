@echo off

:loop
rangestestgen > rangetest.txt
ranges < rangetest.txt > restest.txt
fc /b restest.txt rangeres.txt > nul
if errorlevel 1 goto ending
echo test OK
goto loop

:ending
