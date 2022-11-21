#include <iostream>
#include <fstream>
using namespace std;

int main()
{

    // ifstream code_input("peldaprogram.cpp");
    string code = "#include <iostream> \
\nusing namespace std;\
\n\
\nint main()\
\n{\
\n    freopen(\"bemenet.txt\", \"r\", stdin);\
\n    freopen(\"kimenet.txt\", \"w\", stdout);\
\n\
\n\
\n\
\n    return 0;\
\n}";
    // while (getline(code_input, code)) {
    //     string temp;
    //     cin >> temp;
    //     code += temp;
    // }
    
    freopen("input.txt", "r", stdin);
    string first_line = "// Széri József - sjim2307\n";
    string folder_name;
    getline(cin, folder_name);


    for (int i = 1; i <= 10; i++)
    {
        string file_name;
        getline(cin, file_name);

        string full_path = folder_name + "\\" + file_name + ".cpp";

        freopen(full_path.c_str(), "a", stdout);
        cout << first_line;
        cout << "//" + file_name << endl;
        cout << "/*\n*/" << endl;
        cout << endl;
        cout << code;
    }
}