// osg_hello.cpp : �������̨Ӧ�ó������ڵ㡣 
// ����osg��Ŀ��
// 1. ����Ŀ���ԣ�VC++Ŀ¼-->����Ŀ¼�����osg��includeĿ¼��
// 2. ��VC++Ŀ¼-->��Ŀ¼�����osg��libĿ¼;
// 3. ������-->������-->����������
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

