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

     Code originaly from Olivier Teulière <ipkiss @@ gmail.com>
*/

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QMessageBox>

#include <QSettings>
#include <QDate>
#include <QVariant>

#include "update_checker.h"


#include "cangote.h"
#include "core/cangotecore.h"
#include "core/gnunet/gnunet.h"
#include "preferences/preferences.h"




using namespace std;


#define URL "http://www.cangote.org/getversion"



UpdateChecker::UpdateChecker(QObject *parent)
    : QObject(parent)
{
}


void UpdateChecker::checkForUpdate()
{

    // Do nothing if the updates are deactivated in the preferences
    if (!thePrefs->checkNewVersion())
        return;

    QString dateStr = thePrefs->nextCheckDate();
    QDate nextCheckDate = QDate::fromString(dateStr, Qt::ISODate);

    // If the next date for the check is in the future, nothing to do
    if (nextCheckDate.isValid() && nextCheckDate > QDate::currentDate())
        return;

    emit notifyInfo("Checking for updates...");

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(updateCheckFinished(QNetworkReply*)));
    networkManager->get(QNetworkRequest(QUrl(URL)));
}


void UpdateChecker::updateCheckFinished(QNetworkReply *iReply)
{
    // Check at most once a week
    const int nbDaysToWait = 7;

    // Save the new check date
    QDate nextCheckDate = QDate::currentDate().addDays(nbDaysToWait);

    thePrefs->setNextCheckDate(nextCheckDate.toString(Qt::ISODate));


    if (iReply->error() == QNetworkReply::NoError)
    {
        qDebug() << ("Update file retrieved successfully");
        QByteArray data = iReply->readAll().trimmed();
        bool newer = isNewer(data);

        if (newer)
        {
            qWarning() << "New version available: " << data;
            showNewVersion(data);
        }
        else
            emit notifyInfo("Update check completed, no new version available");
    }
    else
    {
        qCritical() << "Could not retrieve update file: " << iReply->errorString();
        emit notifyInfo("Update check failed. Please check your internet connection");
    }

    // Delete the reply
    iReply->deleteLater();
}


UpdateChecker::VersionNumber UpdateChecker::parseVersionNumber(QString iVersion) const
{
    VersionNumber vn;

    // A version number has the following form: 1.12a-git (where 'a' is an
    // optional letter, and -git is optional as well)
    // Regexp to the rescue!
    QRegExp re("^(\\d+)\\.(\\d+)([a-z])?(-git.*)?$");
    re.setPatternSyntax(QRegExp::RegExp2);
    if (re.indexIn(iVersion) == -1)
    {
        qWarning() << "Error parsing version number: " << iVersion;
        vn.major = -1;
        vn.minor = -1;
        vn.letter = 0;
        return vn;
    }
    vn.major = re.cap(1).toInt();
    vn.minor = re.cap(2).toInt();
    vn.letter = 0;
    if (re.pos(3) != -1)
        vn.letter = re.cap(3)[0].toLatin1();
    vn.suffix = re.cap(4);

    qDebug() << "Parsed version number: " << vn.major << "." << vn.minor <<
              (vn.letter ? QString(vn.letter) : "") << vn.suffix <<
              " (from '" << iVersion << "')";
    return vn;
}


bool UpdateChecker::isNewer(QString iNewVersion) const
{
    // Before doing a lot of work, check the most common case first
    if (iNewVersion == PACKAGE_VERSION)
        return false;

    // Parse the 2 version strings
    const VersionNumber &currVN = parseVersionNumber(PACKAGE_VERSION);
    const VersionNumber &newVN = parseVersionNumber(iNewVersion);
    if (currVN.major == -1 || newVN.major == -1)
        return false;

    // We have the following order:
    //  - 1.* < 2.*
    //  - 1.12* < 1.12a* < 1.12b* < ... < 1.13*
    //  - 1.12 < 1.13-git < 1.13

    // Compare the major numbers
    if (newVN.major > currVN.major)
        return true;
    if (newVN.major < currVN.major)
        return false;

    // Compare the minor numbers
    if (newVN.minor > currVN.minor)
        return true;
    if (newVN.minor < currVN.minor)
        return false;

    // Compare the letters
    if (newVN.letter != 0 || currVN.letter != 0)
    {
        if (newVN.letter == 0 || currVN.letter == 0)
            return currVN.letter == 0;
        if (newVN.letter > currVN.letter)
            return true;
        if (newVN.letter < currVN.letter)
            return false;
    }

    // Compare the suffixes
    if (newVN.suffix != "" || currVN.suffix != "")
    {
        if (newVN.suffix == "" || currVN.suffix == "")
            return newVN.suffix == "";
    }

    // If we reach this point, the 2 version numbers have (different) suffixes.
    // This is not expected, so we are conservative...
    qWarning() <<"Cannot compare version numbers: " <<
             PACKAGE_VERSION << " and " << iNewVersion;
    return false;
}


void UpdateChecker::showNewVersion(QString iVersion) const
{
    const QString url = ("http://www.cangote.org/newversion");
    // TRANSLATORS: Here %1 represents a version number.
    QString msg = QString("Cangote %1 is available.").arg(iVersion);
    msg += "<br>" + QString("You can download it from %1.")
        .arg(QString("<a href=\"%1\">%2</a>").arg(url).arg(url));
    msg += "<br><br>" + QString("This message will be displayed at most once a week.");
    QMessageBox infoBox(QMessageBox::Information, QString("New version available"),
                         msg, QMessageBox::Ok);
    infoBox.setTextFormat(Qt::RichText);
    infoBox.exec();
}


