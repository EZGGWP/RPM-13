#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QCoreApplication>
#include <qsqlquerymodel.h>

class Db : public QObject {
    Q_OBJECT
private:
    QString dbDir;
public:
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString exactTable = "Owners";
    int exactRow = 1;
    int rowCount = 1;
    explicit Db(QObject *parent = nullptr);
    ///
    /// @brief checkDbfile Проверка на существование файла БД
    /// @param path Путь к файлу
    ///
    void checkDbfile(QString path);
    ///
    /// @brief createDb Создание пустой БД
    ///
    void createDb();
public slots:
    ///
    /// @brief addRowPets Добавление записи в таблицу Pets
    /// @param PetPass Номер паспорта животного
    /// @param OwnerPass Номер паспорта хозяина
    /// @param Name Имя животного
    /// @param Weight Вес животного
    ///
    void addRowPets(QString PetPass, int OwnerPass, QString Name, int Weight);
    ///
    /// @brief addRowOwners Добавление записи в таблицу Owners
    /// @param ID Идентификатор хозяина
    /// @param lastName Фамилия хозяина
    /// @param firstName Имя Хозяина
    ///
    void addRowOwners(int ID, QString lastName, QString firstName);
    ///
    /// @brief updateRowPets Обновить запись в таблица Pets
    /// @param PetPass Номер паспорта животного
    /// @param OwnerPass Номер паспорта хозяина
    /// @param Name Имя животного
    /// @param Weight Вес животного
    ///
    void updateRowPets(QString PetPass, int OwnerPass, QString Name, int Weight);
    ///
    /// @brief updateRowOwners Обновление записи в таблице Owners
    /// @param ID Идентификатор хозяина
    /// @param lastName Фамилия хозяина
    /// @param firstName Имя хозяина
    ///
    void updateRowOwners(int ID, QString lastName, QString firstName);
    ///
    /// @brief removeRow Удалить запись по ключу
    /// @param key Ключ
    ///
    void removeRow(QString key);
    ///
    /// @brief next Переход к следующей записи
    ///
    void next();
    ///
    /// @brief prev Переход к предыдущей записи
    ///
    void prev();
    ///
    /// @brief check запрос, считающий количество записей
    ///
    void check();
signals:
    ///
    /// @brief throwPath Передать путь
    /// @param p Сам путь
    ///
    void throwPath(QString p);
    ///
    /// @brief throwExactRow Передать некую запись
    /// @param s Номер записи
    ///
    void throwExactRow(QString s);
    ///
    /// @brief throwIdUser Передать идентификатор хозяина
    /// @param s Идентификатор хозяина
    ///
    void throwIdUser(QString s);
    ///
    /// @brief throwLastName Передать фамилию хозяина
    /// @param s Фамилия хозяина
    ///
    void throwLastName(QString s);
    ///
    /// @brief throwFirstName Передать имя хозяина
    /// @param s Имя хозяина
    ///
    void throwFirstName(QString s);
    ///
    /// @brief throwPetPass Передать номер паспорта животного
    /// @param s Номер паспорта животного
    ///
    void throwPetPass(QString s);
    ///
    /// @brief throwOwnerPass Передать номер паспорта хозяина
    /// @param s Номер паспорта хозяина
    ///
    void throwOwnerPass(QString s);
    ///
    /// @brief throwName Передать имя животного
    /// @param s Имя животного
    ///
    void throwName(QString s);
    ///
    /// @brief throwWeight Передать вес животного
    /// @param s Вес животного
    ///
    void throwWeight(QString s);
    ///
    /// @brief enableButtons Включить выключенные кнопки
    /// @param b
    ///
    void enableButtons(bool b);
};

#endif // DBMANAGER_H
