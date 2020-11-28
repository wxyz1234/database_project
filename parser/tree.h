#ifndef TREE
#define TREE
#include <string>
#include <vector>
#include "../RecordManageSystem/DType/DKey.h"
#include "../RecordManageSystem/DType/TypeName.h"
#include "../RecordManageSystem/DType/DSchema.h"

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
class CreateDatabaseTree:public Tree {
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
class DropDatabaseTree :public Tree {
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
class UseDatabaseTree :public Tree {
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
class ShowDatabaseTree :public Tree {
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
class ShowDatabaseSTree :public Tree {
public:
    ShowDatabaseSTree() {        
    }
    void visit() {
        //执行
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
        //执行
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
        //执行
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
        //执行
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
        //执行
    }
};
class ShowTableSTree :public Tree {
public:
    ShowTableSTree() {
    }
    void visit() {
        //执行
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
        tname = nullptr;
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


class attributelistTree :public Tree {
private:
    DSchema* data = NULL;
    std::vector<attributeTree*> a;
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
        if (data != NULL) {
            delete data;
            data = NULL;
        }
        for (auto i : a) {
            delete i;
        }
    }
};
class attributeTree :public Tree {
private:
    std::string name,na1,na2;
    valueTree* def;
    KeyName k;
    bool allownull, hasdefault;
    typeTree* type;
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
        if (n1!=NULL)na1 = n1;
        if (n2!=NULL)na2 = n2;
    }
    ~attributeTree() {
        if (k == KeyName::Null)delete type;
        if (hasdefault)delete def;
    }
};
class typeTree :public Tree {
private:
    TypeName name;
    int p1, p2;
public:
    typeTree(TypeName i, char* i1 = "0", char* i2 = "0") {
        name = i;
        p1 = atoi(i1);
        p2 = atoi(i2);       
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
class valueTree :public Tree {
private:
    std::string data;
    CharTypeName k;
public:
    valueTree(CharTypeName i, char* a) {
        k = i;
        data = a;
    }
};
#endif