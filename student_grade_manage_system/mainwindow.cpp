#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "studatabase.h"
#include <vector>
#include <iostream>

extern Institute database;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // 构造函数
    ui->setupUi(this);

    // 默认展示显示年级界面
    ui->select_tool->setCurrentIndex(0);
    ui->edit->setEnabled(false);
    iniGradeList();

    ui->info_list->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置信息列表为不可编辑
    ui->info_list->setSelectionBehavior(QTableWidget::SelectRows); // 设置信息列表一次选择一整行
    ui->info_list->setSelectionMode(QTableWidget::SingleSelection); // 设置信息列表不能同时选中多行
}

MainWindow::~MainWindow()
{
    // 析构函数
    delete ui;
}


// 刷新界面
void MainWindow::changeInfoListType(int tabIndex) {
    // 当用户切换标签页时初始化界面
    switch (tabIndex) {
        case 0: // 初始化为显示年级界面
            iniGradeList();
            ui->insert->setText("添加年级");
            ui->show_detail->setDisabled(false);
            ui->edit->setEnabled(false);
            break;
        case 1: // 初始化为显示专业界面
            iniMajorList();
            ui->insert->setText("添加专业");
            ui->show_detail->setDisabled(false);
            ui->edit->setEnabled(false);
            break;
        case 2: // 初始化为显示班级界面
            iniClassList();
            ui->insert->setText("添加班级");
            ui->show_detail->setDisabled(false);
            ui->edit->setEnabled(false);
            break;
        case 3: // 初始化为显示学生界面
            iniStuList();
            ui->insert->setText("添加学生");
            ui->show_detail->setDisabled(false);
            ui->edit->setEnabled(true);
            break;
        case 4: // 初始化为显示课程界面
            iniSubList();
            ui->insert->setText("添加课程");
            ui->show_detail->setDisabled(true);
            ui->edit->setEnabled(true);
            break;
    }
}

void MainWindow::refreshMajorList() {
    // 根据所选下拉列表项刷新专业列表

    // 清空信息列表
    ui->info_list->clear();
    ui->info_list->setRowCount(0);

    // 添加表头
    ui->info_list->setHorizontalHeaderItem(0, new QTableWidgetItem("专业名称"));

    // 刷新列表
    auto pg = (Institute::grade_pos) database.findPos(ui->select_grade_tab1->currentText().toInt());
    int currentRow = 0;
    for (auto pm = pg->element.firstMajor(); pm; pm = pm->next, ++currentRow) {
        ui->info_list->insertRow(currentRow);
        ui->info_list->setItem(currentRow, 0, new QTableWidgetItem(QString::fromStdString(pm->element.name)));
    }
}

void MainWindow::refreshClassList() {
    // 根据所选下拉列表项刷新班级列表

    // 清空信息列表
    ui->info_list->clear();
    ui->info_list->setRowCount(0);

    // 添加表头
    ui->info_list->setHorizontalHeaderItem(0, new QTableWidgetItem("班级名称"));

    // 刷新列表
    auto pm = (Institute::major_pos) database.findPos(ui->select_grade_tab2->currentText().toInt(),
                                                      ui->select_major_tab2->currentText().toStdString());
    int currentRow = 0;
    for (auto pc = pm->element.firstClass(); pc; pc = pc->next, ++currentRow) {
        ui->info_list->insertRow(currentRow);
        ui->info_list->setItem(currentRow, 0, new QTableWidgetItem(QString::number(pc->element.id)));
    }
}

void MainWindow::refreshStuList() {
    // 根据所选下拉列表项刷新学生列表

    // 清空信息列表
    ui->info_list->clear();
    ui->info_list->setRowCount(0);

    // 添加表头
    std::vector<std::string> headerText {"学号", "姓名", "性别", "年龄", "电话"};
    for (auto i = 0; i < 5; ++i)
        ui->info_list->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(headerText[i])));

    // 刷新列表
    for (auto i = 0; i < 5; ++i)
        ui->info_list->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(headerText[i])));
    auto pc = (Institute::class_pos) database.findPos(ui->select_grade_tab3->currentText().toInt(),
                                                      ui->select_major_tab3->currentText().toStdString(),
                                                      ui->select_class_tab3->currentText().toInt());
    int currentRow = 0;
    for (auto ps = pc->element.firstStudent(); ps; ps = ps->next, ++currentRow) {
        ui->info_list->insertRow(currentRow);
        ui->info_list->setItem(currentRow, 0, new QTableWidgetItem(QString::fromStdString(ps->element.id)));
        ui->info_list->setItem(currentRow, 1, new QTableWidgetItem(QString::fromStdString(ps->element.name)));
        if (ps->element.sex) {
            ui->info_list->setItem(currentRow, 2, new QTableWidgetItem(QString::fromStdString("男")));
        } else {
            ui->info_list->setItem(currentRow, 2, new QTableWidgetItem(QString::fromStdString("女")));
        }
        ui->info_list->setItem(currentRow, 3, new QTableWidgetItem(QString::number(ps->element.age)));
        ui->info_list->setItem(currentRow, 4, new QTableWidgetItem(QString::fromStdString(ps->element.telephone)));
    }
}

