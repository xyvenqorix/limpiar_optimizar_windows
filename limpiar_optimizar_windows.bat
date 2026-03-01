@echo off
setlocal EnableExtensions EnableDelayedExpansion
chcp 65001 >nul

title Limpiador y Optimizador de Windows (sin desfragmentar)
color 0A

:: Verificar privilegios de administrador
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Este script necesita permisos de administrador.
    echo Haz clic derecho sobre el .bat y selecciona ^"Ejecutar como administrador^".
    echo.
    pause
    exit /b 1
)

:menu
cls
echo ===============================================================
echo            LIMPIADOR Y OPTIMIZADOR DE WINDOWS
echo                (sin desfragmentacion)
echo ===============================================================
echo  1. Limpieza rapida (temporales + Win+R + recientes + papelera)
echo  2. Limpieza profunda (incluye cache de Windows Update)
echo  3. Limpiar SOLO historial Ejecutar (Win+R)
echo  4. Limpiar SOLO archivos temporales
echo  5. Comprobacion de disco (chkdsk /scan)
echo  6. Comprobacion de integridad del sistema (SFC)
echo  7. Ejecutar todo (excepto SFC)
echo  0. Salir
echo ===============================================================
set /p opcion=Selecciona una opcion [0-7]: 

if "%opcion%"=="1" goto limpieza_rapida
if "%opcion%"=="2" goto limpieza_profunda
if "%opcion%"=="3" goto limpiar_run
if "%opcion%"=="4" goto limpiar_temporales
if "%opcion%"=="5" goto check_disco
if "%opcion%"=="6" goto sfc_scan
if "%opcion%"=="7" goto todo_sin_sfc
if "%opcion%"=="0" goto fin

echo Opcion invalida.
timeout /t 2 >nul
goto menu

:limpieza_rapida
call :banner "LIMPIEZA RAPIDA"
call :limpiar_temporales_core
call :limpiar_run_core
call :limpiar_recientes_core
call :vaciar_papelera_core
call :resumen
goto volver_menu

:limpieza_profunda
call :banner "LIMPIEZA PROFUNDA"
call :limpiar_temporales_core
call :limpiar_run_core
call :limpiar_recientes_core
call :limpiar_windows_update_core
call :vaciar_papelera_core
call :resumen
goto volver_menu

:limpiar_run
call :banner "LIMPIAR HISTORIAL EJECUTAR (WIN+R)"
call :limpiar_run_core
call :resumen
goto volver_menu

:limpiar_temporales
call :banner "LIMPIAR ARCHIVOS TEMPORALES"
call :limpiar_temporales_core
call :resumen
goto volver_menu

:check_disco
call :banner "COMPROBACION DE DISCO"
echo Ejecutando: chkdsk C: /scan
chkdsk C: /scan
echo.
echo [OK] Comprobacion de disco finalizada.
call :resumen
goto volver_menu

:sfc_scan
call :banner "COMPROBACION DE INTEGRIDAD (SFC)"
echo Este proceso puede tardar bastante.
echo Ejecutando: sfc /scannow
sfc /scannow
echo.
echo [OK] SFC finalizado.
call :resumen
goto volver_menu

:todo_sin_sfc
call :banner "EJECUTAR TODO (SIN SFC)"
call :limpiar_temporales_core
call :limpiar_run_core
call :limpiar_recientes_core
call :limpiar_windows_update_core
call :vaciar_papelera_core
echo.
echo Ejecutando comprobacion de disco...
chkdsk C: /scan
call :resumen
goto volver_menu

:limpiar_temporales_core
echo.
echo [1/5] Eliminando temporales de usuario...
del /f /s /q "%temp%\*" >nul 2>&1
for /d %%D in ("%temp%\*") do rd /s /q "%%D" >nul 2>&1

echo [2/5] Eliminando temporales de Windows...
del /f /s /q "C:\Windows\Temp\*" >nul 2>&1
for /d %%D in ("C:\Windows\Temp\*") do rd /s /q "%%D" >nul 2>&1

echo [3/5] Limpiando Prefetch (acelera limpieza, no desfragmenta)...
del /f /s /q "C:\Windows\Prefetch\*" >nul 2>&1

echo [4/5] Limpiando cache de miniaturas...
del /f /s /q "%LocalAppData%\Microsoft\Windows\Explorer\thumbcache_*.db" >nul 2>&1

echo [5/5] Limpiando logs temporales comunes...
del /f /s /q "C:\Windows\Logs\CBS\*.log" >nul 2>&1
exit /b

:limpiar_run_core
echo.
echo Limpiando historial de Win+R (RunMRU)...
reg delete "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\RunMRU" /va /f >nul 2>&1
reg add "HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\RunMRU" /f >nul 2>&1
echo [OK] Historial de Ejecutar eliminado.
exit /b

:limpiar_recientes_core
echo.
echo Limpiando documentos recientes y accesos rapidos...
del /f /q "%AppData%\Microsoft\Windows\Recent\*" >nul 2>&1
del /f /q "%AppData%\Microsoft\Windows\Recent\AutomaticDestinations\*" >nul 2>&1
del /f /q "%AppData%\Microsoft\Windows\Recent\CustomDestinations\*" >nul 2>&1
echo [OK] Elementos recientes limpiados.
exit /b

:limpiar_windows_update_core
echo.
echo Limpiando cache de Windows Update...
net stop wuauserv >nul 2>&1
net stop bits >nul 2>&1
del /f /s /q "C:\Windows\SoftwareDistribution\Download\*" >nul 2>&1
for /d %%D in ("C:\Windows\SoftwareDistribution\Download\*") do rd /s /q "%%D" >nul 2>&1
net start bits >nul 2>&1
net start wuauserv >nul 2>&1
echo [OK] Cache de Windows Update limpiada.
exit /b

:vaciar_papelera_core
echo.
echo Vaciando papelera de reciclaje (todas las unidades)...
PowerShell -NoProfile -ExecutionPolicy Bypass -Command "Clear-RecycleBin -Force -ErrorAction SilentlyContinue" >nul 2>&1
echo [OK] Papelera vaciada.
exit /b

:resumen
echo.
echo ---------------------------------------------------------------
echo Proceso terminado. Recomendado: reiniciar el equipo.
echo ---------------------------------------------------------------
exit /b

:volver_menu
echo.
pause
goto menu

:banner
cls
echo ===============================================================
echo %~1
echo ===============================================================
exit /b

:fin
echo.
echo Saliendo...
timeout /t 1 >nul
exit /b 0
