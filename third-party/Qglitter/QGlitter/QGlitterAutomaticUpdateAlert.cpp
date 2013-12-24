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

#include "QGlitterAutomaticUpdateAlert.h"
#include "ui_QGlitterAutomaticUpdateAlert.h"

#include <QPixmap>

QGlitterAutomaticUpdateAlert::QGlitterAutomaticUpdateAlert(QWidget *parent, Qt::WindowFlags f)
	: QDialog(parent, f | Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint)
	, m_ui(new Ui_QGlitterAutomaticUpdateAlert)
	, m_automaticDownloads(false)
	, m_delayInstall(false)
{
	if (!m_ui) {
		return;
	}

	m_ui->setupUi(this);

	connect(m_ui->enableAutomaticDownload, SIGNAL(toggled(bool)), this, SLOT(toggleAutomaticDownloads()));
	connect(m_ui->installNowButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
	connect(m_ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
	connect(m_ui->installLaterButton, SIGNAL(clicked(bool)), this, SLOT(toggleDelayInstall()));
}

QGlitterAutomaticUpdateAlert::~QGlitterAutomaticUpdateAlert()
{
	if (m_ui) {
		delete m_ui;
	}
}

void QGlitterAutomaticUpdateAlert::setAllowSkipping(bool allowSkipping)
{
	if (!m_ui) {
		return;
	}

	m_ui->cancelButton->setVisible(allowSkipping);
}

void QGlitterAutomaticUpdateAlert::setAllowDelaying(bool allowDelaying)
{
	if (!m_ui) {
		return;
	}

	m_ui->installLaterButton->setVisible(allowDelaying);
}

void QGlitterAutomaticUpdateAlert::setApplicationIcon(const QPixmap *applicationIcon)
{
	if (!m_ui) {
		return;
	}

	m_ui->iconLabel->setPixmap(applicationIcon->scaled(m_ui->iconLabel->size()));
}

bool QGlitterAutomaticUpdateAlert::delayUntilQuit() const
{
	return m_delayInstall;
}

bool QGlitterAutomaticUpdateAlert::automaticallyDownloadUpdates() const
{
	return m_automaticDownloads;
}

void QGlitterAutomaticUpdateAlert::setAutomaticallyDownloadUpdates(bool automaticallyDownloadUpdates)
{
	m_automaticDownloads = automaticallyDownloadUpdates;

	if (m_ui) {
		m_ui->enableAutomaticDownload->setChecked(automaticallyDownloadUpdates);
	}
}

void QGlitterAutomaticUpdateAlert::toggleAutomaticDownloads()
{
	m_automaticDownloads = !m_automaticDownloads;
}

void QGlitterAutomaticUpdateAlert::toggleDelayInstall()
{
	m_delayInstall = !m_delayInstall;
	accept();
}
