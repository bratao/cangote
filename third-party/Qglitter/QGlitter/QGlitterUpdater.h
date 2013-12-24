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

#include "QGlitterObject.h"
#include "QGlitterConfig.h"

#include <QObject>

class QGlitterAppcast;
class QGlitterAppcastItem;
class QNetworkReply;
class QPixmap;

typedef int (*VersionComparator)(const QString &, const QString &);

class QGlitterUpdaterPrivate;
class QGLITTER_EXPORTED QGlitterUpdater : public QObject, public QGlitterObject
{
	Q_OBJECT
public:
	QGlitterUpdater(bool allowVersionSkipping = true, bool allowDelayInstalUntilQuit = true, int checkInterval = 0, QObject *parent = 0);
	~QGlitterUpdater();

	const QPixmap *applicationIcon() const;
	void setApplicationIcon(const QPixmap *icon);

	bool automaticallyCheckForUpdates() const;
	void setAutomaticallyCheckForUpdates(bool automaticallyCheckForUpdates);

	bool automaticallyDownloadUpdates() const;
	void setAutomaticallyDownloadUpdates(bool automaticallyDownloadUpdates);

	int checkInterval() const;
	void setCheckInterval(int checkInterval);

	QString defaultLanguage() const;
	void setDefaultLanguage(QString language);

	QString feedUrl() const;
	void setFeedUrl(QString feedUrl);

	QString internalVersion() const;
	void setInternalVersion(QString internalVersion);

	QByteArray publicKey() const;
	void setPublicKey(const QByteArray &publicKey);

	void setVersionComparator(VersionComparator comparator);

signals:
	void errorLoadingAppcast();
	void finishedInstallingUpdate();
	void finishedLoadingAppcast(const QGlitterAppcast &appcast);
	void foundUpdate(const QGlitterAppcastItem &appcastItem);
	void installingUpdate();
	void noUpdatesAvailable();
	void updateCanceled();

public slots:
	void backgroundUpdateCheck();
	void updateCheck();

private slots:
	void aboutToQuit();
	void automaticUpdateDownloaded(int errorCode, QString installerPath);
	void appcastDownloaded(QNetworkReply *reply);
	void updateTimeout();

private:
	void checkForUpdates(const QGlitterAppcast &appcast);
	int compareVersions(const QString &lhs, const QString &rhs) const;
	void downloadAndInstall(int mode, const QGlitterAppcastItem &update);

	QGLITTER_DECLARE_PRIVATE(QGlitterUpdater);
	QGLITTER_DISABLE_COPY(QGlitterUpdater);
};
