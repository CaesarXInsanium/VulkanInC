all: compile  shaders/frag.spv shaders/vertex.spv
	fd --extension c --extension h | ctags -

compile: build
	meson compile -C $^

build:
	mkdir $@
	meson setup $@

shaders/frag.spv: shaders/frag.glsl
	glslc -o $@ -fshader-stage=frag $^
shaders/vertex.spv: shaders/vertex.glsl
	glslc -o $@ -fshader-stage=vertex $^

clean:
	rm -rf build
	rm shaders/frag.spv
	rm shaders/vertex.spv