void MainWindow::refreshSubList() {
    // 根据所选下拉列表项刷新课程列表

    // 清空信息列表
    ui->info_list->clear();
    ui->info_list->setRowCount(0);

    // 添加表头
    std::vector<std::string> headerText {"课程名称", "学分数", "成绩"};
    for (auto i = 0; i < 3; ++i)
        ui->info_list->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(headerText[i])));

    // 刷新列表
    auto pStu = (Institute::stu_pos) database.findPos(ui->select_grade_tab4->currentText().toInt(),
                                                      ui->select_major_tab4->currentText().toStdString(),
                                                      ui->select_class_tab4->currentText().toInt(),
                                                      ui->select_stu_tab4->currentText().toStdString());
    int currentRow = 0;
    for (auto pSub = pStu->element.firstSubject(); pSub; pSub = pSub->next, ++currentRow) {
        ui->info_list->insertRow(currentRow);
        ui->info_list->setItem(currentRow, 0, new QTableWidgetItem(QString::fromStdString(pSub->element.name)));
        ui->info_list->setItem(currentRow, 1, new QTableWidgetItem(QString::number(pSub->element.credit)));
        ui->info_list->setItem(currentRow, 2, new QTableWidgetItem(QString::number(pSub->element.score)));
    }
}


// 响应按钮事件
void MainWindow::showInsertDialog() {
    // 当添加按钮被点击时，显示添加界面
    int index = ui->select_tool->currentIndex();
    if (index == 0) {
        // 初始化添加年级界面
        InsertSingleGradeOrMajorOrClass insertGradeDialog;
        insertGradeDialog.iniAsGradeDialog();
        connect(&insertGradeDialog,
                &InsertSingleGradeOrMajorOrClass::sendGradeData,
                this,
                &MainWindow::addGradeData);
        insertGradeDialog.exec();
    } else if (index == 1) {
        // 初始化添加专业界面
        if (ui->select_grade_tab1->currentIndex() == -1) {
            // 添加操作必须指定添加位置
            ShowSomething warnDialog;
            warnDialog.setInfo(QString::fromStdString("请先选择年级！"));
            warnDialog.exec();
        } else {
            InsertSingleGradeOrMajorOrClass insertMajorDialog;
            insertMajorDialog.iniAsMajorDialog();
            connect(&insertMajorDialog,
                    &InsertSingleGradeOrMajorOrClass::sendMajorData,
                    this,
                    &MainWindow::addMajorData);
            insertMajorDialog.exec();
        }
    } else if (index == 2) {
        // 初始化添加班级界面
        if (ui->select_grade_tab2->currentIndex() == -1
                || ui->select_major_tab2->currentIndex() == -1) {
            // 添加操作必须指定添加位置
            ShowSomething warnDialog;
            warnDialog.setInfo(QString::fromStdString("请先选择年级和专业！"));
            warnDialog.exec();
        } else {
            InsertSingleGradeOrMajorOrClass insertClassDialog;
            insertClassDialog.iniAsClassDialog();
            connect(&insertClassDialog,
                    &InsertSingleGradeOrMajorOrClass::sendClassData,
                    this,
                    &MainWindow::addClassData);
            insertClassDialog.exec();
        }
    } else if (index == 3) {
        // 初始化添加学生界面
        if (ui->select_grade_tab3->currentIndex() == -1
                || ui->select_major_tab3->currentIndex() == -1
                || ui->select_class_tab3->currentIndex() == -1) {
            // 添加操作必须指定添加位置
            ShowSomething warnDialog;
            warnDialog.setInfo(QString::fromStdString("请先选择年级、专业和班级！"));
            warnDialog.exec();
        } else {
            InsertSingleStu insertStuDialog;
            connect(&insertStuDialog,
                    &InsertSingleStu::sendStuData,
                    this,
                    &MainWindow::addStuData);
            insertStuDialog.exec();
        }
    } else if (index == 4) {
        // 初始化添加课程界面
        if (ui->select_grade_tab4->currentIndex() == -1
                || ui->select_major_tab4->currentIndex() == -1
                || ui->select_class_tab4->currentIndex() == -1
                || ui->select_stu_tab4->currentIndex() == -1) {
            // 添加操作必须指定添加位置
            ShowSomething warnDialog;
            warnDialog.setInfo(QString::fromStdString("请先选择年级、专业、班级和学生！"));
            warnDialog.exec();
        } else {
            InsertSingleSubject insertSubDialog;
            connect(&insertSubDialog,
                    &InsertSingleSubject::sendSubData,
                    this,
                    &MainWindow::addSubData);
            insertSubDialog.exec();
        }
    }
}

