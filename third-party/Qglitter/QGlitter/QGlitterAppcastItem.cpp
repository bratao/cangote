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

#include "QGlitterAppcastItem.h"
#include "QGlitterAppcastItem_p.h"

QGlitterAppcastItemPrivate::QGlitterAppcastItemPrivate()
	: deltaFrom("")
	, descriptions()
	, mimeType("")
	, minimumSystemVersion("")
	, operatingSystem("")
	, publicationDate()
	, releaseNotesUrls()
	, shortVersionString("")
	, signature("")
	, size(0)
	, title("")
	, url("")
	, version("")
{
}

QGlitterAppcastItemPrivate::QGlitterAppcastItemPrivate(const QGlitterAppcastItemPrivate &other)
{
	clone(other);
}

void QGlitterAppcastItemPrivate::clone(const QGlitterAppcastItemPrivate &other)
{
	deltaFrom = other.deltaFrom;
	descriptions = other.descriptions;
	mimeType = other.mimeType;
	minimumSystemVersion = other.minimumSystemVersion;
	operatingSystem = other.operatingSystem;
	publicationDate = other.publicationDate;
	releaseNotesUrls = other.releaseNotesUrls;
	shortVersionString = other.shortVersionString;
	signature = other.signature;
	size = other.size;
	title = other.title;
	url = other.url;
	version = other.version;
}

QGlitterAppcastItem::QGlitterAppcastItem()
	: QGlitterObject(new QGlitterAppcastItemPrivate)
{
}

QGlitterAppcastItem::QGlitterAppcastItem(const QGlitterAppcastItem &other)
	: QGlitterObject(new QGlitterAppcastItemPrivate(*other.qglitter_d_func()))
{
}

QGlitterAppcastItem &QGlitterAppcastItem::operator=(const QGlitterAppcastItem &rhs)
{
	if (&rhs == this) {
		return *this;
	}

	*qglitter_d_func() = *rhs.qglitter_d_func();

	return *this;
}

QString QGlitterAppcastItem::deltaFrom() const
{
	const QGLITTER_D(QGlitterAppcastItem);
	return d->deltaFrom;
}

void QGlitterAppcastItem::setDeltaFrom(QString deltaFrom)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->deltaFrom = deltaFrom;
}

QMap<QString, QString> QGlitterAppcastItem::descriptions() const
{
	const QGLITTER_D(QGlitterAppcastItem);
	return d->descriptions;
}

void QGlitterAppcastItem::addDescription(QString language, QString description)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->descriptions[language] = description;
}

QString QGlitterAppcastItem::mimeType() const
{
	const QGLITTER_D(QGlitterAppcastItem);
	return d->mimeType;
}

void QGlitterAppcastItem::setMimeType(QString mimeType)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->mimeType = mimeType;
}

QString QGlitterAppcastItem::minimumSystemVersion() const
{
	const QGLITTER_D(QGlitterAppcastItem);
	return d->minimumSystemVersion;
}

void QGlitterAppcastItem::setMinimumSystemVersion(QString minimumSystemVersion)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->minimumSystemVersion = minimumSystemVersion;
}

QString QGlitterAppcastItem::operatingSystem() const
{
	const QGLITTER_D(QGlitterAppcastItem);
	return d->operatingSystem;
}

void QGlitterAppcastItem::setOperatingSystem(QString operatingSystem)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->operatingSystem = operatingSystem;
}

QDateTime QGlitterAppcastItem::publicationDate() const
{
	const QGLITTER_D(QGlitterAppcastItem);
	return d->publicationDate;
}

void QGlitterAppcastItem::setPublicationDate(QDateTime publicationDate)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->publicationDate = publicationDate;
}

QMap<QString, QString> QGlitterAppcastItem::releaseNotesUrls() const
{
	const QGLITTER_D(QGlitterAppcastItem);
	return d->releaseNotesUrls;
}

void QGlitterAppcastItem::addReleaseNotesUrl(QString language, QString releaseNotesUrl)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->releaseNotesUrls[language] = releaseNotesUrl;
}

QString QGlitterAppcastItem::shortVersionString() const
{
	const QGLITTER_D(QGlitterAppcastItem);

	if (d->shortVersionString.size() == 0) {
		return d->version;
	}

	return d->shortVersionString;
}

void QGlitterAppcastItem::setShortVersionString(QString shortVersionString)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->shortVersionString = shortVersionString;
}

QString QGlitterAppcastItem::signature() const
{
	const QGLITTER_D(QGlitterAppcastItem);
	return d->signature;
}

void QGlitterAppcastItem::setSignature(QString signature)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->signature = signature;
}

int QGlitterAppcastItem::size() const
{
	const QGLITTER_D(QGlitterAppcastItem);
	return d->size;
}

void QGlitterAppcastItem::setSize(int size)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->size = size;
}

QString QGlitterAppcastItem::title() const
{
	const QGLITTER_D(QGlitterAppcastItem);
	return d->title;
}

void QGlitterAppcastItem::setTitle(QString title)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->title = title;
}

QString QGlitterAppcastItem::url() const
{
	const QGLITTER_D(QGlitterAppcastItem);
	return d->url;
}

void QGlitterAppcastItem::setUrl(QString url)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->url = url;
}

QString QGlitterAppcastItem::version() const
{
	const QGLITTER_D(QGlitterAppcastItem);
	return d->version;
}

void QGlitterAppcastItem::setVersion(QString version)
{
	QGLITTER_D(QGlitterAppcastItem);
	d->version = version;
}
