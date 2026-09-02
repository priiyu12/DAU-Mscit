class User:
    def __init__(self, user_id, name, role, email=None, phone=None, address=None):
        self.user_id = user_id
        self.name = name
        self.role = role
        self.email = email
        self.phone = phone
        self.address = address

    def __str__(self):
        return f"User[{self.user_id}] - {self.name}"
    
    def get_user_id(self):
        return self.__user_id

    def get_name(self):
        return self.name

    def get_reputation(self):
        return self.__role

    def update_reputation(self, score):
        self.__role += score
