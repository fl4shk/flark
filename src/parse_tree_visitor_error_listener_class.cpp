#include "parse_tree_visitor_error_listener_class.hpp"
#include "src_code_pos_class.hpp"


namespace frost_hdl
{

ParseTreeVisitorErrorListener::ParseTreeVisitorErrorListener
	(SavedString s_filename)
	: _filename(s_filename)
{
}

ParseTreeVisitorErrorListener::~ParseTreeVisitorErrorListener()
{
}

void ParseTreeVisitorErrorListener::syntaxError
	(antlr4::Recognizer *recognizer, 
	antlr4::Token *offendingSymbol, size_t line, 
	size_t charPositionInLine, const std::string &msg, 
	std::exception_ptr e)
{
	//printerr("Syntax error on line ", line, 
	//	", position ", charPositionInLine, 
	//	":  ", msg, "\n");
	//exit(1);
	SrcCodePos(_filename, line, charPositionInLine).syntax_error(msg);
}
void ParseTreeVisitorErrorListener::reportAmbiguity
	(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa,
	size_t startIndex, size_t stopIndex, 
	bool exact, const antlrcpp::BitSet &ambigAlts, 
	antlr4::atn::ATNConfigSet *configs)
{
}

void ParseTreeVisitorErrorListener::reportAttemptingFullContext
	(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, 
	size_t startIndex, size_t stopIndex,
	const antlrcpp::BitSet &conflictingAlts, 
	antlr4::atn::ATNConfigSet *configs)
{
}

void ParseTreeVisitorErrorListener::reportContextSensitivity
	(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa, 
	size_t startIndex, size_t stopIndex, size_t prediction, 
	antlr4::atn::ATNConfigSet *configs)
{
}

} // namespace frost_hdl
