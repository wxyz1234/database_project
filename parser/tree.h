#ifndef TREE
#define TREE
#include <string>
#include <vector>
#include <windows.h>
#include "../RecordManageSystem/DType/TypeName.h"
#include "../RecordManageSystem/DType/DSchema.h"
#include "../RecordManageSystem/DType/DTypeSchema.h"
#include "../RecordManageSystem/RecordManager.h"
#include "../RecordManageSystem/utils/Myhash.h"

class attributeTree;
class attributelistTree;
class valuelistsTree;
class valuelistTree;
class valueTree;
class WhereClausesTree;
class setClauselistTree;
class columnlistTree;
class columnTree;
class exprTree;
class tablelistTree;
class conditionsTree;
class comparisonTree;
class typeTree;

extern std::string CurrentDatabase;
extern RecordManager* rm;
extern PrimaryData pd;
extern ForeignData fd;
extern int sumRID;

class Tree {
public:
    virtual void visit() {};
    virtual ~Tree() {}
    static void setInstance(Tree* t) {    
        if (tree != nullptr) {
            delete tree;
        }
        tree = t;
    }
    static void run() {    
        if (tree != nullptr)
            tree->visit();
    }
    static Tree* tree;    
};
Tree* Tree::tree = nullptr;

class valueTree :public Tree {
    friend class attributeTree;
    friend class valuelistsTree;
    friend class exprTree;
protected:
    std::string data;
    CharTypeName k;
public:
    valueTree(CharTypeName i, const char* a) {
        k = i;
        data = a;
    }
    valueTree(CharTypeName i) {
        k = i;        
    }
};
class valuelistTree :public Tree {
    friend class valuelistsTree;
protected:
    std::vector<valueTree*> a;
public:
    valuelistTree() {
        a.clear();
    }
    void append(valueTree* i) {
        a.push_back(i);
    }
    ~valuelistTree() {
        for (auto i : a) {
            delete i;
        }
    }
};
class valuelistsTree :public Tree {
private:
    std::vector<valuelistTree*> a;
public:
    valuelistsTree() {
        a.clear();
    }
    void append(valuelistTree* i) {
        a.push_back(i);
    }
    void visit(DSchema* sh, int fileID,const char* name) {
        int i,j;
        bool flag;
        DList* b = new DList(sh);
        for (i = 0; i < a.size(); i++) {
            //valuelistTree转DList
            if (a[i]->a.size() != sh->getnum()) {
                printf("Convert %d DList Failed!\n",i);
                continue;
            }
            flag = false;
            b->isNull = 0;
            for (j = 0; j < sh->getnum();j++) {
                //NULL约束和default约束
                if (a[i]->a[j]->k == CharTypeName::NULLC) {
                    if (!sh->getPart(j)->getAllowNull()) {
                        printf("Convert %d DList Failed!Part %d is NULL but don't allowed.\n", i, j);
                        flag = true;
                        break;
                    }
                    if (sh->getPart(j)->getHaveDefault()) {
                        switch (sh->getPart(j)->getType()) {
                        case TypeName::Int:
                            b->a[j]->setData((int*)sh->getPart(j)->getDef()->getData());
                            break;
                        case TypeName::SmallInt:
                            b->a[j]->setData((short*)sh->getPart(j)->getDef()->getData());
                            break;
                        case TypeName::Char:
                            b->a[j]->setData((char*)sh->getPart(j)->getDef()->getData());
                            break;
                        case TypeName::Double:
                            b->a[j]->setData((double*)sh->getPart(j)->getDef()->getData());
                            break;
                        case TypeName::Float:
                            b->a[j]->setData((float*)sh->getPart(j)->getDef()->getData());
                            break;
                        case TypeName::Date:
                            b->a[j]->setData((DateType*)sh->getPart(j)->getDef()->getData());
                            break;
                        case TypeName::Numeric:
                            b->a[j]->setData((NumericType*)sh->getPart(j)->getDef()->getData());
                            break;
                        }                        
                    }
                    else {
                        switch (sh->getPart(j)->getType()) {
                        case TypeName::Int:
                            b->a[j]->setData((int*)NULL);
                            break;
                        case TypeName::SmallInt:
                            b->a[j]->setData((short*)NULL);
                            break;
                        case TypeName::Char:
                            b->a[j]->setData((char*)NULL);
                            break;
                        case TypeName::Double:
                            b->a[j]->setData((double*)NULL);
                            break;
                        case TypeName::Float:
                            b->a[j]->setData((float*)NULL);
                            break;
                        case TypeName::Date:
                            b->a[j]->setData((DateType*)NULL);
                            break;
                        case TypeName::Numeric:
                            b->a[j]->setData((NumericType*)NULL);
                            break;
                        }                        
                    }
                    continue;
                }
                //具体赋值
                int tmpint;
                short tmpshort;
                int tmplen;
                char* tmpchar;
                double tmpdouble;
                float tmpfloat;
                DateType tmpdate;
                NumericType tmpnumeric;
                
                switch (sh->getPart(j)->getType()) {
                case TypeName::Int:
                    if (a[i]->a[j]->k != CharTypeName::INUM) {
                        printf("Convert %d DList Failed!Part %d is Int.\n", i, j);
                        flag = true;
                        break;
                    }
                    tmpint = atoi(a[i]->a[j]->data.c_str());
                    b->a[j]->setData(&tmpint);
                    break;
                case TypeName::SmallInt:
                    if (a[i]->a[j]->k != CharTypeName::INUM) {
                        printf("Convert %d DList Failed!Part %d is SmallInt.\n", i, j);
                        flag = true;
                        break;
                    }
                    tmpshort = atoi(a[i]->a[j]->data.c_str());
                    b->a[j]->setData(&tmpshort);
                    break;
                case TypeName::Char:                    
                    if (a[i]->a[j]->k != CharTypeName::TEXT) {
                        printf("Convert %d DList Failed!Part %d is Char.\n", i, j);
                        flag = true;
                        break;
                    }
                    tmplen = ((DtypeSchemaChar*)sh->getPart(j))->getlen();
                    tmpchar = new char[tmplen];                    
                    //a[i]->a[j]->data.c_str() 没有tmplen长                    
                    memcpy(tmpchar, a[i]->a[j]->data.c_str(), a[i]->a[j]->data.length()+1);
                    
                    b->a[j]->setData(tmpchar);
                    delete []tmpchar;
                    break;
                case TypeName::Double:
                    if (a[i]->a[j]->k != CharTypeName::FNUM && a[i]->a[j]->k != CharTypeName::INUM) {
                        printf("Convert %d DList Failed!Part %d is Double.\n", i, j);
                        flag = true;
                        break;
                    }
                    tmpdouble = atof(a[i]->a[j]->data.c_str());
                    b->a[j]->setData(&tmpdouble);
                    break;
                case TypeName::Float:
                    if (a[i]->a[j]->k != CharTypeName::FNUM && a[i]->a[j]->k != CharTypeName::INUM) {
                        printf("Convert %d DList Failed!Part %d is Float.\n", i, j);
                        flag = true;
                        break;
                    }
                    tmpfloat = atof(a[i]->a[j]->data.c_str());
                    b->a[j]->setData(&tmpfloat);
                    break;
                case TypeName::Date:
                    if (a[i]->a[j]->k != CharTypeName::DATENUM) {
                        printf("Convert %d DList Failed!Part %d is Date.\n", i, j);
                        flag = true;
                        break;
                    }
                    tmpdate= DateType(a[i]->a[j]->data.c_str());
                    if (!tmpdate.islegal()) {
                        printf("Convert %d DList Failed!Part %d is Date but illegal.\n", i, j);
                        flag = true;
                        break;
                    }
                    b->a[j]->setData(&tmpdate);
                    break;
                case TypeName::Numeric:
                    if (a[i]->a[j]->k != CharTypeName::FNUM) {
                        printf("Convert %d DList Failed!Part %d is Numeric.\n", i, j);
                        flag = true;
                        break;
                    }
                    tmpnumeric = NumericType();
                    tmpnumeric.setd(a[i]->a[j]->data.c_str(),((DtypeSchemaNumeric*)sh->getPart(j))->getsumd(), ((DtypeSchemaNumeric*)sh->getPart(j))->getdotd());
                    b->a[j]->setData(&tmpnumeric);                    
                    break;
                }
                if (flag)break;                
            }                        
            if (flag)continue;                        
            //主键外键约束
            int k = -1;
            int l, pdnum, p;
            int anum[3]; 
            int anum2[3];
            for (k = 0; k < pd.num; k++)                    
                if (pd.filename[k] == std::string(sh->getName()))                            
                    break;
            if (k!=-1){
                for (l = 0; l < pd.unnum[k]; l++)
                    for (j = 0; j < sh->getnum(); j++)
                        if (pd.attrname[k][l] == std::string(sh->getTypeName(j))) {
                            anum[l] = j;
                            break;
                        }                
                if (pd.unnum[k] == 1)
                    if (pd.a[k]->Find(1,b->getPart(anum[0]))) {
                        printf("Primary Key Repeated!\n");
                        flag = true;
                        continue;
                    }
                if (pd.unnum[k] == 2)
                    if (pd.a[k]->Find(2, b->getPart(anum[0]),b->getPart(anum[1]))) {
                        printf("Primary Key Repeated!\n");
                        flag = true;
                        continue;
                    }
                if (pd.unnum[k] == 3)
                    if (pd.a[k]->Find(3, b->getPart(anum[0]), b->getPart(anum[1]), b->getPart(anum[2]))) {
                        printf("Primary Key Repeated!\n");
                        flag = true;
                        continue;
                    }
                pdnum = k;
            }            
            for (k = 0; k < fd.num; k++)
                if (fd.filename[k] == std::string(sh->getName())){                    
                    for (p = 0; p < pd.num; p++)
                        if (fd.reffilename[k] == pd.filename[p])
                            break;
                    for (l = 0; l < fd.unnum[k]; l++)
                        for (j = 0; j < sh->getnum(); j++)
                            if (fd.attrname[k][l] == std::string(sh->getTypeName(j))) {
                                anum2[l] = j;
                                break;
                            }
                    if (fd.unnum[k] == 1)
                        if (!pd.a[p]->Find(1,b->a[anum2[0]])) {
                            printf("Foreign Key Not Found!\n");
                            flag = true;
                            break;
                        }
                    if (fd.unnum[k] == 2)
                        if (!pd.a[p]->Find(2, b->a[anum2[0]], b->a[anum2[1]])) {
                            printf("Foreign Key Not Found!\n");
                            flag = true;
                            break;
                        }
                    if (fd.unnum[k] == 3)
                        if (!pd.a[p]->Find(1, b->a[anum2[0]], b->a[anum2[1]], b->a[anum2[2]])) {
                            printf("Foreign Key Not Found!\n");
                            flag = true;
                            break;
                        }
                }
            if (flag)continue;
            b->makeNull();
            sumRID++;
            b->setRID(sumRID);

            //主键添加
            rm->InsertRecord(fileID, b);
            if (pd.unnum[pdnum] == 1)
                pd.a[pdnum]->Insert(b->getPart(anum[0]));
            if (pd.unnum[pdnum] == 2)
                pd.a[pdnum]->Insert(b->getPart(anum[0]), b->getPart(anum[1]));
            if (pd.unnum[pdnum] == 3)
                pd.a[pdnum]->Insert( b->getPart(anum[0]), b->getPart(anum[1]), b->getPart(anum[2]));
        }
        delete b;
    }
    ~valuelistsTree() {
        for (auto i : a) {
            delete i;
        }
    }
};
class typeTree :public Tree {
    friend class DSchema;
    friend class attributeTree;
    friend class exprTree;
    friend class WhereClausesTree;
protected:
    TypeName name;
    int p1, p2;
public:    
    typeTree(TypeName i) {
        name = i;
        p1 = 0;
        p2 = 0;
    }
    typeTree(TypeName i, int i1) {
        name = i;
        p1 = i1;
        p2 = 0;
    }
    typeTree(TypeName i, int i1, int i2) {
        name = i;
        p1 = i1;
        p2 = i2;
    }
    typeTree(TypeName i, char* i1) {
        name = i;
        p1 = atoi(i1);
        p2 = 0;
    }
    typeTree(TypeName i, char* i1, char* i2) {
        name = i;
        p1 = atoi(i1);
        p2 = atoi(i2);
    }
};
class attributeTree :public Tree {
    friend class attributelistTree;
    friend class AddAttributeTree;
    friend class DSchema;
protected:
    std::string name, na1, na2;
    valueTree* def;
    bool allownull, hasdefault = false;
    typeTree* type;
    bool isPrimary,isForeign;
public:
    attributeTree(bool pr, bool fo, char* na, typeTree* ty, bool an, bool hd, valueTree* de = NULL) {
        isPrimary = pr;
        isForeign = fo;
        name = na;
        type = ty;
        allownull = an;
        hasdefault = hd;
        if (hasdefault)def = de;
    }
    attributeTree(bool pr, bool fo, char* na, char* n1 = NULL, char* n2 = NULL) {
        isPrimary = pr;
        isForeign = fo;
        name = na;
        if (n1 != NULL)na1 = n1;
        else na1 = "";
        if (n2 != NULL)na2 = n2;
        else na2 = "";
    }
    ~attributeTree() {
        if (!isPrimary && !isForeign) {
            delete type;
            if (hasdefault)delete def;
        }
    }
    void addpart(DSchema* data) {
        data->typeName[data->num] = new char[20];
        memcpy(data->typeName[data->num],name.c_str(),20);
        switch (type->name) {
        case TypeName::Int:
            data->a[data->num] = new DtypeSchemaInt();
            ((DtypeSchemaInt*)data->a[data->num])->setlen(type->p1);
            break;
        case TypeName::SmallInt:
            data->a[data->num] = new DtypeSchemaSmallInt();
            break;
        case TypeName::Char:
            data->a[data->num] = new DtypeSchemaChar();
            ((DtypeSchemaChar*)data->a[data->num])->setlen(type->p1);
            break;
        case TypeName::Double:
            data->a[data->num] = new DtypeSchemaDouble();
            break;
        case TypeName::Float:
            data->a[data->num] = new DtypeSchemaFloat();
            break;
        case TypeName::Date:
            data->a[data->num] = new DtypeSchemaDate();
            break;
        case TypeName::Numeric:
            data->a[data->num] = new DtypeSchemaNumeric();
            ((DtypeSchemaNumeric*)data->a[data->num])->setsumdotd(type->p1, type->p2);
            break;
        default:
            printf("TypeName ERROR %d\n", type->name);
        }
        data->a[data->num]->AllowNull = allownull;
        data->a[data->num]->HaveDefault = hasdefault;
        if (hasdefault){
            data->a[data->num]->setDefault(def->data.c_str());                    
        }
        data->a[data->num]->setisPrimary(false);
        data->a[data->num]->setisForeign(false);
        data->num++;
    }
    void addpart(DList* b) {
        switch (type->name) {
        case TypeName::Int:
            b->a[b->num] = new DtypeDataInt();
            ((DtypeSchemaInt*)b->a[b->num])->setlen(type->p1);            
            break;
        case TypeName::SmallInt:
            b->a[b->num] = new DtypeDataSmallInt();
            break;
        case TypeName::Char:
            b->a[b->num] = new DtypeDataChar(type->p1);            
            break;
        case TypeName::Double:
            b->a[b->num] = new DtypeDataDouble();
            break;
        case TypeName::Float:
            b->a[b->num] = new DtypeDataFloat();
            break;
        case TypeName::Date:
            b->a[b->num] = new DtypeDataDate();
            break;
        case TypeName::Numeric:
            b->a[b->num] = new DtypeDataNumeric(type->p1, type->p2);
            break;
        default:
            printf("TypeName ERROR %d\n", type->name);
        }        
        if (hasdefault) {
            int j = b->num;
            switch (type->name) {
            case TypeName::Int:
                b->a[j]->setData((int*)b->fa->getPart(j)->getDef()->getData());
                break;
            case TypeName::SmallInt:
                b->a[j]->setData((short*)b->fa->getPart(j)->getDef()->getData());
                break;
            case TypeName::Char:
                b->a[j]->setData((char*)b->fa->getPart(j)->getDef()->getData());
                break;
            case TypeName::Double:
                b->a[j]->setData((double*)b->fa->getPart(j)->getDef()->getData());
                break;
            case TypeName::Float:
                b->a[j]->setData((float*)b->fa->getPart(j)->getDef()->getData());
                break;
            case TypeName::Date:
                b->a[j]->setData((DateType*)b->fa->getPart(j)->getDef()->getData());
                break;
            case TypeName::Numeric:
                b->a[j]->setData((NumericType*)b->fa->getPart(j)->getDef()->getData());
                break;
            }            
        }
        else {
            int j = b->num;
            switch (type->name) {
            case TypeName::Int:
                b->a[j]->setData((int*)NULL);
                break;
            case TypeName::SmallInt:
                b->a[j]->setData((short*)NULL);
                break;
            case TypeName::Char:
                b->a[j]->setData((char*)NULL);
                break;
            case TypeName::Double:
                b->a[j]->setData((double*)NULL);
                break;
            case TypeName::Float:
                b->a[j]->setData((float*)NULL);
                break;
            case TypeName::Date:
                b->a[j]->setData((DateType*)NULL);
                break;
            case TypeName::Numeric:
                b->a[j]->setData((NumericType*)NULL);
                break;
            }
        }            
        b->num++;
    }
};
class attributelistTree :public Tree {
    friend class CreateTableTree;
protected:
    DSchema* data = NULL;
    std::vector<attributeTree*> a;
public:
    attributelistTree() {
        a.clear();
    }
    void append(attributeTree* i) {
        a.push_back(i);
    }
    void visit(const char* name) {
        //attributelist转DSchema
        data = new DSchema();
        int i, j;
        bool flag;
        data->setName(name);
        for (i = 0; i < a.size(); i++) {
            if (!a[i]->isPrimary && !a[i]->isForeign) {
                a[i]->addpart(data);
            }
            else {
                flag = true;
                for (j=0;j<data->num;j++)
                    if (data->typeName[j] == a[i]->name) {
                        data->a[j]->setisPrimary(a[i]->isPrimary);
                        data->a[j]->setisForeign(a[i]->isForeign);                        
                        if (a[i]->isForeign) {                                                        
                            data->a[j]->initfilename();
                            data->a[j]->setFile(a[i]->na1.c_str());
                            data->a[j]->setName(a[i]->na2.c_str());
                        }                            
                        flag = false;
                        break;
                    }
                if (flag)printf("attribute ERROR\n");
            }
        }
    }
    ~attributelistTree() {
        if (data != NULL) {
            delete data;
            data = NULL;
        }
        for (auto i : a) {
            delete i;
        }
    }
};

