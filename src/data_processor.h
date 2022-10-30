typedef unsigned int size_t;

namespace Data
{
	template <typename T> bool read_until(char terminator, T *output);
	template <typename T, size_t size> bool read(size_t n, char terminator, T(&array)[size]);
}
