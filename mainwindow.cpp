#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <libguile.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->verticalLayout->insertWidget(0, &canvas);
    scm_init_guile();
    connect(ui->schemeButton, &QPushButton::clicked, this, &MainWindow::evalScript);
    QString initialСode("(set! *random-state* (random-state-from-platform)   ; Random seed for PRNG\n"
                        "(define cell-update ()\n"
                        "  (random 4))\n");
    ui->schemeCode->setText(initialСode);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::evalScript()
{
    char* rvalue;
    SCM res;
    res = scm_c_eval_string(ui->schemeCode->toPlainText().toStdString().c_str());
    rvalue = scm_to_utf8_stringn(res, NULL);
    qDebug(rvalue);
}
