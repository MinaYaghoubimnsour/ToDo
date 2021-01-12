#include "todo.hpp"
using namespace std;
int main()
{
    while (true)
    {
        int count = 0;
        string command = "", firstCommand = "", secondCommand = "";

        cout << "----------------------------" << endl;
        cout << "Please enter your request : " << endl;
        getline(cin, command);                     //Get the strng
        sub_command(command, firstCommand, count); //Calling function sub_command
        try
        {
            ++count;
            secondCommand = command.substr(count);
        }
        catch (...) //Catch any exception
        {
        }
        if (firstCommand == ">exit") //exit the program
            break;
        try
        {
            menu(firstCommand, secondCommand); //Calling function menu
        }
        catch (invalid_argument &e) //Catch invalid_argument exception
        {
            cout << e.what() << endl; //Print cintent exception
        }
    }
    return 0; //End of my program
}