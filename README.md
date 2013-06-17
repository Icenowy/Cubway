Cubway
======

Subway的客户端，由于某些历史原因，项目叫做Cubway。

编译：qmake&&make
执行程序：./QtMetro HTML文件路徑

在HTML(JavaScript)中使用例子：
<pre>
xxx.innerHTML=MetroView.System('ls /') //顯示'ls /'的輸出
asrc=MetroView.OpenFile() //讓用戶選取一个檔案(文件)，並把檔案路徑傳給asrc變量
</pre>
