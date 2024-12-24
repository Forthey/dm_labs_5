#include <clocale>
#include <windows.h>

#include "CLI.h"

#pragma execution_character_set( "utf-8" )


int main() {
    SetConsoleOutputCP( 65001 );
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    CLI::run();
}