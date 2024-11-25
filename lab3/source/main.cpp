// #include <locale>
#include <clocale>

#include "CLI.h"

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    CLI::run();
}