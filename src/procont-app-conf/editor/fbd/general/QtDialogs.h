//
// Created by nechi on 28.09.2024.
//

#ifndef EDITORS_QTDIALOGS_H
#define EDITORS_QTDIALOGS_H

#include <QMessageBox>

class QtDialogs {
public:

    static  void    warn_user(const QString &msg);
    static  void    alarm_user(const QString &msg);
    static  void    info_user(const QString &msg);
    static  bool    ask_user(const QString &quest);

};


#endif //EDITORS_QTDIALOGS_H
