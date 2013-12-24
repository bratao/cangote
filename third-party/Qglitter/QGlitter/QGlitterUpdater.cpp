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

#include "QGlitterUpdater.h"
#include "QGlitterUpdater_p.h"
#include "QGlitterAppcast.h"
#include "QGlitterDefaultVersionComparator.h"
#include "QGlitterDownloader.h"
#include "QGlitterUpdateAlert.h"
#include "QGlitterUpdateCheckStatus.h"
#include "QGlitterUpdateStatus.h"
#include "QGlitterAutomaticUpdateAlert.h"
#include "Crypto/Crypto.h"
#include "Platform/Platform.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QLocale>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSettings>
#include <QTimer>

static const char * const kIsFirstLaunch = "QGlitter/IsFirstLaunch";
static const char * const kAutomaticUpdateCheck = "QGlitter/AutomaticCheck";
static const char * const kAutomaticDownload = "QGlitter/AutomaticDownload";
static const char * const kCheckInterval = "QGlitter/CheckInterval";
static const char * const kIgnoredVersions = "QGlitter/IgnoredVersions";
static const char * const kLastCheckTime = "QGlitter/LastUpdateCheck";

static const qint64 kNeverUpdated = 0;
static const int kOneHour = 60 * 60;
static const int kOneDay = kOneHour * 24;

static const int kBackgroundDownload = 0;
static const int kInteractiveDownload = 1;

QGlitterUpdaterPrivate::QGlitterUpdaterPrivate()
	: applicationIcon(0)
	, internalVersion()
	, automaticCheck(true)
	, automaticDownload(false)
	, checkInterval(kOneDay)
	, defaultLanguage("en")
	, feedUrl("")
	, allowVersionSkipping(true)
	, allowDelayInstallUntilQuit(true)
	, isCheckingForUpdates(false)
	, isInteractive(false)
	, lastUpdateCheck(kNeverUpdated)
	, networkAccess(0)
	, settings(0)
	, timer(0)
	, downloader(0)
	, pendingUpdate("")
	, versionComparator(0)
{
}

QGlitterUpdater::QGlitterUpdater(bool allowVersionSkipping, bool allowDelayInstalUntilQuit, int checkInterval, QObject *parent)
	: QObject(parent)
	, QGlitterObject(new QGlitterUpdaterPrivate)
{
	QGLITTER_D(QGlitterUpdater);

	d->checkInterval = (checkInterval == 0) ? kOneDay : checkInterval;
	d->allowVersionSkipping = allowVersionSkipping;
	d->allowDelayInstallUntilQuit = allowDelayInstalUntilQuit;

	QGlitter::cryptoInit();

	d->defaultLanguage = QLocale::system().name();
	d->defaultLanguage.truncate(d->defaultLanguage.lastIndexOf('_'));

	connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(aboutToQuit()));

	d->timer = new QTimer(this);
	connect(d->timer, SIGNAL(timeout()), this, SLOT(updateTimeout()));

	QString settingsDomain = QString("%1.%2").arg(qApp->organizationDomain()).arg(qApp->applicationName().replace(' ', ""));
	d->settings = new QSettings(QSettings::UserScope, "QGlitter", settingsDomain, this);

	d->automaticCheck = d->settings->value(kAutomaticUpdateCheck, true).toBool();
	d->automaticDownload = d->settings->value(kAutomaticDownload, false).toBool();
	d->checkInterval = d->settings->value(kCheckInterval, kOneDay).toInt();
	d->lastUpdateCheck = d->settings->value(kLastCheckTime, kNeverUpdated).value<qint64>();
	d->ignoredVersions = d->settings->value(kIgnoredVersions, QStringList()).toStringList();

	if (!d->settings->value(kIsFirstLaunch, true).toBool()) {
		if (d->lastUpdateCheck == kNeverUpdated) {
			d->timer->start(0);
		} else {
			qint64 currentTime = QDateTime::currentMSecsSinceEpoch() / 1000;
			qint64 timeUntilNextCheck = d->checkInterval - (currentTime - d->lastUpdateCheck);
			qint64 nextDueTime = (timeUntilNextCheck < 0) ? 0 : timeUntilNextCheck;

			d->timer->start(nextDueTime * 1000);
		}
	}

	d->settings->setValue(kIsFirstLaunch, false);

	d->networkAccess = new QNetworkAccessManager(this);
	connect(d->networkAccess, SIGNAL(finished(QNetworkReply *)), this, SLOT(appcastDownloaded(QNetworkReply *)));

	d->downloader = new QGlitterDownloader(this);
}

