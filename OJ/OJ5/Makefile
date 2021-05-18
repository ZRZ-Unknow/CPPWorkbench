cc = g++
src_dir = .
build_dir ?= ./build
include_dir = .
prom = $(build_dir)/$(notdir $(CURDIR))-out
deps = $(shell find $(include_dir)/ -name "*.h")
src = $(shell find $(src_dir)/ -name "*.cpp")
obj = $(src:$(src_dir)/%.cpp=$(build_dir)/%.o)
subsrc = $(shell find $(src_dir)/ -name "*.cpp" | grep -v "./main.cpp")


$(prom): $(obj) $(build_dir)
	$(cc) -o $(prom) $(obj)

submit:$(subsrc) $(deps)
	zip submit.zip $(subsrc) $(deps)

run: $(obj)
	$(cc) -o $(prom) $(obj) && $(prom)

$(build_dir)/%.o: $(src_dir)/%.cpp $(deps)
	@mkdir -p $(dir $@)
	$(cc) -c $< -o $@

clean:
	rm -rf $(build_dir) submit.zip
