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

#include "QGlitterUpdater.h"
#include "QGlitterObject.h"

#include <QStringList>

class QNetworkAccessManager;
class QPixmap;
class QSettings;
class QGlitterDownloader;
class QTimer;

class QGlitterUpdaterPrivate : public QGlitterObjectData
{
	QGLITTER_DECLARE_PUBLIC(QGlitterUpdater);
public:
	QGlitterUpdaterPrivate();

	QScopedPointer<QPixmap> applicationIcon;
	QString internalVersion;
	QByteArray publicKey;

	bool automaticCheck;
	bool automaticDownload;
	int checkInterval;
	QString defaultLanguage;
	QString feedUrl;
	QStringList ignoredVersions;

	bool allowVersionSkipping;
	bool allowDelayInstallUntilQuit;
	bool isCheckingForUpdates;
	bool isInteractive;
	qint64 lastUpdateCheck;
	QNetworkAccessManager *networkAccess;
	QSettings *settings;
	QTimer *timer;
	QGlitterDownloader *downloader;
	QString pendingUpdate;

	VersionComparator versionComparator;
};
