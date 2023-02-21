#include <iostream>
#include <vector>
#include <string>
#include <map>

std::map<std::string, size_t> operators = {{"puts", 0}, {"[", 0}, {"]", 0}, {".", 0}, {" ", 0}, {"\n", 0}, 
                                           {"\"", 0}, {"+", 0}, {"-", 0}, {"*", 0}, {"/", 0}, {",", 0}, 
                                           {"(", 0}, {")", 0}, {"for", 0}, {"loop", 0}, {"while", 0}, {"do", 0}, {"end", 0}, {"in", 0}};
std::map<std::string, size_t> operands;


void GetInfo(std::string code)
{
    std::string prevToken = "", currToken = "";

    auto mapEnd = operators.end();
    for(auto symbol : code)
    {
        std::map<std::string, size_t>::iterator  iter; 
        if((iter = operators.find(std::string(1, symbol))) != mapEnd)
        {
            (*iter).second++;

            if(symbol == '=')

 
            if(prevToken == ".")
                operators[currToken]++;
            else
                operands[currToken]++;
            currToken.clear();
            prevToken = (*iter).first;
            continue;
        }

        currToken.push_back(symbol);
        if((iter = operators.find(currToken)) != mapEnd)
        {
            (*iter).second++;
            currToken.clear();
        }
    } 
    std::map<std::string, size_t>::iterator  iter;  
    if((iter = operators.find(currToken)) != mapEnd)
    {
        (*iter).second++;
        currToken.clear();
    } 
    else
    {
        if(prevToken == ".")
            operators[currToken]++;
        else
            operands[currToken]++;
        currToken.clear();
    }

    std::cout << "Operators:\n";
    for(auto elem : operators)
    {
        std::cout << elem.first << ": " << elem.second << '\n';
    }
    std::cout << std::endl;

    std::cout << "Operands:\n";
    for(auto elem : operands)
    {
        std::cout << elem.first << ": " << elem.second << '\n';
    }



    return;
}