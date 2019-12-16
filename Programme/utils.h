void encryptionMessage(struct public_Key, const char *fileIn,const char *fileOut);
void encryptionBloc(struct public_Key, uint8_t *partMessage, fileOut);
int moduloPuissance(long val, int puissance, int modulo);
uint32_t decipher(struct private_key* pk, uint32_t crypted_message);