class AccountSubject:
    def __init__(self):
        self._observers = []

    def attach(self, observer):
        self._observers.append(observer)

    def detach(self, observer):
        self._observers.remove(observer)

    def notify(self, message):
        for observer in self._observers:
            observer.update(message)


class Observer:
    def update(self, message):
        pass


class LoggerObserver(Observer):
    def update(self, message):
        print(f"[Logger] {message}")

class NotificationObserver(Observer):
    def update(self, message):
        print(f"[Notification] {message}")
