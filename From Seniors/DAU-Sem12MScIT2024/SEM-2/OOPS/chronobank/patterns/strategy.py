class TransferChargeStrategy:
    def calculate_charge(self, amount):
        pass


class NoChargeStrategy(TransferChargeStrategy):
    def calculate_charge(self, amount):
        return 0

class FixedChargeStrategy(TransferChargeStrategy):
    def calculate_charge(self, amount):
        return 10  # Fixed charge

class PercentageChargeStrategy(TransferChargeStrategy):
    def calculate_charge(self, amount):
        return amount * 0.05  # 5% Charge


class TransferContext:
    def __init__(self, strategy: TransferChargeStrategy):
        self.strategy = strategy

    def execute_transfer(self, sender_account, receiver_account, amount):
        charge = self.strategy.calculate_charge(amount)
        total_amount = amount + charge

        if sender_account.get_balance() >= total_amount:
            sender_account._balance -= total_amount
            receiver_account._balance += amount
            print(f"Transfer of {amount} Successful with Charge: {charge}")
        else:
            print("Insufficient Balance!")
