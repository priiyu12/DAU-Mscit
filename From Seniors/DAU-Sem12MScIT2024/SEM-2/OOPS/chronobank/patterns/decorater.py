from models.accounts import SavingTimeAccount

# Base Decorator Class
class AccountDecorator:
    def __init__(self, account):
        self.account = account

    def deposit(self, amount):
        self.account.deposit(amount)

    def withdraw(self, amount):
        self.account.withdraw(amount)

    def get_balance(self):
        return self.account.get_balance()


# Concrete Decorator for Notification Feature
class NotificationDecorator(AccountDecorator):
    def deposit(self, amount):
        super().deposit(amount)
        print(f"[Notification] Deposited {amount} hours.")

    def withdraw(self, amount):
        super().withdraw(amount)
        print(f"[Notification] Withdrawn {amount} hours.")
