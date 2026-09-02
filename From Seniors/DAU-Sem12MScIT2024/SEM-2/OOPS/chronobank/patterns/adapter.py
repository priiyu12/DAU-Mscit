class OldTimeCreditSystem:
    def __init__(self):
        self.time_balance = 0

    def add_time(self, amount):
        self.time_balance += amount

    def deduct_time(self, amount):
        if amount <= self.time_balance:
            self.time_balance -= amount
        else:
            print("Not enough time credits!")

    def get_time_balance(self):
        return self.time_balance


class TimeAccountAdapter:
    def __init__(self, old_system):
        self.old_system = old_system

    def deposit(self, amount):
        self.old_system.add_time(amount)

    def withdraw(self, amount):
        self.old_system.deduct_time(amount)

    def get_balance(self):
        return self.old_system.get_time_balance()
