// Author(s): Wieger Wesselink
// Copyright: see the accompanying file COPYING or copy at
// https://svn.win.tue.nl/trac/MCRL2/browser/trunk/COPYING
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
/// \file mcrl2/data/expression_traits.h
/// \brief Contains term traits for data_expression.

#ifndef MCRL2_DATA_TERM_TRAITS_H
#define MCRL2_DATA_TERM_TRAITS_H

#include <functional>
#include "mcrl2/core/term_traits.h"
#include "mcrl2/data/data_expression.h"
#include "mcrl2/data/bool.h"
#include "mcrl2/data/variable.h"
#include "mcrl2/data/exists.h"
#include "mcrl2/data/forall.h"
#include "mcrl2/data/detail/data_sequence_algorithm.h"
#include "mcrl2/utilities/exception.h"

namespace mcrl2
{

namespace core
{

/// \brief Contains type information for data expressions.
template <>
struct term_traits<data::data_expression>
{
  /// \brief The term type
  typedef data::data_expression term_type;

  /// \brief The variable type
  typedef data::variable variable_type;

  /// \brief The variable sequence type
  typedef data::variable_list variable_sequence_type;

  /// \brief The value true
  /// \return The value true
  static inline
  term_type true_()
  {
    return data::sort_bool::true_();
  }

  /// \brief The value false
  /// \return The value false
  static inline
  term_type false_()
  {
    return data::sort_bool::false_();
  }

  /// \brief Operator not
  /// \param p A term
  /// \return Operator not applied to p
  static inline
  term_type not_(term_type p)
  {
    return data::sort_bool::not_(p);
  }

  /// \brief Operator and
  /// \param p A term
  /// \param q A term
  /// \return Operator and applied to p and q
  static inline
  term_type and_(const term_type& p, const term_type& q)
  {
    return data::sort_bool::and_(p, q);
  }

  /// \brief Operator or
  /// \param p A term
  /// \param q A term
  /// \return Operator or applied to p and q
  static inline
  term_type or_(const term_type& p, const term_type& q)
  {
    return data::sort_bool::or_(p, q);
  }

  /// \brief Operator imp
  /// \param p A term
  /// \param q A term
  /// \return Operator or applied to p and q
  static inline
  term_type imp(const term_type& p, const term_type& q)
  {
    return data::sort_bool::implies(p, q);
  }

  /// \brief Operator forall
  /// \param d A sequence of variables
  /// \param p A term
  /// \return Operator forall applied to d and p
  static inline
  term_type forall(variable_sequence_type d, const term_type& p)
  {
    return data::forall(d, p);
  }

  /// \brief Operator exists
  /// \param d A sequence of variables
  /// \param p A term
  /// \return Operator exists applied to d and p
  static inline
  term_type exists(variable_sequence_type d, const term_type& p)
  {
    return data::exists(d, p);
  }

  /// \brief Test for value true
  /// \param t A term
  /// \return True if the term has the value true
  static inline
  bool is_true(const term_type& t)
  {
    return t == data::sort_bool::true_();
  }

  /// \brief Test for value false
  /// \param t A term
  /// \return True if the term has the value false
  static inline
  bool is_false(const term_type& t)
  {
    return t == data::sort_bool::false_();
  }

  /// \brief Test for operator not
  /// \param t A term
  /// \return True if the term is of type not
  static inline
  bool is_not(const term_type& t)
  {
    return data::sort_bool::is_not_application(t);
  }

  /// \brief Test for operator and
  /// \param t A term
  /// \return True if the term is of type and
  static inline
  bool is_and(const term_type& t)
  {
    return data::sort_bool::is_and_application(t);
  }

  /// \brief Test for operator or
  /// \param t A term
  /// \return True if the term is of type or
  static inline
  bool is_or(const term_type& t)
  {
    return data::sort_bool::is_or_application(t);
  }

  /// \brief Test for implication
  /// \param t A term
  /// \return True if the term is an implication
  static inline
  bool is_imp(const term_type& t)
  {
    return data::sort_bool::is_implies_application(t);
  }

  /// \brief Test for universal quantification
  /// \param t A term
  /// \return True if the term is an universal quantification
  static inline
  bool is_forall(const term_type& t)
  {
    return data::is_forall(t);
  }

  /// \brief Test for existential quantification
  /// \param t A term
  /// \return True if the term is an existential quantification
  static inline
  bool is_exists(const term_type& t)
  {
    return data::is_exists(t);
  }

  /// \brief Test for lambda abstraction
  /// \param t A term
  /// \return True if the term is a lambda expression
  static inline
  bool is_lambda(const term_type& t)
  {
    return data::is_lambda(t);
  }

