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

#include "QGlitterUpdateStatus.h"
#include "ui_QGlitterUpdateStatus.h"
#include "QGlitterCommon.h"
#include "QGlitterDownloader.h"

#include <QPixmap>

const int kStateDownloading = 0;
const int kStateFinished = 1;

QGlitterUpdateStatus::QGlitterUpdateStatus(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f | Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
	, m_ui(new Ui_QGlitterUpdateStatus)
	, m_state(kStateDownloading)
{
	if (!m_ui) {
		return;
	}

	m_ui->setupUi(this);

	m_ui->statusText->setText(QString(kQGlitterBoldText).arg(QObject::tr("Downloading Update")));
	m_ui->pushButton->setText(QObject::tr("Cancel"));

	connect(m_ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(buttonPressed()));

	m_ui->progressBar->setMinimum(0);
	m_ui->progressBar->setMaximum(0);
	m_ui->progressBar->setValue(0);
}

QGlitterUpdateStatus::~QGlitterUpdateStatus()
{
	if (m_ui) {
		delete m_ui;
	}
}

void QGlitterUpdateStatus::setApplicationIcon(const QPixmap *applicationIcon)
{
	if (!m_ui) {
		return;
	}

	m_ui->iconLabel->setPixmap(applicationIcon->scaled(m_ui->iconLabel->size()));
}

void QGlitterUpdateStatus::downloadFinished(int errorCode, QString)
{
	if (!m_ui) {
		return;
	}

	if (errorCode == QGlitterDownloader::NoError) {
		m_ui->progressBar->setMaximum(1);
		m_ui->progressBar->setValue(1);

		m_ui->progressText->setVisible(false);

		m_ui->statusText->setText(QString(kQGlitterBoldText).arg(QObject::tr("Update Downloaded")));

		m_ui->pushButton->setText(QObject::tr("Install and Restart"));

		m_state = kStateFinished;
	} else {
		m_ui->progressBar->setMaximum(1);
		m_ui->progressBar->setValue(1);

		m_ui->progressText->setVisible(false);

		if (errorCode == QGlitterDownloader::DownloadedFileCouldNotBeRead) {
			m_ui->statusText->setText(QString(kQGlitterBoldText).arg(QObject::tr("Could Not Read Downloaded Update")));
		} else if (errorCode == QGlitterDownloader::SignatureVerificationFailure) {
			m_ui->statusText->setText(QString(kQGlitterBoldText).arg(QObject::tr("Could Not Verify Update Signature")));
		} else {
			m_ui->statusText->setText(QString(kQGlitterBoldText).arg(QObject::tr("Error Downloading Update")));
		}

		m_ui->pushButton->setText(QObject::tr("OK"));
	}
}

static QString humanReadableSize(qint64 size)
{
    double num = size;
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";
    QStringListIterator i(list);
    QString unit("bytes");
    while (num >= 1024.0 && i.hasNext()) {
        unit = i.next();
        num /= 1024.0;
    }
    return QString("%1 %2").arg(num, 0, 'f', 1).arg(unit);
}

void QGlitterUpdateStatus::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	if (!m_ui) {
		return;
	}

	m_ui->progressBar->setMaximum(bytesTotal);
	m_ui->progressBar->setValue(bytesReceived);
	m_ui->progressText->setText(QObject::tr("Downloaded %1 of %2").arg(humanReadableSize(bytesReceived)).arg(humanReadableSize(bytesTotal)));
}

void QGlitterUpdateStatus::buttonPressed()
{
	if (m_state == kStateDownloading) {
		reject();
	} else {
		accept();
	}
}
