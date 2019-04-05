#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <exception>
#include <set>
#include <iomanip>

using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

void error(const string & s)
{
    throw invalid_argument(s);
}

void errDateFormat(string c)
{
    stringstream ss;
    ss << "Wrong date format: " << c;
    throw runtime_error(ss.str());
}

class Date {
public:
    /*Date(int new_year, int new_month, int new_day)
    {
        //вызов конструктора из конструктора одного и того же объекта дает неопределенное поведение
        //в данном случае мы получали дату 0-0-0
    }
    */
    explicit Date(string text)
    {
        stringstream ss_in(text);
        int new_day(0), new_month(0), new_year(0);
        char separator1, separator2;
        if ((ss_in >> new_year >> separator1 >> new_month >> separator2 >> new_day)&&(ss_in.eof())&&(separator1 == '-')&&(separator2 == '-'))
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
        else
        {
            errDateFormat(ss_in.str());
        }

    }

    string Print() const
    {
        //string result("");
        stringstream ss;
        ss << fixed << setfill('0')
           << setw(4) << this->GetYear() << "-"
           << setw(2) << this->GetMonth() << "-"
           << setw(2) << this->GetDay();
        return ss.str();
    }

  int GetYear() const
  {
      return this->Year;
  }
  int GetMonth() const
  {
      return this->Month;
  }
  int GetDay() const
  {
      return this->Day;
  }

private:
  int Day;
  int Month;
  int Year;
};

bool operator<(const Date& lhs, const Date& rhs)
{
    if (lhs.GetYear() == rhs.GetYear())
    {
        if (lhs.GetMonth() == rhs.GetMonth())
        {
            return (lhs.GetDay() < rhs.GetDay());
        }
        else return (lhs.GetMonth() < rhs.GetMonth());
    }
    else
    {
        return (lhs.GetYear() < rhs.GetYear());
    }
}



class Database {
public:

  void AddEvent(const Date& date, const string& event)
  {
      data[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event)
  {
      if ((!data.empty())&&(data.find(date) != data.end())) //устраняем выход за границы
      {
          auto map = data.find(date);
          for (auto & i : map->second)
          {
              if (i == event)
              {
                  data.find(date)->second.erase(event);
                  return true;
              }
          }
      }

      return false;
  }

  size_t DeleteDate(const Date& date)
  {
      size_t n(0);
      if ((!data.empty())&&(data.find(date) != data.end())) //устраняем выход за границы
      {
          n = data.at(date).size();
          this->data.erase(date);
      }
      return n;
  }

  /* */vector <string> Find(const Date& date) const
  {
      vector <string> result = {};
      if ((!data.empty())&&(data.find(date) != data.end())) //устраняем выход за границы
      {

          for (auto i : this->data.find(date)->second)
          {
              result.push_back(i);
          }
      }
      return result;
  }

  void Print() const
  {
      if (!data.empty())
      {
          for (auto i : data)
          {
              //cout << i.first.Print() << endl;
              for (auto s : i.second)
              {
                  cout << i.first.Print() << " " << s << endl;
              }
          }
      }
  }

private:
    map <Date, set <string>> data;

};

void PrintVector(const vector <string> & v)
{
    for (auto i : v)
    {
        cout << i << endl;
    }
}

int main() {

      Database db;
      string command;
      while (getline(cin, command))
      {
          try
          {

              stringstream ss_in(command);
              string operation("");
              ss_in >> operation;
              ss_in.ignore(1);
              if (operation == "Add")
              {
                      string date{}, event{};
                      ss_in >> date;
                      ss_in.ignore(1);
                      getline(ss_in, event);
                      db.AddEvent(Date(date), event);
              }

              else if (operation == "Del")
              {
                      string date{}, event{};
                      ss_in >> date;
                      ss_in.ignore(1);
                      if (getline(ss_in, event))
                      {
                          if (db.DeleteEvent(Date(date), event))
                          {
                              cout << "Deleted successfully" << endl;
                          }
                          else
                          {
                              cout << "Event not found" << endl;
                          }
                      }
                      else
                      {
                          cout << "Deleted " << db.DeleteDate(Date(date)) << " events" << endl;
                      }
              }

              else if (operation == "Find")
              {
                      string date{};
                      ss_in >> date;
                      PrintVector(db.Find(Date(date)));
              }

              else if (operation == "Print")
              {
                  db.Print();
              }
              else
              {
                  if (command != "")     {cout << "Unknown command: " << command;}
              }
          }
          catch (const runtime_error& e)
          {
              cout << e.what() << endl;
          }
          catch (const invalid_argument & ia)
          {
              cout << ia.what() << endl;
          }
          catch (...){}

        // Считайте команды с потока ввода и обработайте каждую
      }


  return 0;
}
