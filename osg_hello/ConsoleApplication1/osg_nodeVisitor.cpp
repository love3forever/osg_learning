// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <osg/Node>
#include <osgDB/ReadFile>
#include <iostream>

class InfoVisitor :public osg::NodeVisitor {
public:
	InfoVisitor():osg::NodeVisitor(TRAVERSE_ALL_CHILDREN),_indent(0){}
	
	virtual void apply(osg::Node& node) {
		for (int i = 0; i < _indent; ++i)
		{
			std::cout << " ";
		}
		std::cout << "[" << _indent + 1 << "]" << node.libraryName()
			<< "::" << node.className() << std::endl;

		_indent++;
		traverse(node);
		_indent--;
	}


	virtual void apply(osg::Geode& node) {
		for (int i = 0; i < _indent; i++)
		{
			std::cout << " ";
		}

		std::cout << "[" << _indent + 1 << "]" << node.libraryName()
			<< "::" << node.className() << std::endl;


		for (unsigned int n = 0; n < node.getNumDrawables(); ++n)
		{
			osg::Drawable* drawable = node.getDrawable(n);

			if (!drawable) continue;
			

			for (int i = 0; i < _indent; ++i)
			{
				std::cout << " ";
			}

			std::cout << drawable->libraryName() << "::"
				<< drawable->className() << std::endl;
		}

		_indent++;
		traverse(node);
		_indent--;
	}

protected:
	int _indent;
};


int main(int argc,char** argv)
{
	osg::ArgumentParser arguments(&argc, argv);
	osg::Node* root = osgDB::readNodeFiles(arguments);
	if (!root) root = osgDB::readNodeFile("cow.osg");

	InfoVisitor infoVisitor;
	if (root)
	{
		root->accept(infoVisitor);
	}
	std::cin;
    return 0;
}