void MainWindow::showEditDialog() {
    // 显示学生信息界面
    auto selectedItems = ui->info_list->selectedItems();
    if (selectedItems.empty()) {
        // 必须选中某行才能执行编辑操作
        ShowSomething warnDialog;
        warnDialog.setInfo(QString::fromStdString("请先选中一行！"));
        warnDialog.exec();
    } else {
        auto index = ui->select_tool->currentIndex();
        if (index == 3) {
            // 初始化编辑学生信息界面
            InsertSingleStu editStuDialog;
            auto stuId = selectedItems.at(0)->text();
            auto sex = selectedItems.at(2)->text();
            editStuDialog.iniAsStuEditDialog(stuId, sex);
            connect(&editStuDialog, &InsertSingleStu::sendStuData, this, &MainWindow::updateStuData);
            editStuDialog.exec();
        } else if (index == 4) {
            // 初始化编辑课程界面
            InsertSingleSubject editSubDialog;
            auto subName = selectedItems.at(0)->text();
            editSubDialog.iniAsEditSubDialog(subName);
            connect(&editSubDialog, &InsertSingleSubject::sendSubData, this, &MainWindow::updateSubData);
            editSubDialog.exec();
        }

    }
}

void MainWindow::showSearchDialog() {
    // 当查找按钮被点击时，显示查找界面
    Search searchDialog;
    switch (ui->select_tool->currentIndex()) {
        case 0: // 查找年级
            searchDialog.setWindowTitle(QString::fromStdString("请输入年级编号"));
            searchDialog.setKeyLabelText(QString::fromStdString("年级编号"));
            break;
        case 1: // 查找专业
            searchDialog.setWindowTitle(QString::fromStdString("请输入专业名称"));
            searchDialog.setKeyLabelText(QString::fromStdString("专业名称"));
            break;
        case 2: // 查找班级
            searchDialog.setWindowTitle(QString::fromStdString("请输入班级名称"));
            searchDialog.setKeyLabelText(QString::fromStdString("班级名称"));
            break;
        case 3: // 查找学号
            searchDialog.setWindowTitle(QString::fromStdString("请输入学号或姓名"));
            searchDialog.setKeyLabelText(QString::fromStdString("学号或姓名"));
            break;
        case 4: // 查找课程
            searchDialog.setWindowTitle(QString::fromStdString("请输入课程名称"));
            searchDialog.setKeyLabelText(QString::fromStdString("课程名称"));
            break;
    }
    connect(&searchDialog, &Search::sendKey, this, &MainWindow::showSearchResult);
    searchDialog.exec();
}


// 执行添加操作后更新信息列表及数据库数据
void MainWindow::addGradeData(QString year) {
    // 添加年级信息
    if (year == "") {
        // 年级编号不得为空
        ShowSomething warnDialog;
        warnDialog.setInfo("年级编号不得为空！");
        warnDialog.exec();
    } else {
        auto pg = (Institute::grade_pos) database.findPos(year.toUInt());
        if (pg && pg->element.year == year.toInt()) {
            // 年级编号不得重复
            ShowSomething warnDialog;
            warnDialog.setInfo("当前年级已存在！");
            warnDialog.exec();
        } else {
            int currentRow = ui->info_list->rowCount(); // 获取当前信息列表行数

            // 将新记录添加到表尾
            ui->info_list->insertRow(currentRow);
            ui->info_list->setItem(currentRow, 0, new QTableWidgetItem(year));

            // 更新数据库
            Grade temp;
            temp.year = year.toInt();
            database.insert(temp);
        }
    }
}

void MainWindow::addMajorData(QString majorName) {
    // 添加专业信息
    if (majorName == "") {
        // 专业名称不得为空
        ShowSomething warnDialog;
        warnDialog.setInfo("专业名称不得为空！");
        warnDialog.exec();
    } else {
        auto pm = (Institute::major_pos) database.findPos(ui->select_grade_tab1->currentText().toInt(),
                                                          majorName.toStdString());
        if (pm && pm->element.name == majorName.toStdString()) {
            // 专业名称不得重复
            ShowSomething warnDialog;
            warnDialog.setInfo("当前专业已存在！");
            warnDialog.exec();
        } else {
            int currentRow = ui->info_list->rowCount(); // 获取当前信息列表行数

            // 将新记录添加到表尾
            ui->info_list->insertRow(currentRow);
            ui->info_list->setItem(currentRow, 0, new QTableWidgetItem(majorName));

            // 更新数据库
            Major temp;
            temp.name = majorName.toStdString();
            database.insert(ui->select_grade_tab1->currentText().toInt(), temp);
        }
    }
}

void MainWindow::addClassData(QString classId) {
    // 添加班级信息
    if (classId == "") {
        // 班级名称不得为空
        ShowSomething warnDialog;
        warnDialog.setInfo("班级名称不得为空！");
        warnDialog.exec();
    } else {
        auto pc = (Institute::class_pos) database.findPos(ui->select_grade_tab2->currentText().toInt(),
                                                          ui->select_major_tab2->currentText().toStdString(),
                                                          classId.toInt());
        if (pc && pc->element.id == classId.toInt()) {
            // 班级名称不得重复
            ShowSomething warnDialog;
            warnDialog.setInfo("当前班级已存在！");
            warnDialog.exec();
        } else {
            int currentRow = ui->info_list->rowCount(); // 获取当前信息列表行数

            // 将新记录添加到表尾
            ui->info_list->insertRow(currentRow);
            ui->info_list->setItem(currentRow, 0, new QTableWidgetItem(classId));

            // 更新数据库
            Class temp;
            temp.id = classId.toInt();
            database.insert(ui->select_grade_tab2->currentText().toInt(),
                            ui->select_major_tab2->currentText().toStdString(),
                            temp);
        }
    }
}

