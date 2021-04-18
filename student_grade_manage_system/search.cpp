#include "search.h"
#include "ui_search.h"

Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint); // 禁用最大化按钮
    setFixedSize(this->width(), this->height()); // 禁止调节窗体大小
}

Search::~Search()
{
    delete ui;
}

void Search::setKeyLabelText(QString text) {
    // 设置标签文本
    ui->key_label->setText(text);
}

void Search::acceptAndReturnValue() {
    // 输入完成后传值给主界面并关闭输入对话框
    emit sendKey(ui->key_lineEdit->text());
    close();
}
