
#include "utils.h"

int main(){
	struct public_key pub_key;
	
	pub_key.n=2773;
	pub_key.e=17;

	struct private_key priv_key;
	
	priv_key.p=47;
	priv_key.q=59;
	priv_key.d=157;

	uint32_t message=920;
	printf("%d\n",message );
	uint32_t crypted_message=toPower(message,pub_key.e,pub_key.n);
	printf("%d\n",crypted_message );
	uint32_t decrypted_message=decipher(&priv_key,crypted_message);
	printf("%d\n",decrypted_message);
	return 0;
}