#ifndef WEI
#define WEI
class Wei {
private:
	static unsigned int wei[32];
public:
	static int init() {
		wei[0] = 1;
		int i;
		for (i = 1; i < 32; i++)wei[i] = wei[i - 1] * 2;
		return 0;
	}
	static int BitConvInt(unsigned int k) {
		int i;
		for (i = 0; i < 32; i++)if (wei[i] == k)return i;
		printf("BitConvInt ERROR\n");
		return -1;
	}
	static int getWei(int i) {
		return wei[i];
	}
};
#endif