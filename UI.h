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
    for(int i=0;i<count;i++){
        std::cout<<symbol;
    }
    std::cout<<std::endl;
}
void Delimeter(int count , std::string string){
    for(int i=0;i<string.length()/count;i++){
        std::cout<<string;
    }
}

void PrintMain(){
    std::cout<<std::setw(80)<<std::internal<<"Терминал обмена валютных пар"<<std::endl;
}

void PrintExchange(Terminal* terminal,AccountData& account){
    bool state = true;
    std::string first ;
    std::string second ;
    double amount;
    AccountData buf = account;
    while(state){
        do
        {
            if(terminal->Exchange(buf,first,second,0.0!=0)){
                std::cout<<"Некорректное наименование валют "<<std::endl;
            }
            std::cout<<"Введите название валюты для обмена"<<std::endl;
            std::cout<<"\t-> ";
            SafeCin(first,"");
            std::cout<<"\t-> ";
            SafeCin(second,"");
        }    
        while(terminal->Exchange(buf,first,second,0.0)!=0);
        std::string command;
        std::cout<<std::internal<<"Введите количество валюты "<<first<<" для обмена "<<std::endl;
        std::cout<<"\t-> ";
        SafeCin(amount,"");  
        int code  = terminal->Exchange(buf,first,second,amount);
        switch (code)
        {
            case 0 :
                Delimeter(30,'-');
                if(first!="BTC"){
                    std::cout<<"В результате обмена будет списано "<<std::setprecision(2)<<std::setw(10)<<std::internal<<buf.getCurrency(first)->count-account.getCurrency(first)->count<<" Валюты "<<first<<std::endl;
                }else{
                    std::cout<<"В результате обмена будет списано "<<std::setprecision(7)<<std::setw(10)<<std::internal<<buf.getCurrency(first)->count-account.getCurrency(first)->count<<" Валюты "<<first<<std::endl;
                }
                if(second!="BTC"){
                    std::cout<<"В результате обмена будет получено "<<std::setprecision(2)<<std::setw(10)<<std::internal<<buf.getCurrency(second)->count-account.getCurrency(second)->count<<" Валюты "<<second<<std::endl;
                }else{
                    std::cout<<"В результате обмена будет получено "<<std::setprecision(7)<<std::setw(10)<<std::internal<<buf.getCurrency(second)->count-account.getCurrency(second)->count<<" Валюты "<<second<<std::endl;
                }
                Delimeter(30,'-');
                
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
        Delimeter(30,'-');
    }
    account = buf;
    std::cout<<"Операция выполнена успешно"<<std::endl;
    Delimeter(30,'+');
    terminal->PrintPersonalAccount(account);
    terminal->UpdateCurrencyDate();
    Delimeter(30,'+');
}
