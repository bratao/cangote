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

#include "QGlitterDownloader.h"
#include "Crypto/Crypto.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>

QGlitterDownloader::QGlitterDownloader(QObject *parent)
	: QObject(parent)
	, m_networkAccess(new QNetworkAccessManager(this))
	, m_currentDownload(0)
	, m_downloadedFile(0)
	, m_downloadedFileName("")
	, m_errorCode(QGlitterDownloader::Invalid)
{
}

void QGlitterDownloader::setPublicKey(QByteArray publicKey)
{
	m_publicKey = publicKey;
}

int QGlitterDownloader::errorCode() const
{
	return m_errorCode;
}

QString QGlitterDownloader::installerFile() const
{
	return m_downloadedFileName;
}

void QGlitterDownloader::downloadUpdate(QString url, QString signature)
{
	if (!m_networkAccess) {
		return;
	}

	if (m_currentDownload) {
		cancelDownload();
	}

	m_signature = signature;

	QString fileName = url.mid(url.lastIndexOf("/") + 1);
	m_downloadedFileName = QDir::temp().absoluteFilePath(fileName);

	m_downloadedFile = new QFile(m_downloadedFileName, this);
	if (!m_downloadedFile->open(QIODevice::ReadWrite | QIODevice::Truncate)) {
		return;
	}

	m_currentDownload = m_networkAccess->get(QNetworkRequest(QUrl(url)));
	connect(m_currentDownload, SIGNAL(readyRead()), this, SLOT(readyRead()));
	connect(m_currentDownload, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
	connect(m_currentDownload, SIGNAL(finished()), this, SLOT(finished()));
	connect(m_currentDownload, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(progress(qint64,qint64)));
}

void QGlitterDownloader::cancelDownload()
{
	m_downloadedFileName = "";

	if (m_currentDownload) {
		if (m_currentDownload->isRunning() && m_currentDownload->error() == QNetworkReply::NoError) {
			m_currentDownload->abort();
		}

		m_currentDownload->deleteLater();
		m_currentDownload = 0;
	}

	if (m_downloadedFile) {
		m_downloadedFile->remove();
		m_downloadedFile->deleteLater();
		m_downloadedFile = 0;
	}
}

void QGlitterDownloader::error(QNetworkReply::NetworkError code)
{
	if (code != QNetworkReply::NoError) {
		m_errorCode = QGlitterDownloader::UnspecifiedError;

		emit downloadFinished(m_errorCode, "");

		cancelDownload();
	}
}

void QGlitterDownloader::finished()
{
	if (!m_currentDownload) {
		return;
	}

	if (m_currentDownload->error() != QNetworkReply::NoError) {
		return;
	}

	if (m_downloadedFile) {
		m_downloadedFile->close();
		m_downloadedFile->deleteLater();
		m_downloadedFile = 0;
	}

	if (m_currentDownload) {
		m_currentDownload->deleteLater();
		m_currentDownload = 0;
	}

	QFile fileToVerify(m_downloadedFileName);
	if (fileToVerify.open(QIODevice::ReadOnly)) {
        if ((m_signature.size() == 0 && m_publicKey.size() == 0) || QGlitter::dsaVerify(fileToVerify, QByteArray::fromBase64(m_signature.toLatin1()), m_publicKey)) {
			m_errorCode = QGlitterDownloader::NoError;

			emit downloadFinished(QGlitterDownloader::NoError, m_downloadedFileName);
		} else {
			if (QGlitter::errorMessage().size()) {
				qDebug() << QGlitter::errorMessage();
			}

			emit downloadFinished(QGlitterDownloader::SignatureVerificationFailure, "");
		}
	} else {
		emit downloadFinished(QGlitterDownloader::DownloadedFileCouldNotBeRead, "");
	}

	fileToVerify.close();
}

void QGlitterDownloader::progress(qint64 bytesReceived, qint64 bytesTotal)
{
	emit downloadProgress(bytesReceived, bytesTotal);
}

void QGlitterDownloader::readyRead()
{
	m_downloadedFile->write(m_currentDownload->readAll());
}
