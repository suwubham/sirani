#ifndef SIGNUP_PAGE_H
#define SIGNUP_PAGE_H

#include <QDialog>

namespace Ui {
class signup_page;
}

class signup_page : public QDialog
{
    Q_OBJECT

public:
    explicit signup_page(QWidget *parent = nullptr);
    ~signup_page();

private:
    Ui::signup_page *ui;
};

#endif // SIGNUP_PAGE_H
