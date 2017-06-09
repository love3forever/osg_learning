// Camera.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<osg/Camera>
#include<osgDB/ReadFile>
#include<osgViewer/Viewer>



osg::Camera* createBirdEye(const osg::BoundingSphere& bs) {
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

	double viewDistance = 2.0*bs.radius();
	double znear = viewDistance - bs.radius();
	double zfar = viewDistance + bs.radius();
	float top = bs.radius();
	float right = bs.radius();

	camera->setProjectionMatrixAsOrtho(-right, right, -top, top, znear, zfar);

	osg::Vec3d upDirection(0.0, 1.0, 0.0);
	osg::Vec3d viewDirection(0.0, 0.0, 1.0);
	osg::Vec3d center = bs.center();
	osg::Vec3d eyePoint = center + viewDirection*viewDistance;

	camera->setViewMatrixAsLookAt(eyePoint, center, upDirection);

	osg::ref_ptr<osg::GraphicsContext::Traits> traints = new osg::GraphicsContext::Traits;
	traints->x = 0;
	traints->y = 0;
	traints->width = 800;
	traints->height = 600;
	traints->windowDecoration = true;
	traints->pbuffer = false;
	traints->doubleBuffer = true;
	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traints.get());
	camera->setGraphicsContext(gc.get());

	return camera.release();
}


int main()
{


	osg::Node* model = osgDB::readNodeFile("lz.osg");
	osg::Camera* camera = createBirdEye(model->getBound());
	camera->addChild(model);


	osgViewer::Viewer viewer;
	viewer.setSceneData(camera);

    return viewer.run();
}