void MainWindow::addStuData(QString stuId,
                               QString stuName,
                               QString sex,
                               QString age,
                               QString telephone) {
    // 添加学生信息
    if (stuId == "" || stuName == "") {
        // 学号和姓名不得为空
        ShowSomething warnDialog;
        warnDialog.setInfo("学号和姓名不得为空！");
        warnDialog.exec();
    } else {
        auto pStu = (Institute::stu_pos) database.findPos(ui->select_grade_tab3->currentText().toInt(),
                                                        ui->select_major_tab3->currentText().toStdString(),
                                                        ui->select_class_tab3->currentText().toInt(),
                                                        stuId.toStdString());
        if (pStu && pStu->element.id == stuId.toStdString()) {
            // 学号不得重复
            ShowSomething warnDialog;
            warnDialog.setInfo("当前学号已存在！");
            warnDialog.exec();
        } else {
            int currentRow = ui->info_list->rowCount(); // 获取当前信息列表行数

            // 将新记录添加到表尾
            ui->info_list->insertRow(currentRow);
            ui->info_list->setItem(currentRow, 0, new QTableWidgetItem(stuId));
            ui->info_list->setItem(currentRow, 1, new QTableWidgetItem(stuName));
            ui->info_list->setItem(currentRow, 2, new QTableWidgetItem(sex));
            ui->info_list->setItem(currentRow, 3, new QTableWidgetItem(age));
            ui->info_list->setItem(currentRow, 4, new QTableWidgetItem(telephone));

            // 更新数据库
            Student temp;
            temp.id = stuId.toStdString();
            temp.name = stuName.toStdString();
            if (sex == "男") {
                temp.sex = true;
            } else if (sex == "女") {
                temp.sex = false;
            } else {
                std::cerr << "Not a sex!\n";
                std::terminate();
            }
            temp.age = age.toInt();
            temp.telephone = telephone.toStdString();
            database.insert(ui->select_grade_tab3->currentText().toInt(),
                            ui->select_major_tab3->currentText().toStdString(),
                            ui->select_class_tab3->currentText().toInt(),
                            temp);
        }
    }
}

void MainWindow::addSubData(QString name, QString credit, QString score) {
    // 添加课程信息
    if (name == "") {
        // 课程名称不得为空
        ShowSomething warnDialog;
        warnDialog.setInfo("课程名称不得为空！");
        warnDialog.exec();
    } else {
        auto pSub = (Institute::sub_pos) database.findPos(ui->select_grade_tab3->currentText().toInt(),
                                                          ui->select_major_tab3->currentText().toStdString(),
                                                          ui->select_class_tab3->currentText().toInt(),
                                                          ui->select_stu_tab4->currentText().toStdString(),
                                                          name.toStdString());
        if (pSub && pSub->element.name == name.toStdString()) {
            // 课程名称不得重复
            ShowSomething warnDialog;
            warnDialog.setInfo("当前课程已存在！");
            warnDialog.exec();
        } else {
            int currentRow = ui->info_list->rowCount(); // 获取当前信息列表行数

            // 将新记录添加到表尾
            ui->info_list->insertRow(currentRow);
            ui->info_list->setItem(currentRow, 0, new QTableWidgetItem(name));
            ui->info_list->setItem(currentRow, 1, new QTableWidgetItem(credit));
            ui->info_list->setItem(currentRow, 2, new QTableWidgetItem(score));

            // 更新数据库
            Subject temp;
            temp.name = name.toStdString();
            temp.credit = credit.toInt();
            temp.score = score.toInt();

            database.insert(ui->select_grade_tab3->currentText().toInt(),
                            ui->select_major_tab3->currentText().toStdString(),
                            ui->select_class_tab3->currentText().toInt(),
                            ui->select_stu_tab4->currentText().toStdString(),
                            temp);
        }
    }
}


// 执行编辑操作后更新信息列表及数据库数据
void MainWindow::updateStuData(QString stuId,
                   QString stuName,
                   QString sex,
                   QString age,
                   QString telephone) {
    // 更新学生数据
    // 更新数据库及信息列表
    auto pStu = (Institute::stu_pos) database.findPos(ui->select_grade_tab3->currentText().toInt(),
                                                      ui->select_major_tab3->currentText().toStdString(),
                                                      ui->select_class_tab3->currentText().toInt(),
                                                      stuId.toStdString());
    auto row = ui->info_list->currentRow();
    if (stuName != "") {
        // 修改姓名
        pStu->element.name = stuName.toStdString();
        ui->info_list->setItem(row, 1, new QTableWidgetItem(stuName));
    }
    if (sex != ui->info_list->item(row, 2)->text()) {
        // 修改性别
        pStu->element.sex = sex == "男" ? "男" : "女";
        ui->info_list->setItem(row, 2, new QTableWidgetItem(sex));
    }
    if (age != "") {
        // 修改年龄
        pStu->element.age = age.toInt();
        ui->info_list->setItem(row, 3, new QTableWidgetItem(age));
    }
    if (telephone != "") {
        // 修改电话
        pStu->element.telephone = telephone.toStdString();
        ui->info_list->setItem(row, 4, new QTableWidgetItem(telephone));
    }
}

