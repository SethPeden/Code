import json
from datetime import datetime

class Person:
    def __init__(self, first_name, last_name, birthday, height, weight):
        self.first_name = first_name
        self.last_name = last_name
        self.birthday = datetime.strptime(birthday, '%b %d %Y')
        self.height = height
        self.weight = weight

    def to_json(self):
        json = {}
        json['first_name'] = self.first_name
        json['last_name'] = self.last_name
        json['birthday'] = self.birthday.strftime('%b %d %Y')
        json['height'] = self.height
        json['weight'] = self.weight
        return json

    @staticmethod
    def from_json(json):
        return Person(json['first_name'], json['last_name'], json['birthday'], json['height'], json['weight'])



data = {}

data['People'] = []
data['People'].append(Person('Seth', 'Peden', 'Dec 20 1996', 64, 200).to_json())

with open('data.json', 'w') as file:
    json.dump(data, file, sort_keys=True, indent=2)

with open('data.json', 'r') as file:
    data = json.load(file)
    print(data)
    seth = Person.from_json(data['People'][0])
    print(seth)
