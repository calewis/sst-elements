// Copyright 2009-2017 Sandia Corporation. Under the terms
// of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S.
// Government retains certain rights in this software.
// 
// Copyright (c) 2009-2017, Sandia Corporation
// All rights reserved.
//
// Portions are copyright of other developers:
// See the file CONTRIBUTORS.TXT in the top level directory
// the distribution for more information.
//
// This file is part of the SST software package. For license
// information, see the LICENSE file in the top level directory of the
// distribution.

#include "sst_config.h"

#include "sst/core/element.h"

#include "simpleComponent.h"
#include "simpleClockerComponent.h"
#include "simpleDistribComponent.h"
#include "simpleRNGComponent.h"
#include "simpleStatisticsComponent.h"
#include "simpleMessageGeneratorComponent.h"
#include "simpleLookupTableComponent.h"
#include "simpleSubComponent.h"


using namespace SST;
using namespace SST::SimpleComponent;
using namespace SST::SimpleClockerComponent;
using namespace SST::SimpleDistribComponent;
using namespace SST::SimpleRNGComponent;
using namespace SST::SimpleStatisticsComponent;
using namespace SST::SimpleMessageGeneratorComponent;
using namespace SST::SimpleElementExample;
using namespace SST::SimpleSubComponent;

static Component* create_simpleComponent(SST::ComponentId_t id, SST::Params& params) 
{
    return new simpleComponent(id, params);
}

static Component* create_simpleClockerComponent(SST::ComponentId_t id, SST::Params& params) 
{
    return new simpleClockerComponent(id, params);
}

static Component* create_simpleDistribComponent(SST::ComponentId_t id, SST::Params& params) 
{
    return new simpleDistribComponent(id, params);
}

static Component* create_simpleRNGComponent(SST::ComponentId_t id, SST::Params& params) 
{
    return new simpleRNGComponent(id, params);
}

static Component* create_simpleStatisticsComponent(SST::ComponentId_t id, SST::Params& params)
{
    return new simpleStatisticsComponent(id, params);
}

static Component* create_simpleMessageGeneratorComponent(SST::ComponentId_t id, SST::Params& params)
{
    return new simpleMessageGeneratorComponent(id, params);
}

static Component* create_simpleLookupTableComponent(SST::ComponentId_t id, SST::Params& params)
{
    return new SimpleLookupTableComponent(id, params);
}

static Component* create_SubComponentLoader(SST::ComponentId_t id, SST::Params& params)
{
    return new SubComponentLoader(id, params);
}
static SubComponent* create_SubCompSender(SST::Component *owner, SST::Params& params)
{
    return new SubCompSender(owner, params);
}
static SubComponent* create_SubCompReceiver(SST::Component *owner, SST::Params& params)
{
    return new SubCompReceiver(owner, params);
}

static const ElementInfoParam simpleComponent_params[] = {
    { "workPerCycle", "Count of busy work to do during a clock tick.", NULL},
    { "commFreq", "Approximate frequency of sending an event during a clock tick.", NULL},
    { "commSize", "Size of communication to send.", "16"},
    { NULL, NULL, NULL}
};

static const ElementInfoParam simpleClockerComponent_params[] = {
    { "clock", "Clock frequency", "1GHz" },
    { "clockcount", "Number of clock ticks to execute", "100000"},
    { NULL, NULL, NULL }
};

static const ElementInfoParam simpleDistribComponent_params[] = {
	{ "count", "Number of random values to generate from the distribution", "1000"},
	{ "distrib", "Random distribution to use - \"gaussian\" (or \"normal\"), or \"exponential\"", "gaussian"},
	{ "mean", "Mean value to use if we are sampling from the Gaussian/Normal distribution", "1.0"},
	{ "stddev", "Standard deviation to use for the distribution", "0.2"},
	{ "lambda", "Lambda value to use for the exponential distribution", "1.0"},
	{ "binresults", "Print the results, only if value is \"1\"", "1"},
	{ "probcount", "Number of probabilities in discrete distribution"},
	{ "prob%(probcount)d", "Probability values for discrete distribution"},
  	{ NULL, NULL, NULL }
};

static const ElementInfoParam simpleRNGComponent_params[] = {
    { "seed_w", "The seed to use for the random number generator", "7" },
    { "seed_z", "The seed to use for the random number generator", "5" },
    { "seed", "The seed to use for the random number generator.", "11" },
    { "rng", "The random number generator to use (Marsaglia or Mersenne), default is Mersenne", "Mersenne"},
    { "count", "The number of random numbers to generate, default is 1000", "1000" },
    { "verbose", "Sets the output verbosity of the component", "0" },
    { NULL, NULL, NULL }
};