QGlitterUpdater::~QGlitterUpdater()
{
}

const QPixmap *QGlitterUpdater::applicationIcon() const
{
	const QGLITTER_D(QGlitterUpdater);
	return d->applicationIcon.data();
}

void QGlitterUpdater::setApplicationIcon(const QPixmap *icon)
{
	QGLITTER_D(QGlitterUpdater);
	d->applicationIcon.reset(new QPixmap(*icon));
}

bool QGlitterUpdater::automaticallyCheckForUpdates() const
{
	const QGLITTER_D(QGlitterUpdater);
	return d->automaticCheck;
}

void QGlitterUpdater::setAutomaticallyCheckForUpdates(bool automaticallyCheckForUpdates)
{
	QGLITTER_D(QGlitterUpdater);
	d->automaticCheck = automaticallyCheckForUpdates;
	d->settings->setValue(kAutomaticUpdateCheck, d->automaticCheck);
}

bool QGlitterUpdater::automaticallyDownloadUpdates() const
{
	const QGLITTER_D(QGlitterUpdater);
	return d->automaticDownload;
}

void QGlitterUpdater::setAutomaticallyDownloadUpdates(bool automaticallyDownloadUpdates)
{
	QGLITTER_D(QGlitterUpdater);
	d->automaticDownload = automaticallyDownloadUpdates;
	d->settings->setValue(kAutomaticDownload, d->automaticDownload);
}

int QGlitterUpdater::checkInterval() const
{
	const QGLITTER_D(QGlitterUpdater);
	return d->checkInterval;
}

void QGlitterUpdater::setCheckInterval(int checkInterval)
{
	QGLITTER_D(QGlitterUpdater);

	if (checkInterval < kOneHour) {
		checkInterval = kOneHour;
	}

	d->checkInterval = checkInterval;
	d->settings->setValue(kCheckInterval, d->checkInterval);

	if (d->timer) {
		d->timer->setInterval(d->checkInterval * 1000);
	}
}

QString QGlitterUpdater::defaultLanguage() const
{
	const QGLITTER_D(QGlitterUpdater);
	return d->defaultLanguage;
}

void QGlitterUpdater::setDefaultLanguage(QString language)
{
	QGLITTER_D(QGlitterUpdater);
	d->defaultLanguage = language;
}

QString QGlitterUpdater::feedUrl() const
{
	const QGLITTER_D(QGlitterUpdater);
	return d->feedUrl;
}

void QGlitterUpdater::setFeedUrl(QString feedUrl)
{
	QGLITTER_D(QGlitterUpdater);
	d->feedUrl = feedUrl;
}

QString QGlitterUpdater::internalVersion() const
{
	const QGLITTER_D(QGlitterUpdater);
	return d->internalVersion;
}

void QGlitterUpdater::setInternalVersion(QString internalVersion)
{
	QGLITTER_D(QGlitterUpdater);
	d->internalVersion = internalVersion;
}

QByteArray QGlitterUpdater::publicKey() const
{
	const QGLITTER_D(QGlitterUpdater);
	return d->publicKey;
}

void QGlitterUpdater::setPublicKey(const QByteArray &publicKey)
{
	QGLITTER_D(QGlitterUpdater);
	d->publicKey = publicKey;
	d->downloader->setPublicKey(publicKey);
}

void QGlitterUpdater::setVersionComparator(VersionComparator comparator)
{
	QGLITTER_D(QGlitterUpdater);
	d->versionComparator = comparator;
}

int QGlitterUpdater::compareVersions(const QString &lhs, const QString &rhs) const
{
	const QGLITTER_D(QGlitterUpdater);

	if (d->versionComparator == 0) {
		return QGlitter::defaultVersionComparator(lhs, rhs);
	}

	return d->versionComparator(lhs, rhs);
}

