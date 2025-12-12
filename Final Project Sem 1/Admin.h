#ifndef ADMIN_H
#define ADMIN_H

#include <string>
using namespace std;

class Admin{
private:
    string username;
    string password;

public:
    Admin(string uName = "admin", string pass = "admin");
    bool checkUser(string inputUser, string inputPass) const;

};

#endif