#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;


// ============================================================
// CONFIGURACION
// ============================================================

void ConfigurarConsola()
{
    system("color 0A");
    system("title Limpiador y Optimizador de Windows - xyvenqorix");
}


// ============================================================
// ADMINISTRADOR
// ============================================================

bool EsAdministrador()
{
    BOOL admin = FALSE;
    HANDLE token = NULL;

    if (OpenProcessToken(
        GetCurrentProcess(),
        TOKEN_QUERY,
        &token))
    {
        TOKEN_ELEVATION elevation;
        DWORD size = sizeof(elevation);

        if (GetTokenInformation(
            token,
            TokenElevation,
            &elevation,
            sizeof(elevation),
            &size))
        {
            admin = elevation.TokenIsElevated;
        }

        CloseHandle(token);
    }

    return admin == TRUE;
}


// ============================================================
// PAUSA
// ============================================================

void Pausa()
{
    cout << "\nPresiona una tecla para continuar...";
    system("pause >nul");
}


// ============================================================
// BANNER
// ============================================================

void Banner(const char* texto)
{
    system("cls");

    cout << "===============================================================\n";
    cout << "              LIMPIADOR Y OPTIMIZADOR\n";
    cout << "===============================================================\n\n";

    cout << "                    " << texto << "\n\n";

    cout << "===============================================================\n\n";
}


// ============================================================
// ABRIR INSTAGRAM
// ============================================================

void AbrirInstagram()
{
    cout << "\nAbriendo Instagram de Rodol...\n";

    system(
        "start \"\" \"https://www.instagram.com/rodol_ugc/\""
    );
}


// ============================================================
// RESUMEN
// ============================================================

void Resumen()
{
    cout << "\n";
    cout << "---------------------------------------------------------------\n";
    cout << "[OK] Proceso terminado.\n";
    cout << "---------------------------------------------------------------\n";

    AbrirInstagram();

    cout << "\n";
    Pausa();
}


// ============================================================
// TEMPORALES
// ============================================================

void LimpiarTemporales()
{
    cout << "\n[1/6] Eliminando temporales de usuario...\n";

    system(
        "del /f /s /q \"%temp%\\*\" >nul 2>&1"
    );

    system(
        "for /d %D in (\"%temp%\\*\") do rd /s /q \"%D\" >nul 2>&1"
    );


    cout << "[2/6] Eliminando temporales de Windows...\n";

    system(
        "del /f /s /q \"C:\\Windows\\Temp\\*\" >nul 2>&1"
    );

    system(
        "for /d %D in (\"C:\\Windows\\Temp\\*\") do rd /s /q \"%D\" >nul 2>&1"
    );


    cout << "[3/6] Limpiando Prefetch...\n";

    system(
        "del /f /s /q \"C:\\Windows\\Prefetch\\*\" >nul 2>&1"
    );


    cout << "[4/6] Limpiando cache de miniaturas...\n";

    system(
        "del /f /s /q "
        "\"%LocalAppData%\\Microsoft\\Windows\\Explorer\\thumbcache_*.db\" "
        ">nul 2>&1"
    );


    cout << "[5/6] Limpiando logs temporales comunes...\n";

    system(
        "del /f /s /q "
        "\"C:\\Windows\\Logs\\CBS\\*.log\" "
        ">nul 2>&1"
    );


    cout << "[6/6] Ejecutando Liberador de espacio...\n";

    system("cleanmgr /sagerun");


    cout << "\n[OK] Archivos temporales limpiados.\n";
}


// ============================================================
// HISTORIAL WIN + R
// ============================================================

void LimpiarRun()
{
    cout << "\nLimpiando historial de Win+R...\n";

    system(
        "reg delete "
        "\"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU\" "
        "/va /f >nul 2>&1"
    );

    system(
        "reg add "
        "\"HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\RunMRU\" "
        "/f >nul 2>&1"
    );

    cout << "[OK] Historial de Ejecutar eliminado.\n";
}


