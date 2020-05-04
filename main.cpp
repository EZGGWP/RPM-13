#include "mainwindow.h"

#include <QApplication>

///
/// @brief qMain Это функция мэйн, с которой начинается выполнение программы
/// @param argc
/// @param argv
/// @return Возвращает результат выполнения приложения
///
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
