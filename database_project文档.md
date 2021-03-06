# 数据库项目记录文档

## （一）文件架构

1、filesystem：页式文件系统相关代码文件夹

2、RecordManageSystem：记录管理模块代码文件夹

3、RecordManageSystem/DType：不同数据类型储存相关代码文件夹

4、data：数据库信息储存文件夹

## （二）数据信息在文件中的储存格式

#### 一、data文件夹下的每一个文档对应一个数据库。

#### 二、数据库下的每一个文件储存了一个模式以及这个模式所有记录的信息。

#### 三、文件格式如下：

（1）第0页，buf[0]表示总页数(不包括0)、buf[1]表示总记录个数
（2）第0页，buf[2+]当前表记录格式：
			1、char[20]名字
			2、一个int对应属性数量
			3、每个属性，一个char[20]名字开头，然后1个int表示类型，然后具体参数（字符串长度上限等）。
			4、之后一个int表示是否是主键，一个int表示是否是外键，后跟参数（外键对应主键名字）。一个int表示AllowNull，一个int表示HaveDefault，后跟参数（默认值是多少）。
（3）之后每一页：
			1、单个记录长度128*4字节
			2、每一页最多存31（32-1）个记录
			3、buf[0]储存当前页存了几个记录
			4、buf[1]储存空间占用的位数组，1有空间，0没空间
			5、buf[2+]具体各个记录，每个记录都是RID信息+null记录信息+按照第一页模式顺序记录的数据值

### 四、数据约束

#### 1、主键约束

​	本项目支持最多3个一起的联合主键，用Myhash.h中实现的PrimaryData类对象pd（定义在程序入口Parser.c）进行维护，PrimaryData类中有一个Myhash对象，可以hash储存所有的主键数值用于快速判重，PrimaryData类也保存了主键文件名主键属性名，约束名等相关信息，一切对主键约束的判定和修改都会体现为对对象pd的修改。

#### 2、外键约束

​	用Myhash.h中实现的ForeignData类对象fd（定义在程序入口Parser.c）进行维护，ForeignData类保存了外键文件名外键属性名和外键依赖的主键文件名和属性名的相关信息，一切对外键约束的判定和修改都会体现为对ForeignData类对象fd的修改和对PrimaryData类对象pd的查询。

#### 3、NOT NULL约束

​	添加数据的时候进行判断，为空则报错。

#### 4、DEFAULT约束

​	添加数据的时候进行判断，为空则赋默认值。

## （三）代码文件及相关类介绍

### 一、页式文件系统相关

#### 1、filesystem/fileio/FileManager.h

​	助教提供代码，内置FileManager类，负责页式文件读写。

#### 2、filesystem/bufmanager/BufPageManager.h

​	助教提供代码，内置BufPageManager类，负责实现缓存功能提高程序效率。

#### 3、filesystem/filesystem.h

​	提供BufFileManager类，把缓存功能嵌入到页式文件读写功能里，只需要正常使用FileManager的接口也可以拥有缓存加速的功能了。

#### 4、filesystem/testfilesystem.cpp

​	助教写的极其简单的页式文件系统测试程序。

#### 5、其他非核心代码均由助教实现，原理细节请去查看助教的文档

### 二、记录管理模块核心

#### 1、RecordManageSystem/RecordManager.h

​	记录管理模块核心RecordManager类。

​	内置创建文件、删除文件、打开文件、关闭文件、写入记录、删除记录、更新记录、查看记录、读取模式等之后要用的核心函数。

#### 2、RecordManageSystem/TestRecordManager.cpp

​    测试程序1，进行了简单的模式生成和记录生成，并进行了基础的文件创建删除，文件打开关闭，模式读写，记录读写测试，保证RecordManager类正确性，**因后续更新，已不再维护**。

#### 3、RecordManageSystem/ReadFile.cpp

​    测试程序2，在测试程序1的基础上，进行了大规模记录写入，记录更新，记录删除，记录再写入，并实时检查记录储存准确性，保证RecordManager类正确性。
​	最后生成了一个Myhash类保存了所有记录的主码信息，保证Myhash类正确性，**因后续更新，已不再维护**。

### 三、记录管理模块数据储存部分

#### 1、RecordManageSystem/DType/TypeName.h

​	内置枚举型变量TypeName，记录了本数据库能支持的所有变量类型。

