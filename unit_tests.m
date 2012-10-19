#import <Cocoa/Cocoa.h>
#import "STTest.h"
#import "nsuserdefaults-helper.h"

void testNSUserDefaults(){
	STTest(@"Test unitialized user defaults", ^{
		STAssertNil(defaults_object(@"user/email"), @"Key user/email should return nil");
	});
	
	STTest(@"Test initializing user defaults", ^{
		defaults_init([NSDictionary dictionaryWithObject:@"brutella@github.com" forKey:@"user/email"]);
		STAssertNotNil(defaults_object(@"user/email"), @"Key user/email should not return nil");
	});
	
	STTest(@"Test setting bool object", ^{
		defaults_set_object(@"user/logged-in", [NSNumber numberWithBool:YES]);
		STAssert([defaults_object(@"user/logged-in") boolValue], @"Key user/logged should be true");
	});
	
	STTest(@"Test setting string object", ^{
		defaults_set_object(@"user/firstname", @"Matthias");
		STAssert([defaults_object(@"user/firstname") isEqualToString:@"Matthias"], @"Key user/firstname should be Matthias");
	});
	
	STTest(@"Test observing value", ^{
		__block BOOL called = NO;
		defaults_observe(@"user/email", ^(NSString *email){
			STAssert([email isEqualToString:@"brutella@gmail.com"], @"user/email must be brutella@gmail.com");
			called = YES;
		});
		defaults_set_object(@"user/email", @"brutella@gmail.com");
		STAssert(called, @"Observer block must be called");
	});
	
	// Cleanup user defaults
	NSDictionary *defaultsDictionary = [[NSUserDefaults standardUserDefaults] dictionaryRepresentation];
	for (NSString *key in [defaultsDictionary allKeys]) {
	    [[NSUserDefaults standardUserDefaults] removeObjectForKey:key];
	}
	[[NSUserDefaults standardUserDefaults] synchronize];
}

int main(int argc, char *argv[])
{
	@autoreleasepool {
		testNSUserDefaults();
	}
	return 0;
}