void MainWindow::updateSubData(QString name, QString credit, QString score) {
    // 更新课程数据
    // 更新数据库及信息列表
    auto pSub = (Institute::sub_pos) database.findPos(ui->select_grade_tab4->currentText().toInt(),
                                                      ui->select_major_tab4->currentText().toStdString(),
                                                      ui->select_class_tab4->currentText().toInt(),
                                                      ui->select_stu_tab4->currentText().toStdString(),
                                                      name.toStdString());
    auto row = ui->info_list->currentRow();
    if (credit != "") {
        pSub->element.credit = credit.toInt();
        ui->info_list->setItem(row, 1, new QTableWidgetItem(credit));
    }
    if (score != "") {
        pSub->element.score = score.toInt();
        ui->info_list->setItem(row, 2, new QTableWidgetItem(score));
    }
}


// 执行删除操作后更新信息列表及数据库数据
void MainWindow::delData() {
    auto selectedItems = ui->info_list->selectedItems();
    if (selectedItems.empty()) {
        // 必须选中某行才能执行删除操作
        ShowSomething warnDialog;
        warnDialog.setInfo(QString::fromStdString("请先选中一行！"));
        warnDialog.exec();
    } else {
        // 更新数据库
        if (ui->select_tool->currentIndex() == 0) {
            // 删除年级
            auto year = selectedItems.at(0)->text().toInt();
            database.delItem(year);
        } else if (ui->select_tool->currentIndex() == 1) {
            // 删除专业
            auto year = ui->select_grade_tab1->currentText().toInt();
            auto majorName = selectedItems.at(0)->text().toStdString();
            database.delItem(year, majorName);
        } else if (ui->select_tool->currentIndex() == 2) {
            // 删除班级
            auto year = ui->select_grade_tab2->currentText().toInt();
            auto majorName = ui->select_major_tab2->currentText().toStdString();
            auto classId = selectedItems.at(0)->text().toInt();
            database.delItem(year, majorName, classId);
        } else if (ui->select_tool->currentIndex() == 3) {
            // 删除学生
            auto year = ui->select_grade_tab3->currentText().toInt();
            auto majorName = ui->select_major_tab3->currentText().toStdString();
            auto classId = ui->select_class_tab3->currentText().toInt();
            auto stuId = selectedItems.at(0)->text().toStdString();
            database.delItem(year, majorName, classId, stuId);
        } else if (ui->select_tool->currentIndex() == 4) {
            // 删除课程
            auto year = ui->select_grade_tab4->currentText().toInt();
            auto majorName = ui->select_major_tab4->currentText().toStdString();
            auto classId = ui->select_class_tab4->currentText().toInt();
            auto stuId = ui->select_stu_tab4->currentText().toStdString();
            auto subName = selectedItems.at(0)->text().toStdString();
            database.delItem(year, majorName, classId, stuId, subName);
        }
        // 更新信息列表
        ui->info_list->removeRow(ui->info_list->currentRow());
    }
}

void MainWindow::delAll() {
    auto index = ui->select_tool->currentIndex();
    if (index == 0) {
        // 清空年级列表
        // 更新数据库
        database.clear();

        // 更新信息列表
        ui->info_list->clear();
        ui->info_list->setRowCount(0);
        ui->info_list->setHorizontalHeaderItem(0, new QTableWidgetItem("年级编号"));
        ui->info_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    } else if (index == 1) {
        // 清空专业列表
        if (ui->select_grade_tab1->currentIndex() == -1) {
            // 清空操作必须指定需要清空的链表
            ShowSomething warnDialog;
            warnDialog.setInfo(QString::fromStdString("请先选择年级！"));
            warnDialog.exec();
        } else {
            // 更新数据库
            database.clear(ui->select_grade_tab1->currentText().toInt());
            // 更新信息列表
            refreshMajorList();
        }
    } else if (index == 2) {
        // 清空班级列表
        if (ui->select_grade_tab2->currentIndex() == -1
                || ui->select_major_tab2->currentIndex() == -1) {
            // 清空操作必须指定需要清空的链表
            ShowSomething warnDialog;
            warnDialog.setInfo(QString::fromStdString("请先选择年级和专业名称！"));
            warnDialog.exec();
        } else {
            // 更新数据库
            database.clear(ui->select_grade_tab2->currentText().toInt(),
                           ui->select_major_tab2->currentText().toStdString());
            // 更新信息列表
            refreshClassList();
        }
    } else if (index == 3) {
        // 清空学生列表
        if (ui->select_grade_tab3->currentIndex() == -1
                || ui->select_major_tab3->currentIndex() == -1
                || ui->select_class_tab3->currentIndex() == -1) {
            // 清空操作必须指定需要清空的链表
            ShowSomething warnDialog;
            warnDialog.setInfo(QString::fromStdString("请先选择年级、专业名称和班级名称！"));
            warnDialog.exec();
        } else {
            // 更新数据库
            database.clear(ui->select_grade_tab3->currentText().toInt(),
                           ui->select_major_tab3->currentText().toStdString(),
                           ui->select_class_tab3->currentText().toInt());
            // 更新信息列表
            refreshStuList();
        }
    } else if (index == 4) {
        // 清空课程列表
        if (ui->select_grade_tab4->currentIndex() == -1
                || ui->select_major_tab4->currentIndex() == -1
                || ui->select_class_tab4->currentIndex() == -1
                || ui->select_stu_tab4->currentIndex() == -1) {
            // 清空操作必须指定需要清空的链表
            ShowSomething warnDialog;
            warnDialog.setInfo(QString::fromStdString("请先选择年级、专业名称、班级名称和学号！"));
            warnDialog.exec();
        } else {
            // 更新数据库
            database.clear(ui->select_grade_tab4->currentText().toInt(),
                           ui->select_major_tab4->currentText().toStdString(),
                           ui->select_class_tab4->currentText().toInt(),
                           ui->select_stu_tab4->currentText().toStdString());
            // 更新信息列表
            refreshSubList();
        }
    }
}


