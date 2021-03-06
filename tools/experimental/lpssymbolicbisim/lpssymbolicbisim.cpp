// Author(s): Thomas Neele
// Copyright: see the accompanying file COPYING or copy at
// https://github.com/mCRL2org/mCRL2/blob/master/COPYING
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
/// \file lpssymbolicbisim.cpp

#define TOOLNAME "lpssymbolicbisim"
#define AUTHORS "Thomas Neele"

//C++
#include <exception>
#include <cstdio>

//LPS
#include "mcrl2/lps/io.h"

//Tool framework
#include "mcrl2/data/bool.h"
#include "mcrl2/data/data_expression.h"
#include "mcrl2/data/lambda.h"
#include "mcrl2/data/parse.h"
#include "mcrl2/data/prover_tool.h"
#include "mcrl2/data/rewriter_tool.h"
#include "mcrl2/utilities/input_output_tool.h"

#include "forward_exploration.h"
#include "symbolic_bisim.h"
#include "simplify_lps.h"
#include "tool_mode.h"

using namespace mcrl2::utilities;
using namespace mcrl2::core;
using namespace mcrl2::lps;
using mcrl2::data::tools::rewriter_tool;
using mcrl2::utilities::tools::input_output_tool;
using namespace mcrl2::log;


class lpssymbolicbisim_tool: public rewriter_tool<input_output_tool>
{

protected:
  typedef rewriter_tool<input_output_tool> super;

  std::string m_invariant;
  running_mode m_mode;

  /// Parse the non-default options.
  void parse_options(const command_line_parser& parser)
  {
    super::parse_options(parser);

    m_mode = parser.option_argument_as<running_mode>("mode");
    if(parser.options.count("invariant") > 0)
    {
      m_invariant = parser.option_argument("invariant");
    }
  }

  void add_options(interface_description& desc)
  {
    super::add_options(desc);
    desc.add_option("mode", make_enum_argument<running_mode>("S")
      .add_value(partition_refinement, true)
      .add_value(exploration)
      .add_value(exploration_and_refinement)
      .add_value(simplify_lps),
      "execute in the given mode",'m');
    desc.
    add_option("invariant",
               make_mandatory_argument("expr"),
               "add invariant that makes up the only block in the initial partition",
               'i');
  }

public:
  lpssymbolicbisim_tool()
    : super(
      TOOLNAME,
      AUTHORS,
      "Output the minimal LTS under strong bisimulation",
      "Performs partition refinement on "
      "INFILE and outputs the resulting LTS. "
      "This tool is highly experimental. "),
      m_invariant("true")
  {}

  /// Runs the algorithm.
  /// Reads a specification from input_file,
  /// applies real time abstraction to it and writes the result to output_file.
  bool run()
  {
    mCRL2log(verbose) << "Parameters of lpssymbolicbisim:" << std::endl;
    mCRL2log(verbose) << "  input file:         " << m_input_filename << std::endl;
    mCRL2log(verbose) << "  output file:        " << m_output_filename << std::endl;
    mCRL2log(verbose) << "  data rewriter       " << m_rewrite_strategy << std::endl;

    stochastic_specification spec;
    load_lps(spec, input_filename());

    mcrl2::data::data_expression inv;
    if(m_mode == exploration || m_mode == exploration_and_refinement)
    {
      inv = mcrl2::data::forward_exploration_algorithm<stochastic_specification>(spec, m_rewrite_strategy).run();
    }
    else
    {
      inv = mcrl2::data::lambda(spec.process().process_parameters(), parse_data_expression(m_invariant, spec.process().process_parameters(), spec.data()));
    }
    if(m_mode == partition_refinement || m_mode == exploration_and_refinement)
    {
      mcrl2::data::symbolic_bisim_algorithm<stochastic_specification>(spec, inv, m_rewrite_strategy).run();
    }

    if(m_mode == simplify_lps)
    {
      mCRL2log(verbose) << "Simplifying ..." << std::endl;
      mcrl2::data::simplify_one_by_one(spec, m_rewrite_strategy);
      save_lps(spec, output_filename());
    }

    return true;
  }

};

int main(int argc, char** argv)
{
  return lpssymbolicbisim_tool().execute(argc, argv);
}
