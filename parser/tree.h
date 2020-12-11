#ifndef TREE
#define TREE
#include <string>
#include <vector>
#include <windows.h>
#include "../RecordManageSystem/DType/DKey.h"
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
            //valuelistTreeתDList
            if (a[i]->a.size() != sh->getnum()) {
                printf("Convert %d DList Failed!\n",i);
                continue;
            }
            flag = false;
            b->isNull = 0;
            for (j = 0; j < sh->getnum();j++) {
                //NULLԼ����defaultԼ��
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
                //���帳ֵ
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
                    memcpy(tmpchar, a[i]->a[j]->data.c_str(), tmplen);                    
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
                //�������Լ��
                int k;
                if (sh->getPart(j)->getKey()->getKey()==KeyName::Primary) {
                    for (k = 0; k < pd.num; k++)
                        if (pd.filename[k] == std::string(sh->getName()) && pd.attrname[k] == std::string(sh->getTypeName(j)))
                            break;
                    if (pd.a[k]->Find(b->a[j]->getData())) {
                        printf("Primary Key Repeated!\n");
                        flag = true;
                        break;
                    }
                }
                if (sh->getPart(j)->getKey()->getKey() == KeyName::Foreign) {
                    for (k = 0; k < pd.num; k++)
                        if (pd.filename[k] == std::string(((DForeign*)sh->getPart(j)->getKey())->getFile()) && pd.attrname[k] == std::string(((DForeign*)sh->getPart(j)->getKey())->getName()))
                            break;
                    if (!pd.a[k]->Find(b->a[j]->getData())) {
                        printf("Foreign Key Not Found!\n");
                        flag = true;
                        break;
                    }
                }
            }                        
            if (flag)continue;                        
            b->makeNull();
            sumRID++;
            b->setRID(sumRID);

            //�������
            rm->InsertRecord(fileID, b);
            for (j = 0; j < pd.num; j++) 
                if (pd.filename[j]==std::string(name)){
                    int k;
                    for (k = 0; k < sh->getnum(); k++)
                        if (sh->getPart(k)->getKey()->getKey() == KeyName::Primary) {
                            pd.a[j]->Insert(b->a[k]->getData());
                            break;
                        }
                    break;
                }
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
    friend class DSchema;
protected:
    std::string name, na1, na2;
    valueTree* def;
    bool allownull, hasdefault = false;
    typeTree* type;
    KeyName k;
