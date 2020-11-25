#ifndef TYPENAME
#define TYPENAME
enum class TypeName { Int, SmallInt, Char, Double, Float, Date, Numeric};
enum class CharTypeName { TEXT, INUM, FNUM, DATENUM };
enum class opName { EQ,GT,LT,GE,LE,NE,IN,NN };
enum class clacopName { ADD,MINUS,MULTI,DIV,MODC };
enum class exprType { VALUE,COLUMN,EXPR2 };
#endif