#ifndef SHOWSOMETHING_H
#define SHOWSOMETHING_H

#include <QDialog>

namespace Ui {
class ShowSomething;
}

class ShowSomething : public QDialog
{
    Q_OBJECT

public:
    explicit ShowSomething(QWidget *parent = nullptr);
    ~ShowSomething();
    void setInfo(QString s);

private:
    Ui::ShowSomething *ui;
};

#endif // SHOWSOMETHING_H
