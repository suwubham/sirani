#ifndef CONNECTION_H
#define CONNECTION_H
#include <QString>

bool connOpen();
void connClose();
bool Email_check(QString email);
bool pw_check(QString pw);

class User{
public:
    QString first_name;
    QString last_name;
    QString email;
    QString password;
    QString username;
};



#endif // CONNECTION_H
