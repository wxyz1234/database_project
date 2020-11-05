#ifndef WEI
#define WEI
class Wei {	
public:
	static int wei[31];
	static void init() {
		wei[0] = 1;
		int i;
		for (i = 1; i < 31; i++)wei[i] = wei[i - 1] * 2;		
	}
	static int BitConvInt(unsigned int k) {
		int i;
		for (i = 0; i < 31; i++)if (wei[i] == k)return i;
		printf("%d BitConvInt ERROR\n",k);
		return -1;
	}
};
#endif