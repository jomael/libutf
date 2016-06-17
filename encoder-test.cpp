#include "encoder.hpp"

#include <assert.h>

namespace {
	void TestUTF8(void);
} /* namespace */

int main(void){
	TestUTF8();
	return 0;
}

namespace {
	void TestUTF8(void){

		unsigned char encoded_byte = 0;

		/* defaults to UTF-8 */
		utfx::Encoder encoder;

		/* writes symbol 'delta' */
		/* UTF-32 : 0x0394       */
		/* UTF-8  : 0xce, 0x94   */
		encoder.Write(0x0394);

		auto read_count = encoder.Read(&encoded_byte, 1);
		assert(read_count == 1);
		assert(encoded_byte == 0xce);

		read_count = encoder.Read(&encoded_byte, 1);
		assert(read_count == 1);
		assert(encoded_byte == 0x94);

		read_count = encoder.Read(&encoded_byte, 1);
		assert(read_count == 0);
	}
} /* namespace */

