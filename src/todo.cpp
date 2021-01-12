#include "todo.hpp"
using namespace std;
//**************************start_class_functions***********************************
vector<ToDo> vec;
ToDo::ToDo(std::string n, ui p, bool f, ui i) //A constructor that takes 3 parameters
    : task_name(n), priority(p), favorite(f), id(i)
{
}
ToDo::~ToDo() //destructur
{
}
void ToDo::get_info(int number) //Function for printing object information that takes 1 parameter
{
    char ch;
    if (favorite == 1)
        ch = 'y';
    else
        ch = 'n';
    cout << setw(number + 3) << left << task_name;
    cout << priority << setw(4) << right << ch << setw(7) << right << id << endl;
}
//**************************end_class_functions*************************************
void sub_command(const string &command, string &firstCommand, int &count) //Get a subset of a string
{
    while (command[count] != ' ' && command[count])
    {
        firstCommand += command[count];
        ++count;
    }
}
//-------------------------------------------------
void menu(const string &firstCommand, const string &secondCommand) //List to do the user's request
{
    if (firstCommand == ">add") //Add the correct object to the vector
    {
        try
        {
            add(); //calling function add
        }
        catch (out_of_range &e)
        {
            cout << e.what() << endl; //Catch out_of_range exception
        }
    }
    else if (firstCommand == ">delete") //Delete an object with a specified id from the vector
    {
        try
        {
            del(); //calling function del
        }
        catch (invalid_argument &e) //Catch invalid_argument exception
        {
            char ch;
            cout << e.what() << endl;
            cin.get(ch);
        }
        catch (out_of_range &e) //Catch out_of_range exception
        {
            cout << e.what() << endl;
        }
    }
    else if (firstCommand == ">complete") //Function for complete objects
    {
        try
        {
            complete(); //calling function del
        }
        catch (out_of_range &e) //Catch out_of_range exception
        {
            cout << e.what() << endl;
        }
        catch (...) //Catch any exception
        {
        }
    }
    else if (firstCommand == ">edit") //Function to edit objects
    {
        try
        {
            edit(secondCommand); //calling function edit
        }
        catch (out_of_range &e) //Catch out_of_range exception
        {
            cout << e.what() << endl;
        }
        catch (invalid_argument &e) //Catch invalid_argument exception
        {
            cout << e.what() << endl;
        }
    }
    else if (firstCommand == ">list-todo") //Function to display all of the object information
    {
        try
        {
            list_todo(); //calling function list_todo
        }
        catch (invalid_argument &e) //Catch invalid_argument exception
        {
            cout << e.what() << endl;
        }
    }
    else if (firstCommand == ">list-complete") //Function to display all of thecomlete object information
    {
        try
        {
            list_complete(); //calling function list_complete
        }
        catch (invalid_argument &e) //Catch invalid_argument exception
        {
            cout << e.what() << endl;
        }
    }
    else
    {
        throw invalid_argument(">>Your command is invalid please try again ");
    }
}
//--------------------------------------------------
void add()
{
    string n;
    bool f;
    ui p, i;
    char ch;
    cout << ">Tack Name : ";
    getline(cin, n);
    cout << ">Priority 1(most) to 5(least) : ";
    cin >> p;
    if (p >= 6 || p < 1)
    {
        cin.get(ch);
        throw out_of_range(">>Your priority number is out of range");
    }
    cout << ">Favorite (y/n) : ";
    cin >> ch;
    switch (ch)
    {
    case 'y':
    case 'Y':
        f = 1;
        break;
    case 'n':
    case 'N':
        f = 0;
        break;
    default:
        cin.get(ch);
        throw out_of_range(">>You entered an inappropriate character for favorite");
    }
    while (true)
    {
        int flag = 0;
        srand(static_cast<unsigned int>(time(0))); //Choose a random number between 1000 and 10000
        i = rand() % 9000 + 1000;
        for (size_t i = 0; i < vec.size(); i++)
        {
            if (i == vec[i].id)
            {
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
    ToDo todo(n, p, f, i); //Make new object from ToDo calss
    vec.push_back(todo);   //Add the object to the end of the vector
    if (vec.back().favorite == 1)
        ch = 'y';
    else
        ch = 'n';
    cout << ">Your task has been successfully added to the list.\nTask Information :\n";
    cout << vec.back().task_name
         << " | priority(" << vec.back().priority
         << ") | favorite(" << ch
         << ") | ID:" << vec.back().id << endl;
    cin.get(ch);
}
//--------------------------------------------------
void list_todo()
{
    if (vec.size() == 0)
        throw invalid_argument(">>The vector is empty and it is not possible to display data");
    int number = vec.front().task_name.size();
    for (size_t i = 1; i < vec.size(); i++) //Get the maximum length of vector strings or cells
    {
        if (number < vec[i].task_name.size())
            number = vec[i].task_name.size();
    }
    cout << setfill(' ') << setw(number + 3) << left << "Task"
         << "P" << setw(4) << right << "F" << setw(5) << "ID" << endl;
    for (size_t i = 1; i <= (number + 15); i++)
    {
        cout << "_";
    }
    cout << endl;
    for (size_t i = 1; i <= 5; i++) //To print in order of priority
    {
        for (size_t j = 0; j < vec.size(); j++)
        {
            if (vec[j].priority == i && vec[j].favorite == 1)
            {
                vec[j].get_info(number);
            }
        }
        for (size_t j = 0; j < vec.size(); j++)
        {
            if (vec[j].priority == i && vec[j].favorite == 0)
            {
                vec[j].get_info(number);
            }
        }
    }
}
//--------------------------------------------------
void complete()
{
    ui i;
    cout << ">Enter Task ID : ";
    cin >> i;
    int j = 0, flag = 0;
    for (j = 0; j < vec.size(); j++)
    {
        if (i == vec[j].id)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        char ch;
        cout << ">Found!" << vec[j].task_name << "." << endl;
        cout << "complete (y/n) : ";
        cin.get(ch);
        cin.get(ch);
        switch (ch)
        {
        case 'y':
        case 'Y':
            vec[j].completed = 1;
            cout << ">Task \"" << vec[j].task_name << "\",completed." << endl;
            break;
        case 'n':
        case 'N':
            break;
        default:
            cin.get(ch);
            throw out_of_range(">>You entered an inappropriate character for favorite");
        }
        cin.get(ch);
    }
    else
    {
        char ch;
        cout << ">Not Found this ID" << endl;
        cin.get(ch);
        throw invalid_argument("");
    }
}
//--------------------------------------------------
void list_complete()
{
    if (vec.size() == 0)
        throw invalid_argument(">>The vector is empty and it is not possible to display data");
    int flag = 0;
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec[i].completed == 1)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        throw invalid_argument(">>None of the notes are complete");
    int number = vec.front().task_name.size();
    for (size_t i = 1; i < vec.size(); i++) //Get the maximum length of vector strings or cells
    {
        if (number < vec[i].task_name.size())
            number = vec[i].task_name.size();
    }

    cout << setfill(' ') << setw(number + 3) << left << "Task"
         << "ID" << endl;
    for (size_t i = 1; i <= (number + 15); i++)
    {
        cout << "_";
    }
    cout << endl;
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec[i].completed == 1)
        {
            cout << setw(number + 3) << left << vec[i].task_name << vec[i].id << endl;
        }
    }
}
//--------------------------------------------
void edit(const std::string &secondCommand)
{
    char ch;
    if (vec.size() == 0)
        throw invalid_argument(">>The vector is empty and it is not possible to display data");
    string str = "";
    string num = "";
    getline(cin, str);
    ui number = 0;
    int flag = 0;
    stringstream geek(secondCommand);
    geek >> number;
    int i = 0;
    for (i = 0; i < vec.size(); i++)
    {
        if (vec[i].id == number)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        throw invalid_argument(">>There is no note with this id");
    int c = 0;
    while (c != (str.size()))
    {
        while (str[c] == ' ')
        {
            ++c;
        }
        num = "";
        string s1 = "";
        s1 += str[c];
        ++c;
        while (str[c] != '-' && (c < str.size()))
        {
            s1 += str[c];
            ++c;
        }
        if (s1.substr(0, 2) == "-p")
        {
            ui number1 = 0;
            int cs = 2;
            while (s1[cs] == ' ')
            {
                ++cs;
            }
            num = "";
            while (s1[cs] >= '0' && s1[cs] <= '9')
            {
                num += s1[cs];
                ++cs;
            }
            stringstream geek(num);
            geek >> number1;
            if (number1 >= 6 || number1 <= 0)
            {
                throw out_of_range(">>Your priority number is out of range");
            }
            vec[i].priority = number1;
        }
        else if (s1.substr(0, 2) == "-n")
        {
            int cs = 2;
            while (s1[cs] == ' ')
            {
                ++cs;
            }
            vec[i].task_name = s1.substr(cs);
        }
        else if (s1.substr(0, 2) == "-f")
        {
            int cs = 2;
            while (s1[cs] == ' ')
            {
                ++cs;
            }
            ch = s1[cs];
            char c;
            switch (ch)
            {
            case 'y':
            case 'Y':
                vec[i].favorite = 1;
                break;
            case 'n':
            case 'N':
                vec[i].favorite = 0;
                break;
            default:
                cin.get(c);
                throw out_of_range(">>You entered an inappropriate character for favorite");
            }
        }
        else
            throw invalid_argument(">>Your request to edit is not valid");
    }
}
//---------------------------------------------------
void del()
{
    if (vec.size() == 0)
        throw invalid_argument(">>The vector is empty and it is not possible to display data");
    ui i, flag = 0, j;
    cout << ">Enter Task ID : ";
    cin >> i;
    for (j = 0; j < vec.size(); j++)
    {
        if (vec[j].id == i)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        throw invalid_argument(">Not Found this ID");
    char ch;
    cout << ">Found! " << vec[j].task_name << endl;
    cout << "delete (y/n) : ";
    cin >> ch;
    string s;
    switch (ch)
    {
    case 'y':
    case 'Y':
        s = vec[j].task_name;
        vec.erase(vec.begin() + j);
        cout << ">Task \"" << s << "\",deleted." << endl;
        break;
    case 'n':
    case 'N':
        break;
    default:
        cin.get(ch);
        throw out_of_range(">>You entered an inappropriate character for favorite");
        break;
    }
    cin.get(ch);
}
