#include <vector>
#include <string>
#include <map>
#include <iostream>

#pragma once

namespace ArgumentParser {



class ArgParser {

    struct Params {
        bool _isString = false;
        bool _isInt = false;
        bool _isBool = false;

        char _shortName;
        char* _longName;
        char* _discription;

        std::vector<std::string> _values;

        Params(char shortName = ' ', char* longName = "", uint8_t typeOfData = 0) {
            _shortName = shortName;
            _longName = longName;
            if (typeOfData == 1) {
                _isString = true;
            } else if (typeOfData == 2) {
                _isInt = true;
            } else if (typeOfData == 3) {
                _isBool = true;
            }
        }

        Params& Default(const char* value) {
            _values.emplace_back(value);
            return *this;
        }

        Params& StoreValue(const std::string& value) {

            return *this;
        }
    };

    const char* name;
    std::vector<Params*> params;


public:

    ArgParser(const char* str) {
        name = str;
    }

    bool Parse(const std::vector<std::string>& args) {
        uint64_t countOfParams = 0;
        for (uint64_t i = 0; i < args.size(); ++i) {
            for (uint64_t j = 0; i < args[i].length(); ++i) {
                if (args[i].length() > 3 and args[i][j] == '-' and args[i][j + 1] != '-') {
                    const char nameOfParam = args[i][j + 1];
                    std::string valueOfParam = std::string(args[i].begin() + 2, args[i].end());
                    for (uint64_t k = 0; k < params.size(); ++k) {
                        if (params[k]->_shortName == nameOfParam) {
                            params[k]->_values.emplace_back(valueOfParam);
                        }
                    }
                } else if (args[i].length() > 3 and args[i][j] == '-' and args[i][j + 1] == '-') {
                    std::string valueOfParam;
                    std::string nameOfParam;
                    for (uint64_t k = 0; k < args[i].length(); ++i) {
                        if (args[i][k] == '=') {
                            nameOfParam = std::string(args[i], 0, k + 1);
                            valueOfParam = std::string(args[i], k + 2, args[i].length() - (k + 2));
                        }
                        for (uint64_t t = 0; t < params.size(); ++t) {
                            if (params[t]->_longName == nameOfParam) {
                                params[t]->_values.emplace_back(valueOfParam);
                            }
                        }
                    }
                } else {
                    return false;
                }
            }
        }
        return !args.empty();
    }

    Params& AddStringArgument(char shortName = ' ', char* longName = "") {
        Params* temp = new Params(shortName, longName, 1);
        params.emplace_back(temp);
        return *temp;
    }

    std::string GetStringValue(const std::string& nameOfParams) {
        for (uint64_t i = 0; i < params.size(); ++i) {
            if (params[i]->_longName == nameOfParams) {
                return params[i]->_values[0];
            }
        }
        return "";
    }

//    ArgParser::stringVars& GetStringValue(const std::string& nameOfVar) {
//        return stringVars;
//    }



};


} // namespace ArgumentParser