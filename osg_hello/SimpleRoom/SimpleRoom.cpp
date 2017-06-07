// SimpleRoom.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<osg/Texture2D>
#include<osg/Geometry>
#include<osg/Geode>
#include<osgDB/ReadFile>
#include<osgUtil/SmoothingVisitor>
#include<osgViewer/Viewer>

const float w = 4.0;
const float h = 6.0;
const float zero = 0.0;
const float nn = -0.707;
const float pn = 0.707;


osg::Drawable* createHouseWall() {
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	vertices->push_back(osg::Vec3(zero, zero, w));
	vertices->push_back(osg::Vec3(zero,zero,zero));
	vertices->push_back(osg::Vec3(h, zero, w));
	vertices->push_back(osg::Vec3(h, zero, zero));
	vertices->push_back(osg::Vec3(h,w,w));
	vertices->push_back(osg::Vec3(h,w,zero));
	vertices->push_back(osg::Vec3(zero,w,w));
	vertices->push_back(osg::Vec3(zero, w, zero));
	vertices->push_back(osg::Vec3(zero, zero, w));
	vertices->push_back(osg::Vec3(zero, zero, zero));


	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(10);
	(*normals)[0].set(nn, nn, zero);
	(*normals)[1].set(nn, nn, zero);
	(*normals)[2].set(pn, nn, zero);
	(*normals)[3].set(pn, nn, zero);
	(*normals)[4].set(pn, pn, zero);
	(*normals)[5].set(pn, pn, zero);
	(*normals)[6].set(nn, pn, zero);
	(*normals)[7].set(nn, pn, zero);
	(*normals)[8].set(nn, nn, zero);
	(*normals)[9].set(nn, nn, zero);


	osg::ref_ptr<osg::Vec2Array> texCoords = new osg::Vec2Array(10);
	(*texCoords)[0].set(0.0, 1.0);
	(*texCoords)[1].set(0.0, 0.0);
	(*texCoords)[2].set(0.3, 1.0);
	(*texCoords)[3].set(0.3, 0.0);
	(*texCoords)[4].set(0.5, 1.0);
	(*texCoords)[5].set(0.5, 0.0);
	(*texCoords)[6].set(0.8, 1.0);
	(*texCoords)[7].set(0.8, 0.0);
	(*texCoords)[8].set(1.0, 1.0);
	(*texCoords)[9].set(1.0, 0.0);


	osg::ref_ptr<osg::Geometry> houseWall = new osg::Geometry;
	houseWall->setVertexArray(vertices.get());
	houseWall->setTexCoordArray(0,texCoords.get());
	houseWall->setNormalArray(normals.get());

	houseWall->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	houseWall->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP, 0, 10));

	houseWall->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::Texture2D(osgDB::readImageFile("Images/blueFlowers.png")));

	return houseWall.release();
}


osg::Drawable* createRoomRoof() {
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	vertices->push_back(osg::Vec3(-0.2, -0.5, 3.5));
	vertices->push_back(osg::Vec3(6.2,-0.5,3.5));
	vertices->push_back(osg::Vec3(0.8,2.0,6.0));
	vertices->push_back(osg::Vec3(5.2,2.0,6.0));
	vertices->push_back(osg::Vec3(-0.2, 4.5, 3.5));
	vertices->push_back(osg::Vec3(6.2,4.5,3.5));

	osg::ref_ptr<osg::DrawArrays> root = new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP, 0, 6);
	osg::ref_ptr<osg::DrawElementsUInt> roofSide = new osg::DrawElementsUInt(osg::DrawElementsUInt::TRIANGLES, 6);
	(*roofSide)[0] = 0;
	(*roofSide)[1] = 2;
	(*roofSide)[2] = 4;
	(*roofSide)[3] = 5;
	(*roofSide)[4] = 3;
	(*roofSide)[5] = 1;


	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(0.25, zero, zero, 1.0));

	osg::ref_ptr<osg::Geometry> houseRoof = new osg::Geometry;
	houseRoof->setVertexArray(vertices.get());
	houseRoof->setColorArray(colors.get());
	houseRoof->setColorBinding(osg::Geometry::BIND_OVERALL);
	houseRoof->addPrimitiveSet(root.get());
	houseRoof->addPrimitiveSet(roofSide.get());
	
	osgUtil::SmoothingVisitor smv;
	smv.smooth(*houseRoof);
	return houseRoof.release();
}



int main()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(createHouseWall());
	geode->addDrawable(createRoomRoof());

	osgViewer::Viewer viewer;
	viewer.setSceneData(geode.get());
    return viewer.run();
}

