#ifndef BF_BUFFER_HXX
#define BF_BUFFER_HXX

#include <cstddef>

class BfBuffer {
private:
	char * code_buffer;
	size_t code_size;

public:
	BfBuffer(const BfBuffer &) = delete;
	BfBuffer(BfBuffer &&) = delete;
	BfBuffer &operator=(const BfBuffer &) = delete;
	BfBuffer &operator=(BfBuffer &&) = delete;

	BfBuffer(const char *bf_file);
	~BfBuffer();
	const char * get_buffer_ptr();
	size_t get_buffer_size();

};

#endif
