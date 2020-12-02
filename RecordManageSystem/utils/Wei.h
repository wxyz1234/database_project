#ifndef WEI
#define WEI
class Wei {	
public:
	static int wei[32];
	static int shiwei[10];
	static void init() {
		shiwei[0] = 1;
		wei[0] = 1;
		int i;
		for (i = 1; i < 32; i++)wei[i] = wei[i - 1] * 2;		
		for (i = 1; i < 10; i++)shiwei[i] = shiwei[i - 1] * 10;
	}
	static int BitConvInt(unsigned int k) {
		int i;
		for (i = 0; i < 32; i++)if (wei[i] == k)return i;
		printf("%d BitConvInt ERROR\n",k);
		return -1;
	}
};
#endif