#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
const std::string cf = "config";
const std::string tf = "template.tex";
const std::string head = "head.tex";
const std::string tail = "\\end{document}";
const std::set<char> blank{' ', '\t', '\n', '\r'};
struct LineBreaker {
    std::string name, file, texfile, subsection;
    // the four array mean that:
    // 1: the name of the current Section.
    // 2: the cpp/java/etc file int the current Section.
    // 3: the tex file in the current Section.
    // 4: weather there exists a subsubsection.
    LineBreaker(const std::string &s) {
        auto it = s.begin();
        while (it != s.end() && *it != '<') it++;
        if (it != s.end()) it++;
        while (it != s.end() && *it != '>') name.push_back(*(it++));

        while (it != s.end() && *it != '<') it++;
        if (it != s.end()) it++;
        while (it != s.end() && *it != '>') file.push_back(*(it++));

        while (it != s.end() && *it != '<') it++;
        if (it != s.end()) it++;
        while (it != s.end() && *it != '>') texfile.push_back(*(it++));

        while (it != s.end() && *it != '<') it++;
        if (it != s.end()) it++;
        while (it != s.end() && *it != '>') subsection.push_back(*(it++));
    }
};

// Find how many Sections the main tex have.
std::vector<std::string> ReadConf(const std::string &filename) {
    std::ifstream in(filename);
    std::vector<std::string> v;
    std::string str;
    while (getline(in,str)) {
        bool flag = false;
        for (auto &u: str) if(!blank.count(u)) flag = true;
        if (flag) v.push_back(str);
    }
    in.close();
    return v;
}

// print the content int the file 'filename'.
void CopyFile(const std::string &filename, std::ofstream &out) {
    std::ifstream in(filename);
    std::string str;
    while (getline(in, str)) out << str << "\n";
    in.close();
}

// create the subsubsection
void SubSubsection(const LineBreaker &lb, const std::string &sec, std::ofstream &out){
    std::string subSubConf = sec + "/" + lb.name + "/" + cf;
    auto subs = ReadConf(subSubConf);
    for (auto &sub : subs) {
        LineBreaker subLb(sub);
        if (subLb.name.empty()) continue;
        std::cout << "\t\tsubsubsection " << subLb.name << "\n";
        out << "\\subsubsection{" << subLb.name << "}\n";
        std::string dir = sec + "/" + lb.name;
        if (subLb.texfile.size()) {
            out << "\\begin{spacing}{1.5}\n\\input{" << dir << "/" << subLb.texfile << "}\n\\end{spacing}\n";
        }
        if (subLb.file.size()) {
            out << "\\lstinputlisting{" << dir << "/" << subLb.file << "}\n";
        }
    }
}

int main() {
    std::ofstream tex(tf);
    CopyFile(head, tex);
    auto secs = ReadConf(cf);
    for (auto &sec: secs) {
        std::cout << "section: " << sec << "\n";
        tex << "\\section{" << sec << "}\n";
        std::string subConf = sec + "/" +  cf;
        auto subs = ReadConf(subConf);
        for (auto &sub : subs) {
            LineBreaker lb(sub);
            if (lb.name.empty()) continue;
            std::cout << "\tsubsection " << lb.name << "\n";
            tex << "\\subsection{" << lb.name << "}\n";
            if (lb.texfile.size()) {
                tex << "\\begin{spacing}{1.5}\n\\input{" << sec << "/" << lb.texfile << "}\n\\end{spacing}\n";
            }
            if (lb.subsection.size()) SubSubsection(lb, sec, tex);
            if (lb.file.size()) {
                std::string filePath = sec + "/" + lb.file;
                tex << "\\lstinputlisting{" << filePath << "}\n";
            }
        }
    }
    tex << "\n" << tail;
    tex.close();
    return 0;
}
