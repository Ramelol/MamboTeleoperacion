
cd .

chcp 1252

if "%1"=="" ("D:\Programas\MATLAB~1\bin\win64\gmake"  -j5  -f flightControlSystem.mk all) else ("D:\Programas\MATLAB~1\bin\win64\gmake"  -j5  -f flightControlSystem.mk %1)
@if errorlevel 1 goto error_exit

exit 0

:error_exit
echo The make command returned an error of %errorlevel%
exit 1