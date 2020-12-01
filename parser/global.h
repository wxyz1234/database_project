#ifndef GLOBAL
#define GLOBAL
#include <string>
#include "../RecordManageSystem/RecordManager.h"
#include "../RecordManageSystem/utils/Wei.h"
std::string CurrentDatabase = "";
RecordManager* rm = new RecordManager();
const unsigned int maxunsignint = 4294967295;
int Wei::wei[32];
int Wei::shiwei[9];
#endif