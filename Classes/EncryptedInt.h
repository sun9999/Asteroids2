/*
 * EncryptedInt.h
 *
 *  Created on: 30 Dec, 2014
 *      Author: sip
 */

#ifndef ENCRYPTEDINT_H_
#define ENCRYPTEDINT_H_

class EncryptedInt {
private:
	int mEncrypted;
	int decrypt();
public:
	EncryptedInt(int raw);
	~EncryptedInt();

	operator int() {return decrypt();}
	int operator = (int val) {EncryptedInt(val); return val;}
	int operator += (int val) {EncryptedInt(val + decrypt()); return decrypt();}

};

#endif /* ENCRYPTEDINT_H_ */
