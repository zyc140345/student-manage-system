#include "insertsinglestu.h"
#include "ui_insertsinglestu.h"
#include <QRegularExpressionValidator>

InsertSingleStu::InsertSingleStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertSingleStu)
{
    // 构造函数
    ui->setupUi(this);

    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint); // 禁用最大化按钮
    setFixedSize(this->width(), this->height()); // 禁止调节窗体大小
    ui->id_lineEdit->setValidator(
                new QRegularExpressionValidator(QRegularExpression("^[0-9]*[1-9][0-9]*$"))); // 限制学号只能输入正整数
    ui->age_lineEdit->setValidator(
                new QRegularExpressionValidator(QRegularExpression("^[0-9]*[1-9][0-9]*$"))); // 限制年龄只能输入正整数
    ui->telephone_lineEdit->setValidator(
                new QRegularExpressionValidator(QRegularExpression("^[0-9]*[1-9][0-9]*$"))); // 限制电话只能输入正整数
}

InsertSingleStu::~InsertSingleStu()
{
    // 析构函数
    delete ui;
}

void InsertSingleStu::iniAsStuEditDialog(QString stuId, QString sex) {
    // 初始化为编辑学生信息对话框
    ui->id_lineEdit->setText(stuId);
    ui->id_lineEdit->setEnabled(false);
    ui->name_lineEdit->setPlaceholderText("不修改请留空");
    if (sex == "男") {
        ui->select_man->setChecked(true);
    } else {
        ui->select_woman->setChecked(true);
    }
    ui->age_lineEdit->setPlaceholderText("不修改请留空");
    ui->telephone_lineEdit->setPlaceholderText("不修改请留空");
}

void InsertSingleStu::acceptAndReturnValue() {
    // 输入完成后传值给主界面并关闭输入对话框
    QString sex;
    if (ui->select_man->isChecked()) {
        sex = QString::fromStdString("男");
    } else {
        sex = QString::fromStdString("女");
    }
    emit sendStuData(ui->id_lineEdit->text(),
                     ui->name_lineEdit->text(),
                     sex,
                     ui->age_lineEdit->text(),
                     ui->telephone_lineEdit->text());
    close();
}
