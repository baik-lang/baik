ifeq ($(PREFIX),)
    PREFIX := /usr/local/bin
endif

.PHONY: build install wasm wasm@docker html@docker
build:
	@if [ ! -d "dist" ]; then echo "Create dist directory..."; mkdir dist; fi
	@echo "Build BAIK source...."
	@cc -DBAIK_MAIN -DBAIK_GENERATE_INAC -DCS_MMAP baik.c -o dist/baik -Wall -std=c99 -lreadline 
	@echo "Binary path dist/baik"
install:
	@echo "install baik to $(PREFIX)/baik"
	@cp dist/baik $(PREFIX)
wasm:
	emcc wasm.c baik.c -o docs/playground/baik.js -Wall -std=c99 -s WASM=1
wasm@docker:
	docker run --rm -v $(PWD):/src -t apiaryio/emcc emcc wasm.c baik.c -o docs/playground/baik.js -Wall -std=c99 -s WASM=1
html@docker:
	docker run --rm -v $(PWD):/src -t apiaryio/emcc emcc wasm.c baik.c -o dist/baik.html -Wall -std=c99 -s WASM=1