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

		utfx::Encoder encoder;

		/* should default to UTF-8 */
		assert(encoder.GetMode() == utfx::Encoder::Mode::UTF8);

		/* should start in a reading state */
		assert(encoder.GetState() == utfx::Encoder::State::Reading);

		/* writes symbol 'delta' */
		/* UTF-32 : 0x0394       */
		/* UTF-8  : 0xce, 0x94   */
		encoder.Write(0x0394);

		/* now that data has been written, should be in a writing state */
		assert(encoder.GetState() == utfx::Encoder::State::Writing);

		auto read_count = encoder.Read(&encoded_byte, 1);
		assert(read_count == 1);
		assert(encoded_byte == 0xce);

		/* should be in a writing state, still */
		assert(encoder.GetState() == utfx::Encoder::State::Writing);

		read_count = encoder.Read(&encoded_byte, 1);
		assert(read_count == 1);
		assert(encoded_byte == 0x94);

		/* there should be no more data letft */
		read_count = encoder.Read(&encoded_byte, 1);
		assert(read_count == 0);

		/* should be back in a reading state */
		assert(encoder.GetState() == utfx::Encoder::State::Reading);
	}
} /* namespace */

