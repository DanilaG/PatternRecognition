#include "MainWindow.h"

#include <QFile>
#include <QJsonObject>
#include <iostream>

#include "Logic/Logic.h"
#include "ui_MainWindow.h"

#define SET_ANS(NUMBER, RADIUS)                                       \
    {                                                                 \
        const unsigned int number_attempts =                          \
            ui->Attempt##NUMBER##SpinBox->value();                    \
        const double probability =                                    \
            calculate_probability({{0, 0}, RADIUS}, number_attempts); \
        ui->Ans##NUMBER##Lable->setNum(probability);                  \
        ui->Misc##NUMBER##Lable->setNum(analytic_ans - probability);  \
    }

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    load_config();
    ui->AnalyticAnsLabel->setNum(analytic_ans);
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::save_config() {
    QFile config(config_file_name);
    if (!config.open(QIODevice::WriteOnly)) {
        std::cerr << "Failed to save configs!" << std::endl;
        return false;
    }

    QJsonObject json({{"Attempt1", ui->Attempt1SpinBox->value()},
                      {"Attempt2", ui->Attempt2SpinBox->value()},
                      {"Attempt3", ui->Attempt3SpinBox->value()},
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
    ui->Attempt1SpinBox->setValue(json["Attempt1"].toInt());
    ui->Attempt2SpinBox->setValue(json["Attempt2"].toInt());
    ui->Attempt3SpinBox->setValue(json["Attempt3"].toInt());
    ui->RadiusSpinBox->setValue(json["Radius"].toInt());

    config.close();
    return true;
}

void MainWindow::on_CountButton_clicked() {
    const double radius = ui->RadiusSpinBox->value();

    SET_ANS(1, radius);
    SET_ANS(2, radius);
    SET_ANS(3, radius);

    save_config();
}
