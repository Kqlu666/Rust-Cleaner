#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <Rpcdce.h>
#include <sstream>
#include <iomanip>
#pragma comment(lib, "Rpcrt4.lib")

namespace clean {
    namespace fs = std::filesystem;

    void temp_file( ) {
        system( "del C:\\Temp\\ /f /s /q" );
        system( "del C:\\Windows\\Prefetch\\ /f /s /q" );
        system( "del C:\\Windows\\Temp\\ /f /s /q" );
        system( "del C:\\*.log /a /s /q /f" );
        system( "del C:\\*.temp /a /s /q /f" );
        system( "del C:\\*.tmp /a /s /q /f" );
        system( "del C:\\*.bak /a /s /q /f" );
        system( "del C:\\*.old /a /s /q /f" );
        system( "del C:\\*.chk /a /s /q /f" );
        system( "del C:\\*.mkd /a /s /q /f" );
        system( "del C:\\*.pf /a /s /q /f" );
        system( "del C:\\*.dlf /a /s /q /f" );
    }
    void download( ) {
        std::filesystem::path downloadsPath = std::filesystem::path( getenv( "USERPROFILE" ) ) / "Downloads";

        std::filesystem::path wildcardPath = downloadsPath / "*.*";

        for( const auto& entry : std::filesystem::directory_iterator( downloadsPath ) ) {
            std::filesystem::remove_all( entry.path( ) );
        }

        std::cout << "[ Downloads ] Очистка папки загрузок завершена успешно." << std::endl;
    }
    void computer_name( ) {
        DWORD bufferSizeNetBIOS = MAX_COMPUTERNAME_LENGTH + 1;
        wchar_t computerNameNetBIOS[ MAX_COMPUTERNAME_LENGTH + 1 ];

        if( GetComputerNameEx( ComputerNamePhysicalNetBIOS, computerNameNetBIOS, &bufferSizeNetBIOS ) )
            std::wcout << L"[ ComputerNamePhysicalNetBIOS ] Текущее имя компьютера: " << computerNameNetBIOS << std::endl;

        DWORD bufferSizeDnsHostname = MAX_COMPUTERNAME_LENGTH + 1;
        wchar_t computerNameDnsHostname[ MAX_COMPUTERNAME_LENGTH + 1 ];

        if( GetComputerNameEx( ComputerNamePhysicalDnsHostname, computerNameDnsHostname, &bufferSizeDnsHostname ) )
            std::wcout << L"[ ComputerNamePhysicalDnsHostname ] Текущее имя компьютера: " << computerNameDnsHostname << std::endl;

        DWORD uniqueNumber = GetTickCount( );

        std::wstring computerName = L"Computer" + std::to_wstring( uniqueNumber );
        if( SetComputerNameExW( ComputerNamePhysicalNetBIOS, computerName.c_str( ) ) )
            std::wcout << L"[ ComputerNamePhysicalNetBIOS ] Имя компьютера успешно изменено на: " << computerName << std::endl;

        if( SetComputerNameExW( ComputerNamePhysicalDnsHostname, computerName.c_str( ) ) )
            std::wcout << L"[ ComputerNamePhysicalDnsHostname ] Имя компьютера успешно изменено на: " << computerName << std::endl;
    }
    void machine_guid( ) {
        HKEY hKey;
        if( RegOpenKeyEx( HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Cryptography", 0, KEY_SET_VALUE, &hKey ) == ERROR_SUCCESS ) {
            UUID newUuid;
            UuidCreate( &newUuid );

            RPC_WSTR newUuidString;
            if( UuidToString( &newUuid, &newUuidString ) == RPC_S_OK ) {
                if( RegSetValueEx( hKey, L"MachineGuid", 0, REG_SZ, reinterpret_cast< const BYTE* >( newUuidString ), sizeof( wchar_t ) * ( wcslen( reinterpret_cast< const wchar_t* >( newUuidString ) ) + 1 ) ) == ERROR_SUCCESS )
                    std::wcout << L"[ MachineGuid ] Значение параметра успешно изменено на: " << newUuidString << std::endl;
            }
            RpcStringFree( &newUuidString );

            RegCloseKey( hKey );
        }

    }
    void cache( ) {
        system( "ipconfig /flushdns" );
        system( "del C:\\Users\\%username%\\AppData\\Local\\Microsoft\\Windows\\INetCookies\\ / f / s / q" );
        system( "del C:\\Users\\%username%\\AppData\\Local\\Microsoft\\Windows\\INetCache\\ / f / s / q" );
        system( "del C:\\Users\\%username%\\AppData\\Local\\Microsoft\\Windows\\History\\ / f / s / q" );
    }
    void remove_directory( const std::wstring& path ) {
        try {
            for( const auto& entry : fs::directory_iterator( path ) ) {
                if( fs::is_directory( entry.path( ) ) ) {
                    remove_directory( entry.path( ) );
                    fs::remove( entry.path( ) );
                }
                else {
                    fs::remove( entry.path( ) );
                }
            }
        }
        catch( const std::exception& e ) {
            std::cerr << "Ошибка: " << e.what( ) << std::endl;
        }
    }
    void eac_path( ) {
        std::wstring EasyAntiCheat_EOS = L"C:\\Program Files (x86)\\EasyAntiCheat_EOS\\";
        std::wstring EasyAntiCheat = L"C:\\Program Files (x86)\\EasyAntiCheat";
        remove_directory( EasyAntiCheat_EOS );
        remove_directory( EasyAntiCheat );
    }
    void reg_delete_key( HKEY hKeys, LPCWSTR lpSubKey ) {
        HKEY hKey;

        LONG result = RegOpenKeyExW( hKeys, lpSubKey, 0, KEY_ALL_ACCESS, &hKey );
        RegDeleteTree( hKey, nullptr );
        RegCloseKey( hKey );
    }
    void eac_log( ) {
        const wchar_t* ValveKey = L"SOFTWARE\\Valve";
        const wchar_t* EosKey = L"SOFTWARE\\WOW6432Node\\EasyAntiCheat_EOS";
        const wchar_t* EacKey = L"SOFTWARE\\WOW6432Node\\EasyAntiCheat";
        const wchar_t* EosService = L"SYSTEM\\ControlSet001\\Services\\EasyAntiCheat_EOS";
        const wchar_t* EacService = L"SYSTEM\\ControlSet001\\Services\\EasyAntiCheat_EOS";
        const wchar_t* VwifimpService = L"SYSTEM\\ControlSet001\\Services\\vwifimp\\Enum";
        const wchar_t* RustKey = L"Software\\Facepunch Studios LTD\\Rust";

        reg_delete_key( HKEY_LOCAL_MACHINE, ValveKey );
        reg_delete_key( HKEY_LOCAL_MACHINE, EosKey );
        reg_delete_key( HKEY_LOCAL_MACHINE, EacKey );
        reg_delete_key( HKEY_LOCAL_MACHINE, EacService );
        reg_delete_key( HKEY_LOCAL_MACHINE, EosService );
        reg_delete_key( HKEY_LOCAL_MACHINE, VwifimpService );
        reg_delete_key( HKEY_CURRENT_USER, RustKey );
    }
    void name( ) {
        HKEY hKey;
        LPCWSTR subKey = L"Volatile Environment";
        LPCWSTR valueName = L"USERNAME";

        LONG result = RegOpenKeyEx( HKEY_CURRENT_USER, subKey, 0, KEY_SET_VALUE, &hKey );
        srand( time( 0 ) );
        int randomValue = 100000 + rand( ) % 100001;

        std::wstring username = std::to_wstring( randomValue );
        result = RegSetValueEx( hKey, valueName, 0, REG_SZ, ( BYTE* )username.c_str( ), ( username.size( ) + 1 ) * sizeof( wchar_t ) );

        if( result == ERROR_SUCCESS )
            std::wcout << L"[ UserName ] set to: " << username << std::endl;

        RegCloseKey( hKey );
    }
}