static const ElementInfoParam simpleStatisticsComponent_params[] = {
    { "seed_w", "The seed to use for the random number generator", "7" },
    { "seed_z", "The seed to use for the random number generator", "5" },
    { "seed", "The seed to use for the random number generator.", "11" },
    { "rng", "The random number generator to use (Marsaglia or Mersenne), default is Mersenne", "Mersenne"},
    { "count", "The number of random numbers to generate, default is 1000", "1000" },
    { NULL, NULL, NULL }
};

static const ElementInfoStatistic simpleStatisticsComponent_statistics[] = {
    { "stat1_U32", "Test Statistic 1 - Collecting U32 Data", "units", 1},   // Name, Desc, Enable Level 
    { "stat2_U64", "Test Statistic 2 - Collecting U64 Data", "units", 2},
    { "stat3_I32", "Test Statistic 3 - Collecting I32 Data", "units", 3},
    { "stat4_I64", "Test Statistic 4 - Collecting I64 Data", "units", 4},
    { "stat5_U32", "Test Statistic 5 - Collecting U32 Data", "units", 5},
    { "stat6_U64", "Test Statistic 6 - Collecting U64 Data", "units", 6},
    { NULL, NULL, NULL, 0 }
};

static const ElementInfoParam simpleMessageGeneratorComponent_params[] = {
    { "printStats", "Prints the statistics from the component", "0"},
    { "clock", "Sets the clock for the message generator", "1GHz" },
    { "sendcount", "Sets the number of sends in the simulation.", "1000" },
    { "outputinfo", "Sets the level of output information", "1" },
    { NULL, NULL, NULL }
};

static const char* simpleComponent_port_events[] = { "simpleComponent.simpleComponentEvent", NULL };

static const ElementInfoPort simpleComponent_ports[] = {
    {"Nlink", "Link to the simpleComponent to the North", simpleComponent_port_events},
    {"Slink", "Link to the simpleComponent to the South", simpleComponent_port_events},
    {"Elink", "Link to the simpleComponent to the East",  simpleComponent_port_events},
    {"Wlink", "Link to the simpleComponent to the West",  simpleComponent_port_events},
    {NULL, NULL, NULL}
};

static const char * simpleMessageGeneratorComponent_port_events[] = {"simpleMessageGeneratorComponent.simpleMessage", NULL};

static const ElementInfoPort simpleMessageGeneratorComponent_ports[] = {
    { "remoteComponent", "Sets the link for the message component, message components talk to each other exchanging simple messages", simpleMessageGeneratorComponent_port_events },
    { NULL, NULL, NULL }
};


static const ElementInfoParam simpleLookupTableComponent_params[] = {
    { "filename", "Filename to load as the table", ""},
    {"num_entities", "Number of entities in the sim", "1"},
    {"myid", "ID Number (0 <= myid < num_entities)", "0"},
    { NULL, NULL, NULL }
};



static const ElementInfoParam simpleSubComp_SubCompLoader_params[] = {
    {"clock", "Clock Rate", "1GHz"},
    {NULL, NULL, NULL}
};

static const ElementInfoSubComponentHook simpleSubComp_SubCompLoader_subComps[] = {
    {"mySubComp", "Subcomponent to do my real work", "SST::SimpleSubComponent::SubCompInterface"},
    {NULL, NULL, NULL}
};

static const ElementInfoParam simpleSubComp_SubCompSender_params[] = {
    {"sendCount", "Number of Messages to Send", "10"},
    {NULL, NULL, NULL}
};

static const ElementInfoStatistic simpleSubComp_SubCompSender_stats[] = {
    {"numSent", "# of msgs sent", "", 1},
    {NULL, NULL, NULL, 0}
};

static const ElementInfoPort simpleSubComp_SubCompSender_ports[] = {
    {"sendPort", "Sending Port", simpleMessageGeneratorComponent_port_events},
    {NULL, NULL, NULL}
};

static const ElementInfoParam simpleSubComp_SubCompReceiver_params[] = {
    {NULL, NULL, NULL}
};

static const ElementInfoStatistic simpleSubComp_SubCompReceiver_stats[] = {
    {"numRecv", "# of msgs sent", "", 1},
    {NULL, NULL, NULL, 0}
};

static const ElementInfoPort simpleSubComp_SubCompReceiver_ports[] = {
    {"recvPort", "Receiving Port", simpleMessageGeneratorComponent_port_events},
    {NULL, NULL, NULL}
};


