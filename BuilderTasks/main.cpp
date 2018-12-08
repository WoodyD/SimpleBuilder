#include <string>
#include <ostream>
#include <vector>
#include <iostream>

//all fields private, even constructors.
class Code{
    friend class CodeBuilder;
    std::string name, type;
    std::vector<Code> elements;
    
    Code() {}
    Code(std::string name, std::string type) : name(name), type(type) {}
    
};


class CodeBuilder
{
    Code code;
    
public:
    CodeBuilder(const std::string& class_name)
    {
    code.name = class_name;
    }
    
    //for fluent interface
    CodeBuilder& add_field(const std::string& name, const std::string& type)
    {
        Code c{name, type};
        code.elements.push_back(c);
        //code.elements.emplace_back(c);
        return *this;
    }
    
    //override << operator
    friend std::ostream& operator <<(std::ostream& os, const CodeBuilder& obj)
    {
        os << "class " << obj.code.name << "\n{" << std::endl;
        
        for(auto el : obj.code.elements)
            os << "  " << el.type << " " << el.name << ";" << std::endl;
        
        os << "};" << std::endl;
        
        return os;
    }
};

int main(int argc, const char * argv[]) {
    //fluent interface
    auto cb = CodeBuilder("Person").add_field("name", "string").add_field("age", "int");
    
    std::cout << cb;
    
    return 0;
}