// ============================================================
// ARCHIVOS RECIENTES
// ============================================================

void LimpiarRecientes()
{
    cout << "\nLimpiando documentos recientes...\n";

    system(
        "del /f /q "
        "\"%AppData%\\Microsoft\\Windows\\Recent\\*\" "
        ">nul 2>&1"
    );

    system(
        "del /f /q "
        "\"%AppData%\\Microsoft\\Windows\\Recent\\AutomaticDestinations\\*\" "
        ">nul 2>&1"
    );

    system(
        "del /f /q "
        "\"%AppData%\\Microsoft\\Windows\\Recent\\CustomDestinations\\*\" "
        ">nul 2>&1"
    );

    cout << "[OK] Elementos recientes limpiados.\n";
}


// ============================================================
// WINDOWS UPDATE
// ============================================================

void LimpiarWindowsUpdate()
{
    cout << "\nLimpiando cache de Windows Update...\n";

    cout << "Deteniendo Windows Update...\n";

    system(
        "net stop wuauserv >nul 2>&1"
    );


    cout << "Deteniendo BITS...\n";

    system(
        "net stop bits >nul 2>&1"
    );


    cout << "Eliminando archivos descargados...\n";

    system(
        "del /f /s /q "
        "\"C:\\Windows\\SoftwareDistribution\\Download\\*\" "
        ">nul 2>&1"
    );

    system(
        "for /d %D in "
        "(\"C:\\Windows\\SoftwareDistribution\\Download\\*\") "
        "do rd /s /q \"%D\" >nul 2>&1"
    );


    cout << "Iniciando BITS...\n";

    system(
        "net start bits >nul 2>&1"
    );


    cout << "Iniciando Windows Update...\n";

    system(
        "net start wuauserv >nul 2>&1"
    );


    cout << "[OK] Cache de Windows Update limpiada.\n";
}


// ============================================================
// PAPELERA
// ============================================================

void VaciarPapelera()
{
    cout << "\nVaciando papelera de reciclaje...\n";

    system(
        "PowerShell -NoProfile "
        "-ExecutionPolicy Bypass "
        "-Command "
        "\"Clear-RecycleBin -Force -ErrorAction SilentlyContinue\" "
        ">nul 2>&1"
    );

    cout << "[OK] Papelera vaciada.\n";
}


// ============================================================
// LIMPIEZA RAPIDA
// ============================================================

void LimpiezaRapida()
{
    Banner("LIMPIEZA RAPIDA");

    LimpiarTemporales();
    LimpiarRun();
    LimpiarRecientes();
    VaciarPapelera();

    Resumen();
}


// ============================================================
// LIMPIEZA PROFUNDA
// ============================================================

void LimpiezaProfunda()
{
    Banner("LIMPIEZA PROFUNDA");

    LimpiarTemporales();
    LimpiarRun();
    LimpiarRecientes();
    LimpiarWindowsUpdate();
    VaciarPapelera();

    Resumen();
}


// ============================================================
// CHKDSK
// ============================================================

void ComprobarDisco()
{
    Banner("COMPROBACION DE DISCO");

    cout << "Ejecutando: chkdsk C: /scan\n\n";

    system("chkdsk C: /scan");

    cout << "\n[OK] Comprobacion de disco finalizada.\n";

    Resumen();
}


// ============================================================
// SFC
// ============================================================

void ComprobarSFC()
{
    Banner("COMPROBACION DE INTEGRIDAD DEL SISTEMA");

    cout << "Este proceso puede tardar bastante.\n\n";

    cout << "Ejecutando: sfc /scannow\n\n";

    system("sfc /scannow");

    cout << "\n[OK] SFC finalizado.\n";

    Resumen();
}


// ============================================================
// TODO EXCEPTO SFC
// ============================================================

