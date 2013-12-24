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

#include "QGlitterAppcast.h"
#include "QGlitterAppcast_p.h"

static const char * const kSparkleNamespace = "http://www.andymatuschak.org/xml-namespaces/sparkle";

QGlitterAppcast::QGlitterAppcast()
	: QGlitterObject(new QGlitterAppcastPrivate)
{
}

QList<QGlitterAppcastItem> QGlitterAppcast::items() const
{
	const QGLITTER_D(QGlitterAppcast);
	return d->items;
}

bool QGlitterAppcast::read(QIODevice *data)
{
	QGLITTER_D(QGlitterAppcast);

	d->xmlReader.setDevice(data);

	if (d->xmlReader.readNextStartElement()) {
		if (d->xmlReader.name() == "rss" && d->xmlReader.attributes().value("version") == "2.0") {
			readAppcast();
		} else {
			d->xmlReader.raiseError(QObject::tr("The file is not an RSS version 2.0 file."));
		}
	}

	return !d->xmlReader.error();
}

void QGlitterAppcast::readAppcast()
{
	QGLITTER_D(QGlitterAppcast);

	bool foundChannel = false;
	while (d->xmlReader.readNextStartElement()) {
		if (d->xmlReader.name() == "channel" && foundChannel == false) {
			readChannel();
			foundChannel = true;
		} else {
			d->xmlReader.raiseError(QObject::tr("Unrecognized RSS tag or multiple channels"));
			return;
		}
	}
}

void QGlitterAppcast::readChannel()
{
	QGLITTER_D(QGlitterAppcast);

	while (d->xmlReader.readNextStartElement()) {
		if (d->xmlReader.name() == "title") {
			d->title = d->xmlReader.readElementText();
		} else if (d->xmlReader.name() == "link") {
			d->link = d->xmlReader.readElementText();
		} else if (d->xmlReader.name() == "description") {
			d->description = d->xmlReader.readElementText();
		} else if (d->xmlReader.name() == "language") {
			d->language = d->xmlReader.readElementText();
		} else if (d->xmlReader.name() == "item") {
			readItem();
		} else {
			d->xmlReader.raiseError(QObject::tr("Unrecognized RSS channel tag"));
			return;
		}
	}
}

void QGlitterAppcast::readItem()
{
	QGLITTER_D(QGlitterAppcast);

	QGlitterAppcastItem currentItem;
	QString minimumSystemVersion;

	while (d->xmlReader.readNextStartElement()) {
		if (d->xmlReader.name() == "title") {
			currentItem.setTitle(d->xmlReader.readElementText());
		} else if (d->xmlReader.name() == "pubDate") {
			currentItem.setPublicationDate(QDateTime::fromString(d->xmlReader.readElementText()));
		} else if (d->xmlReader.name() == "releaseNotesLink" && d->xmlReader.namespaceUri() == kSparkleNamespace) {
			QString language = d->xmlReader.attributes().value("xml:lang").toString();
			if (language.size() == 0) {
				if (d->language.size() == 0) {
					language = "en";
				} else {
					language = d->language;
				}
			}

			currentItem.addReleaseNotesUrl(language, d->xmlReader.readElementText());
		} else if (d->xmlReader.name() == "description") {
			QString language = d->xmlReader.attributes().value("xml:lang").toString();
			if (language.size() == 0) {
				if (d->language.size() == 0) {
					language = "en";
				} else {
					language = d->language;
				}
			}

			currentItem.addDescription(language, d->xmlReader.readElementText());
		} else if (d->xmlReader.name() == "minimumSystemVersion" && d->xmlReader.namespaceUri() == kSparkleNamespace) {
			minimumSystemVersion = d->xmlReader.readElementText();
		} else if (d->xmlReader.name() == "enclosure") {
			QXmlStreamAttributes attributes = d->xmlReader.attributes();

			if (attributes.hasAttribute("url") && attributes.hasAttribute("length") && attributes.hasAttribute("type")) {
				currentItem.setMimeType(attributes.value("type").toString());
				currentItem.setMinimumSystemVersion(minimumSystemVersion);
				currentItem.setSize(attributes.value("length").toString().toInt());
				currentItem.setUrl(attributes.value("url").toString());

				currentItem.setDeltaFrom(attributes.value(kSparkleNamespace, "deltaFrom").toString());
				currentItem.setOperatingSystem(attributes.value(kSparkleNamespace, "os").toString());
				currentItem.setShortVersionString(attributes.value(kSparkleNamespace, "shortVersionString").toString());
				currentItem.setSignature(attributes.value(kSparkleNamespace, "dsaSignature").toString());
				currentItem.setVersion(attributes.value(kSparkleNamespace, "version").toString());
			} else {
				d->xmlReader.raiseError(QObject::tr("Invalid RSS enclosure"));
				return;
			}
		} else {
			d->xmlReader.raiseError(QObject::tr("Unrecognized RSS item tag"));
			return;
		}
	}

	d->xmlReader.skipCurrentElement();

	d->items.append(currentItem);
}
