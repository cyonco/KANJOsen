@echo off

:loop
    copy   C:\Users\yuzu6\WorkSpace\contest\2021\Transfer\imp.csv  C:\Users\yuzu6\AppData\Local\Temp\scp47313\var\lib\mysql\fortest\import\imp.csv
    timeout 1
goto :loop

exit /b 0y