// 显示搜索结果
void MainWindow::showSearchResult(QString key) {
    if (key == "") {
        ShowSomething warnDialog;
        warnDialog.setInfo("关键字不得为空！");
        warnDialog.exec();
    } else {
        auto items = ui->info_list->findItems(key, Qt::MatchExactly);
        if (ui->select_tool->currentIndex() == 0) {
            // 查找年级
            if (items.empty()) {
                ShowSomething warnDialog;
                warnDialog.setInfo("找不到此年级！");
                warnDialog.exec();
            } else {
                ui->info_list->setCurrentItem(items.at(0));
            }
        } else if (ui->select_tool->currentIndex() == 1) {
            // 查找专业
            if (items.empty()) {
                ShowSomething warnDialog;
                warnDialog.setInfo("找不到此专业！");
                warnDialog.exec();
            } else {
                ui->info_list->setCurrentItem(items.at(0));
            }
        } else if (ui->select_tool->currentIndex() == 2) {
            // 查找班级
            if (items.empty()) {
                ShowSomething warnDialog;
                warnDialog.setInfo("找不到此班级！");
                warnDialog.exec();
            } else {
                ui->info_list->setCurrentItem(items.at(0));
            }
        } else if (ui->select_tool->currentIndex() == 3) {
            // 查找学生
            if (items.empty()) {
                ShowSomething warnDialog;
                warnDialog.setInfo("找不到此学生！");
                warnDialog.exec();
            } else {
                ui->info_list->setCurrentItem(items.at(0));
            }
        } else if (ui->select_tool->currentIndex() == 4) {
            // 查找课程
            if (items.empty()) {
                ShowSomething warnDialog;
                warnDialog.setInfo("找不到此课程！");
                warnDialog.exec();
            } else {
                ui->info_list->setCurrentItem(items.at(0));
            }
        }
    }
}


// 初始化信息列表
void MainWindow::iniGradeList() {
    // 初始化年级列表

    // 清空信息列表
    ui->info_list->clear();
    ui->info_list->setRowCount(0);
    ui->info_list->setColumnCount(1);

    // 添加表头
    ui->info_list->setHorizontalHeaderItem(0, new QTableWidgetItem("年级编号"));
    ui->info_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 从数据库读取数据填充年级列表
    for (auto p = (Institute::grade_pos) database.firstGrade(); p; p = p->next) {
        int currentRow = ui->info_list->rowCount();
        ui->info_list->insertRow(currentRow);
        ui->info_list->setItem(currentRow, 0, new QTableWidgetItem(
                                   QString::number(p->element.year)));
    }
}

void MainWindow::iniMajorList() {
    // 初始化专业列表

    // 清空信息列表及下拉菜单
    ui->info_list->clear();
    ui->info_list->setRowCount(0);
    ui->info_list->setColumnCount(1);
    ui->select_grade_tab1->clear();

    // 添加表头
    ui->info_list->setHorizontalHeaderItem(0, new QTableWidgetItem("专业名称"));
    ui->info_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 从数据库读取数据填充下拉菜单
    for (auto p = (Institute::grade_pos) database.firstGrade(); p; p = p->next) {
        ui->select_grade_tab1->addItem(QString::number(p->element.year));
    }
}

void MainWindow::iniClassList() {
    // 初始化班级列表

    // 清空信息列表及下拉菜单
    ui->info_list->clear();
    ui->info_list->setRowCount(0);
    ui->info_list->setColumnCount(1);
    ui->select_grade_tab2->clear();
    ui->select_major_tab2->clear();

    // 添加表头
    ui->info_list->setHorizontalHeaderItem(0, new QTableWidgetItem("班级名称"));
    ui->info_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 从数据库读取数据填充下拉菜单
    for (auto p = (Institute::grade_pos) database.firstGrade(); p; p = p->next) {
        ui->select_grade_tab2->addItem(QString::number(p->element.year));
    }
}

void MainWindow::iniStuList() {
    // 初始化学生列表

    // 清空信息列表及下拉菜单
    ui->info_list->clear();
    ui->info_list->setRowCount(0);
    ui->info_list->setColumnCount(5);
    ui->select_grade_tab3->clear();
    ui->select_major_tab3->clear();
    ui->select_class_tab3->clear();

    // 添加表头
    std::vector<std::string> headerText {"学号", "姓名", "性别", "年龄", "电话"};
    for (auto i = 0; i < 5; ++i)
        ui->info_list->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(headerText[i])));
    ui->info_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 从数据库读取数据填充下拉菜单
    for (auto p = (Institute::grade_pos) database.firstGrade(); p; p = p->next) {
        ui->select_grade_tab3->addItem(QString::number(p->element.year));
    }
}

