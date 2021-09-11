@echo off

:loop
pargen
parsums2 < paroatest.txt > parout.txt
fc /b parout.txt parresu.txt > nul
if errorlevel 1 goto ending
echo test OK
goto loop

:ending
