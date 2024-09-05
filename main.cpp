#include "Terminal.h"
#include "UI.h"
#include <string>

int main(){
    std::string command ;
    bool isActive = true;
    Terminal* terminal = Terminal::getInstance();
    AccountData myAccount = AccountData(
            1000000.0,
            0.0,
            0.0,
            0.0,
            0.0
    );
    /*
    terminal->PrintCurrencyRate();
    terminal->PrintPersonalAccount(myAccount);
    terminal->PrintTerminalAccount();
    terminal->UpdateCurrencyDate();
    terminal->PrintCurrencyRate();
    int code1 = terminal->Exchange(myAccount,"RUB","USD",50000);
    terminal->PrintCurrencyRate();
    terminal->PrintPersonalAccount(myAccount);
    //terminal->PrintTerminalAccount();
    int code2 = terminal->Exchange(myAccount,"USD","RUB",200);
    terminal->PrintCurrencyRate();
    terminal->PrintPersonalAccount(myAccount);
    //terminal->PrintTerminalAccount();
    std::cout<<code1<<std::endl;
    std::cout<<code2<<std::endl;
    */
    PrintMain();
    Delimeter(50,'=');
    while(isActive){
        Delimeter(30,'-');
        terminal->PrintCurrencyRate();
        Delimeter(30,'-');
        terminal->PrintPersonalAccount(myAccount);
        Delimeter(30,'-');
        terminal->PrintTerminalAccount();
        Delimeter(30,'-');
        PrintExchange(terminal,myAccount);
        std::cout<<"Желаете продолжить? yes/no"<<std::endl;
        SafeCin(command,"");
        while(command!="yes"&&command!="no"){
            std::cout<<"Некорректная команда"<<std::endl;
            SafeCin(command,"");
        }
        if(command=="no") isActive = false;
    }
    Delimeter(50,'=');
    
}