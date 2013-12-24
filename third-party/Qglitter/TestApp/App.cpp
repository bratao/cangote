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

#include "App.h"

#include "QGlitter/QGlitter"

#include <QApplication>
#include <QFile>

static const int kOneHour = 1 * 60 * 60;

App::App(QWidget *parent, Qt::WindowFlags f)
	: QWidget(parent, f)
	, m_updater(new QGlitterUpdater(true, true, kOneHour, this))
{
	QFile publicKeyFile(":/Resources/dsa_pub.pem");
	if (publicKeyFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		m_updater->setPublicKey(publicKeyFile.readAll());
		publicKeyFile.close();
	}

	QPixmap applicationIcon(":/Resources/TestAppIcon.png");
	m_updater->setApplicationIcon(&applicationIcon);

    m_updater->setFeedUrl("http://localhost/appfeed.xml");

	connect(m_updater, SIGNAL(finishedInstallingUpdate()), qApp, SLOT(quit()));
}

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

	application.setApplicationName("UpdateTest");
    application.setApplicationVersion("0.1.0");
	application.setOrganizationDomain("com.aegos.qglitter.test");

	App *app = new App();
	app->show();

	return application.exec();
}
