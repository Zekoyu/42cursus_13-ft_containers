/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:44:08 by llefranc          #+#    #+#             */
/*   Updated: 17-03-2022 17:12 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

int	getTestNumber(int *nb);
std::string toString(int i);
void printTestName(const std::string& nbLine, std::string name, const std::string& info = "");
std::string NumberToString (int Number);

#endif