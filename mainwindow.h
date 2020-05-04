#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "db.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#include <QCoreApplication>
#include <QSqlDatabase>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Db* dbm;
    QString path = QCoreApplication::applicationDirPath() + "/db.db";
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    ///
    /// @brief setTableOwners Сделать таблицу Onwers активной
    ///
    void setTableOwners();
    ///
    /// @brief setTablePets Сделать таблицу Pets активной
    ///
    void setTablePets();
    ///
    /// @brief initRemoveRow Инициализация удаления ряда
    ///
    void initRemoveRow();
    ///
    /// @brief initAddRow Инициализация добавления ряда
    ///
    void initAddRow();
    ///
    /// @brief initUpdateRow Инициализация обновления ряда
    ///
    void initUpdateRow();
    ///
    /// @brief setDisabledSave Выключение кнопки сохранения для поддержания целостности при добавлении новой записи
    ///
    void setDisabledSave();
    ///
    /// @brief initExecQuery Инициализация выполнения запроса
    ///
    void initExecQuery();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
