#include "Admin.h"

Admin::Admin(string uName, string pass) : username(uName), password(pass){}

bool Admin::checkUser(string inputUser, string inputPass) const{
    if(inputUser == username && inputPass == password) { return true; }
    else{ return false; }
}