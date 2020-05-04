#include "db.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
Db::Db(QObject *parent) : QObject(parent) {

}

void Db::checkDbfile(QString path) {
    QFile file(path);
        if (file.exists()) {
            this->dbDir = path;
            this->db.setDatabaseName(dbDir);
            qDebug() << "File found";
        } else {
            QMessageBox msgBox;
            msgBox.setText("Файл с БД не найден!");
            msgBox.setInformativeText("Не расстраивайтесь, мы создадим новый в " + QCoreApplication::applicationDirPath() + "/db.db");
            msgBox.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);
            msgBox.exec();
            this->dbDir = QCoreApplication::applicationDirPath() + "/db.db";
            qDebug() << "File not found. Creating in stock";
            createDb();
        }
    emit throwPath(dbDir);
    check();
    emit throwExactRow(QString::number(exactRow) + "/" + QString::number(rowCount));
}

void Db::createDb() {
    this->db.setDatabaseName(dbDir);
    db.open();
    QSqlQuery query;
    query.exec("CREATE TABLE 'Owners' ('ID' INTEGER NOT NULL PRIMARY KEY UNIQUE, 'Last_name' TEXT NOT NULL, 'First_name' TEXT NOT NULL)");
    query.exec("CREATE TABLE 'Pets' ('PetPassNum' TEXT NOT NULL UNIQUE, 'OwnerPassNum' INTEGER NOT NULL, 'Name' TEXT NOT NULL, 'Weight' INTEGER NOT NULL, PRIMARY KEY ('PetPassNum'))");
    qDebug() << "Created empty base";
    db.close();
    check();
    emit throwExactRow(QString::number(exactRow) + "/" + QString::number(rowCount));
}

void Db::addRowPets(QString petPass, int ownerPass, QString name, int weight) {
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO Pets VALUES (:pet_pass, :owner_pass, :name, :weight)");
    query.bindValue(":pet_pass", petPass);
    query.bindValue(":owner_pass", ownerPass);
    query.bindValue(":name", name);
    query.bindValue(":weight", weight);
    qDebug() << query.exec();
    db.close();
    check();
    emit throwExactRow(QString::number(exactRow) + "/" + QString::number(rowCount));
}

void Db::addRowOwners(int ID, QString lastName, QString firstName) {
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO Owners VALUES (:id, :last_name, :first_name)");
    query.bindValue(":id", ID);
    query.bindValue(":last_name", lastName);
    query.bindValue(":first_name", firstName);
    qDebug() << query.exec();
    db.close();
    check();
    emit throwExactRow(QString::number(exactRow) + "/" + QString::number(rowCount));
}

void Db::updateRowPets(QString petPass, int ownerPass, QString name, int weight) {
    db.open();
    QSqlQuery query;
    query.prepare("UPDATE Pets SET OwnerPassNum = :owner_pass, Name = :name, Weight = :weight WHERE PetPassNum = :pet_pass");
    query.bindValue(":pet_pass", petPass);
    query.bindValue(":owner_pass", ownerPass);
    query.bindValue(":name", name);
    query.bindValue(":weight", weight);
    qDebug() << query.exec();
    db.close();
    check();
    emit throwExactRow(QString::number(exactRow) + "/" + QString::number(rowCount));
}

void Db::updateRowOwners(int ID, QString lastName, QString firstName) {
    db.open();
    QSqlQuery query;
    query.prepare("UPDATE Owners SET Last_name = :last_name, First_name = :first_name WHERE ID = :id");
    query.bindValue(":id", ID);
    query.bindValue(":last_name", lastName);
    query.bindValue(":first_name", firstName);
    qDebug() << query.exec();
    db.close();
    check();
    emit throwExactRow(QString::number(exactRow) + "/" + QString::number(rowCount));
}

void Db::removeRow(QString key) {
    db.open();
    QSqlQuery query;
    qDebug() << key;
    if (exactTable == "Owners") {
        query.prepare("DELETE FROM Owners WHERE ID = :key");
        query.bindValue(":key", key.toInt());
    }
    if (exactTable == "Pets") {
        query.prepare("DELETE FROM Pets WHERE ID = :key");
        query.bindValue(":key", key);
    }
    qDebug() << query.exec();
    db.close();
    check();
    emit throwExactRow(QString::number(exactRow) + "/" + QString::number(rowCount));
}


void Db::next() {
    if (exactRow < rowCount) {
        exactRow++;
    }
    emit throwExactRow(QString::number(exactRow) + "/" + QString::number(rowCount));
}

void Db::prev() {
    if (exactRow > 1) {
        exactRow--;
    }
    emit throwExactRow(QString::number(exactRow) + "/" + QString::number(rowCount));
}

void Db::check() {
    db.open();
    rowCount = 0;
    QSqlQuery query;
    qDebug() << query.exec("SELECT * FROM " + exactTable);
    while (query.next()) {
        if (query.at() == exactRow - 1) {
            if(exactTable == "Owners") {
                qDebug() << query.value(0).toString();
                emit throwIdUser(query.value(0).toString());
                qDebug() << query.value(1).toString();
                emit throwLastName(query.value(1).toString());
                qDebug() << query.value(2).toString();
                emit throwFirstName(query.value(2).toString());
            }
            if(exactTable == "Pets") {
                qDebug() << query.value(0).toString();
                emit throwPetPass(query.value(0).toString());
                qDebug() << query.value(1).toString();
                emit throwOwnerPass(query.value(1).toString());
                qDebug() << query.value(2).toString();
                emit throwName(query.value(2).toString());
                qDebug() << query.value(3).toString();
                emit throwWeight(query.value(3).toString());
            }
        }
        rowCount++;
    }
    db.close();
    emit enableButtons(true);
}
