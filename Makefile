project := dmon
summary := A C++ library for building daemon processes

STD := c++20

library := lib$(project)
$(library).type := shared
define $(library).libs
 ext++
 fmt
 timber
endef

install := $(library)
targets := $(install)

include mkbuild/base.mk