class columnTree :public Tree {
    friend class setClauselistTree;
    friend class WhereClausesTree;
    friend class columnlistTree;
    friend class exprTree;
    friend class AddPrimaryTree;    
    friend class AddForeignTree;
protected:
    std::string tname, aname;
public:
    columnTree(char* c1, char* c2) {
        tname = c1;
        aname = c2;
    }
    columnTree(char* c1) {
        tname = "";
        aname = c1;
    }
};
class columnlistTree :public Tree {
    friend class SelectTree;
    friend class AddPrimaryTree;
    friend class AddForeignTree;
protected:
    std::vector<columnTree*> a;
public:
    columnlistTree() {
        a.clear();
    }
    void append(columnTree* i) {
        a.push_back(i);
    }
    void show(std::vector<DList*> &dl) {
        int i, j, k;
        columnTree* col;
        TypeName tn;
        for (k = 0; k < a.size(); k++) {
            col = a[k];
            if ((col->tname == "") && (dl.size() == 1))
                col->tname = dl[0]->getfa()->getName();
            for (j = 0; j < dl.size(); j++)
                if (strcmp(col->tname.c_str(), dl[j]->getfa()->getName()) == 0) {                
                    for (i = 0; i < dl[j]->getfa()->getnum(); i++) {
                        if (strcmp(col->aname.c_str(), dl[j]->getfa()->getTypeName(i)) == 0) {
                            tn = dl[j]->getfa()->getPart(i)->getType();
                            if (dl[j]->getPart(i)->getData() == NULL) {
                                printf("Table: %s ,Attr: %s ,Data is NULL\n", col->tname.c_str(), col->aname.c_str());
                                break;
                            }
                            printf("Table: %s ,Attr: %s ,Data is ",col->tname.c_str(),col->aname.c_str());
                            DateType* tmp;
                            NumericType* tmp2;
                            int sumd, dotd, len;
                            switch (tn) {
                            case TypeName::Int:
                                len = ((DtypeSchemaInt*)dl[j]->getfa()->getPart(i))->getlen();
                                sumd = *((int*)dl[j]->getPart(i)->getData());
                                if (sumd < 0) {
                                    printf("-");
                                    sumd = -sumd;
                                }
                                for (int j = len - 1; j >= 0; j--)printf("%d", sumd / Wei::shiwei[j] % 10);
                                printf("\n");
                                break;
                            case TypeName::SmallInt:
                                printf("%d\n", *((short*)dl[j]->getPart(i)->getData()));
                                break;
                            case TypeName::Char:
                                printf("%s\n", ((char*)dl[j]->getPart(i)->getData()));
                                break;
                            case TypeName::Double:
                                printf("%f\n", *((double*)dl[j]->getPart(i)->getData()));
                                break;
                            case TypeName::Float:
                                printf("%f\n", *((float*)dl[j]->getPart(i)->getData()));
                                break;
                            case TypeName::Date:
                                tmp = ((DateType*)dl[j]->getPart(i)->getData());
                                printf("Date:%d\\%d\\%d\n", tmp->getyear(), tmp->getmonth(), tmp->getday());
                                break;
                            case TypeName::Numeric:
                                tmp2 = ((NumericType*)dl[j]->getPart(i)->getData());
                                sumd = ((DtypeSchemaNumeric*)dl[j]->getfa()->getPart(i))->getsumd();
                                dotd = ((DtypeSchemaNumeric*)dl[j]->getfa()->getPart(i))->getdotd();
                                printf("Numeric:%s\n", tmp2->getd(sumd, dotd));
                                break;
                            default:
                                printf("Type ERROR\n");
                            }
                            break;
                        }                        
                    }    
                    break;
                }
        }
    }
    ~columnlistTree() {
        for (auto i : a) {
            delete i;
        }
    }
};
class exprTree :public Tree {
private:
    exprType k;
    valueTree* value;
    columnTree* col;
    exprTree* expr1, * expr2;
    clacopName op;
public:
    exprTree(valueTree* x1) {
        k = exprType::VALUE;
        value = x1;
    }
    exprTree(columnTree* x1) {
        k = exprType::COLUMN;
        col = x1;
    }
    exprTree(exprTree* x1, clacopName y, exprTree* x2) {
        k = exprType::EXPR2;
        op = y;
        expr1 = x1;
        expr2 = x2;
    }
    bool checkdata(std::vector<DSchema*> &ds, typeTree* ty) {
        int i,j;
        DateType tmpdate;
        switch (k) {
        case exprType::VALUE:
            switch (value->k) {
            case CharTypeName::INUM:
                return (ty->name == TypeName::Int || ty->name == TypeName::SmallInt || ty->name == TypeName::Double || ty->name == TypeName::Float);
                break;
            case CharTypeName::FNUM:
                return (ty->name == TypeName::Double || ty->name == TypeName::Float || ty->name == TypeName::Numeric);
                break;
            case CharTypeName::TEXT:
                return (ty->name == TypeName::Char);
                break;
            case CharTypeName::DATENUM:
                tmpdate = DateType(value->data.c_str());
                if (!tmpdate.islegal())
                    return false;
                return (ty->name == TypeName::Date);
                break;
            case CharTypeName::NULLC:
                return true;
                break;
            }
            break;
        case exprType::COLUMN:                        
            for (j = 0; j < ds.size(); j++)
                if ((strcmp(col->tname.c_str(),ds[j]->getName())==0)||((col->tname == "")&&(ds.size()==1)))
                    for (i = 0; i < ds[j]->getnum(); i++) {
                        if (strcmp(col->aname.c_str(), ds[j]->getTypeName(i)) == 0) {
                            if (ty->name == TypeName::Char)
                                return (ds[j]->getPart(i)->getType() == ty->name && ((DtypeSchemaChar*)ds[j]->getPart(i))->getlen() == ty->p1);
                            if (ty->name == TypeName::Numeric)
                                return (ds[j]->getPart(i)->getType() == ty->name && ((DtypeSchemaNumeric*)ds[j]->getPart(i))->getsumd() == ty->p1 && ((DtypeSchemaNumeric*)ds[j]->getPart(i))->getdotd() == ty->p2);
                            return (ds[j]->getPart(i)->getType() == ty->name);
                        }
            }
            return false;
            break;
        case exprType::EXPR2:
            switch (op) {
            case clacopName::ADD:
            case clacopName::MINUS:
            case clacopName::MULTI:
            case clacopName::DIV:
                if (ty->name != TypeName::Int && ty->name != TypeName::SmallInt && ty->name != TypeName::Double && ty->name != TypeName::Float)
                    return false;
                return (expr1->checkdata(ds, ty) && expr2->checkdata(ds, ty));
                break;
            case clacopName::MODC:
                if (ty->name != TypeName::Int && ty->name != TypeName::SmallInt)
                    return false;
                return (expr1->checkdata(ds, ty) && expr2->checkdata(ds, ty));
                break;
            }
            break;
        }
    }
    bool checkdata(DSchema* sh, typeTree* ty) {
        int i;
        DateType tmpdate;
        switch (k) {
        case exprType::VALUE:
            switch (value->k) {
            case CharTypeName::INUM:
                return (ty->name == TypeName::Int || ty->name == TypeName::SmallInt || ty->name == TypeName::Double || ty->name == TypeName::Float);
                break;
            case CharTypeName::FNUM:
                return (ty->name == TypeName::Double || ty->name == TypeName::Float || ty->name == TypeName::Numeric);
                break;
            case CharTypeName::TEXT:
                return (ty->name == TypeName::Char);
                break;
            case CharTypeName::DATENUM:
                tmpdate = DateType(value->data.c_str());
                if (!tmpdate.islegal())
                    return false;
                return (ty->name == TypeName::Date);
                break;
            case CharTypeName::NULLC:
                return true;
                break;
            }
            break;
        case exprType::COLUMN:
            if (col->tname != "" && strcmp(col->tname.c_str(), sh->getName()) != 0)
                return false;
            for (i = 0; i < sh->getnum(); i++) {
                if (strcmp(col->aname.c_str(), sh->getTypeName(i)) == 0) {
                    if (ty->name == TypeName::Char)
                        return (sh->getPart(i)->getType() == ty->name && ((DtypeSchemaChar*)sh->getPart(i))->getlen() == ty->p1);
                    if (ty->name == TypeName::Numeric)
                        return (sh->getPart(i)->getType() == ty->name && ((DtypeSchemaNumeric*)sh->getPart(i))->getsumd() == ty->p1 && ((DtypeSchemaNumeric*)sh->getPart(i))->getdotd() == ty->p2);
                    return (sh->getPart(i)->getType() == ty->name);
                }
            }
            return false;
            break;
        case exprType::EXPR2:
            switch (op) {
            case clacopName::ADD:
            case clacopName::MINUS:
            case clacopName::MULTI:
            case clacopName::DIV:
                if (ty->name != TypeName::Int && ty->name != TypeName::SmallInt && ty->name != TypeName::Double && ty->name != TypeName::Float)
                    return false;
                return (expr1->checkdata(sh, ty) && expr2->checkdata(sh, ty));
                break;
            case clacopName::MODC:
                if (ty->name != TypeName::Int && ty->name != TypeName::SmallInt)
                    return false;
                return (expr1->checkdata(sh, ty) && expr2->checkdata(sh, ty));
                break;
            }
            break;
        }
    }
    bool makedata(std::vector<DList*> &dl, DtypeData* ans, typeTree* ty) {
        int i,j;
        DtypeData* tmp;
        int tmpint;
        short tmpshort;
        int tmplen;
        char* tmpchar;
        double tmpdouble;
        float tmpfloat;
        DateType tmpdate;
        NumericType tmpnumeric;
        switch (k) {
        case exprType::VALUE:
            switch (value->k) {
            case CharTypeName::INUM:
                switch (ty->name) {
                case(TypeName::Int):
                    tmpint = atoi(value->data.c_str());
                    ans->setData(&tmpint);
                    break;
                case (TypeName::SmallInt):
                    tmpshort = atoi(value->data.c_str());
                    ans->setData(&tmpshort);
                    break;
                case(TypeName::Double):
                    tmpdouble = atof(value->data.c_str());
                    ans->setData(&tmpdouble);
                    break;
                case (TypeName::Float):
                    tmpfloat = atof(value->data.c_str());
                    ans->setData(&tmpfloat);
                    break;
                }
                break;
            case CharTypeName::FNUM:
                switch (ty->name) {
                case(TypeName::Double):
                    tmpdouble = atof(value->data.c_str());
                    ans->setData(&tmpdouble);
                    break;
                case (TypeName::Float):
                    tmpfloat = atof(value->data.c_str());
                    ans->setData(&tmpfloat);
                    break;
                case (TypeName::Numeric):
                    tmpnumeric = NumericType();
                    tmpnumeric.setd(value->data.c_str(), ty->p1, ty->p2);
                    ans->setData(&tmpnumeric);
                    break;
                }
                break;
            case CharTypeName::TEXT:
                tmplen = ty->p1;
                tmpchar = new char[tmplen];
                memcpy(tmpchar, value->data.c_str(), tmplen);
                ans->setData(tmpchar);
                delete[]tmpchar;
                break;
            case CharTypeName::DATENUM:
                tmpdate = DateType(value->data.c_str());
                ans->setData(&tmpdate);
                break;
            case CharTypeName::NULLC:
                switch (ty->name) {
                case (TypeName::Int):
                    ans->setData((int*)NULL);
                    break;
                case (TypeName::SmallInt):
                    ans->setData((short*)NULL);
                    break;
                case (TypeName::Char):
                    ans->setData((char*)NULL);
                    break;
                case (TypeName::Double):
                    ans->setData((double*)NULL);
                    break;
                case (TypeName::Float):
                    ans->setData((float*)NULL);
                    break;
                case (TypeName::Date):
                    ans->setData((DateType*)NULL);
                    break;
                case (TypeName::Numeric):
                    ans->setData((NumericType*)NULL);
                    break;
                }
                break;
            }
            return true;
            break;
        case exprType::COLUMN:
            for (j = 0; j < dl.size(); j++)
                if ((strcmp(col->tname.c_str(), dl[j]->getfa()->getName()) == 0) || ((col->tname == "") && (dl.size() == 1)))
                    for (i = 0; i < dl[j]->getfa()->getnum(); i++) {
                        if (strcmp(col->aname.c_str(), dl[j]->getfa()->getTypeName(i)) == 0) {
                            switch (ty->name) {
                            case TypeName::Int:
                                ans->setData(((int*)dl[j]->getPart(i)->getData()));
                                break;
                            case TypeName::SmallInt:
                                ans->setData(((short*)dl[j]->getPart(i)->getData()));
                                break;
                            case TypeName::Char:
                                ans->setData(((char*)dl[j]->getPart(i)->getData()));
                                break;
                            case TypeName::Double:
                                ans->setData(((double*)dl[j]->getPart(i)->getData()));
                                break;
                            case TypeName::Float:
                                ans->setData(((float*)dl[j]->getPart(i)->getData()));
                                break;
                            case TypeName::Date:
                                ans->setData(((DateType*)dl[j]->getPart(i)->getData()));
                                break;
                            case TypeName::Numeric:
                                ans->setData(((NumericType*)dl[j]->getPart(i)->getData()));
                                break;
                            }
                            return true;
                        }
                    }
            break;
        case exprType::EXPR2:
            switch (ty->name) {
            case TypeName::Int:
                tmp = new DtypeDataInt();
                break;
            case TypeName::SmallInt:
                tmp = new DtypeDataSmallInt();
                break;
            case TypeName::Char:
                tmp = new DtypeDataChar(((DtypeDataChar*)ans)->get_len());
                break;
            case TypeName::Double:
                tmp = new DtypeDataDouble();
                break;
            case TypeName::Float:
                tmp = new DtypeDataFloat();
                break;
            case TypeName::Date:
                tmp = new DtypeDataDate();
                break;
            case TypeName::Numeric:
                tmp = new DtypeDataNumeric(((DtypeDataNumeric*)ans)->getsumdotd());
                break;
            }
            if (!expr1->makedata(dl, ans, ty)) {
                delete tmp;
                return false;
            }
            if (!expr2->makedata(dl, tmp, ty)) {
                delete tmp;
                return false;
            }
            if (ans->getData() == NULL || tmp->getData() == NULL) {
                switch (ty->name) {
                case (TypeName::Int):
                    ans->setData((int*)NULL);
                    break;
                case (TypeName::SmallInt):
                    ans->setData((short*)NULL);
                    break;
                case (TypeName::Char):
                    ans->setData((char*)NULL);
                    break;
                case (TypeName::Double):
                    ans->setData((double*)NULL);
                    break;
                case (TypeName::Float):
                    ans->setData((float*)NULL);
                    break;
                case (TypeName::Date):
                    ans->setData((DateType*)NULL);
                    break;
                case (TypeName::Numeric):
                    ans->setData((NumericType*)NULL);
                    break;
                }
                delete tmp;
                return false;
            }
            switch (op) {
            case clacopName::ADD:
                switch (ty->name) {
                case TypeName::Int:
                    *((int*)ans->getData()) += *((int*)tmp->getData());
                    break;
                case TypeName::SmallInt:
                    *((short*)ans->getData()) += *((short*)tmp->getData());
                    break;
                case TypeName::Double:
                    *((double*)ans->getData()) += *((double*)tmp->getData());
                    break;
                case TypeName::Float:
                    *((float*)ans->getData()) += *((float*)tmp->getData());
                    break;
                }
                break;
            case clacopName::MINUS:
                switch (ty->name) {
                case TypeName::Int:
                    *((int*)ans->getData()) -= *((int*)tmp->getData());
                    break;
                case TypeName::SmallInt:
                    *((short*)ans->getData()) -= *((short*)tmp->getData());
                    break;
                case TypeName::Double:
                    *((double*)ans->getData()) -= *((double*)tmp->getData());
                    break;
                case TypeName::Float:
                    *((float*)ans->getData()) -= *((float*)tmp->getData());
                    break;
                }
                break;
            case clacopName::MULTI:
                switch (ty->name) {
                case TypeName::Int:
                    *((int*)ans->getData()) *= *((int*)tmp->getData());
                    break;
                case TypeName::SmallInt:
                    *((short*)ans->getData()) *= *((short*)tmp->getData());
                    break;
                case TypeName::Double:
                    *((double*)ans->getData()) *= *((double*)tmp->getData());
                    break;
                case TypeName::Float:
                    *((float*)ans->getData()) *= *((float*)tmp->getData());
                    break;
                }
                break;
            case clacopName::DIV:
                switch (ty->name) {
                case TypeName::Int:
                    if ((*((int*)tmp->getData())) == 0) {
                        delete tmp;
                        return false;
                    }
                    *((int*)ans->getData()) /= *((int*)tmp->getData());
                    break;
                case TypeName::SmallInt:
                    if ((*((int*)tmp->getData())) == 0) {
                        delete tmp;
                        return false;
                    }
                    *((short*)ans->getData()) /= *((short*)tmp->getData());
                    break;
                case TypeName::Double:
                    if ((*((int*)tmp->getData())) == 0) {
                        delete tmp;
                        return false;
                    }
                    *((double*)ans->getData()) /= *((double*)tmp->getData());
                    break;
                case TypeName::Float:
                    if ((*((int*)tmp->getData())) == 0) {
                        delete tmp;
                        return false;
                    }
                    *((float*)ans->getData()) /= *((float*)tmp->getData());
                    break;
                }
                break;
            case clacopName::MODC:
                switch (ty->name) {
                case TypeName::Int:
                    if ((*((int*)tmp->getData())) == 0) {
                        delete tmp;
                        return false;
                    }
                    *((int*)ans->getData()) %= *((int*)tmp->getData());
                    break;
                case TypeName::SmallInt:
                    if ((*((int*)tmp->getData())) == 0) {
                        delete tmp;
                        return false;
                    }
                    *((short*)ans->getData()) %= *((short*)tmp->getData());
                    break;
                }
                break;
            }
            delete tmp;
            return true;
            break;
        }
    }
    bool makedata(DList* b, DtypeData* ans, typeTree* ty) {
        int i;
        DtypeData* tmp;
        int tmpint;
        short tmpshort;
        int tmplen;
        char* tmpchar;
        double tmpdouble;
        float tmpfloat;
        DateType tmpdate;
        NumericType tmpnumeric;
        switch (k) {
        case exprType::VALUE:
            switch (value->k) {
            case CharTypeName::INUM:
                switch (ty->name) {
                case(TypeName::Int):
                    tmpint = atoi(value->data.c_str());
                    ans->setData(&tmpint);
                    break;
                case (TypeName::SmallInt):
                    tmpshort = atoi(value->data.c_str());
                    ans->setData(&tmpshort);
                    break;
                case(TypeName::Double):
                    tmpdouble = atof(value->data.c_str());
                    ans->setData(&tmpdouble);
                    break;
                case (TypeName::Float):
                    tmpfloat = atof(value->data.c_str());
                    ans->setData(&tmpfloat);
                    break;
                }
                break;
            case CharTypeName::FNUM:
                switch (ty->name) {
                case(TypeName::Double):
                    tmpdouble = atof(value->data.c_str());
                    ans->setData(&tmpdouble);
                    break;
                case (TypeName::Float):
                    tmpfloat = atof(value->data.c_str());
                    ans->setData(&tmpfloat);
                    break;
                case (TypeName::Numeric):
                    tmpnumeric = NumericType();
                    tmpnumeric.setd(value->data.c_str(), ty->p1, ty->p2);
                    ans->setData(&tmpnumeric);
                    break;
                }
                break;
            case CharTypeName::TEXT:
                tmplen = ty->p1;
                tmpchar = new char[tmplen];
                memcpy(tmpchar, value->data.c_str(), tmplen);
                ans->setData(tmpchar);
                delete[]tmpchar;
                break;
            case CharTypeName::DATENUM:
                tmpdate = DateType(value->data.c_str());
                ans->setData(&tmpdate);
                break;
            case CharTypeName::NULLC:
                switch (ty->name) {
                case (TypeName::Int):
                    ans->setData((int*)NULL);
                    break;
                case (TypeName::SmallInt):
                    ans->setData((short*)NULL);
                    break;
                case (TypeName::Char):
                    ans->setData((char*)NULL);
                    break;
                case (TypeName::Double):
                    ans->setData((double*)NULL);
                    break;
                case (TypeName::Float):
                    ans->setData((float*)NULL);
                    break;
                case (TypeName::Date):
                    ans->setData((DateType*)NULL);
                    break;
                case (TypeName::Numeric):
                    ans->setData((NumericType*)NULL);                    
                    break;
                }                                
                break;
            }
            return true;
            break;
        case exprType::COLUMN:
            for (i = 0; i < b->getfa()->getnum(); i++) {
                if (strcmp(col->aname.c_str(), b->getfa()->getTypeName(i)) == 0) {                    
                    switch (ty->name) {
                    case TypeName::Int:
                        ans->setData(((int*)b->getPart(i)->getData()));
                        break;
                    case TypeName::SmallInt:
                        ans->setData(((short*)b->getPart(i)->getData()));
                        break;
                    case TypeName::Char:
                        ans->setData(((char*)b->getPart(i)->getData()));
                        break;
                    case TypeName::Double:
                        ans->setData(((double*)b->getPart(i)->getData()));
                        break;
                    case TypeName::Float:
                        ans->setData(((float*)b->getPart(i)->getData()));
                        break;
                    case TypeName::Date:
                        ans->setData(((DateType*)b->getPart(i)->getData()));
                        break;
                    case TypeName::Numeric:
                        ans->setData(((NumericType*)b->getPart(i)->getData()));
                        break;
                    }                    
                    return true;
                }
            }
            break;
        case exprType::EXPR2:
            switch (ty->name) {
            case TypeName::Int:
                tmp = new DtypeDataInt();
                break;
            case TypeName::SmallInt:
                tmp = new DtypeDataSmallInt();
                break;
            case TypeName::Char:
                tmp = new DtypeDataChar(((DtypeDataChar*)ans)->get_len());
                break;
            case TypeName::Double:
                tmp = new DtypeDataDouble();
                break;
            case TypeName::Float:
                tmp = new DtypeDataFloat();
                break;
            case TypeName::Date:
                tmp = new DtypeDataDate();
                break;
            case TypeName::Numeric:
                tmp = new DtypeDataNumeric(((DtypeDataNumeric*)ans)->getsumdotd());
                break;
            }
            if (!expr1->makedata(b, ans, ty)) {
                delete tmp;
                return false;
            }
            if (!expr2->makedata(b, tmp, ty)) {
                delete tmp;
                return false;
            }
            if (ans->getData() == NULL || tmp->getData() == NULL) {
                switch (ty->name) {
                case (TypeName::Int):
                    ans->setData((int*)NULL);
                    break;
                case (TypeName::SmallInt):
                    ans->setData((short*)NULL);
                    break;
                case (TypeName::Char):
                    ans->setData((char*)NULL);
                    break;
                case (TypeName::Double):
                    ans->setData((double*)NULL);
                    break;
                case (TypeName::Float):
                    ans->setData((float*)NULL);
                    break;
                case (TypeName::Date):
                    ans->setData((DateType*)NULL);
                    break;
                case (TypeName::Numeric):
                    ans->setData((NumericType*)NULL);
                    break;
                }
                delete tmp;
                return false;
            }
            switch (op) {
            case clacopName::ADD:                                
                switch (ty->name) {
                case TypeName::Int:
                    *((int*)ans->getData()) += *((int*)tmp->getData());
                    break;
                case TypeName::SmallInt:
                    *((short*)ans->getData()) += *((short*)tmp->getData());
                    break;
                case TypeName::Double:
                    *((double*)ans->getData()) += *((double*)tmp->getData());
                    break;
                case TypeName::Float:
                    *((float*)ans->getData()) += *((float*)tmp->getData());
                    break;
                }
                break;
            case clacopName::MINUS:
                switch (ty->name) {
                case TypeName::Int:
                    *((int*)ans->getData()) -= *((int*)tmp->getData());
                    break;
                case TypeName::SmallInt:
                    *((short*)ans->getData()) -= *((short*)tmp->getData());
                    break;
                case TypeName::Double:
                    *((double*)ans->getData()) -= *((double*)tmp->getData());
                    break;
                case TypeName::Float:
                    *((float*)ans->getData()) -= *((float*)tmp->getData());
                    break;
                }
                break;
            case clacopName::MULTI:                
                switch (ty->name) {
                case TypeName::Int:
                    *((int*)ans->getData()) *= *((int*)tmp->getData());
                    break;
                case TypeName::SmallInt:
                    *((short*)ans->getData()) *= *((short*)tmp->getData());
                    break;
                case TypeName::Double:
                    *((double*)ans->getData()) *= *((double*)tmp->getData());
                    break;
                case TypeName::Float:
                    *((float*)ans->getData()) *= *((float*)tmp->getData());
                    break;
                }
                break;
            case clacopName::DIV:                
                switch (ty->name) {
                case TypeName::Int:
                    if ((*((int*)tmp->getData())) == 0) {
                        delete tmp;
                        return false;
                    }                        
                    *((int*)ans->getData()) /= *((int*)tmp->getData());
                    break;
                case TypeName::SmallInt:
                    if ((*((int*)tmp->getData())) == 0) {
                        delete tmp;
                        return false;
                    }
                    *((short*)ans->getData()) /= *((short*)tmp->getData());
                    break;
                case TypeName::Double:
                    if ((*((int*)tmp->getData())) == 0) {
                        delete tmp;
                        return false;
                    }
                    *((double*)ans->getData()) /= *((double*)tmp->getData());
                    break;
                case TypeName::Float:
                    if ((*((int*)tmp->getData())) == 0) {
                        delete tmp;
                        return false;
                    }
                    *((float*)ans->getData()) /= *((float*)tmp->getData());
                    break;
                }
                break;
            case clacopName::MODC:
                switch (ty->name) {
                case TypeName::Int:
                    if ((*((int*)tmp->getData())) == 0) {
                        delete tmp;
                        return false;
                    }
                    *((int*)ans->getData()) %= *((int*)tmp->getData());
                    break;
                case TypeName::SmallInt:
                    if ((*((int*)tmp->getData())) == 0) {
                        delete tmp;
                        return false;
                    }
                    *((short*)ans->getData()) %= *((short*)tmp->getData());
                    break;
                }
                break;
            }
            delete tmp;
            return true;
            break;
        }
    }
    ~exprTree() {
        switch (k) {
        case exprType::VALUE:
            delete value;
            break;
        case exprType::COLUMN:
            delete col;
            break;
        case exprType::EXPR2:
            delete expr1, expr2;
            break;
        };
    }
};
class comparisonTree :public Tree {
    friend class WhereClausesTree;
protected:
    columnTree* col;
    opName op;
    exprTree* expr;
public:
    comparisonTree(columnTree* x1, opName y, exprTree* x2) {
        col = x1;
        op = y;
        expr = x2;
    }
    ~comparisonTree() {
        delete col;
        if (expr != nullptr)delete expr;
    }
};
class conditionsTree :public Tree {
    friend class WhereClausesTree;
protected:
    std::vector<comparisonTree*> a;
public:
    conditionsTree() {
        a.clear();
    }
    void append(comparisonTree* i) {
        a.push_back(i);
    }
    ~conditionsTree() {
        for (auto i : a) {
            delete i;
        }
    }
};
class WhereClausesTree {
private:
    conditionsTree* a;
public:
    WhereClausesTree(conditionsTree* i) {
        a = i;
    }
    WhereClausesTree() {
        a = nullptr;
    }
    bool checklist(std::vector<DSchema*> &ds) {
        if (a == nullptr)return true;
        int i, j, n;
        n = a->a.size();
        typeTree* ty;
        TypeName tyname;
        bool flag;
        int k = -1;
        for (i = 0; i < n; i++) {
            if ((a->a[i]->col->tname != "") ||((a->a[i]->col->tname=="")&& ds.size() ==1)) {
                bool flag = false;
                for (j = 0; j < ds.size(); j++)
                    if ((strcmp(a->a[i]->col->tname.c_str(), ds[j]->getName()) == 0) || ((strcmp(a->a[i]->col->tname.c_str(), "") == 0) && (ds.size() == 1))) {
                        k = j;
                        flag = true;
                        break;
                    }
                if (!flag)
                    return false;
            }
            else 
                return false;
            flag = false;
            for (j = 0; j < ds[k]->getnum(); j++) {
                if (strcmp(ds[k]->getTypeName(j), a->a[i]->col->aname.c_str()) == 0) {
                    tyname = ds[k]->getPart(j)->getType();
                    if (tyname == TypeName::Char) {
                        ty = new typeTree(TypeName::Char, ((DtypeSchemaChar*)ds[k]->getPart(j))->getlen());
                    }
                    else
                        if (tyname == TypeName::Numeric) {
                            ty = new typeTree(TypeName::Numeric, ((DtypeSchemaNumeric*)ds[k]->getPart(j))->getsumd(), ((DtypeSchemaNumeric*)ds[k]->getPart(j))->getdotd());
                        }
                        else ty = new typeTree(tyname);

                    flag = true;
                    break;
                }
            }
            if (!flag)
                return false;
            if (a->a[i]->op == opName::GT || a->a[i]->op == opName::LT || a->a[i]->op == opName::LE || a->a[i]->op == opName::LE)
                if (ty->name == TypeName::Char || ty->name == TypeName::Date || ty->name == TypeName::Numeric) {
                    delete ty;
                    return false;
                }
            if (a->a[i]->expr != nullptr)
                if (!a->a[i]->expr->checkdata(ds, ty)) {
                    delete ty;
                    return false;
                }
            delete ty;
        }
        return true;        
    }
    bool check(DSchema* sh) {
        if (a == nullptr)return true;
        int i, j, n;
        n = a->a.size();
        typeTree* ty;
        TypeName tyname;
        bool flag;
        for (i = 0; i < n; i++) {            
            if (strcmp(a->a[i]->col->tname.c_str(),"") != 0 && strcmp(a->a[i]->col->tname.c_str(), sh->getName()) != 0)
                return false;
            flag = false;
            for (j = 0; j < sh->getnum(); j++) {
                if (strcmp(sh->getTypeName(j), a->a[i]->col->aname.c_str()) == 0) {
                    tyname = sh->getPart(j)->getType();
                    if (tyname == TypeName::Char) {
                        ty = new typeTree(TypeName::Char, ((DtypeSchemaChar*)sh->getPart(j))->getlen());
                    }
                    else
                        if (tyname == TypeName::Numeric) {
                            ty = new typeTree(TypeName::Numeric, ((DtypeSchemaNumeric*)sh->getPart(j))->getsumd(), ((DtypeSchemaNumeric*)sh->getPart(j))->getdotd());
                        }
                        else ty = new typeTree(tyname);

                    flag = true;
                    break;
                }
            }
            if (!flag)return false;
            if (a->a[i]->op == opName::GT || a->a[i]->op == opName::LT || a->a[i]->op == opName::LE || a->a[i]->op == opName::LE)
                if (ty->name == TypeName::Char || ty->name == TypeName::Date || ty->name == TypeName::Numeric) {
                    delete ty;
                    return false;
                }
            if (a->a[i]->expr!=nullptr)
                if (!a->a[i]->expr->checkdata(sh, ty)) {
                    delete ty;
                    return false;
                }            
            delete ty;
        }
        return true;
    }
    bool checklist(std::vector<DList*>& dl) {
        if (a == nullptr)return true;
        int i, j, l, n;
        n = a->a.size();
        typeTree* ty;
        TypeName tyname;
        DtypeData* data1, * data2;   
        bool flag;
        for (i = 0; i < n; i++) {            
            flag = false;
            for (l = 0; l < dl.size(); l++) {            
                if ((strcmp(dl[l]->getfa()->getName(), a->a[i]->col->tname.c_str())==0)||((strcmp(a->a[i]->col->tname.c_str(),"")==0)&&(dl.size()==1))) {
                    for (j = 0; j < dl[l]->getfa()->getnum(); j++) {
                        if (strcmp(dl[l]->getfa()->getTypeName(j), a->a[i]->col->aname.c_str()) == 0) {
                            tyname = dl[l]->getfa()->getPart(j)->getType();
                            switch (tyname) {
                            case TypeName::Int:
                                data1 = (DtypeDataInt*)(dl[l]->getPart(j));
                                break;
                            case TypeName::SmallInt:
                                data1 = (DtypeDataSmallInt*)(dl[l]->getPart(j));
                                break;
                            case TypeName::Char:
                                data1 = (DtypeDataChar*)(dl[l]->getPart(j));
                                break;
                            case TypeName::Double:
                                data1 = (DtypeDataDouble*)(dl[l]->getPart(j));
                                break;
                            case TypeName::Float:
                                data1 = (DtypeDataFloat*)(dl[l]->getPart(j));
                                break;
                            case TypeName::Date:
                                data1 = (DtypeDataDate*)(dl[l]->getPart(j));
                                break;
                            case TypeName::Numeric:
                                data1 = (DtypeDataNumeric*)(dl[l]->getPart(j));
                                break;
                            }
                            flag = true;
                            break;
                        }
                    }                                        
                }
                if (flag)break;
            } 
            if (!flag) 
                return false;
            switch (tyname) {
            case TypeName::Int:
                data2 = new DtypeDataInt();
                ty = new typeTree(TypeName::Int);
                break;
            case TypeName::SmallInt:
                data2 = new DtypeDataSmallInt();
                ty = new typeTree(TypeName::SmallInt);
                break;
            case TypeName::Char:
                data2 = new DtypeDataChar(((DtypeSchemaChar*)dl[l]->getfa()->getPart(j))->getlen());
                ty = new typeTree(TypeName::Char, ((DtypeSchemaChar*)dl[l]->getfa()->getPart(j))->getlen());
                break;
            case TypeName::Double:
                data2 = new DtypeDataDouble();
                ty = new typeTree(TypeName::Double);
                break;
            case TypeName::Float:
                data2 = new DtypeDataFloat();
                ty = new typeTree(TypeName::Float);
                break;
            case TypeName::Date:
                data2 = new DtypeDataDate();
                ty = new typeTree(TypeName::Date);
                break;
            case TypeName::Numeric:
                data2 = new DtypeDataNumeric(((DtypeSchemaNumeric*)dl[l]->getfa()->getPart(j))->getsumdotd());
                ty = new typeTree(TypeName::Numeric, ((DtypeSchemaNumeric*)dl[l]->getfa()->getPart(j))->getsumd(), ((DtypeSchemaNumeric*)dl[l]->getfa()->getPart(j))->getdotd());
                break;
            }
            if (a->a[i]->expr != nullptr) {
                if (!a->a[i]->expr->makedata(dl, data2, ty)) {
                    delete data2, ty;
                    return false;
                }
            }
            else {
                switch (ty->name) {
                case (TypeName::Int):
                    data2->setData((int*)NULL);
                    break;
                case (TypeName::SmallInt):
                    data2->setData((short*)NULL);
                    break;
                case (TypeName::Char):
                    data2->setData((char*)NULL);
                    break;
                case (TypeName::Double):
                    data2->setData((double*)NULL);
                    break;
                case (TypeName::Float):
                    data2->setData((float*)NULL);
                    break;
                case (TypeName::Date):
                    data2->setData((DateType*)NULL);
                    break;
                case (TypeName::Numeric):
                    data2->setData((NumericType*)NULL);
                    break;
                }
            }
            switch (a->a[i]->op) {
            case opName::EQ:
                switch (ty->name) {
                case (TypeName::Int):
                    if (*((int*)data1->getData()) != *((int*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (*((short*)data1->getData()) != *((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Char):
                    if (strcmp((char*)data1->getData(), (char*)data2->getData()) != 0) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (*((double*)data1->getData()) != *((double*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (*((float*)data1->getData()) != *((float*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Date):
                    if (!((DateType*)data1->getData())->equal((DateType*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Numeric):
                    if (!((NumericType*)data1->getData())->equal((NumericType*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                }
                break;
            case opName::GT:
                switch (ty->name) {
                case (TypeName::Int):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((int*)data1->getData()) <= *((int*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((short*)data1->getData()) <= *((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((double*)data1->getData()) <= *((double*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((float*)data1->getData()) <= *((float*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                default:
                    printf("op ERROR!\n");
                    delete data2, ty;
                    return false;
                    break;
                }
                break;
            case opName::LT:
                switch (ty->name) {
                case (TypeName::Int):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((int*)data1->getData()) >= *((int*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((short*)data1->getData()) >= *((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((double*)data1->getData()) >= *((double*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((float*)data1->getData()) >= *((float*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                default:
                    printf("op ERROR!\n");
                    delete data2, ty;
                    return false;
                    break;
                }
                break;
            case opName::GE:
                switch (ty->name) {
                case (TypeName::Int):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((int*)data1->getData()) < *((int*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((short*)data1->getData()) < *((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((double*)data1->getData()) < *((double*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((float*)data1->getData()) < *((float*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                default:
                    printf("op ERROR!\n");
                    delete data2, ty;
                    return false;
                    break;
                }
                break;
            case opName::LE:
                switch (ty->name) {
                case (TypeName::Int):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((int*)data1->getData()) > * ((int*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((short*)data1->getData()) > * ((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((double*)data1->getData()) > * ((double*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((float*)data1->getData()) > * ((float*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                default:
                    printf("op ERROR!\n");
                    delete data2, ty;
                    return false;
                    break;
                }
                break;
            case opName::NE:
                switch (ty->name) {
                case (TypeName::Int):
                    if (*((int*)data1->getData()) == *((int*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (*((short*)data1->getData()) == *((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Char):
                    if (strcmp((char*)data1->getData(), (char*)data2->getData()) == 0) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (*((double*)data1->getData()) == *((double*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (*((float*)data1->getData()) == *((float*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Date):
                    if (((DateType*)data1->getData())->equal((DateType*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Numeric):
                    if (((NumericType*)data1->getData())->equal((NumericType*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                }
                break;
            case opName::INULL:
                if (data1->getData() != NULL) {
                    delete data2, ty;
                    return false;
                }
                break;
            case opName::NNULL:
                if (data1->getData() == NULL) {
                    delete data2, ty;
                    return false;
                }
                break;
            }
            delete data2, ty;
        }
        return true;
    }
    bool check(DList* b) {
        if (a == nullptr)return true;
        int i, j, n;
        n = a->a.size();
        typeTree* ty;
        TypeName tyname;
        DtypeData* data1, * data2;
        for (i = 0; i < n; i++) {
            for (j = 0; j < b->getfa()->getnum(); j++) {
                if (strcmp(b->getfa()->getTypeName(j), a->a[i]->col->aname.c_str()) == 0) {
                    tyname = b->getfa()->getPart(j)->getType();                    
                    switch (tyname) {
                    case TypeName::Int:
                        data1 = (DtypeDataInt*)(b->getPart(j));                            
                        break;
                    case TypeName::SmallInt:
                        data1 = (DtypeDataSmallInt*)(b->getPart(j));                            
                        break;
                    case TypeName::Char:
                        data1 = (DtypeDataChar*)(b->getPart(j));                            
                        break;
                    case TypeName::Double:
                        data1 = (DtypeDataDouble*)(b->getPart(j));                            
                        break;
                    case TypeName::Float:
                        data1 = (DtypeDataFloat*)(b->getPart(j));                            
                        break;
                    case TypeName::Date:
                        data1 = (DtypeDataDate*)(b->getPart(j));                            
                        break;
                    case TypeName::Numeric:
                        data1 = (DtypeDataNumeric*)(b->getPart(j));                            
                        break;
                    }                                        
                    break;
                }
            }
            switch (tyname) {
            case TypeName::Int:                
                data2 = new DtypeDataInt();
                ty = new typeTree(TypeName::Int);
                break;
            case TypeName::SmallInt:                
                data2 = new DtypeDataSmallInt();
                ty = new typeTree(TypeName::SmallInt);
                break;
            case TypeName::Char:                
                data2 = new DtypeDataChar(((DtypeSchemaChar*)b->getfa()->getPart(j))->getlen());
                ty = new typeTree(TypeName::Char, ((DtypeSchemaChar*)b->getfa()->getPart(j))->getlen());
                break;
            case TypeName::Double:                
                data2 = new DtypeDataDouble();
                ty = new typeTree(TypeName::Double);
                break;
            case TypeName::Float:                
                data2 = new DtypeDataFloat();
                ty = new typeTree(TypeName::Float);
                break;
            case TypeName::Date:                
                data2 = new DtypeDataDate();
                ty = new typeTree(TypeName::Date);
                break;
            case TypeName::Numeric:                
                data2 = new DtypeDataNumeric(((DtypeSchemaNumeric*)b->getfa()->getPart(j))->getsumdotd());
                ty = new typeTree(TypeName::Numeric, ((DtypeSchemaNumeric*)b->getfa()->getPart(j))->getsumd(), ((DtypeSchemaNumeric*)b->getfa()->getPart(j))->getdotd());
                break;
            }
            if (a->a[i]->expr != nullptr) {
                if (!a->a[i]->expr->makedata(b, data2, ty)) {
                    delete data2, ty;
                    return false;
                }
            }
            else{
                switch (ty->name) {
                case (TypeName::Int):
                    data2->setData((int*)NULL);
                    break;
                case (TypeName::SmallInt):
                    data2->setData((short*)NULL);
                    break;
                case (TypeName::Char):
                    data2->setData((char*)NULL);
                    break;
                case (TypeName::Double):
                    data2->setData((double*)NULL);
                    break;
                case (TypeName::Float):
                    data2->setData((float*)NULL);
                    break;
                case (TypeName::Date):
                    data2->setData((DateType*)NULL);
                    break;
                case (TypeName::Numeric):
                    data2->setData((NumericType*)NULL);
                    break;
                }                
            }
            switch (a->a[i]->op) {
            case opName::EQ:                
                switch (ty->name) {
                case (TypeName::Int):
                    if (*((int*)data1->getData()) != *((int*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (*((short*)data1->getData()) != *((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Char):
                    if (strcmp((char*)data1->getData(),(char*)data2->getData())!=0) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (*((double*)data1->getData()) != *((double*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (*((float*)data1->getData()) != *((float*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Date):
                    if (!((DateType*)data1->getData())->equal((DateType*)data2->getData())) {                        
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Numeric):
                    if (!((NumericType*)data1->getData())->equal((NumericType*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                }
                break;
            case opName::GT:
                switch (ty->name) {
                case (TypeName::Int):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((int*)data1->getData()) <= *((int*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((short*)data1->getData()) <= *((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((double*)data1->getData()) <= *((double*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((float*)data1->getData()) <= *((float*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                default:
                    printf("op ERROR!\n");
                    delete data2, ty;
                    return false;
                    break;
                }
                break;
            case opName::LT:
                switch (ty->name) {
                case (TypeName::Int):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((int*)data1->getData()) >= * ((int*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((short*)data1->getData()) >= * ((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((double*)data1->getData()) >= * ((double*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((float*)data1->getData()) >= * ((float*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                default:
                    printf("op ERROR!\n");
                    delete data2, ty;
                    return false;
                    break;
                }
                break;
            case opName::GE:
                switch (ty->name) {
                case (TypeName::Int):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((int*)data1->getData()) < * ((int*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((short*)data1->getData()) < * ((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((double*)data1->getData()) < * ((double*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((float*)data1->getData()) < * ((float*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                default:
                    printf("op ERROR!\n");
                    delete data2, ty;
                    return false;
                    break;
                }
                break;
            case opName::LE:
                switch (ty->name) {
                case (TypeName::Int):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((int*)data1->getData()) > * ((int*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((short*)data1->getData()) > * ((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((double*)data1->getData()) > * ((double*)data2->getData())) {                        
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((float*)data1->getData()) > * ((float*)data2->getData())) {                        
                        delete data2, ty;
                        return false;
                    }
                    break;
                default:
                    printf("op ERROR!\n");
                    delete data2, ty;
                    return false;
                    break;
                }
                break;
            case opName::NE:
                switch (ty->name) {
                case (TypeName::Int):
                    if (*((int*)data1->getData()) == *((int*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (*((short*)data1->getData()) == *((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Char):
                    if (strcmp((char*)data1->getData(), (char*)data2->getData()) == 0) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (*((double*)data1->getData()) == *((double*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (*((float*)data1->getData()) == *((float*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Date):
                    if (((DateType*)data1->getData())->equal((DateType*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Numeric):
                    if (((NumericType*)data1->getData())->equal((NumericType*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    break;
                }
                break;
            case opName::INULL:
                if (data1->getData() != NULL) {
                    delete data2, ty;
                    return false;
                }
                break;
            case opName::NNULL:
                if (data1->getData() == NULL) {                    
                    delete data2, ty;
                    return false;
                }
                break;
            }
            delete data2, ty;
        }
        return true;
    }
    ~WhereClausesTree() {
        delete a;
    }
};

class setClauseTree :public Tree {
    friend class setClauselistTree;
protected:
    exprTree* expr;
    columnTree* col;
public:
    setClauseTree(columnTree* c, exprTree* e) {
        expr = e;
        col = c;
    }
    ~setClauseTree() {
        delete expr;
        delete col;
    }
};
class setClauselistTree :public Tree {
private:
    std::vector<setClauseTree*> a;
public:
    setClauselistTree() {
        a.clear();
    }
    bool check(DSchema* sh) {        
        int i, j, n;
        n = a.size();
        typeTree* ty;
        TypeName tyname;
        bool flag;
        for (i = 0; i < n; i++) {
            if (strcmp(a[i]->col->tname.c_str(), "") != 0 && strcmp(a[i]->col->tname.c_str(), sh->getName()) != 0)
                return false;
            flag = false;
            for (j = 0; j < sh->getnum(); j++) {
                if (strcmp(sh->getTypeName(j), a[i]->col->aname.c_str()) == 0) {
                    if (sh->getPart(j)->getisPrimary() || sh->getPart(j)->getisForeign())
                        return false;
                    tyname = sh->getPart(j)->getType();
                    if (tyname == TypeName::Char) {
                        ty = new typeTree(TypeName::Char, ((DtypeSchemaChar*)sh->getPart(j))->getlen());
                    }
                    else
                        if (tyname == TypeName::Numeric) {
                            ty = new typeTree(TypeName::Numeric, ((DtypeSchemaNumeric*)sh->getPart(j))->getsumd(), ((DtypeSchemaNumeric*)sh->getPart(j))->getdotd());
                        }
                        else ty = new typeTree(tyname);

                    flag = true;
                    break;
                }
            }
            if (!flag)return false;            
            if (!a[i]->expr->checkdata(sh, ty)) {
                delete ty;
                return false;
            }
            delete ty;
        }
        return true;
    }
    void change(DList* b) {        
        int i, j, n;
        n = a.size();
        typeTree* ty;
        TypeName tyname;
        DtypeData* data2;
        int chnum;
        for (i = 0; i < n; i++) {
            for (j = 0; j < b->getfa()->getnum(); j++) {
                if (strcmp(b->getfa()->getTypeName(j), a[i]->col->aname.c_str()) == 0) {
                    tyname = b->getfa()->getPart(j)->getType();
                    chnum = j;
                    break;
                }
            }
            switch (tyname) {
            case TypeName::Int:
                data2 = new DtypeDataInt();
                ty = new typeTree(TypeName::Int);
                break;
            case TypeName::SmallInt:
                data2 = new DtypeDataSmallInt();
                ty = new typeTree(TypeName::SmallInt);
                break;
            case TypeName::Char:
                data2 = new DtypeDataChar(((DtypeSchemaChar*)b->getfa()->getPart(j))->getlen());
                ty = new typeTree(TypeName::Char, ((DtypeSchemaChar*)b->getfa()->getPart(j))->getlen());
                break;
            case TypeName::Double:
                data2 = new DtypeDataDouble();
                ty = new typeTree(TypeName::Double);
                break;
            case TypeName::Float:
                data2 = new DtypeDataFloat();
                ty = new typeTree(TypeName::Float);
                break;
            case TypeName::Date:
                data2 = new DtypeDataDate();
                ty = new typeTree(TypeName::Date);
                break;
            case TypeName::Numeric:
                data2 = new DtypeDataNumeric(((DtypeSchemaNumeric*)b->getfa()->getPart(j))->getsumdotd());
                ty = new typeTree(TypeName::Numeric, ((DtypeSchemaNumeric*)b->getfa()->getPart(j))->getsumd(), ((DtypeSchemaNumeric*)b->getfa()->getPart(j))->getdotd());
                break;
            }
            if (!a[i]->expr->makedata(b, data2, ty)) {
                delete data2, ty;
                continue;
            }
            if ((!b->getfa()->getPart(chnum)->getAllowNull()) && (data2->getData() == NULL))
                continue;
            switch (tyname) {
            case TypeName::Int:
                b->getPart(chnum)->setData((int*)data2->getData());
                break;
            case TypeName::SmallInt:
                b->getPart(chnum)->setData((short*)data2->getData());
                break;
            case TypeName::Char:
                b->getPart(chnum)->setData((char*)data2->getData());
                break;
            case TypeName::Double:
                b->getPart(chnum)->setData((double*)data2->getData());
                break;
            case TypeName::Float:
                b->getPart(chnum)->setData((float*)data2->getData());
                break;
            case TypeName::Date:
                if (!((DateType*)data2->getData())->islegal())
                    break;
                b->getPart(chnum)->setData((DateType*)data2->getData());
                break;
            case TypeName::Numeric:
                b->getPart(chnum)->setData((NumericType*)data2->getData());
                break;
            }
        }
    }
    void append(setClauseTree* i) {
        a.push_back(i);
    }
    ~setClauselistTree() {
        for (auto i : a) {
            delete i;
        }
    }
};

class CreateDatabaseTree:public Tree {
private:
    std::string name;
public:
    CreateDatabaseTree(char* i) {
        name = i;
    }
    void visit() {
        //创建数据库（文件夹）
        string a = "../data/" + name;
        if (GetFileAttributesA(a.c_str()) == INVALID_FILE_ATTRIBUTES) {
            if (CreateDirectory(a.c_str(), NULL)){
                printf("Create Database %s success.\n",name.c_str());
            }
            else {
                printf("Create Database %s failed.\n", name.c_str());
            }
        }
        else {
            printf("Database %s already exists.\n",name.c_str());
        }
    }    
};
class DropDatabaseTree :public Tree {
private:
    std::string name;
public:
    DropDatabaseTree(char* i) {
        name = i;
    }
    void visit() {        
        //删除数据库（文件夹）
        string a = "../data/" + name;
        if (GetFileAttributesA(a.c_str()) & FILE_ATTRIBUTE_DIRECTORY) {
                string filea = a + "/*";
                WIN32_FIND_DATA FindFileData;
                HANDLE file = FindFirstFile(filea.c_str(), &FindFileData);
                if (file != INVALID_HANDLE_VALUE) {
                    do {
                        if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        }
                        else {                                                
                            DeleteFile(std::string(a+"/"+ FindFileData.cFileName).c_str());
                        }
                    } while (FindNextFile(file, &FindFileData));
                FindClose(file);
            }
            if (RemoveDirectory(a.c_str()))
                printf("Drop Database %s success.\n",name.c_str());
        }
        else {
            printf("Database %s doesn't exist.\n",name.c_str());
        }        
    }
};
class UseDatabaseTree :public Tree {
private:
    std::string name;
public:
    UseDatabaseTree(char* i) {
        name = i;
    }
    void visit() {
        //指定当前数据库
        if (_access(std::string("../data/" + name + "/").c_str(), 0) == -1) {
            printf("Database %s is not exist!\n",name.c_str());
            return;
        }
        CurrentDatabase = name;        

        //主键外键重新初始化
        pd.clean();
        fd.clean();
        /*
        string a = "../data/" + name + "/*";
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file != INVALID_HANDLE_VALUE) {
            do {
                if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                }
                else {
                    int fileID;
                    rm->OpenFile(std::string("../data/" + name + "/" + FindFileData.cFileName).c_str(), fileID);
                    DSchema* sh = new DSchema();
                    rm->GetSchema(fileID, *sh);
                    for (int i = 0; i < sh->getnum();i++) {
                        if (sh->getPart(i)->getisPrimary()) {
                            pd.add(FindFileData.cFileName,sh->getTypeName(i),sh->getPart(i));
                            //主键具体数值更新
                            if (!rm->PDUpdate(fileID, pd.num - 1, i, sh)) {
                                printf("Read Table %s Error!\n", FindFileData.cFileName);
                            }
                        }
                        if (sh->getPart(i)->getisForeign()) {
                            fd.add(FindFileData.cFileName, sh->getTypeName(i), sh->getPart(i)->getKey());
                        }                    
                    }
                    rm->CloseFile(fileID);
                }
            } while (FindNextFile(file, &FindFileData));
        }                    
        FindClose(file);
        */
        printf("Use Database %s success.\n",name.c_str());
    }
};
class ShowDatabaseTree :public Tree {
private:
    std::string name;
public:
    ShowDatabaseTree(char* i) {
        name = i;
    }
    void visit() {
        //查找指定数据库的所有表
        if (_access(std::string("../data/" + name + "/").c_str(), 0) == -1) {
            printf("There is no Database %s.\n", name.c_str());
            return;
        }
        string a = "../data/" + name + "/*";        
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table in %s.\n",name.c_str());
        }
        else {
            printf("Table names in %s:\n",name.c_str());
            do {
                if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {                    
                }
                else {                    
                    printf("%s\n",FindFileData.cFileName);                    
                }
            } while (FindNextFile(file, &FindFileData));
        }
        FindClose(file);
    }
};
class ShowDatabaseSTree :public Tree {
public:
    ShowDatabaseSTree() {        
    }
    void visit() {
        //查找所有数据库        
        string a = "../data/*";        
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFileA(a.c_str(), &FindFileData);                
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Database folder.\n");
        }
        else {
            printf("Database names:\n");            
            do {
                if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    if ((strcmp(FindFileData.cFileName,".")) && (strcmp(FindFileData.cFileName, "..")))                        
                        printf("%s\n", FindFileData.cFileName);
                }
                else {                                        
                }
            } while (FindNextFileA(file, &FindFileData));
        }
        FindClose(file);
    }
};
class ShowDatabaseDescTree :public Tree {
private:
    std::string name;
public:
    ShowDatabaseDescTree(char* i) {
        name = i;
    }
    void visit() {
        //查找指定数据库的所有表，反向输出
        if (_access(std::string("../data/" + name + "/").c_str(), 0) == -1) {
            printf("There is no Database %s.\n", name.c_str());
            return;
        }
        string a = "../data/" + name + "/*";        
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        vector<string> b;
        b.clear();
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Database %s.\n",name.c_str());
        }
        else {
            printf("Table names Desc in %s:\n",name.c_str());
            do {
                if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                }
                else {
                    b.push_back(FindFileData.cFileName);                    
                }
            } while (FindNextFile(file, &FindFileData));     
            for (int i = b.size() - 1; i >= 0; i--) {
                printf("%s\n",b[i].c_str());                
            }
        }
        FindClose(file);
    }
};

class CreateTableTree :public Tree {
private:
    std::string name;
    attributelistTree* attribute;
public:
    CreateTableTree(char* i, attributelistTree* j) {
        name = i;
        attribute = j;
    }
    void visit() {        
        //创建表（文件）           
        if (_access(std::string("../data/"+ CurrentDatabase+"/").c_str(), 0) == -1 || CurrentDatabase=="") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + name;
        if (GetFileAttributesA(a.c_str()) != INVALID_FILE_ATTRIBUTES) {            
            printf("Table %s already exists.\n", name.c_str());
            return;
        }        
        attribute->visit(name.c_str());
        //外键约束检查
        /*
        int i,j;
        bool flag=true;
        for (i = 0; i < attribute->data->getnum(); i++) 
            if (attribute->data->getPart(i)->getisForeign()) {
                flag = false;
                for (j=0;j<pd.num;j++)
                    if ((pd.filename[j] == std::string(attribute->data->getPart(i)->getFile())) && (pd.attrname[j] == std::string(attribute->data->getPart(i)->getName()))) 
                        if (pd.a[j]->sameType(attribute->data->getPart(i))) {
                            flag = true;
                            break;
                        }     
                if (!flag)break;
            }        
        if (!flag) {
            printf("Add Foreign Key Failed!\n");
            return;
        }
        */
        //主键外键添加
        /*
        for (int i = 0; i < attribute->data->getnum(); i++) {
            if (attribute->data->getPart(i)->getisPrimary()) {
                pd.add(name.c_str(), attribute->data->getTypeName(i), attribute->data->getPart(i));                
            }
            if (attribute->data->getPart(i)->getisForeign()) {
                fd.add(name.c_str(), attribute->data->getTypeName(i), attribute->data->getPart(i)->getKey());
            }
        }
        */

        //printf("create table way:%s\n", std::string("../data/" + CurrentDatabase + "/" + name).c_str());
        rm->CreateFileF(std::string("../data/" + CurrentDatabase + "/" + name).c_str(), attribute->data);
        printf("Create Table %s success.\n", name.c_str());
    }
    ~CreateTableTree() {
        delete attribute;
    }
};
class DropTableTree :public Tree {
private:
    std::string name;
public:
    DropTableTree(char* i) {
        name = i;
    }
    void visit() {        
        //删除表（文件）
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + name;
        if ((GetFileAttributesA(a.c_str()) & FILE_ATTRIBUTE_DIRECTORY)==0) {    
            //外键约束检查
            int i;
            bool flag = true;
            for (i = 0; i < fd.num; i++)
                if (fd.reffilename[i] == name) {
                    flag = false;
                    break;
                }
            if (!flag) {
                printf("Delete Primary Key Failed!\n");
                return;
            }
            //主键外键删除
            i = 0;
            while (i < pd.num) {
                if (pd.filename[i] == name) {
                    pd.num--;
                    pd.filename[i] = pd.filename[pd.num];
                    pd.unnum[i] = pd.unnum[pd.num];
                    pd.pdname[i] = pd.pdname[pd.num];
                    pd.attrname[i][0] = pd.attrname[pd.num][0];
                    if (pd.unnum[i]>1)
                        pd.attrname[i][1] = pd.attrname[pd.num][1];
                    if (pd.unnum[i] > 2)
                        pd.attrname[i][2] = pd.attrname[pd.num][2];
                    delete pd.a[i];
                    pd.a[i] = pd.a[pd.num];
                    pd.a.pop_back();                    
                }
                else i++;
            }
            i = 0;
            while (i < fd.num) {
                if (fd.filename[i] == name) {
                    fd.num--;
                    fd.filename[i] = fd.filename[fd.num];
                    fd.reffilename[i] = fd.reffilename[fd.num];
                    fd.unnum[i] = fd.unnum[fd.num];
                    fd.fdname[i] = fd.fdname[fd.num];
                    fd.attrname[i][0] = fd.attrname[fd.num][0];
                    fd.refattrname[i][0] = fd.refattrname[fd.num][0];
                    if (fd.unnum[i] > 1) {
                        fd.attrname[i][1] = fd.attrname[fd.num][1];
                        fd.refattrname[i][1] = fd.refattrname[fd.num][1];
                    }
                    if (fd.unnum[i] > 2) {
                        fd.attrname[i][2] = fd.attrname[fd.num][2];
                        fd.refattrname[i][2] = fd.refattrname[fd.num][2];
                    }
                }
                else i++;
            }

            if (DeleteFile(a.c_str()))
                printf("Drop Table %s success.\n", name.c_str());
        }
        else {
            printf("Table %s doesn't exist.\n", name.c_str());
        }
    }
};
class ShowTableTree :public Tree {
private:
    std::string name;
public:
    ShowTableTree(char* i) {
        name = i;
    }
    void visit() {
        //查找当前数据库特定表和表的具体数据
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/"+name;
        //printf("show table way:%s\n", a.c_str());
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table %s.\n",name.c_str());
        }
        else {
            printf("Table:%s\n", name.c_str());            
            if (!rm->ShowTable(a.c_str(),false)) {
                printf("Read Table %s Error!\n", FindFileData.cFileName);
            }         
        }
        FindClose(file);
    }
};
class ShowTableDescTree :public Tree {
private:
    std::string name;
public:
    ShowTableDescTree(char* i) {
        name = i;
    }
    void visit() {
        //查找当前数据库特定表和表的具体数据，反向输出
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + name;
        //printf("show table way:%s\n", a.c_str());
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table %s.\n", name.c_str());
        }
        else {
            printf("Table:%s\n", name.c_str());
            if (!rm->ShowTable(a.c_str(), true)) {
                printf("Read Table %s Error!\n", FindFileData.cFileName);
            }
        }
        FindClose(file);
    }
};
class ShowTableSTree :public Tree {
public:
    ShowTableSTree() {
    }
    void visit() {
        //查找当前数据库所有表和表的细节
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/*";
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no CurrentDatabase.\n");
        }
        else {
            printf("Tables in %s:\n", CurrentDatabase.c_str());
            do {
                if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                }
                else {
                    printf("Table:%s\n", FindFileData.cFileName);
                    if (!rm->ShowTable(std::string("../data/" + CurrentDatabase + "/" + FindFileData.cFileName).c_str(), false)) {
                        printf("Read Table %s Error!\n", FindFileData.cFileName);
                    }
                }
            } while (FindNextFile(file, &FindFileData));
        }
        FindClose(file);
    }
};

class CreateIndexTree :public Tree {
private:
    std::string idxname,tabname,attrname;
public:
    CreateIndexTree(char* i1, char* i2, char* i3) {
        idxname = i1;
        tabname = i2;
        attrname = i3;
    }
    void visit() {
        //执行
    }
};
class DropIndexTree :public Tree {
private:
    std::string name;
public:
    DropIndexTree(char* i) {
        name = i;
    }
    void visit() {
        //执行
    }
};

class AddPrimaryTree :public Tree {
private:
    columnlistTree* collist;
    std::string tname,name;    
public:
    AddPrimaryTree(char* t, columnlistTree* col,char* na) {
        tname = t;
        name = na;
        collist = col;
    }
    void visit() {
        //添加主键约束    
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + tname;
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table %s.\n", tname.c_str());
            return;
        }       
        if (collist->a.size() > 3) {
            printf("There is too many Primary Keys.\n");
            return;
        }
        for (int i = 0; i < pd.num; i++)
            if (pd.filename[i] == tname)
            {
                printf("There is Primary Key in the same table.");
                return;
            }
        int fileID;
        rm->OpenFile(a.c_str(), fileID);
        DSchema* sh = new DSchema();
        rm->GetSchema(fileID, *sh);
        int i, j, k;
        int ll[40];
        int anum[3];        
        int n = collist->a.size();
        for (j = 0; j < n; j++) {
            anum[j] = -1;
            for (i = 0; i < sh->getnum(); i++) {
                if (collist->a[j]->tname != "")
                    break;
                if (strcmp(sh->getTypeName(i), collist->a[j]->aname.c_str()) == 0) {
                    anum[j] = i;
                    break;
                }
            }                
            if (anum[j] == -1)
            {
                printf("Wrong Attribute Name!\n");
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            if (sh->getPart(anum[j])->getisPrimary()) {
                printf("Attribute is Already Primary Key!\n");
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
        }       
        BufType filebuf = new unsigned int[2048];
        if (rm->fm->readPage(fileID, 0, filebuf, 0) == -1) {
            printf("AddPrimary readPage ERROR\n");
            delete[] filebuf;
            delete sh;
            rm->CloseFile(fileID);
            FindClose(file);
            return;
        }
        int pagenum;
        pagenum = filebuf[0];
        BufType pagebuf = new unsigned int[2048];
        DList* b = new DList(sh);
        Myhash* ha = new Myhash();       
        ha->setunnum(n);
        for (j = 0; j < n; j++) {
            ha->setType(sh->getPart(anum[j])->getType(),j);
            if (sh->getPart(anum[j])->getType() == TypeName::Int) {
                ha->setlen(((DtypeSchemaInt*)sh->getPart(anum[j]))->getlen(),j);
            }
            if (sh->getPart(anum[j])->getType() == TypeName::Char) {
                ha->setlen(((DtypeSchemaChar*)sh->getPart(anum[j]))->getlen(),j);
            }
            if (sh->getPart(anum[j])->getType() == TypeName::Numeric) {
                ha->setsumd(((DtypeSchemaNumeric*)sh->getPart(anum[j]))->getsumd(),j);
                ha->setdotd(((DtypeSchemaNumeric*)sh->getPart(anum[j]))->getdotd(),j);
            }
        }
        
        for (i = 1; i <= pagenum; i++) {
            if (rm->fm->readPage(fileID, i, pagebuf, 0) == -1) {
                printf("AddPrimary readPage ERROR\n\n");
                delete ha;
                delete[] filebuf;
                delete[] pagebuf;
                delete sh;
                delete b;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            k = Wei::wei[31] - 1 - pagebuf[1];
            ll[0] = 0;
            while (k > 0) {
                j = k & (-k);
                k -= j;
                j = Wei::BitConvInt(j);
                ll[0] += 1;
                ll[ll[0]] = j;
            }
            for (j = 1; j <= ll[0]; j++) {
                b->readDataBuf(pagebuf + 2 + 64 * ll[j]);
                if (n == 1) {
                    if (ha->Find(1, b->getPart(anum[0]))) {
                        printf("Primary Data Conflict!\n");
                        delete ha;
                        delete[] pagebuf;
                        delete[] filebuf;
                        delete sh;
                        delete b;
                        rm->CloseFile(fileID);
                        FindClose(file);
                        return;
                    }
                    else {
                        ha->Insert(b->getPart(anum[0]));
                    }
                }
                if (n == 2) {
                    if (ha->Find(2, b->getPart(anum[0]), b->getPart(anum[1]))) {
                        printf("Primary Data Conflict!\n");
                        delete ha;
                        delete[] pagebuf;
                        delete[] filebuf;
                        delete sh;
                        delete b;
                        rm->CloseFile(fileID);
                        FindClose(file);
                        return;
                    }
                    else {
                        ha->Insert(b->getPart(anum[0]), b->getPart(anum[1]));
                    }
                }
                if (n == 3) {
                    if (ha->Find(3, b->getPart(anum[0]), b->getPart(anum[1]), b->getPart(anum[2]))) {
                        printf("Primary Data Conflict!\n");
                        delete ha;
                        delete[] pagebuf;
                        delete[] filebuf;
                        delete sh;
                        delete b;
                        rm->CloseFile(fileID);
                        FindClose(file);
                        return;
                    }
                    else {
                        ha->Insert(b->getPart(anum[0]), b->getPart(anum[1]), b->getPart(anum[2]));
                    }
                }
            }
        }
        for (j = 0; j < n; j++) {            
            sh->a[anum[j]]->isPrimary = true;
        }
        
        sh->writeSchemaBuf(filebuf + 2);
        if (rm->fm->writePage(fileID, 0, filebuf, 0) == -1) {
            printf("AddPrimary writePage ERROR\n");
            delete ha;
            delete[] pagebuf;
            delete[] filebuf;
            delete sh;
            delete b;
            rm->CloseFile(fileID);
            FindClose(file);
            return;
        }
        pd.unnum[pd.num] = n;
        pd.filename[pd.num] = tname;
        pd.pdname[pd.num] = name;
        for (j = 0; j < n; j++)
            pd.attrname[pd.num][j] = sh->getTypeName(anum[j]);
        pd.a.push_back(ha);
        pd.num++;

        delete[] pagebuf;
        delete[] filebuf;
        delete sh;
        delete b;
        rm->CloseFile(fileID);
    }
};
class AddForeignTree :public Tree {
private:
    columnlistTree *collist,*refcollist;
    std::string tname, reftname, name;

public:
    AddForeignTree(char* t, columnlistTree* col,char* reft, columnlistTree* refcol,char* na) {
        tname = t;
        reftname = reft;
        name = na;
        collist = col;
        refcollist = refcol;
    }
    void visit() {
        //添加外键约束
        if (collist->a.size() != refcollist->a.size()) {
            printf("Attribute Num Fault!\n");            
            return;
        }
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + tname;
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table %s.\n", name.c_str());
            FindClose(file);
            return;
        }
        int fileID;
        rm->OpenFile(a.c_str(), fileID);
        DSchema* sh = new DSchema();
        rm->GetSchema(fileID, *sh);
        int i, j, k;
        int ll[40];
        int anum[3];
        int n = collist->a.size();
        for (j = 0; j < n; j++)
            anum[j] = -1;
        int pdnum = -1;
        for (j = 0; j < n; j++)
            for (i = 0; i < sh->getnum(); i++)
                if (strcmp(sh->getTypeName(i), collist->a[j]->aname.c_str()) == 0) {
                    anum[j] = i;
                    break;
                }
        for (i = 0; i < pd.num; i++)
            if (pd.filename[i] == reftname) {
                if (pd.unnum[i] != refcollist->a.size()) {
                    printf("Reference Attribute Num Fault!\n");
                    delete sh;
                    rm->CloseFile(fileID);
                    FindClose(file);
                    return;
                }
                for (j = 0; j < pd.unnum[i]; j++) {
                    if (refcollist->a[j]->tname != "") {
                        printf("Attribute Name Fault!\n");
                        delete sh;
                        rm->CloseFile(fileID);
                        FindClose(file);
                        return;
                    }
                    if (pd.attrname[i][j] != refcollist->a[j]->aname) {
                        printf("Reference Attribute Name Fault!\n");
                        delete sh;
                        rm->CloseFile(fileID);
                        FindClose(file);
                        return;
                    }
                }                    
                pdnum = i;
                break;
            }       
        for (j = 0; j < n; j++)
            if (anum[j] == -1) {
                printf("Wrong Attribute Name!\n");
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
        if (pdnum == -1)
        {
            printf("Wrong Attribute Name!\n");
            delete sh;
            rm->CloseFile(fileID);
            FindClose(file);
            return;
        }
        for (i = 0; i < n; i++)
            if (sh->getPart(anum[i])->getisForeign()) {
                printf("Attribute is Already Foreign Key!\n");
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
        for (i = 0; i < n; i++)
            if (!pd.a[pdnum]->sameType(sh->getPart(anum[i]),i)) {
                printf("Attribute Type is not Matching!\n");
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
        BufType filebuf = new unsigned int[2048];
        if (rm->fm->readPage(fileID, 0, filebuf, 0) == -1) {
            printf("AddForeign readPage ERROR\n");
            delete[] filebuf;
            delete sh;
            rm->CloseFile(fileID);
            FindClose(file);
            return;
        }
        int pagenum;
        pagenum = filebuf[0];
        BufType pagebuf = new unsigned int[2048];
        DList* b = new DList(sh);
        for (i = 1; i <= pagenum; i++) {
            if (rm->fm->readPage(fileID, i, pagebuf, 0) == -1) {
                printf("AddForeign readPage ERROR\n\n");
                delete[] filebuf;
                delete[] pagebuf;
                delete sh;
                delete b;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            k = Wei::wei[31] - 1 - pagebuf[1];
            ll[0] = 0;
            while (k > 0) {
                j = k & (-k);
                k -= j;
                j = Wei::BitConvInt(j);
                ll[0] += 1;
                ll[ll[0]] = j;
            }
            for (j = 1; j <= ll[0]; j++) {
                b->readDataBuf(pagebuf + 2 + 64 * ll[j]);
                if (n == 1)
                    if (!pd.a[pdnum]->Find(1, b->getPart(anum[0]))) {
                        printf("Foreign Data Conflict!\n");
                        delete[] pagebuf;
                        delete[] filebuf;
                        delete sh;
                        delete b;
                        rm->CloseFile(fileID);
                        FindClose(file);
                        return;
                    }
                if (n == 2)
                    if (!pd.a[pdnum]->Find(2, b->getPart(anum[0]), b->getPart(anum[1]))) {
                        printf("Foreign Data Conflict!\n");
                        delete[] pagebuf;
                        delete[] filebuf;
                        delete sh;
                        delete b;
                        rm->CloseFile(fileID);
                        FindClose(file);
                        return;
                    }
                if (n == 3)
                    if (!pd.a[pdnum]->Find(1, b->getPart(anum[0]), b->getPart(anum[2]), b->getPart(anum[3]))) {
                        printf("Foreign Data Conflict!\n");
                        delete[] pagebuf;
                        delete[] filebuf;
                        delete sh;
                        delete b;
                        rm->CloseFile(fileID);
                        FindClose(file);
                        return;
                    }
            }
        }      
        for (i = 0; i < n; i++){
            sh->a[anum[i]]->setisForeign(true);
            sh->a[anum[i]]->initfilename();
            sh->a[anum[i]]->setFile(tname.c_str());
            sh->a[anum[i]]->setName(collist->a[i]->aname.c_str());
        }
        
        sh->writeSchemaBuf(filebuf + 2);
        if (rm->fm->writePage(fileID, 0, filebuf, 0) == -1) {
            printf("AddForeign writePage ERROR\n");
            delete[] pagebuf;
            delete[] filebuf;
            delete sh;
            delete b;
            rm->CloseFile(fileID);
            FindClose(file);
            return;
        }
        fd.filename[fd.num] = tname;
        fd.unnum[fd.num] = n;
        fd.reffilename[fd.num] = reftname;
        for (i = 0; i < n; i++) {
            fd.attrname[fd.num][i] = collist->a[i]->aname;            
            fd.refattrname[fd.num][i] = refcollist->a[i]->aname;
        }            
        fd.fdname[fd.num] = name;
        fd.num++;

        delete[] pagebuf;
        delete[] filebuf;
        delete sh;
        delete b;
        rm->CloseFile(fileID);
    }
};

class DropPrimaryTree :public Tree {
private:
    std::string tname, pdname;
public:
    DropPrimaryTree(char* i) {
        tname = i;
        pdname = "";
    }
    DropPrimaryTree(char* t, char* a) {
        tname = t;
        pdname = a;
    }
    void visit() {
        //删除主键
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + tname;
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table %s.\n", tname.c_str());
        }
        else {
            int fileID;
            int i, j, k;
            k = -1;
            int n = 0;
            rm->OpenFile(a.c_str(), fileID);
            DSchema* sh = new DSchema();
            rm->GetSchema(fileID, *sh);
            if (pdname == "") {
                for (i = 0; i < pd.num; i++)
                    if (pd.filename[i] == tname) {
                        k = i;
                        pdname = pd.pdname[i];
                        break;
                    }
            }
            else
                for (i = 0; i < pd.num; i++)
                    if (pd.filename[i] == tname && pdname == pd.pdname[i]) {
                        k = i;                        
                        break;
                    }                

            if (k == -1) {
                printf("There is no Primary Key %s in Table %s\n", pdname.c_str(), tname.c_str());
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }            
            for (i = 0; i < fd.num; i++)
                if (fd.reffilename[i] == tname) {                    
                    printf("There is Other Foreign Key reference to this Key!\n");
                    delete sh;
                    rm->CloseFile(fileID);
                    FindClose(file);
                    return;
                }
            int anum[3];
            for (j = 0; j < pd.unnum[k]; j++)
                for (i = 0; i < sh->getnum(); i++)
                    if (pd.attrname[k][j] == std::string(sh->getTypeName(i)))
                        anum[j] = i;
            for (i = 0; i < pd.unnum[k]; i++)
                sh->getPart(anum[i])->setisPrimary(false);            

            pd.num--;
            delete pd.a[k];
            pd.a[k] = pd.a[pd.num];
            pd.a.pop_back();
            pd.filename[k] = pd.filename[pd.num];
            pd.unnum[k] = pd.unnum[pd.num];
            pd.attrname[k][0] = pd.attrname[pd.num][0];
            pd.attrname[k][1] = pd.attrname[pd.num][1];
            pd.attrname[k][2] = pd.attrname[pd.num][2];
            pd.pdname[k] = pd.pdname[pd.num];                                                

            BufType buf = new unsigned int[2048];
            if (rm->fm->readPage(fileID, 0, buf, 0) == -1) {
                printf("DropPrimary readPage ERROR\n");
                delete[] buf;
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            sh->writeSchemaBuf(buf + 2);
            if (rm->fm->writePage(fileID, 0, buf, 0) == -1) {
                printf("DropPrimary writePage ERROR\n");
                delete[] buf;
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            delete[] buf;            
            delete sh;
            rm->CloseFile(fileID);            
        }
        FindClose(file);        
    }
};
class DropForeignTree :public Tree {
private:
    std::string tname,fdname;
public:
    DropForeignTree(char* t,char* a) {
        tname = t;
        fdname = a;
    }
    void visit() {
        //删除外键
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + tname;
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table %s.\n", tname.c_str());
        }
        else {
            int fileID;
            int i, j, k;
            k = -1;
            int anum[3];
            rm->OpenFile(a.c_str(), fileID);
            DSchema* sh = new DSchema();
            rm->GetSchema(fileID, *sh);            
            for (i = 0; i < fd.num; i++)
                if (fdname == fd.fdname[i]) {
                    k = i;
                    break;
                }
            if (k == -1) {
                printf("There is no Foreign Key %s in Table %s\n", fdname.c_str(), tname.c_str());
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }            
            for (j = 0; j < fd.unnum[k]; j++)
                for (i = 0; i < sh->getnum(); i++)
                    if (sh->getPart(i)->getisForeign() && strcmp(fd.attrname[k][j].c_str(), sh->getTypeName(i)) == 0) {
                        anum[j] = i;
                        break;
                    }            
            for (j = 0; j < fd.unnum[k]; j++) {                
                sh->getPart(anum[j])->clearfileattr();                
                sh->getPart(anum[j])->setisForeign(false);
            }       

            fd.num--;
            fd.filename[k] = fd.filename[fd.num];
            fd.fdname[k] = fd.fdname[fd.num];
            fd.reffilename[k] = fd.reffilename[fd.num];
            fd.unnum[k] = fd.unnum[k];
            for (i = 0; i < fd.unnum[k]; i++)
            {
                fd.attrname[k][i] = fd.attrname[fd.num][i];
                fd.refattrname[k][i] = fd.refattrname[fd.num][i];
            }                        

            BufType buf = new unsigned int[2048];
            if (rm->fm->readPage(fileID, 0, buf, 0) == -1) {
                printf("DropForeign readPage ERROR\n");
                delete[] buf;
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            sh->writeSchemaBuf(buf + 2);
            if (rm->fm->writePage(fileID, 0, buf, 0) == -1) {
                printf("DropForeign writePage ERROR\n");
                delete[] buf;
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            delete[] buf;
            delete sh;
            rm->CloseFile(fileID);
        }
        FindClose(file);
    }
};
class AddAttributeTree :public Tree {
private:
    std::string name;
    attributeTree* attribute;
public:
    AddAttributeTree(char* i, attributeTree* a) {
        name = i;
        attribute = a;
    }
    void visit() {   
        //添加属性
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + name;
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table %s.\n", name.c_str());
            FindClose(file);
            return;
        }        
        if (!attribute->isPrimary && !attribute->isForeign) {
            //添加普通属性
            int fileID;
            rm->OpenFile(a.c_str(), fileID);
            DSchema* sh = new DSchema();

            rm->GetSchema(fileID, *sh);            

            BufType filebuf = new unsigned int[2048];
            if (rm->fm->readPage(fileID, 0, filebuf, 0) == -1) {
                printf("AddAttribute readPage ERROR\n");
                delete[] filebuf;
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            int pagenum;
            pagenum = filebuf[0];            

            DList* b;
            int i, j, k;
            int ll[40];
            BufType pagebuf = new unsigned int[2048];
            BufType buf = new unsigned int[64];
            for (i = 1; i <= pagenum; i++) {
                rm->fm->readPage(fileID, i, pagebuf, 0);
                k = Wei::wei[31] - 1 - pagebuf[1];
                ll[0] = 0;
                while (k > 0) {
                    j = k & (-k);
                    k -= j;
                    j = Wei::BitConvInt(j);
                    ll[0] += 1;
                    ll[ll[0]] = j;
                }
                for (j = 1; j <= ll[0]; j++) {
                    b = new DList(sh);
                    b->readDataBuf(pagebuf + 2 + 64 * ll[j]);                    
                    attribute->addpart(b);
                    b->writeDataBuf(buf);
                    delete b;
                    memcpy(pagebuf + 2 + 64 * ll[j], buf, 256);
                }
                rm->fm->writePage(fileID, i, pagebuf, 0);
            }
            attribute->addpart(sh);
            sh->writeSchemaBuf(filebuf + 2);
            rm->fm->writePage(fileID, 0, filebuf, 0);
            delete[] buf;
            delete[] filebuf;
            delete[] pagebuf;
            delete sh;            
            rm->CloseFile(fileID);
        }
        if (attribute->isPrimary) {
            //添加主键约束
            printf("Can't AddAttribute Primary Key.\n");
            FindClose(file);
            return;
        }
        if (attribute->isForeign) {
            //添加外键约束
            printf("AddAttribute Foreign Key.\n");
            FindClose(file);
            return;
        }        
        FindClose(file);
    }
    ~AddAttributeTree() {
        delete attribute;
    }
};
class DropAttributeTree :public Tree {
private:
    std::string tname, aname;
public:
    DropAttributeTree(char* t, char* a)
    {
        tname = t;
        aname = a;
    }
    void visit() {
        //删除属性
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + tname;
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table %s.\n", tname.c_str());
        }
        else {
            int fileID;
            rm->OpenFile(a.c_str(), fileID);
            DSchema* sh = new DSchema();

            rm->GetSchema(fileID, *sh);
            int i, j, k;            
            k = -1;
            for (i=0;i<sh->getnum();i++)
                if (strcmp(aname.c_str(), sh->getTypeName(i)) == 0)
                {
                    k = i;
                    break;
                }
            if (k == -1) {
                printf("Wrong Attribute Name!\n");
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }            
            if (sh->getPart(k)->getisPrimary() || sh->getPart(k)->getisForeign()) {
                printf("Can't Drop Primary Key or Foreign Key!\n");
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }                 
            int attrnum = k;

            BufType filebuf = new unsigned int[2048];
            if (rm->fm->readPage(fileID, 0, filebuf, 0) == -1) {
                printf("DropAttribute readPage ERROR\n");
                delete[] filebuf;
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            int pagenum;
            pagenum = filebuf[0];            
            
            DList* b;
            int ll[40];
            BufType pagebuf = new unsigned int[2048];
            BufType buf = new unsigned int[64];
            for (i = 1; i <= pagenum; i++) {
                rm->fm->readPage(fileID, i, pagebuf, 0);
                k = Wei::wei[31] - 1 - pagebuf[1];
                ll[0] = 0;
                while (k > 0) {
                    j = k & (-k);
                    k -= j;
                    j = Wei::BitConvInt(j);
                    ll[0] += 1;
                    ll[ll[0]] = j;
                }
                for (j = 1; j <= ll[0]; j++) {    
                    b = new DList(sh);
                    b->readDataBuf(pagebuf + 2 + 64 * ll[j]);                    
                    b->DropAttr(attrnum);
                    b->writeDataBuf(buf);
                    delete b;
                    memcpy(pagebuf + 2 + 64 * ll[j], buf, 256);                                        
                }            
                rm->fm->writePage(fileID, i, pagebuf, 0);
            }
            sh->DropAttr(attrnum);
            sh->writeSchemaBuf(filebuf + 2);
            rm->fm->writePage(fileID, 0, filebuf, 0);
            delete[] buf;
            delete[] filebuf;
            delete[] pagebuf;
            delete sh;            
            rm->CloseFile(fileID);
        }
        FindClose(file);
    }
};
class TableRenameTree :public Tree {
private:
    std::string oldname, newname;
public:
    TableRenameTree(char* o, char* n)
    {
        oldname = o;
        newname = n;
    }
    void visit() {
        //模式重命名        
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + oldname;        
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table %s.\n", oldname.c_str());
        }
        else {
            int fileID;
            rm->OpenFile(a.c_str(), fileID);
            DSchema* sh = new DSchema();
            rm->GetSchema(fileID, *sh);   
            sh->setName(newname.c_str());
            BufType buf = new unsigned int[2048];
            if (rm->fm->readPage(fileID, 0, buf, 0) == -1) {
                printf("Rename readPage ERROR\n");
                return;
            }            
            sh->writeSchemaBuf(buf + 2);
            if (rm->fm->writePage(fileID, 0, buf, 0) == -1) {
                printf("Rename writePage ERROR\n");
                return;
            }
            delete[] buf;
            delete sh;            
            rm->CloseFile(fileID);
            if (rename(std::string("../data/" + CurrentDatabase + "/" + oldname).c_str(), std::string("../data/" + CurrentDatabase + "/" + newname).c_str()) == 1) {
                printf("Rename File ERROR\n");
                return;
            }
        }
        FindClose(file);
    }
};

class InsertTree :public Tree {
private:
    std::string name;
    valuelistsTree* a;
public:
    InsertTree(char* na, valuelistsTree* x) {
        name = na;
        a = x;
    }
    void visit() {
        //添加记录
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string filea = "../data/" + CurrentDatabase + "/" + name;        
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(filea.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table %s.\n", name.c_str());
            FindClose(file);
            return;
        }        
        FindClose(file);
        int fileID;
        rm->OpenFile(filea.c_str(), fileID);
        DSchema* sh = new DSchema();
        rm->GetSchema(fileID, *sh);
        a->visit(sh, fileID,name.c_str());        
        delete sh;        
        rm->CloseFile(fileID);
    }
    ~InsertTree() {
        delete a;
    }
};
class DeleteTree :public Tree {
private:
    std::string name;
    WhereClausesTree* wherecl;
public:
    DeleteTree(char* na, WhereClausesTree* w) {
        name = na;
        wherecl = w;
    }
    void visit() {
        //删除记录
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + name;        
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table %s.\n", name.c_str());            
        }
        else {            
            for (int i = 0; i < fd.num; i++)
                if (fd.reffilename[i] == name) {
                    printf("There is Foreign Key reference to Table %s.Stop!\n", name.c_str());
                    FindClose(file);
                    return;
                }
            //遍历所有记录
            int fileID;            
            rm->OpenFile(a.c_str(), fileID);
            DSchema* sh = new DSchema();            
            rm->GetSchema(fileID, *sh);            
            if (!wherecl->check(sh)) {                
                printf("Where Check Fault!Stop!\n");
                delete sh;                
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            DList* b = new DList(sh);
            BufType pagebuf = new unsigned int[2048];
            if (rm->fm->readPage(fileID, 0, pagebuf, 0) == -1) {
                printf("ERROR\n");
                delete[] pagebuf;                
                delete sh;
                delete b;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            int pagenum = pagebuf[0];
            int i, j, k;
            int ll[40];

            int pdnum;            
            pdnum = -1;
            for (pdnum = 0; pdnum < pd.num; pdnum++)
                if (pd.filename[pdnum] == name)
                    break;
            int anum[3];
            for (i = 0; i < pd.unnum[pdnum]; i++) 
                for (j = 0; j < sh->getnum(); j++)
                    if (strcmp(sh->getTypeName(j), pd.attrname[pdnum][i].c_str()) == 0) {
                        anum[i] = j;
                        break;
                    }                                    

            for (i = 1; i <= pagenum; i++) {
                if (rm->fm->readPage(fileID, i, pagebuf, 0) == -1) {
                    printf("ERROR\n");                                        
                    delete[] pagebuf;
                    delete sh;
                    delete b;
                    rm->CloseFile(fileID);
                    FindClose(file);
                    return;
                }
                k = Wei::wei[31] - 1 - pagebuf[1];
                ll[0] = 0;
                while (k > 0) {
                    j = k & (-k);
                    k -= j;
                    j = Wei::BitConvInt(j);
                    ll[0] += 1;
                    ll[ll[0]] = j;
                }
                for (j = 1; j <= ll[0]; j++) {
                    b->readDataBuf(pagebuf + 2 + 64 * ll[j]);
                    if (wherecl->check(b)) {
                        rm->DeleteRecord(fileID, PageLoc(i, ll[j]));                        
                        if (pdnum != -1) {
                            if (pd.unnum[pdnum] == 1)
                                pd.a[pdnum]->Delete(b->getPart(anum[0]));
                            if (pd.unnum[pdnum] == 2)
                                pd.a[pdnum]->Delete(b->getPart(anum[0]), b->getPart(anum[1]));
                            if (pd.unnum[pdnum] == 3)
                                pd.a[pdnum]->Delete(b->getPart(anum[0]), b->getPart(anum[1]), b->getPart(anum[2]));
                        }                            
                    }                        
                }
            }
            delete[] pagebuf;
            delete sh;
            delete b;
            rm->CloseFile(fileID);
        }
        FindClose(file);
    }
    ~DeleteTree() {
        if (wherecl != nullptr)delete wherecl;
    }
};
class UpdateTree :public Tree {
private:
    std::string name;
    WhereClausesTree* wherecl;
    setClauselistTree* setcl;
public:
    UpdateTree(char* na, setClauselistTree* s, WhereClausesTree* w) {
        name = na;
        setcl = s;
        wherecl = w;
    }
    void visit() {        
        //更新记录
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + name;
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Table %s.\n", name.c_str());
        }
        else {
            //遍历所有记录
            int fileID;
            rm->OpenFile(a.c_str(), fileID);
            DSchema* sh = new DSchema();
            rm->GetSchema(fileID, *sh);
            if (!wherecl->check(sh)) {
                printf("Where Check Fault!Stop!\n");
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            if (!setcl->check(sh)) {
                printf("Set Check Fault!Stop!\n");
                delete sh;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            DList* b = new DList(sh);
            BufType pagebuf = new unsigned int[2048];
            if (rm->fm->readPage(fileID, 0, pagebuf, 0) == -1) {
                printf("ERROR\n");
                delete[] pagebuf;
                delete sh;
                delete b;
                rm->CloseFile(fileID);
                FindClose(file);
                return;
            }
            int pagenum = pagebuf[0];
            int i, j, k;
            int ll[40];
            for (i = 1; i <= pagenum; i++) {
                if (rm->fm->readPage(fileID, i, pagebuf, 0) == -1) {
                    printf("ERROR\n");
                    delete[] pagebuf;
                    delete sh;
                    delete b;
                    rm->CloseFile(fileID);
                    FindClose(file);
                    return;
                }
                k = Wei::wei[31] - 1 - pagebuf[1];
                ll[0] = 0;
                while (k > 0) {
                    j = k & (-k);
                    k -= j;
                    j = Wei::BitConvInt(j);
                    ll[0] += 1;
                    ll[ll[0]] = j;
                }
                for (j = 1; j <= ll[0]; j++) {
                    b->readDataBuf(pagebuf + 2 + 64 * ll[j]);
                    if (wherecl->check(b)) {
                        setcl->change(b);
                        rm->UpdateRecord(fileID, PageLoc(i, ll[j]), b);
                    }
                }
            }
            delete[] pagebuf;
            delete sh;
            delete b;
            rm->CloseFile(fileID);
        }
        FindClose(file);
    }
    ~UpdateTree() {
        delete setcl;
        if (wherecl != nullptr)delete wherecl;
    }
};

class tablelistTree :public Tree {
    friend class SelectTree;
protected:
    std::vector<std::string> a;
public:
    tablelistTree() {
        a.clear();
    }
    void append(char* i) {
        a.push_back(std::string(i));
    }
};
class SelectTree :public Tree {
private:
    columnlistTree* collist;
    tablelistTree* tablelist;
    WhereClausesTree* wherecl;

    std::vector<HANDLE> fl;
    std::vector<DSchema*> ds;
    std::vector<DList*> dl;
    std::vector<int> fid;
    std::vector<BufType> pbl;
    std::vector<int> pagenum;
    bool flag;
    int ans;
public:
    SelectTree(columnlistTree* cl, tablelistTree* tl, WhereClausesTree* w) {
        collist = cl;
        tablelist = tl;
        wherecl = w;
    }
    void visit() {
        //select查找具体数据
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        int tnum = tablelist->a.size();
        int i;
        for (i = 0; i < tnum; i++) {
            string a = "../data/" + CurrentDatabase + "/" + tablelist->a[i];
            WIN32_FIND_DATA FindFileData;
            HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
            if (file == INVALID_HANDLE_VALUE) {
                printf("There is no Table %s.\n", tablelist->a[i].c_str());
            }
            else {
            }
            FindClose(file);
        }
        fl.clear();
        ds.clear();
        fid.clear();
        for (i = 0; i < tnum; i++) {
            string a = "../data/" + CurrentDatabase + "/" + tablelist->a[i];
            WIN32_FIND_DATA FindFileData;
            HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
            int fileID;
            rm->OpenFile(a.c_str(), fileID);
            DSchema* sh = new DSchema();
            rm->GetSchema(fileID, *sh);
            fl.push_back(file);
            ds.push_back(sh);
            fid.push_back(fileID);
        }
        if (!wherecl->checklist(ds)) {
            printf("Where Check Fault!Stop!\n");
            for (i = 0; i < tnum; i++) {
                delete ds[i];
                rm->CloseFile(fid[i]);
                FindClose(fl[i]);
            }
            return;
        }
        dl.clear();
        pbl.clear();
        pagenum.clear();
        flag = true;
        for (i = 0; i < tnum; i++) {
            DList* b = new DList(ds[i]);
            dl.push_back(b);
            BufType pagebuf = new unsigned int[2048];
            if (rm->fm->readPage(fid[i], 0, pagebuf, 0) == -1) {
                printf("READPAGE FILE %d PAGE 0 ERROR\n", i);
                flag = false;
            }          
            pbl.push_back(pagebuf);
            pagenum.push_back(pagebuf[0]);            
        }
        if (!flag) {
            for (i = 0; i < tnum; i++) {
                delete ds[i];
                rm->CloseFile(fid[i]);
                FindClose(fl[i]);
                delete[] pbl[i];
                delete dl[i];
            }
            return;
        }

        flag = true;
        ans = 0;
        makeRecordList(0);
        printf("ALL ANSWER'S NUM IS %d\n",ans);

        for (i = 0; i < tnum; i++) {
            delete ds[i];
            rm->CloseFile(fid[i]);
            FindClose(fl[i]);
            delete[] pbl[i];
            delete dl[i];
        }
    }
    void showall(std::vector<DList*> dl) {
        int i, j;
        TypeName tn;        
        int nk;
        for (j = 0; j < dl.size(); j++) {            
            nk = dl[j]->getNull();
            printf("Table %s:\n",dl[j]->getfa()->getName());
            for (i = 0; i < dl[j]->getfa()->getnum(); i++) {
                if ((nk & Wei::wei[i]) > 0) {
                    printf("DList 's part %d is NULL\n", i);
                    continue;
                }                    
                printf("DList 's part %d is ", i);
                tn = dl[j]->getfa()->getPart(i)->getType();
                DateType* tmp;
                NumericType* tmp2;
                int sumd, dotd, len;
                switch (tn) {
                case TypeName::Int:
                    len = ((DtypeSchemaInt*)dl[j]->getfa()->getPart(i))->getlen();
                    sumd = *((int*)dl[j]->getPart(i)->getData());
                    if (sumd < 0) {
                        printf("-");
                        sumd = -sumd;
                    }
                    for (int j = len - 1; j >= 0; j--)printf("%d", sumd / Wei::shiwei[j] % 10);
                    printf("\n");
                    break;
                case TypeName::SmallInt:
                    printf("%d\n", *((short*)dl[j]->getPart(i)->getData()));
                    break;
                case TypeName::Char:
                    printf("%s\n", ((char*)dl[j]->getPart(i)->getData()));
                    break;
                case TypeName::Double:
                    printf("%f\n", *((double*)dl[j]->getPart(i)->getData()));
                    break;
                case TypeName::Float:
                    printf("%f\n", *((float*)dl[j]->getPart(i)->getData()));
                    break;
                case TypeName::Date:
                    tmp = ((DateType*)dl[j]->getPart(i)->getData());
                    printf("Date:%d\\%d\\%d\n", tmp->getyear(), tmp->getmonth(), tmp->getday());
                    break;
                case TypeName::Numeric:
                    tmp2 = ((NumericType*)dl[j]->getPart(i)->getData());
                    sumd = ((DtypeSchemaNumeric*)dl[j]->getfa()->getPart(i))->getsumd();
                    dotd = ((DtypeSchemaNumeric*)dl[j]->getfa()->getPart(i))->getdotd();
                    printf("Numeric:%s\n", tmp2->getd(sumd, dotd));
                    break;
                default:
                    printf("Type ERROR\n");
                }
            }
        }
    }
    void makeRecordList(int d) {
        if (d == tablelist->a.size()) {            
            if (wherecl->checklist(dl)) {
                ans += 1;
                if (collist == nullptr) {
                    showall(dl);
                }
                else {
                    collist->show(dl);
                }                
            }            
            return;
        }        
        
        int i, j, k;
        int ll[40];

        for (i = 1; i <= pagenum[d]; i++) {
            if (rm->fm->readPage(fid[d], i, pbl[d], 0) == -1) {
                printf("READPAGE FILE %d PAGE %d ERROR\n", d, i);
                flag = false;
                return;
            }
            k = Wei::wei[31] - 1 - pbl[d][1];
            ll[0] = 0;
            while (k > 0) {
                j = k & (-k);
                k -= j;
                j = Wei::BitConvInt(j);
                ll[0] += 1;
                ll[ll[0]] = j;
            }
            for (j = 1; j <= ll[0]; j++) {
                dl[d]->readDataBuf(pbl[d] + 2 + 64 * ll[j]);
                makeRecordList(d + 1);
            }
        }
    }
    ~SelectTree() {
        if (collist != nullptr)delete collist;
        delete tablelist;
        if (wherecl != nullptr)delete wherecl;
    }
};

#endif