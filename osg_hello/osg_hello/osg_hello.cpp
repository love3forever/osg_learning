// osg_hello.cpp : 定义控制台应用程序的入口点。 
// 配置osg项目：
// 1. 打开项目属性，VC++目录-->包含目录中添加osg的include目录；
// 2. 在VC++目录-->库目录中添加osg的lib目录;
// 3. 在属性-->链接器-->输入中增加
//		OpenThreadsd.lib
//		osgd.lib
//		osgDBd.lib
//		osgUtild.lib
//		osgGAd.lib
//		osgViewerd.lib
//		osgTextd.lib

#include "stdafx.h"
#include <osgViewer/Viewer>
#include <osgDB/ReadFile>


int main()
{
	osgViewer::Viewer viewer;
	viewer.setSceneData(osgDB::readNodeFile("cow.osg"));
    return viewer.run();
}

