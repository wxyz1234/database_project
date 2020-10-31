#ifndef PAGELOC
#define PAGELOC
class PageLoc {
public:
	int PageID, LocID;
	PageLoc(int i, int j) {
		PageID = i;
		LocID = j;
	}
};
#endif