#ifndef BF_LEXER_HXX
#define BF_LEXER_HXX

#include <string>
#include <vector>

#include "BfBuffer.hxx"

class BfLexer {
private:
	std::vector<char> bf_token;

public:
	BfLexer ();
	BfLexer(const BfLexer &) = delete;
	BfLexer(BfLexer &&) = delete;
	BfLexer &operator=(const BfLexer &) = delete;
	BfLexer &operator=(BfLexer &&) = delete;

	std::vector<char> lex_code(BfBuffer &source_code);
	void dump();
};

#endif
