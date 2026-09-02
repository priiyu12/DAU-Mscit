class AccountState:
    def handle(self, account):
        pass

class ActiveState(AccountState):
    def handle(self, account):
        print(f"Account {account.get_account_id()} is Active.")


class FrozenState(AccountState):
    def handle(self, account):
        print(f"Account {account.get_account_id()} is Frozen. Cannot perform operations.")


class ClosedState(AccountState):
    def handle(self, account):
        print(f"Account {account.get_account_id()} is Closed. Contact Admin.")


class AccountContext:
    def __init__(self, account):
        self.account = account
        self.state = ActiveState()

    def set_state(self, state: AccountState):
        self.state = state

    def apply_state(self):
        self.state.handle(self.account)
