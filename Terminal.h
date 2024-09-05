#pragma once

#include "DataType.h"
#include "CurrencyRate.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

class Terminal{

private:
    static Terminal* Instance ;
    AccountData TerminalAccount;
    CurrencyRateList CurrencyDate;
    Terminal(){
        TerminalAccount = AccountData(
            10000.0,
            1000.0,
            1000.0,
            1000.0,
            1.5
        );
        CurrencyDate =  CurrencyRateList();
    }
public:
    Terminal(const  Terminal&  ) = delete;
    void operator=(const  Terminal& ) = delete;

    static Terminal* getInstance(){
        if(Instance==nullptr){
            Instance = new Terminal();
        }else{
            return Instance;
        }
    }
    void UpdateCurrencyDate(){
        srand( (unsigned)time(NULL) );
        for(int i =0;i<CurrencyDate.list.size();i++){
            //std::cout<<rand()%11<<std::endl;
            double change = 1.0 + (( rand()%11 ) - 5 )*0.01;
            //std::cout<<change<<std::endl;
            CurrencyDate.list[i].rate=CurrencyDate.list[i].rate*change;
        }
    }
    int Exchange(AccountData& account,std::string firstIn,std::string secondIn,double amount){
        bool flag = false;
        bool invert = false;
        int index = 9;
        for(int i =0;i<CurrencyDate.list.size();i++){
            if(CurrencyDate.list[i].first==firstIn && CurrencyDate.list[i].second==secondIn ){
                flag = true;
                index = i;
            }else if(CurrencyDate.list[i].first==secondIn && CurrencyDate.list[i].second==firstIn ){
                flag = true;
                index = i;
                invert = true;
            }
        }
        if(!flag ||amount<0){
            return 1;
        }

        double rate = 0.0;
        if(!invert){
            rate = CurrencyDate.list[index].rate;
        }else{
            rate = 1.0/CurrencyDate.list[index].rate;
        }

        if(account.getCurrency(firstIn)->count<amount){
            return 2;
        }
        if(TerminalAccount.getCurrency(secondIn)->count<amount/rate){
            return 3;
        }
        account.getCurrency(firstIn)->count-=amount;
        TerminalAccount.getCurrency(firstIn)->count+=amount;
        account.getCurrency(secondIn)->count+=amount/rate;
        TerminalAccount.getCurrency(secondIn)->count-=amount/rate;
        return 0;
    }
    void PrintTerminalAccount(){
        std::cout<<"Баланс Терминала : "<<std::endl;
        for(int i =0;i<TerminalAccount.list.size();i++){
            if(i!=4){
                std::cout<<std::setw(5)<<TerminalAccount.list[i].name<<"  :=  "<<std::setprecision(2)<<std::fixed<<TerminalAccount.list[i].count<<std::endl;
            }else{
                std::cout<<std::setw(5)<<TerminalAccount.list[i].name<<"  :=  "<<std::setprecision(7)<<std::fixed<<TerminalAccount.list[i].count<<std::endl;
            }
            
        }
    }
    void PrintPersonalAccount(const AccountData& PersonalAccount){
        std::cout<<"Баланс Пользователя : "<<std::endl;
        for(int i =0;i<PersonalAccount.list.size();i++){
            if(i!=4){
                std::cout<<std::setw(5)<<PersonalAccount.list[i].name<<"  :=  "<<std::setprecision(2)<<std::fixed<<PersonalAccount.list[i].count<<std::endl;
            }else{
                std::cout<<std::setw(5)<<PersonalAccount.list[i].name<<"  :=  "<<std::setprecision(7)<<std::fixed<<PersonalAccount.list[i].count<<std::endl;
            }
        }
    }
    void PrintCurrencyRate(){
        std::cout<<"Текущий обменный курс : "<<std::endl;
        for(int i =0;i<CurrencyDate.list.size();i++){
            if(i!=4){
                std::cout<<std::setw(5)<<CurrencyDate.list[i].first<<"  -> "<<std::setw(4)<<CurrencyDate.list[i].second<<"  :=  "<< std::setprecision(1)<<std::fixed<<CurrencyDate.list[i].rate<<std::endl;
            }else{
                std::cout<<std::setw(5)<<CurrencyDate.list[i].first<<"  -> "<<std::setw(4)<<CurrencyDate.list[i].second<<"  :=  "<< std::setprecision(7)<<std::fixed<<CurrencyDate.list[i].rate<<std::endl;
            }
        }
    }
};

Terminal* Terminal::Instance=new Terminal();