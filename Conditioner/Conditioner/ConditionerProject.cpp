#include <locale.h>
#include <iostream>
#include "Conditioner.h"

int main() {

    setlocale(LC_ALL, "Russian");

    Conditioner c1("Samsung", "AR09", 10.5, 25, "охлаждение", 2022);
    Conditioner c2, c3;

    c2.setBrand("LG");
    c2.setModel("P12EP");
    c2.setWeight(12.0);
    c2.setTemperature(22);
    c2.setMode("нагрев");
    c2.setYear(2023);

    c3.setBrand("Daikin");
    c3.setModel("FTXB35");
    c3.setWeight(8.5);
    c3.setTemperature(24);
    c3.setMode("авто");
    c3.setYear(2021);

    std::cout << "До настройки:" << std::endl;
    c1.printInfo();
    c2.printInfo();
    c3.printInfo();

    for (int i = 0; i < 3; ++i) {
        c1.adjust("охлаждение", 22 - i);
        c2.adjust("нагрев", 26 + i);
        c3.adjust("охлаждение", 23 - i);
    }

    std::cout << "\nПосле настройки:" << std::endl;
    c1.printInfo();
    c2.printInfo();
    c3.printInfo();

    c1.serialize("D:\\Conditioners\\1.txt");
    c2.serialize("D:\\Conditioners\\2.txt");
    c3.serialize("D:\\Conditioners\\3.txt");

    return 0;
}