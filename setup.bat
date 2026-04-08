@echo off
title VISIONFORGE Professional Setup
chcp 65001 >nul
setlocal EnableDelayedExpansion

:: ESC character for ANSI codes
for /f %%a in ('echo prompt $E^| cmd /q') do set "ESC=%%a"

:: Colors
set "CYAN=%ESC%[96m"
set "GREEN=%ESC%[92m"
set "YELLOW=%ESC%[93m"
set "WHITE=%ESC%[97m"
set "DIM=%ESC%[90m"
set "RESET=%ESC%[0m"
set "BOLD=%ESC%[1m"
set "CLEAR_LINE=%ESC%[2K"

cls
echo.
echo %CYAN%%BOLD%  ╔══════════════════════════════════════════════════╗%RESET%
echo %CYAN%%BOLD%  ║                                                  ║%RESET%
echo %CYAN%%BOLD%  ║      VISION FORGE PROFESSIONAL INSTALLER         ║%RESET%
echo %CYAN%%BOLD%  ║                                                  ║%RESET%
echo %CYAN%%BOLD%  ╚══════════════════════════════════════════════════╝%RESET%
echo.
echo %DIM%  Initializing setup environment...%RESET%
echo.
echo.
echo.
echo.
echo.

call :loading "Preparing environment"
call :loading "Installing pip"
python\python.exe python\get-pip.py >nul 2>&1
call :loading "Installing Python dependencies"
python\python.exe -m pip install -r requirements.txt
call :loading "Downloading Chromium browser"
python\python.exe -m playwright install chromium
echo comleted_setup > setup.flag
call :loading "Finalizing installation"

cls
echo.
echo %GREEN%%BOLD%  ╔══════════════════════════════════════════════════╗%RESET%
echo %GREEN%%BOLD%  ║                                                  ║%RESET%
echo %GREEN%%BOLD%  ║            SETUP COMPLETED SUCCESSFULLY          ║%RESET%
echo %GREEN%%BOLD%  ║                                                  ║%RESET%
echo %GREEN%%BOLD%  ╚══════════════════════════════════════════════════╝%RESET%
echo.
echo %WHITE%  VISION FORGE Professional is ready to use.%RESET%
echo %DIM%  You may close this window or press any key to exit.%RESET%
echo.
pause >nul
exit

:: -----------------------------------------------
:: Animated Loading Bar (no cls flicker)
:: -----------------------------------------------
:loading
set "msg=%~1"
setlocal EnableDelayedExpansion

:: Move cursor up to the progress area (6 lines up from bottom)
set "UP=%ESC%[6A"
set "DOWN=%ESC%[1B"

:: Spinner chars
set "sp[0]=⠋"
set "sp[1]=⠙"
set "sp[2]=⠸"
set "sp[3]=⠴"
set "sp[4]=⠦"
set "sp[5]=⠇"

set "full_bar=══════════════════════════════════════"
set "bar_len=38"

for /l %%i in (0,1,37) do (
    :: Calculate filled portion
    set "fill="
    set "empty="
    for /l %%f in (1,1,%%i) do set "fill=!fill!█"
    set /a "emp=bar_len - %%i"
    for /l %%e in (1,1,!emp!) do set "empty=!empty!░"

    :: Spinner index
    set /a "si=%%i %% 6"
    set "spin=!sp[%si%]!"

    :: Percentage
    set /a "pct=(%%i * 100) / bar_len"

    :: Move up and rewrite progress lines
    echo !UP!
    echo %CLEAR_LINE%%YELLOW%  !spin!  %WHITE%%BOLD%!msg!%RESET%
    echo %CLEAR_LINE%%DIM%  ────────────────────────────────────────────────%RESET%
    echo %CLEAR_LINE%%CYAN%  ║ !fill!!empty! ║  %GREEN%%BOLD%!pct!%%%RESET%
    echo %CLEAR_LINE%%DIM%  ────────────────────────────────────────────────%RESET%
    echo %CLEAR_LINE%

    :: Small delay via ping
    ping -n 1 -w 30 127.0.0.1 >nul
)

:: Done state
echo !UP!
echo %CLEAR_LINE%%GREEN%  ✓  %WHITE%%BOLD%!msg!%RESET%
echo %CLEAR_LINE%%DIM%  ────────────────────────────────────────────────%RESET%
echo %CLEAR_LINE%%GREEN%  ║ ██████████████████████████████████████ ║  100%%%RESET%
echo %CLEAR_LINE%%DIM%  ────────────────────────────────────────────────%RESET%
echo %CLEAR_LINE%

endlocal
goto :eof