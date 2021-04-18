#ifndef INSERTSINGLESUBJECT_H
#define INSERTSINGLESUBJECT_H

#include <QDialog>

namespace Ui {
class InsertSingleSubject;
}

class InsertSingleSubject : public QDialog
{
    Q_OBJECT

public:
    explicit InsertSingleSubject(QWidget *parent = nullptr);
    ~InsertSingleSubject();
    void iniAsEditSubDialog(QString subName);

signals:
    void sendSubData(QString name, QString credit, QString score);

public slots:
    void acceptAndReturnValue();

private:
    Ui::InsertSingleSubject *ui;
};

#endif // INSERTSINGLESUBJECT_H
