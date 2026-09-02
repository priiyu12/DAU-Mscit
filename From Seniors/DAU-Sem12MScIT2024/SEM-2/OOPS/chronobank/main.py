from patterns.facade import ChronoBankFacade
from patterns.builder import UserBuilder
from patterns.factory import AccountFactory
from patterns.command import DepositCommand, WithdrawCommand, TransactionInvoker
from patterns.observer import LoggerObserver, NotificationObserver, AccountSubject
from patterns.singleton import Logger
from patterns.state import AccountContext, ActiveState, FrozenState, ClosedState
from patterns.decorater import NotificationDecorator
from patterns.adapter import OldTimeCreditSystem, TimeAccountAdapter
from patterns.strategy import TransferContext, NoChargeStrategy, FixedChargeStrategy, PercentageChargeStrategy

# 202412048 Harsh Mehta
# 202412115 Hiten Thakkar
# 202412105 Aditi Shukla
# 202412068 Mahek Patel



def preload_data(users, accounts, facade, logger):
    from models.user import User
    from models.accounts import InvestorAccount, LoanAccount,SavingTimeAccount
    from patterns.state import AccountContext


    u1 = User("U101", "Harsh", "U", email="harsh@gmail.com")
    u2 = User("U102", "Hiten", "U",email="hiten@gmail.com", phone="1234567890")
    u3 = User("U103", "Aditi", "I",email="aditi@gmail.com")
    u4 = User("U104", "Mahek", "L",email="mahek@gmail.com")

    users[u1.user_id] = u1
    users[u2.user_id] = u2
    users[u3.user_id] = u3
    users[u4.user_id] = u4

    
    a1 = SavingTimeAccount("A101", u1,1000)

    a2 = SavingTimeAccount("A102", u2,500)

    a3 = InvestorAccount("A103", u3,2000 ,interest_rate=15.0)

    a4 = LoanAccount("A104", u4,0, loan_limit=1000)

    
    for acc in [a1, a2, a3, a4]:
        accounts[acc.get_account_id()] = {
            "account": acc,
            "context": AccountContext(acc),
            "decorated": False
        }

    print("PRELOADED 4 users and accounts created.")

