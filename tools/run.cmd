@echo off
rem Build the native game from this checkout and start it, on Windows: tools\run.ps1,
rem past PowerShell's policy against running scripts. Its options are in its comment.
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0run.ps1" %*
exit /b %errorlevel%
