/********************************************************************************
** Form generated from reading UI file 'QGlitterUpdateAlert.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGLITTERUPDATEALERT_H
#define UI_QGLITTERUPDATEALERT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QGlitterUpdateAlert
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *iconLabel;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *headerLabel;
    QLabel *messageLabel;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QTextBrowser *releaseNotes;
    QSpacerItem *verticalSpacer_3;
    QCheckBox *enableAutomaticDownload;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *skipVersionButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *remindMeLaterButton;
    QPushButton *installUpdateButton;

    void setupUi(QDialog *QGlitterUpdateAlert)
    {
        if (QGlitterUpdateAlert->objectName().isEmpty())
            QGlitterUpdateAlert->setObjectName(QStringLiteral("QGlitterUpdateAlert"));
        QGlitterUpdateAlert->resize(652, 372);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QGlitterUpdateAlert->sizePolicy().hasHeightForWidth());
        QGlitterUpdateAlert->setSizePolicy(sizePolicy);
        QGlitterUpdateAlert->setSizeGripEnabled(true);
        QGlitterUpdateAlert->setModal(false);
        gridLayout = new QGridLayout(QGlitterUpdateAlert);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, -1, 13, -1);
        iconLabel = new QLabel(QGlitterUpdateAlert);
        iconLabel->setObjectName(QStringLiteral("iconLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(iconLabel->sizePolicy().hasHeightForWidth());
        iconLabel->setSizePolicy(sizePolicy1);
        iconLabel->setMinimumSize(QSize(64, 64));
        iconLabel->setMaximumSize(QSize(64, 64));

        verticalLayout_2->addWidget(iconLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        headerLabel = new QLabel(QGlitterUpdateAlert);
        headerLabel->setObjectName(QStringLiteral("headerLabel"));
        headerLabel->setText(QStringLiteral("<html><head/><body><p><span style=\" font-weight:600;\">A new version of Software is available!</span></p></body></html>"));

        verticalLayout->addWidget(headerLabel);

        messageLabel = new QLabel(QGlitterUpdateAlert);
        messageLabel->setObjectName(QStringLiteral("messageLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(messageLabel->sizePolicy().hasHeightForWidth());
        messageLabel->setSizePolicy(sizePolicy2);
        messageLabel->setText(QStringLiteral("<html><head/><body><p>Software 0.0 is now available &mdash; you have 0.0. Would you like to download it now?</p></body></html>"));
        messageLabel->setWordWrap(false);

        verticalLayout->addWidget(messageLabel);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        label_3 = new QLabel(QGlitterUpdateAlert);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        releaseNotes = new QTextBrowser(QGlitterUpdateAlert);
        releaseNotes->setObjectName(QStringLiteral("releaseNotes"));
        QSizePolicy sizePolicy3(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(releaseNotes->sizePolicy().hasHeightForWidth());
        releaseNotes->setSizePolicy(sizePolicy3);
        releaseNotes->setMinimumSize(QSize(0, 177));

        verticalLayout->addWidget(releaseNotes);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        enableAutomaticDownload = new QCheckBox(QGlitterUpdateAlert);
        enableAutomaticDownload->setObjectName(QStringLiteral("enableAutomaticDownload"));

        verticalLayout->addWidget(enableAutomaticDownload);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        skipVersionButton = new QPushButton(QGlitterUpdateAlert);
        skipVersionButton->setObjectName(QStringLiteral("skipVersionButton"));

        horizontalLayout_2->addWidget(skipVersionButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        remindMeLaterButton = new QPushButton(QGlitterUpdateAlert);
        remindMeLaterButton->setObjectName(QStringLiteral("remindMeLaterButton"));

        horizontalLayout_2->addWidget(remindMeLaterButton);

        installUpdateButton = new QPushButton(QGlitterUpdateAlert);
        installUpdateButton->setObjectName(QStringLiteral("installUpdateButton"));

        horizontalLayout_2->addWidget(installUpdateButton);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        QWidget::setTabOrder(installUpdateButton, remindMeLaterButton);
        QWidget::setTabOrder(remindMeLaterButton, skipVersionButton);
        QWidget::setTabOrder(skipVersionButton, enableAutomaticDownload);
        QWidget::setTabOrder(enableAutomaticDownload, releaseNotes);

        retranslateUi(QGlitterUpdateAlert);

        QMetaObject::connectSlotsByName(QGlitterUpdateAlert);
    } // setupUi

    void retranslateUi(QDialog *QGlitterUpdateAlert)
    {
        QGlitterUpdateAlert->setWindowTitle(QApplication::translate("QGlitterUpdateAlert", "Software Update", 0));
        iconLabel->setText(QString());
        label_3->setText(QApplication::translate("QGlitterUpdateAlert", "<html><head/><body><p><span style=\" font-weight:600;\">Release Notes:</span></p></body></html>", 0));
        enableAutomaticDownload->setText(QApplication::translate("QGlitterUpdateAlert", "Automatically download and install updates in the future", 0));
        skipVersionButton->setText(QApplication::translate("QGlitterUpdateAlert", "Skip This Version", 0));
        remindMeLaterButton->setText(QApplication::translate("QGlitterUpdateAlert", "Remind Me Later", 0));
        installUpdateButton->setText(QApplication::translate("QGlitterUpdateAlert", "Install Update", 0));
    } // retranslateUi

};

namespace Ui {
    class QGlitterUpdateAlert: public Ui_QGlitterUpdateAlert {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGLITTERUPDATEALERT_H
