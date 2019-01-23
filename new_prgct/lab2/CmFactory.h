//
// Created by alex_ on 01.12.2018.
//

#ifndef LAB2_CMFACTORY_H
#define LAB2_CMFACTORY_H

#pragma once

#include <iostream>
#include <map>
#include <string>

#include "CommandList/Command.h"

typedef Command* (*RetFunc)();


class CmFactory {
private:
    std::map<std::string, RetFunc> Commands;
    static CmFactory* instance;

public:
    CmFactory()= default;
    CmFactory(const CmFactory &) = delete;
    CmFactory& operator= (const CmFactory &) = delete;

    static CmFactory * getGlobalInstance() {
        if (nullptr == instance) {
            instance = new CmFactory;
        }
        return instance;
    }

    bool CmRegister(const std::string &name, RetFunc proc){
        Commands.insert(std::make_pair(name,proc));
        std::cout <<"complete : [CMFACTORY:: CMREGISTER] : "<< name <<" registered"<<std::endl;
        return true;
    }

     Command* toCommand(const std::string &name){
         auto I = Commands.find( name );
         if ( I != Commands.end())
            return Commands[name]();
         return nullptr;
    }
};


#endif //LAB2_CMFACTORY_H
