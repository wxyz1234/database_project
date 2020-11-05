#ifndef PAGELOC
#define PAGELOC
class PageLoc {
public:
	int PageID, LocID;
	PageLoc() {
		PageID = 0;
		LocID = 0;
	}
	PageLoc(int i, int j) {
		PageID = i;
		LocID = j;
	}
};
#endif