# crawl_project
A crawler for crawling web pages

1，项目简介：
本项目为一个小型的网页抓取器，实现了简单的网页抓取功能。

2，项目文件：
文件夹scmph为项目需要用到的一些库文件。
文件夹crawl_project为项目代码及输入输出文件。

3，输入输出：
系统输入为crawl_project下的url.txt文件，内含20000条url。
项目编译后的结果保存在output文件夹下。
其中
    output/bin/  --> 保存运行结果 demo
    output/conf/ --> 保存配置文件 crawl.conf(配置crawler个数)
    output/data/ --> 保存抓取的html文件 X.html
    output/log/  --> 保存运行日志 crawllog,crawllog.wf

4，编译运行：
编译：执行代码目录中的Makefile文件 --> make
运行：执行 output/bin/目录中的demo --> ./demo

5，TODOLIST:
(1)增加一些遗漏的异常处理，提高系统的容错性。
(2)增加响应信息过滤功能，只保存网页内容。
