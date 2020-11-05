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
			4、之后一个int表示主键外键，后跟参数（外键对应主键名字）。一个int表示AllowNull，一个int表示HaveDefault，后跟参数（默认值是多少）。
（3）之后每一页：
			1、单个记录长度128*4字节
			2、每一页最多存31（32-1）个记录
			3、buf[0]储存当前页存了几个记录
			4、buf[1]储存空间占用的位数组，1有空间，0没空间
			5、buf[2+]具体各个记录，每个记录都是RID信息+null记录信息+按照第一页模式顺序记录的数据值

### 四、测试数据不同模式单条记录大小计算

（1）supplier表（细节下略）：
		2(RID+isNull)+1(int)+7(char(25))+11(varchar(40))+1(int)+4(char(15))+5(numeric)+26(varchar(101))=57
（2）nation表：
		2+1+7+1+39=50
（3）region表：
		2+1+7+39=49
（4）customer表：
		2+1+7+11+1+4+5+3+26=60
（5）part表：
		2+1+7+11+3+7+1+3+5+6=46
（6）partsupp表：
		2+1+1+1+5+50=60
（7）orders表：
		2+1+1+1+5+1+4+1+4+4=24
（8）lineitem表：
		2+1+1+1+1+5+5+5+5+1+1+1+1+1+7+7+12=57

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

#### 2、RecordManageSystem/ReadFile.cpp

​    测试程序1，有待完善

#### 3、RecordManageSystem/TestRecordManager.cpp

​    测试程序2，尚未实现

### 三、记录管理模块数据储存部分

#### 1、RecordManageSystem/DType/TypeName.h

​	内置枚举型变量TypeName，记录了本数据库能支持的所有变量类型。

#### 2、RecordManageSystem/DType/DSchema.h

​	提供DSchema类，记录了一个模块的所有相关信息。

​	相关变量包括name模块名字。num属性数量。typeName不同属性的名字。DTypeSchema类数组a[i]记录了不同属性的信息。

​	相关函数有getXX、setXX等读写相关变量的函数，也有writeSchemaBuf、readSchemaBuf类整体信息和文件系统交互的函数。

#### 3、RecordManageSystem/DType/DTypeSchema.h

​	提供DtypeSchema抽象类，记录了一个模块中的属性需要的相关信息。

​	相关变量包括是否允许为空AllowNull，是否有默认值HaveDefault，以及一个def记录对应值。主键外键相关信息DKey类对象key。

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

#### 6、RecordManageSystem/DType/DKey.h

​	提供了枚举类型KeyName和对应的类DKey、DPrimary、DForeign，分别表示本属性没有特殊信息、是主键、是外键。其中DForeign还额外记录了外键对应的主键所在模式名字以及主键属性名。

#### 7、RecordManageSystem/DType/Date.h

​	提供了DateType类，负责解决日期类型数据的相关底层操作，包括记录，修改，查询，合法性判断。

### 四、记录管理模块辅助代码

#### 1、RecordManageSystem/utils/PageLoc.h

​	内置PageLoc类，这个类只有2个参数PageID, LocID。表示了文件中的一个记录位置，PageID为页码，LocID为本页中的第几个位置。

#### 2、RecordManageSystem/utils/Wei.h

​	内置Wei类，这个类内置了2的0次方到2的30次方常数，以及i与2^i的静态转化函数，主要用于位运算实现。

#### 3、RecordManageSystem/utils/Myhash.h

​	内置Myhash类，一个可以储存TypeName里所有类型数据的hash表，之后的约束性判断会使用此类。