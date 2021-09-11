@echo off
set prefix=ele
set /A cnt=0
set /A test=500
for /l %%x in (1, 1, %test%) do (
    ele < s_ele\in\%prefix%%%x.in > res\res%%x.txt
    fc /a res\res%%x.txt s_ele\out\%prefix%%%x.out > nul
    if errorlevel 1 (
        echo test %%x% FAIL
    ) else (
        echo test %%x% OK
        set /A cnt=cnt+1
    )
)

set \A cnt=cnt-1
echo %cnt% / %test%