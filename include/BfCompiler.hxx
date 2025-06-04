#ifndef BF_COMPILER_HXX
#define BF_COMPILER_HXX

#include <string>
#include <vector>


class BfCompiler{
private:
	int fd;

	void _create_file();
	void _write(const char *buffer, size_t buffer_size);
public:
	void compile(const std::vector<char> &tokens);
	~BfCompiler();
};

#endif
