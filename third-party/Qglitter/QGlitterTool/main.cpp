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

#include "QGlitter/Crypto/Crypto.h"

#include <QFile>

#include <iostream>

void printUsage()
{
	std::cerr << "Usage:" << std::endl;
	std::cerr << "    qglitter-tool generate <keysize> [passphrase]" << std::endl;
	std::cerr << "    qglitter-tool sign <keyfile> <file> [passphrase]" << std::endl;
	std::cerr << "    qglitter-tool verify <keyfile> <file> <signature>" << std::endl << std::endl;
}

int main(int argc, char *argv[])
{
	QGlitter::cryptoInit();

	if ((argc == 3 || argc == 4) && QString(argv[1]) == "generate") {
		bool ok = false;
		int keySize = QString(argv[2]).toInt(&ok);
		if (!ok) {
			printUsage();
			return -1;
		}

		if (keySize < 2048) {
			std::cerr << "Minimum keysize is 2048" << std::endl;
			return -1;
		}

		QString passphrase = "";
		if (argc == 4) {
			passphrase = argv[3];
		} else {
			std::cerr << "WARNING: Generating a key without a passphrase" << std::endl;
		}

		if (!QGlitter::dsaKeygen(keySize, passphrase)) {
			std::cerr << "Unable to generate keypair" << std::endl;
			if (QGlitter::errorMessage().size()) {
				std::cerr << "ERROR: " << QGlitter::errorMessage().toStdString() << std::endl;
			}
			return -3;
		}

		return 0;
	}

	if (argc == 4 || argc == 5) {
		QString action = argv[1];
		if (action != "sign" && action != "verify") {
			printUsage();
			return -1;
		}

		QFile key(argv[2]);
		if (!key.open(QIODevice::ReadOnly | QIODevice::Text)) {
			std::cerr << "Unable to read keyfile: " << argv[2] << std::endl;
			return -1;
		}

		QByteArray keyData = key.readAll();

		key.close();

		QFile data(argv[3]);
		if (!data.open(QIODevice::ReadOnly)) {
			std::cerr << "Unable to read data file " << argv[3] << std::endl;
			return -1;
		}

		if (action == "sign") {
			QString passphrase = "";
			if (argc == 5) {
				passphrase = argv[4];
			}

			std::cout << QGlitter::dsaSign(data, keyData, passphrase).toBase64().data() << std::endl;
			if (QGlitter::errorMessage().size()) {
				std::cerr << "ERROR: " << QGlitter::errorMessage().toStdString() << std::endl;
			}
		} else {
			if (argc != 5) {
				printUsage();
				return -1;
			}

			QByteArray signature = QByteArray::fromBase64(argv[4]);

			if (QGlitter::dsaVerify(data, signature, keyData)) {
				return 0;
			} else {
				std::cerr << "Signature does not match" << std::endl;
				if (QGlitter::errorMessage().size()) {
					std::cerr << "ERROR: " << QGlitter::errorMessage().toStdString() << std::endl;
				}
				return -2;
			}
		}

		return 0;
	}

	printUsage();
	return -1;
}
