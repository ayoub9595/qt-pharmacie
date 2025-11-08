#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "Databse.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , database(nullptr)
{
    ui->setupUi(this);

    // Créez database APRÈS setupUi
    database = new XamppDatabase(this);

    connect(database, &XamppDatabase::connectionStatusChanged,
            this, &MainWindow::onConnectionStatusChanged);
    connect(database, &XamppDatabase::errorOccurred,
            this, &MainWindow::onDatabaseError);

    setupDatabase();
}

MainWindow::~MainWindow()
{
    delete database;
    delete ui;
}

void MainWindow::setupDatabase()
{
    if (database->connectToDatabase("localhost", "TestQt", "root", "")) {
        qDebug() << "Connection established";
    }
}



void MainWindow::onConnectionStatusChanged(bool connected)
{
    if (connected) {
        qDebug() << "✓ Connection status: Connected";
    } else {
        qDebug() << "✗ Connection status: Disconnected";
    }
}

void MainWindow::onDatabaseError(const QString &error)
{
    QMessageBox::critical(this, "Database Error", error);
}

void MainWindow::on_loginButton_clicked()
{
    // Récupérer les valeurs des champs
    QString email = ui->emailLineEdit->text();
    QString password = ui->passwordLineEdit->text();




    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs !");
        return;
    }


    if (!email.contains("@")) {
        QMessageBox::warning(this, "Erreur", "Email invalide ! Il doit contenir @");
        return;
    }


    if (password.length() < 6) {
        QMessageBox::warning(this, "Erreur", "Le mot de passe doit contenir au moins 6 caractères !");
        return;
    }


    if (email == "admin@test.com" && password == "123456") {
        QMessageBox::information(this, "Succès",
                                 "Connexion réussie !\n\nBienvenue " + email);

        // Vérifier si "Se souvenir de moi" est coché
        if (ui->rememberCheckBox->isChecked()) {
            qDebug() << "L'utilisateur veut être mémorisé";
        }

        // TODO: Ici vous pouvez charger l'interface principale

    } else {
        QMessageBox::critical(this, "Échec",
                              "Email ou mot de passe incorrect !\n\nEssayez:\nEmail: admin@test.com\nMot de passe: 123456");
    }
}

