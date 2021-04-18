#include "showsomething.h"
#include "ui_showsomething.h"

ShowSomething::ShowSomething(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowSomething)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint); // 禁用最大化按钮
    setFixedSize(this->width(), this->height()); // 禁止调节窗体大小
}

ShowSomething::~ShowSomething()
{
    delete ui;
}

void ShowSomething::setInfo(QString s) {
    // 设置标签文本
    ui->info->setText(s);
}
