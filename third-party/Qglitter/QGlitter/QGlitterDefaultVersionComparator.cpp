// Original Objective-C Code Copyright (c) 2007 Andy Matuschak
// https://github.com/andymatuschak/Sparkle/blob/7b3928db9b61d4eb97b26437d9ea1c9024539d49/SUStandardVersionComparator.m
//
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

#include "QGlitterDefaultVersionComparator.h"

#include <QList>

enum VersionElementType
{
	VETSeparator,
	VETNumber,
	VETString
};

struct VersionElement
{
	VersionElement() : type(VETSeparator), string(""), number(0) {}
	VersionElement(VersionElementType t, QString s) : type(t), string(s) { if (t == VETNumber) number = s.toLongLong(); }

	VersionElementType type;
	QString string;
	qint64 number;
};

VersionElementType characterType(QChar ch)
{
	if (ch.isPunct() || ch.isSpace()) return VETSeparator;
	if (ch.isDigit()) return VETNumber;

	return VETString;
}

QList<VersionElement> splitVersionString(const QString &str)
{
	QList<VersionElement> parts;

	if (str.isEmpty()) {
		return parts;
	}

	int tokenStart = 0;
	VersionElementType tokenType = characterType(str[0]);

	int pos = 1;
	for ( ; pos < str.length(); ++pos) {
		VersionElementType curCharType = characterType(str[pos]);

		if (curCharType != tokenType || curCharType == VETSeparator) {
			parts.append(VersionElement(tokenType, str.mid(tokenStart, pos - tokenStart)));

			tokenType = curCharType;
			tokenStart = pos;
		}
	}

	parts.append(VersionElement(tokenType, str.mid(tokenStart, pos - tokenStart)));

	return parts;
}

int QGlitter::defaultVersionComparator(const QString &lhs, const QString &rhs)
{
	QList<VersionElement> lhsParts = splitVersionString(lhs);
	QList<VersionElement> rhsParts = splitVersionString(rhs);

	for (int i = 0; i < qMin(lhsParts.size(), rhsParts.size()); ++i) {
		if (lhsParts[i].type == rhsParts[i].type) {
			// Same type comparison

			if (lhsParts[i].type == VETNumber) {
				if (lhsParts[i].number < rhsParts[i].number) {
					return -1;
				}
				if (lhsParts[i].number > rhsParts[i].number) {
					return 1;
				}
			} else if (lhsParts[i].type == VETString) {
				int comparison = lhsParts[i].string.compare(rhsParts[i].string);
				if (comparison != 0) {
					return comparison;
				}
			}
		} else {
			// number > string

			if (lhsParts[i].type != VETString && rhsParts[i].type == VETString) {
				return 1;
			} else if (lhsParts[i].type == VETString && rhsParts[i].type != VETString) {
				return -1;
			} else {
				// number > separator

				if (lhsParts[i].type == VETNumber) {
					return -1;
				} else {
					return 1;
				}
			}
		}
	}

	if (lhsParts.size() != rhsParts.size()) {
		VersionElement missingPart;
		int shorterResult = 0;
		int longerResult = 0;

		if (lhsParts.size() > rhsParts.size()) {
			missingPart = lhsParts[rhsParts.size()];
			shorterResult = -1;
			longerResult = 1;
		} else {
			missingPart = rhsParts[lhsParts.size()];
			shorterResult = 1;
			longerResult = -1;
		}

		if (missingPart.type == VETString) {
			// Shorter version wins if the missing element is a string

			return shorterResult;
		} else {
			// Longer version wins if the missing element is a number or separator

			return longerResult;
		}
	}

	return 0;
}