void QGlitterUpdater::checkForUpdates(const QGlitterAppcast &appcast)
{
	QGLITTER_D(QGlitterUpdater);

	QString currentVersion;
	if (d->internalVersion.size()) {
		currentVersion = d->internalVersion;
	} else {
		currentVersion = qApp->applicationVersion();
	}

	QGlitterAppcastItem currentBestUpdate;
	currentBestUpdate.setVersion(currentVersion);

	QList<QGlitterAppcastItem> appcastItems = appcast.items();
	for (int i = 0; i < appcastItems.size(); ++i) {
		if (!d->isInteractive) {
			if (d->ignoredVersions.indexOf(appcastItems[i].version()) >= 0) {
				continue;
			}
		}

		if (appcastItems[i].operatingSystem().length() > 0 && appcastItems[i].operatingSystem().compare(QGlitter::os(), Qt::CaseInsensitive) != 0) {
			continue;
		}

		if (appcastItems[i].minimumSystemVersion().length() > 0 && QGlitter::osVersionLessThan(appcastItems[i].minimumSystemVersion().toLower())) {
			continue;
		}

		if ((compareVersions(appcastItems[i].version(), currentBestUpdate.version()) > 0) ||
			((compareVersions(appcastItems[i].version(), currentBestUpdate.version()) >= 0) && appcastItems[i].deltaFrom() == currentVersion)) {
			currentBestUpdate = appcastItems[i];
		}
	}

	if (compareVersions(currentBestUpdate.version(), currentVersion) > 0) {
		emit foundUpdate(currentBestUpdate);

		if (!d->automaticDownload) {

			QGlitterUpdateAlert *updateAlert = new QGlitterUpdateAlert();

			if (d->applicationIcon) {
				updateAlert->setApplicationIcon(d->applicationIcon.data());
			}
			updateAlert->setAutomaticallyDownloadUpdates(d->automaticDownload);
			updateAlert->setDefaultLanguage(d->defaultLanguage);
			updateAlert->setAppcastItem(currentBestUpdate);
			updateAlert->setAllowSkipping(d->allowVersionSkipping);

			if (updateAlert->exec()) {
				downloadAndInstall(kInteractiveDownload, currentBestUpdate);
			}

			if (updateAlert->skipVersion()) {
				d->ignoredVersions.append(currentBestUpdate.version());
				d->settings->setValue(kIgnoredVersions, d->ignoredVersions);
			}

			if (updateAlert->automaticallyDownloadUpdates()) {
				setAutomaticallyDownloadUpdates(updateAlert->automaticallyDownloadUpdates());
			}

			updateAlert->deleteLater();
		} else {
			downloadAndInstall(kBackgroundDownload, currentBestUpdate);
		}
	} else {
		emit noUpdatesAvailable();
	}
}

void QGlitterUpdater::aboutToQuit()
{
	QGLITTER_D(QGlitterUpdater);

	if (d->pendingUpdate.length() > 0) {
		emit installingUpdate();
		if (QGlitter::installUpdate(d->pendingUpdate)) {
			emit finishedInstallingUpdate();
		}
	}
}

void QGlitterUpdater::automaticUpdateDownloaded(int errorCode, QString installerPath)
{
	QGLITTER_D(QGlitterUpdater);

	if (errorCode != QGlitterDownloader::NoError) {
		return;
	}

	// Disconnect in case this update is canceled and the next update is not automatic
	disconnect(d->downloader, SIGNAL(downloadFinished(int, QString)), this, SLOT(automaticUpdateDownloaded(int, QString)));

	// TODO: should probably allow for automatic installing as well
	QGlitterAutomaticUpdateAlert *updateAlert = new QGlitterAutomaticUpdateAlert();

	if (d->applicationIcon) {
		updateAlert->setApplicationIcon(d->applicationIcon.data());
	}
	updateAlert->setAllowSkipping(d->allowVersionSkipping);
	updateAlert->setAllowDelaying(d->allowDelayInstallUntilQuit);

	updateAlert->exec();
	updateAlert->deleteLater();

	if (updateAlert->result() == QDialog::Rejected) {
		emit updateCanceled();
	} else {
		if (d->allowDelayInstallUntilQuit && updateAlert->delayUntilQuit()) {
			d->pendingUpdate = installerPath;
		} else {
			emit installingUpdate();
			if (QGlitter::installUpdate(installerPath)) {
				emit finishedInstallingUpdate();
			}
		}
	}
}

