#include "BfBuffer.hxx"

#include <fcntl.h>
#include <unistd.h>

#include "Logger.hxx"

BfBuffer::BfBuffer(const char *bf_code){
	int bf_fd = open(bf_code, O_RDONLY);
	if (bf_fd <= 0) {
		log_error_and_exit("  [ERROR] Failed to Open:", bf_code, "\n  ", strerror(errno));
	}

	size_t byte_size = lseek(bf_fd, 0,  SEEK_END);
	lseek(bf_fd, 0, SEEK_SET);

	BfBuffer::code_buffer = new char[byte_size];
	BfBuffer::code_size = byte_size;

	size_t read_res = read(bf_fd, BfBuffer::code_buffer, BfBuffer::code_size);
	if(read_res <= 0){
		log_error_and_exit("  [ERROR] Failed to Read from:", bf_code, "\n  ", strerror(errno));
	}

}

size_t BfBuffer::get_buffer_size(){
	return BfBuffer::code_size;
}

const char *BfBuffer::get_buffer_ptr(){
	return BfBuffer::code_buffer;
}

BfBuffer::~BfBuffer(){
	delete[] BfBuffer::code_buffer;
	BfBuffer::code_size = 0;
}
