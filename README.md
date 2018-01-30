# 17-years-of-Electronic-Design-Competition
17年电子设计竞赛，四轴题目源代码

## camera of ov7725
	使用的是ov7725 简单的二值化，提取黑点，投影到坐标系中（以中心为原点，实际上要加偏移量）
## flight control
	移植的匿名控制代码，修改定高部分，使用激光vl53l01定高，加上光流与下位机的ov7725，进行位置控制