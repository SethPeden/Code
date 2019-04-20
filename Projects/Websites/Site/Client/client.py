import requests

URL = 'http://localhost'
PORT = '3000'

response = requests.post(url = URL + ':' + PORT)

print(response.json())
