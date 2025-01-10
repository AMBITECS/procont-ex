#ifndef SETTINGS_H
#define SETTINGS_H

#include <QHash>

// const auto _g_settings_def = QHash<QString, QString>
// {
//     {"Geometry/mainwindow_width_def",       "1920"},
//     {"Geometry/mainwindow_height_def",      "1080"},
//     {"Geometry/mainwindow_width_min",       "1024"},
//     {"Geometry/mainwindow_height_min",      "768"}
// };

const std::unordered_map<QString, QString> _g_settings_def =
{
    {"Geometry/mainwindow_width_def",       "1920"},
    {"Geometry/mainwindow_height_def",      "1080"},
    {"Geometry/mainwindow_width_min",       "1024"},
    {"Geometry/mainwindow_height_min",      "768"}
};

const auto _g_settings_min = QHash<QString, QString>
{
    {"Geometry/mainwindow_width_min",       "1024"},
    {"Geometry/mainwindow_height_min",      "768"}
};

#endif // SETTINGS_H
