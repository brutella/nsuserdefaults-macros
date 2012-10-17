# Some handy NSUserDefaults marcos

This macros make it easy to store, fetch and observe values in the `NSUserDefaults`. I first discovered this macros in [kod](https://github.com/rsms/kod/blob/master/src/kconf.h) and now use it in [Justnotes](http://selfcoded.com/justnotes) as well.

### Show me some code.

Alright. How did you register default values the old way?

	NSUserDefaults *standardDefaults = [NSUserDefaults standardUserDefaults];
	NSDictionary *defaults = [NSDictionary dictionaryWithObjectsAndKeys: @"brutella@github.com", @"user/email"];
	[standardUserDefaults registerDefaults:defaults]
		
Now, do it the easy way.

	defaults_init( @{ @"user/email"  : @"brutella@github.com" });

Isn't that nice and much shorter? Let's take a look at more examples.
	
	// Set
    defaults_set_object(@"user/username", @"Matthias");
    defaults_set_object(@"user/logged-in", @(YES));
	
	// Get
	NSString *email = defaults_object(@"user/email");
	NSString *username = defaults_object(@"user/username");
	BOOL loggedIn = [defaults_object(@"user/logged-in") boolValue];

What's also nice is that you can observe a value and get a callback when it changed.

	defaults_observe_object(@"user/email", ^(NSString *email){
        ...
    });