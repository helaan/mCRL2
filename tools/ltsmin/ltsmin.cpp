// Author(s): Muck van Weerdenburg, Bert Lisser
// Copyright: see the accompanying file COPYING or copy at
// https://svn.win.tue.nl/trac/MCRL2/browser/trunk/COPYING
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
/// \file ltsmin.cpp

#define NAME "ltsmin"
#define AUTHOR "Muck van Weerdenburg"

#include "mcrl2/core/detail/struct.h"
#include "mcrl2/core/aterm_ext.h"
#include "ltsmin.h"
#include "mcrl2/core/messaging.h"
#include "mcrl2/utilities/command_line_interface.h"
#include "mcrl2/utilities/command_line_messaging.h"
#include "mcrl2/exception.h"

using namespace mcrl2::utilities;
using namespace mcrl2::core;

int traceLevel = 0, optimal = 0, classes = 0, add_state_parameter = 0;

struct t_tool_options {
  std::string inputname;
  std::string outputname;
  int         task;
};

bool parse_command_line(int ac, char** av, t_tool_options& options) {

  interface_description clinterface(av[0], NAME, AUTHOR,
    "minimise an LTS",
    "[OPTION]... INFILE OUTFILE\n",
    "Minimise the LTS in the SVC format from INFILE using bisimulation reduction and save the resulting LTS to OUTFILE.\n"
    "\n"
    "Note that the input SVC file must have been generated by lps2lts.");

  clinterface.
    add_option("equivalence", make_mandatory_argument("NAME"),
      "use equivalence NAME:\n"
      "  'strong' for strong bisimulation (default), or\n"
      "  'branching' for branching bisimulation\n"
      , 'e').
    add_option("add",
      "do not minimise but save a copy of the original LTS extended with a "
      "state parameter indicating the bisimulation class a state belongs to ", 'a').
    add_option("tau", make_mandatory_argument("ACTNAME"),
        "consider action with name ACTNAME to be an internal (tau) action");

  command_line_parser parser(clinterface, ac, av);

  if (parser.continue_execution()) {
    options.task = CMD_REDUCE;

    if (0 < parser.options.count("verbose") + parser.options.count("debug")) {
      traceLevel=1;
    }

    if (parser.options.count("equivalence")) {
      std::string eq_name(parser.option_argument("equivalence"));
      if (eq_name == "strong") {
        options.task = CMD_REDUCE;
      } else if (eq_name == "branching") {
        options.task = CMD_BRANCH_REDUCE;
      } else {
        parser.error("option -e/--equivalence has illegal argument '" + eq_name + "'");
      }
    }

    if (0 < parser.options.count("add")) {
      add_state_parameter = 1;
    }
    if (0 < parser.options.count("tau")) {
      add_tau_action(strdup(parser.option_argument("tau").c_str()));
    }

    if (parser.arguments.size() != 2) {
      parser.error("incorrect number of arguments");
    }
    options.inputname = parser.arguments[0];
    options.outputname = parser.arguments[1];
    if (options.inputname == options.outputname) {
      parser.error("input file and output file are not allowed to be the same");
    }
  }

  return parser.continue_execution();
}

int doReduce(t_tool_options const& options);
int doBranchReduce(t_tool_options const& options);

int main(int argc, char *argv[])
{
  MCRL2_ATERM_INIT(argc, argv)

  gsWarningMsg("the use of this tool is deprecated; use ltsconvert instead\n");

  try {
    t_tool_options options;

    if (parse_command_line(argc, argv, options)) {
      SVCbool indexed = SVCfalse;

      if ( SVCopen(inFile, const_cast < char* > (options.inputname.c_str()), SVCread, readIndex) )
      {
        throw mcrl2::runtime_error(options.inputname + ": " + std::string(SVCerror(SVCerrno)));
      } else {
        if ( SVCopen(outFile, const_cast < char* > (options.outputname.c_str()), SVCwrite, &indexed) )
        {
          throw mcrl2::runtime_error(options.outputname + ": " + std::string(SVCerror(SVCerrno)));
        }
      }

      if (options.task == CMD_BRANCH_REDUCE) {
        return doBranchReduce(options);
      }

      return doReduce(options);
    }
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
} /* main */

int doReduce(t_tool_options const& options)
  {
  SVCstateIndex initState = ReadData();
  Reduce();
  if ( add_state_parameter )
  {
    SVCbool b;
    SVCfile inf;
    SVCopen(&inf, const_cast < char* > (options.inputname.c_str()), SVCread, &b);
    WriteDataAddParam(&inf,initState,WITH_TAULOOPS);
  } else {
    WriteData(initState,WITH_TAULOOPS);
  }
  return 0;
  }

int doBranchReduce(t_tool_options const& options)
  {
  SVCstateIndex initState = ReadData();
  SCC();
//  initState = ReturnEquivalenceClasses(initState, DELETE_TAULOOPS);
  /* ATwarning("Number of states after deletion of tau loops: %d\n", nstate); */
  ReduceBranching();
  if ( add_state_parameter )
  {
    SVCbool b;
    SVCfile inf;
    SVCopen(&inf, const_cast < char* > (options.inputname.c_str()), SVCread, &b);
    WriteDataAddParam(&inf,initState,DELETE_TAULOOPS);
  } else {
    WriteData(initState, DELETE_TAULOOPS);
  }
  return 0;
  }
   /* doCompare */
int doCompare(void)
  {
  SVCstateIndex init1, init2;
  ReadCompareData(&init1, &init2);
  if (Compare(init1, init2)) return EXIT_NOTOK;
  if (traceLevel) ATwarning("Transition systems are strongly bisimilar\n");
  return EXIT_OK;
  }
   /* doCompare */
int doBranchCompare(void)
  {
  SVCstateIndex init1, init2;
  ReadCompareData(&init1, &init2);
  if (CompareBranching(init1, init2)) return EXIT_NOTOK;
  if (traceLevel) ATwarning("Transition systems are branching bisimilar\n");
  return EXIT_OK;
  } /* doCompare */
