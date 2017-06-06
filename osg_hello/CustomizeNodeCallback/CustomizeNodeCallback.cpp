// CustomizeNodeCallback.cpp : 定义控制台应用程序的入口点。
// 为node添加回调事件

#include "stdafx.h"
#include<osg/io_utils>
#include<osg/PositionAttitudeTransForm>
#include<osgDB/ReadFile>
#include<osgViewer/Viewer>
#include<iostream>


class RotateCallBack :public osg::NodeCallback {
public:
	RotateCallBack():_rotateZ(0.0){}

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv) {
		osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*>(node);
		if (pat)
		{
			osg::Quat quat(osg::DegreesToRadians(_rotateZ), osg::Z_AXIS);
			pat->setAttitude(quat);
			_rotateZ += 1.0;
		}

		traverse(node, nv);
	}

protected:
	double _rotateZ;
};


class InfoCallBack :public osg::NodeCallback {
public:
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv) {
		osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*>(node);
		if (pat)
		{
			double angle = 0.0;
			osg::Vec3 axis;
			pat->getAttitude().getRotate(angle, axis);

			std::cout << "Node is rotating around the(" << axis << ")axis,"
				<< osg::RadiansToDegrees(angle) << " degrees" << std::endl;
		}

		traverse(node, nv);
	}
};


int main(int argc,char** argv)
{
	osg::ArgumentParser arguments(&argc, argv);
	osg::Node* model = osgDB::readNodeFiles(arguments);
	if (!model)
	{
		model = osgDB::readNodeFile("cow.osg");
	}

	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform;
	pat->addChild(model);

	pat->setUpdateCallback(new RotateCallBack);
	pat->addUpdateCallback(new InfoCallBack);

	osgViewer::Viewer viewer;
	viewer.setSceneData(pat.get());
    return viewer.run();
}