void MainWindow::iniSubList() {
    // 初始化课程列表

    // 清空信息列表及下拉菜单
    ui->info_list->clear();
    ui->info_list->setRowCount(0);
    ui->info_list->setColumnCount(3);
    ui->select_grade_tab4->clear();
    ui->select_major_tab4->clear();
    ui->select_class_tab4->clear();
    ui->select_stu_tab4->clear();

    // 添加表头
    std::vector<std::string> headerText {"课程名称", "学分数", "成绩"};
    for (auto i = 0; i < 3; ++i)
        ui->info_list->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(headerText[i])));
    ui->info_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 从数据库读取数据填充下拉菜单
    for (auto p = (Institute::grade_pos) database.firstGrade(); p; p = p->next) {
        ui->select_grade_tab4->addItem(QString::number(p->element.year));
    }
}


// 初始化下拉菜单
void MainWindow::iniMajorComboBoxTab2(int index) {
    // 查找专业所属年级
    auto pg = (Institute::grade_pos) \
            database.findPos(ui->select_grade_tab2->itemText(index).toInt());

    // 清空下拉菜单
    ui->select_major_tab2->clear();

    // 从数据库读取数据填充下拉菜单
    for (auto pm = pg->element.firstMajor(); pm; pm = pm->next) {
        ui->select_major_tab2->addItem(QString::fromStdString(pm->element.name));
    }

    // 异常检测
    if (ui->select_major_tab2->count() == 0) {
        ShowSomething warnDialog;
        warnDialog.setInfo(QString::fromStdString("当前年级中没有任何专业，\n请先前往查看专业页面添加专业！"));
        warnDialog.exec();
    }
}

void MainWindow::iniMajorComboBoxTab3(int index) {
    // 查找专业所属年级
    auto pg = (Institute::grade_pos) \
            database.findPos(ui->select_grade_tab3->itemText(index).toInt());

    // 清空下拉菜单
    ui->select_major_tab3->clear();

    // 从数据库读取数据填充下拉菜单
    for (auto pm = pg->element.firstMajor(); pm; pm = pm->next) {
        ui->select_major_tab3->addItem(QString::fromStdString(pm->element.name));
    }

    // 异常检测
    if (ui->select_major_tab3->count() == 0) {
        ShowSomething warnDialog;
        warnDialog.setInfo(QString::fromStdString("当前年级中没有任何专业，\n请先前往查看专业页面添加专业！"));
        warnDialog.exec();
    }
}

void MainWindow::iniClassComboBoxTab3(int index) {
    // 查找班级所属专业
    auto pm = (Institute::major_pos) \
            database.findPos(ui->select_grade_tab3->currentText().toInt(),
                             ui->select_major_tab3->itemText(index).toStdString());

    // 清空下拉菜单
    ui->select_class_tab3->clear();

    // 从数据库读取数据填充下拉菜单
    for (auto pc = pm->element.firstClass(); pc; pc = pc->next) {
        ui->select_class_tab3->addItem(QString::number(pc->element.id));
    }

    // 异常检测
    if (ui->select_class_tab3->count() == 0) {
        ShowSomething warnDialog;
        warnDialog.setInfo(QString::fromStdString("当前专业中没有任何班级，\n请先前往查看班级页面添加班级！"));
        warnDialog.exec();
    }
}

void MainWindow::iniMajorComboBoxTab4(int index) {
    // 查找专业所属年级
    auto pg = (Institute::grade_pos) \
            database.findPos(ui->select_grade_tab4->itemText(index).toInt());

    // 清空下拉菜单
    ui->select_major_tab4->clear();

    // 从数据库读取数据填充下拉菜单
    for (auto pm = pg->element.firstMajor(); pm; pm = pm->next) {
        ui->select_major_tab4->addItem(QString::fromStdString(pm->element.name));
    }

    // 异常检测
    if (ui->select_major_tab4->count() == 0) {
        ShowSomething warnDialog;
        warnDialog.setInfo(QString::fromStdString("当前年级中没有任何专业，\n请先前往查看专业页面添加专业！"));
        warnDialog.exec();
    }
}

void MainWindow::iniClassComboBoxTab4(int index) {
    // 查找班级所属专业
    auto pm = (Institute::major_pos) \
            database.findPos(ui->select_grade_tab4->currentText().toInt(),
                             ui->select_major_tab4->itemText(index).toStdString());

    // 清空下拉菜单
    ui->select_class_tab4->clear();

    // 从数据库读取数据填充下拉菜单
    for (auto pc = pm->element.firstClass(); pc; pc = pc->next) {
        ui->select_class_tab4->addItem(QString::number(pc->element.id));
    }

    // 异常检测
    if (ui->select_class_tab4->count() == 0) {
        ShowSomething warnDialog;
        warnDialog.setInfo(QString::fromStdString("当前专业中没有任何班级，\n请先前往查看班级页面添加班级！"));
        warnDialog.exec();
    }
}

