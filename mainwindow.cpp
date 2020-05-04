#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>
#include <QDir>
#include <QMessageBox>
#include <QValidator>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->rB_Pets, &QRadioButton::clicked, ui->sA_Pets, &QScrollArea::show);
    connect(ui->rB_Owners, &QRadioButton::clicked, ui->sA_Owners, &QScrollArea::show);
    connect(ui->rB_Owners, &QPushButton::clicked, this, &MainWindow::setTableOwners);
    connect(ui->rB_Pets, &QPushButton::clicked, this, &MainWindow::setTablePets);
    connect(ui->rB_Pets, &QRadioButton::clicked, ui->sA_Owners, &QScrollArea::hide);
    connect(ui->rB_Owners, &QRadioButton::clicked, ui->sA_Pets, &QScrollArea::hide);

    dbm = new Db(this);
    connect(dbm, &Db::throwPath, ui->le_path, &QLineEdit::setText);

    connect(ui->rB_Pets, &QRadioButton::clicked, dbm, &Db::check);
    connect(ui->rB_Owners, &QRadioButton::clicked, dbm, &Db::check);

    connect(ui->pB_save, &QPushButton::clicked, this, &MainWindow::initUpdateRow);
    connect(ui->pB_remove, &QPushButton::clicked, this, &MainWindow::initRemoveRow);
    connect(ui->pB_add, &QPushButton::clicked, this, &MainWindow::initAddRow);

    connect(ui->pB_noteToLeft, &QPushButton::clicked, dbm, &Db::prev);
    connect(ui->pB_noteToRight, &QPushButton::clicked, dbm, &Db::next);

    connect(ui->pB_noteToLeft, &QPushButton::clicked, dbm, &Db::check);
    connect(ui->pB_noteToRight, &QPushButton::clicked, dbm, &Db::check);

    connect(dbm, &Db::throwExactRow, ui->label_note, &QLabel::setText);

    connect(dbm, &Db::throwIdUser, ui->lineEdit_ID, &QLineEdit::setText);
    connect(dbm, &Db::throwLastName, ui->lineEdit_Last, &QLineEdit::setText);
    connect(dbm, &Db::throwFirstName, ui->lineEdit_First, &QLineEdit::setText);

    connect(dbm, &Db::throwPetPass, ui->lE_PetPass, &QLineEdit::setText);
    connect(dbm, &Db::throwOwnerPass, ui->lE_OwnerPass, &QLineEdit::setText);
    connect(dbm, &Db::throwName, ui->lE_Name, &QLineEdit::setText);
    connect(dbm, &Db::throwWeight, ui->lE_Weight, &QLineEdit::setText);

    ui->lE_OwnerPass->setValidator(new QIntValidator());
    ui->lE_Weight->setValidator(new QIntValidator());
    ui->lineEdit_ID->setValidator(new QIntValidator());

    ui->sA_Pets->hide();
    ui->sA_Owners->hide();

    dbm->checkDbfile(this->path);

    ui->rB_Owners->click();

    connect(ui->lE_PetPass, &QLineEdit::textChanged, this, &MainWindow::setDisabledSave);
    connect(ui->lineEdit_ID, &QLineEdit::textChanged, this, &MainWindow::setDisabledSave);
    connect(dbm, &Db::enableButtons, ui->pB_save, &QPushButton::setEnabled);

    connect(ui->pB_Exec, &QPushButton::clicked, this, &MainWindow::initExecQuery);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setTableOwners() {
    dbm->exactTable = "Owners";
    qDebug() << "Current table: Owners";
}

void MainWindow::setTablePets() {
    dbm->exactTable = "Pets";
    qDebug() << "Current table: Pets";
}

void MainWindow::initRemoveRow() {
    if (dbm->exactTable == "Owners") {
        dbm->removeRow(ui->lineEdit_ID->text());
    }
    if (dbm->exactTable == "Pets") {
        dbm->removeRow(ui->lE_PetPass->text());
    }
}

void MainWindow::initAddRow() {
    if (dbm->exactTable == "Owners") {
        dbm->addRowOwners(ui->lineEdit_ID->text().toInt(), ui->lineEdit_Last->text(), ui->lineEdit_First->text());
    }
    if (dbm->exactTable == "Pets") {
        dbm->addRowPets(ui->lE_PetPass->text(), ui->lE_OwnerPass->text().toInt(), ui->lE_Name->text(), ui->lE_Weight->text().toInt());
    }
}

void MainWindow::initUpdateRow() {
    if (dbm->exactTable == "Owners") {
        dbm->updateRowOwners(ui->lineEdit_ID->text().toInt(), ui->lineEdit_Last->text(), ui->lineEdit_First->text());
    }
    if (dbm->exactTable == "Pets") {
        dbm->updateRowPets(ui->lE_PetPass->text(), ui->lE_OwnerPass->text().toInt(), ui->lE_Name->text(), ui->lE_Weight->text().toInt());
    }
}

void MainWindow::setDisabledSave() {
    ui->pB_save->setDisabled(true);
}

void MainWindow::initExecQuery() {
    dbm->db.open();
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery query;
    query.exec(ui->comboBox->currentText());
    model->setQuery(query);
    ui->tableView->setModel(model);
    dbm->db.close();
}
