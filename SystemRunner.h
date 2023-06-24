#ifndef EXPEDIA_PROJECT_EXPEDIA_H
#include "User.h"
#include "Utilities.h"
#define EXPEDIA_PROJECT_EXPEDIA_H

class Expedia{
    UserManager mgr;
public:
    void Run() {
        IRegister();

        int choice = ExpediaUtilities::createMenu({
                                              "View Profile", "Make Itenerary",
                                              "List My Itenerary", "Logout"});
//        if(choice==1)usr.ViewProfile();
//        else if(choice==2)usr.MakeItenerary();
//        else if(choice==3)usr.listIten();
//        else if(choice==4)IRegister();
    }
    void IRegister(){
        int choice= ExpediaUtilities::createMenu({"Login", "SignUP"});
        if(choice==1)mgr.Login();
        else         mgr.SignUP();
        cout<<"Hello "<<mgr.GetCur().getName()<<"| "<<"User View\n";

    }
};
#endif