public:
    attributeTree(char* na, typeTree* ty, bool an, bool hd, valueTree* de = NULL) {
        k = KeyName::Null;
        name = na;
        type = ty;
        allownull = an;
        hasdefault = hd;
        if (hasdefault)def = de;
    }
    attributeTree(KeyName i, char* na, char* n1 = NULL, char* n2 = NULL) {
        k = i;
        name = na;
        if (n1 != NULL)na1 = n1;
        if (n2 != NULL)na2 = n2;
    }
    ~attributeTree() {
        if (k == KeyName::Null) {
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
        if (data->a[data->num]->HaveDefault){
            data->a[data->num]->setDefault(def->data.c_str());                    
        }
        data->a[data->num]->setKey(KeyName::Null);
        data->num++;
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
        //attributelistתDSchema
        data = new DSchema();
        int i, j;
        bool flag;
        data->setName(name);
        for (i = 0; i < a.size(); i++) {
            if (a[i]->k == KeyName::Null) {
                a[i]->addpart(data);
            }
            else {
                flag = true;
                for (j=0;j<data->num;j++)
                    if (data->typeName[j] == a[i]->name) {
                        if (a[i]->k == KeyName::Primary) {
                            data->a[j]->key = new DPrimary();
                        }
                        if (a[i]->k == KeyName::Foreign) {
                            data->a[j]->key = new DForeign();
                            data->a[j]->key->setFile(a[i]->na1.c_str());
                            data->a[j]->key->setName(a[i]->na2.c_str());
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
    friend class WhereClausesTree;
    friend class exprTree;
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
private:
    std::vector<columnTree*> a;
public:
    columnlistTree() {
        a.clear();
    }
    void append(columnTree* i) {
        a.push_back(i);
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
                    if ((b->getNull() & Wei::wei[i]) == 0) {
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
                    }
                    else {
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
                    if ((b->getNull() & Wei::wei[j]) == 0) {
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
                    }
                    else {
                        switch (tyname) {
                        case TypeName::Int:
                            data1 = (DtypeDataInt*)(b->getPart(j));
                            data1->setData((int*)NULL);
                            break;
                        case TypeName::SmallInt:
                            data1 = (DtypeDataSmallInt*)(b->getPart(j));
                            data1->setData((short*)NULL);
                            break;
                        case TypeName::Char:
                            data1 = (DtypeDataChar*)(b->getPart(j));
                            data1->setData((char*)NULL);
                            break;
                        case TypeName::Double:
                            data1 = (DtypeDataDouble*)(b->getPart(j));
                            data1->setData((double*)NULL);
                            break;
                        case TypeName::Float:
                            data1 = (DtypeDataFloat*)(b->getPart(j));
                            data1->setData((float*)NULL);
                            break;
                        case TypeName::Date:
                            data1 = (DtypeDataDate*)(b->getPart(j));
                            data1->setData((DateType*)NULL);
                            break;
                        case TypeName::Numeric:
                            data1 = (DtypeDataNumeric*)(b->getPart(j));
                            data1->setData((NumericType*)NULL);
                            break;
                        }
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
                    if (*((int*)data1->getData()) == *((int*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (*((short*)data1->getData()) == *((short*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Char):
                    if (strcmp((char*)data1->getData(),(char*)data2->getData())==0) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (*((double*)data1->getData()) == *((double*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (*((float*)data1->getData()) == *((float*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Date):
                    if (((DateType*)data1->getData())->equal((DateType*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Numeric):
                    if (((NumericType*)data1->getData())->equal((NumericType*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
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
                    if (*((int*)data1->getData()) > *((int*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((short*)data1->getData()) > *((short*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((double*)data1->getData()) > *((double*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((float*)data1->getData()) > *((float*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
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
                    if (*((int*)data1->getData()) < * ((int*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
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
                        //delete data2, ty;
                        //return true;
                    }
                    else {
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
                        //delete data2, ty;
                        //return true;
                    }
                    else {
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
                        //delete data2, ty;
                        //return true;
                    }
                    else {
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
                    if (*((int*)data1->getData()) >= * ((int*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
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
                        //delete data2, ty;
                        //return true;
                    }
                    else {
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
                        //delete data2, ty;
                        //return true;
                    }
                    else {
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
                        //delete data2, ty;
                        //return true;
                    }
                    else {
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
                    if (*((int*)data1->getData()) <= * ((int*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((short*)data1->getData()) <= * ((short*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Double):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((double*)data1->getData()) <= * ((double*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
                        delete data2, ty;
                        return false;
                    }
                    break;
                case (TypeName::Float):
                    if (data1->getData() == NULL || data2->getData() == NULL) {
                        delete data2, ty;
                        return false;
                    }
                    if (*((float*)data1->getData()) <= * ((float*)data2->getData())) {
                        //delete data2, ty;
                        //return true;
                    }
                    else {
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
                    else {
                        //delete data2, ty;
                        //return true;
                    }
                    break;
                case (TypeName::SmallInt):
                    if (*((short*)data1->getData()) == *((short*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    else {
                        //delete data2, ty;
                        //return true;
                    }
                    break;
                case (TypeName::Char):
                    if (strcmp((char*)data1->getData(), (char*)data2->getData()) == 0) {
                        delete data2, ty;
                        return false;
                    }
                    else {
                        //delete data2, ty;
                        //return true;
                    }
                    break;
                case (TypeName::Double):
                    if (*((double*)data1->getData()) == *((double*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    else {
                        //delete data2, ty;
                        //return true;
                    }
                    break;
                case (TypeName::Float):
                    if (*((float*)data1->getData()) == *((float*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    else {
                        //delete data2, ty;
                        //return true;
                    }
                    break;
                case (TypeName::Date):
                    if (((DateType*)data1->getData())->equal((DateType*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    else {
                        //delete data2, ty;
                        //return true;
                    }
                    break;
                case (TypeName::Numeric):
                    if (((NumericType*)data1->getData())->equal((NumericType*)data2->getData())) {
                        delete data2, ty;
                        return false;
                    }
                    else {
                        //delete data2, ty;
                        //return true;
                    }
                    break;
                }
                break;
            case opName::INULL:
                if (data1->getData() == NULL) {
                    //delete data2, ty;
                    //return true;
                }
                else {
                    delete data2, ty;
                    return false;
                }
                break;
            case opName::NNULL:
                if (data1->getData() != NULL) {
                    //delete data2, ty;
                    //return true;
                }
                else {
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
private:
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
    void change(DList* b) {
        //
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
        //�������ݿ⣨�ļ��У�
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
        //ɾ�����ݿ⣨�ļ��У�
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
        //ָ����ǰ���ݿ�
        if (_access(std::string("../data/" + name + "/").c_str(), 0) == -1) {
            printf("Database %s is not exist!\n",name.c_str());
            return;
        }
        CurrentDatabase = name;        

        //����������³�ʼ��
        pd.clean();
        fd.clean();
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
                        if (sh->getPart(i)->getKey()->getKey() == KeyName::Primary) {
                            pd.add(FindFileData.cFileName,sh->getTypeName(i),sh->getPart(i));
                            //����������ֵ����
                            if (!rm->PDUpdate(fileID, pd.num - 1, i, sh)) {
                                printf("Read Table %s Error!\n", FindFileData.cFileName);
                            }
                        }
                        if (sh->getPart(i)->getKey()->getKey() == KeyName::Foreign) {
                            fd.add(FindFileData.cFileName, sh->getTypeName(i), sh->getPart(i)->getKey());
                        }                    
                    }
                    rm->CloseFile(fileID);
                }
            } while (FindNextFile(file, &FindFileData));
        }                    
        FindClose(file);

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
        //����ָ�����ݿ�����б�
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
        //�����������ݿ�        
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
        //����ָ�����ݿ�����б��������
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
        //�������ļ���           
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
        //���Լ�����
        int i,j;
        bool flag=true;
        for (i = 0; i < attribute->data->getnum(); i++) 
            if (attribute->data->getPart(i)->getKey()->getKey() == KeyName::Foreign) {
                flag = false;
                for (j=0;j<pd.num;j++)
                    if ((pd.filename[j] == std::string(attribute->data->getPart(i)->getKey()->getFile())) && (pd.attrname[j] == std::string(attribute->data->getPart(i)->getKey()->getName()))) 
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
        //����������
        for (int i = 0; i < attribute->data->getnum(); i++) {
            if (attribute->data->getPart(i)->getKey()->getKey() == KeyName::Primary) {
                pd.add(name.c_str(), attribute->data->getTypeName(i), attribute->data->getPart(i));                
            }
            if (attribute->data->getPart(i)->getKey()->getKey() == KeyName::Foreign) {
                fd.add(name.c_str(), attribute->data->getTypeName(i), attribute->data->getPart(i)->getKey());
            }
        }

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
        //ɾ�����ļ���
        if (_access(std::string("../data/" + CurrentDatabase + "/").c_str(), 0) == -1 || CurrentDatabase == "") {
            printf("CurrentDatabase is not exist!\n");
            return;
        }
        string a = "../data/" + CurrentDatabase + "/" + name;
        if ((GetFileAttributesA(a.c_str()) & FILE_ATTRIBUTE_DIRECTORY)==0) {    
            //���Լ�����
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
            //�������ɾ��
            i = 0;
            while (i < pd.num) {
                if (pd.filename[i] == name) {
                    pd.num--;
                    pd.filename[i] = pd.filename[fd.num];
                    pd.attrname[i] = pd.attrname[fd.num];
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
                    fd.attrname[i] = fd.attrname[fd.num];
                    fd.reffilename[i] = fd.reffilename[fd.num];
                    fd.refattrname[i] = fd.refattrname[fd.num];                    
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
        //���ҵ�ǰ���ݿ��ض���ͱ�ľ�������
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
        //���ҵ�ǰ���ݿ��ض���ͱ�ľ������ݣ��������
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
        //���ҵ�ǰ���ݿ����б�ͱ��ϸ��
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
        //ִ��
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
        //ִ��
    }
};

class AddPrimaryTree :public Tree {
private:
    std::string tname, aname;
public:
    AddPrimaryTree(char* t, char* a) {
        tname = t;
        aname = a;
    }
    void visit() {
        //ִ��
    }
};
class DropPrimaryTree :public Tree {
private:
    std::string name;
public:
    DropPrimaryTree(char* i) {
        name = i;
    }
    void visit() {
        //ִ��
    }
};
class AddForeignTree :public Tree {
private:
    std::string tname, aname, ftname, faname;
public:
    AddForeignTree(char* t, char* a, char* ft, char* fa) {
        tname = t;
        aname = a;
        ftname = ft;
        faname = fa;
    }
    void visit() {
        //ִ��
    }
};
class DropForeignTree :public Tree {
private:
    std::string tname,aname;
public:
    DropForeignTree(char* t,char* a) {
        tname = t;
        aname = a;
    }
    void visit() {
        //ִ��
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
        //ִ��
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
        //ִ��
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
        //ִ��
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
        //��Ӽ�¼
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
        //ɾ����¼
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
            //�������м�¼
            int fileID;            
            rm->OpenFile(a.c_str(), fileID);
            DSchema* sh = new DSchema();            
            rm->GetSchema(fileID, *sh);            
            if (!wherecl->check(sh)) {                
                printf("Where Type Fault!Stop!\n");
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

            int pk, pdnum;
            for (pk = 0; pk < sh->getnum(); pk++)
                if (sh->getPart(pk)->getKey()->getKey() == KeyName::Primary)
                    break;
            if (sh->getPart(pk)->getKey()->getKey() != KeyName::Primary)
                pk = -1;
            if (pk != -1) {
                for (pdnum = 0; pdnum < pd.num; pdnum++)
                    if (pd.filename[pdnum] == name && pd.attrname[pdnum] == sh->getTypeName(pk))
                        break;
            }
            else {
                pdnum = -1;
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
                        if (pdnum != -1)
                            pd.a[pdnum]->Delete(b->getPart(pk)->getData());
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
        //ִ��
    }
    ~UpdateTree() {
        delete setcl;
        if (wherecl != nullptr)delete wherecl;
    }
};
class SelectTree :public Tree {
private:
    columnlistTree* collist;
    tablelistTree* tablelist;
    WhereClausesTree* wherecl;    
public:
    SelectTree(columnlistTree* cl, tablelistTree* tl,WhereClausesTree* w) {
        collist = cl;
        tablelist = tl;
        wherecl = w;
    }
    void visit() {
        //ִ��
    }
    ~SelectTree() {
        if (collist != nullptr)delete collist;
        delete tablelist;
        if (wherecl != nullptr)delete wherecl;
    }
};

class tablelistTree :public Tree {
private:
    std::vector<std::string> a;
public:
    tablelistTree() {
        a.clear();
    }
    void append(char* i) {
        a.push_back(std::string(i));
    }
};

#endif