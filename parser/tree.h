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

class valueTree :public Tree {
    friend class attributeTree;
protected:
    std::string data;
    CharTypeName k;
public:
    valueTree(CharTypeName i, char* a) {
        k = i;
        data = a;
    }
};
class valuelistTree :public Tree {
private:
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
    ~valuelistsTree() {
        for (auto i : a) {
            delete i;
        }
    }
};
class typeTree :public Tree {
    friend class DSchema;
    friend class attributeTree;
protected:
    TypeName name;
    int p1, p2;
public:
    TypeName getTypeName() {
        return name;
    }
    typeTree(TypeName i, char* i1 = "0", char* i2 = "0") {
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
    bool allownull, hasdefault;
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
        if (k == KeyName::Null)delete type;
        if (hasdefault)delete def;
    }
    void addpart(DSchema* data) {
        data->typeName[data->num] = new char[20];
        switch (type->getTypeName()) {
        case TypeName::Int:
            data->a[data->num] = new DtypeSchemaInt();
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
            break;
        default:
            printf("TypeName ERROR %d\n", type->name);
        }
        data->a[data->num]->AllowNull = allownull;
        data->a[data->num]->HaveDefault = hasdefault;
        if (data->a[data->num]->HaveDefault)data->a[data->num]->setDefault(def->data.c_str());
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
        //attributelist转DSchema
        data = new DSchema();
        int i, j;
        data->setName(name);
        for (i = 0; i < a.size(); i++) {
            if (a[i]->k == KeyName::Null) {
                a[i]->addpart(data);
            }
            else {
                //
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
            if (CreateDirectory(a.c_str(), NULL))
                printf("Create Database %s success.\n",name.c_str());
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
        CurrentDatabase = name;
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
        string a = "../data/" + name + "/*";
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no Database %s.\n",name.c_str());
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
                printf("%s\n",b[i]);
            }
        }
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
        attribute->visit(name.c_str());
        rm->CreateFileF(std::string("../data/" + CurrentDatabase + "/" + name).c_str(), attribute->data);
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
        string a = "../data/" + CurrentDatabase + "/" + name;
        if ((GetFileAttributesA(a.c_str()) & FILE_ATTRIBUTE_DIRECTORY)==0) {
            if (RemoveDirectory(a.c_str()))
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
        //查找当前数据库特定表和表的细节
        string a = "../data/" + CurrentDatabase + "/"+name;
        WIN32_FIND_DATA FindFileData;
        HANDLE file = FindFirstFile(a.c_str(), &FindFileData);
        if (file == INVALID_HANDLE_VALUE) {
            printf("There is no CurrentDatabase.\n");
        }
        else {
            printf("Table:%s\n", name.c_str());
            int fileID;
            rm->OpenFile(a.c_str(), fileID);
            DSchema* sh = new DSchema();
            rm->GetSchema(fileID, *sh);
            sh->writeDSchema();
            rm->CloseFile(fileID);            
        }
    }
};
class ShowTableSTree :public Tree {
public:
    ShowTableSTree() {
    }
    void visit() {
        //查找当前数据库所有表和表的细节
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
                    int fileID;
                    rm->OpenFile(a.c_str(), fileID);
                    DSchema* sh = new DSchema();
                    rm->GetSchema(fileID, *sh);
                    sh->writeDSchema();
                    rm->CloseFile(fileID);
                }
            } while (FindNextFile(file, &FindFileData));
        }
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
    std::string tname, aname;
public:
    AddPrimaryTree(char* t, char* a) {
        tname = t;
        aname = a;
    }
    void visit() {
        //执行
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
        //执行
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
        //执行
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
        //执行
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
        //执行
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
        //执行
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
        //执行
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
        //执行
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
        //执行
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
        //执行
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
        //执行
    }
    ~SelectTree() {
        if (collist != nullptr)delete collist;
        delete tablelist;
        if (wherecl != nullptr)delete wherecl;
    }
};

class WhereClausesTree {
private:
    conditionsTree* a;
public:
    WhereClausesTree(conditionsTree* i) {
        a = i;
    }
    ~WhereClausesTree() {
        delete a;
    }
};
class conditionsTree :public Tree {
private:
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
class comparisonTree :public Tree {
private:
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

class exprTree :public Tree {
private:
    exprType k;
    valueTree* value;
    columnTree* col;
    exprTree *expr1, *expr2;
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
class columnTree :public Tree {
private:
    std::string tname, aname;
public:
    columnTree(char* c1,char* c2) {
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
    void append(setClauseTree* i) {
        a.push_back(i);
    }
    ~setClauselistTree() {
        for (auto i : a) {
            delete i;
        }    
    }
};

#endif