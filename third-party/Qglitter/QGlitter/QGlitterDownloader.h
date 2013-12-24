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

#pragma once

#include <QObject>
#include <QNetworkReply>

class QFile;

class QGlitterDownloader : public QObject
{
	Q_OBJECT
public:
	enum DownloadError
	{
		NoError = 0,

		SignatureVerificationFailure,
		DownloadedFileCouldNotBeRead,
		UnspecifiedError,

		Invalid = 0xffff,
	};

	QGlitterDownloader(QObject *parent = 0);

	void setPublicKey(QByteArray publicKey);

	int errorCode() const;
	QString installerFile() const;

signals:
	void downloadFinished(int errorCode, QString pathToFile);
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

public slots:
	void downloadUpdate(QString url, QString signature);
	void cancelDownload();

private slots:
	void error(QNetworkReply::NetworkError code);
	void finished();
	void progress(qint64 bytesReceived, qint64 bytesTotal);
	void readyRead();

private:
	QNetworkAccessManager *m_networkAccess;
	QNetworkReply *m_currentDownload;
	QFile *m_downloadedFile;
	QString m_downloadedFileName;
	QString m_signature;
	QByteArray m_publicKey;
	int m_errorCode;
};
