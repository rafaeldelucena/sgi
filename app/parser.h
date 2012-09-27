#ifndef SGI_PARSER_H_
#define SGI_PARSER_H_

#include <string>
#include "view/displayfile.h"
#include "app/formas.h"

class ObjParser
{
    public:
        ObjParser(DisplayFile *df);
        ~ObjParser();

        void exportToObj(const std::string &path);
        void importFromObj(const std::string &path);
    
    private:
        void checkFaces(void);
        void parseLine(const std::string &line);
        Point extractVertices(const std::string &line);
        std::string extractName(const std::string &line);
        
        DisplayFile *displayFile;
};


#endif /* SGI_PARSER_H_ */
