#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "insertsinglestu.h"
#include "insertsinglegradeormajororclass.h"
#include "insertsinglesubject.h"
#include "search.h"
#include "showsomething.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void iniGradeList();
    void iniMajorList();
    void iniClassList();
    void iniStuList();
    void iniSubList();


public slots:
    void showInsertDialog();
    void showEditDialog();
    void showSearchDialog();

    void changeInfoListType(int tabIndex);
    void refreshMajorList();
    void refreshClassList();
    void refreshStuList();
    void refreshSubList();

    void addGradeData(QString year);
    void addMajorData(QString majorName);
    void addClassData(QString classId);
    void addStuData(QString stuId,
                       QString stuName,
                       QString sex,
                       QString age,
                       QString telephone);
    void addSubData(QString name, QString credit, QString score);

    void updateStuData(QString stuId,
                       QString stuName,
                       QString sex,
                       QString age,
                       QString telephone);
    void updateSubData(QString name, QString credit, QString score);

    void delData();
    void delAll();

    void showSearchResult(QString key);

    void iniMajorComboBoxTab2(int index);
    void iniMajorComboBoxTab3(int index);
    void iniClassComboBoxTab3(int index);
    void iniMajorComboBoxTab4(int index);
    void iniClassComboBoxTab4(int index);
    void iniStuComboBoxTab4(int index);

    void showDetail();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
