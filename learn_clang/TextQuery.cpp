#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>

class TextQuery
{
public:
    typedef std::vector<std::string>::size_type line_no;
public:
    void readFile(std::ifstream& is);
    std::set<line_no> runQuery(std::string word) const;
    std::string getLine(line_no i) const;
private:
    void storeFile(std::ifstream& is);
    void buildTable();
private:
    std::vector<std::string> allLines;
    std::map<std::string, std::set<line_no> > table;
};

void TextQuery::readFile(std::ifstream& fin)
{
    storeFile(fin);
    buildTable();
}

void TextQuery::storeFile(std::ifstream& fin)
{
    std::string line;
    while (std::getline(fin, line))
    {
        allLines.push_back(line);
    }
}

void TextQuery::buildTable()
{
    for (line_no i = 0; i < allLines.size(); ++i)
    {
        std::istringstream iss(allLines[i]);
        std::string word;
        while (iss >> word)
        {
            table[word].insert(i);
        }
    }
}

std::set<TextQuery::line_no> TextQuery::runQuery(std::string word) const
{
    std::map<std::string, std::set<TextQuery::line_no> >::const_iterator it = table.find(word);
    if (it == table.end())
    {
        return std::set<line_no>();
    }
    else
    {
        return it->second;
    }
}

std::string TextQuery::getLine(line_no line) const
{
    if (line < allLines.size())
    {
        return allLines[line];
    }
    throw std::out_of_range("line number out of range");
}



void printResults(const std::set<TextQuery::line_no>& locs, const std::string& word, const TextQuery& tq)
{
    typedef std::set<TextQuery::line_no> lineNums;
    lineNums::size_type sz = locs.size();
    std::cout << word << " ocuurs " << sz << " times" << std::endl;

    lineNums::iterator it;
    for (it = locs.begin(); it != locs.end(); ++it)
    {
        std::cout << "\t" << "line (" << (*it) + 1 << ") " << tq.getLine(*it) << std::endl;
    }
}

std::ifstream& open_file(std::ifstream& fin, const std::string& filename)
{
    fin.close();
    fin.clear();
    fin.open(filename.c_str());
    return fin;
}

int main(int argc, char* argv[])
{
    std::ifstream fin;
    if (argc < 2 || !open_file(fin, argv[1]))
    {
        std::cerr << "NO Input File !!!" << std::endl;
        return EXIT_FAILURE;
    }

    TextQuery tq;
    tq.readFile(fin);
    while (true)
    {
        std::cout << "Enter the word to look for, or q to quit: ";
        std::string s;
        std::cin >> s;

        if (!std::cin || s == "q") break;
        std::set<TextQuery::line_no> locs = tq.runQuery(s);
        printResults(locs, s, tq);
    }
    return 0;
}
