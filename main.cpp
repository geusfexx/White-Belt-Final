#include <iostream>
#include <sstream>
#include <map>
#include <exception>

using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

void error(const string & s)
{
    throw runtime_error(s);
}

void errDateFormat(string c)
{
    stringstream ss;
    ss << "Wrong date format: " << c;
    throw runtime_error(ss.str());
}

class Date {
public:
    Date(int new_year, int new_month, int new_day)
    {
        if ((new_month <1)||(new_month > 12))
        {
            error("Month value is invalid: " + to_string(new_month));
        }
        else this->Month = new_month;

        if ((new_day < 1)||(new_day > 31))
        {
            error("Day value is invalid: " + to_string(new_day));
        }
        else this->Day = new_day;

        this->Year = new_year;
    }

    Date(string text)
    {
        stringstream ss_in(text);
        int new_day(0), new_month(0), new_year(0);
        char separator1, separator2;
        string end = "";

        if ((ss_in >> new_year >> separator1 >> new_month >> separator2 >> new_day)&&(ss_in.eof()))
        {
            Date(new_year, new_month, new_day);
        }
        else
        {
            errDateFormat(ss_in.str());
        }

    }

  int GetYear() const;
  int GetMonth() const;
  int GetDay() const;

private:
  int Day;
  int Month;
  int Year;
};

bool operator<(const Date& lhs, const Date& rhs);



class Database {
public:
  void AddEvent(const Date& date, const string& event);
  bool DeleteEvent(const Date& date, const string& event);
  int  DeleteDate(const Date& date);

  /* ??? */void Find(const Date& date) const;

  void Print() const;

private:
    map <Date, string> data;

};

int main() {
  Database db;

  string command;
  while (getline(cin, command))
  {
      stringstream ss_in(command);
      string operation{};
      ss_in >> operation;
      if (operation == "Add")
      {
          string data{}, event{};//Journey across the universe
          ss_in >> data;
          ss_in.ignore(1);
          getline(ss_in, event);
          try {

          } catch (const runtime_error& e) {
              cout << e.what() << endl;
              return 2;
          }

          //db.AddEvent()

      }

      else if (operation == "Del")
      {

      }

      else if (operation == "Find")
      {

      }

      else if (operation == "Print")
      {

      }

    // Считайте команды с потока ввода и обработайте каждую
  }

  return 0;
}
