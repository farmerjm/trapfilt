all:
	g++ filt.cc `root-config --cflags` `root-config --glibs` -o filt -g 
