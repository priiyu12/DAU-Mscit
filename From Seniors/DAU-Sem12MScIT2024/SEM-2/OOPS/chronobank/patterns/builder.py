from models.user import User

class UserBuilder:
    def __init__(self, user_id, name, role):
        self.user_id = user_id
        self.name = name
        self.role = role
        self.email = None
        self.phone = None
        self.address = None

    def with_email(self, email):
        self.email = email
        return self

    def with_phone(self, phone):
        self.phone = phone
        return self

    def with_address(self, address):
        self.address = address
        return self

    def build(self):
        return User(self.user_id, self.name, self.role, self.email, self.phone, self.address)
