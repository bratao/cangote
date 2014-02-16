/********************************************************************************
** Form generated from reading UI file 'QGlitterUpdateStatus.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGLITTERUPDATESTATUS_H
#define UI_QGLITTERUPDATESTATUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QGlitterUpdateStatus
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *iconLabel;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *statusText;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QLabel *progressText;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QDialog *QGlitterUpdateStatus)
    {
        if (QGlitterUpdateStatus->objectName().isEmpty())
            QGlitterUpdateStatus->setObjectName(QStringLiteral("QGlitterUpdateStatus"));
        QGlitterUpdateStatus->resize(490, 113);
        QGlitterUpdateStatus->setModal(false);
        horizontalLayout_2 = new QHBoxLayout(QGlitterUpdateStatus);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, -1, 13, -1);
        iconLabel = new QLabel(QGlitterUpdateStatus);
        iconLabel->setObjectName(QStringLiteral("iconLabel"));
        iconLabel->setMinimumSize(QSize(64, 64));
        iconLabel->setMaximumSize(QSize(64, 64));

        verticalLayout_2->addWidget(iconLabel);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        statusText = new QLabel(QGlitterUpdateStatus);
        statusText->setObjectName(QStringLiteral("statusText"));

        verticalLayout->addWidget(statusText);

        progressBar = new QProgressBar(QGlitterUpdateStatus);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setMinimumSize(QSize(258, 0));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        progressText = new QLabel(QGlitterUpdateStatus);
        progressText->setObjectName(QStringLiteral("progressText"));
        progressText->setText(QStringLiteral("<html><head/><body><p><span style=\" font-weight:600;\">Downloaded 0.0 MB of 0.0 MB</span></p></body></html>"));

        horizontalLayout->addWidget(progressText);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(QGlitterUpdateStatus);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMinimumSize(QSize(0, 32));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(QGlitterUpdateStatus);

        QMetaObject::connectSlotsByName(QGlitterUpdateStatus);
    } // setupUi

    void retranslateUi(QDialog *QGlitterUpdateStatus)
    {
        QGlitterUpdateStatus->setWindowTitle(QApplication::translate("QGlitterUpdateStatus", "Updating Software", 0));
        iconLabel->setText(QString());
        statusText->setText(QApplication::translate("QGlitterUpdateStatus", "<html><head/><body><p><span style=\" font-weight:600;\">Downloading Update</span></p></body></html>", 0));
        pushButton->setText(QApplication::translate("QGlitterUpdateStatus", "Cancel Download", 0));
    } // retranslateUi

};

namespace Ui {
    class QGlitterUpdateStatus: public Ui_QGlitterUpdateStatus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGLITTERUPDATESTATUS_H
