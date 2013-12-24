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
#include "QGlitterObject.h"

#include <QMap>
#include <QString>

class QGlitterAppcastItemPrivate : public QGlitterObjectData
{
	QGLITTER_DECLARE_PUBLIC(QGlitterAppcastItem);
public:
	QGlitterAppcastItemPrivate();
	QGlitterAppcastItemPrivate(const QGlitterAppcastItemPrivate &other);

	void clone(const QGlitterAppcastItemPrivate &other);

	QString deltaFrom;
	QMap<QString, QString> descriptions;
	QString mimeType;
	QString minimumSystemVersion;
	QString operatingSystem;
	QDateTime publicationDate;
	QMap<QString, QString> releaseNotesUrls;
	QString shortVersionString;
	QString signature;
	int size;
	QString title;
	QString url;
	QString version;
};
