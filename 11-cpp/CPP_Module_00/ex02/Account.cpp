/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 15:09:49 by fbenkaci          #+#    #+#             */
/*   Updated: 2025/10/07 11:01:49 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit)
{
	 
	_accountIndex = _nbAccounts;
	_amount = initial_deposit;
	_totalAmount += initial_deposit;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
	_nbAccounts++;

	_displayTimestamp();
	std::cout << "index:" << _accountIndex 
			  << ";amount:" << _amount 
			  << ";created" << std::endl; 
}

int Account::getNbAccounts(void)
{
	return (_nbAccounts);
}

int Account::getTotalAmount(void)
{
	return (_totalAmount);
}

int Account::getNbDeposits(void)
{
	return (_totalNbDeposits);
}

int Account::getNbWithdrawals(void)
{
	return (_totalNbWithdrawals);
}

int Account::checkAmount(void) const
{
	return (_amount);
}

void Account::_displayTimestamp( void )
{
	std::tm *tm;
	std::time_t timestamp = std::time(0);
	tm = std::localtime(&timestamp);
	
	std::cout << "[";
	std::cout << tm->tm_year + 1900 << tm->tm_mon + 1; // Display year
	tm->tm_mday < 10 ? std::cout<< std::setw(2) << std::setfill('0') << tm->tm_mday :std::cout << tm->tm_mday; // Dislpay day
	tm->tm_hour < 10 ? std::cout<< std::setw(2) << std::setfill('0') << tm->tm_hour :std::cout << "_" << tm->tm_hour; // Display hour
	tm->tm_min < 10 ? std::cout << std::setw(2) << std::setfill('0') << tm->tm_min :std::cout << tm->tm_min; // Display minutes
	tm->tm_sec < 10 ? std::cout << std::setw(2) << std::setfill('0') << tm->tm_sec :std::cout << tm->tm_sec; // Display second
	std::cout << "] ";
}

void Account::displayAccountsInfos(void)
{
	_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts() 
			  << ";total:" << getTotalAmount() 
			  << ";deposits:" << getNbDeposits() 
			  << ";withdrawals:" << getNbWithdrawals() << std::endl;
}

void Account::makeDeposit(int deposit)
{
	int p_amount = _amount;
	_amount += deposit;
	_nbDeposits++;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";p_amount:" << p_amount
			  << ";deposit:" << deposit
			  << ";amount:" << checkAmount()
			  << ";nb_deposits:" << _nbDeposits << std::endl; 
	_totalAmount += deposit;
	_totalNbDeposits++;
}

bool Account::makeWithdrawal(int withdrawal)
{
	int p_amount = _amount;
	if (withdrawal <= p_amount)
	{
		_amount -= withdrawal;
		_nbWithdrawals++;
		_displayTimestamp();
		std::cout << "index:" << _accountIndex 
				  << ";p_amount:" << p_amount
				  << ";withdrawal:" << withdrawal
				  << ";amount:" << _amount
				  << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
		_totalAmount -= withdrawal;
		_totalNbWithdrawals++;
	}
	else
	{
		_displayTimestamp();
		std::cout << "index:" << _accountIndex 
				  << ";p_amount:" << p_amount
				  << ";withdrawal:refused" << std::endl;
	}

	return (true);
}

void Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex 
			  << ";amount:" << checkAmount() 
			  << ";deposits:" << _nbDeposits
			  << ";withdrawals:" << _nbWithdrawals << std::endl;
}

Account::~Account(void)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex 
			  << ";amount:" << checkAmount() 
			  << ";closed" << std::endl; 
}