void TodoSinSFC()
{
    Banner("EJECUTAR TODO (SIN SFC)");

    LimpiarTemporales();
    LimpiarRun();
    LimpiarRecientes();
    LimpiarWindowsUpdate();
    VaciarPapelera();

    cout << "\nEjecutando comprobacion de disco...\n\n";

    system("chkdsk C: /scan");

    cout << "\n[OK] Proceso terminado.\n";

    Resumen();
}


// ============================================================
// ACERCA DE
// ============================================================

void AcercaDe()
{
    const char* titulo =
        "Limpiador y Optimizador de Windows";

    const char* texto =
        "LIMPIADOR Y OPTIMIZADOR DE WINDOWS\n\n"
        "Version: 3.0\n\n"
        "Herramienta Administradora de limpieza y mantenimiento para Tu pc Windows "
        "manten tu equipo sin Basura Con Nuestra Herramienta.\n\n"
        "Creador: xyvenqorix\n"
        "WhatsApp: (+53)56639178\n"
        "Correo: rodolfo.vercel@gmail.com\n\n"
        "Facil De Usar.\n"
        "Libre De virus Y muy Util.";

    MessageBoxA(
        NULL,
        texto,
        titulo,
        MB_OK | MB_ICONINFORMATION
    );
}


// ============================================================
// MENU
// ============================================================

void Menu()
{
    while (true)
    {
        system("cls");

        cout << "===============================================================\n";
        cout << "        LIMPIADOR Y OPTIMIZADOR DE WINDOWS\n";
        cout << "                    xyvenqorix\n";
        cout << "===============================================================\n\n";

        cout << "  [1] Limpieza rapida\n";
        cout << "      Temporales + Win+R + recientes + papelera\n\n";

        cout << "  [2] Limpieza profunda\n";
        cout << "      Incluye cache de Windows Update\n\n";

        cout << "  [3] Limpiar historial Ejecutar (Win+R)\n\n";

        cout << "  [4] Limpiar archivos temporales\n\n";

        cout << "  [5] Comprobacion de disco (CHKDSK)\n\n";

        cout << "  [6] Comprobacion de integridad del sistema (SFC)\n\n";

        cout << "  [7] Ejecutar todo (excepto SFC)\n\n";

        cout << "  [8] Acerca de\n\n";

        cout << "  [0] Salir\n\n";

        cout << "===============================================================\n\n";

        cout << "Selecciona una opcion [0-8]: ";

        int opcion;

        cin >> opcion;


        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\nOpcion invalida.\n";

            Sleep(1000);

            continue;
        }


        switch (opcion)
        {
            case 1:
                LimpiezaRapida();
                break;

            case 2:
                LimpiezaProfunda();
                break;

            case 3:

                Banner("LIMPIAR HISTORIAL EJECUTAR");

                LimpiarRun();

                Resumen();

                break;

            case 4:

                Banner("LIMPIAR ARCHIVOS TEMPORALES");

                LimpiarTemporales();

                Resumen();

                break;

            case 5:
                ComprobarDisco();
                break;

            case 6:
                ComprobarSFC();
                break;

            case 7:
                TodoSinSFC();
                break;

            case 8:
                AcercaDe();
                break;

            case 0:

                system("cls");

                cout << "\nSaliendo...\n";

                Sleep(800);

                return;

            default:

                cout << "\nOpcion invalida.\n";

                Sleep(1000);

                break;
        }
    }
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    ConfigurarConsola();


    // --------------------------------------------------------
    // ADMINISTRADOR
    // --------------------------------------------------------

    if (!EsAdministrador())
    {
        system("cls");

        cout << "===============================================================\n";
        cout << "                 PERMISOS INSUFICIENTES\n";
        cout << "===============================================================\n\n";

        cout << "Esta aplicacion necesita ejecutarse como administrador.\n\n";

        cout << "Haz clic derecho sobre el EXE y selecciona:\n";
        cout << "\"Ejecutar como administrador\".\n\n";

        Pausa();

        return 1;
    }


    // --------------------------------------------------------
    // MENU
    // --------------------------------------------------------

    Menu();


    return 0;
}