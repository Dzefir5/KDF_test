#pragma once

#include <string>
#include <vector>


class AccountCurrencyData{
public:
    std::string name= "";
    double count =0.0;

    AccountCurrencyData(std::string inname,double incount){
        name = inname;
        count = incount;
    }
};

class AccountData{
public:
    std::vector<AccountCurrencyData> list = {
        AccountCurrencyData("RUB",0),
        AccountCurrencyData("USD",0),
        AccountCurrencyData("EUR",0),
        AccountCurrencyData("USDT",0),
        AccountCurrencyData("BTC",0)
    };
    AccountData(){};
    AccountData(
        double RUB_in,
        double USD_in,
        double EUR_in,
        double USDT_in,
        double BTC_in
    ){
        list[0].count=RUB_in;
        list[1].count=USD_in;
        list[2].count=EUR_in;
        list[3].count=USDT_in;
        list[4].count=BTC_in;
    };
    AccountCurrencyData* getCurrency(int index){
        if(index>=list.size()||index<0){
           return nullptr ; 
        }
        return &list[index];
    }
    AccountCurrencyData* getCurrency(std::string name){
        for(int i=0;i<list.size();i++){
            if(list[i].name==name){
                return &list[i];
            }
        }
        return nullptr;
    }
};
