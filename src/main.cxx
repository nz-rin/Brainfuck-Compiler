#include "BfCompiler.hxx"
#include "BfLexer.hxx"
#include "Logger.hxx"

#include "BfBuffer.hxx"

int main(int argc, const char *argv[]){

	if(argc < 2){
		log_error_and_exit("\t[ERROR] Not enough Args\tbfc [bf source code]");
	}

	BfBuffer bfbuf(argv[1]);
	BfLexer bflex;

	std::vector<char> bf_tokens = bflex.lex_code(bfbuf);

	BfCompiler bfc;
	bfc.compile(bf_tokens);

	log_info("RUN SUCCESSFULL");
	return 0;
}
