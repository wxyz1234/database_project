#ifndef TYPENAME
#define TYPENAME
enum class TypeName { Int, SmallInt, Char, Double, Float, Date, Numeric};
enum class CharTypeName { TEXT, INUM, FNUM, DATE };
enum class opName { EQ,GT,LT,GE,LE,NE,IN,NN };
enum class clacopName { ADD,MINUS,MULTI,DIV,MOD };
enum class exprType { VALUE,COLUMN,EXPR2 };
#endif