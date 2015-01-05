/*
 * EncryptedInt.h
 *
 *  Created on: 30 Dec, 2014
 *      Author: sip
 */

#ifndef ENCRYPTEDINT_H_
#define ENCRYPTEDINT_H_

#include "cocos2d.h"

USING_NS_CC;

class EncryptedInt {
private:
    bool isGeneratedRandomKey;
    int randomKey;
	int mEncrypted;
	int encrypt(int);
protected:
    int getRandomKey();
public:
	EncryptedInt();
	EncryptedInt(int raw);
	~EncryptedInt();
    
    int getEncryptedValue(){return mEncrypted;}    
    int decrypt();

	operator int() {return decrypt();}
	int operator = (int val) {mEncrypted=encrypt(val); return val;}
	int operator += (int val) {mEncrypted=encrypt(decrypt()+val); return decrypt();}
	int operator -= (int val) {mEncrypted=encrypt(decrypt()-val); return decrypt();}
	int operator ++ (int val) {mEncrypted=encrypt(decrypt()+1); return decrypt();}
	int operator -- (int val) {mEncrypted=encrypt(decrypt()-1); return decrypt();}

};

#endif /* ENCRYPTEDINT_H_ */
