#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int varvis_int = 0;
int N;
int new_size = 0;
string path;
string str;
char WillContinue;

vector<string> varname;
vector<int> varsize;

void NewVar(int a)
{
    if (a == 1) {              //добавление переменной и её размера в выделенные векторы, переменная может быть со значением и без
        varname.push_back(str.substr(0, str.find("=")) + "|" + to_string(varvis_int));
        varsize.push_back(stoi(str.substr(str.find("(") + 1, str.find(")") - str.find("(") - 1)));
        new_size += stoi(str.substr(str.find("(") + 1, str.find(")") - str.find("(") - 1)); }
    else {
        cout << "\tНе удалось сохранить переменную  " + (str.substr(0, str.find("="))) << endl;
         }
}

void ShowVar()
{
    for (int i = 0; i < varsize.size(); i++)     //вывод видимых переменных из места вызова функции
    {
        if (varsize[i] == 0)
        {
            varsize[i] = 0;
        }
        else if (stoi(varname[i].substr(varname[i].find("|") + 1, str.find(" ") - str.find("|") - 1)) >= varvis_int)
        {
            cout << "\t" + varname[i].substr(0, varname[i].find("|")) << " = " << varsize[i] << endl;
        }
    }
}


int main()
{
    setlocale(LC_ALL, "ru"); 

    cout << "Вас приветствует курсовая работа №11" << endl;
    cout << "Федоренко Павла Андреевича группы МПМ - 121 \n" << endl;
    cout << "Данная программа предназначена для работы с динамической памятью с шаблонным на вход видом \n" << endl;  

    do
    {
        cout << "Введите полное название документа, который нужно обработать \n" << endl;
        cin >> path;

        ifstream file_in;
        file_in.open(path);

        cout << "Теперь введите количество задаваемой оперативной памяти N \n" << endl;

        cin >> N;

        if (!file_in.is_open())
        {
            cout << "Ошибка открытия файла!" << endl;
        }
        else
        {
            cout << endl << "Открытие файла..." << endl << endl;
            

            while (!file_in.eof())
            {

                file_in >> str;

                if (str == "{")
                {
                    varvis_int++;
                }

                else if (str == "}")
                {
                    varvis_int--;
                }

                else if (str == "ShowVar;")
                {                   
                    ShowVar();
                    cout << endl << "---------------------" << "\t\t\t busy memory: " << new_size << "\n" << endl;
                }

                else
                {
                    if (stoi(str.substr(str.find("(") + 1, str.find(")") - str.find("(") - 1)) + new_size <= N)
                    {
                        NewVar(1);
                    }
                    else if (!varname.empty())
                    {
                        for (int i = 0; !varname.empty() and stoi(str.substr(str.find("(") + 1, str.find(")") - str.find("(") - 1)) + new_size > N; i++)
                        {
                            i = 0;
                            cout << "\tУдаление переменной... " + varname[i].substr(0, varname[i].find("|")) <<"  Освобождено памяти " << varsize[i] << endl;
                            varname.erase(varname.begin());
                            new_size -= varsize[i];
                            varsize.erase(varsize.begin());
                        }
                        if (stoi(str.substr(str.find("(") + 1, str.find(")") - str.find("(") - 1)) + new_size <= N)
                        {
                            NewVar(1);
                        }
                        else
                        {
                            NewVar(0);
                        }
                    }
                    else
                    {
                        NewVar(0);
                    }
                }
            }
        }

        file_in.close();     

        cout << "Количество занимаемой в данной момент памяти   " << new_size << "/" << N << endl << endl;
        cout << "Если вы желаете перезапустить программу, введите в консоль символ \'y\'"<< endl;

        new_size = 0;
        varname.clear();
        varsize.clear();

        cin >> WillContinue;
    }
    while (WillContinue == 'y');
    
    return 0;
}