@echo off

:loop
    copy   Y:\test.csv  c:\Users\yuzu6\AppData\Local\Temp\scp15863\var\lib\mysql\fortest\import\imp.csv
    timeout 1
goto :loop

exit /b 0y