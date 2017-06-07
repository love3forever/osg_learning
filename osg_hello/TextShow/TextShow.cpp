// TextShow.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<osg/Geode>
#include<osg/Geometry>
#include<osgText/Text>
#include<osgViewer/Viewer>
#include<locale.h>

void setupProperties(osgText::Text& textObj, osgText::Font* font, float size, const osg::Vec3& pos) {
	textObj.setFont(font);
	textObj.setCharacterSize(size);
	textObj.setPosition(pos);
	textObj.setColor(osg::Vec4(0.0,0.0,1.0,1.0));
	textObj.setAlignment(osgText::Text::CENTER_BOTTOM);
	textObj.setAxisAlignment(osgText::Text::XZ_PLANE);
}


void createContent(osgText::Text& textObj, const char* string) {
	int requiredSize = mbstowcs(NULL, string, 0);
	wchar_t* wtext = new wchar_t[requiredSize + 1];
	mbstowcs(wtext, string, requiredSize + 1);
	textObj.setText(wtext);
	delete wtext;
}

int main()
{
	setlocale(LC_ALL, ".936");
	const char* titleString = "木兰辞\n 拟古决绝词柬友";
	const char* textString = {
		"abc\n"
		"def\n"
		"ghi"
	};

	osgText::Font* fontHei = osgText::readFontFile("Fonts/simhei.ttf");
	osgText::Font* fontKai = osgText::readFontFile("Fonts/simkai.ttf");

	osg::ref_ptr<osgText::Text> title = new osgText::Text;
	setupProperties(*title, fontHei, 20.0f, osg::Vec3(0.0, 0.0, 0.0));
	createContent(*title, titleString);

	osg::ref_ptr<osgText::Text> text = new osgText::Text;
	setupProperties(*text, fontKai, 15.0, osg::Vec3(0.0, 0.0, -80.0));
	createContent(*text, textString);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(osg::createTexturedQuadGeometry(
		osg::Vec3(-150, 1.0, -130), osg::Vec3(300, 0.0, 0.0), osg::Vec3(0.0, 0.0, 200.0), 1.0, 1.0));
	geode->addDrawable(title.get());
	geode->addDrawable(text.get());

	osgViewer::Viewer viewer;
	viewer.setSceneData(geode.get());

    return viewer.run();
}

