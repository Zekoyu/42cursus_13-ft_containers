/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:27:13 by llefranc          #+#    #+#             */
/*   Updated: 17-03-2022 17:17 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>

#include "utils.hpp"
#include "../include_your_files.hpp"

// Needed for testing
// #include "stl_like.hpp"
#include "print_type.hpp"

void    testVector(const int (&arrInt)[20], const std::string (&arrString)[20]);
void    testList(const int (&arrInt)[20], const std::string (&arrString)[20]);
void    testStack(const int (&arrInt)[20], const std::string (&arrString)[20]);
void    testQueue(const int (&arrInt)[20], const std::string (&arrString)[20]);
void    testMap(const int (&arrInt)[20], const std::string (&arrString)[20]);

#endif