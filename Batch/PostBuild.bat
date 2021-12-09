@echo on

set "Configuration=%1%"
set "Platform=%2%"

IF %1 == Debug goto DEBUG
IF %1 == Release goto RELEASE

:DEBUG
set Config=Debug
goto END

:RELEASE
set Config=Release
goto END

:END
echo %2\bin\windeployqt.exe ..\Bin\%Config%
%2\bin\windeployqt.exe ..\Bin\%Config%