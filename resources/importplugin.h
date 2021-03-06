#ifndef MISC_UTILS_IMPORT_PLUGIN_H
#define MISC_UTILS_IMPORT_PLUGIN_H

#include "resources/config.h"

#ifdef QT_STATIC
# if defined(GUI_QTWIDGETS) || defined(GUI_QTQUICK)
#  include <QtPlugin>
#  ifdef Q_OS_WIN32
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#  endif
#  ifdef SVG_SUPPORT
Q_IMPORT_PLUGIN(QSvgPlugin)
#  endif
#  ifdef SVG_ICON_SUPPORT
Q_IMPORT_PLUGIN(QSvgIconPlugin)
#  endif
# endif
#endif

#endif // MISC_UTILS_IMPORT_PLUGIN_H
