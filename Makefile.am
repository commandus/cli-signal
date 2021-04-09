SUBDIRS = .
ACLOCAL_AMFLAGS = -I m4

commoncppflags = -Ithird_party

GEN = 

AM_CXXFLAGS=-std=c++11 -O0
COMMON_CPP_FLAGS = -D_GLIBCXX_USE_CXX11_ABI=0

BUILT_SOURCES = $(GEN)
CLEANFILES = $(GEN)

if USEJSON
LIB_STORAGE=
C_STORAGE=store-json.cpp 
H_STORAGE=
endif

if USELMDB
LIB_STORAGE=-l lmdb
C_STORAGE=store-lmdb.cpp
H_STORAGE=
endif

if USEMDBX
LIB_STORAGE=-l mdbx
C_STORAGE=store-lmdb.cpp
H_STORAGE=
endif

#
# Binaries
#
bin_PROGRAMS = cli-signal

commonlibs =

rapid_headers = \
	third_party/rapidjson/allocators.h       third_party/rapidjson/encodings.h        third_party/rapidjson/fwd.h             third_party/rapidjson/memorystream.h    third_party/rapidjson/prettywriter.h   third_party/rapidjson/schema.h  \
	third_party/rapidjson/writer.h           third_party/rapidjson/document.h         third_party/rapidjson/filereadstream.h  third_party/rapidjson/istreamwrapper.h  third_party/rapidjson/ostreamwrapper.h third_party/rapidjson/rapidjson.h \
	third_party/rapidjson/stream.h           third_party/rapidjson/encodedstream.h    third_party/rapidjson/filewritestream.h third_party/rapidjson/memorybuffer.h    third_party/rapidjson/pointer.h        third_party/rapidjson/reader.h \
	third_party/rapidjson/stringbuffer.h     third_party/rapidjson/error/en.h         third_party/rapidjson/error/error.h     third_party/rapidjson/internal/biginteger.h third_party/rapidjson/internal/dtoa.h  third_party/rapidjson/internal/itoa.h \
	third_party/rapidjson/internal/pow10.h   third_party/rapidjson/internal/stack.h   third_party/rapidjson/internal/strtod.h third_party/rapidjson/internal/diyfp.h  third_party/rapidjson/internal/ieee754.h third_party/rapidjson/internal/meta.h \
	third_party/rapidjson/internal/regex.h   third_party/rapidjson/internal/strfunc.h third_party/rapidjson/internal/swap.h \
	third_party/rapidjson/msinttypes/inttypes.h third_party/rapidjson/msinttypes/stdint.h

nobase_dist_include_HEADERS = \
	config-filename.h  config-json.h  errlist.h  utilstring.h \
	third_party/argtable3/argtable3.h \
	$(rapid_headers)

cli_signal_SOURCES = \
	cli-signal.cpp \
	config-filename.cpp  config-json.cpp  errlist.cpp  utilstring.cpp \
	$(C_STORAGE) \
	third_party/argtable3/argtable3.c

cli_signal__LDADD = $(commonlibs) $(LIB_STORAGE) -lpthread
cli_signal_CPPFLAGS = $(commoncppflags)

#
# Configs, readme, CMake etc.
#
configdir = $(datadir)
dist_config_DATA = \
   autogen.sh CMakeLists.txt CODE_OF_CONDUCT.md CONTRIBUTING.md COPYING HISTORY LICENSE README.md TODO \
   third_party/argtable3/README

#
# Tests
#
check_PROGRAMS =
TESTS = $(check_PROGRAMS)
