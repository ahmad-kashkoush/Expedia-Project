#include "Menu.h"
class SystemRunner{
public:
    void Run(){
       int choice= Menu::createMenu({"Login", "SignUP"});
       cout<<choice;
    }
};