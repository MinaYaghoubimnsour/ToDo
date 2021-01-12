#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>   //time()
#include <iomanip> //setw()-setfill()
#include <vector>
#include <climits> //rand()-srand()
#include <sstream> //Convert string to int/unsigned int
#ifndef TODO_HPP
#define TODO_HPP
typedef unsigned int ui; //using typedef for unsigned it
void del();
void add();
void complete();
void list_todo();
void list_complete();
void edit(const std::string &);
void menu(const std::string &, const std::string &);         //List to do the user's request
void sub_command(const std::string &, std::string &, int &); //Get a subset of a string
class ToDo                                                   //This class is for storing our notes
{
    //friends ->
    friend void del();
    friend void add();
    friend void list_todo();
    friend void complete();
    friend void list_complete();
    friend void edit(const std::string &);
    friend void edit(const std::string &secondCommand);

private:
    std::string task_name;
    ui priority;
    ui id;
    bool favorite;
    bool completed = 0;

public:
    ToDo(std::string, ui, bool, ui); //A constructor that takes 3 parameters
    void get_info(int);              //Print the information of each note->name-favorite-priority-id
    void set_complete();
    ~ToDo(); //A destructor
};
#endif