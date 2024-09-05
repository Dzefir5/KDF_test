#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include "Terminal.h"

template<typename T>
void SafeCin(T& input,std::string ErrorMessage){
    while ( !(std::cin >> input)) {
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout << ErrorMessage<<std::endl;;
    }
}

void Delimeter(int count , char symbol){
    std::cout<<std::endl;
    for(int i=0;i<count;i++){
        std::cout<<symbol;
    }
    std::cout<<std::endl;
}
void Delimeter(int count , std::string string){
    std::cout<<std::endl;
    for(int i=0;i<string.length()/count;i++){
        std::cout<<string;
    }
}

void PrintMain(){
    std::cout<<std::setw(100)<<std::internal<<"Терминал обмена валютных пар"<<std::endl;
}

void PrintExchange(Terminal* terminal,AccountData& account){
    bool state = true;
    std::string first ;
    std::string second ;
    double amount;
    while(state){
        std::cout<<"Введите название валюты для обмена"<<std::endl;
        SafeCin(first,"");
        SafeCin(second,"");
        std::string command;
        std::cout<<std::internal<<"Введите количество валюты "<<first<<" для обмена "<<std::endl;
        SafeCin(amount,"");  
        AccountData buf = account;
        int code  = terminal->Exchange(buf,first,second,amount);
        switch (code)
        {
            case 0 :
                if(second!="BTC"){
                    std::cout<<"в результате обмена будет получено +"<<std::setprecision(2)<<buf.getCurrency(second)->count-account.getCurrency(second)->count<<" Валюты "<<second<<std::endl;
                }else{
                    std::cout<<"в результате обмена будет получено +"<<std::setprecision(7)<<buf.getCurrency(second)->count-account.getCurrency(second)->count<<" Валюты "<<second<<std::endl;
                }
                
                std::cout<<"Желаете продолжить? yes/no"<<std::endl;
                SafeCin(command,"");
                while(command!="yes"&&command!="no"){
                    std::cout<<"Некорректная команда"<<std::endl;
                    SafeCin(command,"");
                }
                if(command=="yes"){
                    state = false;
                    Delimeter(30,'-');
                } 
                state = false;
                break;
            case 1 :
                std::cout<<"Некорректные данные для обмена"<<std::endl;
                break;
            case 2 :
                std::cout<<"Недостаток средств на личном счёте"<<std::endl;
                break;
            case 3 :
                std::cout<<"Недостаток средств на счёте терминала"<<std::endl;
                break;
        }
    }
    
    terminal->Exchange(account,first,second,amount);
    std::cout<<"Операция выполнена успешно"<<std::endl;
    Delimeter(30,'+');
    terminal->PrintPersonalAccount(account);
    terminal->UpdateCurrencyDate();
    Delimeter(30,'+');
}
