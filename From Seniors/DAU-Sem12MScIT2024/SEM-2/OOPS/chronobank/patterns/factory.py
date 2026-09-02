from models.accounts import SavingTimeAccount, InvestorAccount, LoanAccount

class AccountFactory:
    @staticmethod
    def create_account(account_type, account_id, user, balance=0, **kwargs):
        if account_type == "Saving":
            return SavingTimeAccount(account_id, user, balance)
        elif account_type == "Investor":
            return InvestorAccount(account_id, user, balance, kwargs.get('interest_rate', 10))
        elif account_type == "Loan":
            return LoanAccount(account_id, user, balance, kwargs.get('loan_limit', 500))
        else:
            raise ValueError("Invalid Account Type")
