@echo off

:loop
hasit_testgen
has_og < hash_input.txt > hash_res.txt
fc /b hash_result.txt hash_res.txt > nul
if errorlevel 1 goto ending
echo test OK
goto loop

:ending
