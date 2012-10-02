#include <iostream>
#include <fstream>
#include <regex>
#include "app/parser.h"

Parser::Parser(DisplayFile *df)
{
    displayFile = df;
}

void Parser::exportToObj(const std::string &path)
{
    std::ofstream file;
    file.open(path.c_str());
    if (file.is_open()) {
        for (unsigned int i=0; i < displayFile->objectsSize(); i++) {
            Object *obj = displayFile->getObjectAt(i);
            for (unsigned int j=0; j < obj->pointsCount(); j++) {
                file << obj->point(i)->toObj();
            }
        }
    }
    file.close();
}

void Parser::importFromObj(const std::string &path)
{
    std::cout << "Parsing..." << std::endl;
    std::ifstream file(path);
    std::string line;
    if (file.is_open()) {
        while(file.good()) {
            std::cout << "lendo o arquivo...." << std::endl;
            getline(file, line);
            std::cout << "get file!" << std::endl;
            parseLine(line);
        }
    }
}

void Parser::parseLine(const std::string &line)
{
    std::regex rgxFaces("f( [1-9])*");
    std::smatch what;
   
    if (std::regex_match(line, what, rgxFaces)) {
    }

    std::string name = extractName(line);
    Point point = extractVertices(line);

    std::cout << name << std::endl;
    std::cout << point.toString();
    
}

std::string Parser::extractName(const std::string &line)
{
    std::regex rgxName("o (.)* ");
    std::smatch what;
    std::string name;
    if (std::regex_match(line, what, rgxName)) {
        std::cout << "str match! <<" << std::endl;
        name = what[0].str();
        return name;
    }
}

Point Parser::extractVertices(const std::string &line)
{
    std::regex rgxVertices("v [0-9]*.[0-9]* [0-9]*.[0-9]* [0-9]*.[0-9]*");
    std::regex rgxVector("[0-9]*.[0-9]*");
    std::smatch what;
    double x = 0, y = 0, z = 0;
    if (std::regex_match(line, what, rgxVertices)) {
        std::string strTmp = what[0].str();
        std::smatch tmp;
        if (std::regex_match(strTmp, tmp, rgxVector)) {
            x = stod(tmp[0]);
            y = stod(tmp[1]);
            z = stod(tmp[2]);
            return Point(x, y, z);
        }
    }
}

void Parser::checkFaces()
{

}
