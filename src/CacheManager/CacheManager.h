//
// Created by vladimir on 14.04.19.
//

#ifndef TECELASQL_CACHEMANAGER_H
#define TECELASQL_CACHEMANAGER_H


#include <string>

class CacheManager {
public:
    void setTimerOnKey(long expire);
    void stopTimer(std::string key);
};


#endif //TECELASQL_CACHEMANAGER_H
