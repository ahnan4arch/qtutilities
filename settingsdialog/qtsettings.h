// The functions and classes declared in this header are experimental.
// API/ABI might change in minor release!

#ifndef DIALOGS_QT_UTILITIES_QTSETTINGS_H
#define DIALOGS_QT_UTILITIES_QTSETTINGS_H

#include "./optionpage.h"

#include <memory>

QT_FORWARD_DECLARE_CLASS(QFontDialog)
QT_FORWARD_DECLARE_CLASS(QSettings)

namespace Dialogs {

class OptionCategory;
struct QtSettingsData;

BEGIN_DECLARE_UI_FILE_BASED_OPTION_PAGE_CUSTOM_CTOR(QtAppearanceOptionPage)
public:
    explicit QtAppearanceOptionPage(QtSettingsData &settings, QWidget *parentWidget = nullptr);
private:
    DECLARE_SETUP_WIDGETS
    QtSettingsData &m_settings;
    QFontDialog *m_fontDialog;
END_DECLARE_OPTION_PAGE

BEGIN_DECLARE_UI_FILE_BASED_OPTION_PAGE_CUSTOM_CTOR(QtLanguageOptionPage)
public:
    explicit QtLanguageOptionPage(QtSettingsData &settings, QWidget *parentWidget = nullptr);
private:
    DECLARE_SETUP_WIDGETS
    QtSettingsData &m_settings;
END_DECLARE_OPTION_PAGE

BEGIN_DECLARE_UI_FILE_BASED_OPTION_PAGE_CUSTOM_CTOR(QtEnvOptionPage)
public:
    explicit QtEnvOptionPage(QtSettingsData &settings, QWidget *parentWidget = nullptr);
private:
    QtSettingsData &m_settings;
END_DECLARE_OPTION_PAGE

class LIB_EXPORT QtSettings
{
public:
    QtSettings();
    ~QtSettings();

    void restore(QSettings &settings);
    void save(QSettings &settings) const;
    void apply();
    bool hasCustomFont() const;

    OptionCategory *category();

private:
    std::unique_ptr<QtSettingsData> m_d;
};

}

#endif // DIALOGS_QT_UTILITIES_QTSETTINGS_H