def main():
    print("=== Welcome to ChronoBank CLI System ===")
    
    users = {}
    accounts = {}
    facade = ChronoBankFacade()
    invoker = TransactionInvoker()
    logger = Logger()
    subject = AccountSubject()

    # Attach default observers
    subject.attach(LoggerObserver())
    subject.attach(NotificationObserver())

    strategy_map = {
        1: NoChargeStrategy(),
        2: FixedChargeStrategy(),
        3: PercentageChargeStrategy()
    }
    preload_data(users, accounts, facade, logger)
    while True:
        print("\n--- Main Menu ---")
        print("1. Create User")
        print("2. Create Account")
        print("3. Deposit")
        print("4. Withdraw")
        print("5. Transfer Money")
        print("6. Take Loan")
        print("7. Apply Interest")
        print("8. Set Account State")
        print("9. Toggle Notification")
        print("10. Use Legacy Adapter Account")
        print("11. Check Account Balance")
        print("0. Exit")
        choice = input("Choose an option: ")

        if choice == "1": #Builder Pattern
            user_id = input("User ID: ")
            name = input("Name: ")
            role = input("Role: ")
            builder = UserBuilder(user_id, name, role)

            if input("Add Email? (y/n): ") == "y":
                builder.with_email(input("Email: "))
            if input("Add Phone? (y/n): ") == "y":
                builder.with_phone(input("Phone: "))
            if input("Add Address? (y/n): ") == "y":
                builder.with_address(input("Address: "))

            user = builder.build()
            users[user_id] = user
            logger.log(f"User created: {user.get_name()}")

        elif choice == "2": #Factory Pattern
            acc_id = input("Account ID: ")
            user_id = input("User ID: ")
            if user_id not in users:
                print("User not found!")
                continue
            print("Account Types: 1. Saving  2. Investor  3. Loan")
            acc_type = input("Choose Account Type: ")
            account = None
            if acc_type == "1":
                account = AccountFactory.create_account("Saving", acc_id, users[user_id])
            elif acc_type == "2":
                rate = float(input("Interest Rate: "))
                account = AccountFactory.create_account("Investor", acc_id, users[user_id], interest_rate=rate)
            elif acc_type == "3":
                limit = float(input("Loan Limit: "))
                account = AccountFactory.create_account("Loan", acc_id, users[user_id], loan_limit=limit)
            else:
                print("Invalid type")
                continue

            accounts[acc_id] = {
                "account": account,
                "context": AccountContext(account),
                "decorated": False
            }
            logger.log(f"Account created: {acc_id} - {account.account_type()}")

        elif choice == "3": #Command Pattern
            acc_id = input("Account ID: ")
            amount = float(input("Amount to Deposit: "))
            if amount <= 0:
                print("Deposit amount must be positive!")
                continue
            if acc_id in accounts:
                account = accounts[acc_id]["account"]
                if accounts[acc_id]["decorated"]:
                    account = NotificationDecorator(account)
                cmd = DepositCommand(account, amount)
                invoker.execute_command(cmd)
                print(f"Updated Balance for {account.get_account_id()} is {account.get_balance()} hours")
                subject.notify(f"{amount} deposited in Account {acc_id}")
            else:
                print("Account not found!")

        elif choice == "4": #Command Pattern
            acc_id = input("Account ID: ")
            amount = float(input("Amount to Withdraw: "))
            if amount <= 0:
                print("Withdraw amount must be positive!")
                continue
            if acc_id in accounts:
                account = accounts[acc_id]["account"]
                if accounts[acc_id]["decorated"]:
                    account = NotificationDecorator(account)
                cmd = WithdrawCommand(account, amount)
                invoker.execute_command(cmd)
                print(f"Updated Balance for {account.get_account_id()} is {account.get_balance()} hours")
                subject.notify(f"{amount} withdrawn from Account {acc_id}")
            else:
                print("Account not found!")

        elif choice == "5": #Strategy Pattern
            sender_id = input("Sender Account ID: ")
            receiver_id = input("Receiver Account ID: ")
            amount = float(input("Amount: "))
            if amount <= 0:
                print("Transfer amount must be positive!")
                continue
            if sender_id == receiver_id:
                print("Sender and receiver cannot be the same!")
                continue
            else:
                print("Transfer Strategy: 1. No Charge  2. Fixed  3. 5% Percentage")
                strat_choice = int(input("Choose: "))
                if sender_id in accounts and receiver_id in accounts:
                    context = TransferContext(strategy_map.get(strat_choice, NoChargeStrategy()))
                    context.execute_transfer(accounts[sender_id]["account"], accounts[receiver_id]["account"], amount)
                    subject.notify(f"Transfer of {amount} from {sender_id} to {receiver_id}")
                else:
                    print("One or both accounts not found!")

        elif choice == "6": #Observer Pattern
            acc_id = input("Loan Account ID: ")
            amount = float(input("Loan Amount: "))
            if amount <= 0:
                print("Loan amount must be positive!")
                continue
            if acc_id in accounts:
                loan_account = accounts[acc_id]["account"]
                if loan_account.loan_limit < amount:
                    print("Loan limit exceeded!")
                else:
                    print("Loan Granted!")
                    loan_account._balance += amount
                    loan_account.loan_limit -= amount
                    print(f"Updated Balance for {loan_account.get_account_id()} is {loan_account.get_balance()} hours")
                    subject.notify(f"Loan of {amount} granted to Account {acc_id}")
            else:
                print("Account not found!")

        elif choice == "7": #Facade Pattern
            acc_id = input("Investor Account ID: ")
            if acc_id in accounts:
                account = accounts[acc_id]["account"]
                if account.account_type() == "Investor Account":
                    facade.invest(account)
                else:
                    print("Provided account is not an Investor Account.")
            else:
                print("Account not found!")

        elif choice == "8": #State Pattern
            acc_id = input("Account ID: ")
            if acc_id in accounts:
                context = accounts[acc_id]["context"]
                print("State: 1. Active  2. Frozen  3. Closed")
                s = input("Set state: ")
                if s == "1":
                    context.set_state(ActiveState())
                elif s == "2":
                    context.set_state(FrozenState())
                elif s == "3":
                    context.set_state(ClosedState())
                context.apply_state()
            else:
                print("Account not found!")

        elif choice == "9": #Decorator Pattern
            acc_id = input("Account ID: ")
            if acc_id in accounts:
                accounts[acc_id]["decorated"] = not accounts[acc_id]["decorated"]
                print("Notification toggled.")
            else:
                print("Account not found!")

        elif choice == "10": #Adapter Pattern
            legacy = TimeAccountAdapter(OldTimeCreditSystem())
            while True:
                print("\nLegacy Adapter Menu:")
                print("1. Deposit Time")
                print("2. Withdraw Time")
                print("3. Check Time Balance")
                print("0. Back to Main Menu")
                sub = input("Choice: ")
                if sub == "1":
                    legacy.deposit(float(input("Amount: ")))
                elif sub == "2":
                    legacy.withdraw(float(input("Amount: ")))
                elif sub == "3":
                    print(f"Legacy Time Balance: {legacy.get_balance()} hours")
                elif sub == "0":
                    break

        elif choice == "11": 
            acc_id = input("Account ID: ")
            if acc_id in accounts:
                account = accounts[acc_id]["account"]
                print(f"Balance of Account {acc_id}: {account.get_balance()}")
            else:
                print("Account not found!")

        elif choice == "0":
            print("Exiting ChronoBank. Goodbye!")
            break

        else:
            print("Invalid option!")

if __name__ == "__main__":
    main()
