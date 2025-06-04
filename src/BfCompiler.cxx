#include "BfCompiler.hxx"
#include "Logger.hxx"

#include <fcntl.h>
#include <stack>
#include <unistd.h>

BfCompiler::~BfCompiler(){
	int cres = close(BfCompiler::fd);
	if (cres == -1){
		log_error_and_sterror_and_exit("\t[ERROR] Failed to close file\n\t");
	}
}

void BfCompiler::_create_file(){
	fd = open("main.asm", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP| S_IWGRP );
	if (fd <= 0){
		log_error_and_sterror_and_exit("\t[ERROR] Failed to create file\n\t");
	}
}

void BfCompiler::_write(const char *buffer, size_t buffer_size){
	size_t wres = write(BfCompiler::fd, buffer, buffer_size);
	if (wres <= 0){
		log_error_and_sterror_and_exit("\t[ERROR] Failed to write to file\n\t");
	}
}

std::string_view _asm_start = {
	"[BITS 64]\n"
	"section .text\n"
		"\tglobal _start\n"
	"_start:\n"
		"\tpush rbp\n"
		"\tmov rbp, rsp\n"
};

std::string_view _asm_init = {
	"\tsub rsp, 30000\n"
	"\tmov rax, rbp\n"
};

std::string_view _asm_cell_inc = {
	"\tadd BYTE [rax], 1\n"
};

std::string_view _asm_cell_dec = {
	"\tsub BYTE [rax], 1\n"
};

std::string_view _asm_ptr_inc = {
	"\tadd rax, 1\n"
};

std::string_view _asm_ptr_dec = {
	"\tsub rax, 1\n"
};

std::string_view _asm_jz = {
	"\tmov bl, [rax]\n"
	"\ttest bl, bl\n"
	"\tjz "
};

std::string_view _asm_jnz = {
	"\tmov bl, [rax]\n"
	"\ttest bl, bl\n"
	"\tjnz "
};

std::string_view _asm_write = {
	"\tmov rsi, rax\n" //BUFFER
	"\tpush rax\n"

	"\tmov rax, 1\n" //WRITE
	"\tmov rdx, 1\n" //SIZE_T
	"\tmov rdi, 1\n" //FD
	"\tsyscall\n"
	"\tpop rax\n"
};

std::string_view _asm_read = {
	"\tmov rsi, rax\n" //BUFFER
	"\tpush rax\n"

	"\tmov rax, 0\n" //READ
	"\tmov rdx, 1\n" //SIZE_T
	"\tmov rdi, 1\n" //FD
	"\tsyscall\n"
	"\tpop rax\n"
};
std::string_view _asm_exit = {
	"\tmov rax, 60\n"
	"\tmov rdi, 1\n"
	"\tsyscall\n"
};


void BfCompiler::compile(const std::vector<char> &tokens){
	_create_file();

	_write(_asm_start.data(), _asm_start.size());
	_write(_asm_init.data(), _asm_init.size());
	std::string bfasm = "";

	size_t loop_counter = 0;

	std::string sb = "";

	std::stack<std::string> _conditional_start = std::stack<std::string>();
	std::stack<std::string> _conditional_end = std::stack<std::string>();


	size_t conditional_end_1 = 0;

	for(char token : tokens){
		switch ( token ) {
			case '+' :
			{
				bfasm.append(_asm_cell_inc);
			}
				break;
			case '-' :
			{
				bfasm.append(_asm_cell_dec);
			}
				break;
			case '<' :
			{
				bfasm.append(_asm_ptr_dec);
			}
				break;
			case '>' :
			{
				bfasm.append(_asm_ptr_inc);
			}
				break;
			case '.' :
			{

				bfasm += "\t; -- Write Syscall\n";
				bfasm.append(_asm_write);
			}
				break;
			case ',' :
			{
				bfasm += "\t; -- Read Syscall\n";
				bfasm.append(_asm_read);
			}
				break;
			case '[':
			{
				sb += "conditional_"; sb += std::to_string(loop_counter);
				_conditional_start.push(sb); sb.clear(); loop_counter++;

				bfasm += _conditional_start.top(); bfasm +=':';

				bfasm += " ; -- Jump if Zero\n";

				sb += "conditional_end_"; sb += std::to_string(conditional_end_1++);
				_conditional_end.push(sb); sb.clear();

				bfasm.append(_asm_jz); bfasm += _conditional_end.top(); bfasm += "\n";

			}
				break;
			case ']':
			{
				bfasm += "\n; -- Jump if Not Zero\n";

				bfasm.append(_asm_jnz); bfasm += _conditional_start.top();
				_conditional_start.pop();
				bfasm += "\n";
				bfasm += _conditional_end.top(); bfasm += ":\n";
				_conditional_end.pop();
			}
				break;
		}
	}
	_write(bfasm.data(), bfasm.size());

	_write(_asm_exit.data(), _asm_exit.size());
}
