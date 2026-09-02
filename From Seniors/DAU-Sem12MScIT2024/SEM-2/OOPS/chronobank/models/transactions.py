from abc import ABC, abstractmethod

class Transaction(ABC):
    @abstractmethod
    def execute(self):
        pass


class TransferTransaction(Transaction):
    def __init__(self, sender, receiver, amount):
        self.sender = sender
        self.receiver = receiver
        self.amount = amount

    def execute(self):
        if self.sender.get_balance() >= self.amount:
            self.sender._balance -= self.amount
            self.receiver._balance += self.amount
            print("Transfer Successful!")
        else:
            print("Insufficient Balance!")


class LoanTransaction(Transaction):
    def __init__(self, loan_account, amount):
        self.loan_account = loan_account
        self.amount = amount

    def execute(self):
        self.loan_account.take_loan(self.amount)
        print("Loan Granted!")


class InvestmentTransaction(Transaction):
    def __init__(self, investor_account):
        self.investor_account = investor_account

    def execute(self):
        self.investor_account.apply_interest()
        print("Interest Applied!")
