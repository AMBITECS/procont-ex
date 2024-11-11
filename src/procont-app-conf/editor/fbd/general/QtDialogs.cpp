//
// Created by nechi on 28.09.2024.
//

#include "QtDialogs.h"
#include <QPushButton>

void QtDialogs::warn_user(const QString &msg)
{
    QMessageBox box(nullptr);
    box.setWindowTitle("Минуточку!...");
    box.setWindowIcon(QIcon(":/16/images/16x16/bell.png"));
    box.setText(msg);
    box.setIconPixmap(QPixmap(":/48/images/48x48/199.png"));

    box.exec();
}

void QtDialogs::alarm_user(const QString &msg)
{
    QMessageBox box(nullptr);
    box.setWindowTitle("Внимание!!!");
    box.setWindowIcon(QIcon(":/16/images/16x16/bell.png"));
    box.setText(msg);
    box.setIconPixmap(QPixmap(":/24/images/24x24/Danger.png"));

    box.exec();
}

void QtDialogs::info_user(const QString &msg)
{
    QMessageBox box(nullptr);
    box.setWindowTitle("Для справки.");
    box.setWindowIcon(QIcon(":/16/images/16x16/bell.png"));
    box.setText(msg);
    box.setIconPixmap(QPixmap(":/48/images/48x48/155.png"));

    box.exec();
}

bool QtDialogs::ask_user(const QString &quest)
{
    QMessageBox box(nullptr);
    box.setWindowTitle("Ваше решение?");
    box.setWindowIcon(QIcon(":/24/images/24x24/Question.png"));
    box.setText(quest);
    box.setIconPixmap(QPixmap(":/48/images/48x48/comm-info.png"));

    QPushButton *yes_btn = box.addButton(QMessageBox::StandardButton::Yes);
    QPushButton *no_btn = box.addButton(QMessageBox::StandardButton::No);

    yes_btn->setText("Да");
    yes_btn->setIcon(QIcon(":/24/images/24x24/OK.png"));

    no_btn->setText("Нет");
    no_btn->setIcon(QIcon(":/24/images/24x24/Erase.png"));


    int res = box.exec();

    return res == QMessageBox::StandardButton::Yes;
}