  /// \brief Conversion from variable to term
  /// \param v A variable
  /// \return The converted variable
  static inline
  const term_type& variable2term(const variable_type& v)
  {
    return v;
  }

  /// \brief Test if a term is a variable
  /// \param t A term
  /// \return True if the term is a variable
  static inline
  bool is_variable(const term_type& t)
  {
    return data::is_variable(t);
  }

  /// \brief Returns the free variables of a term
  /// \param t A term
  /// \return The free variables of a term
  static inline
  variable_sequence_type free_variables(const term_type& t)
  {
    std::set<variable_type> v = data::find_free_variables(data::data_expression(t));
    return variable_sequence_type(v.begin(), v.end());
  }

  /// \brief Returns the intersection of two unordered sets of variables
  /// \param v A sequence of data variables
  /// \param w A sequence of data variables
  /// \return The difference of two sets.
  static inline
  variable_sequence_type set_intersection(const variable_sequence_type& v, const variable_sequence_type& w)
  {
    return data::detail::set_intersection(v, w);
  }

  /// \brief Returns the difference of two unordered sets of variables
  /// \param v A sequence of data variables
  /// \param w A sequence of data variables
  /// \return The difference of two sets.
  static inline
  variable_sequence_type set_difference(const variable_sequence_type& v, const variable_sequence_type& w)
  {
    return data::detail::set_difference(v, w);
  }

  /// \brief Test if a term is constant
  /// \param t A term
  /// \return True if the term is constant. N.B. It is unknown if the current implementation
  /// works for quantifier expressions.
  static inline
  bool is_constant(const term_type& t)
  {
    return data::find_variables(t).empty();
  }

  static inline
  const term_type& left(const term_type& t)
  {
    const data::data_expression_list& arguments = atermpp::aterm_cast<data::data_expression_list>(atermpp::list_arg2(t));
    assert(arguments.size() == 2);
    return *(arguments.begin());
  }

  static inline
  const term_type& right(const term_type& t)
  {
    const data::data_expression_list& arguments = atermpp::aterm_cast<data::data_expression_list>(atermpp::list_arg2(t));
    assert(arguments.size() == 2);
    return *(++(arguments.begin()));
  }

  static inline
  const term_type& not_arg(const term_type& t)
  {
    assert(is_not(t));
    const data::data_expression_list& arguments = atermpp::aterm_cast<data::data_expression_list>(atermpp::list_arg2(t));
    return arguments.front();
  }

  /// \brief Pretty print function
  /// \param t A term
  /// \return A pretty print representation of the term
  static inline
  std::string pp(const term_type& t)
  {
    return data::pp(t);
  }
};

} // namespace core

namespace data
{
/// \brief expression traits (currently nothing more than core::term_traits)
template < typename Expression >
struct expression_traits : public core::term_traits< Expression >
{
  // Type of expression that represents variables
  typedef mcrl2::data::variable variable_type;

  static bool is_true(data_expression const& e)
  {
    return sort_bool::is_true_function_symbol(e);
  }

  static bool is_false(data_expression const& e)
  {
    return sort_bool::is_false_function_symbol(e);
  }

  static bool is_application(data_expression const& e)
  {
    return data::is_application(e);
  }

  static bool is_abstraction(data_expression const& e)
  {
    return data::is_abstraction(e);
  }

  static const data_expression& head(data_expression const& e)
  {
    return application(e).head();
  }

  static const data_expression_list& arguments(data_expression const& e)
  {
    return atermpp::aterm_cast<data::data_expression_list>(atermpp::list_arg2(e));
  }

  static data_expression_list variables(data_expression const& a)
  {
    return data_expression_list(abstraction(a).variables());
  }

  static data_expression body(data_expression const& a)
  {
    return abstraction(a).body();
  }

  static data_expression replace_body(data_expression const& variable_binder, data_expression const& new_body)
  {
    return abstraction(abstraction(variable_binder).binding_operator(), abstraction(variable_binder).variables(), new_body);
  }

  template < typename Container >
  static application make_application(data_expression const& e, Container const& arguments)
  {
    return application(e, arguments);
  }

  static data_expression false_()
  {
    return sort_bool::false_();
  }

  static data_expression true_()
  {
    return sort_bool::true_();
  }

  static data_expression and_(data_expression const& e1, data_expression const& e2)
  {
    return sort_bool::and_(e1, e2);
  }

  static data_expression or_(data_expression const& e1, data_expression const& e2)
  {
    return sort_bool::or_(e1, e2);
  }
};

} // namespace core

} // namespace mcrl2

#endif // MCRL2_DATA_TERM_TRAITS_H
