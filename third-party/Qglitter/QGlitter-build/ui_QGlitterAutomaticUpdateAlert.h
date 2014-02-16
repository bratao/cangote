/********************************************************************************
** Form generated from reading UI file 'QGlitterAutomaticUpdateAlert.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGLITTERAUTOMATICUPDATEALERT_H
#define UI_QGLITTERAUTOMATICUPDATEALERT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QGlitterAutomaticUpdateAlert
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *iconLabel;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *headerLabel;
    QLabel *messageLabel;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *enableAutomaticDownload;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *installLaterButton;
    QPushButton *installNowButton;

    void setupUi(QDialog *QGlitterAutomaticUpdateAlert)
    {
        if (QGlitterAutomaticUpdateAlert->objectName().isEmpty())
            QGlitterAutomaticUpdateAlert->setObjectName(QStringLiteral("QGlitterAutomaticUpdateAlert"));
        horizontalLayout_2 = new QHBoxLayout(QGlitterAutomaticUpdateAlert);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, -1, 13, -1);
        iconLabel = new QLabel(QGlitterAutomaticUpdateAlert);
        iconLabel->setObjectName(QStringLiteral("iconLabel"));
        iconLabel->setMinimumSize(QSize(64, 64));
        iconLabel->setMaximumSize(QSize(64, 64));

        verticalLayout->addWidget(iconLabel);

        verticalSpacer = new QSpacerItem(1, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        headerLabel = new QLabel(QGlitterAutomaticUpdateAlert);
        headerLabel->setObjectName(QStringLiteral("headerLabel"));
        headerLabel->setText(QStringLiteral("<html><head/><body><p><span style=\" font-weight:600;\">A new version of Software is available!</span></p></body></html>"));

        verticalLayout_2->addWidget(headerLabel);

        messageLabel = new QLabel(QGlitterAutomaticUpdateAlert);
        messageLabel->setObjectName(QStringLiteral("messageLabel"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(messageLabel->sizePolicy().hasHeightForWidth());
        messageLabel->setSizePolicy(sizePolicy);
        messageLabel->setText(QStringLiteral("<html><head/><body><p>Software 0.0 is now available &mdash; you have 0.0. Would you like to download it now?</p></body></html>"));
        messageLabel->setWordWrap(false);

        verticalLayout_2->addWidget(messageLabel);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_2);

        enableAutomaticDownload = new QCheckBox(QGlitterAutomaticUpdateAlert);
        enableAutomaticDownload->setObjectName(QStringLiteral("enableAutomaticDownload"));

        verticalLayout_2->addWidget(enableAutomaticDownload);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        cancelButton = new QPushButton(QGlitterAutomaticUpdateAlert);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        installLaterButton = new QPushButton(QGlitterAutomaticUpdateAlert);
        installLaterButton->setObjectName(QStringLiteral("installLaterButton"));

        horizontalLayout->addWidget(installLaterButton);

        installNowButton = new QPushButton(QGlitterAutomaticUpdateAlert);
        installNowButton->setObjectName(QStringLiteral("installNowButton"));

        horizontalLayout->addWidget(installNowButton);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);

        QWidget::setTabOrder(installNowButton, installLaterButton);
        QWidget::setTabOrder(installLaterButton, cancelButton);
        QWidget::setTabOrder(cancelButton, enableAutomaticDownload);

        retranslateUi(QGlitterAutomaticUpdateAlert);

        QMetaObject::connectSlotsByName(QGlitterAutomaticUpdateAlert);
    } // setupUi

    void retranslateUi(QDialog *QGlitterAutomaticUpdateAlert)
    {
        QGlitterAutomaticUpdateAlert->setWindowTitle(QApplication::translate("QGlitterAutomaticUpdateAlert", "Software Update", 0));
        iconLabel->setText(QString());
        enableAutomaticDownload->setText(QApplication::translate("QGlitterAutomaticUpdateAlert", "Automatically download and install updates in the future", 0));
        cancelButton->setText(QApplication::translate("QGlitterAutomaticUpdateAlert", "Don't Install", 0));
        installLaterButton->setText(QApplication::translate("QGlitterAutomaticUpdateAlert", "Install on Quit", 0));
        installNowButton->setText(QApplication::translate("QGlitterAutomaticUpdateAlert", "Install and Relaunch", 0));
    } // retranslateUi

};

namespace Ui {
    class QGlitterAutomaticUpdateAlert: public Ui_QGlitterAutomaticUpdateAlert {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGLITTERAUTOMATICUPDATEALERT_H
