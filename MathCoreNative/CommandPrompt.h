#pragma once
#include "OdBaseObject.h"
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <stack>
#include "IActionCmd.h"

typedef OdSmartPtr<class CommandPrompt> CommandPromptPtr;
class CommandPrompt
	: public OdBaseObject
{
	OD_RTTI_DECLARE(CommandPrompt, OdBaseObject);
public:
    CommandPrompt();

    bool processInput(std::string& input);
    void registerCommand(const std::string& command, IActionCmd* func);
    void appendCommand(const std::string& input);
    void appendPrompt(const std::string& input);

    int historySize() const;
    std::vector<std::string> getHistory() const;
    void removeLast(int total);
    bool executeAllPrompts();

    void undo();
    void redo();

    static std::vector<std::string> split(const std::string& str);
    static std::vector<std::string> split(const std::string& str, char delimiter);
private:

    void saveStateForUndo();

    std::map<std::string, IActionCmd*> commandMap;
    std::vector<std::string> History;
    std::stack<std::string> undoStack;
    std::stack<std::string> redoStack;
	// Inherited via OdBaseObject
	OdBaseObjectPtr Clone() override;
};

OD_RTTI_DEFINE(CommandPrompt, OdBaseObject)