#include <string>
#include <vector>
#include "../RecordManageSystem/DType/DKey.h"
#include "../RecordManageSystem/DType/TypeName.h"
#include "../RecordManageSystem/DType/DSchema.h"
void workerror(char* msg) {
    printf("Work error: %s\n", msg);
}
class Tree;
class CreateDatabaseTree;
class Tree {
public:
    virtual void visit() {};
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
class CreateDatabaseTree:Tree {
private:
    std::string name;
public:
    CreateDatabaseTree(char* i) {
        name = i;
    }
    void visit() {
        //执行
    }    
};
class DropDatabaseTree :Tree {
private:
    std::string name;
public:
    DropDatabaseTree(char* i) {
        name = i;
    }
    void visit() {
        //执行
    }
};
class UseDatabaseTree :Tree {
private:
    std::string name;
public:
    UseDatabaseTree(char* i) {
        name = i;
    }
    void visit() {
        //执行
    }
};
class ShowDatabaseTree :Tree {
private:
    std::string name;
public:
    ShowDatabaseTree(char* i) {
        name = i;
    }
    void visit() {
        //执行
    }
};
class ShowDatabaseSTree :Tree {
public:
    ShowDatabaseSTree() {        
    }
    void visit() {
        //执行
    }
};
class ShowDatabaseDescTree :Tree {
private:
    std::string name;
public:
    ShowDatabaseDescTree(char* i) {
        name = i;
    }
    void visit() {
        //执行
    }
};

class CreateTableTree :Tree {
private:
    std::string name;
    attributelistTree* attribute;
public:
    CreateTableTree(char* i, attributelistTree* j) {
        name = i;
        attribute = j;
    }
    void visit() {
        attribute->visit();
        //执行
    }
    ~CreateTableTree() {
        delete attribute;
    }
};
class DropTableTree :Tree {
private:
    std::string name;
public:
    DropTableTree(char* i) {
        name = i;
    }
    void visit() {
        //执行
    }
};
class ShowTableTree :Tree {
private:
    std::string name;
public:
    ShowTableTree(char* i) {
        name = i;
    }
    void visit() {
        //执行
    }
};
class ShowTableSTree :Tree {
public:
    ShowTableSTree() {
    }
    void visit() {
        //执行
    }
};

class CreateIndexTree :Tree {
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
class DropIndexTree :Tree {
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

class AddPrimaryTree :Tree {
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
class DropPrimaryTree :Tree {
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
class AddForeignTree :Tree {
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
class DropForeignTree :Tree {
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
class AddAttributeTree :Tree {
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
class DropAttributeTree :Tree {
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
class TableRenameTree :Tree {
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

class InsertTree :Tree {
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
class DeleteTree :Tree {
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
class UpdateTree :Tree {
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
class SelectTree :Tree {
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
class conditionsTree :Tree {
private:
    vector<comparisonTree*> a;
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
class comparisonTree :Tree {
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

class exprTree :Tree {
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
class columnTree :Tree {
private:
    std::string tname, aname;
public:
    columnTree(char* c1,char* c2) {
        tname = c1;
        aname = c2;
    }
    columnTree(char* c1) {
        tname = nullptr;
        aname = c1;
    }
};
class columnlistTree :Tree {
private:
    vector<columnTree*> a;
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
class tablelistTree :Tree {
private:
    vector<std::string> a;
public:
    tablelistTree() {
        a.clear();
    }
    void append(char* i) {
        a.push_back(std::string(i));
    }
};

class setClauseTree :Tree {
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
class setClauselistTree :Tree {
private:
    vector<setClauseTree*> a;
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


class attributelistTree :Tree {
private:
    DSchema* data = NULL;
    vector<attributeTree*> a;
public:
    attributelistTree() {
        a.clear();
    }
    void append(attributeTree* i) {
        a.push_back(i);
    }
    void visit() {
        //执行
        //attributelist转DSchema
        data = new DSchema();
    }
    ~attributelistTree() {
        if (data != NULL)delete data;
        for (auto i : a) {
            delete i;
        }
    }
};
class attributeTree :Tree {
private:
    std::string name,def,na1,na2;
    KeyName k;
    bool allownull, hasdefault;
    typeTree* type;
public:
    attributeTree(char* na, typeTree* ty, bool an, bool hd, char* de = NULL) {
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
        na1 = n1;
        na2 = n2;
    }
    ~attributeTree() {
        delete type;
    }
};
class typeTree :Tree {
private:
    std::string name;
    int p1, p2;
public:
    typeTree(char* i, int i1 = 0, int i2 = 0) {
        name = i;
        p1 = i1;
        p2 = i2;
    }    
};
class valuelistsTree :Tree {
private:    
    vector<attributeTree*> a;
public:
    valuelistsTree() {
        a.clear();
    }
    void append(attributeTree* i) {
        a.push_back(i);
    }   
    ~valuelistsTree() {
        for (auto i : a) {
            delete i;
        }
    }
};
class valuelistTree :Tree {
private:    
    vector<valueTree*> a;
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
class valueTree :Tree {
private:
    std::string data;
    CharTypeName k;
public:
    valueTree(CharTypeName i, char* a) {
        k = i;
        data = a;
    }
};