void MainWindow::iniStuComboBoxTab4(int index) {
    // 查找学生所属班级
    auto pc = (Institute::class_pos) \
            database.findPos(ui->select_grade_tab4->currentText().toInt(),
                             ui->select_major_tab4->currentText().toStdString(),
                             ui->select_class_tab4->itemText(index).toInt());

    // 清空下拉菜单
    ui->select_stu_tab4->clear();

    // 从数据库读取数据填充下拉菜单
    for (auto ps = pc->element.firstStudent(); ps; ps = ps->next) {
        ui->select_stu_tab4->addItem(QString::fromStdString(ps->element.id));
    }

    // 异常检测
    if (ui->select_stu_tab4->count() == 0) {
        ShowSomething warnDialog;
        warnDialog.setInfo(QString::fromStdString("当前班级中没有任何学生，\n请先前往查看学生页面添加学生！"));
        warnDialog.exec();
    }
}


void MainWindow::showDetail() {
    // 显示所选项详细信息
    auto selectedItems = ui->info_list->selectedItems();
    if (selectedItems.empty()) {
        // 必须选中某行才能执行删除操作
        ShowSomething warnDialog;
        warnDialog.setInfo(QString::fromStdString("请先选中一行！"));
        warnDialog.exec();
    } else {
        if (ui->select_tool->currentIndex() == 0) {
            // 获取所选年级编号
            QString year = selectedItems.at(0)->text();

            // 跳转到查看专业页面并初始化
            ui->select_tool->setCurrentIndex(1);
            changeInfoListType(1);

            // 在年级下拉菜单中选中需要查看的年级
            for (int gradeIndex = 0; gradeIndex < ui->select_grade_tab1->count(); ++gradeIndex) {
                if (ui->select_grade_tab1->itemText(gradeIndex) == year) {
                    ui->select_grade_tab1->setCurrentIndex(gradeIndex);
                    break;
                }
            }

            // 刷新信息列表
            refreshMajorList();
        } else if (ui->select_tool->currentIndex() == 1) {
            // 获取所选年级和专业名称
            int gradeIndex = ui->select_grade_tab1->currentIndex();
            QString majorName = selectedItems.at(0)->text();

            // 跳转到查看班级页面并初始化
            ui->select_tool->setCurrentIndex(2);
            changeInfoListType(2);

            // 在下拉菜单中选中需要查看的年级和专业
            ui->select_grade_tab2->setCurrentIndex(gradeIndex);
            iniMajorComboBoxTab2(gradeIndex);
            for (int majorIndex = 0; majorIndex < ui->select_major_tab2->count(); ++majorIndex) {
                if (ui->select_major_tab2->itemText(majorIndex) == majorName) {
                    ui->select_major_tab2->setCurrentIndex(majorIndex);
                    break;
                }
            }
            refreshClassList();
        } else if (ui->select_tool->currentIndex() == 2) {
            // 获取所选年级、专业名称和班级名称
            int gradeIndex = ui->select_grade_tab2->currentIndex();
            int majorIndex = ui->select_major_tab2->currentIndex();
            QString classId = selectedItems.at(0)->text();

            // 跳转到查看学生页面并初始化
            ui->select_tool->setCurrentIndex(3);
            changeInfoListType(3);

            // 在下拉菜单中选中需要查看的年级、专业和班级
            ui->select_grade_tab3->setCurrentIndex(gradeIndex);
            iniMajorComboBoxTab3(gradeIndex);
            ui->select_major_tab3->setCurrentIndex(majorIndex);
            iniClassComboBoxTab3(majorIndex);
            for (int classIndex = 0; classIndex < ui->select_class_tab3->count(); ++classIndex) {
                if (ui->select_class_tab3->itemText(classIndex) == classId) {
                    ui->select_class_tab3->setCurrentIndex(classIndex);
                    break;
                }
            }
            refreshStuList();
        } else if (ui->select_tool->currentIndex() == 3) {
            // 获取所选年级、专业名称、班级名称和学号
            int gradeIndex = ui->select_grade_tab3->currentIndex();
            int majorIndex = ui->select_major_tab3->currentIndex();
            int classIndex = ui->select_class_tab3->currentIndex();
            QString stuId = selectedItems.at(0)->text();

            // 跳转到查看课程页面并初始化
            ui->select_tool->setCurrentIndex(4);
            changeInfoListType(4);

            // 在下拉菜单中选中需要查看的年级、专业、班级和学生
            ui->select_grade_tab4->setCurrentIndex(gradeIndex);
            iniMajorComboBoxTab4(gradeIndex);
            ui->select_major_tab4->setCurrentIndex(majorIndex);
            iniClassComboBoxTab4(majorIndex);
            ui->select_class_tab4->setCurrentIndex(classIndex);
            iniStuComboBoxTab4(classIndex);
            for (int stuIndex = 0; stuIndex < ui->select_stu_tab4->count(); ++stuIndex) {
                if (ui->select_stu_tab4->itemText(stuIndex) == stuId) {
                    ui->select_stu_tab4->setCurrentIndex(stuIndex);
                    break;
                }
            }
            refreshSubList();
        }
    }
}
