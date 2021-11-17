# -*- Makefile -*-
#
#

AM_CPPFLAGS = \
	$(MPI_CPPFLAGS)

compdir = $(pkglibdir)
comp_LTLIBRARIES = libbell.la
libbell_la_SOURCES = \
	bell.h \
	bell.cc

deprecated_libbell_sources =

libbell_la_LDFLAGS = -module -avoid-version

install-exec-hook:
	$(SST_REGISTER_TOOL) SST_ELEMENT_SOURCE     bell=$(abs_srcdir)
	$(SST_REGISTER_TOOL) SST_ELEMENT_TESTS      bell=$(abs_srcdir)/tests

##########################################################################
##########################################################################
##########################################################################


