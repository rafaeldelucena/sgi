#include <iostream>
#include <fstream>
#include <sstream>
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
    std::vector<std::string> objs;
    std::string coords;
    if (file.is_open()) {
        file << "mtllib " << path << ".mtl" << std::endl;
        unsigned int totalPoints = 0;
        for (unsigned int i=0; i < displayFile->objectsCount(); i++) {
            std::stringstream s;
            Object *obj = displayFile->getObjectAt(i);
            for (unsigned int j=0; j < obj->pointsCount(); j++) {
                file << obj->point(i).toObj();
                totalPoints++;
                s << totalPoints << " ";
            }
            if (obj->type() == POINT) {
                coords = "p " + s.str(); 
            } else {
                coords = "l " + s.str();
            }
            objs.push_back(coords);
        }
        for (unsigned int k=0; k < objs.size(); k++) {
            Object *obj = displayFile->getObjectAt(k);
            file << "o " << "Object" << k+1 << std::endl;
            file << objs[k] << std::endl;
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
            std::cout << line << "<-- THE  LINE" << std::endl;
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
    std::regex rgxName("^o [:w:]*");
    std::smatch results;
    std::string name;
    if (std::regex_match(line, results, rgxName)) {
        std::cout << "str match! <<" << std::endl;
        name = results[0].str();
        return name;
    }
}

Point Parser::extractVertices(const std::string &line)
{
    std::regex rgxVertices("^v [0-9]*");
    std::regex rgxVector("[0-9]*.[0-9]*");
    std::smatch results;
    double x = 0, y = 0, z = 0;
    if (std::regex_match(line, results, rgxVertices)) {
        std::string strTmp = results[0].str();
        std::cout << strTmp << std::endl;
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
