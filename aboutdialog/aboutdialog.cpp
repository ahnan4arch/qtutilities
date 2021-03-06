#include "./aboutdialog.h"
#include "../misc/dialogutils.h"

#include "ui_aboutdialog.h"

#include <QGraphicsPixmapItem>
#include <QApplication>
#include <QDesktopWidget>
#include <QStyle>

/*!
    \namespace Dialogs
    \brief Provides common dialogs such as AboutDialog, EnterPasswordDialog and SettingsDialog.
*/

namespace Dialogs {

/*!
 * \class Dialogs::AboutDialog
 * \brief The AboutDialog class provides a simple about dialog.
 */

/*!
 * \brief Constructs an about dialog with the provided information.
 * \param parent Specifies the parent widget.
 * \param applicationName Specifies the name of the application. If empty, QApplication::applicationName() will be used.
 * \param creator Specifies the creator of the application. If empty, QApplication::organizationName() will be used.
 * \param version Specifies the version of the application. If empty, QApplication::applicationVersion() will be used.
 * \param description Specifies a short description about the application.
 * \param website Specifies the URL to the website of the application. If empty, QApplication::organizationDomain() will be used.
 * \param image Specifies the application icon. If the image is null, the standard information icon will be used.
 */
AboutDialog::AboutDialog(QWidget *parent, const QString &applicationName, const QString &creator, const QString &version, const QString &website, const QString &description, const QImage &image) :
    QDialog(parent),
    m_ui(new Ui::AboutDialog)
{
    m_ui->setupUi(this);
    makeHeading(m_ui->productNameLabel);
    setStyleSheet(dialogStyle());
    setWindowFlags(Qt::Tool);
    if(!applicationName.isEmpty()) {
        m_ui->productNameLabel->setText(applicationName);
    } else if(!QApplication::applicationDisplayName().isEmpty()) {
        m_ui->productNameLabel->setText(QApplication::applicationDisplayName());
    } else {
        m_ui->productNameLabel->setText(QApplication::applicationName());
    }
    m_ui->creatorLabel->setText(tr("developed by %1").arg(
                                    creator.isEmpty() ? QApplication::organizationName() : creator));
    m_ui->versionLabel->setText(version.isEmpty() ? QApplication::applicationVersion() : version);
    m_ui->websiteLabel->setText(tr("For updates and bug reports visit the <a href=\"%1\" style=\"text-decoration: underline; color: palette(link);\">project website</a>.").arg(
                                  website.isEmpty() ? QApplication::organizationDomain() : website));
    m_ui->descLabel->setText(description);
    m_iconScene = new QGraphicsScene(this);
    auto *item = image.isNull()
            ? new QGraphicsPixmapItem(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation, nullptr, this).pixmap(128))
            : new QGraphicsPixmapItem(QPixmap::fromImage(image));
    m_iconScene->addItem(item);
    m_ui->graphicsView->setScene(m_iconScene);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), parentWidget() ? parentWidget()->geometry() : QApplication::desktop()->availableGeometry()));
}

/*!
 * \brief Constructs an about dialog with the specified \a parent, \a description and \a image.
 */
AboutDialog::AboutDialog(QWidget *parent, const QString &description, const QImage &image) :
    AboutDialog(parent, QString(), QString(), QString(), QString(), description, image)
{}

/*!
 * \brief Destroys the about dialog.
 */
AboutDialog::~AboutDialog()
{}

}
