#ifndef WIDGETSETTINGS_H
#define WIDGETSETTINGS_H

#include <QTabWidget>

#include <QModelIndex>
#include <QDomNode>

// ----------------------------------------------------------------------------
// *** CustomTabStyle ***

/*!
 * \brief The CustomTabStyle class
 */

#include <QProxyStyle>

class CustomTabStyle : public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type_, const QStyleOption* option_, const QSize& size_, const QWidget* widget_) const;
    void drawControl(ControlElement element_, const QStyleOption* option_, QPainter* painter_, const QWidget* widget_) const;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** LogViewer ***

/*!
 * \brief The LogViewer class
 */

class LogViewer : public QWidget
{
    Q_OBJECT

public:
    LogViewer();
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings ***

/*!
 * \brief The WidgetSettings class
 */
class WidgetSettings : public QTabWidget
{
    Q_OBJECT
public:
    enum eDeviceType
    {
        eDT_Unknown             = 0,
        eDT_CANbus              = 1,
        eDT_CANopen_manager     = 2,
        eDT_CANopen_device      = 3,
        eDT_CANopen_remote_device = 4
    };
public:
    WidgetSettings(const QModelIndex & index_);

    static eDeviceType assignType(const QDomNode &);

protected:
    QModelIndex _m_index;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_CANbus ***

/*!
 * \brief The WidgetSettings_CANbus class
 */
class WidgetSettings_CANbus : public WidgetSettings
{
    Q_OBJECT
public:
    WidgetSettings_CANbus(const QModelIndex & index_);

private:
    [[nodiscard]] QWidget * createTab1();
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_CANopen_manager ***

/*!
 * \brief The WidgetSettings_CANopen_manager class
 */
class WidgetSettings_CANopen_manager : public WidgetSettings
{
    Q_OBJECT
public:
    WidgetSettings_CANopen_manager(const QModelIndex & index_);

private:
    [[nodiscard]] QWidget * createTab1();
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_CANopen_device ***

/*!
 * \brief The WidgetSettings_CANopen_device class
 */
class WidgetSettings_CANopen_device : public WidgetSettings
{
    Q_OBJECT
public:
    WidgetSettings_CANopen_device(const QModelIndex & index_);

private:
    [[nodiscard]] QWidget * createTab1();
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_CANopen_remote_device ***

/*!
 * \brief The WidgetSettings_CANopen_remote_device class
 */
class WidgetSettings_CANopen_remote_device : public WidgetSettings
{
    Q_OBJECT
public:
    WidgetSettings_CANopen_remote_device(const QModelIndex & index_);

private:
    [[nodiscard]] QWidget * createTab1();
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_creator ***

/*!
 * \brief The WidgetSettings_creator class
 */
class WidgetSettings_creator
{
public:
    WidgetSettings_creator() = default;

    [[nodiscard]] virtual WidgetSettings * create(const QModelIndex & index_) = 0;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_creator_CANbus ***

/*!
 * \brief The WidgetSettings_creator_CANbus class
 */
class WidgetSettings_creator_CANbus : public WidgetSettings_creator
{
public:
    WidgetSettings_creator_CANbus() = default;

    [[nodiscard]] WidgetSettings * create(const QModelIndex & index_);
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_creator_CANopen_manager ***

/*!
 * \brief The WidgetSettings_creator_CANopen_manager class
 */
class WidgetSettings_creator_CANopen_manager : public WidgetSettings_creator
{
public:
    WidgetSettings_creator_CANopen_manager() = default;

    [[nodiscard]] WidgetSettings * create(const QModelIndex & index_);
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_creator_CANopen_device ***

/*!
 * \brief The WidgetSettings_creator_CANopen_device class
 */
class WidgetSettings_creator_CANopen_device : public WidgetSettings_creator
{
public:
    WidgetSettings_creator_CANopen_device() = default;

    [[nodiscard]] WidgetSettings * create(const QModelIndex & index_);
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_creator_CANopen_remote_device ***

/*!
 * \brief The WidgetSettings_creator_CANopen_remote_device class
 */
class WidgetSettings_creator_CANopen_remote_device : public WidgetSettings_creator
{
public:
    WidgetSettings_creator_CANopen_remote_device() = default;

    [[nodiscard]] WidgetSettings * create(const QModelIndex & index_);
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_builder ***

/*!
 * \brief The WidgetSettings_builder class
 */
class WidgetSettings_builder
{
public:
    WidgetSettings_builder();
    ~WidgetSettings_builder();

    [[nodiscard]] WidgetSettings * build(const QModelIndex & index_);

private:
    QHash<WidgetSettings::eDeviceType, WidgetSettings_creator*> m_creators;
};
// ----------------------------------------------------------------------------

#endif // WIDGETSETTINGS_H
