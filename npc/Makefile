all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL"); # DO NOT REMOVE THIS LINE!!!
	verilator -Wall vsrc/our.v csrc/sim_main.cpp --cc --trace --exe --build;obj_dir/Vour;gtkwave wave.vcd
    
include ../Makefile
