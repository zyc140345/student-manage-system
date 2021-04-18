#ifndef INSERTSINGLESTU_H
#define INSERTSINGLESTU_H

#include <QDialog>

namespace Ui {
class InsertSingleStu;
}

class InsertSingleStu : public QDialog
{
    Q_OBJECT

public:
    explicit InsertSingleStu(QWidget *parent = nullptr);
    ~InsertSingleStu();
    void iniAsStuEditDialog(QString stuId, QString sex);

signals:
    void sendStuData(QString stuId,
                     QString stuName,
                     QString sex,
                     QString age,
                     QString telephone);

public slots:
    void acceptAndReturnValue();

private:
    Ui::InsertSingleStu *ui;
};

#endif // INSERTSINGLESTU_H
