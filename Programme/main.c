#include "rsa.h"

int main(){
	public_key pub_key;

	pub_key.n=2773;
	pub_key.e=17;

	private_key priv_key;

	priv_key.p=47;
	priv_key.q=59;
	priv_key.d=157;


	return 0;
}


    //On affiche le sha
    printSha256(hashTab);

    return 0;
}