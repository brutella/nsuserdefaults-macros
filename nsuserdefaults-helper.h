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