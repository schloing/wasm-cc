EMCC    = emcc
CFLAGS  = -s WASM=1 -s EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall']" -s EXPORTED_FUNCTIONS="['_WASMopenBuffer', '_init_cc', '_tokenize_source', '_parse_source', '_clean_cc', '_malloc', '_free']" -s ALLOW_MEMORY_GROWTH=1 -o a.out.html

SOURCES = wrapper.c cc-alculus/src/parser.c cc-alculus/src/tokenizer.c
OUTPUT  = a.out.js a.out.wasm a.out.html

all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(EMCC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OUTPUT)

.PHONY: all clean