void QGlitterUpdater::downloadAndInstall(int mode, const QGlitterAppcastItem &update)
{
	QGLITTER_D(QGlitterUpdater);

	d->downloader->downloadUpdate(update.url(), update.signature());

	if (mode == kInteractiveDownload) {
		QGlitterUpdateStatus *downloadStatus = new QGlitterUpdateStatus();

		if (d->applicationIcon) {
			downloadStatus->setApplicationIcon(d->applicationIcon.data());
		}

		connect(d->downloader, SIGNAL(downloadProgress(qint64, qint64)), downloadStatus, SLOT(downloadProgress(qint64, qint64)));
		connect(d->downloader, SIGNAL(downloadFinished(int, QString)), downloadStatus, SLOT(downloadFinished(int, QString)));

		downloadStatus->exec();
		downloadStatus->deleteLater();

		if (downloadStatus->result() == QDialog::Rejected) {
			d->downloader->cancelDownload();
			emit updateCanceled();
		} else if (d->downloader->errorCode() == QGlitterDownloader::NoError) {
			emit installingUpdate();
			if (QGlitter::installUpdate(d->downloader->installerFile())) {
				emit finishedInstallingUpdate();
			}
		}
	} else {
		connect(d->downloader, SIGNAL(downloadFinished(int, QString)), this, SLOT(automaticUpdateDownloaded(int, QString)));
	}
}

void QGlitterUpdater::updateCheck()
{
	QGLITTER_D(QGlitterUpdater);

	if (d->isCheckingForUpdates) {
		return;
	}

	d->isInteractive = true;
	d->isCheckingForUpdates = true;
	QNetworkReply *reply = d->networkAccess->get(QNetworkRequest(QUrl(d->feedUrl)));

	QGlitterUpdateCheckStatus *updateCheckStatus = new QGlitterUpdateCheckStatus();
	connect(this, SIGNAL(foundUpdate(const QGlitterAppcastItem &)), updateCheckStatus, SLOT(close()));
	connect(this, SIGNAL(noUpdatesAvailable()), updateCheckStatus, SLOT(noUpdatesAvailable()));
	connect(this, SIGNAL(errorLoadingAppcast()), updateCheckStatus, SLOT(noUpdatesAvailable()));

	updateCheckStatus->setNetworkReply(reply);
	if (d->applicationIcon) {
		updateCheckStatus->setApplicationIcon(d->applicationIcon.data());
	}

	updateCheckStatus->exec();
	updateCheckStatus->deleteLater();

	d->isInteractive = false;
}

void QGlitterUpdater::backgroundUpdateCheck()
{
	QTimer::singleShot(0, this, SLOT(updateTimeout()));
}

void QGlitterUpdater::appcastDownloaded(QNetworkReply *reply)
{
	QGLITTER_D(QGlitterUpdater);

	if (reply->error() == QNetworkReply::NoError) {
		QGlitterAppcast appcast;

		if (appcast.read(reply)) {
			emit finishedLoadingAppcast(appcast);
			checkForUpdates(appcast);
		} else {
			emit errorLoadingAppcast();
		}
	}

	d->isCheckingForUpdates = false;
	d->lastUpdateCheck = QDateTime::currentMSecsSinceEpoch() / 1000;
	d->timer->setInterval(d->checkInterval * 1000);

	reply->deleteLater();
}

void QGlitterUpdater::updateTimeout()
{
	QGLITTER_D(QGlitterUpdater);

	if (d->isCheckingForUpdates) {
		return;
	}

	d->isCheckingForUpdates = true;
	d->networkAccess->get(QNetworkRequest(QUrl(d->feedUrl)));
}

