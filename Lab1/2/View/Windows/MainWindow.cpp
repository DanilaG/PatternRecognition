#include "MainWindow.h"

#include <QFile>
#include <QJsonObject>
#include <iostream>

#include "Logic/Logic.h"
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

    QJsonObject json({{"Attempt", ui->AttemptSpinBox->value()},
                      {"Radius", ui->RadiusSpinBox->value()}});
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
    ui->RadiusSpinBox->setValue(json["Radius"].toInt());

    config.close();
    return true;
}

void MainWindow::on_CountButton_clicked() {
    const unsigned int number_attempts = ui->AttemptSpinBox->value();
    const double radius = ui->RadiusSpinBox->value();

    const double probability = calculate_probability({{0, 0}, radius}, number_attempts);
    ui->AnswerLabel->setNum(probability);

    save_config();
}
