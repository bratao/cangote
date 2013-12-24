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

#include <QDialog>

class QNetworkReply;
class QPixmap;
class Ui_QGlitterUpdateStatus;

class QGlitterUpdateCheckStatus : public QDialog
{
	Q_OBJECT
public:
	QGlitterUpdateCheckStatus(QWidget *parent = 0, Qt::WindowFlags f = 0);
	~QGlitterUpdateCheckStatus();

	void setApplicationIcon(const QPixmap *applicationIcon);
	void setNetworkReply(QNetworkReply *networkReply);

public slots:
	void noUpdatesAvailable();

private slots:
	void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
	Ui_QGlitterUpdateStatus *m_ui;
	QNetworkReply *m_networkReply;
};