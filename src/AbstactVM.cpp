#include "AbstactVM.hpp"


namespace {

    std::string commands[] = {
            "pop",
            "dump",
            "add",
            "sub",
            "mul",
            "div",
            "mod",
            "print",
            "exit"
    };

    std::string commandsWithArgs[] = {
            "push",
            "assert"
    };

    std::string types[] = {
            "int8",
            "int16",
            "int32",
            "float",
            "double"
    };

    std::pair<std::string, eOperandType> stringType[] = {
            {"int8", Int8},
            {"int16", Int16},
            {"int32", Int32},
            {"float", Float},
            {"double", Double}
    };

    eOperandType getType(std::string const &string)
    {
        for (const auto& a : stringType)
        {
            if (a.first == string)
                return (a.second);
        }
        throw (std::logic_error("stringType"));
    }
}

int AbstactVM::getLine()
{
    if (_line == 0)
        _line++;
    return _line;
}

std::string AbstactVM::makeRegexStr(int isCommandUseArgs)
{
    size_t arrSize = 0;
    std::string spaces = "\\s*";
    std::string openBracket = "(" + spaces +"\\(" + spaces + ")*";
    std::string closeBracket = "(" + spaces +"\\)" + spaces + ")*";
    std::string number = "(" + spaces + R"([\+-]?\d+(\.\d*)?)" + spaces + ")";
    std::string	operand = "(" + spaces + "[-\\+\\*/]" + spaces + ")";
    std::string	comments = "(;[\\d\\D]*)?";
    std::string res =  spaces + "(";

    if (isCommandUseArgs == -1)
        return (spaces + comments);
    if (isCommandUseArgs == 1)
        arrSize = sizeof(commandsWithArgs) / sizeof(std::string);
    else if (isCommandUseArgs == 0)
        arrSize = sizeof(commands) / sizeof(std::string);
    for (size_t  i = 0; i < arrSize; i++)
    {
        if (isCommandUseArgs)
            res += commandsWithArgs[i];
        else
            res += commands[i];
        if (i != arrSize - 1)
            res += "|";
        else
            res += ")";
    }
    if (!isCommandUseArgs)
        return (res + spaces + comments);
    arrSize = sizeof(types) / sizeof(std::string);
    res += " (";
    for (size_t  i = 0; i < arrSize; i++)
    {
        res += types[i];
        if (i != arrSize - 1)
            res += "|";
        else
            res += ")";
    }
    res += "\\(("+ openBracket + number + closeBracket +
           "(" + operand + openBracket + number + closeBracket +")*)\\)" +
           spaces + comments;
    return (res);
}

void AbstactVM::lexerParser(std::string &str, VMLogic &vmLogic)
{
    std::cmatch result;
    std::regex regularWithArg(makeRegexStr(1)); // 1 for command with args
    std::regex regular(makeRegexStr(0)); // 0 for command without args
    std::regex regularComment(makeRegexStr(-1)); // -1 for comments

    Calculator calculator;
    std::string command;
    std::string type;
    std::string value;
    std::string comment;

    std::stringstream ss;

    if (vmLogic.getIsExitPresent() || std::regex_match(str.c_str(), result, regularComment))
        return;
    if (std::regex_match(str.c_str(), result, regularWithArg))
    {
        command = result[1];
        type = result[2];
        value = result[3];
        if (std::string(result[result.size() - 1])[0] == ';')
            comment = result[result.size() - 1];
        ss << std::setprecision(5) << calculator.calculatePolishString(value);
        vmLogic.commandExe(command, getType(type), ss.str());
        ss.str("");
    }
    else if (std::regex_match(str.c_str(), result, regular))
    {
        command = result[1];
        if (std::string(result[result.size() - 1])[0] == ';')
            comment = result[result.size() - 1];
        vmLogic.commandExe(command);
    }
    else
        throw std::logic_error("Invalid command");
    command = "";
    type = "";
    value = "";
}

void AbstactVM::launch(int argc, char *argv[])
{
    std::string str;
    std::ifstream file(argv[1]);

    VMLogic vmLogic;

    if (argc > 2)
        throw std::logic_error("Two many arguments");
    if (argc == 2)
    {
        if (!file.is_open())
            throw std::logic_error("Can not open your file");
        while (std::getline(file, str))
        {
            AbstactVM::_line++;
            lexerParser(str, vmLogic);
        }
    }
    if (argc == 1)
    {
        while (std::getline(std::cin, str))
        {
            if (str == ";;")
                break;
            AbstactVM::_line++;
            lexerParser(str, vmLogic);
        }
    }
    if (!vmLogic.getIsExitPresent())
        throw std::logic_error("Exit is not present");
}

AbstactVM::AbstactVM()
{
    _line = 0;
}