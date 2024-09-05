#pragma once

#include <string>
#include <vector>

class CurrencyRate{
public:
    std::string first= "" ;
    std::string second="" ; 
    double rate =0.0;
    double defaultRate = 0.0;
    CurrencyRate(std::string infirst,std::string insecond,double inrate =0.0){
        first = infirst;
        second = insecond;
        rate = inrate;
        defaultRate = inrate;
    }
};

class CurrencyRateList{
public:
    std::vector<CurrencyRate> list = {
        CurrencyRate("RUB","USD",70.0),
        CurrencyRate("RUB","EUR",90.0),
        CurrencyRate("USD","EUR",0.9),
        CurrencyRate("USD","USDT",1.0),
        CurrencyRate("BTC","USD",0.000017)
    };
    CurrencyRateList(){};
};
