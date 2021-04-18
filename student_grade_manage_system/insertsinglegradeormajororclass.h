#ifndef INSERTSINGLEGRADEORMAJORORCLASS_H
#define INSERTSINGLEGRADEORMAJORORCLASS_H

#include <QDialog>

namespace Ui {
class InsertSingleGradeOrMajorOrClass;
}

class InsertSingleGradeOrMajorOrClass : public QDialog
{
    Q_OBJECT

public:
    explicit InsertSingleGradeOrMajorOrClass(QWidget *parent = nullptr);
    ~InsertSingleGradeOrMajorOrClass();

    void iniAsGradeDialog();
    void iniAsMajorDialog();
    void iniAsClassDialog();
    int dialogType() { return dt; }

signals:
    void sendGradeData(QString year);
    void sendMajorData(QString majorName);
    void sendClassData(QString classId);

public slots:
    void acceptAndReturnValue();

private:
    Ui::InsertSingleGradeOrMajorOrClass *ui;
    int dt;
};

#endif // INSERTSINGLEGRADEORMAJORORCLASS_H