static const ElementInfoSubComponent simpleElementSubComponents[] = {
    {
        .name = "SubCompSender",
        .description = "Sending Subcomponent",
        .printHelp = NULL,
        .alloc = create_SubCompSender,
        .params = simpleSubComp_SubCompSender_params,
        .stats = simpleSubComp_SubCompSender_stats,
        .provides = "SST::simpleSubComponent::SubCompInterface",
        .ports = simpleSubComp_SubCompSender_ports,
        .subComponents = NULL
    },
    {
        .name = "SubCompReceiver",
        .description = "Receiving Subcomponent",
        .printHelp = NULL,
        .alloc = create_SubCompReceiver,
        .params = simpleSubComp_SubCompReceiver_params,
        .stats = simpleSubComp_SubCompReceiver_stats,
        .provides = "SST::simpleSubComponent::SubCompInterface",
        .ports = simpleSubComp_SubCompReceiver_ports,
        .subComponents = NULL
    },
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
};

static const ElementInfoComponent simpleElementComponents[] = {
    { "simpleComponent",                                 // Name
      "Simple Demo Component",                           // Description
      NULL,                                              // PrintHelp
      create_simpleComponent,                            // Allocator
      simpleComponent_params,                            // Parameters
      simpleComponent_ports,                             // Ports
      COMPONENT_CATEGORY_PROCESSOR,                      // Category
      NULL                                               // Statistics
    },
    { "simpleClockerComponent",                          // Name
      "Clock Benchmark Component",                       // Description
      NULL,                                              // PrintHelp
      create_simpleClockerComponent,                     // Allocator
      simpleClockerComponent_params,                     // Parameters
      NULL,                                              // Ports
      COMPONENT_CATEGORY_UNCATEGORIZED,                  // Category
      NULL                                               // Statistics
    },
    { "simpleDistribComponent",                          // Name
      "Random Number Distribution Component",            // Description
      NULL,                                              // PrintHelp
      create_simpleDistribComponent,                     // Allocator
      simpleDistribComponent_params,                     // Parameters
      NULL,                                              // Ports
      COMPONENT_CATEGORY_UNCATEGORIZED,                  // Category
      NULL                                               // Statistics
    },
    { "simpleRNGComponent",                              // Name
      "Random number generation component",              // Description
      NULL,                                              // PrintHelp
      create_simpleRNGComponent,                         // Allocator
      simpleRNGComponent_params,                         // Parameters
      NULL,                                              // Ports
      COMPONENT_CATEGORY_UNCATEGORIZED,                  // Category
      NULL                                               // Statistics
    },
    { "simpleStatisticsComponent",                       // Name
      "Statistics Demo Component",                       // Description
      NULL,                                              // PrintHelp
      create_simpleStatisticsComponent,                  // Allocator
      simpleStatisticsComponent_params,                  // Parameters
      NULL,                                              // Ports
      COMPONENT_CATEGORY_UNCATEGORIZED,                  // Category
      simpleStatisticsComponent_statistics               // Statistics
    },
    { "simpleMessageGeneratorComponent",                 // Name
      "Messaging rate benchmark component",              // Description
      NULL,                                              // PrintHelp
      create_simpleMessageGeneratorComponent,            // Allocator
      simpleMessageGeneratorComponent_params,            // Parameters
      simpleMessageGeneratorComponent_ports,             // Ports
      COMPONENT_CATEGORY_NETWORK,                        // Category
      NULL                                               // Statistics
    },
    { "simpleLookupTableComponent",                      // Name
      "Demonstrates using a Shared Lookup Table",        // Description
      NULL,                                              // PrintHelp
      create_simpleLookupTableComponent,                 // Allocator
      simpleLookupTableComponent_params,                 // Parameters
      NULL,                                              // Ports
      COMPONENT_CATEGORY_UNCATEGORIZED,                  // Category
      NULL                                               // Statistics
    },
    {
        .name = "SubComponentLoader",
        .description = "Demonstrates subcomponents",
        .printHelp = NULL,
        .alloc = create_SubComponentLoader,
        .params = simpleSubComp_SubCompLoader_params,
        .ports = NULL,
        .category = COMPONENT_CATEGORY_UNCATEGORIZED,
        .stats = NULL,
        .subComponents = simpleSubComp_SubCompLoader_subComps
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL}
};

extern "C" {
    ElementLibraryInfo simpleElementExample_eli = {
        "simpleElementExample",                          // Name
        "A Simple Example Element With Demo Components", // Description
        simpleElementComponents,                         // Components
        NULL,                                            // Events 
        NULL,                                            // Introspectors 
        NULL,                                            // Modules 
        simpleElementSubComponents,                      // Subcomponents
        NULL,                                            // Partitioners
        NULL,                                            // Python Module Generator
        NULL                                             // Generators
    };
}


