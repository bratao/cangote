// Copyright (c) 2012 AlterEgo Studios
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "QGlitterUpdateCheckStatus.h"
#include "ui_QGlitterUpdateStatus.h"
#include "QGlitterCommon.h"

#include <QNetworkReply>

QGlitterUpdateCheckStatus::QGlitterUpdateCheckStatus(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f | Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
	, m_ui(new Ui_QGlitterUpdateStatus)
	, m_networkReply(0)
{
	if (!m_ui) {
		return;
	}

	m_ui->setupUi(this);

	m_ui->statusText->setText(QString(kQGlitterBoldText).arg(QObject::tr("Checking for Updates")));
	m_ui->pushButton->setText(QObject::tr("Cancel"));

	connect(m_ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(reject()));

	m_ui->progressText->setVisible(false);

	m_ui->progressBar->setMinimum(0);
	m_ui->progressBar->setMaximum(0);
	m_ui->progressBar->setValue(0);
}

QGlitterUpdateCheckStatus::~QGlitterUpdateCheckStatus()
{
	if (m_ui) {
		delete m_ui;
	}
}

void QGlitterUpdateCheckStatus::setApplicationIcon(const QPixmap *applicationIcon)
{
	if (!m_ui) {
		return;
	}

	m_ui->iconLabel->setPixmap(applicationIcon->scaled(m_ui->iconLabel->size()));
}

void QGlitterUpdateCheckStatus::setNetworkReply(QNetworkReply *networkReply)
{
	if (!networkReply) {
		return;
	}

	connect(networkReply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(downloadProgress(qint64, qint64)));
	m_networkReply = networkReply;
}

void QGlitterUpdateCheckStatus::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	if (!m_ui) {
		return;
	}

	m_ui->progressBar->setMaximum(bytesTotal);
	m_ui->progressBar->setValue(bytesReceived);
}

void QGlitterUpdateCheckStatus::noUpdatesAvailable()
{
	if (!m_ui) {
		return;
	}

	m_ui->statusText->setText(QString(kQGlitterBoldText).arg(QObject::tr("No Updates Found")));
	m_ui->pushButton->setText(QObject::tr("OK"));

	m_ui->progressBar->setMinimum(0);
	m_ui->progressBar->setMaximum(1);
	m_ui->progressBar->setValue(1);
}
