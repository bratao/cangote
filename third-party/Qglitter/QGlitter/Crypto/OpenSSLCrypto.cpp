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

#include "Crypto/Crypto.h"

#include <QIODevice>
#include <QString>

#include <openssl/bio.h>
#include <openssl/dsa.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

#include <cstdio>

#if defined WIN32 && !defined __MINGW32__
#include <openssl/applink.c>
#endif

static QByteArray messageDigest(QIODevice &sourceData)
{
	EVP_MD_CTX *mdctx = EVP_MD_CTX_create();
	EVP_DigestInit_ex(mdctx, EVP_sha1(), NULL);

	while (!sourceData.atEnd()) {
		QByteArray buffer = sourceData.read(4096);
		EVP_DigestUpdate(mdctx, buffer.constData(), buffer.size());
	}

	unsigned int md_len = 0;
	unsigned char md_value[EVP_MAX_MD_SIZE] = {};
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
	EVP_MD_CTX_destroy(mdctx);

	return QByteArray((const char *)md_value, md_len);
}

void QGlitter::cryptoInit()
{
	OpenSSL_add_all_ciphers();
	ERR_load_crypto_strings();
}

static QString s_qglitterErrorMessage = "";

const QString &QGlitter::errorMessage()
{
	return s_qglitterErrorMessage;
}

bool QGlitter::dsaKeygen(int size, const QString &passphrase)
{
	bool success = false;

	DSA *dsa = DSA_generate_parameters(size, NULL, 0, NULL, NULL, NULL, NULL);
	if (dsa) {
		if (DSA_generate_key(dsa)) {
			const EVP_CIPHER *enc = NULL;
			unsigned char *kstr = 0;
			int klen = 0;

			QByteArray passphraseData = passphrase.toUtf8();
			if (passphraseData.size() > 0) {
				enc = EVP_aes_256_cbc();
				kstr = (unsigned char *)passphraseData.data();
				klen = passphraseData.size();
			}

			FILE *privateKeyFile = fopen("dsa_priv.pem", "w");
			if (privateKeyFile && PEM_write_DSAPrivateKey(privateKeyFile, dsa, enc, kstr, klen, NULL, NULL)) {
				FILE *publicKeyFile = fopen("dsa_pub.pem", "w");
				if (publicKeyFile && PEM_write_DSA_PUBKEY(publicKeyFile, dsa)) {
					success = true;
				}

				if (publicKeyFile) {
					fclose(publicKeyFile);
				}
			}

			if (privateKeyFile) {
				fclose(privateKeyFile);
			}
		} else {
			s_qglitterErrorMessage = ERR_error_string(ERR_get_error(), 0);
		}

		DSA_free(dsa);
	} else {
		s_qglitterErrorMessage = ERR_error_string(ERR_get_error(), 0);
	}

	return success;
}

bool QGlitter::dsaVerify(QIODevice &sourceData, const QByteArray &signature, const QByteArray &publicKey)
{
	QByteArray rawSignature = QByteArray::fromBase64(signature);
	BIO *publicKeyData = BIO_new_mem_buf((void *)publicKey.constData(), publicKey.size());

	bool verified = false;

	DSA *dsa = PEM_read_bio_DSA_PUBKEY(publicKeyData, 0, 0, 0);
	if (dsa) {
		QByteArray digest = messageDigest(sourceData);

		int status = DSA_verify(0, (const unsigned char *)digest.constData(), digest.size(), (const unsigned char *)rawSignature.constData(), rawSignature.size(), dsa);
		if (status > 0) {
			verified = true;
		} else if (status < 0) {
			s_qglitterErrorMessage = ERR_error_string(ERR_get_error(), 0);
		}

		DSA_free(dsa);
	} else {
		s_qglitterErrorMessage = ERR_error_string(ERR_get_error(), 0);
	}

	BIO_free(publicKeyData);

	return verified;
}

QByteArray QGlitter::dsaSign(QIODevice &sourceData, const QByteArray &privateKey, const QString &passphrase)
{
	BIO *privateKeyData = BIO_new_mem_buf((void *)privateKey.constData(), privateKey.size());

	QByteArray passphraseData = passphrase.toUtf8();
	QByteArray signature;

	DSA *dsa = PEM_read_bio_DSAPrivateKey(privateKeyData, 0, 0, (void *)passphraseData.constData());
	if (dsa) {
		QByteArray digest = messageDigest(sourceData);
		QByteArray dsaSignature(DSA_size(dsa), 0);

		unsigned int signatureLength = dsaSignature.size();
		if (DSA_sign(0, (const unsigned char *)digest.constData(), digest.size(), (unsigned char *)dsaSignature.data(), &signatureLength, dsa)) {
			dsaSignature.truncate(signatureLength);
			signature = dsaSignature.toBase64();
		} else {
			s_qglitterErrorMessage = ERR_error_string(ERR_get_error(), 0);
		}

		DSA_free(dsa);
	} else {
		s_qglitterErrorMessage = ERR_error_string(ERR_get_error(), 0);
	}

	BIO_free(privateKeyData);

	return signature;
}
