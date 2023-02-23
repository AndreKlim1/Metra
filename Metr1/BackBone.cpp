#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

std::map<std::string, size_t> operators = {{"puts", 0}, {"[", 0}, {"]", 0}, {".", 0}, {" ", 0}, {"\n", 0}, 
                                           {"\"", 0}, {"+", 0}, {"-", 0}, {"*", 0}, {"=", 0}, {"/", 0}, {",", 0}, 
                                           {"(", 0}, {")", 0}, {"for", 0}, {"loop", 0}, {"while", 0}, {"do", 0}, 
                                           {"else", 0}, {"elsif", 0}, {"==", 0}, {">", 0}, {"<", 0}, {">=", 0}, {"<=", 0}, {"end", 0}, 
                                           {"begin", 0},{"case", 0}, {"when", 0}, {"gets", 0}, {"!", 0}, {"swapped", 0}, 
                                           {"break", 0}, {"def", 0}, {"if", 0}, {"..", 0}, {"break", 0}, {"gets", 0}};
std::map<std::string, size_t> operands;

const std::string ignore = "do \n else elsif when in";


void GetInfo(std::string code)
{
    std::string prevToken = "", currToken = "";
    
    auto mapEnd = operators.end(); // Для проверки на присутствие в списке операторов
    bool dot = false;
    for(auto symbol : code) 
    {
        //std::cout << currToken << " " << prevToken << "\n"; 
        prevToken = currToken;
        currToken.push_back(symbol);

        if(operators.find(currToken) != mapEnd)
        {
           continue;
        }
        else if(operators.find(prevToken) != mapEnd)
        {
            if(prevToken == ".") dot = true;
            operators[prevToken]++;
            currToken = symbol;
            if(prevToken != ".") dot = false; 
        }
        else if (operators.find(std::string(1, symbol)) != mapEnd)
        {
            if(dot || symbol == '(')
                operators[prevToken]++;
            else
                operands[prevToken]++;
            currToken = symbol;
            dot = false;
        }

    } 
    std::map<std::string, size_t>::iterator  iter;  
    if((iter = operators.find(currToken)) != mapEnd)
        (*iter).second++;
    else if(dot)
            operators[currToken]++;
        else
            operands[currToken]++;
    dot = false;
    currToken.clear();

    std::cout << "Operators:\n";
    auto end = operators.end();
    for(auto beg = operators.begin(); beg != end;)
    {
        if((beg->second == 0) || (beg->first != "if" && ignore.find(beg->first) != std::string::npos))
        {
            beg = operators.erase(beg);
            continue;
        }
        std::cout << beg->first << ": " << beg->second << '\n';
        beg++;
    }
    std::cout << std::endl;

    operands.erase("in");
    std::cout << "Operands:\n";
    for(auto elem : operands)
    {
        std::cout << elem.first << ": " << elem.second << '\n';
    }



    return;
}

