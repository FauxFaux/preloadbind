all: target

virus.so: virus.c
	$(CC) -D_GNU_SOURCE -fPIC -shared -o virus.so -ldl $<

virus.dylib: virus.c
	$(CC) -dynamiclib -o virus.dylib $<

help:
	@echo 'Going to start the app; run "nc localhost 13337" to quit it.'

bad: help target
	./target

linux: help target virus.so
	env LD_PRELOAD=/lib/x86_64-linux-gnu/libdl.so.2:./virus.so ./target

osx: help target virus.dylib
	env DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=./virus.dylib ./target



