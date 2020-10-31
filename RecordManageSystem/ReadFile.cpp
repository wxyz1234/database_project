#include "RecordManager.h"
#include "Myhash.h"
#include <stdio.h>
#include <map>
#include <hash_set>
using namespace std;
RecordManager* rm;
DSchema* sh;
map<int, PageLoc> RP;
int main() {
	rm = new RecordManager();
	sh = new DSchema();	
	int fileID;
	rm->OpenFile("data/input.txt", fileID);
	rm->GetSchema(fileID, *sh);	
	int pk;	
	TypeName tn;
	Myhash ha;
	for (int i = 0; i < sh->getnum(); i++) 
		if (sh->getPart(i)->key->getKey()== KeyName::Primary){
			pk = i;			
			tn = sh->getPart(i)->getType();	
			if (tn == TypeName::Char) {
				int l = ((DtypeSchemaChar*)sh->getPart(i))->getlen();
				ha.setlen(l);
			}				
			ha.setType(tn);
			break;
		}
	BufType buf;
	rm->fm->readPage(fileID,0,buf,0);
	int num = buf[0];
	int i,j,k,p;
	PageLoc pl= PageLoc(0,0);
	DList list=DList(sh);
	for (i = 1; i <= num; i++) {
		rm->fm->readPage(fileID, i, buf, 0);
		k = buf[0];
		p =~buf[1];
		while (k > 0) {
			j =p & (-p);
			p -= j;
			j = Wei::BitConvInt(j);
			pl = PageLoc(i, j);			
			rm->FindRecord(fileID, pl, list);			
			RP[list.getRID()] = pl;
			ha.Insert(list.getPart(pk)->getData());
			k--;
		}
	}
	return 0;
}