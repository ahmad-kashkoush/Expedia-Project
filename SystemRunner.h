#include "Menu.h"
#include "User.h"
class SystemRunner{
    User usr;
public:
    void Run() {
        IRegister();

        int choice = Menu::createMenu({
                                              "View Profile", "Make Itenerary",
                                              "List My Itenerary", "Logout"});
        if(choice==1)usr.ViewProfile();
        else if(choice==2)usr.MakeItenerary();
        else if(choice==3)usr.listIten();
        else if(choice==4)IRegister();
    }
    void IRegister(){
        int choice= Menu::createMenu({"Login", "SignUP"});
        if(choice==1)Login();
        else         SignUP();
        cout<<"Hello "<<usr.getName()<<"| "<<"User View\n";

    }
    void Login(){
        cout<<"Enter User name and Password\n";
        string Name, Password;
        cin>>Name>>Password;
        usr= User(Name, Password);
    }
    void SignUP(){

    }

};