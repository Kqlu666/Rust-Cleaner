#include "utils.hpp"

int main()
{
    setlocale( LC_ALL, "Russian" );

    clean::download( );
    clean::temp_file( );
    clean::cache( );
    clean::computer_name( );
    clean::eac_log( );
    clean::eac_path( );
    clean::name( );
}
