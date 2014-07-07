#! /usr/bin/env python
#coding=utf-8
#获取当前目录下所有文件的名字并且在最后加上 \
import os
lineList = []
def printFile(path = "./", dirStr = ""):
    
    filesList = os.listdir(path)
    pathStr = ""
    if path != "./":
        pathStr = path[3:len(path)] + "/"
    for file in filesList:
        s = str(file)
        #忽略版本控制文件
        if s.startswith(".") or s.endswith(".h") or s.endswith(".py"):
            continue
        #判断是否为目录
        if os.path.isdir(path+"/"+s) == True:
            #递归调用
            printFile(path+"/"+s, dirStr)
        else:
            lineList.append(dirStr + pathStr + s)

    
if __name__ == "__main__":
    printFile("./", "../../Classes/")
    for name in lineList:
        if lineList.index(name) < len(lineList) - 1:
            name += " \\"
        print name
    

        