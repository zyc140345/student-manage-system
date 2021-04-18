#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>

namespace Ui {
class search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr);
    ~Search();

    void setKeyLabelText(QString text);

signals:
    void sendKey(QString key);

public slots:
    void acceptAndReturnValue();

private:
    Ui::search *ui;
};

#endif // SEARCH_H
