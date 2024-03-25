CXX = clang++
CPPFLAGS = -D__USE_MINGW_ANSI_STDIO=0
CXXFLAGS = -std=c++20 -pipe -O2 -g -gcodeview -march=i486 -mguard=cf -municode \
	-Wall -Wextra -Wpedantic -Werror=gnu -Wold-style-cast \
	-Wno-missing-field-initializers
LDFLAGS = -fuse-ld=lld -municode \
	-Wl,--major-subsystem-version=3,--minor-subsystem-version=10,--strip-all,--gc-sections,--pdb=$(@).pdb \
	-Wl,--Xlink=/Brepro,--Xlink=/dependentloadflag:0x800 \
	-Wl,--Xlink=/manifest:embed,--Xlink=/manifestinput:longPathAware.manifest \
	-Wl,--Xlink=-merge:.buildid=.rdata,--Xlink=-merge:.eh_fram=.rdata,--Xlink=-merge:.tls=.data \
	-Wl,--Xlink=/pdbaltpath:%_PDB%,--Xlink=/release \
#	-Wl,--Xlink=/safeseh
LDLIBS = -lntdll

strename : strename.cpp Release/fileextd.obj fileextd.lib