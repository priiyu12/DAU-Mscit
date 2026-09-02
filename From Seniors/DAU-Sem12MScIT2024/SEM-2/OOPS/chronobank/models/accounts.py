from abc import ABC, abstractmethod

class TimeAccount(ABC):
    def __init__(self, account_id, owner_name, balance):
        self.__account_id = account_id
        self.__owner_name = owner_name
        self._balance = balance 

    def get_account_id(self):
        return self.__account_id

    def get_owner_name(self):
        return self.__owner_name.get_name()

    def get_balance(self):
        return self._balance

    def deposit(self, amount):
        if amount > 0:
            self._balance += amount
        else:
            print("Invalid Amount")

    def withdraw(self, amount):
        if amount < self._balance:
            self._balance -= amount
        else:
            print("Invalid Amount")


    @abstractmethod
    def account_type(self):
        pass


class SavingTimeAccount(TimeAccount):
    def account_type(self):
        return "Saving Account"


class InvestorAccount(TimeAccount):
    def __init__(self, account_id, owner_name, balance, interest_rate):
        super().__init__(account_id, owner_name, balance)
        self.interest_rate = interest_rate

    def account_type(self):
        return "Investor Account"

    def apply_interest(self):
        self._balance += (self._balance * self.interest_rate)/100


class LoanAccount(TimeAccount):
    def __init__(self, account_id, owner_name, balance, loan_limit):
        super().__init__(account_id, owner_name, balance)
        self.loan_limit = loan_limit

    def account_type(self):
        return "Loan Account"

    def take_loan(self, amount):
        if amount <= self.loan_limit:
            self._balance += amount
        else:
            print("Loan limit exceeded!")
