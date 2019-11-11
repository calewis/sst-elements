// Copyright 2013-2018 NTESS. Under the terms
// of Contract DE-NA0003525 with NTESS, the U.S.
// Government retains certain rights in this software.
//
// Copyright (c) 2013-2018, NTESS
// All rights reserved.
//
// Portions are copyright of other developers:
// See the file CONTRIBUTORS.TXT in the top level directory
// the distribution for more information.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#ifndef COMPONENTS_AURORA_RVMA_NIC_CMDS_H
#define COMPONENTS_AURORA_RVMA_NIC_CMDS_H

#include "sst/elements/hermes/rvma.h"

namespace SST {
namespace Aurora {
namespace RVMA {

#define FOREACH_CMD(NAME) \
        NAME(InitWindow)   \
        NAME(CloseWindow)   \
        NAME(WinIncEpoch)   \
        NAME(WinGetEpoch)   \
        NAME(WinGetBufPtrs)   \
        NAME(PostBuffer)   \
        NAME(PostOneTimeBuffer)   \
        NAME(Put)   \
        NAME(Mwait)   \
        NAME(NumCmds)  \

#define GENERATE_CMD_ENUM(ENUM) ENUM,
#define GENERATE_CMD_STRING(STRING) #STRING,

class NicCmd : public SST::Event {
  public:

	enum Type { 
        FOREACH_CMD(GENERATE_CMD_ENUM)
    } type;
	bool waitResp;
	bool useDelay;

    NicCmd() : Event() {}
	NicCmd( Type type ) : Event(), type( type ), waitResp(true), useDelay(true) {}


    void serialize_order(SST::Core::Serialization::serializer &ser)  override {
        Event::serialize_order(ser);
		ser & type;
	}
    ImplementSerializable(SST::Aurora::RVMA::NicCmd);
};


class InitWindowCmd : public NicCmd {
  public:
	InitWindowCmd() {}

	InitWindowCmd( Hermes::RVMA::VirtAddr addr, size_t threshold, Hermes::RVMA::EpochType type ) : 
		NicCmd(InitWindow), addr(addr), threshold(threshold), type(type)
	{}

	Hermes::RVMA::VirtAddr addr;
	size_t threshold;
	Hermes::RVMA::EpochType type;

    NotSerializable(InitWindowCmd);
};

class CloseWindowCmd : public NicCmd {
  public:
	CloseWindowCmd() {}

	CloseWindowCmd( Hermes::RVMA::Window window ) :
		NicCmd(CloseWindow), window(window)
	{}

	Hermes::RVMA::Window window;

    NotSerializable(CloseWindowCmd);
};

class WinIncEpochCmd : public NicCmd {
  public:
	WinIncEpochCmd() {}

	WinIncEpochCmd( Hermes::RVMA::Window window ) : 
		NicCmd(WinIncEpoch), window(window) 
	{}

	Hermes::RVMA::Window window;

    NotSerializable(WinIncEpochCmd);
};

class WinGetEpochCmd : public NicCmd {
  public:
	WinGetEpochCmd() {}

	WinGetEpochCmd( Hermes::RVMA::Window window ) : 
		NicCmd(WinGetEpoch), window(window) 
	{}

	Hermes::RVMA::Window window;

    NotSerializable(WinGetEpochCmd);
};

class WinGetBufPtrsCmd : public NicCmd {
  public:
	WinGetBufPtrsCmd() {}

	WinGetBufPtrsCmd( Hermes::RVMA::Window window, int max ) : 
		NicCmd(WinGetBufPtrs), window(window), max(max)  
	{}

	Hermes::RVMA::Window window;
	int max;

    NotSerializable(WinGetBufPtrsCmd);
};

class PutCmd : public NicCmd {
  public:
	PutCmd() {}

	PutCmd( const Hermes::MemAddr& srcAddr, size_t size, Hermes::ProcAddr proc, Hermes::RVMA::VirtAddr virtAddr, size_t offset, 
			Hermes::RVMA::Completion* completion, int* handle ) :
		NicCmd(Put), srcAddr(srcAddr), size(size), proc(proc), virtAddr(virtAddr), offset( offset ), completion(completion), handle(handle)
	{ 
		waitResp = false;
	}

	Hermes::MemAddr srcAddr;
	size_t size;
	Hermes::ProcAddr proc;
	Hermes::RVMA::VirtAddr virtAddr;
	size_t offset;
	Hermes::RVMA::Completion* completion;
	int* handle;

    NotSerializable(PutCmd);
};

class PostBufferCmd : public NicCmd {
  public:
	PostBufferCmd() {}

	PostBufferCmd( Hermes::MemAddr addr, size_t size, Hermes::RVMA::Completion* completion, Hermes::RVMA::Window window ) :
		NicCmd(PostBuffer), addr(addr), size(size), completion(completion), window(window)
	{
		waitResp = false;
	}

	Hermes::MemAddr addr;
	size_t size;
	Hermes::RVMA::Completion* completion;
	Hermes::RVMA::Window window;

    NotSerializable(PostBufferCmd);
};

class PostOneTimeBufferCmd : public NicCmd {
  public:
	PostOneTimeBufferCmd() {}

	PostOneTimeBufferCmd( Hermes::RVMA::VirtAddr winAddr, size_t threshold, Hermes::RVMA::EpochType type,
		Hermes::MemAddr bufAddr, size_t size, Hermes::RVMA::Completion* completion ) :
		NicCmd(PostOneTimeBuffer), winAddr(winAddr), threshold(threshold), type(type), bufAddr(bufAddr), size(size), completion(completion)
	{
		waitResp = false;
	}

	Hermes::RVMA::VirtAddr winAddr;
	size_t threshold;
	Hermes::RVMA::EpochType type;

	Hermes::MemAddr bufAddr;
	size_t size;
	Hermes::RVMA::Completion* completion;

    NotSerializable(PostOneTimeBufferCmd);
};

class MwaitCmd : public NicCmd {
  public:
	MwaitCmd() {}

	MwaitCmd( Hermes::RVMA::Completion* completion, bool blocking ) : 
		NicCmd(Mwait), completion(completion), blocking(blocking)
	{
		useDelay = false;
	}

	Hermes::RVMA::Completion* completion;
	bool blocking;
    NotSerializable(MwaitCmd);
};
}
}
}

#endif
