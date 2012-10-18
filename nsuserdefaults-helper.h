#define SI static inline
SI NSUserDefaults *defaults() 						{ return [NSUserDefaults standardUserDefaults]; }
SI void defaults_init(NSDictionary *dictionary) 	{ [defaults() registerDefaults:dictionary]; }

SI void defaults_save()                     		{ [defaults() synchronize]; }
SI id defaults_object(NSString *key)         { return [defaults() objectForKey:key]; }

SI void defaults_post_notification(NSString *key) {
	[[NSNotificationCenter defaultCenter] postNotificationName:key object:nil userInfo:@{ @"value" : defaults_object(key) }];
}

SI void defaults_set_object(NSString *key, NSObject *object) {
	[defaults() setObject:object forKey:key];
	defaults_save();
	defaults_post_notification(key);
}

SI void defaults_remove(NSString *key) { [defaults() removeObjectForKey:key]; }

typedef void(^ValueChangedBlock)(id object);

SI void defaults_observe_object(NSString *key, ValueChangedBlock block) {
	[[NSNotificationCenter defaultCenter] addObserverForName:key object:nil queue:[NSOperationQueue mainQueue] usingBlock:^(NSNotification *n){
		block( [n.userInfo objectForKey:@"value"] );
	}];
}