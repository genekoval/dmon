project := dmon
summary := A C++ library for building daemon processes

STD := c++20

library := lib$(project)
$(library).type := shared
$(library).libs := ext++ fmt timber

install := $(library)
targets := $(install)

files = $(include) $(src) Makefile VERSION

include mkbuild/base.mk
