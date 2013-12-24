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

#include <QDateTime>
#include <QMap>
#include <QString>

class QGlitterAppcastItemPrivate;
class QGLITTER_EXPORTED QGlitterAppcastItem : public QGlitterObject
{
public:
	QGlitterAppcastItem();
	QGlitterAppcastItem(const QGlitterAppcastItem &other);

	QGlitterAppcastItem &operator=(const QGlitterAppcastItem &rhs);

	QString deltaFrom() const;
	void setDeltaFrom(QString deltaFrom);

	QMap<QString, QString> descriptions() const;
	void addDescription(QString language, QString description);

	QString mimeType() const;
	void setMimeType(QString mimeType);

	QString minimumSystemVersion() const;
	void setMinimumSystemVersion(QString minimumSystemVersion);

	QString operatingSystem() const;
	void setOperatingSystem(QString operatingSystem);

	QDateTime publicationDate() const;
	void setPublicationDate(QDateTime publicationDate);

	QMap<QString, QString> releaseNotesUrls() const;
	void addReleaseNotesUrl(QString language, QString releaseNotesUrl);

	QString shortVersionString() const;
	void setShortVersionString(QString shortVersionString);

	QString signature() const;
	void setSignature(QString signature);

	int size() const;
	void setSize(int size);

	QString title() const;
	void setTitle(QString title);

	QString url() const;
	void setUrl(QString url);

	QString version() const;
	void setVersion(QString version);

private:
	QGLITTER_DECLARE_PRIVATE(QGlitterAppcastItem);
};
