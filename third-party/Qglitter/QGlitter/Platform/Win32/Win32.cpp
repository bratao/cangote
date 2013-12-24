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

#include <QIODevice>
#include <QSysInfo>

#include "Windows.h"

bool QGlitter::installUpdate(const QString &installerPath)
{
    MoveFileExA(installerPath.toLatin1().data(), NULL, MOVEFILE_DELAY_UNTIL_REBOOT);

	QString command = QString("start %1").arg(installerPath);
    return system(command.toLatin1().data()) == 0;
}

bool QGlitter::osVersionLessThan(QString other)
{
	switch (QSysInfo::WindowsVersion) {
	case QSysInfo::WV_XP:
		return other != "xp";

	case QSysInfo::WV_VISTA:
		return other == "7" || other == "8";

	case QSysInfo::WV_WINDOWS7:
		return other == "8";

	//case QSysInfo::WV_WINDOWS8:
	//	return "8";

	default:
		return false;
	}

	return false;
}

QString QGlitter::os()
{
	return "windows";
}
