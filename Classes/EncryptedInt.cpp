/*
 * EncryptedInt.cpp
 *
 *  Created on: 2 Jan, 2015
 *      Author: sip
 */

#include "EncryptedInt.h"
#include "GameUtil.h"

int EncryptedInt::getRandomKey() {
    if (!isGeneratedRandomKey) {
        randomKey = GameUtil::getRandNumber(1000000, 9999999);
        isGeneratedRandomKey = true;
    }
    return randomKey;
}

EncryptedInt::EncryptedInt() {
	isGeneratedRandomKey= false;
	mEncrypted = 0 ^ getRandomKey();
}

EncryptedInt::EncryptedInt(int raw) {
	isGeneratedRandomKey= false;
	mEncrypted = raw ^ getRandomKey();
}

EncryptedInt::~EncryptedInt() {}

int EncryptedInt::decrypt() {
	return mEncrypted ^ getRandomKey();
}

int EncryptedInt::encrypt(int raw) {
    mEncrypted=raw ^ getRandomKey();
    return mEncrypted;
}

