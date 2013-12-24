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

#include "Platform/Platform.h"

#include <QDir>
#include <QIODevice>
#include <QSysInfo>

#include <CoreFoundation/CoreFoundation.h>
#include <Security/Security.h>

#include <cstdlib>

#include <QDebug>

bool QGlitter::installUpdate(const QString &installerPath)
{
	QString command = QString("hdiutil attach '%1' -autoopen; rm '%1'").arg(installerPath);
	bool success = system(command.toAscii().data()) == 0;

	return success;
}

bool QGlitter::osVersionLessThan(QString other)
{
	switch (QSysInfo::MacintoshVersion) {
	case QSysInfo::MV_10_5:
		return "10.5" < other;

	case QSysInfo::MV_10_6:
		return "10.6" < other;

	case QSysInfo::MV_10_7:
		return "10.7" < other;

	case QSysInfo::MV_10_8:
		return "10.8" < other;

	default:
		return false;
	}

	return false;
}

QString QGlitter::os()
{
	return "osx";
}
