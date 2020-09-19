#include "MainWindow.h"

#include <QFile>
#include <QJsonObject>
#include <iostream>

#include "Logic/ProbabilityCounter.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    load_config();
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::save_config() {
    QFile config(config_file_name);
    if (!config.open(QIODevice::WriteOnly)) {
        std::cerr << "Failed to save configs!" << std::endl;
        return false;
    }

    QJsonObject json({{"Attempt", ui->AttemptSpinBox->value()}});
    config.write(QJsonDocument(json).toJson(QJsonDocument::Indented));

    config.close();
    return true;
}

bool MainWindow::load_config() {
    QFile config(config_file_name);
    if (!config.open(QIODevice::ReadOnly)) {
        std::cerr << "Failed to load configs!" << std::endl;
        return false;
    }

    QJsonObject json = QJsonDocument::fromJson(config.readAll()).object();
    ui->AttemptSpinBox->setValue(json["Attempt"].toInt());

    config.close();
    return true;
}

void MainWindow::on_CountButton_clicked() {
    const unsigned int digit_capacity = 4;
    const unsigned int number_attempts = ui->AttemptSpinBox->value();

    ui->UniqueAnsLabel->setNum(
        UniqProbabilityCounter(digit_capacity).count(number_attempts));
    ui->PairAnsLabel->setNum(
        PairProbabilityCounter(digit_capacity).count(number_attempts));
    ui->DoublePairAnsLabel->setNum(
        DoublePairProbabilityCounter(digit_capacity).count(number_attempts));
    ui->TripletAnsLabel->setNum(
        TripletProbabilityCounter(digit_capacity).count(number_attempts));

    save_config();
}
