#include <iostream>
#include <fstream>
#include <regex>
#include "app/parser.h"

ObjParser::ObjParser(DisplayFile *df)
{
    displayFile = df;
}

void ObjParser::exportToObj(const std::string &path)
{
    std::ofstream file;
    file.open(path.c_str());
    if (file.is_open()) {
        for (unsigned int i=0; i < displayFile->objectsCount(); i++) {
            Object *obj = displayFile->getObjectAt(i);
            for (unsigned int j=0; j < obj->pointsCount(); j++) {
                file << obj->point(i)->toString();
            }
        }
    }
    file.close();
}

void ObjParser::importFromObj(const std::string &path)
{
    std::cout << "Parsing..." << std::endl;
    std::ifstream file(path);
    std::string line;
    if (file.is_open()) {
        while(file.good()) {
            getline(file, line);
            parseLine(line);
        }
    }
}

void ObjParser::parseLine(const std::string &line)
{
    std::regex rgxFaces("f( [1-9])*");
    std::smatch what;
   
    if (std::regex_match(line.begin(), line.end(), what, rgxFaces)) {
    }

    std::string name = extractName(line);
    Point point = extractVertices(line);

    std::cout << name << std::endl;
    std::cout << point.toString();
    
}

std::string ObjParser::extractName(const std::string &line)
{
    std::regex rgxName("o (.)* ");
    std::smatch what;
    std::string name;
    if (std::regex_match(line.begin(), line.end(), what, rgxName)) {
        name = what[0];
    }
    return name;
}

Point ObjParser::extractVertices(const std::string &line)
{
    std::regex rgxVertices("v [0-9]*.[0-9]* [0-9]*.[0-9]* [0-9]*.[0-9]*");
    std::regex rgxVector("[0-9]*.[0-9]*");
    std::string strTmp;
    std::cmatch what;
    double x = 0, y = 0, z = 0;
    if (std::regex_match(line.begin(), line.end(), what, rgxVertices)) {
        strTmp = what[0].str();
        std::cmatch tmp;
        if (std::regex_match(strTmp.begin(), strTmp.end(), tmp, rgxVector)) {
            x = stod(tmp[0]);
            y = stod(tmp[1]);
            z = stod(tmp[2]);
        }
    }

    return Point(x, y, z);
}

void ObjParser::checkFaces()
{

}
