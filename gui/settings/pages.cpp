/*
     This file is part of Cangote
     (C) 2012 Bruno Cabral (and other contributing authors)

     Cangote is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published
     by the Free Software Foundation; either version 3, or (at your
     option) any later version.

     Cangote is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with Cangote; see the file COPYING.  If not, write to the
     Free Software Foundation, Inc., 59 Temple Place - Suite 330,
     Boston, MA 02111-1307, USA.
*/


#include <QtGui>

 #include "pages.h"

 ConfigurationPage::ConfigurationPage(QWidget *parent)
     : QWidget(parent)
 {
     QGroupBox *configGroup = new QGroupBox(tr("Network configuration"));

     QLabel *serverLabel = new QLabel(tr("Server:"));
     QComboBox *serverCombo = new QComboBox;
     serverCombo->addItem(tr("Qt (Australia)"));
     serverCombo->addItem(tr("Qt (Germany)"));
     serverCombo->addItem(tr("Qt (Norway)"));
     serverCombo->addItem(tr("Qt (People's Republic of China)"));
     serverCombo->addItem(tr("Qt (USA)"));

     QHBoxLayout *serverLayout = new QHBoxLayout;
     serverLayout->addWidget(serverLabel);
     serverLayout->addWidget(serverCombo);

     QVBoxLayout *configLayout = new QVBoxLayout;
     configLayout->addLayout(serverLayout);
     configGroup->setLayout(configLayout);

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(configGroup);
     mainLayout->addStretch(1);
     setLayout(mainLayout);
 }

 UpdatePage::UpdatePage(QWidget *parent)
     : QWidget(parent)
 {
     QGroupBox *updateGroup = new QGroupBox(tr("Package selection"));
     QCheckBox *systemCheckBox = new QCheckBox(tr("Update system"));
     QCheckBox *appsCheckBox = new QCheckBox(tr("Update applications"));
     QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));

     QGroupBox *packageGroup = new QGroupBox(tr("Existing packages"));

     QListWidget *packageList = new QListWidget;
     QListWidgetItem *qtItem = new QListWidgetItem(packageList);
     qtItem->setText(tr("Qt"));
     QListWidgetItem *qsaItem = new QListWidgetItem(packageList);
     qsaItem->setText(tr("QSA"));
     QListWidgetItem *teamBuilderItem = new QListWidgetItem(packageList);
     teamBuilderItem->setText(tr("Teambuilder"));

     QPushButton *startUpdateButton = new QPushButton(tr("Start update"));

     QVBoxLayout *updateLayout = new QVBoxLayout;
     updateLayout->addWidget(systemCheckBox);
     updateLayout->addWidget(appsCheckBox);
     updateLayout->addWidget(docsCheckBox);
     updateGroup->setLayout(updateLayout);

     QVBoxLayout *packageLayout = new QVBoxLayout;
     packageLayout->addWidget(packageList);
     packageGroup->setLayout(packageLayout);

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(updateGroup);
     mainLayout->addWidget(packageGroup);
     mainLayout->addSpacing(12);
     mainLayout->addWidget(startUpdateButton);
     mainLayout->addStretch(1);
     setLayout(mainLayout);
 }

 QueryPage::QueryPage(QWidget *parent)
     : QWidget(parent)
 {
     QGroupBox *packagesGroup = new QGroupBox(tr("Look for packages"));

     QLabel *nameLabel = new QLabel(tr("Name:"));
     QLineEdit *nameEdit = new QLineEdit;

     QLabel *dateLabel = new QLabel(tr("Released after:"));
     QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());

     QCheckBox *releasesCheckBox = new QCheckBox(tr("Releases"));
     QCheckBox *upgradesCheckBox = new QCheckBox(tr("Upgrades"));

     QSpinBox *hitsSpinBox = new QSpinBox;
     hitsSpinBox->setPrefix(tr("Return up to "));
     hitsSpinBox->setSuffix(tr(" results"));
     hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
     hitsSpinBox->setMinimum(1);
     hitsSpinBox->setMaximum(100);
     hitsSpinBox->setSingleStep(10);

     QPushButton *startQueryButton = new QPushButton(tr("Start query"));

     QGridLayout *packagesLayout = new QGridLayout;
     packagesLayout->addWidget(nameLabel, 0, 0);
     packagesLayout->addWidget(nameEdit, 0, 1);
     packagesLayout->addWidget(dateLabel, 1, 0);
     packagesLayout->addWidget(dateEdit, 1, 1);
     packagesLayout->addWidget(releasesCheckBox, 2, 0);
     packagesLayout->addWidget(upgradesCheckBox, 3, 0);
     packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
     packagesGroup->setLayout(packagesLayout);

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(packagesGroup);
     mainLayout->addSpacing(12);
     mainLayout->addWidget(startQueryButton);
     mainLayout->addStretch(1);
     setLayout(mainLayout);
 }
