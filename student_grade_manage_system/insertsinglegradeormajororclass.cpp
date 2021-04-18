#include "insertsinglegradeormajororclass.h"
#include "ui_insertsinglegradeormajororclass.h"
#include <QRegularExpressionValidator>

InsertSingleGradeOrMajorOrClass::InsertSingleGradeOrMajorOrClass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertSingleGradeOrMajorOrClass)
{
    // 构造函数
    ui->setupUi(this);

    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint); // 禁用最大化按钮
    setFixedSize(this->width(), this->height()); // 禁止调节窗体大小
}

InsertSingleGradeOrMajorOrClass::~InsertSingleGradeOrMajorOrClass()
{
    // 析构函数
    delete ui;
}


// 初始化输入新建信息对话框
void InsertSingleGradeOrMajorOrClass::iniAsGradeDialog() {
    // 初始化为输入年级编号对话框
    setWindowTitle(QString::fromStdString("请输入年级编号"));
    ui->label->setText(QString::fromStdString("年级编号"));
    ui->lineEdit->setValidator(
                new QRegularExpressionValidator(QRegularExpression("^[0-9]*[1-9][0-9]*$"))); // 限制年级编号只能输入正整数
    dt = 0;
}

void InsertSingleGradeOrMajorOrClass::iniAsMajorDialog() {
    // 初始化为输入专业名称对话框
    setWindowTitle(QString::fromStdString("请输入专业名称"));
    ui->label->setText(QString::fromStdString("专业名称"));
    dt = 1;
}

void InsertSingleGradeOrMajorOrClass::iniAsClassDialog() {
    // 初始化为输入班级名称对话框
    setWindowTitle(QString::fromStdString("请输入班级名称"));
    ui->label->setText(QString::fromStdString("班级名称"));
    ui->lineEdit->setValidator(
                new QRegularExpressionValidator(QRegularExpression("^[0-9]*[1-9][0-9]*$"))); // 限制班级名称只能输入正整数
    dt = 2;
}

void InsertSingleGradeOrMajorOrClass::acceptAndReturnValue() {
    // 输入完成后传值给主界面并关闭输入对话框
    switch (dt) {
        case 0:
            emit sendGradeData(ui->lineEdit->text());
            break;
        case 1:
            emit sendMajorData(ui->lineEdit->text());
            break;
        case 2:
            emit sendClassData(ui->lineEdit->text());
            break;
    }
    close();
}
