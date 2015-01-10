#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::SetLabelText(QString text, QString texttwo)
{
   ui->label2->setText(text);
   ui->label3->setText(texttwo);
}
