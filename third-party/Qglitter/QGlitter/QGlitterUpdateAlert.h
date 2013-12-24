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

#include "QGlitterAppcastItem.h"

#include <QDialog>
#include <QGlitterDownloader.h>

class QPixmap;
class Ui_QGlitterUpdateAlert;

class QGlitterUpdateAlert : public QDialog
{
	Q_OBJECT
public:
	QGlitterUpdateAlert(QWidget *parent = 0, Qt::WindowFlags f = 0);
	~QGlitterUpdateAlert();

	void setAllowSkipping(bool allowSkipping);

	void setAppcastItem(const QGlitterAppcastItem &appcastItem);

	void setApplicationIcon(const QPixmap *applicationIcon);

	bool automaticallyDownloadUpdates() const;
	void setAutomaticallyDownloadUpdates(bool automaticallyDownloadUpdates);

	void setDefaultLanguage(const QString &defaultLanguage);

	bool skipVersion();

private slots:
	void toggleSkipVersion();
	void toggleAutomaticDownloads();
    void downloadFinished(int errorCode, QString pathToFile);

private:
	Ui_QGlitterUpdateAlert *m_ui;

	QString m_defaultLanguage;
	QGlitterAppcastItem m_appcastItem;
	bool m_skipVersion;
	bool m_automaticDownloads;
    QGlitterDownloader m_releaseNotesDownloader;
    
    void downloadReleaseNotes(const QString &url);
};
