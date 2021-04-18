#include "insertsinglesubject.h"
#include "ui_insertsinglesubject.h"
#include <QRegularExpressionValidator>

InsertSingleSubject::InsertSingleSubject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertSingleSubject)
{
    // 构造函数
    ui->setupUi(this);

    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint); // 禁用最大化按钮
    setFixedSize(this->width(), this->height()); // 禁止调节窗体大小
    ui->credit_lineEdit->setValidator(
                new QRegularExpressionValidator(QRegularExpression("^[0-9]*[1-9][0-9]*$"))); // 限制学分数只能输入正整数
    ui->score_lineEdit->setValidator(
                new QRegularExpressionValidator(QRegularExpression("^[0-9]*[1-9][0-9]*$"))); // 限制成绩只能输入正整数
}

InsertSingleSubject::~InsertSingleSubject()
{
    // 析构函数
    delete ui;
}

void InsertSingleSubject::iniAsEditSubDialog(QString subName) {
    // 初始化为编辑课程信息对话框
    ui->name_lineEdit->setText(subName);
    ui->name_lineEdit->setEnabled(false);
    ui->credit_lineEdit->setPlaceholderText("不修改请留空！");
    ui->score_lineEdit->setPlaceholderText("不修改请留空！");
}

void InsertSingleSubject::acceptAndReturnValue() {
    // 输入完成后传值给主界面并关闭输入对话框
    emit sendSubData(ui->name_lineEdit->text(),
                     ui->credit_lineEdit->text(),
                     ui->score_lineEdit->text());
    close();
}
