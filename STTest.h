// Copyright (c) 2012, Matthias Hochgatterer <matthias.hochgatterer@gmail.com>
//       
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//       
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#import <Foundation/Foundation.h>

// STTest assert macros
#define STAssert(condition, description) \
	if (!(condition)) { \
		[[NSException exceptionWithName:NSInternalInconsistencyException reason:description userInfo:nil] raise]; \
	}

#define STAssertNotNil(isNotNil, description) STAssert(isNotNil != nil, description)
#define STAssertNil(isNil, description) STAssert(isNil == nil, description)

// STTest definition
static inline void STTest(NSString *name, void(^block)()){
	@try {
		block();
	} @catch (NSException *e){
		NSLog(@"%@ failed: %@", name, e);
	}
}

// STTest's self test
void testSTTest() {
	STTest(@"Test STTest's STAssert", ^{
		STAssert(true, @"Check for true should not fail.")
		STAssert(false, @"Check for false should fail.");
	});
	
	STTest(@"Test STTest's STAssertNil", ^{
		STAssertNil(nil, @"Check for nil should not fail.");
		STAssertNil(@"", @"Check for empty string should fail.");
	});
	
	STTest(@"Test STTest's STAssertNotNil", ^{
		STAssertNotNil(@"", @"Check for empty string should not fail.");
		STAssertNotNil(nil, @"Check for nil should fail.");
	});
}