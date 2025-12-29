#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "systemmonitor.h"
#include "utils/formatters.h"
#include "widgets/infocard.h"
#include <iostream>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InfoCard* infocard = new InfoCard("CPU", this);
    infocard->setValue("99%");
    infocard->setPercentage(99);
    infocard->setSubtitle("Processor activity");
    setCentralWidget(infocard);
}

MainWindow::~MainWindow()
{
    delete ui;
}
