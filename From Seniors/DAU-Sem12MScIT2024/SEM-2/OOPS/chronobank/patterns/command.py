class Command:
    def execute(self):
        pass

class DepositCommand(Command):
    def __init__(self, account, amount):
        self.account = account
        self.amount = amount

    def execute(self):
        self.account.deposit(self.amount)

class WithdrawCommand(Command):
    def __init__(self, account, amount):
        self.account = account
        self.amount = amount

    def execute(self):
        self.account.withdraw(self.amount)


class TransactionInvoker:
    def __init__(self):
        self.history = []

    def execute_command(self, command):
        command.execute()
        self.history.append(command)
