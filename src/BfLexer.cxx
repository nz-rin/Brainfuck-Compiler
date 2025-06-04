#include "BfLexer.hxx"
#include <iostream>

BfLexer::BfLexer(){
	bf_token = std::vector<char>();
}

bool _is_bf_token(char c){
	switch (c) {
		case '<': return true;
		case '>': return true;

		case '[': return true;
		case ']': return true;

		case '-': return true;
		case '+': return true;

		case '.': return true;
		case ',': return true;

		default: return false;
	}
}

std::vector<char> BfLexer::lex_code(BfBuffer &source_code){
	const char * code = source_code.get_buffer_ptr();
	for( size_t i = 0; i < source_code.get_buffer_size(); i++){
		if( _is_bf_token(code[i]) )
			bf_token.push_back(code[i]);
	}
	return bf_token;
}

void BfLexer::dump(){
	for ( char c : bf_token)
		std::cout << c;

	std::cout << std::endl;
}
