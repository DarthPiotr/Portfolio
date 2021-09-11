@echo off
fc /b result.txt restest.txt
if errorlevel 1 goto error
echo OK
goto end
:error
echo ERROR
:end
echo end.