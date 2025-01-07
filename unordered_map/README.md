# #include<unordered_map>
`unordered_map` 的插入有两种方式，如下代码所示：
```
std::unordered_map<std::string, Parameter<float>> params;

params["param1"] = Parameter<float>("param1");

params.emplace("param2", Parameter<float>("param2"));
```


* `params["param1"]` 只要一出现就会首先调用默认的构造函数，如果没有构造函数则编译不会通过。随后会调用赋值构造函数，整个构造流程相当于
```
params["param1"] = Parameter<float>("param1");
<=>
Parameter param1;                      // 先构造
param1 = Parameter<float>("param1");   // 再赋值
```


* `params.emplace()` 方法则不会调用默认构造函数，整个构造过程相当于
```
params.emplace("param2", Parameter<float>("param2"));
<=>
Parameter param2 = Parameter<float>("param2");
```