​	也内置了CharTypeName、opName、clacopName、exprType等用于语法分析的枚举类型变量。

#### 2、RecordManageSystem/DType/DSchema.h

​	提供DSchema类，记录了一个模块的所有相关信息。

​	相关变量包括name模块名字。num属性数量。typeName不同属性的名字。DTypeSchema类数组a[i]记录了不同属性的信息。

​	相关函数有getXX、setXX等读写相关变量的函数，也有writeSchemaBuf、readSchemaBuf类整体信息和文件系统交互的函数。

#### 3、RecordManageSystem/DType/DTypeSchema.h

​	提供DtypeSchema抽象类，记录了一个模块中的属性需要的相关信息。

​	相关变量包括是否允许为空AllowNull，是否有默认值HaveDefault，以及一个def记录对应值。

​	主键外键相关信息isPrimary，isForeign，refFile，refName记录外键依赖文件和属性名字。

​	相关函数有readBuf、writeBuf，子类初始化和文件系统中进行基础信息（比如char类型字符串上限数值）交互的函数。

​	readTypebuf、writeTypeBuf，类整体信息和文件系统交互的函数。

​	在DtypeSchema抽象类基础上，有DtypeSchemaInt、DtypeSchemaSmallInt、DtypeSchemaChar等等不同类型数据对应的子类，数量和TypeName内类型数量一致。

​	这些子类实现了getType获取类型和getsize获取数据大小等函数。

#### 4、RecordManageSystem/DType/DList.h

​	提供了DList类，记录了一条记录的所有相关信息。

​	相关变量包括对应模板指针fa，记录唯一编号RID，通过位运算记录相关属性是否为空变量isNull，isNull更新lazy标记Nullchange，和记录所有属性数值的数组a[i]。

​	相关函数包括getXX、setXX等读写相关变量的函数，也有writeDataBuf、readDataBuf类整体信息和文件系统交互的函数。

#### 5、RecordManageSystem/DType/DTypeData.h

​	提供了DtypeData抽象类，记录一条记录的某一个属性的相关信息。

​	这个类对TypeName的每一个类型都有对应子类，DtypeDataInt、DtypeDataSmallInt、DtypeDataChar等等。

​	相关函数有getData、setData等数据读写函数、getType、getsize的基础信息函数和writeDataBuf、readDataBuf等类信息和文件系统交互函数。

#### 6、RecordManageSystem/DType/Date.h

​	提供了DateType类，负责解决日期类型数据的相关底层操作，包括记录，修改，查询，合法性判断。

#### 7、RecordManageSystem/DType/Numeric.h

​	提供了NumericType类，负责解决Numeric类型数据的相关第层操作，包括记录，修改，查询，输出，合法性判断等。

### 四、记录管理模块辅助代码

#### 1、RecordManageSystem/utils/PageLoc.h

​	内置PageLoc类，这个类只有2个参数PageID, LocID。表示了文件中的一个记录位置，PageID为页码，LocID为本页中的第几个位置。

#### 2、RecordManageSystem/utils/Wei.h

​	内置Wei类，这个类内置了2的0次方到2的30次方常数，以及i与2^i的静态转化函数，主要用于位运算实现。

#### 3、RecordManageSystem/utils/Myhash.h

​	内置Myhash类，一个可以储存TypeName里所有类型数据的hash表，之后的约束性判断会使用此类。

​	内置了PrimaryData类和ForeignData类，用于记录所有主键约束和外键约束

### 五、系统管理模块和查询解析模块

#### 1、Parser/Lexer.l

​	flex词法分析器代码，用于处理所有输入语句，生成lexer.c（但是按照cpp语法编译运行）。

#### 2、Parser/Parser.y

​	bison语法分析器代码，接受lexer.c的数据并进行进一步数据分析，生成parser.h，parser.c（但是按照cpp语法编译运行）最终调用tree.h中的语句具体实现完成输入语句执行。

#### 3、Parser/makefile

​	负责编译链接Lexer.l和Parser.y，生成Lexer.c，Parser.c，Parser.h，Parser.output（这个文件展示了语法分析的所有状态和转移方式）

#### 4、Parser/tree.h

​	内部有一个父类Tree和无数不用子类，这些类会调用之前所有模块的各种代码，用于执行实现各种完全不同的语句。