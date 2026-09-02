from models.user import User
from models.accounts import SavingTimeAccount, InvestorAccount, LoanAccount
from models.transactions import TransferTransaction, LoanTransaction, InvestmentTransaction

class ChronoBankFacade:
    def create_user(self, user_id, name, user_type):
        return User(user_id, name, user_type)

    def create_basic_account(self, acc_id, user):
        return SavingTimeAccount(acc_id, user, 0)

    def create_investor_account(self, acc_id, user, interest_rate):
        return InvestorAccount(acc_id, user, 0, interest_rate)

    def create_loan_account(self, acc_id, user, loan_limit):
        return LoanAccount(acc_id, user, 0, loan_limit)

    def deposit(self, account, amount):
        account.deposit(amount)

    def transfer(self, sender, receiver, amount):
        transfer = TransferTransaction(sender, receiver, amount)
        transfer.execute()

    def take_loan(self, loan_account, amount):
        loan = LoanTransaction(loan_account, amount)
        loan.execute()

    def invest(self, account):
        investment = InvestmentTransaction(account)
        investment.execute()
